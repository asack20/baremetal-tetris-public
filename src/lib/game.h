/****************************************************************************
game.h

Module that controls overall game initialization and flow

Andrew Sack
CS107E
3/9/22
****************************************************************************/

#ifndef GAME_H
#define GAME_H

/*
 * 'game_init'
 *
 * Init game module and all dependent modules
 *
 */
void game_init(void);

/*
 * 'game_run_pregame'
 *
 * Display intro UI and get difficulty
 *
 */
void game_run_pregame(void);

/*
 * 'game_run_game'
 *
 * Play the actual tetris game
 *
 */
void game_run_game(void);

/*
 * 'game_run_endgame'
 *
 * Display endscreen and wait for restart
 *
 */
void game_run_postgame(void);

#endif