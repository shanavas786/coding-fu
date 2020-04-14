#!/usr/bin/env python3

from .token_types import TokenType, Token
from .error_logger import ErrorLogger

KEYWORDS = {
    kw.value: kw
    for kw in [
        TokenType.AND,
        TokenType.CLASS,
        TokenType.ELSE,
        TokenType.FALSE,
        TokenType.FOR,
        TokenType.FUN,
        TokenType.IF,
        TokenType.NIL,
        TokenType.OR,
        TokenType.PRINT,
        TokenType.RETURN,
        TokenType.SUPER,
        TokenType.THIS,
        TokenType.TRUE,
        TokenType.VAR,
        TokenType.WHILE,
    ]
}

# not all though
SINGLE_CHAR_TOKENS = [
    TokenType.LEFT_PAREN,
    TokenType.RIGHT_PAREN,
    TokenType.LEFT_BRACE,
    TokenType.RIGHT_BRACE,
    TokenType.COMMA,
    TokenType.DOT,
    TokenType.MINUS,
    TokenType.PLUS,
    TokenType.STAR,
    # TokenType.SLASH, conflicts with comment character
    TokenType.SEMI_COLON,
]


# list of single char token and its matching two char tokens
ONE_TWO_CHAR_TOKENS = [
    (TokenType.NOT, TokenType.NOT_EQUAL),
    (TokenType.EQUAL, TokenType.EQUAL_EQUAL),
    (TokenType.LESSER, TokenType.LESSER_EQUAL),
    (TokenType.GREATER, TokenType.GREATER_EQUAL),
]

WHITESPACES = [" ", "\t", "\r"]


class Scanner:
    def __init__(self, src: str):
        self.source = src
        # points to the next character
        self.current = 0
        self.line = 1
        # points to the starting index of lexeme in process
        self.start = 0
        self.tokens = []

    def scan_tokens(self):
        while not self.is_end():
            self.start = self.current
            self.scan_token()

        # add eof token
        self.tokens.append(Token(TokenType.EOF, "", None, self.line))
        return self.tokens

    def peek(self):
        return self.source[self.current]

    def peek2(self):
        return self.source[self.current + 1]

    def get_char(self):
        self.current += 1
        return self.source[self.current - 1]

    def expect_char(self, ch):
        if self.peek() == ch:
            return self.get_char()

    def add_token(self, token_type, literal=None):
        lexeme = self.source[self.start : self.current]
        self.tokens.append(Token(token_type, lexeme, literal, self.line))

    def is_end(self):
        return self.current >= len(self.source)

    def scan_token(self):
        ch = self.get_char()
        for tk in SINGLE_CHAR_TOKENS:
            if ch == tk.value:
                self.add_token(tk)
                return

        # handle one or two tokens
        for tk, mtk in ONE_TWO_CHAR_TOKENS:
            if ch == tk.value:
                self.add_token(mtk if self.expect_char("=") else tk)
                return

        # handle / and comment (//)
        if ch == "/":
            if self.expect_char("/"):
                # comment, ignore rest of the line
                while not (self.is_end() or self.peek() == "\n"):
                    self.get_char()
            else:
                self.add_token(TokenType.SLASH)
        elif ch in WHITESPACES:
            return
        elif ch == "\n":
            self.line += 1
        elif ch == '"':
            # handle string
            self.handle_string()
        elif ch.isalpha():
            # handle identifier
            self.handle_identifier()
        elif ch.isdecimal():
            self.handle_number()
        elif ch.isalpha():
            self.handle_identifier()
        else:
            ErrorLogger.error(self.line, f"Unexpected character {ch}")

    def handle_string(self):
        while not (self.is_end() or self.peek() == '"'):
            self.get_char()
            if self.peek() == "\n":
                self.line += 1

        if self.is_end():
            ErrorLogger.error(self.line, "Untermiated String")
            return

        # +1 to ignore starting "
        val = self.source[self.start + 1 : self.current]
        # consume ending "
        self.get_char()
        self.add_token(TokenType.STRING, val)

    def handle_identifier(self):
        while self.peek().isalnum():
            self.get_char()

        ident = self.source[self.start:self.current]
        token_type = KEYWORDS.get(ident, TokenType.IDENTIFIER)
        self.add_token(token_type)

    def handle_number(self):
        dotted = False

        while self.peek().isdecimal():
            self.get_char()

        if self.peek() == "." and self.peek2().isdecimal():
            dotted = True
            self.get_char()
            while self.peek().isdecimal():
                self.get_char()

        num = self.source[self.start:self.current]
        self.add_token(TokenType.NUMBER, float(num) if dotted else int(num))
