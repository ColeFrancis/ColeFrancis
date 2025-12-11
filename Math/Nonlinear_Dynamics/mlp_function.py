import numpy as np
import matplotlib.pyplot as plt
import torch
import torch.nn as nn

class MLP_FUNC(nn.Module):
    def __init__(self):
        super().__init__()

        self.fc1 = nn.Linear(1, 500)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(500, 1)

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        return x
    
model = MLP_FUNC()

def target_func(x):
    return  0.5 * x**3 + x**2 - 0.5 * x + 1

x_train = torch.linspace(-3, 1.5, 200).unsqueeze(1)
y_train = target_func(x_train)

criterion = nn.MSELoss()
optimizer = torch.optim.SGD(model.parameters(), lr = 0.001, momentum=0.9)

plt.plot(x_train.numpy(), y_train.numpy(), label="true")

for epoch in range(5000):
    optimizer.zero_grad()
    y_pred = model(x_train)
    loss = criterion(y_pred, y_train)
    loss.backward()
    optimizer.step()

    if epoch == 0 or epoch == 10 or epoch == 20 or epoch == 50 or epoch == 100 or epoch == 200 or epoch == 500 or epoch == 1000 or epoch == 4999:
        print(f"Epoch {epoch}, Loss: {loss.item():.6f}")
        plt.plot(x_train.numpy(), y_pred.detach().numpy(), label=f'Epoch {epoch}')

plt.legend()
plt.show()
