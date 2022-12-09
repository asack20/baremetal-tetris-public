/****************************************************************************
tetris-tests.c

Unit Tests for tetris game

Andrew Sack
CS107E
3/9/22
****************************************************************************/

#include "printf.h"
#include "uart.h"
#include "tetromino.h"
#include "board.h"
#include "timer.h"
#include "input.h"
#include "interrupts.h"
#include "startend.h"

#define TEST_DELAY 500 // ms pause between tests

/*
 * Print tetromino struct to terminal with ascii version of piece
 */
void print_tetromino(tetromino_t piece)
{
    printf("type: %d, color: %x, rotation %d, x_pos: %d, y_pos: %d\n\n", 
        piece.shape_idx, piece.color, piece.rotation, piece.x_pos, piece.y_pos);

    for (int r = 0; r < 4; r++)
    {
        for(int y = 0; y <4; y++)
        {
            for (int x = 0; x<4; x++)
            {
                if (piece.rots[r][y][x] == 1)
                {
                    printf("X");
                }
                else 
                {
                    printf(".");
                }
            }
            printf("\n");
        }
        printf("\n----\n");    
    }
}


/*
 * Test printing of tetrominos to verify constants are accurate
 */
void test_tetromino_pieces(void)
{
    printf("Printing Starter Tetromino Details\n");

    print_tetromino(get_starter_tetromino(I_SHAPE_IDX));
    print_tetromino(get_starter_tetromino(O_SHAPE_IDX));
    print_tetromino(get_starter_tetromino(T_SHAPE_IDX));
    print_tetromino(get_starter_tetromino(L_SHAPE_IDX));
    print_tetromino(get_starter_tetromino(J_SHAPE_IDX));
    print_tetromino(get_starter_tetromino(S_SHAPE_IDX));
    print_tetromino(get_starter_tetromino(Z_SHAPE_IDX));
}

/* Draw tetrominos in various locations on screen with rotations
*/
void test_draw_tetromino(void)
{
    
    printf("Drawing I and T Tetrominos to screen \n");
    tetromino_t I_piece = get_starter_tetromino(I_SHAPE_IDX);
    board_draw_tetromino(I_piece);

    // Move and rotate
    I_piece.x_pos = 5;
    I_piece.y_pos = 5;
    I_piece.rotation = 1;

    board_draw_tetromino(I_piece);

    tetromino_t T_piece = get_starter_tetromino(T_SHAPE_IDX);
    // Move and rotate
    T_piece.x_pos = 6;
    board_draw_tetromino(T_piece);

    timer_delay_ms(TEST_DELAY);
}

/* Methodically Draw all tetrominos and rotations to screen
*/
void test_draw_all_tetromino(void)
{
    printf("Drawing all tetromino rotations to screen \n");
    for (int i = 0; i < 7; i++)
    {
        // Go through every rotation and draw
        tetromino_t piece = get_starter_tetromino(i);
        
        piece.x_pos = 0;
        piece.y_pos = 0;
        piece.rotation = 0;
        board_draw_tetromino(piece); 
        
        piece.x_pos = 5;
        piece.y_pos = 0;
        piece.rotation = 1;
        board_draw_tetromino(piece);

        piece.x_pos = 0;
        piece.y_pos = 5;
        piece.rotation = 2;
        board_draw_tetromino(piece);

        piece.x_pos = 5;
        piece.y_pos = 5;
        piece.rotation = 3;
        board_draw_tetromino(piece);
        timer_delay_ms(TEST_DELAY);

        // now clear tetrominos
        piece.x_pos = 0;
        piece.y_pos = 0;
        piece.rotation = 0;
        board_clear_tetromino(piece); 
        
        piece.x_pos = 5;
        piece.y_pos = 0;
        piece.rotation = 1;
        board_clear_tetromino(piece);

        piece.x_pos = 0;
        piece.y_pos = 5;
        piece.rotation = 2;
        board_clear_tetromino(piece);

        piece.x_pos = 5;
        piece.y_pos = 5;
        piece.rotation = 3;
        board_clear_tetromino(piece);

        timer_delay_ms(TEST_DELAY);
    }
}

/* Init and draw 5 random tetrominos
*/
void test_random_tetromino(void)
{
    printf("Drawing 5 random tetrominos\n");
    for (int i = 0; i < 5; i++)
    {
        tetromino_init();
        tetromino_t piece = get_tetromino();

        board_draw_tetromino(piece);

        timer_delay_ms(TEST_DELAY);
        board_clear_tetromino(piece);
        timer_delay_ms(TEST_DELAY);
    }
}

