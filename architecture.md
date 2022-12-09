- Board Module
	+ board_init
		* Specify dimensions of board
		* Init 2D array that keeps track of color of each tile. Make all black (no tile)
	+ board_insert_block
		* Take block struct and add to board array in correct locations
	+ board_draw_block
		* Take block struct and draw to monitor in correct location. Do not save
	+ board_draw_board
		* draws whole board from it's array
	+ block_check_collision
		* Takes a block struct and checks if it's position is valid with current board state
		
- Tetromino Module
	+ tetromino_init
		* Generate new random block at top of screen
	+ tetromino_move_left
	+ tetromino_move_right
	+ tetromino_rotate_cw
	+ tetromino_rotate_ccw
	+ tetromino_move_down
	+ tetromino_t
		* color_t color
		* bool[4][4] shape 
			- Bitmap that defines shape of tetromino
		* x_pos 
			- x-coord in board space of top left of shape 
		* y_pos 
			- y-coord in board space of top left of shape
- Input Module
	+ Interrupt Handler for each key
	+ Add to ring buffer for sequential processing
	
- Game Module
	+ game_init(difficulty)
		* Init board
	+ game run
		* inf loop until game over
		* Check for input
		* Check for time update
		* Update Screen
		

https://tetris.fandom.com/wiki/SRS
{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}}

Straight (Cyan) I
{{{0,0,0,0},
 {1,1,1,1},
 {0,0,0,0},
 {0,0,0,0}},

{{0,0,1,0},
 {0,0,1,0},
 {0,0,1,0},
 {0,0,1,0}},

{{0,0,0,0},
 {0,0,0,0},
 {1,1,1,1},
 {0,0,0,0}},

{{0,1,0,0},
 {0,1,0,0},
 {0,1,0,0},
 {0,1,0,0}}}

Block (Yellow) O
{{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}},
 
{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}}}

T-Shape (Purple) T
{{0,0,0,0},
 {0,1,0,0},
 {1,1,1,0},
 {0,0,0,0}}

Left L-Shape (Orange) L
{{0,0,0,0},
 {0,0,0,1},
 {0,1,1,1},
 {0,0,0,0}}

Right L-Shape (Blue) J
{{0,0,0,0},
 {1,0,0,0},
 {1,1,1,0},
 {0,0,0,0}}

Left Zig-Zag (Red) S
{{0,0,0,0},
 {1,1,0,0},
 {0,1,1,0},
 {0,0,0,0}}

Right Zig-Zag (Green) Z
{{0,0,0,0},
 {0,0,1,1},
 {0,1,1,0},
 {0,0,0,0}}

 const shape_t O_shape[4] = {
{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}},
{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}},
{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}},  
{{0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0}} 
};
