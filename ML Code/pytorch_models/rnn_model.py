import torch
from torch import nn
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
import matplotlib.pyplot as plt
import seaborn as sns
from torch.utils.data import Dataset, DataLoader
from sklearn.model_selection import train_test_split
import numpy as np


class RNNDataset(Dataset):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __len__(self):
        return len(self.x)

    def __getitem__(self, index):
        _x = self.x[index]
        _y = self.y[index]
        return _x, _y


class RNNModel(nn.Module):

    def __init__(self, batch_size, rnn_input_dim, rnn_hidden_dim, rnn_num_layers=1):
        super().__init__()
        # Initial hidden state for each epoch
        self.h_0 = torch.zeros(size=(rnn_num_layers, batch_size, rnn_hidden_dim)).to(device)

        # Model layers
        self.rnn_input = nn.LSTM(input_size=rnn_input_dim, hidden_size=rnn_hidden_dim, num_layers=rnn_num_layers,
                                 dropout=0.2)
        # out --> (direction * num_layers, batch, hidden) (hidden state) SQUEEZE
        self.linear1 = nn.Linear(rnn_hidden_dim, 128)
        self.relu = nn.ReLU()
        self.dropout = nn.Dropout(p=0.2)
        self.fc_out = nn.Linear(128, 1)

    def forward(self, x):
        outputs, (hidden, cell) = self.rnn_input(x)
        x = self.linear1(hidden)
        x = self.relu(x)
        x = self.dropout(x)
        x = self.fc_out(x)
        return x


def training_loop():
    # Hyper parameters
    batch_size = 64
    num_features = norm_x_data.shape[1]
    rnn_hidden_dim = 256
    learning_rate = 0.0001
    weight_decay = 1e-5
    epochs = 20

    # Instantiate model
    model = RNNModel(batch_size=batch_size, rnn_input_dim=num_features, rnn_hidden_dim=rnn_hidden_dim).to(device)
    model = model.float()

    # Optimizer and loss function
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate, weight_decay=weight_decay)
    criterion = torch.nn.MSELoss()

    # Data loaders
    training_generator = DataLoader(RNNDataset(train_x, train_y), batch_size=batch_size, shuffle=True)
    validation_generator = DataLoader(RNNDataset(val_x, val_y), batch_size=batch_size, shuffle=True)

    # Loop over epochs
    train_loss_history = []
    val_loss_history = []
    for epoch in range(epochs):
        # Train batch
        batch_train_loss_history = []
        for (batch_train_x, batch_train_y) in training_generator:
            # Zero out gradients
            optimizer.zero_grad()

            # Add new axis
            batch_train_x = batch_train_x[None, :, :]

            # Set model to train
            model.train()

            # Make predictions
            train_predictions = model(batch_train_x.float())
            train_predictions = train_predictions.squeeze(2).squeeze(0)  # reduce to one dimension

            # Calculate train loss
            train_loss = criterion(train_predictions, batch_train_y)
            batch_train_loss_history.append(train_loss.item())

            # Back prop and optimizer step
            train_loss.backward()
            optimizer.step()

        train_loss_history.append(sum(batch_train_loss_history) / len(batch_train_loss_history))

        # Validation batch NOTE: after back prop on training
        batch_val_loss_history = []
        total_test_preds = []
        for (batch_val_x, batch_val_y) in validation_generator:
            # Add new axis
            batch_val_x = batch_val_x[None, :, :]

            # Evaluate model
            model.eval()
            with torch.no_grad():
                val_predictions = model(batch_val_x)
            model.train()
            val_predictions = val_predictions.squeeze(2).squeeze(0)  # reduce to one dimension

            # Calculate validation loss
            val_loss = criterion(val_predictions, batch_val_y)
            batch_val_loss_history.append(val_loss.item())
        val_loss_history.append(sum(batch_val_loss_history) / len(batch_val_loss_history))

    # Plot loss
    plt.figure()
    plt.title('MSE Loss')
    plt.plot(range(epochs), train_loss_history, label='train loss')
    plt.plot(range(epochs), val_loss_history, label='val loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    # Set device to enable GPU
    device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')
    print('DEVICE', device)

    # Load in data
    data = pd.read_csv('train_data.csv')
    y_data = data.pop('Angle').to_numpy()
    x_data = data
    x_data.drop(columns=['Time_0', 'Time_1'], inplace=True)

    # Split train, val, test
    # train_x, val_x, train_y, val_y = train_test_split(norm_x_data, y_data, test_size=0.5, random_state=0, shuffle=True)
    # val_x, test_x, val_y, test_y = train_test_split(val_x, val_y, test_size=0.5, random_state=0, shuffle=True)

    # Scale X between 0 and 1
    min_max_scaler = MinMaxScaler(feature_range=(0, 1))
    norm_x_data = min_max_scaler.fit_transform(x_data)

    # FOR TESTING
    train_x = norm_x_data
    train_y = y_data

    # Cast to tensors
    train_x = torch.tensor(train_x, requires_grad=False, dtype=torch.float).to(device)
    train_y = torch.tensor(train_y, requires_grad=False, dtype=torch.float).to(device)

    # test_x = torch.tensor(test_x, requires_grad=False, dtype=torch.float).to(device)
    # test_y = torch.tensor(test_y, requires_grad=False, dtype=torch.float).to(device)

    # TESTING
    test_data = pd.read_csv('test_data_2.csv')
    test_y = test_data.pop('Angle').to_numpy()
    test_x = test_data
    test_x.drop(columns=['Time_0', 'Time_1'], inplace=True)

    norm_test_data = min_max_scaler.transform(test_x)

    val_x = torch.tensor(norm_test_data, requires_grad=False, dtype=torch.float).to(device)
    val_y = torch.tensor(test_y, requires_grad=False, dtype=torch.float).to(device)

    training_loop()








