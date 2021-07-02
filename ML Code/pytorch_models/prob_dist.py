import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

train_data = pd.read_csv('train_data.csv')
sns.distplot(train_data['Angle'])
plt.show()