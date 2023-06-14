import numpy as np
import matplotlib.pyplot as plt

# Assuming your diagram is stored in the 'diagram' array
diagram = np.random.randint(0, 9, (501, 501))

plt.imshow(diagram, cmap='RdYlBu_r')
plt.colorbar()  # Add a colorbar for reference

plt.show()