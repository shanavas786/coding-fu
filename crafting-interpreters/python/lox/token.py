#!/usr/bin/env python3

from enum import Enum, auto


class TokenType(Enum):
    # single char tokens
    LEFT_PAREN = "("
    RIGHT_PAREN = ")"
    LEFT_BRACE = "{"
    RIGHT_BRACE = "}"
    COMMA = ","
    DOT = "."
    MINUS = "-"
    PLUS = "+"
    STAR = "*"
    SLASH = "/"
    SEMI_COLON = ";"

    # one or two chars
    NOT = "!"
    NOT_EQUAL = "!="
    EQUAL = "="
    EQUAL_EQUAL = "=="
    LESSER = "<"
    LESSER_EQUAL = "<="
    GREATER = ">"
    GREATER_EQUAL = ">="

    # literals
    IDENTIFIER = "ident"
    STRING = "string"
    NUMBER = "number"

    # keywords
    AND = "and"
    CLASS = "class"
    ELSE = "else"
    FALSE = "false"
    FUN = "fun"
    FOR = "for"
    IF = "if"
    NIL = "nil"
    OR = "or"
    PRINT = "print"
    RETURN = "return"
    SUPER = "super"
    THIS = "this"
    TRUE = "true"
    VAR = "var"
    WHILE = "while"

    EOF = "eof"


class Token:
    def __init__(self, token_type, lexeme, literal, line):
        self.token_type = token_type
        self.lexeme = lexeme
        self.literal = literal
        self.line = line

    def __str__(self):
        return f"{self.token_type} {self.lexeme} {self.literal}"
