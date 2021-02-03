# Top to down, left to right - James Powell
# https://www.youtube.com/watch?v=DlgbPLvBs30


# 1. module imports

# module.py
class A:
    pass

class B:
    pass

# script.py

from module import A

a = A()

isinstance(a, A) # True

import module

b = module.B()

isinstance(b, module.B) # True


from importlib import reload
import module; module = reload(module)

isinstance(a, A) # True - A is already captured
isinstance(b, module.B) # False - compares with reloaded B

from module import A, B

isinstance(a, A) # False - imports reloaded A
isinstance(b, B) # False - imports reloaded A

# mutable default arg

def f(x=[]):    # executed only once
    x.append(len(x))
    return x

f() # [0]
f() # [0, 1]
f() # [0, 1, 2]


def f(*args, **kwargs):
    def g(x=[]):        # executed everytime outer function is called
        x.append(len(x))
        return x
    return g(*args, **kwargs)

f() # [0]
f() # [0]
f() # [0]


def d(f):
    def _(*args, **kwargs):
        return f(*args, **kwargs)
    return _

@d
def f(x=[]):    # executed only once
    x.append(len(x))
    return x

f() # [0]
f() # [0, 1]
f() # [0, 1, 2]


class A():
    @staticmethod
    def f(x=[]):    # executed only once
        x.append(len(x))
        return x

A.f() # [0]
A.f() # [0, 1]
A.f() # [0, 1, 2]

# local and global scope

old = locals()
x = 10
set(locals()) - set(old) # {}

old = locals().copy()
x = 10
set(locals()) - set(old) # {'old', 'x'}


def f():
    locals()['x'] = 10  # x is not available in code.co_varnames,
                        # so statically assumes it as global variable
    return x

f() # NameError: name x is not defined

def f(x=10):
    locals()['x'] = 100
    return x

f() # 10


def f():
    globals()['x'] = 10 # x is not available in code.co_varnames,
                        # so statically assumes it as global variable
    return x

f() # 10


def f(x=10):
    locals()['x'] = 1
    globals()['x'] = 100
    return x    # statically identifies that it is a closure variable

f() # 10


def f(x=10):
    def g():
        x += 1
        return x
    return g()

f() # UnboundLocalError: x referenced before assignment
nonlocal x # tells python x is a closure/deref variable
global x # tells python x is a global variable

# python execution model
    # LOAD_GLOBAL
    # LOAD_FAST     # loads from code.co_varnames
    # LOAD_DEREF
    # LOAD_COST     # loads from consts


from module import A # A = module.A - binds A
# capatures the Object A early so no subsequent changes in the moule will be reflected

import math    # doesn't execute code
               # math = sys.modules['math']

from sys import path
path.append("/tmp") # works
path.insert(0, "/tmp") # works

from sys import path
path = ["/tmp"] + path  # doesn't work

import sys
sys.path = ["/tmp"] + sys.path  # works
