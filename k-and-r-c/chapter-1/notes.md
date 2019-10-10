# Chapter 1

## Section 1.3

1. Integer division truncates
2. If an arithmetic operator has integer operands, an integer operation is performed
3. If an arithmetic operator has one floating-point operand and one integer
   operand, integer will be converted to floating-point before the operation is
   done
4. output formatting
  - %d     print as decimal
  - %6d    print as decimal, atleast 6 characters wide
  - %f     print as floating-point
  - %6f    print as floating-point, atleast 6 chars wide
  - %.2f   print as floating-point, 3 chars after decimal point
  - %6.1f  print as floating-point, atleast 6 chars wide and 1 after decimal point
  - %.0f   print as floating-point, no decimal point and fractional part

## Section 1.5
1. Return type of `getchar` is `int` to accommodate `EOF`
2. Assignment is an expression and has value of left hand side after the assignment
3. Isolated semicolon -> null statement

### Section 1.10
1. automatic variables - created only when the function is called
2. local variables are by default automatic
3. external var must be defined exactly once and declared in each function that
   wants to access it
4. If the definition fo an external variable occurs in the source file before
   its use in a particular function, `extern` keyword can be omitted
5. Definition - where the variable is created / assigned storage
   Declaration - where nature of variable is stated.
