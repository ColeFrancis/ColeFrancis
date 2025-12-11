import matplotlib.pyplot as plt
import numpy as np

points_r = []
points_i = []

with open ('data_out', 'r') as f:
    for line in f:
        values = line.strip().split()
        if not values:
            continue

        if (len(values) >= 3 and values[2] == '1'):
            points_r.append(float(values[0]))
            points_i.append(float(values[1]))

width, height = 4000, 4000
H, xedges, yedges = np.histogram2d(points_i, points_r, bins=[height, width], range=[[-1.5, 1.5], [-2, 1]])

H = (H > 0).astype(float)

plt.imshow(H, extent=[-2, 1, -1.5, 1.5], cmap='binary', origin='lower')
plt.tight_layout()
plt.savefig('mandlebrot.png', dpi=300, bbox_inches='tight', pad_inches=0)

#plt.scatter(points_r, points_i, s=0.5, color='black')
#plt.xlim(-2, 1)
#plt.ylim(-1.5, 1.5)
#plt.show()
