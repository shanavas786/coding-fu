#!/usr/bin/env python3

from .ast import Ast
from .error_logger import ErrorLogger
from .token_types import Token, TokenType


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
        program -> declaration* EOF
        """
        statements = []
        while not self.is_end():
            statements.append(self.declaration())
        return statements

    def declaration(self):
        """
        declaration -> funDecl | varDecl | statement
        """
        try:
            if self.match(TokenType.FUN):
                return self.function_declaration("function")

            if self.match(TokenType.VAR):
                return self.variable_declaration()
            return self.statement()
        except ParseError:
            self.synchronize()

    def function_declaration(self, kind):
        """
        funDecl -> IDENTIFIER "(" params? ")" block
        params -> IDENTIFIER ("," IDENTIFIER)*
        """
        name = self.consume(TokenType.IDENTIFIER, f"expected {kind} name.")
        self.consume(TokenType.LEFT_PAREN, f"expected ( after {kind} name.")

        params = []
        if not self.check(TokenType.RIGHT_PAREN):
            params.append(self.consume(TokenType.IDENTIFIER, "expected identifier."))
            while self.match(TokenType.COMMA):
                params.append(
                    self.consume(TokenType.IDENTIFIER, "expected identifier.")
                )
        self.consume(TokenType.RIGHT_PAREN, "expected ) after params")
        self.consume(TokenType.LEFT_BRACE, f"expected {{ before {kind} body.")
        body = self.block()

        return Ast.Function(name, params, body)

    def variable_declaration(self):
        """
        varDecl -> "var" IDENTIFIER ( "=" expression )? ;
        """
        name = self.consume(TokenType.IDENTIFIER, "expected identifier")

        val = None
        if self.match(TokenType.EQUAL):
            val = self.expression()

        self.consume(TokenType.SEMI_COLON, "expected ;")
        return Ast.Var(name, val)

    def statement(self):
        """
        statement -> if_statement
                     | while_statement
                     | for_statement
                     | expr_statement
                     | print_statement
                     | block
        """
        if self.match(TokenType.IF):
            return self.if_statement()

        if self.match(TokenType.WHILE):
            return self.while_statement()

        if self.match(TokenType.FOR):
            return self.for_statement()

        if self.match(TokenType.PRINT):
            return self.print_statement()

        if self.match(TokenType.LEFT_BRACE):
            return self.block()

        return self.expression_statement()

    def while_statement(self):
        """
        while_statement => "while" "(" expression ")" statement
        """
        self.consume(TokenType.LEFT_PAREN, "Expected (")
        cond = self.expression()
        self.consume(TokenType.RIGHT_PAREN, "Expected )")
        body = self.statement()

        return Ast.While(cond, body)

    def for_statement(self):
        """
        for_statement => "for" "(" (varDecl | expression_statement | ";")
                                   (expression)? ;
                                   (expression)?")" statement
        """
        self.consume(TokenType.LEFT_PAREN, "Expected (")

        if self.match(TokenType.SEMI_COLON):
            init = None
        if self.match(TokenType.VAR):
            init = self.variable_declaration()
        else:
            init = self.expression_statement()

        cond = Ast.Literal(True)
        if not self.check(TokenType.SEMI_COLON):
            cond = self.expression()

        self.consume(TokenType.SEMI_COLON, "expected ;")

        increment = None
        if not self.check(TokenType.RIGHT_PAREN):
            increment = self.expression()

        self.consume(TokenType.RIGHT_PAREN, "expected )")

        body = self.statement()

        if increment is not None:
            body = Ast.Block([body, Ast.Expression(increment)])

        body = Ast.While(cond, body)

        if init is not None:
            body = Ast.Block([init, body])

        return body

    def if_statement(self):
        """
        if_statement => "if" "(" expression ")" statement ("else" statement)?
        """
        self.consume(TokenType.LEFT_PAREN, "Expected (")
        cond = self.expression()
        self.consume(TokenType.RIGHT_PAREN, "Expected )")
        then_branch = self.statement()

        else_branch = None
        if self.match(TokenType.ELSE):
            else_branch = self.statement()

        return Ast.If(cond, then_branch, else_branch)

    def print_statement(self):
        expr = self.expression()
        self.consume(TokenType.SEMI_COLON, "expected semicolon")
        return Ast.Print(expr)

    def expression_statement(self):
        expr = self.expression()
        self.consume(TokenType.SEMI_COLON, "expected semicolon")
        return Ast.Expression(expr)

    def block(self) -> Ast.Block:
        """
        block = "{" (declaration)* "}"
        """

        declarations = []
        while not (self.check(TokenType.RIGHT_BRACE) or self.is_end()):
            declaration = self.declaration()
            declarations.append(declaration)

        self.consume(TokenType.RIGHT_BRACE, "expected }.")

        return Ast.Block(declarations)

    def expression(self) -> Ast.Expr:
        """
        expression -> assignment
        """
        return self.assignment()

    def assignment(self) -> Ast.Assign:
        """
        assignment -> IDENTIFIER "=" assignment
                     | logic_or
        """
        expr = self.logic_or()

        if self.match(TokenType.EQUAL):
            token = self.previous()
            value = self.assignment()

            if isinstance(expr, Ast.Variable):
                return Ast.Assign(expr.name, value)

            self.error(token, "Invalid assignement target")
        return expr

    def logic_or(self):
        """
        logic_or -> logic_and ("or" logic_and)*
        """
        left = self.logic_and()

        right = None
        while self.match(TokenType.OR):
            op = self.previous()
            right = self.logic_and()
            left = Ast.Logical(left, op, right)

        return left

    def logic_and(self):
        """
        logic_and -> equality ("or" equality)*
        """
        left = self.equality()

        while self.match(TokenType.AND):
            op = self.previous()
            right = self.equality()
            left = Ast.Logical(left, op, right)

        return left

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
        unary -> ("!" | "-") unary | call"
        """
        if self.match(TokenType.MINUS, TokenType.NOT):
            op = self.previous()
            right = self.unary()
            expr = Ast.Unary(op, right)
            return expr

        return self.call()

    def call(self) -> Ast.Expr:
        """
        call -> primary ("(" arguments? ")")*
        """
        expr = self.primary()

        while self.match(TokenType.LEFT_PAREN):
            args = self.arguments()
            token = self.consume(TokenType.RIGHT_PAREN, "expected ).")
            expr = Ast.Call(expr, token, args)

        return expr

    def arguments(self) -> list:
        """
        arguments -> expression (", " expression)*
        """
        args = []
        while not self.check(TokenType.RIGHT_PAREN):
            args.append(self.expression())
            while self.match(TokenType.COMMA):
                args.append(self.expression())

        if len(args) > 255:
            self.error(self.peek(), "cannot have more than 255 arguments")

        return args

    def primary(self) -> Ast.Expr:
        """
        primary -> NUMBER | STRING | "false" | "true" | "nil"
                   | "(" expression ")" | IDENTIFIER
        """
        if self.match(TokenType.FALSE):
            return Ast.Literal(False)

        if self.match(TokenType.TRUE):
            return Ast.Literal(True)

        if self.match(TokenType.NIL):
            return Ast.Literal(None)

        if self.match(TokenType.STRING, TokenType.NUMBER):
            return Ast.Literal(self.previous().literal)

        if self.match(TokenType.IDENTIFIER):
            return Ast.Variable(self.previous())

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
