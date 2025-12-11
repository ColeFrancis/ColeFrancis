import numpy as np
import pygame
import matplotlib.pyplot as plt

CELL_SIZE = 100
GRID_WIDTH = 3
GRID_HEIGHT = 3

TAU = 10
DT = 0.1
RM = 1
V_THRESHOLD = 100
V_REST = 50
V_REFACTORY = 0
T_REFRACTORY = 0.5

class Neuron:
    def __init__(self):
        self.v = V_REST
        self.next_v = V_REST
        self.refractory_time = 0

    def compute_next_potential(self, i_in=0):
        if self.refractory_time > 0:
            self.next_v = V_REFACTORY
            self.refractory_time -= DT
            return
        
        v_next = self.v

        if v_next >= V_THRESHOLD:
            v_next = V_REFACTORY
            self.refractory_time = T_REFRACTORY
        
        v_next -= (DT/TAU) * (v_next - V_REST)
        v_next += RM * i_in

        self.next_v = v_next

    def commit(self):
        self.v = self.next_v
    
    def get_spike(self):
        if self.v >= V_THRESHOLD:
            return 1
        else:
            return 0
        
pygame.init()
screen = pygame.display.set_mode((GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE))
clock = pygame.time.Clock()

grid = []
potentials = []
for y in range(GRID_HEIGHT):
    grid.append([])
    potentials.append([])
    for x in range(GRID_WIDTH):
        grid[y].append(Neuron())
        potentials[y].append([])


time = 0
times = []

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if pygame.mouse.get_pressed()[0]:
            mx, my = pygame.mouse.get_pos()
            gx = mx // CELL_SIZE
            gy = my // CELL_SIZE

            grid[gy][gx].v = V_THRESHOLD

    # compute next membrane potential
    for y in range(GRID_HEIGHT):
        for x in range(GRID_WIDTH):
            i_in = 0
            # sum over all neighbors
            for dy in (-1, 0, 1):
                for dx in (-1, 0, 1):
                    if dx == 0 and dy == 0:
                        continue
                    nx = x + dx
                    ny = y + dy
                    if 0 <= nx < GRID_WIDTH and 0 <= ny < GRID_HEIGHT:
                        i_in += 50*grid[ny][nx].get_spike()

            grid[y][x].compute_next_potential(i_in)

    # commit membrane potentials
    for y in range(GRID_HEIGHT):
        for x in range(GRID_WIDTH):
            grid[y][x].commit()
            potentials[y][x].append(grid[y][x].v)

    times.append(time)
    time += DT

    
    screen.fill((0, 0, 0))
    for y in range(GRID_HEIGHT):
        for x in range(GRID_WIDTH):
            if (grid[y][x].get_spike()):
                pygame.draw.rect(screen, (255, 255, 0), (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))
            else:
                color_val = int(255*grid[y][x].v/V_THRESHOLD)
                pygame.draw.rect(screen, (color_val, color_val, color_val), (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))


    pygame.display.flip()
    clock.tick(60)

fig, axes = plt.subplots(GRID_WIDTH, GRID_HEIGHT, figsize=(10,10))

for y in range(GRID_HEIGHT):
    for x in range(GRID_WIDTH):
        axes[y][x].plot(times, potentials[y][x])
        axes[y][x].set_title(f'Cell {y+1},{x+1}')
        axes[y][x].set_xlabel('time')
        axes[y][x].set_ylabel('potential')

plt.tight_layout()
plt.show()

pygame.quit()