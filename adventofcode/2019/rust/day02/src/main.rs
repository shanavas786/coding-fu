use std::fs;
use prelude::nums_from_csv_str;

struct Intcode {
    code: Vec<u64>,
    pc: usize
}


impl Intcode {
    pub fn new(code: Vec<u64>) -> Self {
        Self {
            code,
            pc: 0,
        }
    }

    fn fetch(&mut self) -> u64 {
        let op = self.code[self.pc];
        self.pc += 1;
        op
    }

    fn read(&self, index: u64) -> u64 {
        self.code[index as usize]
    }

    fn write(&mut self, index: u64, value: u64) {
        self.code[index as usize] = value;
    }

    pub fn run(mut self) -> Vec<u64> {
        let mut opcode = self.fetch();

        while opcode != 99 {
            if opcode == 1 {
                let mut pc = self.fetch();
                let op1 = self.read(pc);
                pc = self.fetch();
                let op2 = self.read(pc);
                pc = self.fetch();
                self.write(pc, op1 + op2);
            } else if opcode == 2 {
                let mut pc = self.fetch();
                let op1 = self.read(pc);
                pc = self.fetch();
                let op2 = self.read(pc);
                pc = self.fetch();
                self.write(pc, op1 * op2);
            }
            opcode = self.fetch();
        }

        self.code
    }
}

fn patch_1202(mut code: Vec<u64>) -> Vec<u64> {
    code[1] = 12;
    code[2] = 2;
    code
}

fn patch(mut code: Vec<u64>, noun: u64, verb: u64) -> Vec<u64> {
    code[1] = noun;
    code[2] = verb;
    code
}

fn main() {
    let filename = "../../inputs/day02.txt";
    let contents = fs::read_to_string(filename)
        .expect("Something went wrong reading the input");

    let iter = nums_from_csv_str(&contents);
    let code: Vec<u64> = iter.collect();

    let machine = Intcode::new(patch_1202(code.to_owned()));
    let result = machine.run();

    println!("part 1: value at position zero {}", result[0]);

    for noun in 1..=99 {
        for verb in 1..=99 {
            let machine = Intcode::new(patch(code.to_owned(), noun, verb));
            let result = machine.run();

            if result[0] == 19690720 {
                println!("part 2: 100 * noun + verb is {}", 100 * noun + verb);
                return;
            }
        }
    }
}
