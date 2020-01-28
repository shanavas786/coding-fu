- default values are evaluated only once. Mutable objects should not be used as default value for arguments
- def f(pos1, pos2, /, posorkwd, \*, kwd1, kwd2):
- call by object reference, call by name
- single element tuple
- sequence packing and unpacking
- dictionary key - immutable
- list(dictionary) -> list of keys
- import \* imports all names except those beginning with an underscore
- __all__
- fstring
- magic methods: __str__, __repr__

- def bool\_return():
  ...     try:
  ...         return True
  ...     finally:
  ...         return False
  ...
  >>> bool\_return()
  False

- execution order
  try
  else
  finally
  [rethrow]


  try
  except
  finally
  [re throw]



- If an exception occurs during execution of the try clause, the exception may be handled by an except clause.
  If the exception is not handled by an except clause, the exception is re-raised after the finally clause has been executed.
- An exception could occur during execution of an except or else clause. Again, the exception is re-raised after the finally clause has been executed.

- If the try statement reaches a break, continue or return statement, the finally clause will execute just prior to the break, continue or return statement’s execution.
- If a finally clause includes a return statement, the finally clause’s return statement will execute before, and instead of, the return statement in a try clause.


- context manager
  __init__
  __enter__
  __exit__

- how to modify a class after it is created
  - add a method ?
- is python class is an object ?
  - type(Class) ?
- namespace is a mapping of names to objects - implemented as python dicts in Cpython
- attribute - anything that follows a dot
- module attributes are writable
- global, local, nonlocal
- class definitions can be enclosed in if/function blocks
- iterator protocol, __iter__, __next__, StopIteration
- generator, yield
- >>> c = []; d = []
  >>> c is d
  False
  >>> c = d = []
  >>> c is d
  True

- Exception chaining can be explicitly suppressed by specifying None in the from clause:
```python
  try:
     print(1 / 0)
  except:
     raise RuntimeError("Something bad happened") from None
```
- the Boolean operations or and and always return one of their operands.
- and and or are shortcircuit operators
- a == not b is syntax error
- <<, >> Negative shift counts are illegal and cause a ValueError to be raised.
