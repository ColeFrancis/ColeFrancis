import numpy as np
import pygame
import random

class Grid:
    def __init__(self, n):
        self.part_row = 0
        self.part_col = 0

        self.grid = [[random.randint(0, 1) for _ in range(n)] for _ in range(n)]
        #self.grid = [row[:] for row in initial_state]

        self.next_grid = [[0 for _ in row] for row in self.grid]

    def get_state(self, row, col):
        return self.grid[row][col]
    
    def update(self):
        rows = len(self.grid)
        cols = len(self.grid[0])

        self.part_row ^= 1
        self.part_col ^= 1

        for row in range(self.part_row, rows, 2):
            for col in range(self.part_col, cols, 2):
                r0 = row
                r1 = (row + 1) % rows
                c0 = col
                c1 = (col + 1) % cols

                if (self.grid[r0][c0] == self.grid[r1][c0] == self.grid[r0][c1] == self.grid[r1][c1]):
                    self.next_grid[r0][c0] ^= 1
                    self.next_grid[r1][c0] ^= 1
                    self.next_grid[r0][c1] ^= 1
                    self.next_grid[r1][c1] ^= 1

        self.grid = [row[:] for row in self.next_grid]


CANVAS_WIDTH = 2000
CANVAS_HEIGHT = 2000

board = Grid(80)

grid_height = len(board.grid)
grid_width = len(board.grid[0])

cell_height = CANVAS_HEIGHT / grid_height
cell_width = CANVAS_WIDTH / grid_width

pygame.init()
screen = pygame.display.set_mode((CANVAS_WIDTH, CANVAS_HEIGHT))
clock = pygame.time.Clock()



forcing = []

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((255, 255, 255))
    for y in range(len(board.grid)):
        for x in range(len(board.grid[y])):
            if (board.get_state(y, x)):
                pygame.draw.rect(screen, (0, 0, 0), (x * cell_width, y * cell_height, cell_width, cell_height))
    
    pygame.display.flip()

    board.update()

    clock.tick(5)

pygame.quit()