/* Does a series of moves and draws of tetromino
*/
void test_move_tetromino(void)
{
    board_init();
    tetromino_init();

    // move to right edge of screen
    printf("Moving to right edge\n");
    while(tetromino_move_right())
    {
        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();
    }


    // move back to left edge
    printf("Moving to left edge\n");
    while(tetromino_move_left())
    {
        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();
    }

    printf("Moving 2 down and 2 right\n");
    tetromino_move_down();
    tetromino_move_down();
    tetromino_move_right();
    tetromino_move_right();

    tetromino_draw_tetromino();
    timer_delay_ms(TEST_DELAY);
    tetromino_clear_tetromino();

    printf("Rotate clockwise 4 times\n");
    for (int i = 0; i < 4; i++)
    {
        tetromino_rotate_cw();
        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();
    }

    printf("Rotate counterclockwise 5 times\n");
    for (int i = 0; i < 5; i++)
    {
        tetromino_rotate_ccw();
        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();
    }

    printf("Moving to bottom of board\n");
    while(tetromino_move_down())
    {
        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();
    }

}

/* test inserting into board grid array and drawing whole grid
*/
void test_insert_tetromino(void)
{
    board_init();
    printf("Drawing Empty Board\n");
    board_draw_board();
    timer_delay_ms(TEST_DELAY);

    // Fill entire board with I pieces
    tetromino_t piece = get_starter_tetromino(I_SHAPE_IDX);
    piece.rotation = 1;
    int base_x = -2;
    // Fill with I pieces
    for (int j = 0; j < 20; j+=4)
    {
        for (int i = 0; i < 10; i++)
        {
            piece.x_pos = i + base_x;
            piece.y_pos = j;
            board_insert_tetromino(piece);
        }
    }

    printf("Board should be filled with Cyan\n");
    board_draw_board();
    timer_delay_ms(TEST_DELAY);

    printf("Reseting. Drawing Empty Board\n");
    board_reset_board();
    board_draw_board();
    timer_delay_ms(TEST_DELAY);

    // Fill entire board with L pieces
    piece = get_starter_tetromino(L_SHAPE_IDX);
    // Fill with L pieces
    for (int j = 0; j < 20; j+=2)
    {
        for (int i = 0; i < 10; i+=3)
        {
            piece.x_pos = i;
            piece.y_pos = j;
            board_insert_tetromino(piece);
        }
    }

    printf("Board should be filled with Orange L pieces\n");
    board_draw_board();
    timer_delay_ms(TEST_DELAY);
}

// Tests moving tetrominos and inserting on top of each other
void test_move_insert(void)
{
    board_init();
    tetromino_init();
    
    // Stack 3 I's vertically on far left of screen
    printf("Stacking 3 I's vertically on far left \n");
    for (int i = 0; i < 3; i++)
    {
        set_tetromino(I_SHAPE_IDX); // override init
        tetromino_rotate_ccw();
        tetromino_move_left();

        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();

        while(tetromino_move_down())
        {
            tetromino_draw_tetromino();
            timer_delay_ms(TEST_DELAY);
            tetromino_clear_tetromino();
        }
        tetromino_insert_tetromino();
        board_draw_board();
        timer_delay_ms(TEST_DELAY);
    }

    // Stack L's nested
    printf("Stacking 10 L's alternating orientation\n");
    for (int i = 0; i < 5; i++)
    {
        set_tetromino(L_SHAPE_IDX); // override init
        tetromino_move_right();

        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();

        while(tetromino_move_down())
        {
            tetromino_draw_tetromino();
            timer_delay_ms(TEST_DELAY);
            tetromino_clear_tetromino();
        }
        tetromino_insert_tetromino();
        board_draw_board();
        timer_delay_ms(TEST_DELAY);

        // repeat for upside down L
        set_tetromino(L_SHAPE_IDX); // override init
        tetromino_move_right();
        tetromino_rotate_cw();
        tetromino_rotate_cw();

        tetromino_draw_tetromino();
        timer_delay_ms(TEST_DELAY);
        tetromino_clear_tetromino();

        while(tetromino_move_down())
        {
            tetromino_draw_tetromino();
            timer_delay_ms(TEST_DELAY);
            tetromino_clear_tetromino();
        }
        tetromino_insert_tetromino();
        board_draw_board();
        timer_delay_ms(TEST_DELAY);
    }
}

