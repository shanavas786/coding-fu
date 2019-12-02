use std::fs::File;
use std::io::{BufReader, BufRead};


pub fn nums_from_file(path: &str) -> impl Iterator<Item = u64> {
    let input = File::open(path).expect("Failed to open file");
    let buffered = BufReader::new(input);

    buffered.lines()
            .map(|line| line.ok().unwrap().as_str().parse().unwrap())

}


#[test]
fn test_nums_from_file() {
    use std::io::Write;
    let path = "/tmp/nums.txt";

    let mut output = File::create(path).expect("Failed to create file");
    write!(output, "123\n90\n123\n").expect("ads");

    for num in nums_from_file(path) {
        println!("{}", num)
    }
}
