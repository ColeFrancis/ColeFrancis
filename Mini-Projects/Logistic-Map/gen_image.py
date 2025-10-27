import matplotlib.pyplot as plt
import numpy as np

r_vals = []
x_vals = []

with open ('logistic_out', 'r') as f:
    for line in f:
        values = line.strip().split()
        if not values:
            continue

        r = float(values[0])
        x = np.array(values[1:], dtype=float)
        r_vals.extend([r] * len(x))
        x_vals.extend(x)

H, xedges, yedges = np.histogram2d(r_vals, x_vals, bins=(4000,2000), range=[[3.5,4.0], [0,1]])

H = np.log1p(H)
H = np.flipud(H.T)
H = np.power(H, 0.1)

plt.figure(figsize=(10,6), dpi=600)
plt.imshow(H, extent=[3.5, 4.0, 0, 1], cmap='binary', aspect='auto')

#plt.scatter(r_vals, x_vals, s=0.01, color='black')
plt.xlabel("r")
plt.ylabel("x")
plt.title("Logistic map")
plt.savefig('logistic_map.png', dpi=600, bbox_inches='tight', pad_inches=0)
plt.close()
