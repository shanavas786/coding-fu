#!/usr/bin/env python3
from .error_logger import RuntimeException


class Environment:
    def __init__(self, enclosing=None):
        self.enclosing = enclosing
        self.values = {}

    def define(self, name, val):
        self.values[name] = val

    def get(self, name):
        if name.lexeme in self.values:
            return self.values[name.lexeme]

        if self.enclosing:
            return self.enclosing.get(name)

        raise RuntimeException(name, f"Undefined variable {name.lexeme}.")

    def assign(self, name, val):
        if name.lexeme in self.values:
            self.values[name.lexeme] = val
            return

        if self.enclosing:
            return self.enclosing.assign(name, val)

        raise RuntimeException(name, f"Undefined variable {name.lexeme}.")

    def getAt(self, depth, name):
        return self.nthAncestor(depth).values.get(name)

    def assignAt(self, depth, name, value):
        self.nthAncestor(depth).values[name] = value

    def nthAncestor(self, n):
        env = self
        while n:
            env = env.enclosing
            n = n - 1
        return env
