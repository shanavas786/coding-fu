#!/usr/bin/env python3
from abc import ABC, abstractmethod

from .environment import Environment
from .error_logger import Return


class LoxCallable(ABC):
    @abstractmethod
    def call(self, interpreter, args):
        pass

    @abstractmethod
    def arity(self) -> int:
        pass


class LoxFunction(LoxCallable):
    def __init__(self, func, closure):
        self.closure = closure
        self.func = func

    def arity(self) -> int:
        return len(self.func.params)

    def call(self, interpreter, args):
        env = Environment(self.closure)
        for param, value in zip(self.func.params, args):
            env.define(param.lexeme, value)

        try:
            interpreter.execute_block(self.func.body.statements, env)
        except Return as r:
            return r.value

    def __str__(self):
        return f"<fn {self.func.name.lexeme}>"
