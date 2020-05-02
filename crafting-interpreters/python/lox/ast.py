#!/usr/bin/env python3
from .token_types import Token

expr = {
    "Expr": {
        "Assign": [("Token", "name"), ("Expr", "value")],
        "Binary": [("Expr", "left"), ("Token", "op"), ("Expr", "right")],
        "Grouping": [("Expr", "exp")],
        "Literal": [("object", "value")],
        "Unary": [("Token", "op"), ("Expr", "exp")],
        "Variable": [("Token", "name")],
    },
    "Stmt": {
        "Block": [("list", "statements")],
        "Expression": [("Expr", "exp")],
        "Print": [("Expr", "exp")],
        "Var": [("Token", "name"), ("Expr", "value")],
    }
}


class AstBuilder:
    def __init__(self):
        self.classes = {"Token": Token, "object": object, "list": list}  # hack

    def __getattr__(self, name):
        return self.classes[name]

    def register_class(self, name, klass):
        self.classes[name] = klass

    def build_init(self, fields):
        def init(me, *args):
            for info, value in zip(fields, args):
                klass_name, name = info
                klass = getattr(self, klass_name)
                assert isinstance(value, klass)
                setattr(me, name, value)

        return init

    def build_accept_func(self, name, base):
        def accept(me, visitor):
            fun = getattr(visitor, f"visit{name}{base}")
            return fun(me)

        return accept

    def create_class(self, name, base=None, fields=None):
        attrs = {}
        bases = ()
        if fields:
            attrs = {
                "__init__": self.build_init(fields),
                "accept": self.build_accept_func(name, base),
            }

        if base:
            bases = (getattr(self, base), )

        klass = type(name, bases, attrs)
        self.register_class(name, klass)

    def build_ast_classes(self, expr):
        for base, children in expr.items():
            self.create_class(base)
            for child, fields in children.items():
                self.create_class(child, base, fields)


Ast = AstBuilder()
Ast.build_ast_classes(expr)



# from plox.token_types import Token, TokenType
# from plox.ast import Ast
# from plox.ast_printer import AstPrinter
# m = Ast.Binary(Ast.Unary(Token(TokenType.MINUS, "-", None, 1), Ast.Literal(123)), Token(TokenType.STAR, "*", None, 1), Ast.Grouping(Ast.Literal(45.67)))
# v=AstPrinter()
# v.print(m)
