#!/usr/bin/env python3

def max_product(l):
    prod = 1
    neg_prod = 1
    no_neg = 0
    max_neg = None

    for num in l:
        if num == 0 or num == 1:
            continue
        if num < 0:
            no_neg += 1
            if max_neg is None or max_neg < num:
                max_neg = num
            neg_prod *= num

    if no_neg % 2:
        neg_prod /= num

    return str(prod * neg_prod)
