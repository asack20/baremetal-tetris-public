/****************************************************************************
board.h

Module for the overall tetris game board

Andrew Sack
CS107E
3/9/22
****************************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "tetromino.h"

/*
 * 'board_init'
 *
 * Inits GL for size of board and text. Inits board_grid array
 */
void board_init(void);

/*
 * 'board_insert_tetromino'
 *
 * Adds tetromino piece to board grid array if it is in valid position.
 *
 * @param piece	tetromino_t to insert
 * @return   	true if insert was successful
 */
bool board_insert_tetromino(tetromino_t piece);

/*
 * 'board_draw_tetromino'
 *
 * Draws tetromino to screen if it is in valid position. Does not insert 
 *
 * @param piece	tetromino_t to draw
 * @return   	true if draw was successful
 */
bool board_draw_tetromino(tetromino_t piece);

/*
 * 'board_clear_tetromino'
 *
 * Draws over tetromino with bg color if it is in valid position. 
 *
 * @param piece	tetromino_t to clear
 * @return   	true if draw was successful
 */
bool board_clear_tetromino(tetromino_t piece);

/*
 * 'board_draw_board'
 *
 * Reads board_grid array and draws whole board to screen
 *
 * @return   	true if draw was successful
 */
bool board_draw_board(void);

/*
 * 'board_reset_board'
 *
 * Sets whole board_grid array to BG color
 *
 * @return   	true if successful
 */
bool board_reset_board(void);

/*
 * 'board_valid_tetromino_position'
 *
 * Checks if tetromino is in valid position. 
 * (Fully inside board and not overlapping other tiles)
 *
 * @param piece	tetromino_t to check
 * @return   	true if position is valid
 */
bool board_valid_tetromino_position(tetromino_t piece);

/*
 * 'board_is_tetromino_docked'
 *
 * Checks if tetromino is in docked position. 
 * (Any tile of tetromino directly above bottom of board or other tile)
 *
 * @param piece	tetromino_t to check
 * @return   	true if docked
 */
bool board_is_tetromino_docked(tetromino_t piece);

/*
 * 'board_collapse_rows'
 *
 * Removes any full rows and shifts rows down to replace it
 *
 * @return   	number of rows collapsed
 */
int board_collapse_rows(void);

/*
 * 'board_draw_score'
 *
 * Draws the specified score to the screen in the text section
 *
 * @param   score to draw
 */
void board_draw_score(int score);



#endif