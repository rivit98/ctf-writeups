import marshal

with open("./mapdump", "rb") as f:
    map = marshal.load(f)


def dfs(x, y, visited):
    if x == 125 and y == 126:
        return list(visited)

    for m in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
        mx, my = m
        nx = x + mx
        ny = y + my
        if (nx, ny) in visited or not map[ny][nx]:
            continue

        if v := dfs(nx, ny, visited + [(nx, ny)]):
            return v

    return []


def main():
    startx, starty = 1, 0
    positions = dfs(startx, starty, [])
    print(positions)

    # get move sequence
    moves = []
    x,y = startx, starty
    for px,py in positions:
        mx = px-x
        my = py-y

        if mx == 1:
            moves.append('C')
        if mx == -1:
            moves.append('E')
        if my == 1:
            moves.append('O')
        if my == -1:
            moves.append('H')

        x = px
        y = py

    print(''.join(moves))

if __name__ == "__main__":
    import sys

    sys.setrecursionlimit(10000)
    main()
