import numpy as np

arr = np.array([[0, 0, 0], 
                [0, 1, 1],
                [0, 1, 1]])

zero_indices = np.where(arr == 0)
one_indices = np.where(arr == 1)

print("Indices where elements are 0:")
print(zero_indices)

print("\nIndices where elements are 1:")
print(one_indices)