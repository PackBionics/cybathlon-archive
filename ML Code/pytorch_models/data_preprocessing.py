import pandas as pd
import numpy as np
import os


def preprocess_excel_data(input_path, output_path):
    # Load raw data
    data = pd.read_excel(input_path, header=None)

    # Drop non-numeric columns by looking at first index
    columns = data.columns
    header = np.array([])
    for i, col_val in enumerate(data.iloc[0].to_list()):
        try:
            int(col_val)
        except ValueError:
            data = data.drop(labels=columns[i], axis=1)
            header = np.append(header, col_val)

    # Clean up headers
    header = [x.split(':')[0] for x in header[header != 'nan']]

    # Add dimension label to headers
    new_head = []
    for i in header:
        if i == 'Quat1':
            [new_head.append(i + '_' + dim) for dim in ['1', '2', '3', '4']]
        elif i == 'Angle':
            new_head.append('Angle')
        elif i != 'Time':
            [new_head.append(i + '_' + dim) for dim in ['x', 'y', 'z']]
        else:
            [new_head.append(i + '_' + str(j)) for j in range(2)]
    data.columns = new_head

    data.to_csv(output_path, index=False)


