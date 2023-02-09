import numpy as np


    # Define the maze environment
maze = np.array([
  [0, 0, 0, 0, 1],
  [0, 1, 0, 0, 0],
  [0, 1, 0, 1, 0],
  [0, 0, 0, 1, 0],
  [0, 1, 0, 0, 0],
])

# Define the starting position
start = (0, 0)

# Define the actions and their effects
actions = {
  "up": (-1, 0),
  "down": (1, 0),
  "left": (0, -1),
  "right": (0, 1),
}


def reset_environment():
  return start

def take_action(state, action):
  x, y = state
  action = list(actions.keys())[action]
  dx, dy = actions[action]
  new_x, new_y = x + dx, y + dy
  
  # Check if the new position is within the maze and not a wall
  if 0 <= new_x < maze.shape[0] and 0 <= new_y < maze.shape[1] and maze[new_x, new_y] == 0:
    new_state = (new_x, new_y)
    reward = -1
    done = False
  else:
    new_state = state
    reward = -10
    done = False
  
  # Check if the new position is the goal
  if new_state == (maze.shape[0] - 1, maze.shape[1] - 1):
    reward = 100
    done = True
  
  return new_state, reward, done

# Define the environment
n_states = 100
n_actions = 4

# Initialize the Q-table with zeros
Q = np.zeros((n_states, n_actions))

# Define the learning rate, discount factor, and exploration rate
alpha = 0.1
gamma = 0.9
epsilon = 0.3

# Start the episode loop
for episode in range(1000):
  
  # Reset the environment and get the initial state
  current_state = reset_environment()
  done = False

  # Start the step loop
  while not done:
    
    # Choose an action based on the current state and exploration rate
    if np.random.uniform(0, 1) < epsilon:
      action = np.random.choice(n_actions)
    else:
      action = np.argmax(Q[current_state])
    
    # Take the action and observe the new state, reward, and if the episode is done
    new_state, reward, done = take_action(current_state, action)
    
    # Update the Q-table using the Q-learning rule
    Q[current_state, action] = (1 - alpha) * Q[current_state, action] + alpha * (reward + gamma * np.max(Q[new_state, :]))
    
    # Update the current state
    current_state = new_state


