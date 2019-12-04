#!/usr/bin/env python3


class Intcode:
    def __init__(self, code: list):
        self.code = code
        self.pc = 0

    def fetch(self) -> int:
        op = self.code[self.pc]
        self.pc += 1
        return op

    def read(self, index: int) -> int:
        return self.code[index]

    def write(self, index: int, value: int):
        self.code[index] = value

    def run(self) -> list:
        while True:
            opcode = self.fetch()

            if opcode == 1:
                op1 = self.read(self.fetch())
                op2 = self.read(self.fetch())
                val = op1 + op2
                self.write(self.fetch(), val)
            elif opcode == 2:
                op1 = self.read(self.fetch())
                op2 = self.read(self.fetch())
                val = op1 * op2
                self.write(self.fetch(), val)
            elif opcode == 99:
                break

        return self.code


def patch_1202(code: list) -> list:
    code[1] = 12
    code[2] = 2
    return code


if __name__ == "__main__":
    code = []
    with open("../inputs/day02.txt") as ip:
        code = list(map(int, ip.read().split(",")))
        machine = Intcode(patch_1202(code))
        result = machine.run()
        print(result)
