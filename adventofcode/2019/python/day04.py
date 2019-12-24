#!/usr/bin/env python3


def is_adjascent(digits):
    """
    Check if the number has two adjacent digits
    """
    prev = None
    for digit in digits:
        if prev == digit:
            return True
        prev = digit

    return False


def is_adjascent_2(digits):
    """
    Check if the number has two adjacent digits that it not part
    of a larger matching group
    """
    prev = None
    matches = 0
    for digit in digits:
        if prev == digit:
            matches += 1
        elif matches == 1:
            return True
        else:
            matches = 0
        prev = digit
    return matches == 1


def get_next_pass(digits):
    n = 5
    digits[n] += 1
    while digits[n] == 10:
        digits[n] = 0
        digits[n - 1] += 1
        n -= 1

    n = 0
    while n < 5:
        if digits[n + 1] < digits[n]:
            digits[n + 1] = digits[n]
        n += 1
    return digits


def get_num(digits):
    num = 0
    for digit in digits:
        num = num * 10 + digit
    return num


def get_password_count(frm, to, is_adjascent):
    """
    Get count of numbers that satisfies the conditions
    1. It is a six-digit number.
    2. The value is within the range given in your puzzle input.
    3. a) Two adjacent digits are the same (like 22 in 122345) - Part 1
       b) Two adjacent matching digits are not part of a larger group of matching digits- Part 2
    4. Going from left to right, the digits never decrease;
    they only ever increase or stay the same (like 111123 or 135679).
    5. between frm and to
    """

    num = frm

    # make number compatible with #1
    if num < 100000:
        num = 100000

    digits = []
    while num > 0:
        digit = num % 10
        digits.append(digit)
        num //= 10
    digits.reverse()

    count = 0

    while get_num(digits) < to:
        if is_adjascent(digits):
            count += 1
        digits = get_next_pass(digits)

    return count


assert get_password_count(134792, 675810, is_adjascent) == 1955
assert get_password_count(134792, 675810, is_adjascent_2) == 1319
