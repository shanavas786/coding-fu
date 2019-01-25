use std::io;

macro_rules! make_reader {
    ($fname:ident, $type:ty) => {
        pub fn $fname() -> $type {
            let mut input = String::new();
            io::stdin()
                .read_line(&mut input)
                .expect("Failed to read line");
            let num: $type = input.trim().parse().expect("Please type a number");
            num
        }
    };
}

make_reader! {read_i64, i64}
