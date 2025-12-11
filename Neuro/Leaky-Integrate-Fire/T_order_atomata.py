# Base:
#   If sum of neighbors on over past T (tau) steps > V (threshold), turn on
#
# Refractory period:
#   If cell was on < R (refractory) (usually 1) steps ago, don't turn on
#
# Hebbian Synapses:
#   If cell turns on in the same cycle a neighbor turns on (or some # steps more recent then T) then increase the weight
#   
# Small-world structure
#   Change from cellular atomata to network atomata

import numpy as np
import pygame

TAU = 10
THRESHOLD = 6
REFRACTORY = 2

class Cell:
    def __init__(self, initial_state):
        self._next_state = 0
        self.history = [initial_state] + [0] * (TAU-1) # [0] is most recent, [TAU] is least recent
    
    def compute_next_state(self, neighbor_sum=0):
        self._next_state = 0

        if neighbor_sum >= THRESHOLD:
            for i in range(REFRACTORY):
                if self.history[i] == 1:
                    return
                
            self._next_state = 1

    def commit_next_state(self):
        self.history.insert(0, self._next_state)
        self.history.pop()

class Grid:
    def __init__(self, initial_state):
        self.grid = []

        for row in range(len(initial_state)):
            row_list = []
            for col in range(len(initial_state[row])):
                row_list.append(Cell(initial_state[row][col]))

            self.grid.append(row_list)

    def _sum_neighbors(self, row, col):
        sum = 0
        for t in range(0, TAU):
            for dy in (-1, 0, 1):
                    for dx in (-1, 0, 1):
                        nr = row + dy
                        nc = col + dx

                        if dy == 0 and dx == 0:
                            continue

                        if 0 <= nr < len(self.grid) and 0 <= nc < len(self.grid[row]):
                            sum += self.grid[nr][nc].history[t]

        return sum
    
    def update_grid(self, forcing_neurons):
        for row in range(len(self.grid)):
            for col in range(len(self.grid[row])):
                sum = self._sum_neighbors(row, col)

                for i in range(len(forcing_neurons)):
                    if forcing_neurons[i][0] == row and forcing_neurons[i][1] == col:
                        sum = THRESHOLD

                self.grid[row][col].compute_next_state(sum)
    
        for row in range(len(self.grid)):
            for col in range(len(self.grid[row])):
                self.grid[row][col].commit_next_state()

    def get_state(self, row, col):
        return self.grid[row][col].history[0]

CANVAS_WIDTH = 500
CANVAS_HEIGHT = 500

initial_states = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

grid_height = len(initial_states)
grid_width = len(initial_states[0])

cell_height = CANVAS_HEIGHT / grid_height
cell_width = CANVAS_WIDTH / grid_width

pygame.init()
screen = pygame.display.set_mode((CANVAS_WIDTH, CANVAS_HEIGHT))
clock = pygame.time.Clock()


atomata_grid = Grid(initial_states)

forcing = []

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if pygame.mouse.get_pressed()[0]:
            mx, my = pygame.mouse.get_pos()
            gx = mx // cell_width
            gy = my // cell_height

            forcing.append([gy, gx])

    screen.fill((255, 255, 255))
    for y in range(len(atomata_grid.grid)):
        for x in range(len(atomata_grid.grid[y])):
            if (atomata_grid.get_state(y, x)):
                pygame.draw.rect(screen, (0, 0, 0), (x * cell_width, y * cell_height, cell_width, cell_height))
    
    pygame.display.flip()

    atomata_grid.update_grid(forcing)

    forcing = []

    clock.tick(5)

pygame.quit()
