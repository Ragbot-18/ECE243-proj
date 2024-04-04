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

#include "nios2_ctrl_reg_macros.h"
//#include "address_map_nios2.h"

/*************************************************************************************************************/
//GLOBAL DEFINATIONS
#define KEY_BUFFER_SIZE 64

/*************************************************************************************************************/

/*************************************************************************************************************/
//GLOBAL VARIABLES



volatile char key_buffer[KEY_BUFFER_SIZE]; //pointer to the key buffer;
volatile int key_buffer_count = 0; //counter for the key buffer;
int g = 10; // gravity


/*************************************************************************************************************/




/*************************************************************************************************************/
//FUNCTION HEADERS

void wait_for_vsync();
void plot_pixel(int x, int y, unsigned short int color);
void clear_screen();
void draw();
    void draw_sprite(int x, int y, int width, int height, uint16_t sprite[][width]); 
        // sprite is the image array, x and y are the top left position of the sprite, width and height are the dimensions of the sprite
    void draw_background();
    void spawn_knight();
    void erase_knights();
    void update_knights();
void intializeSprites();
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
    int dx;
    int ypos;
    int width;
    int height;
    int health;
    int hitbox; // this is the right hand hitbox of the knight (xpos + width)
    int detectionRange; // this is the range past the hitbox that the knight will be scanning for entities
    spriteState state;
    unsigned short (*image)[22][15];
    int currentImage;
    bool isVisible;

} Knight;

typedef struct Tower {
    int xpos;
    int ypos;
    int width;
    int height;
    int health;
    int hitbox; // this is the right hand hitbox of the tower (xpos + width)
    int detectionRange; // this is the range past the hitbox that the tower will be scanning for entities
    spriteState state;
    // unsigned short (*image)[22][15];
    // int currentImage;
    // bool isVisible;

} Tower;

typedef struct Projectile {
    int xpos;
    int ypos;
    int dx;
    int dy;
    int speed;
    //int damage;
    //int range;
    //int type;
    // spriteState state;
    // unsigned short (*image)[22][15];
    // int currentImage;
    // bool isVisible;

} Projectile;


/*************************************************************************************************************/

#endif  // GLOBAL_H