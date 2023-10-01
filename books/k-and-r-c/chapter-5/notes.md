# Pointers and Arrays
  - pointer is a group of cells (because short and int are) that can hold an address
# 5.1. Pointers and Addresses
  - address operator '&' can't be applied to expressions, constants or
    register variables
  - `int *p` means `*p` is an int
  - `(*p)++` parentheses are necessary as unary operators `*` and `++`
    associate right to left
  - if `ip` points to `x` `*ip` can occur wherever `x` could
  - every pointer points to a specific data type except pointer to void
    It can hold any type of pointer.

# 5.2. Pointers and Function Arguments
  - C passes arguments to functions by value

# 5.3. Pointers and Arrays
  - p = &a[0] is a synonym of p = a
  - a[i] === *(a+i)
  - pointer is variable so, p=a, p++ are legal
  - By definition the value of a variable or expression of type array
    is the address of the first element of the array. That's why array name
    can't be assigned a value.
  - array name is not a variable so, a=p, a++ are illegal
    https://www.geeksforgeeks.org/lvalue-and-rvalue-in-c-language/
  - when a function is called with an array name, location of first element is passed

# 5.4 Address Arithmetic
  - pointers to the same array can be compared
  - behavior is undefined for arithmetic or comparison with pointers to a
    different array
  - if p and q points to the same array, q-p+1 is the number of elements
    between them inclusive;

  - The valid pointer operations are
    - assignment of pointers of same type
    - adding, subtracting integers
    - subtracting or comparing two pointers to same array
  - Adding/multiplying pointers are invalid

# 5.5 Character pointers and functions
  - difference btw
    char amessage[] = "hello world";
    char *pmessage = "hello world";
    is that amessage is an array. individual characters can be changed but
    amessage will always point to the first element.
    pmessage can be modified to point anywhere, but the result will be undefined
    if string contents are modified;

# 5.9 Pointers vs Multi-dimensional array
  - difference btw
    int a[10][20]
    int* b[10]

    a allocate 10x20 bytes of storage.
    b allocates only 10.

    Adavantage of pointers is that the rows can be of different lengths.

# 5.10 Command line arguments
  - argv[argc] is null

# 5.11 Pointers to functions
  - int (\*comp) (void \*, void\*)
    \*comp is a function that accepts two pointer arguments and returns an int
