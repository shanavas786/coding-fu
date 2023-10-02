#!/usr/bin/env python3

import lox
from lox.token import TokenType, Token
from string import digits, ascii_letters

IDENTIFIER_CHARS = ascii_letters + digits + '_'

SINGLE_CHAR_TOKENS = {
    tk.value: tk
    for tk in (
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
    )
}

# list of single char token and its matching two char tokens
ONE_TWO_CHAR_TOKENS = {
    tk.value: (tk, next_tk)
    for tk, next_tk in (
        (TokenType.NOT, TokenType.NOT_EQUAL),
        (TokenType.EQUAL, TokenType.EQUAL_EQUAL),
        (TokenType.LESSER, TokenType.LESSER_EQUAL),
        (TokenType.GREATER, TokenType.GREATER_EQUAL),
    )
}

WHITESPACES = [" ", "\t", "\r"]

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


class Scanner:
    def __init__(self, source):
        self.source = source
        self.start = 0  # start index of the cursor token
        self.cursor = 0  # current position of scanner cursor
        self.line = 1  # line counter
        self.tokens = []

    def add_token(self, token_type, literal=None):
        lexeme = self.source[self.start : self.cursor]
        self.tokens.append(Token(token_type, lexeme, literal, self.line))

    def scan_tokens(self):
        while not self.is_end():
            self.start = self.cursor
            token = self.scan_token()

        self.tokens.append(Token(TokenType.EOF, "\0", None, self.line))
        return self.tokens

    def is_end(self):
        return self.cursor >= len(self.source)

    def scan_token(self):
        char = self.advance()

        if tk := SINGLE_CHAR_TOKENS.get(char):
            self.add_token(tk)
        elif tk := ONE_TWO_CHAR_TOKENS.get(char):
            # try to match the second character of two char token
            if self.advance(tk[1].value[1]):
                self.add_token(tk[1])
            else:
                self.add_token(tk[0])
        elif char in WHITESPACES:
            return
        elif char == "/":
            # handle / and comment
            if self.advance("/"):
                # The rest of the line is comment
                self.skip_til("\n")
            else:
                self.add_token(TokenType.SLASH)
        elif char == "\n":
            self.line += 1
        elif char == '"':
            self.scan_string()
        elif char in digits:
            self.scan_number()
        elif char in ascii_letters:
            self.scan_identifier()
        else:
            lox.Lox.error("Unexpected character", line=self.line)

    def advance(self, match=None):
        # if match is non None, advance only if the current char
        # matches
        char = self.peek()
        if match is None:
            self.cursor += 1
        elif char == match:
            self.cursor += 1
        else:
            char = None

        return char

    def peek(self):
        if not self.is_end():
            return self.source[self.cursor]

    def skip_til(self, char):
        while (not self.is_end()) and self.peek() != char:
            c = self.advance()
            if c == "\n":
                self.line += 1

    def scan_string(self):
        self.skip_til('"')
        if self.is_end():
            lox.Lox.error("Unterminated string", line=self.line)
            return

        # consume the end quote
        self.advance()
        literal = self.source[self.start + 1 : self.cursor - 1]
        self.add_token(TokenType.STRING, literal)

    def scan_number(self):
        while not self.is_end() and self.peek() in digits:
            self.advance()

        if self.is_end():
            literal = float(self.source[self.start : self.cursor])
            self.add_token(TokenType.NUMBER, literal)
            return

        elif self.peek() == ".":
            self.advance()
            while not self.is_end() and self.peek() in digits:
                self.advance()

        literal = float(self.source[self.start : self.cursor])
        self.add_token(TokenType.NUMBER, literal)

    def scan_identifier(self):
        while not self.is_end() and self.peek() in IDENTIFIER_CHARS:
            self.advance()

        lexeme = self.source[self.start:self.cursor]
        if lexeme in KEYWORDS:
            self.add_token(KEYWORDS[lexeme])
        else:
            self.add_token(TokenType.IDENTIFIER)
