import sys

from .scanner import Scanner
from .parser import Parser
from .ast_printer import AstPrinter


class Lox:
    has_error = False

    def run(self, src: str):
        scanner = Scanner(src)
        parser = Parser(scanner.scan_tokens())
        ast = parser.parse()
        printer = AstPrinter()
        print(printer.print(ast))

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
