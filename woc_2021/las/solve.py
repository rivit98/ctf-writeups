from pwn import *
from collections import deque

p = remote('kctf.rozdzka.securing.pl', 30000)
mv = lambda d: p.sendline(d.encode())

p.recvuntil('Stoisz przed wejsciem do lasu.')
m = p.recvuntil('Twoja lokalizacja:').decode().splitlines()
m = m[2:-3]

# lab = open('./sample.txt', 'rt', encoding='utf8').read().strip().splitlines()
lab = m
walls = {'┬', '│', '┌', '┐', '└', '┘', '┤', '├', '┴', '┼', '─', '╴', '╶', '╷', '╵'}

maze = []
for line in lab:
    maze_row = []
    for idx in range(0, len(line), 2):
        c = line[idx]

        if c in walls:
            maze_row.append('*')
        elif c in {' ', '#'}:
            if c == '#':
                start_pos = (len(maze), len(maze_row))

            maze_row.append(' ')

        else:
            print("unknown char", c)
            raise SystemExit


    # print(''.join(maze_row))
    maze.append(maze_row)


height = len(maze)
width = len(maze[0])

def maze2graph(maze):
    graph = {(i, j): [] for j in range(width) for i in range(height) if maze[i][j] == ' '}

    for row, col in graph.keys():
        if row < height - 1 and maze[row + 1][col] == ' ':
            graph[(row, col)].append(("S", (row + 1, col)))
            graph[(row + 1, col)].append(("N", (row, col)))
        if col < width - 1 and maze[row][col + 1] == ' ':
            graph[(row, col)].append(("E", (row, col + 1)))
            graph[(row, col + 1)].append(("W", (row, col)))

    return graph

def find_path_dfs(maze, start, goal):
    stack = deque([("", start)])
    visited = set()
    graph = maze2graph(maze)
    while stack:
        path, current = stack.pop()
        if current == goal:
            return path

        if current in visited:
            continue

        visited.add(current)
        for direction, neighbour in graph[current]:
            stack.append((path + direction, neighbour))

    raise SystemExit('no way')


targets = [(i, j) for j in range(width) for i in range(height) if (i == 0 or j == 0 or i == height-1 or j == width-1) and maze[i][j] == ' ' and (i, j) != start_pos]
print("start", start_pos)

# [(15, 0), (50, 49), (0, 71), (33, 110)]

way = find_path_dfs(maze, start_pos, (15, 0))
way = way[::2]
print(way)

for c in way:
    mv(c)

p.interactive()
