import numpy as np
import matplotlib.pyplot as plt

################################################################################
### Envoronment variables and time scale
################################################################################

Dt = 0.01
Duration = 10
t = np.arange(0, Duration, Dt)

################################################################################
### Generate Oscillators, initialize weights, define activation
################################################################################

NUMBER_OSCILLTORS = 500 
f_min, f_max = 1.0, 40.0

freqs = np.logspace(np.log10(f_min), np.log10(f_max), NUMBER_OSCILLTORS)
phases = np.random.uniform(0, 2*np.pi, NUMBER_OSCILLTORS)
#phases = np.zeros(NUMBER_OSCILLTORS)

oscillators = np.array([np.sin(2*np.pi*f*t + p) for f, p in zip(freqs, phases)])
# small gaussian noise
oscillators += np.random.normal(scale=0.05, size=oscillators.shape) 

weights = np.random.normal(scale=0.1, size=NUMBER_OSCILLTORS)

def sigma(x): # relu activation function works better than sigmoid, tanh
    return np.maximum(0, x)

# For backpropogation
def sigma_prime(x):
    return (x>0).astype(float)

################################################################################
### Setup for training
################################################################################

def forward(weights, oscillators):
    output = np.sum(weights[:, None] * oscillators, axis=0)
    output = sigma(output)
    return output

def gaussian(t, T_target, sigma_t):
    return np.exp(-0.5 * ((t - T_target) / sigma_t)**2)

target_time = 3.5
target_width = 0.5

target_curve = gaussian(t, target_time, target_width)

################################################################################
### Training loop
################################################################################

epochs = 2000
learning_rate = 0.005

print_period = 10

for epoch in range(1, epochs):
    z = np.sum(weights[:,None] * oscillators, axis=0)
    out = sigma(z)

    error = target_curve - out 
    loss = np.mean(error**2)
    
    dL_dz = -2 * error * sigma_prime(z)

    gradient = np.mean(dL_dz[None, :] * oscillators, axis=1)

    weights -= learning_rate * gradient

    if (epoch % print_period ) == 0:
        peak_time = t[np.argmax(out)]
        print(f"epoch: {epoch}, loss={loss:.6e}, peak_time={peak_time:0.3f}s")

out = forward(weights, oscillators)

plt.plot(t, target_curve, label="Target")
plt.plot(t, out, label="Model output")
#plt.plot(t, oscillators[0])
plt.xlabel("output")
plt.ylabel("time")
plt.title("Simple Striatal beat frequency model")
plt.legend()
plt.show()
