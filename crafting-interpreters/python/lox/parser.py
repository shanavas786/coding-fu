#!/usr/bin/env python3

from .token_types import TokenType, Token
from .error_logger import ErrorLogger
from .ast import Ast


class ParseError(RuntimeError):
    pass


class Parser:
    def __init__(self, tokens):
        self.current = 0
        self.tokens = tokens

    def peek(self) -> Token:
        return self.tokens[self.current]

    def previous(self) -> Token:
        return self.tokens[self.current - 1]

    def advance(self) -> Token:
        token = self.peek()
        if not self.is_end():
            self.current += 1
        return token

    def is_end(self) -> bool:
        return self.peek().token_type == TokenType.EOF

    def match(self, *token_types) -> bool:
        for token_type in token_types:
            if self.check(token_type):
                self.advance()
                return True
        return False

    def check(self, token_type: TokenType):
        return (not self.is_end()) and self.peek().token_type == token_type

    def consume(self, token_type: TokenType, message: str) -> Token:
        if self.check(token_type):
            return self.advance()

        self.error(self.peek(), message)

    def error(self, token: Token, message: str):
        ErrorLogger.error(token=token, message=message)
        raise ParseError()

    def parse(self) -> Ast.Expr:
        """
        program -> statement* EOF
        """
        statements = []
        while not self.is_end():
            statements.append(self.statement())
        return statements

    def statement(self):
        """
        statement -> expr_statement | print_statement
        """

        if self.match(TokenType.PRINT):
            return self.print_statement()
        return self.expr_statement()

    def print_statement(self):
        expr = self.expression()
        self.consume(TokenType.SEMI_COLON, "expected semicolon")
        return Ast.Print(expr)

    def expression_statement(self):
        expr = self.expression()
        self.consume(TokenType.SEMI_COLON, "expected semicolon")
        return Ast.Expression(expr)

    def expression(self) -> Ast.Expr:
        """
        expression -> equality
        """
        return self.equality()

    def equality(self) -> Ast.Expr:
        """
        equality -> comparison (('==' | '!=') equality)*
        """
        expr = self.comparison()

        while self.match(TokenType.EQUAL_EQUAL, TokenType.NOT_EQUAL):
            op = self.previous()
            right = self.equality()
            expr = Ast.Binary(expr, op, right)

        return expr

    def comparison(self) -> Ast.Expr:
        """
        comparison -> addition ((">" | ">=" | "<" | "<=") comparison)*
        """
        expr = self.addition()

        while self.match(
            TokenType.LESSER,
            TokenType.LESSER_EQUAL,
            TokenType.GREATER,
            TokenType.GREATER_EQUAL,
        ):
            op = self.previous()
            right = self.comparison()
            expr = Ast.Binary(expr, op, right)

        return expr

    def addition(self) -> Ast.Expr:
        """
        addition -> multiplication (("+" | "-") addition)*
        """
        expr = self.multiplication()

        while self.match(TokenType.PLUS, TokenType.MINUS):
            op = self.previous()
            right = self.addition()
            expr = Ast.Binary(expr, op, right)

        return expr

    def multiplication(self) -> Ast.Expr:
        """
        multiplication -> unary (("*" | "/") multiplication)*
        """
        expr = self.unary()

        while self.match(TokenType.STAR, TokenType.SLASH):
            op = self.previous()
            right = self.multiplication()
            expr = Ast.Binary(expr, op, right)

        return expr

    def unary(self) -> Ast.Expr:
        """
        unary -> ("!" | "-") unary | primary"
        """
        if self.match(TokenType.MINUS, TokenType.NOT):
            op = self.previous()
            right = self.unary()
            expr = Ast.Unary(op, right)
            return expr

        return self.primary()

    def primary(self) -> Ast.Expr:
        """
        primary -> NUMBER | STRING | "false" | "true" | "nil"
                   | "(" expression ")"
        """
        if self.match(TokenType.FALSE):
            return Ast.Literal(False)

        if self.match(TokenType.TRUE):
            return Ast.Literal(True)

        if self.match(TokenType.NIL):
            return Ast.Literal(None)

        if self.match(TokenType.STRING, TokenType.NUMBER):
            return Ast.Literal(self.previous().literal)

        if self.match(TokenType.LEFT_PAREN):
            expr = self.expression()
            self.consume(TokenType.RIGHT_PAREN, "Exprected ')' after expression")
            return Ast.Grouping(expr)

        self.error(self.peek(), "Expcted expression")

    def synchronize(self):
        while not self.is_end():
            if self.match(TokenType.SEMI_COLON):
                return

            for token_type in [
                TokenType.CLASS,
                TokenType.FUN,
                TokenType.VAR,
                TokenType.FOR,
                TokenType.IF,
                TokenType.WHILE,
                TokenType.PRINT,
                TokenType.RETURN,
            ]:
                if self.check(token_type):
                    return

            self.advance()
