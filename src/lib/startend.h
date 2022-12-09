/****************************************************************************
startend.h

Module that draws start and end splash screens

Andrew Sack
CS107E
3/14/22
****************************************************************************/

#ifndef STARTEND_H
#define STARTEND_H

/*
 * 'startscreen_init'
 *
 * Inits GL for start screen
 */
void startscreen_init(void);

/*
 * 'startscreen_draw'
 *
 * Draws start screen
 */
void startscreen_draw(void);

/*
 * 'startscreen_selectdifficulty'
 *
 * Highlights selected difficulty on screen
 */
void startscreen_select_difficulty(int difficulty);

/*
 * 'endscreen_init'
 *
 * Inits GL for end screen
 */
void endscreen_init(void);

/*
 * 'endscreen_draw'
 *
 * Draws end screen with score sorted in leaderboard
 *
 * @param 	score to include in leaderboard 
 */
void endscreen_draw(int score);


#endif