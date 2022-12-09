/****************************************************************************
tetromino.h

Module to represent and manipulate a single tetromino

Andrew Sack
CS107E
3/9/22
****************************************************************************/

#ifndef TETROMINO_H
#define TETROMINO_H

#include "gl.h" // for color
#include <stdbool.h>

typedef char shape_t[4][4];

typedef enum {
    I_SHAPE_IDX = 0,
    O_SHAPE_IDX = 1,
    T_SHAPE_IDX  = 2,
    L_SHAPE_IDX  = 3,
    J_SHAPE_IDX  = 4,
    S_SHAPE_IDX  = 5,
    Z_SHAPE_IDX  = 6
}shape_idx_t;

typedef struct{
    color_t color;
    shape_idx_t shape_idx;
    int rotation;
    int x_pos;
    int y_pos;
    shape_t rots[4];
} tetromino_t;

/*
 * 'tetromino_init'
 *
 * Randomly copies a starter tetromino to module variable
 *
 */
void tetromino_init(void);

/*
 * 'tetromino_move_left'
 *
 * If able, moves x position of tetromino 1 tile left
 *
 * @return   true if position actually changed
 */
bool tetromino_move_left(void);

/*
 * 'tetromino_move_right'
 *
 * If able, moves x position of tetromino 1 tile right
 *
 * @return   true if position actually changed
 */
bool tetromino_move_right(void);

/*
 * 'tetromino_rotate_cw'
 *
 * If able, rotates tetromino clockwise by 90 degrees
 *
 * @return   true if position actually changed
 */
bool tetromino_rotate_cw(void);

/*
 * 'tetromino_rotate_ccw'
 *
 * If able, rotates tetromino counterclockwise by 90 degrees
 *
 * @return   true if position actually changed
 */
bool tetromino_rotate_ccw(void);

/*
 * 'tetromino_move_down'
 *
 * If able, moves y position of tetromino 1 tile down
 *
 * @return   true if position actually changed
 */
bool tetromino_move_down(void);

/*
 * 'get_starter_tetromino'
 *
 * Returns copy of const tetromino struct for specified shape
 *
 * @param idx   enum corresponding to order of shapes in TETROMINO_LIST 
 * @return      tetromino_t struct for specified shape
 */
tetromino_t get_starter_tetromino(shape_idx_t idx);

/*
 * 'get_tetromino'
 *
 * Returns current value of module's this_tetromino
 *
 * @return      tetromino_t struct 
 */
tetromino_t get_tetromino(void);

/*
 * 'set_tetromino'
 *
 * FOR TESTING ONLY: overwrites random init with specified shape.
 *
 * @param idx   enum corresponding to order of shapes in TETROMINO_LIST 
 */
void set_tetromino(shape_idx_t idx);

/*
 * 'tetromino_draw_tetromino'
 *
 * Wrapper to call board_draw_tetromino on this_tetromino
 *
 * @return   return val of board_draw_tetromino
 */
bool tetromino_draw_tetromino(void);

/*
 * 'tetromino_clear_tetromino'
 *
 * Wrapper to call board_clear_tetromino on this_tetromino
 *
 * @return   return val of board_clear_tetromino
 */
bool tetromino_clear_tetromino(void);

/*
 * 'tetromino_insert_tetromino'
 *
 * Wrapper to call board_insert_tetromino on this_tetromino
 *
 * @return   return val of board_insert_tetromino
 */
bool tetromino_insert_tetromino(void);

/*
 * 'tetromino_is_tetromino_docked'
 *
 * Wrapper to call board_is_tetromino_docked on this_tetromino
 *
 * @return   return val of board_is_tetromino_docked
 */
bool tetromino_is_tetromino_docked(void);

#endif