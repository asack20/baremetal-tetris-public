/****************************************************************************
startend.c

Module that draws start and end splash screens

Andrew Sack
CS107E
3/14/22
****************************************************************************/

#include "startend.h"
#include "gl.h"
#include "printf.h"

#define START_HEIGHT 16
#define START_WIDTH 32
#define CHAR_PX_HEIGHT 20
#define CHAR_PX_WIDTH 14
#define BG_COLOR GL_BLACK
#define TEXT_COLOR GL_WHITE
#define LOGO_BLOCK_SIZE 20

#define END_HEIGHT 20
#define END_WIDTH 32


// size of frame buf in pixels
#define START_PX_HEIGHT (START_HEIGHT * CHAR_PX_HEIGHT)
#define START_PX_WIDTH (START_WIDTH * CHAR_PX_WIDTH)
#define END_PX_HEIGHT (END_HEIGHT * CHAR_PX_HEIGHT)
#define END_PX_WIDTH (END_WIDTH * CHAR_PX_WIDTH)

// Function Prototypes
static void single_startscreen_draw(void);
static void single_draw_difficulty(int difficulty);
static void draw_logo(void);
static void draw_leaderboard(int score);

// Leaderboard Information
static const char *names[] = {"Pat   ","Julie ","Andrew","Liana ", "Maria ", "Anna  ", "Matt  ", "Jesse ", "RPi   "};
static const int scores[] = {1073, 300, 250, 200, 150, 100, 50, 25, 5}; 

/*
 * 'startscreen_init'
 *
 * Inits GL for start screen
 */
void startscreen_init(void)
{
	gl_init(START_PX_WIDTH, START_PX_HEIGHT, GL_DOUBLEBUFFER);

	// draw background
	gl_clear(BG_COLOR);
	gl_swap_buffer(); // swap and repeat for other buffer
	gl_clear(BG_COLOR);
}

/*
 * 'startscreen_draw'
 *
 * Draws start screen
 */
void startscreen_draw(void)
{
	single_startscreen_draw();
	gl_swap_buffer();
	single_startscreen_draw();
}

/*
 * 'startscreen_select_difficulty'
 *
 * Highlights selected difficulty on screen
 *
 * @param 	difficulty from 1-3
 */
void startscreen_select_difficulty(int difficulty)
{
	// Draw and swap
	single_draw_difficulty(difficulty);
	gl_swap_buffer();
	single_draw_difficulty(difficulty);
}

/*
 * 'single_startscreen_draw'
 *
 * Helper to draw to 1 frame buffer
 */
static void single_startscreen_draw(void)
{
	// line 1 (DRAW LOGO)
	draw_logo();
	// line 3
	gl_draw_string(0, 3*CHAR_PX_HEIGHT, "Select a Difficulty from 1-3", TEXT_COLOR);
	// line 4 (Difficulty Levels)
	single_draw_difficulty(1); // default
	// line 6
	gl_draw_string(0, 6*CHAR_PX_HEIGHT, "Press Enter to start the game", TEXT_COLOR);
	// line 8
	gl_draw_string(0, 8*CHAR_PX_HEIGHT, "Controls:", TEXT_COLOR);
	// line 9
	gl_draw_string(0, 9*CHAR_PX_HEIGHT, "Up    - Rotate Clockwise", TEXT_COLOR);
	// line 10
	gl_draw_string(0, 10*CHAR_PX_HEIGHT, "Down  - Move Down", TEXT_COLOR);
	// line 11
	gl_draw_string(0, 11*CHAR_PX_HEIGHT, "Left  - Move Left", TEXT_COLOR);
	// line 12
	gl_draw_string(0, 12*CHAR_PX_HEIGHT, "Right - Move Right", TEXT_COLOR);
	// line 13 
	gl_draw_string(0, 13*CHAR_PX_HEIGHT, "Q     - Rotate Counterclockwise", TEXT_COLOR);
	// line 14
	gl_draw_string(0, 14*CHAR_PX_HEIGHT, "W     - Rotate Clockwise", TEXT_COLOR);
	// line 15
	gl_draw_string(0, 15*CHAR_PX_HEIGHT, "Esc   - Quit", TEXT_COLOR);
}

/*
 * 'draw_logo'
 *
 * Helper to draw tetris logo
 */
static void draw_logo(void)
{
	int x_start = 164;
	// Draw Background
	gl_draw_rect(x_start+(0*LOGO_BLOCK_SIZE), 1*CHAR_PX_HEIGHT, LOGO_BLOCK_SIZE, LOGO_BLOCK_SIZE, GL_RED);
	gl_draw_rect(x_start+(1*LOGO_BLOCK_SIZE), 1*CHAR_PX_HEIGHT, LOGO_BLOCK_SIZE, LOGO_BLOCK_SIZE, GL_ORANGE);
	gl_draw_rect(x_start+(2*LOGO_BLOCK_SIZE), 1*CHAR_PX_HEIGHT, LOGO_BLOCK_SIZE, LOGO_BLOCK_SIZE, GL_YELLOW);
	gl_draw_rect(x_start+(3*LOGO_BLOCK_SIZE), 1*CHAR_PX_HEIGHT, LOGO_BLOCK_SIZE, LOGO_BLOCK_SIZE, GL_GREEN);
	gl_draw_rect(x_start+(4*LOGO_BLOCK_SIZE), 1*CHAR_PX_HEIGHT, LOGO_BLOCK_SIZE, LOGO_BLOCK_SIZE, GL_CYAN);
	gl_draw_rect(x_start+(5*LOGO_BLOCK_SIZE), 1*CHAR_PX_HEIGHT, LOGO_BLOCK_SIZE, LOGO_BLOCK_SIZE, GL_PURPLE);

	// Draw Text
	gl_draw_char(x_start+(0*LOGO_BLOCK_SIZE)+3, 1*CHAR_PX_HEIGHT+3, 'T', GL_WHITE);
	gl_draw_char(x_start+(1*LOGO_BLOCK_SIZE)+3, 1*CHAR_PX_HEIGHT+3, 'E', GL_WHITE);
	gl_draw_char(x_start+(2*LOGO_BLOCK_SIZE)+3, 1*CHAR_PX_HEIGHT+3, 'T', GL_WHITE);
	gl_draw_char(x_start+(3*LOGO_BLOCK_SIZE)+3, 1*CHAR_PX_HEIGHT+3, 'R', GL_WHITE);
	gl_draw_char(x_start+(4*LOGO_BLOCK_SIZE)+3, 1*CHAR_PX_HEIGHT+3, 'I', GL_WHITE);
	gl_draw_char(x_start+(5*LOGO_BLOCK_SIZE)+3, 1*CHAR_PX_HEIGHT+3, 'S', GL_WHITE);
}

