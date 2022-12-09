/****************************************************************************
input.c

Module for responding to keyboard inputs

Andrew Sack
CS107E
3/13/22
****************************************************************************/

#include "input.h"
#include "keyboard.h"

/*
 * 'input_init'
 *
 * Init input module and underlying keyboard module
 *
 */
void input_init(void)
{
	keyboard_init(KEYBOARD_CLOCK, KEYBOARD_DATA);
}

/*
 * 'read_pregame_input'
 *
 * Read a single keyboard action and convert to valid tetris_input for pregame
 *
 * @return      enum val of input read 
 */
tetris_input_t read_pregame_input(void)
{
	key_action_t action = keyboard_read_sequence();

	// Only act on presses
	if (action.what == KEY_PRESS)
	{
		ps2_key_t key = ps2_keys[action.keycode];

		// Convert to tetris enum type
		switch (key.ch)
		{
			case '\n': 
				return ENTER_INPUT;
			case '1':
				return ONE_INPUT;
			case '2':
				return TWO_INPUT;
			case '3':
				return THREE_INPUT;
			default:
				return INVALID_INPUT;
		}
	}

	return INVALID_INPUT;
}

/*
 * 'read_game_input'
 *
 * Read a single keyboard action and convert to valid tetris_input for midgame
 *
 * @return      enum val of input read 
 */
tetris_input_t read_game_input(void)
{
	key_action_t action = keyboard_read_sequence();

	// Only act on presses
	if (action.what == KEY_PRESS)
	{
		ps2_key_t key = ps2_keys[action.keycode];

		// Convert to tetris enum type
		switch (key.ch)
		{
			case PS2_KEY_ARROW_LEFT:
				return LEFT_ARROW_INPUT;
			case PS2_KEY_ARROW_RIGHT:
				return RIGHT_ARROW_INPUT;
			case PS2_KEY_ARROW_UP:
				return UP_ARROW_INPUT;
			case PS2_KEY_ARROW_DOWN:
				return DOWN_ARROW_INPUT;
			case 'q':
				return Q_INPUT;
			case 'w':
				return W_INPUT;
			case PS2_KEY_ESC:
				return ESCAPE_INPUT;
			default:
				return INVALID_INPUT;
		}
	}

	return INVALID_INPUT;
}