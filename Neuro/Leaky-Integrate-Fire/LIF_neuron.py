import numpy as np
import matplotlib.pyplot as plt

T_STOP = 30

TAU = 10
DT = 0.1
RM = 1
V_THRESHOLD = 100
V_REST = 50
V_REFACTORY = 0

class Neuron:
    def __init__(self, neighbor_ids):
        self.v = V_REST
        self.neighbor_ids = neighbor_ids

    def update(self, i_in=0):
        if self.v >= V_THRESHOLD:
            self.v = V_REFACTORY
        
        self.v -= (DT/TAU) * (self.v - V_REST)
        self.v += RM * i_in
    
    def get_spike(self):
        if self.v >= V_THRESHOLD:
            return 1
        else:
            return 0

        
t = np.arange(0, T_STOP, DT)

spikes = np.zeros_like(t)
spikes[1] = 1
spikes[5] = 1

neuron1 = Neuron([])
neuron2 = Neuron([])

potentials1 = []
potentials2 = []



for i in range(len(t)):
    neuron1.update(50*spikes[i])
    neuron2.update(50*neuron1.get_spike())

    potentials1.append(neuron1.v)
    potentials2.append(neuron2.v)

plt.plot(t, potentials1, label='neuron1')
plt.plot(t, potentials2, label='neuron2')
plt.xlabel('Time (t)')
plt.ylabel('Membrane Potential')
plt.title('Neuron membrane potential over time')
plt.legend()
plt.show()


        

