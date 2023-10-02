#!/usr/bin/env python3
import sys

from lox.scanner import Scanner
from lox.token import Token, TokenType


def test_greater():
    scanner = Scanner(">")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.GREATER, ">", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_greater_equal():
    scanner = Scanner(">=")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.GREATER_EQUAL, ">=", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]

    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_lesser():
    scanner = Scanner("<")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.LESSER, "<", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_lesser_equal():
    scanner = Scanner("<=")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.LESSER_EQUAL, "<=", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_not():
    scanner = Scanner("!")
    tokens = scanner.scan_tokens()
    actual = [Token(TokenType.NOT, "!", None, 1), Token(TokenType.EOF, "\0", None, 1)]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_not_equal():
    scanner = Scanner("!=")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.NOT_EQUAL, "!=", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_equal():
    scanner = Scanner("=")
    tokens = scanner.scan_tokens()
    actual = [Token(TokenType.EQUAL, "=", None, 1), Token(TokenType.EOF, "\0", None, 1)]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_equal_equal():
    scanner = Scanner("==")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.EQUAL_EQUAL, "==", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_equal_equal_equal():
    scanner = Scanner("===")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.EQUAL_EQUAL, "==", None, 1),
        Token(TokenType.EQUAL, "=", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_comment_bol():
    scanner = Scanner("// this is a comment")
    tokens = scanner.scan_tokens()
    actual = [Token(TokenType.EOF, "\0", None, 1)]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_comment_mol():
    scanner = Scanner(">=// this is a comment")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.GREATER_EQUAL, ">=", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_comment_multiline():
    scanner = Scanner(">=// this is a comment\n<=")
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.GREATER_EQUAL, ">=", None, 1),
        Token(TokenType.LESSER_EQUAL, "<=", None, 2),
        Token(TokenType.EOF, "\0", None, 2),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_string_singleline():
    scanner = Scanner('"str1" + "str2"')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.STRING, '"str1"', "str1", 1),
        Token(TokenType.PLUS, "+", None, 1),
        Token(TokenType.STRING, '"str2"', "str2", 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_string_multiline():
    scanner = Scanner('"str1 \n str2"')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.STRING, '"str1 \n str2"', "str1 \n str2", 2),
        Token(TokenType.EOF, "\0", None, 2),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_int():
    scanner = Scanner('123')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.NUMBER, "123", float(123), 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line

def test_float():
    scanner = Scanner('123.45')
    tokens = scanner.scan_tokens()
    print(list(map(lambda x: x.lexeme, tokens)))
    actual = [
        Token(TokenType.NUMBER, "123.45", float(123.45), 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_addition():
    scanner = Scanner('123.45+35.897')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.NUMBER, "123.45", float(123.45), 1),
        Token(TokenType.PLUS, "+", None , 1),
        Token(TokenType.NUMBER, "35.897", float(35.897) , 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_identifier():
    scanner = Scanner('cat - dog')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.IDENTIFIER, "cat", None, 1),
        Token(TokenType.MINUS, "-", None , 1),
        Token(TokenType.IDENTIFIER, "dog", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line


def test_keyword():
    scanner = Scanner('var if else while')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.VAR, "var", None, 1),
        Token(TokenType.IF, "if", None, 1),
        Token(TokenType.ELSE, "else", None, 1),
        Token(TokenType.WHILE, "while", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line

def test_statement():
    scanner = Scanner('var variable = 5 + 10;')
    tokens = scanner.scan_tokens()
    actual = [
        Token(TokenType.VAR, "var", None, 1),
        Token(TokenType.IDENTIFIER, "variable", None, 1),
        Token(TokenType.EQUAL, "=", None, 1),
        Token(TokenType.NUMBER, "5", float(5), 1),
        Token(TokenType.PLUS, "+", None, 1),
        Token(TokenType.NUMBER, "10", None, 1),
        Token(TokenType.SEMI_COLON, ";", None, 1),
        Token(TokenType.EOF, "\0", None, 1),
    ]
    assert len(tokens) == len(actual)
    for t, at in zip(tokens, actual):
        assert t.token_type == at.token_type
        assert t.lexeme == at.lexeme
        assert t.line == at.line
