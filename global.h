/*************************************************************************************************************
global.h - header file that includes libraries being used and declares functions

Authors: Raghav Prasad, Marcus Cheung
Last Updated: Mar. 24th, 2024
*************************************************************************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

// Included Files/Libraries
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "images.h"




/*************************************************************************************************************/
//FUNCTION HEADERS

void wait_for_vsync();
void plot_pixel(int x, int y, short int color);
void clear_screen();
void draw();
void draw_background();

//void draw();
    //void update_positions --> have different parts of code to update different types of characters



/*************************************************************************************************************/



/*************************************************************************************************************/
//TYPEDEF STRUCTS

typedef enum {
    Intro,
    Game,
    GameOver
} gameState;

typedef struct Knight {
    int xpos;
    int ypos;
    int state;
    int health;


} Knight;





/*************************************************************************************************************/

#endif  // GLOBAL_H