/*
 * 'single_draw_difficulty'
 *
 * Helper to draw difficulty to 1 frame buffer
 */
static void single_draw_difficulty(int difficulty)
{
	color_t fg;
	color_t bg;

	// Draw 1
	if (difficulty == 1)
	{
		fg = BG_COLOR;
		bg = TEXT_COLOR;
	}
	else
	{
		fg = TEXT_COLOR;
		bg = BG_COLOR;
	} 
	gl_draw_rect(7*CHAR_PX_WIDTH-1, 4*CHAR_PX_HEIGHT-1, 16, 17, bg);
	gl_draw_char(7*CHAR_PX_WIDTH, 4*CHAR_PX_HEIGHT, '1', fg);

	// Draw 2
	if (difficulty == 2)
	{
		fg = BG_COLOR;
		bg = TEXT_COLOR;
	}
	else
	{
		fg = TEXT_COLOR;
		bg = BG_COLOR;
	} 
	gl_draw_rect(15*CHAR_PX_WIDTH-1, 4*CHAR_PX_HEIGHT-1, 16, 17, bg);
	gl_draw_char(15*CHAR_PX_WIDTH, 4*CHAR_PX_HEIGHT, '2', fg);

	// Draw 3
	if (difficulty == 3)
	{
		fg = BG_COLOR;
		bg = TEXT_COLOR;
	}
	else
	{
		fg = TEXT_COLOR;
		bg = BG_COLOR;
	} 
	gl_draw_rect(23*CHAR_PX_WIDTH-1, 4*CHAR_PX_HEIGHT-1, 16, 17, bg);
	gl_draw_char(23*CHAR_PX_WIDTH, 4*CHAR_PX_HEIGHT, '3', fg);
}

/*
 * 'endscreen_init'
 *
 * Inits GL for end screen
 */
void endscreen_init(void)
{
	gl_init(END_PX_WIDTH, END_PX_HEIGHT, GL_DOUBLEBUFFER);

	// draw background
	gl_clear(BG_COLOR);
	gl_swap_buffer(); // swap and repeat for other buffer
	gl_clear(BG_COLOR);
}

/*
 * 'endscreen_draw'
 *
 * Draws end screen with score sorted in leaderboard
 *
 * @param 	score to include in leaderboard 
 */
void endscreen_draw(int score)
{
	gl_clear(BG_COLOR);

	// line 1
	draw_logo();

	// line 3
	// GAME OVER
	gl_draw_string((END_PX_WIDTH/2)-(9*CHAR_PX_WIDTH/2), 3*CHAR_PX_HEIGHT, "GAME OVER", TEXT_COLOR);

	// line 4
	// Score: %d
	char score_str[20];
	snprintf(score_str, 20, "Score: %d", score); 
	gl_draw_string((END_PX_WIDTH/2)-(9*CHAR_PX_WIDTH/2), 4*CHAR_PX_HEIGHT, score_str, TEXT_COLOR);

	// line 6
	gl_draw_string(0, 6*CHAR_PX_HEIGHT, "Leaderboard", TEXT_COLOR);
	
	// Line 7
	gl_draw_string(0, 7*CHAR_PX_HEIGHT, "--------------", TEXT_COLOR);
	
	// Line 8-17
	draw_leaderboard(score);
	
	// Line 19
	gl_draw_string(0, 19*CHAR_PX_HEIGHT, "Press Enter to Play Again", TEXT_COLOR);

	gl_swap_buffer();
}

/*
 * 'draw_leaderboard'
 *
 * Draws leaderboard to endscreen with specified score inserted
 *
 * @param 	score to include in leaderboard 
 */
static void draw_leaderboard(int score)
{
	int bufsz = 20;
	char buf[bufsz];
	int display_num = 1;
	int idx = 0;
	int row_offset = 7; // rows from top to start leaderboard

	// Print all the scores higher than user
	while ((scores[idx] > score) && (idx < 9))
	{
		snprintf(buf, bufsz,"%02d %s %04d", display_num, names[idx], scores[idx]);
		gl_draw_string(0, (display_num+row_offset)*CHAR_PX_HEIGHT, buf, TEXT_COLOR);
		idx++;
		display_num++;
	}

	// Print user
	snprintf(buf, bufsz,"%02d %s %04d", display_num, "You   ", score);
	gl_draw_string(0, (display_num+row_offset)*CHAR_PX_HEIGHT, buf, TEXT_COLOR);
	display_num++;


	// print scores lower than user
	while(idx < 9)
	{
		snprintf(buf, bufsz,"%02d %s %04d", display_num, names[idx], scores[idx]);
		gl_draw_string(0, (display_num+row_offset)*CHAR_PX_HEIGHT, buf, TEXT_COLOR);
		idx++;
		display_num++;
	}
}