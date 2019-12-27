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

    def output(self, value: int):
        print(value)

    def input(self):
        return 1

    def run(self) -> list:
        while True:
            inst = self.fetch()
            # opcode is last two digits
            opcode = inst % 100

            if opcode == 1:
                op1 = self.fetch()
                mode = inst // 100
                if mode % 10 == 0:
                    op1 = self.read(op1)

                op2 = self.fetch()
                mode = mode // 10
                if mode % 10 == 0:
                    op2 = self.read(op2)

                val = op1 + op2
                self.write(self.fetch(), val)
            elif opcode == 2:
                op1 = self.fetch()
                mode = inst // 100
                if mode % 10 == 0:
                    op1 = self.read(op1)

                op2 = self.fetch()
                mode = mode // 10
                if mode % 10 == 0:
                    op2 = self.read(op2)

                val = op1 * op2

                self.write(self.fetch(), val)
            elif opcode == 3:
                op1 = self.fetch()
                val = self.input()
                self.write(op1, val)
            elif opcode == 4:
                op1 = self.fetch()
                mode = inst // 100
                if mode % 10 == 0:
                    op1 = self.read(op1)

                self.output(op1)
            elif opcode == 99:
                break

        return self.code


if __name__ == "__main__":
    code = []
    with open("../inputs/day05.txt") as ip:
        code = list(map(int, ip.read().split(",")))
        machine = Intcode(code[:])
        result = machine.run()
