/****************************************************************************
input.h

Module for responding to keyboard inputs

Andrew Sack
CS107E
3/13/22
****************************************************************************/
#ifndef INPUT_H
#define INPUT_H

typedef enum {
    INVALID_INPUT = 0,
    LEFT_ARROW_INPUT,
    RIGHT_ARROW_INPUT,
    UP_ARROW_INPUT,
    DOWN_ARROW_INPUT,
    ENTER_INPUT,
    ONE_INPUT,
    TWO_INPUT,
    THREE_INPUT,
    Q_INPUT,
    W_INPUT,
    ESCAPE_INPUT
} tetris_input_t;

/*
 * 'input_init'
 *
 * Init input module and underlying keyboard module
 *
 */
void input_init(void);

/*
 * 'read_pregame_input'
 *
 * Read a single keyboard action and convert to valid tetris_input for pregame
 *
 * @return      enum val of input read 
 */
tetris_input_t read_pregame_input(void);

/*
 * 'read_game_input'
 *
 * Read a single keyboard action and convert to valid tetris_input for midgame
 *
 * @return      enum val of input read 
 */
tetris_input_t read_game_input(void);

#endif