## Tetris

## Team members
Andrew Sack

## Project description
This project aims to implement a game of tetris on the Raspberry Pi. It will 
utilize a ps2 keyboard for control and display the game on an HDMI monitor using
graphics built on top of the graphics library from past assignments. 

Short description of the basic idea and end goal you are aiming for. 
Include stretch goals and/or fallback position to indicate how you 
might fine-tune the project scope if needed.

## Hardware, budget
- HDMI Monitor and cable
- PS2 Keyboard and adapters

Nothing needs to be purchased. Everything can be borrowed from the CS107E lab. 

## Major tasks, member responsibilities
Major task breakdown and who is responsible for each tasks

- Graphics 
	+ Board Background
	+ Titles, Instructions, Score, etc
	+ Tetris Pieces
- Inputs
	+ Interrupt-driven keyboard key presses
		* Can also change to buttons on breadboard (still interrupt-driven)
	+ Start/Stop (Space/Enter)
	+ Move Left (Left Arrom)
	+ Move Right (Right Arrow)
	+ Rotate CW (W)
	+ Rotate CCW (Q)
	+ [Optional] Move Down (Down Arrow) 
- Main Game
	+ Start/Stop
	+ Display score
	+ Display Instructions/Messages
	+ Detect Game loss
	+ Detect and handle row elimination
	+ Interrupt Timer to move tetris block down
	+ [Optional] - Select Difficulty (change speed of down motion)
	+ [Optional] - High Score Board (wouldn't survive reboot)
- Tetromino(Tetris Blocks) 
	+ Randomly select block
	+ Move left & right, Rotate CW & CCW
	+ Detect when block hits other blocks
	+ Prevent moving out of bounds

## Schedule, midpoint milestones
# By March 9 (Lab)
- Overall project architecture complete
- Ability to add tetrominos to board and display board state
- Data structures for blocks, board, etc fully defined and mostly implemented

# By March 12
- Keyboard input
- Basic game functionality
	+ Move and rotate blocks
	+ Detect block landing
	+ Detect game loss
	+ Row elimination

# By March 15 (Demo Session)
- Score
- Instructions
- Extra graphic components
- Start/End states

# By March 16 (Code Submission)
All final code and documentation pushed to github


## Resources needed, issues
This project only needs the libpi libraries from past assignments. It builds on 
a lot of prior code (keyboard, graphics, etc), so this should be very achievable. 

The biggest risk is with the graphics. It needs to run fast enough that the 
user is not annoyed by the graphics refresh speed and bugs in graphics can be 
difficult to debug. 