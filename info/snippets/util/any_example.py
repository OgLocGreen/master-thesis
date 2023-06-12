import numpy as np

# Creating a three-dimensional logical array
I_2 = np.array([[[True, False, False],
                 [False, False, False]],

                [[True, False, True],
                 [False, False, False]],
                 
                 
                 [[False, False, False],
                 [True, False, False]],

                [[False, False, False],
                    [False, False, True]]])

# Calculating logical OR along the third dimension
I = np.any(I_2, axis=0)

# Printing the result
print(I)
print(I.shape)


# Input array of shape (501, 501, 8)
I_2 = np.random.choice([False, True], size=(501, 501, 8))

# Calculating logical OR along the third dimension
I = np.any(I_2, axis=2)

# Printing the shape of I before and after
print("Shape before:", I_2.shape)
print("Shape after:", I.shape)


# Getting the shape of the input array
rows, cols, depth = I_2.shape

# Creating the resulting array of shape (501, 501)
I_np = np.zeros((rows, cols), dtype=bool)
I_sci = np.zeros((rows, cols), dtype=bool)

# Calculating logical OR along the third dimension using a for loop
for i in range(depth):
    I_np = np.logical_or(I, I_2[:, :, i])
    I_sci = np.bitwise_or(I, I_2[:, :, i])




"""
[True, False, True],
    [True, False, True]
"""