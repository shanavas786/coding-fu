use prelude::read_i64;

/// What is the largest prime factor of a given number
fn largest_prime_factor(mut num: i64) -> i64 {
    if num < 0 {
        return 1;
    } else if num < 2 {
        return num;
    }

    while num % 2 == 0 {
        num /= 2;
    }

    if num == 1 {
        return 2;
    }

    // num must be odd now
    let mut factor = 3;
    while factor <= (num as f64).sqrt() as i64 {
        if num == factor {
            break;
        } else if num % factor == 0 {
            num /= factor;
            factor = 3;
        } else {
            factor += 2;
        }
    }

    if num > 2 {
        num
    } else {
        factor
    }
}

fn main() {
    let num = read_i64();
    for _ in 0..num {
        println!("{}", largest_prime_factor(read_i64()));
    }
}

#[test]
fn test_max_prime() {
    assert_eq!(largest_prime_factor(10), 5);
    assert_eq!(largest_prime_factor(-1), 1);
    assert_eq!(largest_prime_factor(0), 0);
    assert_eq!(largest_prime_factor(1), 1);
    assert_eq!(largest_prime_factor(9), 3);
    assert_eq!(largest_prime_factor(2), 2);
    assert_eq!(largest_prime_factor(3), 3);
    assert_eq!(largest_prime_factor(17), 17);
    assert_eq!(largest_prime_factor(13195), 29);
    assert_eq!(largest_prime_factor( 31*6), 31);
}
