/****************************************************************************
tetromino.c

Module to represent and manipulate a single tetromino

Andrew Sack
CS107E
3/9/22
****************************************************************************/
#include "tetromino.h"
#include "randomHardware.h"
#include "board.h"
#include <stdbool.h>

// Definition of Tetromino starter consts
const tetromino_t I_TETROMINO = {GL_CYAN, I_SHAPE_IDX,  0, 0, 0,
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
};

const tetromino_t O_TETROMINO = {GL_YELLOW, O_SHAPE_IDX,  0, 0, 0,
{{{0,1,1,0},
 {0,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,1,1,0},
 {0,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,1,1,0},
 {0,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},  

{{0,1,1,0},
 {0,1,1,0},
 {0,0,0,0},
 {0,0,0,0}}}
};

const tetromino_t T_TETROMINO = {GL_PURPLE, T_SHAPE_IDX,  0, 0, 0,
{{{0,1,0,0},
 {1,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,1,0,0},
 {0,1,1,0},
 {0,1,0,0},
 {0,0,0,0}},

{{0,0,0,0},
 {1,1,1,0},
 {0,1,0,0},
 {0,0,0,0}},  

{{0,1,0,0},
 {1,1,0,0},
 {0,1,0,0},
 {0,0,0,0}}}
};

const tetromino_t L_TETROMINO = {GL_ORANGE, L_SHAPE_IDX,  0, 0, 0,
{{{0,0,1,0},
 {1,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,1,0,0},
 {0,1,0,0},
 {0,1,1,0},
 {0,0,0,0}},

{{0,0,0,0},
 {1,1,1,0},
 {1,0,0,0},
 {0,0,0,0}},  

{{1,1,0,0},
 {0,1,0,0},
 {0,1,0,0},
 {0,0,0,0}}}
};

const tetromino_t J_TETROMINO = {GL_BLUE, J_SHAPE_IDX,  0, 0, 0,
{{{1,0,0,0},
 {1,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,1,1,0},
 {0,1,0,0},
 {0,1,0,0},
 {0,0,0,0}},

{{0,0,0,0},
 {1,1,1,0},
 {0,0,1,0},
 {0,0,0,0}},  

{{0,1,0,0},
 {0,1,0,0},
 {1,1,0,0},
 {0,0,0,0}}}
};

const tetromino_t S_TETROMINO = {GL_GREEN, S_SHAPE_IDX,  0, 0, 0,
{{{0,1,1,0},
 {1,1,0,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,1,0,0},
 {0,1,1,0},
 {0,0,1,0},
 {0,0,0,0}},

{{0,0,0,0},
 {0,1,1,0},
 {1,1,0,0},
 {0,0,0,0}},  

{{1,0,0,0},
 {1,1,0,0},
 {0,1,0,0},
 {0,0,0,0}}}
};

const tetromino_t Z_TETROMINO = {GL_RED, Z_SHAPE_IDX,  0, 0, 0,
{{{1,1,0,0},
 {0,1,1,0},
 {0,0,0,0},
 {0,0,0,0}},

{{0,0,1,0},
 {0,1,1,0},
 {0,1,0,0},
 {0,0,0,0}},

{{0,0,0,0},
 {1,1,0,0},
 {0,1,1,0},
 {0,0,0,0}},  

{{0,1,0,0},
 {1,1,0,0},
 {1,0,0,0},
 {0,0,0,0}}}
};

// Create list of pointers to tetromino consts
static const tetromino_t* TETROMINO_LIST[] = 
	{&I_TETROMINO, &O_TETROMINO, &T_TETROMINO, &L_TETROMINO, &J_TETROMINO, 
		&S_TETROMINO, &Z_TETROMINO};

static tetromino_t this_tetromino;
static bool first_init = true;

/*
 * 'tetromino_init'
 *
 * Randomly copies a starter tetromino to module variable
 *
 */
void tetromino_init(void)
{
	// This init will be called a lot. Only do this part 1st time
	if (first_init)
	{
		random_init();
		first_init = false;
	}
	
	unsigned int tetromino_idx = random_getNumber(6, 0); // max,min

	// copy starter tetromino to reset struct
	this_tetromino = get_starter_tetromino(tetromino_idx);

    // move x pos to center
    this_tetromino.x_pos = 4;

}

/*
 * 'tetromino_move_left'
 *
 * If able, moves x position of tetromino 1 tile left
 *
 * @return   true if position actually changed
 */
bool tetromino_move_left(void)
{
	// Create copy to test if new position is valid
	tetromino_t new_tetromino = this_tetromino;
	new_tetromino.x_pos -= 1;

	if (board_valid_tetromino_position(new_tetromino))
	{
		this_tetromino = new_tetromino;
		return true;
	}
	return false;
}

/*
 * 'tetromino_move_right'
 *
 * If able, moves x position of tetromino 1 tile right
 *
 * @return   true if position actually changed
 */
bool tetromino_move_right(void)
{
	// Create copy to test if new position is valid
	tetromino_t new_tetromino = this_tetromino;
	new_tetromino.x_pos += 1;

	if (board_valid_tetromino_position(new_tetromino))
	{
		this_tetromino = new_tetromino;
		return true;
	}
	return false;
}

/*
 * 'tetromino_rotate_cw'
 *
 * If able, rotates tetromino clockwise by 90 degrees
 *
 * @return   true if position actually changed
 */
bool tetromino_rotate_cw(void)
{
	// Create copy to test if new position is valid
	tetromino_t new_tetromino = this_tetromino;
	new_tetromino.rotation = (new_tetromino.rotation + 1) %4;

	if (board_valid_tetromino_position(new_tetromino))
	{
		this_tetromino = new_tetromino;
		return true;
	}
	return false;
}

/*
 * 'tetromino_rotate_ccw'
 *
 * If able, rotates tetromino counterclockwise by 90 degrees
 *
 * @return   true if position actually changed
 */
bool tetromino_rotate_ccw(void)
{
	// Create copy to test if new position is valid
	tetromino_t new_tetromino = this_tetromino;
	// +4 ensures always positive so mod works correct
	new_tetromino.rotation = (new_tetromino.rotation - 1 + 4) %4;

	if (board_valid_tetromino_position(new_tetromino))
	{
		this_tetromino = new_tetromino;
		return true;
	}
	return false;
}

/*
 * 'tetromino_move_down'
 *
 * If able, moves y position of tetromino 1 tile down
 *
 * @return   true if position actually changed
 */
bool tetromino_move_down(void)
{
	// Create copy to test if new position is valid
	tetromino_t new_tetromino = this_tetromino;
	new_tetromino.y_pos += 1;

	if (board_valid_tetromino_position(new_tetromino))
	{
		this_tetromino = new_tetromino;
		return true;
	}
	return false;
}

/*
 * 'get_starter_tetromino'
 *
 * Returns copy of const tetromino struct for specified shape
 *
 * @param idx	enum corresponding to order of shapes in TETROMINO_LIST 
 * @return   	tetromino_t struct for specified shape
 */
tetromino_t get_starter_tetromino(shape_idx_t idx)
{
	tetromino_t piece = *TETROMINO_LIST[idx];
	return piece;
}

/*
 * 'get_tetromino'
 *
 * Returns current value of module's this_tetromino
 *
 * @return   	tetromino_t struct 
 */
tetromino_t get_tetromino(void)
{
	return this_tetromino;
}

/*
 * 'set_tetromino'
 *
 * FOR TESTING ONLY: overwrites random init with specified shape.
 *
 * @param idx	enum corresponding to order of shapes in TETROMINO_LIST 
 */
void set_tetromino(shape_idx_t idx)
{
	this_tetromino = *TETROMINO_LIST[idx];
}

/*
 * 'tetromino_draw_tetromino'
 *
 * Wrapper to call board_draw_tetromino on this_tetromino
 *
 * @return   return val of board_draw_tetromino
 */
bool tetromino_draw_tetromino(void)
{
	return board_draw_tetromino(this_tetromino);
}

/*
 * 'tetromino_clear_tetromino'
 *
 * Wrapper to call board_clear_tetromino on this_tetromino
 *
 * @return   return val of board_clear_tetromino
 */
bool tetromino_clear_tetromino(void)
{
	return board_clear_tetromino(this_tetromino);
}

/*
 * 'tetromino_insert_tetromino'
 *
 * Wrapper to call board_insert_tetromino on this_tetromino
 *
 * @return   return val of board_insert_tetromino
 */
bool tetromino_insert_tetromino(void)
{
	return board_insert_tetromino(this_tetromino);
}

/*
 * 'tetromino_is_tetromino_docked'
 *
 * Wrapper to call board_is_tetromino_docked on this_tetromino
 *
 * @return   return val of board_is_tetromino_docked
 */
bool tetromino_is_tetromino_docked(void)
{
    return board_is_tetromino_docked(this_tetromino);
}