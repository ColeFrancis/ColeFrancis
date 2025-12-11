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
import matplotlib.pyplot as plt

TAU = 3
THRESHOLD = 2
REFRACTORY = 1
RADIUS = 2

GRID_WIDTH = 20
STEPS = 20

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
    def __init__(self, initial_states):
        self.grid = [Cell(state) for state in initial_states]

    def _sum_neighbors(self, idx):
        sum = 0
        for t in range(0, TAU):
            if (self.grid[idx].history[t]): # Forget history beyond action potential
                break

            for step in range(1, RADIUS+1):
                neighbor_r = (idx + step) % len(self.grid)
                neighbor_l = (idx - step) % len(self.grid)

                sum += self.grid[neighbor_r].history[t]
                sum += self.grid[neighbor_l].history[t]
        return sum
    
    def update_grid(self, forcing_neurons=[]):
        for idx in range(len(self.grid)):
            sum = self._sum_neighbors(idx)

            for i in range(len(forcing_neurons)):
                if forcing_neurons[i] == idx:
                    sum = THRESHOLD

            self.grid[idx].compute_next_state(sum)

    
        for idx in range(len(self.grid)):
            self.grid[idx].commit_next_state()

    def get_states(self):
        return [cell.history[0] for cell in self.grid]


initial_states = [0] * GRID_WIDTH

atomata_grid = Grid(initial_states)

forcing = [10]

final_grid = [atomata_grid.get_states()]

for step in range(STEPS):
    atomata_grid.update_grid(forcing_neurons=forcing)
    final_grid.append(atomata_grid.get_states())

plt.imshow(final_grid, cmap='gray', interpolation='nearest')
plt.show()