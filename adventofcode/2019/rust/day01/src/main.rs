
/// Fuel required to launch a given module is based on its mass. Specifically,
/// to find the fuel required for a module, take its mass, divide by three,
/// round down, and subtract 2.
///
/// For example:
///
/// For a mass of 12, divide by 3 and round down to get 4, then subtract 2 to
/// get 2.
/// For a mass of 14, dividing by 3 and rounding down still yields 4, so the
/// fuel required is also 2.
/// For a mass of 1969, the fuel required is 654.
/// For a mass of 100756, the fuel required is 33583.
/// The Fuel Counter-Upper needs to know the total fuel requirement.
/// To find it, individually calculate the fuel needed for the mass of each
/// module (your puzzle input), then add together all the fuel values.
///
/// What is the sum of the fuel requirements for all of the modules on your
/// spacecraft?

use prelude::nums_from_file;

fn fuel_required(mass: u64) -> u64 {
    let div = mass.div_euclid(3);
    if div > 2 {
        div - 2
    } else {
        0
    }
}

fn fuel_required_for_all(mass: u64) -> u64 {
    let mut total = 0;
    let mut mass = mass;

    while mass > 0 {
        mass = fuel_required(mass);
        total += mass
    }
    total
}

#[test]
fn test_fuel_required() {
    assert!(fuel_required(12) == 2);
    assert!(fuel_required(14) == 2);
    assert!(fuel_required(1969) == 654);
    assert!(fuel_required(100756) == 33583);
}

#[test]
fn test_fuel_required_for_all() {
    assert!(fuel_required_for_all(1969) == 966);
    assert!(fuel_required_for_all(100756) == 50346);
}

fn main() {
    let path = "../../inputs/day01.txt";
    let answer: u64 = nums_from_file(path).map(fuel_required).sum();
    println!("Total fuel required is: {}", answer);
    let answer: u64 = nums_from_file(path).map(fuel_required_for_all).sum();
    println!("Total fuel required considering fuel mass is: {}", answer);
}
