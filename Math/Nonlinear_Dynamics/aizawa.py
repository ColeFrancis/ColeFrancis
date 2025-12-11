import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Aizawa system definition
def aizawa(t, state, a=0.95, b=0.7, c=0.6, d=3.5, e=0.25, f=0.1):
    x, y, z = state

    dxdt = (z - b) * x - d * y
    dydt = d * x + (z - b) * y
    dzdt = c + a * z - (z * z * z) / 3 - (x * x + y * y) * (1 + e * z) + f * z * (x * x * x)

    return [dxdt, dydt, dzdt]

# Initial condition and time range
initial_state_1 = [1.0, 1.0, 1.0]
initial_state_2 = [1.001, 1.0, 1.0]
t_span = (0, 150)
t_eval = np.linspace(*t_span, 15000)

# Solve the system
solution_1 = solve_ivp(aizawa, t_span, initial_state_1, t_eval=t_eval)
solution_2 = solve_ivp(aizawa, t_span, initial_state_2, t_eval=t_eval)

# Plotting
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')
ax.plot(solution_1.y[0], solution_1.y[1], solution_1.y[2], lw=1.0, color='blue')
ax.plot(solution_2.y[0], solution_2.y[1], solution_2.y[2], lw=1.0, color='red')

ax.set_facecolor('black')
ax.grid(False)
ax.xaxis.pane.set_visible(False)
ax.yaxis.pane.set_visible(False)
ax.zaxis.pane.set_visible(False)

ax.set_title("Aizawa Attractor")
ax.set_xlabel("X Axis")
ax.set_ylabel("Y Axis")
ax.set_zlabel("Z Axis")
plt.show()
