from PIL import Image, ImageDraw

# Define the size of the image
image_size = (500, 500)

# Create a new black image
image = Image.new("RGB", image_size, "black")

# Define the colors of the circles
colors = ["red", "green", "blue", "yellow"]

# Define the size and positions of the circles
circle_size = 100
circle_positions = [
    (0, 0),
    (0, image_size[1] - circle_size),
    (image_size[0] - circle_size, 0),
    (image_size[0] - circle_size, image_size[1] - circle_size),
]

# Draw the circles on the image
draw = ImageDraw.Draw(image)
for i, pos in enumerate(circle_positions):
    draw.ellipse(pos + (pos[0] + circle_size, pos[1] + circle_size), fill="yellow")

# Divide the image into four rectangles
rectangles = [
    (0, 0, image_size[0] // 2, image_size[1] // 2),
    (0, image_size[1] // 2, image_size[0] // 2, image_size[1]),
    (image_size[0] // 2, 0, image_size[0], image_size[1] // 2),
    (image_size[0] // 2, image_size[1] // 2, image_size[0], image_size[1]),
]


# Crop the image into four sub-images
sub_images = [image.crop(rect) for rect in rectangles]

# Save the image
image.save("circles.png")