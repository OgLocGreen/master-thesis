import numpy as np
import matplotlib.pyplot as plt

# Create a 200x200 array with the first 20 rows having 1 in the last column
array1 = np.zeros((200, 200))
array1[:20, -1] = 1

# Create a square array filled with ones
square_size = 100
array2 = np.ones((square_size, square_size))

# Calculate the starting position for placing the square in the middle
start_x = (array1.shape[0] - array2.shape[0]) // 2
start_y = (array1.shape[1] - array2.shape[1]) // 2

# Create an array with the square placed in the middle
expanded_array2 = np.zeros_like(array1, dtype=bool)
expanded_array2[start_x:start_x+array2.shape[0], start_y:start_y+array2.shape[1]] = True

# Perform element-wise logical OR operation
result = np.logical_or(array1, expanded_array2)

print(result.shape)
# Display the resulting image
plt.imshow(result, cmap='gray')
plt.show()
