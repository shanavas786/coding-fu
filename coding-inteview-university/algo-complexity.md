# Algorithmic complexity
    - 2 steps
      - computer independant computation model
      - analyse the runtime

    - RAM model of computations
      Random Access Machine
      architechture independent simple conceptual model of computer
      - each machine instructions takes one step
      - each memory access takes one step
        not true for real computer (HD is slow, different levels of cache ..etc)

## Big O
    A function f(n) is O(g(n)) if there exist a constant C and a positive number
    n0 such that f(n) <= C(g(n)) for all n > n0

    - upper bound
    - worst case

## Omega
    A function f(n) is Omega(g(n)) if there exist a constant C and a positive number
    n0 such that f(n) >= C(g(n)) for all n > n0

    - lower bound
    - best case

## Theta
    A function f(n) is Theta(g(n)) if f(n) is O(g()) and f(n) is Omega(g(n))

    - average case

# Operations
    - O(f(n)) * O(g(n)) => O(f(n) * g(n))
    - Omega(f(n)) * Omega(g(n)) => Omega(f(n) * g(n))
    - Theta(f(n)) * Theta(g(n)) => Theta(f(n) * g(n))
