#!/usr/bin/env python3

cache = {}

def par_index(root, i):
    if i in cache:
        return cache[i]

    if i == root:
        return -1

    left = root // 2
    if (i == left) or i == (root - 1):
        return root

    if i < left:
        return par_index(left, i)
    else:
        return left + par_index(left, i - left)


def get_index(h, i):
    n = 2 ** h - 1
    l = [par_index(n, j) for j in i]
    print(l)



get_index(3, [3, 4, 7])
# print(par_index(7, 4))
