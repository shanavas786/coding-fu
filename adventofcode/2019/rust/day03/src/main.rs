use std::fs;
use std::string::String;


struct Point {
    x: u64,
    y: u64
}


impl Point {
    fn new(x: u64, y: u64) -> Self {
        Self {
            x,
            y
        }
    }
}

struct Line {
    from: Point,
    to: Point,

    /// steps from origin to reach `from`
    steps: u64,
}

impl Line {
    fn new(from: Point, to: Point) -> Self {
        Self {
            from,
            to
        }
    }

    fn get_intersection(self, other: Line) -> Option<Point> {
        let mut intersection = None

        if self.from.x == self.to.x && other.from.y == other.to.y {

        } else if self.from.y == self.to.y && other.from.x == other.to.x {
        }

        intersection
    }
}

fn main() {
    let filename = "../../inputs/day03.txt";
    let contents = fs::read_to_string(filename)
        .expect("Something went wrong reading the input");

    let mut lines = contents.lines();

    let e1str = lines.next().unwrap();
    let e2str = lines.next().unwrap();

    let edges1: Vec<String> = e1str.split(",").map(|s| s.to_owned()).collect();
    let edges2: Vec<String> = e2str.split(",").map(|s| s.to_owned()).collect();

    println!("{:?}", edges1);
    println!("{:?}", edges2);
}
