/****************************************************************************
board.c

Module for the overall tetris game board

Andrew Sack
CS107E
3/9/22
****************************************************************************/
#include "gl.h"
#include "strings.h"
#include "tetromino.h"
#include "board.h"
#include "printf.h"
#include <stdbool.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define PX_PER_TILE 16
#define TEXT_ROWS 1 // Number of rows of text to put at bottom of screen
#define TEXT_PADDING 3 // Extra pixels per row of text
#define BG_COLOR 0xff001a00 // Very dark green
#define TEXT_BG_COLOR GL_SILVER
#define TEXT_COLOR GL_CAYENNE

#define TEXT_TOP BOARD_HEIGHT*PX_PER_TILE

// size of frame buf in pixels
#define PX_HEIGHT ((BOARD_HEIGHT+TEXT_ROWS)*PX_PER_TILE + (TEXT_ROWS*TEXT_PADDING))
#define PX_WIDTH (BOARD_WIDTH*PX_PER_TILE)

// macro functions
#define in_bounds(x,y) ((0 <= x) && (x < BOARD_WIDTH) && (0 <= y) && (y < BOARD_HEIGHT))

// Function Prototypes
static void single_draw_tetromino(tetromino_t piece);
static void single_clear_tetromino(tetromino_t piece);
static void single_draw_board(void);
static void copy_row(int dst_row, int src_row);
static bool board_row_full(int row);
static void clear_row(int row);
static void single_draw_score(const char* str);

static color_t board_grid[BOARD_HEIGHT][BOARD_WIDTH];

/*
 * 'board_init'
 *
 * Inits GL for size of board and text. Inits board_grid array
 */
void board_init(void)
{
	// initialize array to background color
	board_reset_board();

	gl_init(PX_WIDTH, PX_HEIGHT, GL_DOUBLEBUFFER);

	// draw board and text backgrounds
	gl_clear(BG_COLOR);
	gl_draw_rect(0, TEXT_TOP, PX_WIDTH, TEXT_ROWS*(PX_PER_TILE+TEXT_PADDING), TEXT_BG_COLOR);

	gl_swap_buffer(); // swap and repeat for other buffer

	gl_clear(BG_COLOR);
	gl_draw_rect(0, TEXT_TOP, PX_WIDTH, TEXT_ROWS*(PX_PER_TILE+TEXT_PADDING), TEXT_BG_COLOR);
}

/*
 * 'board_insert_tetromino'
 *
 * Adds tetromino piece to board grid array if it is in valid position.
 *
 * @param piece	tetromino_t to insert
 * @return   	true if insert was successful
 */
bool board_insert_tetromino(tetromino_t piece)
{
	// only insert if tetromino is in a valid position
	if (board_valid_tetromino_position(piece) != true)
	{
		return false;
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (piece.rots[piece.rotation][j][i] == 1)
			{
				// write color of the piece to the array
				board_grid[j+piece.y_pos][i+piece.x_pos] = piece.color;
			}
		}
	}
	return true;
}

/*
 * 'board_draw_tetromino'
 *
 * Draws tetromino to screen if it is in valid position. Does not insert 
 *
 * @param piece	tetromino_t to draw
 * @return   	true if draw was successful
 */
bool board_draw_tetromino(tetromino_t piece)
{
	// only draw if tetromino is in a valid position
	if (board_valid_tetromino_position(piece) != true)
	{
		return false;
	}

	// Helper to draw to both buffers
	single_draw_tetromino(piece);
	gl_swap_buffer();
	single_draw_tetromino(piece);

	return true;
}

/*
 * 'board_clear_tetromino'
 *
 * Draws over tetromino with bg color if it is in valid position. 
 *
 * @param piece	tetromino_t to clear
 * @return   	true if draw was successful
 */
bool board_clear_tetromino(tetromino_t piece)
{
	// only draw if tetromino is in a valid position
	if (board_valid_tetromino_position(piece) != true)
	{
		return false;
	}

	// Helper to draw to both buffers
	single_clear_tetromino(piece);
	gl_swap_buffer();
	single_clear_tetromino(piece);

	return true;
}

/*
 * 'board_draw_board'
 *
 * Reads board_grid array and draws whole board to screen
 *
 * @return   	true if draw was successful
 */
bool board_draw_board(void)
{
	// Helper to draw to both buffers
	single_draw_board();
	gl_swap_buffer();
	single_draw_board();

	return true;
}

/*
 * 'board_reset_board'
 *
 * Sets whole board_grid array to BG color
 *
 * @return   	true if successful
 */
bool board_reset_board(void)
{
	for (int i = 0; i < BOARD_HEIGHT*BOARD_WIDTH; i++)
		board_grid[i/BOARD_WIDTH][i%BOARD_WIDTH] = BG_COLOR;
	return true;
}

/*
 * 'board_valid_tetromino_position'
 *
 * Checks if tetromino is in valid position. 
 * (Fully inside board and not overlapping other tiles)
 *
 * @param piece	tetromino_t to check
 * @return   	true if position is valid
 */
