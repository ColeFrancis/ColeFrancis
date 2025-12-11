import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Aizawa system definition
def aizawa(t, state, a=0.9, b=5.0, c=9.9, d=1.0):
    x, y, z = state

    dxdt = -a * x + y * y - (z * z) + a * c
    dydt = x * (y - b * z) + d
    dzdt = -z + x * (b * y + z)

    return [dxdt, dydt, dzdt]

# Initial condition and time range
initial_state = [1.0, 1.0, 1.0]
t_span = (0, 30)
t_eval = np.linspace(*t_span, 20000)

# Solve the system
solution = solve_ivp(aizawa, t_span, initial_state, t_eval=t_eval)

# Plotting
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')
ax.plot(solution.y[0], solution.y[1], solution.y[2], lw=0.5)
ax.set_title("Aizawa Attractor")
ax.set_xlabel("X Axis")
ax.set_ylabel("Y Axis")
ax.set_zlabel("Z Axis")
plt.show()
