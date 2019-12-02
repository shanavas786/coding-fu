# Pointers and Arrays
  - pointer is a group of cells (because short and int are) that can hold an address
# 5.1. Pointers and Addresses
    - address operator '&' can't be applied to expressions, constants or
      register variables
    - `int *p` means `*p` is an int
    - `(*p)++` parentheses are necessary as unary operators `*` and `++`
      associate right to left
    - if `ip` points to `x` `*ip` can occur wherever `x` could

# 5.2. Pointers and Function Arguments

# 5.3. Pointers and Arrays
  - p = &a[0] is a synonym of p = a
  - a[i] === *(a+i)
  - pointer is variable so, p=a, p++ are legal
  - array name is not a variable so, a=p, a++ are illegal
  - when a function is called with an array name, location of first element is passed

# 5.4 Address Arithmetic
