import scipy.io
import numpy as np

# Load the .mat file
def load_data(file_path):
    try:
        data = scipy.io.loadmat(file_path)
        input_data = data.get('input_data')
        output_data = data.get('output_data')

        if input_data is None or output_data is None:
            raise ValueError("'input_data' or 'output_data' not found in the .mat file.")

        return input_data, output_data
    except Exception as e:
        raise ValueError(f"Error loading file: {e}")

# Find the row in 'input_data' closest to the input array and return corresponding 'output_data' row
def find_closest_row(input_data, output_data, input_array):
    try:
        distances = np.linalg.norm(input_data - np.array(input_array), axis=1)
        closest_row_index = np.argmin(distances)
        return output_data[closest_row_index]
    except Exception as e:
        raise ValueError(f"Error in finding closest row: {e}")

# Example usage
if __name__ == "__main__":
    file_path = 'net_data.mat'
    input_array = [12, 52, 60, 150]

    try:
        input_data, output_data = load_data(file_path)
        result = find_closest_row(input_data, output_data, input_array)
        print("The corresponding output_data row is:", result)
    except Exception as e:
        print(e)
