# Chapter 2

- Type of value determines the set of values it can have and what operations can be performed on it.

## section 2.2
 - size of int => usually a word
 - shorts and ints are atleast 16 bits
 - longs are atleast 32 bits
 - short is no longer than int which is no longer than long
 - size of floating point objects are implementation dependant.
 - float, double, long double could 1, 2 or 3 distinct sizes

## section 2.3
- String constants can be concatenated at compile time
  "hello" "world" => "hello world"
- If the variable is not automatic, it will be initialized once only, before the program
  starts executing and the initializer must be a constant expression
- External and static variables are initialized to zero by default
- Uninitialized atomatic variable has garbage (undefined) value


## section 2.5
- % can't be applied to float of double

## section 2.7
- The language doesn't specify if char is signed or unsinged
  When a char is converted to int, can it produce -ve integer ?
  It is machine dependent
- for portability specify signed or unsigned if non character data is to be stored in char
- Conversion takes place across assignments. RHS is converted to the type of LHS
- Longer integers are converted to shorter ones or chars by dropping the higher order bits

## section 2.9
- right shifting signd values will fill vacated bits with sign bit (arithmatic shift) on some
  machines and 0 (logical shift) on other

- A statement is a complete line of code that performs some action (doesn't
  evaluates to a value), while an expression is any section of the code that
  evaluates to a value. Expressions can be combined “horizontally” into larger
  expressions using operators, while statements can only be combined
  “vertically” by writing one after another, or with block constructs. Every
  expression can be used as a statement (whose effect is to evaluate the
  expression and ignore the resulting value)

## section 2.10
- C doesn't specify the order in which operants of an operator are evaluated
  (except for &&, ||, ?: and ,)
  for eg: x = f() + g() either of f or g could be evaluated first
  similarly, the order in which function arguments are evaluated is not specified
  printf("%d, %d", ++n, ++n) could produce different outputs with different compilers.
  a[i] = i++; - behaviour is compiler dependent
