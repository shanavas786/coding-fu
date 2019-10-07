pub struct Prime {
    cache: Vec<i64>,
}

impl Prime {
    pub fn new() -> Prime {
        Prime {
            cache: vec![],
        }
    }

    pub fn is_prime(&mut self, num: i64) -> bool {
        if num == 1 {
            return false;
        }

        if !self.cache.is_empty() {
            let last = self.cache[self.cache.len() - 1];
            if num <= last {
                return self.cache.contains(&num);
            }
            for prime in &self.cache {
                if num % prime == 0 {
                    return false;
                }
            }
        }

        while let Some(prime) = self.next() {
            if num == prime {
                return true;
            } else if num % prime == 0 {
                return false;
            }
            if num/2 < prime {
                break;
            }
        }

        return true;
    }
}

impl Iterator for Prime {
    type Item = i64;

    fn next(&mut self) -> Option<Self::Item> {
        if self.cache.is_empty() {
            self.cache.push(2);
            return Some(2);
        }

        let mut num = self.cache[self.cache.len() - 1];
        if num == 2 {
            num += 1;
        }

        let is_prime = |n: i64| -> bool {
            !self.cache.iter().any(|prime| n % prime == 0)
        };

        while !is_prime(num) {
            num += 2;
        }

        self.cache.push(num);
        return Some(num);
    }
}


#[test]
fn test_is_prime() {
    let mut prime = Prime::new();
    assert!(!prime.is_prime(1));
    assert!(prime.is_prime(2));
    assert!(!prime.is_prime(80));
    assert!(!prime.is_prime(4));
    assert!(prime.is_prime(3));
    assert!(prime.is_prime(7));
    assert!(prime.is_prime(19));
    assert!(!prime.is_prime(91));
}

#[test]
fn test_next_prime() {
    let mut prime = Prime::new();
    assert_eq!(prime.next(), Some(2));
    assert_eq!(prime.next(), Some(3));
    assert_eq!(prime.next(), Some(5));
    assert_eq!(prime.next(), Some(7));
    assert_eq!(prime.next(), Some(11));
}
