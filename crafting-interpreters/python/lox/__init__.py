import sys
from lox.scanner import Scanner

__VERSION__ = "0.0.1"



class Lox:
    had_error = False

    @classmethod
    def error(cls, message, line=None, token=None):
        if token:
            # handle EOF
            if token.token_type == TokenType.EOF:
                cls.report(token.line, "at the end", message)
            else:
                cls.report(token.line, f"near {token.lexeme}", message)
        else:
            cls.report(line, '', message)

    @classmethod
    def report(cls, line, where, message):
        print(f"[line {line}] Error {where}: {message}", file=sys.stderr)
        cls.had_error = True

    def run(self, source):
        scanner = Scanner(source)

        for tk in scanner.scan_tokens():
            print(tk)

    def run_file(self, file_path):
        with open(file_path, 'r') as f:
            source = f.read()

        self.run(source)

    def run_interactive(self):
        print(f"lox version {__VERSION__} \n")
        while True:
            try:
                line = input("> ")
                self.run(line)
            except (EOFError, KeyboardInterrupt):
                print("Bye!")
                break
