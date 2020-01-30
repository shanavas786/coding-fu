#!/usr/bin/env python3
# Given the root node of a binary tree, can you determine if it's also a binary search tree?

def check_binary_search_tree_(root):
    nodes = []
    current = root
    current_val = None

    while True:
        if current:
            nodes.append(current)
            current = current.left
        elif nodes:
            current = nodes.pop()
            if current_val is None:
                current_val = current.data
            elif current_val >= current.data:
                return False
            current_val = current.data
            current = current.right
        else:
            break
    return True


class node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


def test():
    n1 = node(1)
    n2 = node(2)
    n3 = node(3)
    n4 = node(4)
    n5 = node(5)
    n6 = node(6)
    n7 = node(7)

    n3.left = n2
    n3.right = n6

    n2.left = n1
    n2.right = n4

    n6.left = n5
    n6.left = n7


    print(check_binary_search_tree_(n3))

def test1():
    n1 = node(1)
    n2 = node(2)
    n3 = node(3)
    n4 = node(4)
    n5 = node(5)
    n6 = node(6)
    n7 = node(7)

    n4.left = n2
    n4.right = n6

    n2.left = n1
    n2.right = n3

    n6.left = n5
    n6.left = n7


    print(check_binary_search_tree_(n3))
