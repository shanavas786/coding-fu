#!/usr/bin/env python3

import time

from .callables import LoxCallable


class Clock(LoxCallable):
    def __init__(self):
        pass

    def call(self, interpreter, block):
        return time.time()

    def arity(self):
        return 0


clock = Clock()
