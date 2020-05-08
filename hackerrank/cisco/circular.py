#!/usr/bin/env python3


def circularArray1(n, endNodes):
    counter = [0] * n + 1
    paths = len(endNodes) - 1
    for idx in range(paths):
        start_node = endNodes[idx]
        end_node = endNodes[idx + 1]
        if end_node > start_node:
            for i in range(start_node - 1, end_node):
                counter[i] += 1
        else:
            for i in range(start_node - 1, n):
                counter[i] += 1
            for i in range(end_node):
                counter[i] += 1

        print(counter)

    max_visit_node = 0
    max_visit = 0
    for idx in range(n):
        if counter[idx] > max_visit:
            max_visit = counter[idx]
            max_visit_node = idx
    return max_visit_node + 1




def circularArray(n, endNodes):
    counter = [0] * (n + 1)
    paths = len(endNodes) - 1
    for idx in range(paths):
        start_node = endNodes[idx]
        end_node = endNodes[idx + 1]

        if end_node > start_node:
            counter[start_node - 1] += 1
            counter[end_node] -= 1
        else:
            counter[start_node - 1] += 1
            counter[n] -= 1

            counter[0] += 1
            counter[end_node] -= 1

    max_visit_node = 0
    max_visit = 0
    cumulative = 0
    for idx in range(n):
        cumulative += counter[idx]
        if cumulative > max_visit:
            max_visit = cumulative
            max_visit_node = idx
    return max_visit_node + 1


print(circularArray(10, [8, 2, 7, 9, 10]))
