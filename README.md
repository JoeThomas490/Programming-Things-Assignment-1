# Zumo Search Robot
## Programming Things Assignment 1
The first assignment for the Programming "Things" module in my final year.

This involved us programming a small Zumo robot with an arduino board, ultrasonic sensor and xBee communications board to navigate a maze of corridors and rooms, imitating a search and rescue robot. It must be able to autonomously navigate corridors, scan rooms and return back through the building by itself.

# Controls
## State
### Init
'p' - Starts robot after calibration process is over.
### Corridor
Spacebar  - Stops robot carrying on with corridor behaviour.

's'       - Stops robot carrying on with corridor behaviour.

'R'       - Notify the robot it's changing to room state.

'C'       - Notify the robot it's changing to corridor state.
### User
'w'       - Moves robot forward.

'a'       - Turns robot to the left slightly.

'd'       - Turns robot to the right slightly.

's'       - Either stops the robot (if moving forward) or puts it in reverse.

'9'       - Turns robot 90 degrees to the left.

'0'       - Turns robot 90 degrees to the right.

'C'       - Notify the robot it's changing to corridor state.

'R'       - Notify the robot it's changing to room state.

'l'       - Once notified of a state change, tells robot it's moving to the left.

'r'       - Once notified of a state change, tells robot it's moving to the right.

     
