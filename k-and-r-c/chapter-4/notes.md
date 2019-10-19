# Functions and program structure

## 4.1 Basics of functions
 - if return type is missing int is assumed

## 4.2 Functions returning non integers

 - if a function declaration doesn't include arguments, nothing is assumed about
   its arguments and agurment checking is turned off

## 4.3 External Variables

    - external variables: variables defined outside any function
    - functions are always external as c doesn't allow to define functions
      inside a function

## 4.4 Scope Rules
## 4.5 Header Files
## 4.6 Static variables
    - static declaration when applied to an external variable or function,
      limits its scope to rest of the file being compiled
    - static variables thus won't conflict with the same names in other files.
    - if a function is decleared static, it won't be visible to outside the file
      in which it is decleared
    - static variable is initialized only the first time the block is entered.

## 4.7 Register Variables
    - register declaration advises compiler that the variable will be heavily
      used. The idea is that register variables are to be placed in machine
      registers. But compilers are free to ignore the advice.
    - register declaration can only be applied to automatic variables and
      function arguments
    - only a few variables and certain types in each function may be kept in
      registers. The number and types are machine dependant.
    - It is not possible to take the address of a register variable, regardless
      of whether it is placed is register. compilation fails
    - external variables can't be declared register variables.

## 4.8 Block Structure
    - automatic variables including formal parameters also hide external
      variables and functions of the same name.
    - external variable and function can't have same names in same scope

## 4.9 Initialization
    - In the absence of explicit initialization, external and static variables
      are intialized to zero.
    - Unintialized automatic and register values have undefined (garbage) values.
    - for external and static variables, initializer must be a constant expression.
    - if there are fewer elements for an array than the specified number, the
      missing elements will be zero for external/static variables.
    - compiler warns if there are too many initializers

## 4.10 Recursion
## 4.11 The C preprocessor
### 4.11.1 File inclusion
    - if filename is quoted, the search begins where the source program was found.
    - when an included file is changed, all files that depend on it must be recompiled

### 4.11.2 Macro substitution
    - names may be undefined with `#undef name`
    - if a parameter name is preceeded by a `#` in th replacement text, the
      combination will be expanded into quoted string
      #define dprint(expr) print(#expr " = %g \n", expr)
      dprint(x/y) will be expanded to printf("x/y" " = %g \n", x/y)
    - preprocessor operator `##` provides a way to concatenate actual arguments
      during macro expansion
      #define paste(front, back) front ## back
      paste(name, 1) is expanded to name1

### 4.11.3 Conditional inclusion
    - #if defined(name) => #ifdef
    - #if !defined(name) => #ifndef
    - #endif
    - #elif
    - #else
