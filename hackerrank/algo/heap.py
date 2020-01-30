#!/usr/bin/env python3

# Enter your code here. Read input from STDIN. Print output to STDOUT

class Heap():
    def __init__(self):
        self.heap = []

    def push(self, val):
        self.heap.append(val)
        self.bubble_up(len(self.heap))

    def pop(self):
        small = self.heap[0]
        last = self.heap.pop()
        self.heap[0] = last
        self.bubble_down(0)
        return small

    def peek(self):
        return self.heap[0]

    def delete(self, val):
        idx = self.heap.index(val)
        last = self.heap.pop()
        if idx < len(self.heap):
            self.heap[idx] = last
            self.bubble_down(idx + 1)

    def bubble_up(self, index):
        # root
        while index > 1:
            val = self.heap[index - 1]
            par_idx = index // 2
            if self.heap[par_idx - 1] > val:
                self.heap[index - 1] = self.heap[par_idx - 1]
                self.heap[par_idx - 1] = val
                index = par_idx
            else:
                break

    def bubble_down(self, index):
        max_non_leaf = len(self.heap) // 2
        l = len(self.heap)

        while index <= max_non_leaf:
            val = self.heap[index - 1]
            left = index * 2
            right = index * 2 + 1
            swap_with = None

            if right > l:
                # no right child
                if self.heap[left - 1] < val:
                    swap_with = left
            else:
                left_val = self.heap[left - 1]
                right_val = self.heap[right - 1]

                if left_val < val:
                    if left_val < right_val:
                        swap_with = left
                    elif right_val < val:
                        swap_with = right
                elif right_val < val:
                    swap_with = right

            if swap_with is not None:
                self.heap[index - 1] = self.heap[swap_with - 1]
                self.heap[swap_with - 1] = val
                index = swap_with
            else:
                break




if __name__ == "__main__":
    q = int(input())

    heap = Heap()

    for _ in range(q):
        line = list(map(int, input().split()))
        op = line[0]
        val = line[-1]

        if op == 1:
            heap.push(val)
        elif op == 2:
            heap.delete(val)
        elif op == 3:
            print(heap.peek())