// test collapsing rows in board grid
void test_collapse_rows(void)
{
    printf("Testing collapse rows\n");
    // Empty board
    board_init();
    board_collapse_rows();

    printf("Board Should be empty\n");
    board_draw_board();
    timer_delay_ms(3*TEST_DELAY);

    // Fill entire board with I pieces and then clear all
    tetromino_t piece = get_starter_tetromino(I_SHAPE_IDX);
    piece.rotation = 1;
    int base_x = -2;
    // Fill with I pieces
    for (int j = 0; j < 20; j+=4)
    {
        for (int i = 0; i < 10; i++)
        {
            piece.x_pos = i + base_x;
            piece.y_pos = j;
            board_insert_tetromino(piece);
        }
    }

    printf("Board Should be full CYAN\n");
    board_draw_board();
    timer_delay_ms(3*TEST_DELAY);
    
    printf("Board Should be empty\n");
    board_collapse_rows();
    board_draw_board();
    timer_delay_ms(3*TEST_DELAY);

    /* Test partial board collapse */
    // Add T pieces to bottom of screen
    tetromino_t t_piece = get_starter_tetromino(T_SHAPE_IDX);
    t_piece.y_pos = 18;

    for(int i = 0; i <= 6 ; i+=3)
    {
        t_piece.x_pos = i;
        board_insert_tetromino(t_piece);
    }

    // fill row with O pieces
    tetromino_t o_piece = get_starter_tetromino(O_SHAPE_IDX);
    o_piece.y_pos = 16;

    for(int i = -1; i < 10; i+=2)
    {
        o_piece.x_pos = i;
        board_insert_tetromino(o_piece);
    }

    // Add T pieces above
    t_piece.y_pos = 14;

    for(int i = 0; i <= 6 ; i+=3)
    {
        t_piece.x_pos = i;
        board_insert_tetromino(t_piece);
    }

    // fill row with O pieces
    o_piece.y_pos = 12;

    for(int i = -1; i < 10; i+=2)
    {
        o_piece.x_pos = i;
        board_insert_tetromino(o_piece);
    }

    // Add T pieces above
    t_piece.y_pos = 10;

    for(int i = 0; i <= 6 ; i+=3)
    {
        t_piece.x_pos = i;
        board_insert_tetromino(t_piece);
    }

    printf("Board has layers of T and O pieces\n");
    board_draw_board();
    timer_delay_ms(5*TEST_DELAY);
    
    printf("Board should only have T pieces and no gaps\n");
    board_collapse_rows();
    board_draw_board();
    timer_delay_ms(3*TEST_DELAY);
}

/* Test Keyboard input for the valid keys for pregame
*/
void test_pregame_input(void)
{
    printf("Testing Pregame Input Keys. Press 1,2,3. Press Enter to move on\n");

    input_init();

    tetris_input_t input;

    while (1)
    {
        input = read_pregame_input();
        if (input != INVALID_INPUT)
        {
            printf("Input Enum val: %d\n", input);
        }
        if (input == ENTER_INPUT)
        {
            printf("Enter pressed\n");
            return;
        }
    }
}

/* Test Keyboard input for the valid keys for during game
*/
void test_game_input(void)
{
    printf("Testing Mid Game Input Keys. Press Arrow Keys, Q, W. Press Esc to move on\n");

    input_init();

    tetris_input_t input;

    while (1)
    {
        input = read_game_input();
        if (input != INVALID_INPUT)
        {
            printf("Input Enum val: %d\n", input);
        }
        if (input == ESCAPE_INPUT)
        {
            printf("Esc pressed\n");
            return;
        }
    }
}

/* Test display rendering of start screen and difficulty selection
*/
void test_startscreen(void)
{
    printf("Drawing Start Screen \n");
    startscreen_init();
    startscreen_draw();
    timer_delay_ms(3*TEST_DELAY);

    printf("Selecting Difficulty 2\n");
    startscreen_select_difficulty(2);
    timer_delay_ms(3*TEST_DELAY);

    printf("Selecting Difficulty 3\n");
    startscreen_select_difficulty(3);
    timer_delay_ms(3*TEST_DELAY);

    printf("Selecting Difficulty 1\n");
    startscreen_select_difficulty(1);
    timer_delay_ms(10*TEST_DELAY);
}

/* Test display rendering of End Screen with various scores
*/
void test_endscreen(void)
{
    printf("Drawing End Screen and Leaderboard\n");
    endscreen_init();

    int scores[] = {0, 2, 5, 30, 101, 201, 301, 9999};

    for (int i = 0; i < 8; i++)
    {
        printf("Score: %d\n", scores[i]);
        endscreen_draw(scores[i]);
        timer_delay_ms(3*TEST_DELAY);
    }

    timer_delay_ms(10*TEST_DELAY);
}

void main(void)
{
    interrupts_init();
    uart_init();
    printf("Running tests from file %s\n", __FILE__);

    interrupts_global_enable(); 

    test_endscreen();

    test_startscreen();

    test_pregame_input();

    test_game_input();

    test_collapse_rows();

    test_move_insert();

    test_insert_tetromino();

    // random piece so test a few times
    for (int i = 0; i < 3; i++)
        test_move_tetromino();

    test_tetromino_pieces();

    board_init();

    test_draw_tetromino();

    board_init();
    test_draw_all_tetromino();

    board_init();
    test_random_tetromino();

    uart_putchar(EOT);
}
