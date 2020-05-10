#!/usr/bin/env python3
from abc import ABC, abstractmethod
from .environment import Environment


class LoxCallable(ABC):
    @abstractmethod
    def call(self, interpreter, args):
        pass

    @abstractmethod
    def arity(self) -> int:
        pass


class LoxFunction(LoxCallable):
    def __init__(self, func):
        self.func = func

    def arity(self) -> int:
        return len(self.func.params)

    def call(self, interpreter, args):
        env = Environment(interpreter.globs)
        for param, value in zip(self.func.params, args):
            env.define(param.lexeme, value)

        interpreter.execute_block(self.func.body.statements, env)

    def __str__(self):
        return f"<fn {self.func.name.lexeme}>";
