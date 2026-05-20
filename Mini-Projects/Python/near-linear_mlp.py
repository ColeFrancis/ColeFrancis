import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

#################################################
### Generate training data
#################################################

def target_fun(x):
    return torch.sin(x) + 0.3 * x

t = torch.linspace(-10, 10, 1000).unsqueeze(1)

ground_truth = target_fun(t)

#################################################
### Define model
#################################################

WIDTH = 512
DEPTH = 3
NEGATIVE_SLOPE = 0.01

class MLP(nn.Module):
    def __init__(self):
        super().__init__()

        layers = []

        layers.append(nn.Linear(1, WIDTH))
        layers.append(nn.LeakyReLU(negative_slope=NEGATIVE_SLOPE))

        for _ in range(DEPTH - 1):
            layers.append(nn.Linear(WIDTH, WIDTH))
            layers.append(nn.LeakyReLU(negative_slope=NEGATIVE_SLOPE))

        layers.append(nn.Linear( WIDTH, 1))

        self.net = nn.Sequential(*layers)

    def forward(self, x):
        return self.net(x)
    
################################################
### Train model
################################################


EPOCHS = 500
LEARNING_RATE = 1e-3

model = MLP()
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=LEARNING_RATE)


for epoch in range(EPOCHS):
    optimizer.zero_grad()

    y_pred = model(t)

    loss = criterion(y_pred, ground_truth)

    loss.backward()
    optimizer.step()

    if epoch % 50 == 0:
        print(f'Epoch {epoch}, Loss = {loss.item():.6f}')

with torch.no_grad():
    y_out = model(t)

plt.plot(t.numpy(), ground_truth.numpy(), label="True function")
plt.plot(t.numpy(), y_out.numpy(), label='MLP output')
plt.legend()
plt.show()