bool board_valid_tetromino_position(tetromino_t piece)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			// tile in this position
			if (piece.rots[piece.rotation][j][i] == 1)
			{
				// check bounds of board
				if (!in_bounds((i+piece.x_pos), (j+piece.y_pos)))
				{
					return false;
				}
				// check collisions with other blocks (not background)
				if (board_grid[j+piece.y_pos][i+piece.x_pos] != BG_COLOR)
				{
					return false;
				}
			}
		}
	}
	return true; // if it makes it to end return true
}

/*
 * 'board_is_tetromino_docked'
 *
 * Checks if tetromino is in docked position. 
 * (Any tile of tetromino directly above bottom of board or other tile)
 *
 * @param piece	tetromino_t to check
 * @return   	true if docked
 */
bool board_is_tetromino_docked(tetromino_t piece)
{

	for (int j = 3; j >= 0; j--) // loop from bottom to top of tetromino
	{
		for (int i = 0; i < 4; i++)
		{
			// tile in this position
			if (piece.rots[piece.rotation][j][i] == 1)
			{
				// in bottom row
				if ((j + piece.y_pos) >= (BOARD_HEIGHT))
				{
					return true;
				}
				// non-background tile directly below piece
				if (board_grid[j+piece.y_pos+1][i+piece.x_pos] != BG_COLOR)
				{
					return true;
				}
			}
		}
	}
	return false; // if it makes it to end return false
}

/*
 * 'board_collapse_rows'
 *
 * Removes any full rows and shifts rows down to replace it
 *
 * @return   	number of rows collapsed
 */
int board_collapse_rows(void)
{
	int num_collapsed = 0;
	// init to last row
	int dst_row = BOARD_HEIGHT-1;
	
	// iterate bottom to top
	for (int src_row = dst_row; src_row >= 0; src_row--)
	{
		if (!board_row_full(src_row))
		{
			if (src_row != dst_row) // avoid unneccessary work
			{
				copy_row(dst_row, src_row);
			}
			dst_row--;
		}
		else // collapse
			num_collapsed++;
	}

	// clear remaining rows
	for(int row = dst_row; row >= 0; row--)
	{
		clear_row(row);
	}

	return num_collapsed;
}

/*
 * 'board_row_full'
 *
 * Checks if any tiles in specified row of board_grid are BG color
 *
 * @param row	row to check
 * @return   	true if row is full
 */
static bool board_row_full(int row)
{
	// invalid row, return false
	if ((row < 0) || (row >= BOARD_HEIGHT))
		return false;
	
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (board_grid[row][i] == BG_COLOR)
			return false;
	}

	return true;
}

/*
 * 'copy_row'
 *
 * Copies the contents of src_row in board_grid to dst_row
 *
 * @param src_row	row to copy from
 * @param dst_row	row to copy to
 */
static void copy_row(int dst_row, int src_row)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		board_grid[dst_row][i] = board_grid[src_row][i];
	}
}

/*
 * 'clear_row'
 *
 * Sets row in board_grid to all BG color
 *
 * @param row	row to clear
 */
static void clear_row(int row)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		board_grid[row][i] = BG_COLOR;
	}
}



/*
 * 'single_draw_tetromino'
 *
 * Helper function to draw to one buffer
 *
 * @param piece	tetromino_t to draw
 */
static void single_draw_tetromino(tetromino_t piece)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (piece.rots[piece.rotation][j][i] == 1)
				gl_draw_rect((i+piece.x_pos)*PX_PER_TILE, 
					(j+piece.y_pos)*PX_PER_TILE, PX_PER_TILE, PX_PER_TILE, 
					piece.color);
		}
	}
}

/*
 * 'single_clear_tetromino'
 *
 * Helper function to clear to one buffer
 *
 * @param piece	tetromino_t to draw
 */
static void single_clear_tetromino(tetromino_t piece)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (piece.rots[piece.rotation][j][i] == 1)
				gl_draw_rect((i+piece.x_pos)*PX_PER_TILE, 
					(j+piece.y_pos)*PX_PER_TILE, PX_PER_TILE, PX_PER_TILE, 
					BG_COLOR);
		}
	}
}

/*
 * 'single_draw_board'
 *
 * Helper function to draw board to one buffer
 *
 */
static void single_draw_board(void)
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			// draw based on color in board_grid
			gl_draw_rect((i*PX_PER_TILE), 
					(j*PX_PER_TILE), PX_PER_TILE, PX_PER_TILE, 
					board_grid[j][i]);
		}
	}
}

/*
 * 'board_draw_score'
 *
 * Draws the specified score to the screen in the text section
 *
 * @param   score to draw
 */
void board_draw_score(int score)
{
	char buf[20];

	snprintf(buf, 20, "Score: %d", score);

	single_draw_score(buf);
	gl_swap_buffer();
	single_draw_score(buf);
}

/*
 * 'single_draw_score'
 *
 * Helper function to draw score string to one buffer
 *
 * @param   string of score to draw
 */
static void single_draw_score(const char* str)
{
	// Background
	gl_draw_rect(0, TEXT_TOP, PX_WIDTH, TEXT_ROWS*PX_PER_TILE, TEXT_BG_COLOR);

	// Text
	gl_draw_string(0, TEXT_TOP+2, str, TEXT_COLOR);
}