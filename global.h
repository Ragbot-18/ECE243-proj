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
    void draw_sprite(int x, int y, int width, int height, uint16_t sprite[][width]); 
        // sprite is the image array, x and y are the top left position of the sprite, width and height are the dimensions of the sprite
    void draw_background();
    void spawn_knight();
    void erase_knights();
    void update_knights();

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


typedef enum {
    Default,
    Walking,
    Attacking

} spriteState;


typedef struct Knight {
    int xpos;
    int ypos;
    int width;
    int height;
    int health;
    spriteState state;
    int currentImage;


} Knight;





/*************************************************************************************************************/

#endif  // GLOBAL_H