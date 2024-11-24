# https://adventofcode.com/2023/day/10

import collections as coll
import itertools as it

# parse and pad
maze = open('input.txt').read()
num_rows = maze.index('\n')
S_row, S_col = divmod(maze.index('S'), num_rows + 1)
maze = maze.split()
num_rows += 4
num_cols = len(maze[0]) + 4
maze = (
    [[' ']*num_rows] +
    [[' '] + ['.']*(num_cols - 2) + [' ']] +
    [[' ', '.'] + list(row) + ['.', ' '] for row in maze] +
    [[' '] + ['.']*(num_cols - 2) + [' ']] +
    [[' ']*num_rows]
)
start_pos = (S_row + 2, S_col + 2)
maze_at = lambda pos: maze[pos[0]][pos[1]]

def print_maze():
    print('\n'.join(''.join(row) for row in maze))

print(f'found start \'{maze_at(start_pos)}\' at {start_pos}')

# maze logic
right = lambda pos: (pos[0], pos[1] + 1)
above = lambda pos: (pos[0] - 1, pos[1])
left  = lambda pos: (pos[0], pos[1] - 1)
below = lambda pos: (pos[0] + 1, pos[1])
pipings = {
    right: {'-': right, 'J': above, '7': below},
    above: {'|': above, 'F': right, '7': left},
    left:  {'-': left, 'F': below, 'L': above},
    below: {'|': below, 'J': left, 'L': right}
}

def pipe_out_direction_at(prev_pos, curr_pos):
    for in_direction in pipings:
        if curr_pos == in_direction(prev_pos):
            return pipings[in_direction][maze_at(curr_pos)]

# do first step
main_loop = [[start_pos, None]]
for direction in pipings:
    next_pos = direction(start_pos)
    if maze_at(next_pos) in pipings[direction]: 
        main_loop[-1][1] = direction
        main_loop.append([next_pos, None])
        break

# traverse main loop
while main_loop[-1][0] != start_pos:
    next_direction = pipe_out_direction_at(main_loop[-2][0], main_loop[-1][0])
    main_loop[-1][1] = next_direction
    main_loop.append([next_direction(main_loop[-1][0]), None])
print(f'part 1 solution: {len(main_loop)//2}')
main_loop.pop()
start_direction = main_loop[0][1]
final_direction = main_loop[-1][1]

# replace start with correct pipe
def replace_start():
    for in_direction, out_direction_map in pipings.items():
        for pipe_char, out_direction in out_direction_map.items():
            if start_direction == out_direction and final_direction == in_direction:
                maze[start_pos[0]][start_pos[1]] = pipe_char
                return
replace_start()
print(f'replaced start with {maze_at(start_pos)}')

# breadth first search
def flood_replace(*, flood_start_pos, new_tile):
    bool_arr = [[False]*num_cols for _ in range(num_rows)]
    for pos, _ in main_loop:
        bool_arr[pos[0]][pos[1]] = True
    on_main_loop = lambda pos: bool_arr[pos[0]][pos[1]]
    breadth_queue = coll.deque([flood_start_pos])
    area_deleted = maze_at(flood_start_pos) != ' '
    maze[flood_start_pos[0]][flood_start_pos[1]] = new_tile
    while len(breadth_queue) > 0:
        curr_pos = breadth_queue.popleft()
        for direction in pipings:
            next_pos = direction(curr_pos)
            if maze_at(next_pos) != new_tile and not on_main_loop(next_pos):
                area_deleted += maze_at(next_pos) != ' '
                maze[next_pos[0]][next_pos[1]] = new_tile
                breadth_queue.append(next_pos)
    return area_deleted

# remove everything outside main loop
flood_replace(flood_start_pos=(1, 1), new_tile=' ')
print_maze()

# expand maze to expose slippage between pipes
maze = list(it.chain.from_iterable(
    [list(it.chain.from_iterable([c, ' '] for c in row)), [' ']*2*num_cols]
    for row in maze
))
num_rows = len(maze)
num_cols = len(maze[0])
start_pos = (2*start_pos[0], 2*start_pos[1])
main_loop = [[(2*pos[0], 2*pos[1]), step_direction] for pos, step_direction in main_loop]
# not added in order but idc at this point
main_loop += [[step_direction(pos), step_direction] for pos, step_direction in main_loop]

# find first tile inside main loop
def find_first_inside_pos():
    for i, row in enumerate(maze):
        for j, tile in enumerate(row):
            if tile == 'F':
                return right(below((i, j)))
first_inside_pos = find_first_inside_pos()

area_inside = flood_replace(flood_start_pos=first_inside_pos, new_tile='█')

# visually reconnect pipes to make it look pretty
for pos in it.product(range(0, num_rows, 2), range(1, num_cols - 1, 2)):
    if maze_at(left(pos)) in pipings[left] and maze_at(right(pos)) in pipings[right]:
        maze[pos[0]][pos[1]] = '-'
for pos in it.product(range(1, num_rows - 1, 2), range(0, num_cols, 2)):
    if maze_at(below(pos)) in pipings[below] and maze_at(above(pos)) in pipings[above]:
        maze[pos[0]][pos[1]] = '|'

print_maze()
print(f'part 2 solution: {area_inside}')
