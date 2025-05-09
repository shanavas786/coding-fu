# The GNU C Programming Tutorial 4.1 Edition


## Ch 1: Intro

1. C is a flexible high level language

    A high level language with access to law level details


## Ch 2: Using a compiler

### Compilation stages
1. Reads source code and generates intermediatory code (pseudo-code)
2. Generates object code file for each source file - Machine language but not executable.
   These are temporary and will be deleted after after the compilation.
3. Linking. Merges object code with standard library object code to produce standalone executable

## Ch 3: The form of a C program

ANSI standard

## Ch 4: Functions

- Function declaration - declare the function signature/prototype.
- Function definition - function body

- Calling exit() terminate the program. It internally calls a few funtions that perform
  cleanups like closing open files.


## Ch 5: Variables and declarations

### 5.1: Integer variables

* char: Single byte
* short: two bytes
* int: 4 bytes
* long: 8 bytes
* long long: 8 bytes

### 5.2: Float variables

* float: 4 bytes
* double: 8 bytes
* long double: 16 bytes

### 5.4: The cast operator

* Casting always truncates / rounds down

### 5.5: Storage classes

* External variables
    `extern` keyword is used to use variables defined in another file.

* Static variables
    `static` variables maintain its value between function calls.
    global variables are defined as `static` automatically.

* Auto variables
    `auto` is the opposite of `static`.
    local variables are `auto` by default.

* register variables
    `register` keyword is used to store a variable in the computer register.
    modern compilers optimize the code even without the register keyword.


## Ch 6: Scopes

scope: where a variable is visible

* Global scope
  Outside all the funtions. Visible to all functions defined after the variable declaration.

* Local scope
  a. within a block of code - between two curly braces `{}` -
  b. visible in its own block and child blocks.
  c. invisible outside its block.

## Ch 7: Expressions and operators

* Assignment operator:
  something that can be assigned to is called `lvalue`.

* Unary operators:
  a. `++`, `--`, `+` ,`-` and `*` (dereferencing)
  b. precedence is from right to left

## Ch 8: Parameters

* Pass by value
* Pass by reference

* Actual parameters - values appear in function calls
* Formal parameters - variables as they appear in function decleration
* Variadic functions - function that can accept arbitrary number of actual parameters
