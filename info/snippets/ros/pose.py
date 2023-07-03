from geometry_msgs.msg import Pose
from tf.transformations import quaternion_from_euler
import math

def calculate_robot_pose(angle_degrees):
    # Convert the angle from degrees to radians
    angle_radians = math.radians(angle_degrees)

    # Calculate the quaternion representing the orientation
    quaternion = quaternion_from_euler(0, 0, angle_radians)

    # Create a Pose object
    pose = Pose()
    pose.orientation.x = quaternion[0]
    pose.orientation.y = quaternion[1]
    pose.orientation.z = quaternion[2]
    pose.orientation.w = quaternion[3]

    return pose

# Example usage:
angle_degrees = 45
robot_pose = calculate_robot_pose(angle_degrees)

# Access the quaternion components of the orientation
print("Quaternion (x, y, z, w):", robot_pose.orientation.x, robot_pose.orientation.y,
      robot_pose.orientation.z, robot_pose.orientation.w)
