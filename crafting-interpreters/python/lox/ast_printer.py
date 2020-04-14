#!/usr/bin/env python3


class AstPrinter:
    def print(self, expr):
        return expr.accept(self)

    def parenthesize(self, name, *exprs):
        strg = "(" + name

        for expr in exprs:
            strg += " " + expr.accept(self)

        strg += ")"
        return strg

    def visitBinaryExpr(self, expr):
        return self.parenthesize(expr.op.lexeme, expr.left, expr.right)

    def visitGroupingExpr(self, expr):
        return self.parenthesize("group", expr.exp)

    def visitLiteralExpr(self, expr):
        if expr.value is None:
            return "nil"
        return str(expr.value)

    def visitUnaryExpr(self, expr):
        return self.parenthesize(expr.op.lexeme, expr.exp)
