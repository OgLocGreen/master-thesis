import numpy as np

# Create a 109x119 array filled with zeros
array = np.zeros((109, 119))

# Set the last column of the first 21 rows to 1
array[:21, -1] = 1

# Print the array
print(array)