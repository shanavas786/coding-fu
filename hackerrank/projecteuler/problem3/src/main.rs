use prelude::{Prime, read_i64};

/// What is the largest prime factor of a given number
fn largest_prime_factor(prime: &mut Prime, num: i64) -> i64 {
    let mut max = num;

    let mut max_prime = 1;
    let mut i = 1;

    while i < max {
        if num % i == 0 {
            let factor = num / i;
            if prime.is_prime(factor) {
                return factor;
            }
            if prime.is_prime(i) {
                max_prime = i;
            }
            max = factor;
        }
        i += 1;
    }

    max_prime
}

fn main() {
    let mut prime = Prime::new();
    let num = read_i64();
    for _ in 0..num {
        println!("{}", largest_prime_factor(&mut prime, read_i64()));
    }
}

#[test]
fn test_max_prime() {
    let mut prime = Prime::new();

    assert_eq!(largest_prime_factor(&mut prime, 10), 5);
    assert_eq!(largest_prime_factor(&mut prime, 17), 17);
    assert_eq!(largest_prime_factor(&mut prime, 13195), 29);
    assert_eq!(largest_prime_factor(&mut prime, 31*6), 31);
}
