#!/usr/bin/env python3


def get_vertices(wire):
    x = y = 0
    vertices = [(x, y)]

    for edge in wire:
        length = int(edge[1:])

        if edge[0] == "R":
            x += length

        if edge[0] == "L":
            x -= length

        if edge[0] == "U":
            y += length

        if edge[0] == "D":
            y -= length

        vertices.append((x, y))

    return vertices


def get_intersections(edges1, edges2):
    intersections = []

    for i in range(len(edges1) - 1):
        for j in range(len(edges2) - 1):
            intersection = get_intersection(
                edges1[i], edges1[i + 1], edges2[j], edges2[j + 1]
            )
            if intersection:
                intersections.append(intersection)

    # remove 0,0 if any
    try:
        intersections.remove((0, 0))
    except Exception:
        pass

    return intersections


def get_distance(vert):
    return abs(vert[0]) + abs(vert[1])


def get_intersection(e1from, e1to, e2from, e2to):
    e1x1, e1y1 = e1from
    e1x2, e1y2 = e1to
    e2x1, e2y1 = e2from
    e2x2, e2y2 = e2to

    if e1y1 == e1y2 and e2x1 == e2x2:
        # e1 is horizontal and e2 is vertical
        if (e2y1 <= e1y1 <= e2y2 or e2y1 >= e1y1 >= e2y2) and (
            e1x1 <= e2x1 <= e1x2 or e1x1 >= e2x1 >= e1x2
        ):
            return (e2x1, e1y1)
    elif e2y1 == e2y2 and e1x1 == e1x2:
        # e1 is vertical and e2 is horizontal
        if (e1y1 <= e2y1 <= e1y2 or e1y1 >= e2y1 >= e1y2) and (
            e2x1 <= e1x1 <= e2x2 or e2x1 >= e1x1 >= e2x2
        ):
            return (e1x1, e2y1)


def get_closest_intersection(edges1, edges2):
    ints = get_intersections(edges1, edges2)
    return min(map(lambda vert: get_distance(vert), ints))


def test1():
    wire1 = ["R8", "U5", "L5", "D3"]
    wire2 = ["U7", "R6", "D4", "L4"]

    edges1 = get_vertices(wire1)
    edges2 = get_vertices(wire2)
    assert get_closest_intersection(edges1, edges2) == 6


def test2():
    wire1 = ["R75", "D30", "R83", "U83", "L12", "D49", "R71", "U7", "L72"]
    wire2 = ["U62", "R66", "U55", "R34", "D71", "R55", "D58", "R83"]

    edges1 = get_vertices(wire1)
    edges2 = get_vertices(wire2)
    assert get_closest_intersection(edges1, edges2) == 159


if __name__ == "__main__":
    with open("../inputs/day03.txt") as ip:
        lines = ip.readlines()
        wire1 = lines[0].strip().split(",")
        edges1 = get_vertices(wire1)

        wire2 = lines[1].strip().split(",")
        edges2 = get_vertices(wire2)
        print(get_closest_intersection(edges1, edges2))
