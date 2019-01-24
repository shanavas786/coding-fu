mod prelude;

use prelude::read_i32;

// Find the sum of all the multiples of 3 or 5 below N.

fn sum_of_multiples(n: i32) -> i32 {
    (1..n).rfold(0, |acc, x: i32| {
        if x % 3 == 0 || x % 5 == 0 {
            acc + x
        } else {
            acc
        }
    })
}

fn main() {
    let num = read_i32();
    for _ in 0..num {
        println!("{}", sum_of_multiples(read_i32()));
    }
}
