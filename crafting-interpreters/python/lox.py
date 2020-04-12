#!/usr/bin/env python3

import sys

from scanner import Scanner


class Lox:
    has_error = False

    def run(self, src: str):
        scanner = Scanner(src)
        for token in scanner.scan_tokens():
            print(token)

    def run_file(self, filename: str):
        with open(filename, "r") as f:
            src = f.read()
            self.run(src)

        if self.has_error:
            sys.exit(65)

    def run_interactive(self):
        print("plox version 0.0.1\n")
        while True:
            src_line = input("> ")
            self.run(src_line)
            self.has_error = False


if __name__ == "__main__":
    argv = sys.argv[1:]
    lox = Lox()

    if len(argv) > 1:
        print("Usage: plox [script]")
    elif len(argv) == 1:
        lox.run_file(argv[0])
    else:
        lox.run_interactive()
