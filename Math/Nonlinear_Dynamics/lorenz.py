import numpy as np
from scipy.integrate import solve_ivp
from scipy.integrate import odeint
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Lorenz system definition
def lorenz(t, state, sigma=10, rho=28, beta=8/3):
    x, y, z = state
    dxdt = sigma * (y - x)
    dydt = x * (rho - z) - y
    dzdt = x * y - beta * z
    return [dxdt, dydt, dzdt]

# Initial condition and time range

sigma = 10.0
rho = 28.0
beta = 8/3.0

epsilon = 1e-8

initial_state = [1.0, 1.0, 1.0]
initial_pertubered = np.array(initial_state) + epsilon

t_span = (10, 100)
t_eval = np.linspace(*t_span, 10000)

# Solve the system
solution = solve_ivp(lorenz, t_span, initial_state, t_eval=t_eval)
solution_pertubered = solve_ivp(lorenz, t_span, initial_state, t_eval=t_eval)

# Plotting
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')
ax.plot(solution.y[0], solution.y[1], solution.y[2], lw=0.5)
ax.set_title("Lorenz Attractor")
ax.set_xlabel("X Axis")
ax.set_ylabel("Y Axis")
ax.set_zlabel("Z Axis")
plt.show()
