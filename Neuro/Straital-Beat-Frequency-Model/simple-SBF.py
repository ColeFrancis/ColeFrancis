import numpy as np
from scipy.optimize import curve_fit # to fit gaussians
from scipy.signal import argrelextrema
from scipy.interpolate import interp1d
import matplotlib.pyplot as plt

################################################################################
### Envoronment variables
################################################################################

Dt = 0.01
Duration = 40
t = np.arange(0, Duration, Dt)

T = np.array([10, 30])

NUM_OSCILLTORS = 1000
f_min, f_max = 8, 13 # paper didn't specify values but it the alpha band was mentioned earlier in the paper
freq_noise_strength = 0.1

################################################################################
### Generate Oscillators, initialize weights, generate and normalize output
################################################################################

#f_i = (f_min, ..., f_max)
freqs = np.linspace(f_min, f_max, NUM_OSCILLTORS)

# Add gaussain noise to introduce variablilit in frequencies
freqs += np.random.normal(0, freq_noise_strength, freqs.shape)

# v_i = cos(2pi*f_i*t)
oscillators = np.cos(2 * np.pi * freqs * t[:,None]) # shape: (#t, #freqs) 

#w_i,j = sum_j(v_i(T_j)) = sum_j( cos(2pi * f_i * T_j) )
weights = np.cos(2 * np.pi * freqs[:,None] * T) # shape: (#freqs, #T)
weights /= np.max(weights, axis = 0)

#out(t, T) = sum_i (w_i*v_i(t)) = sum_i (osc(t, f_i) * w(f_i, T_j))
out = oscillators @ weights # shape: (#t, #T)
out_norm = np.maximum((out / np.max(np.abs(out), axis=0)), 0)

################################################################################
### Fit gaussian curve
################################################################################

def gaussian(t, A, T, sigma, B):
    return A * np.exp(-0.5 * ((t - T) / sigma)**2) + B
'''
maxima_indices = argrelextrema(out_norm[:, 0], np.greater)[0]
values = out_norm[:,0]

filtered_maxima = maxima_indices #filtered maxima are as such that their values are greater than at least one of their neighbors

changed = True
while changed  and len(filtered_maxima) > 1:
    changed = False
    to_remove = []
    for i in range(1, len(filtered_maxima)-1):
        left_idx = filtered_maxima[i-1]
        center_idx = filtered_maxima[i]
        right_idx = filtered_maxima[i+1]

        if (values[center_idx] < values[left_idx] and values[center_idx] < values[right_idx]):
            to_remove.append(center_idx)

    if to_remove:
        changed=True
        filtered_maxima = np.array([idx for idx in filtered_maxima if idx not in to_remove])

filtered_out_func = interp1d(t[filtered_maxima], out_norm[:,0][filtered_maxima], kind='linear', fill_value='extrapolate')
filtered_out = filtered_out_func(t)

peak_idx = np.argmax(filtered_out)
peak_time = t[peak_idx]

p0 = [1.0, peak_time, 5.0, 0.0] #guess amplitude 1, T=peak_time, sigma=0.5, B=0
params, _ = curve_fit(gaussian, t, filtered_out, p0=p0)
'''
################################################################################
### Plot output
################################################################################

for i in range(len(T)):
    print(i)
    plt.plot(t, out_norm[:,i])
    
plt.plot(t, gaussian(t, 1, 10, 0.2, 0))
plt.xlabel("time")
plt.ylabel("output")
plt.title("Simple Striatal beat frequency model")
plt.legend()
plt.show()
