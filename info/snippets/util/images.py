import numpy as np
import matplotlib.pyplot as plt

# Image size
image_size = (200, 200)

# Create a blank image with a red square in the top left
image_red = np.zeros((image_size[0], image_size[1], 3), dtype=np.uint8)
image_red[:100, :100, 0] = 255  # Set red channel to 255 (full intensity)

# Create a blank image with a green square in the bottom right
image_green = np.zeros((image_size[0], image_size[1], 3), dtype=np.uint8)
image_green[100:, 100:, 1] = 255  # Set green channel to 255 (full intensity)

# Create a blank image with a blue square in the middle
image_blue = np.zeros((image_size[0], image_size[1], 3), dtype=np.uint8)
image_blue[50:150, 50:150, 2] = 255  # Set blue channel to 255 (full intensity)

# Create a blank image to combine the individual images
combined_image = np.zeros((image_size[0] * 3, image_size[1], 3), dtype=np.uint8)

# Combine the images
combined_image[:image_size[0]] = image_red
combined_image[image_size[0]:image_size[0]*2] = image_green
combined_image[image_size[0]*2:] = image_blue

# Display the combined image
fig, ax = plt.subplots(figsize=(6, 12))
ax.imshow(combined_image)
ax.axis('off')
plt.show()
