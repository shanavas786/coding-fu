# Chapter 2

- Type of value determines the set of values it can have and what operations can be performed on it.

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
