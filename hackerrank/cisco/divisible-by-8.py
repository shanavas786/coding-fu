#!/usr/bin/env python3

from itertools import permutations

def checkDivisibility(arr):
    result = ["NO" for _ in range(len(arr))]

    for idx, item in enumerate(arr):
        intlist = list(map(int, item))

        l = len(intlist)
        if l > 3:
            l = 3
        for perm in permutations(intlist, l):
            num = perm[0]
            try:
                num = num * 10 + perm[1]
                num = num * 10 + perm[2]
            except Exception:
                pass
            if num % 8 == 0:
                result[idx] = "YES"
                break

    return result





print(checkDivisibility(["61", "75"]))
print(checkDivisibility(["1000", "125"]))
