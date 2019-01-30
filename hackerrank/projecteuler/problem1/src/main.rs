use prelude::read_i64;

// Find the sum of all the multiples of 3 or 5 below N.

fn sum_of_multiples(n: i64) -> i64 {
    let num_threes = (n - 1) / 3;
    let num_fives = (n - 1) / 5;
    let num_fifteens = (n - 1) / 15;

    let sum_threes = 3 * num_threes * (num_threes + 1) / 2;
    let sum_fives = 5 * num_fives * (num_fives + 1) / 2;
    let sum_fifteens = 15 * num_fifteens * (num_fifteens + 1) / 2;

    sum_threes + sum_fives - sum_fifteens
}

fn main() {
    let num = read_i64();
    for _ in 0..num {
        println!("{}", sum_of_multiples(read_i64()));
    }
}
