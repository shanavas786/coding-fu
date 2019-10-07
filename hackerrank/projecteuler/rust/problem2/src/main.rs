use prelude::read_i64;

/// By considering the terms in the Fibonacci sequence whose
/// values do not exceed MAX, find the sum of the even-valued terms.

struct Fib {
    curr: i64,
    next: i64,
}

impl Fib {
    pub fn new() -> Fib {
        Fib {
            curr: 1,
            next: 1,
        }
    }

    pub fn even_sum_till(&mut self, max: i64) -> i64 {
        self.filter(|x| x % 2 == 0).take_while(|&x| x <= max).sum()
    }
}

impl Iterator for Fib {
    type Item = i64;

    fn next(&mut self) -> Option<i64> {
        let next = self.curr + self.next;

        self.curr = self.next;
        self.next = next;

        Some(self.curr)
    }
}

fn main() {
    let num = read_i64();
    for _ in 0..num {
        println!("{}", Fib::new().even_sum_till(read_i64()));
    }
}
