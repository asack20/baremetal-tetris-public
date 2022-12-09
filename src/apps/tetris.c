/****************************************************************************
tetris.c

Main driver for tetris game

Andrew Sack
CS107E
3/13/22
****************************************************************************/

#include "printf.h"
#include "uart.h"
#include "interrupts.h"
#include "board.h"
#include "timer.h"
#include "input.h"
#include "tetromino.h"
#include "game.h"

void main(void)
{
    uart_init();
    printf("Starting Tetris!\n");

    // Interrupt Init
    interrupts_init();
    game_init();
    interrupts_global_enable(); 
    
    // Game Play Loop
    while (1)
    {
        game_run_pregame();
        game_run_game();
        game_run_postgame();
    }

    uart_putchar(EOT);
}
