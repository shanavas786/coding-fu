#!/usr/bin/env python3

from enum import Enum, auto

from .error_logger import ErrorLogger

class FunctionType(Enum):
    NONE = auto()
    FUNCTION = auto()

class Stack(list):
    def push(self, item):
        self.append(item)

    def peek(self):
        return self[-1]


class Resolver:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self.scopes = Stack()
        self.current_function = FunctionType.FUNCTION

    def define(self, name):
        if self.scopes:
            self.scopes.peek()[name.lexeme] = True

    def declare(self, name):
        if self.scopes:
            scope = self.scopes.peek()
            if name in scope:
                ErrorLogger.error(token=name.lexeme,
                                  message="Variable with this name already declared in this scope.")
            self.scopes.peek()[name.lexeme] = False

    def resolve(self, items):
        """
        Resolves Exprt, Stmt, list[Stmt]
        """
        if isinstance(items, list):
            for item in items:
                self.resolve(item)
        else:
            items.accept(self)

    def resolveFunction(self, stmt, fun_type):
        old_fun_type = self.current_function
        self.current_function = fun_type

        self.beginScope()
        for param in stmt.params:
            self.declare(param)
            self.define(param)

        self.resolve(stmt.body)

        self.endScope()
        self.current_function = old_fun_type

    def beginScope(self):
        """
        Add new scope to the stack
        """
        self.scopes.push({})

    def endScope(self):
        """
        """
        self.scopes.pop()

    def resolveLocal(self, expr, name):
        n = len(self.scopes)
        for i in range(n, 0, -1):
            if name.lexeme in self.scopes[i - 1]:
                self.interpreter.resolve(expr, n - i)
                break

    def visitBlockStmt(self, block):
        self.beginScope()
        self.resolve(block.statements)
        self.endScope()

    def visitVarStmt(self, stmt):
        self.declare(stmt.name)

        if stmt.value is not None:
            self.resolve(stmt.value)

        self.define(stmt.name)

    def visitFunctionStmt(self, stmt):
        self.declare(stmt.name)
        self.define(stmt.name)

        self.resolveFunction(stmt, FunctionType.FUNCTION)

    def visitExpressionStmt(self, stmt):
        self.resolve(stmt.exp)

    def visitIfStmt(self, stmt):
        self.resolve(stmt.cond)
        self.resolve(stmt.then_branch)
        if stmt.else_branch:
            self.resolve(stmt.else_branch)

    def visitReturnStmt(self, stmt):
        if self.current_function == FunctionType.NONE:
            ErrorLogger.error(token=stmt.keyword, message="Cannot return from top-level code.")

        if stmt.exp is not None:
            self.resolve(stmt.exp)

    def visitWhileStmt(self, stmt):
        self.resolve(stmt.cond)
        self.resolve(stmt.body)

    def visitPrintStmt(self, expr):
        self.resolve(expr.exp)

    def visitVariableExpr(self, expr):
        if self.scopes and self.scopes.peek().get(expr.name.lexeme) is False:
            ErrorLogger.error(token=expr.name, message="Cannot read local variable in its own initializer.")

        self.resolveLocal(expr, expr.name)

    def visitBinaryExpr(self, stmt):
        self.resolve(stmt.left)
        self.resolve(stmt.right)

    def visitCallExpr(self, expr):
        self.resolve(expr.callee)
        for arg in expr.args:
            self.resolve(arg)

    def visitGroupingExpr(self, expr):
        self.resolve(expr.exp)

    def visitLiteralExpr(self, expr):
        pass

    def visitLogicalExpr(self, expr):
        self.resolve(stmt.left)
        self.resolve(stmt.right)

    def visitAssignExpr(self, expr):
        self.resolve(expr.value)
        self.resolveLocal(expr, expr.name)

    def visitUnaryExpr(self, expr):
        self.resolve(expr.exp)
