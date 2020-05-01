#![feature(test)]

extern crate test;
use std::collections::HashMap;
use test::Bencher;
static mut A: [u32; 32] = [0; 32];

static BENCH_SIZE: u32 = 32;

unsafe fn fib_static_mut(n: u32) -> u32 {
    if n < 2 {
        return 1;
    }
    println!("{}", n);
    if A[n as usize] == 0 {
        A[n as usize] = fib_static_mut(n - 1) + fib_static_mut(n - 2);
    }

    A[n as usize]
}

fn fib_hashmap(n: u32) -> u32 {
    let mut cache = HashMap::new();
    cache.insert(0u32, 1u32);
    cache.insert(1u32, 1u32);

    fn fib_mem(n: u32, cache: &mut HashMap<u32, u32>) -> u32 {
        let val = cache.get(&n);
        match val {
            Some(&v) => v,
            None => {
                let a = fib_mem(n - 1, cache);
                let b = fib_mem(n - 2, cache);
                cache.insert(n, a + b);
                a + b
            }
        }
    }

    fib_mem(n, &mut cache)
}

struct Fib {
    cache: HashMap<u32, u32>,
}

impl Fib {
    fn new() -> Self {
        let mut cache = HashMap::new();
        cache.insert(0u32, 1u32);
        cache.insert(1u32, 1u32);

        Fib { cache: cache }
    }

    fn get(&mut self, n: u32) -> u32 {
        let val = self.cache.get(&n);
        match val {
            Some(&v) => v,
            None => {
                let a = self.get(n - 1);
                let b = self.get(n - 2);
                self.cache.insert(n, a + b);
                a + b
            }
        }
    }
}


// by Devdutt Shenoi(de-sh)
struct FibV {
    cache: Vec<u32>
}

impl FibV {
    fn new() -> Self {
        FibV{ cache: vec![1,1] }
    }

    fn gen(&mut self, n: u32) {
        let len = self.cache.len() - 1;
        for i in len..(n as usize) {
            self.cache.push(self.cache[i] + self.cache[i-1]);
        }
    }

    fn get(&mut self, n: u32) -> u32 {
        match self.cache.get(n as usize) {
            Some(a) => *a,
            None => {
                self.gen(n);
                *self.cache.get(n as usize).unwrap()
            }
        }
    }
}

#[bench]
fn bench_fib_static_mut(b: &mut Bencher) {
    b.iter(|| {
        (0..BENCH_SIZE)
            .map(|x| unsafe { fib_static_mut(x) })
            .collect::<Vec<u32>>()
    })
}

#[bench]
fn bench_fib_hashmap(b: &mut Bencher) {
    b.iter(|| (0..BENCH_SIZE).map(fib_hashmap).collect::<Vec<u32>>())
}

#[bench]
fn bench_fib_struct(b: &mut Bencher) {
    let mut fib = Fib::new();
    b.iter(|| (0..BENCH_SIZE).map(|x| fib.get(x)).collect::<Vec<u32>>())
}

#[bench]
fn bench_fib_vec(b: &mut Bencher) {
    let mut fib = FibV::new();
    b.iter(|| (0..BENCH_SIZE).map(|x| fib.get(x)).collect::<Vec<u32>>())
}

//    Compiling fib v0.1.0 (/home/shanavas/learn/coding-fu/rust/fib)
//     Finished bench [optimized] target(s) in 0.82s
//      Running target/release/deps/fib-d1b99b5a2fc5179f
//
// running 4 tests
// test bench_fib_hashmap    ... bench:      57,959 ns/iter (+/- 2,442)
// test bench_fib_static_mut ... bench:       4,143 ns/iter (+/- 46)
// test bench_fib_struct     ... bench:         709 ns/iter (+/- 32)
// test bench_fib_vec        ... bench:         122 ns/iter (+/- 0)
//
// test result: ok. 0 passed; 0 failed; 0 ignored; 4 measured; 0 filtered out
