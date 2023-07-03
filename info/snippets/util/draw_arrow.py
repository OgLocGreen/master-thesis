import math
import matplotlib.pyplot as plt

def draw_arrow(x, y, angle):
    arrow_length = 1  # Length of the arrow

    # Calculate the endpoint of the arrow
    arrow_end_x = x + arrow_length * math.cos(math.radians(angle))
    arrow_end_y = y + arrow_length * math.sin(math.radians(angle))

    # Create a figure and axes
    fig, ax = plt.subplots()

    # Plot the arrow
    ax.arrow(x, y, arrow_end_x - x, arrow_end_y - y, head_width=0.1, head_length=0.15, fc='blue', ec='blue')

    # Set the x and y axis limits
    ax.set_xlim([-2, 2])
    ax.set_ylim([-2, 2])

    # Set labels and title
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title('Arrow Visualization')

    # Display the plot
    plt.show()

# Example usage
draw_arrow(0, 0, 0)
draw_arrow(0, 0, 45)
draw_arrow(0, 0, 90)