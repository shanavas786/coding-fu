#!/usr/bin/env python3

def strokesRequired1(picture):
    rows = len(picture)
    cols = len(picture[0])

    colored = [[0 for _ in range(cols)] for i in range(rows)]
    strokes = 0

    for row in range(rows):
        for col in range(cols):
            cell = picture[row][col]

            if col != 0:
                left_cell = picture[row][col - 1]
                # found matching cell reuse that stroke
                if left_cell == cell:
                    left_color = colored[row][col - 1]
                    colored[row][col] = left_color
                    continue

            if row != 0:
                top_cell = picture[row - 1][col]
                # found matching cell reuse that stroke
                if top_cell == cell:
                    top_color = colored[row - 1][col]
                    colored[row][col] = top_color
                    continue

            # couldn't reuse color get new one
            strokes += 1
            colored[row][col] = strokes

    print(picture)
    print(colored)
    return strokes

def strokesRequired(picture):
    rows = len(picture)
    cols = len(picture[0])

    colored = [[0 for _ in range(cols)] for i in range(rows)]
    strokes = 0

    for row in range(rows):
        for col in range(cols):
            if colored[row][col]:
                continue

            cell = picture[row][col]
            stack = set()

            stack.add((row, col))

            # couldn't reuse color get new one
            strokes += 1

            while stack:
                r, c = stack.pop()
                colored[r][c] = strokes
                if r != 0:
                    top_cell = picture[r - 1][c]
                    if top_cell == cell and not (colored[r - 1][c]):
                        stack.add((r - 1, c))

                if r < rows - 1:
                    bottom_cell = picture[r + 1][c]
                    if bottom_cell == cell and not (colored[r + 1][c]):
                        stack.add((r + 1, c))

                if c != 0:
                    left_cell = picture[r][c - 1]
                    if left_cell == cell and not (colored[r][c - 1]):
                        stack.add((r, c - 1))

                if c <  cols - 1:
                    right_cell = picture[r][c + 1]
                    if right_cell == cell and not (colored[r][c + 1]):
                        stack.add((r, c + 1))

    return strokes

# print(strokesRequired(['aaaba', 'ababa', 'aaaca']))
print(strokesRequired(
[
"bbba",
"abba",
"acaa",
"aaac",
]
))
