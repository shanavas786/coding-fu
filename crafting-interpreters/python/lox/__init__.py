import sys

from .scanner import Scanner
from .parser import Parser
from .resolver import Resolver
from .error_logger import ErrorLogger
from .interpreter import Interpreter


class Lox:
    def __init__(self):
        self.interpreter = Interpreter()

    def run(self, src: str):
        scanner = Scanner(src)
        parser = Parser(scanner.scan_tokens())
        ast = parser.parse()

        if (ErrorLogger.has_error):
            return

        resolver = Resolver(self.interpreter)
        resolver.resolve(ast)

        self.interpreter.interpret(ast)

    def run_file(self, filename: str):
        with open(filename, "r") as f:
            src = f.read()
            self.run(src)

        if ErrorLogger.has_error:
            sys.exit(65)

        if ErrorLogger.has_runtime_error:
            sys.exit(70)

    def run_interactive(self):
        print("plox version 0.0.1\n")
        while True:
            src_line = input("> ")
            self.run(src_line)
            ErrorLogger.has_error = False
