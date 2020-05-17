from .callables import LoxCallable, LoxFunction
from .environment import Environment
from .error_logger import ErrorLogger, Return, RuntimeException
from .lib import clock
from .token_types import TokenType

OPERATOR_MAP = {
    TokenType.LESSER: "__lt__",
    TokenType.LESSER_EQUAL: "__le__",
    TokenType.GREATER: "__gt__",
    TokenType.GREATER_EQUAL: "__ge__",
    TokenType.STAR: "__mul__",
    TokenType.SLASH: "__div__",
    TokenType.MINUS: "__sub__",
    TokenType.EQUAL_EQUAL: "__eq__",
}


class Interpreter:
    def __init__(self):
        self.globs = Environment()
        self.env = self.globs
        self.locs = {}

        self.globs.define("clock", clock)

    def interpret(self, statements):
        try:
            for stmt in statements:
                self.execute(stmt)
        except RuntimeException as ex:
            ErrorLogger.runtime_error(ex)

    def evaluate(self, expr):
        """
        Evaluate an expression
        """
        return expr.accept(self)

    def execute(self, stmt):
        """
        Execute a statement
        """
        stmt.accept(self)

    def lookupVariable(self, name, expr):
        depth = self.locs.get(expr)
        if depth is None:
            return self.globs.get(name)
        return self.env.getAt(depth, name.lexeme)

    def resolve(self, expr, depth):
        self.locs[expr] = depth

    def execute_block(self, statements, env):
        prev_env = self.env
        self.env = env
        try:
            for stmt in statements:
                self.execute(stmt)
        finally:
            self.env = prev_env

    def isTruthy(self, expr):
        """
        In Lox, None is Falsy
        rest all are Truthy
        """
        if expr is None:
            return False
        if isinstance(expr, bool):
            return expr
        return True

    def checkNumberOperands(self, token, *values):
        for value in values:
            if isinstance(value, (int, float)):
                continue
            raise RuntimeException(token, " operand/s must be number/s")

    def visitLiteralExpr(self, expr):
        return expr.value

    def visitGroupingExpr(self, expr):
        return self.evaluate(expr.exp)

    def visitUnaryExpr(self, expr):
        val = self.evaluate(expr.exp)

        if expr.op.token_type == TokenType.MINUS:
            return -val
        if expr.op.token_type == TokenType.NOT:
            return not val

    def visitBinaryExpr(self, expr):
        left = self.evaluate(expr.left)
        right = self.evaluate(expr.right)

        tk_type = expr.op.token_type

        if tk_type == TokenType.PLUS:
            if isinstance(left, (int, float)) and isinstance(right, (int, float)):
                return left + right
            if isinstance(left, str) and isinstance(right, str):
                return left + right

            raise RuntimeException(expr.op, "operands must be numbers or strings")

        self.checkNumberOperands(expr.op, left, right)
        op_name = OPERATOR_MAP[tk_type]
        fn = getattr(left, op_name)
        return fn(right)

    def visitExpressionStmt(self, stmt):
        self.evaluate(stmt.exp)

    def visitPrintStmt(self, stmt):
        val = self.evaluate(stmt.exp)
        print(val)

    def visitVarStmt(self, stmt):
        val = None
        if stmt.value is not None:
            val = self.evaluate(stmt.value)
        name = stmt.name.lexeme
        self.env.define(name, val)

    def visitVariableExpr(self, expr):
        return self.lookupVariable(expr.name, expr)

    def visitAssignExpr(self, expr):
        name = expr.name
        val = self.evaluate(expr.value)
        depth = self.locs.get(name)

        if depth is None:
            self.globs.assign(name, val)
        else:
            self.env.assignAt(depth, name, val)

        return val

    def visitLogicalExpr(self, expr):
        left = self.evaluate(expr.left)

        if expr.op.token_type == TokenType.OR:
            if self.isTruthy(left):
                return left
            else:
                return self.evaluate(expr.right)

        if expr.op.token_type == TokenType.AND:
            if self.isTruthy(left):
                return self.evaluate(expr.right)
            else:
                return left

    def visitCallExpr(self, expr):
        callee = self.evaluate(expr.callee)
        args = list(map(self.evaluate, expr.args))

        if not isinstance(callee, LoxCallable):
            raise RuntimeException(expr.paren, "can only call functions and classes")

        expected = callee.arity()
        given = len(args)
        if given != expected:
            raise RuntimeException(
                expr.paren, f"expected {expected} args but got {given}."
            )

        return callee.call(self, args)

    def visitBlockStmt(self, stmt):
        self.execute_block(stmt.statements, Environment(self.env))

    def visitIfStmt(self, stmt):
        if self.isTruthy(self.evaluate(stmt.cond)):
            self.execute(stmt.then_branch)
        elif stmt.else_branch is not None:
            self.execute(stmt.else_branch)

    def visitWhileStmt(self, stmt):
        while self.isTruthy(self.evaluate(stmt.cond)):
            self.execute(stmt.body)

    def visitFunctionStmt(self, stmt):
        func = LoxFunction(stmt, self.env)
        self.env.define(stmt.name.lexeme, func)

    def visitReturnStmt(self, ret):
        val = None
        if ret.exp is not None:
            val = self.evaluate(ret.exp)

        raise Return(val)
