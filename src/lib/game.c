/****************************************************************************
game.c

Module that controls overall game initialization and flow

Andrew Sack
CS107E
3/9/22
****************************************************************************/

#include "game.h"
#include "printf.h"
#include "interrupts.h"
#include "board.h"
#include "timer.h"
#include "input.h"
#include "tetromino.h"
#include "armtimer.h"
#include "startend.h"

// Down speeds for each difficulty
#define SPEED_1 1000000
#define SPEED_2 500000
#define SPEED_3 200000

void down_timer_handler(unsigned int pc, void *unused);

static unsigned int game_speed;
static int score;
static int level;
volatile bool down_interrupt; // used by interrupt


/*
 * 'game_init'
 *
 * Init game module and all dependent modules
 *
 */
void game_init(void)
{
  	// init dependent modules
	input_init();

    // Arm Timer Init
    armtimer_init(game_speed); // 1s
    // Do not enable yet
    armtimer_enable_interrupts();
    interrupts_register_handler(INTERRUPTS_BASIC_ARM_TIMER_IRQ, down_timer_handler, NULL);
    interrupts_enable_source(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
}

/*
 * 'game_run_pregame'
 *
 * Display intro UI and get difficulty
 *
 */
void game_run_pregame(void)
{
	// reset static vars to defaults
	game_speed = SPEED_1; // default
	score = 0;
	down_interrupt = false;

	// Init and draw start screen
	startscreen_init();
	startscreen_draw();	

	printf("Press 1,2,3 to select difficulty. Press Enter to begin\n");

    tetris_input_t input;

    do {
        input = read_pregame_input();
        
        if (input == ONE_INPUT)
        {
        	game_speed = SPEED_1;
        	level = 1;
        	startscreen_select_difficulty(level);
        	printf("Difficulty 1 selected\n");
        }
        else if (input == TWO_INPUT)
        {
        	game_speed = SPEED_2;
        	level = 2;
        	startscreen_select_difficulty(level);
        	printf("Difficulty 2 selected\n");
        }
        else if (input == THREE_INPUT)
        {
        	game_speed = SPEED_3;
        	level = 3;
        	startscreen_select_difficulty(level);
        	printf("Difficulty 3 selected\n");
        }

    } while(input != ENTER_INPUT);

    printf("Starting Game\n");
}

/*
 * 'game_run_game'
 *
 * Play the actual tetris game
 *
 */
void game_run_game(void)
{
	// Board Set up
	board_init();
	board_reset_board();
	board_draw_board();

	// init timer
	armtimer_init(game_speed); 
	armtimer_enable(); 
	armtimer_enable_interrupts();
	down_interrupt = false; // reset 

	printf("Starting Game\n");

    tetromino_init();
    tetromino_draw_tetromino();
    board_draw_score(score);

    tetris_input_t input;
    bool screen_changed;
    bool keep_playing = true;
    tetromino_t old_tetromino;

    while (keep_playing)
    {
        screen_changed = false;
        
        // respond to interrupt if one occurred
        if (down_interrupt)
        {
        	old_tetromino = get_tetromino();
        	screen_changed = tetromino_move_down();
        	down_interrupt = false;
        }

        else // respond to key presses
        {

	       	input = read_game_input();

	        old_tetromino = get_tetromino();

	        switch (input)
	        {
	            case INVALID_INPUT:
	            	break;
	            case LEFT_ARROW_INPUT:
	                screen_changed = tetromino_move_left();
	                break;

	            case RIGHT_ARROW_INPUT:
	                screen_changed = tetromino_move_right();
	                break;

	            case DOWN_ARROW_INPUT:
	                screen_changed = tetromino_move_down();
	                break;

	            case UP_ARROW_INPUT:
	                screen_changed = tetromino_rotate_cw();
	                break;

	            case Q_INPUT:
	                screen_changed = tetromino_rotate_ccw();
	                break;

	            case W_INPUT:
	                screen_changed = tetromino_rotate_cw();
	                break;

	            case ESCAPE_INPUT:
	                keep_playing = false;
	                break;
	            default:
	                break;
        	}
        }
        // if can't move down, insert to board and start new tetromino
        if (tetromino_is_tetromino_docked())
        {
            tetromino_insert_tetromino();
            int num_rows = board_collapse_rows();
            score += (num_rows*num_rows*level); // square to get score
            board_draw_board();
            board_draw_score(score);
            tetromino_init();
            // Fail state is tetromino fails to spawn
            keep_playing = tetromino_draw_tetromino();
        }

        else if (screen_changed)
        {
            board_clear_tetromino(old_tetromino);
            tetromino_draw_tetromino();
        }

    }
    armtimer_disable(); // disable on exit
}

/*
 * 'game_run_postgame'
 *
 * Display endscreen and wait for restart
 *
 */
void game_run_postgame(void)
{
	printf("Game Over. Score: %d\n", score);

	endscreen_init();
	endscreen_draw(score);

	tetris_input_t input;
	
	// Wait for Enter
	do {
        input = read_pregame_input();
    } while(input != ENTER_INPUT);
}

/*
 * 'down_timer_handler'
 *
 * interrupt handler for timer that moves tetrominos down
 *
 */
void down_timer_handler(unsigned int pc, void *unused)
{
    if (armtimer_check_and_clear_interrupt()) {
        down_interrupt = true;
    }
}
