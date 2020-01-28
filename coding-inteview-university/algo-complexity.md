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

# Amortized analysis
  - average worst case complexity
  - occasional operation is slow
  - eg: Hastable insertion

# Recurrence Relation
  - relation in which value of at a point depends on the value at a previous point

# Master theorem
  The master theorem is a recipe that gives asymptotic estimates for a class of recurrence relations that often show up when analyzing recursive algorithms.

  Let a >= 1 and b > 1 be constants, let f(n) be a function, and let T(n) be a function over the positive numbers defined by the recurrence

  T(n) = aT(n/b) + f(n).
  If f(n) = O(n^{d}), where d >= 0, then

  T(n) = O(n^{d}) if a < b^d,
  T(n) = O(n^d log n) if a = b^d,
  T(n) = O(n^{logba}) if a > b^d.

# complexities
  - Fibonacci
    T(n) = T(n-1) + T(n-2)
    assume T(n-1) === T(n-2)
    T(n) = 2T(n-2)
    T(n) = 2^k T(n-2K)
    T(n) proportional to 2^{n/2}
    Lower bound

    lly, assuming T(n-2) === T(n-1)
    T(n) = 2T(n-1)
    T(n) = 2^k T(n-k)
    T(n) proportional to 2^n

  - GCD Euclid's algo
    division of two numbers is proportional to number of digits in that number
    which is log10(n)
