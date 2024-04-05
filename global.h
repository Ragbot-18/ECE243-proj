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
#include "string.h"
#include "images.h"


/*************************************************************************************************************/
//GLOBAL DEFINITIONS
#define KEY_BUFFER_SIZE 64

//#include "nios2_ctrl_reg_macros.h"
#define NIOS2_READ_STATUS(dest) \
    do { dest = __builtin_rdctl(0); } while (0)
#define NIOS2_WRITE_STATUS(src) \
    do { __builtin_wrctl(0, src); } while (0)
#define NIOS2_READ_ESTATUS(dest) \
    do { dest = __builtin_rdctl(1); } while (0)
#define NIOS2_READ_BSTATUS(dest) \
    do { dest = __builtin_rdctl(2); } while (0)
#define NIOS2_READ_IENABLE(dest) \
    do { dest = __builtin_rdctl(3); } while (0)
#define NIOS2_WRITE_IENABLE(src) \
    do { __builtin_wrctl(3, src); } while (0)
#define NIOS2_READ_IPENDING(dest) \
    do { dest = __builtin_rdctl(4); } while (0)
#define NIOS2_READ_CPUID(dest) \
    do { dest = __builtin_rdctl(5); } while (0)

// Game Related Definitions
#define MAX_KNIGHTS 20

#define USER_TOWER_X 35
#define USER_TOWER_X_EDGE 55
#define USER_TOWER_Y 160
#define ENEMY_TOWER_X 285
#define ENEMY_TOWER_X_EDGE 265
#define ENEMY_TOWER_Y 160

#define KNIGHT_DEFAULT_WIDTH 15
#define KNIGHT_DEFAULT_HEIGHT 19
#define KNIGHT_WALKING_WIDTH 15
#define KNIGHT_WALKING_HEIGHT 22
#define KNIGHT_ATTACKING_WIDTH 27
#define KNIGHT_ATTACKING_HEIGHT 19

#define DIGIT_WIDTH 6
#define DIGIT_HEIGHT 10


/*************************************************************************************************************/

/*************************************************************************************************************/
//FUNCTION HEADERS
int main();
void interrupt_handler(void);
void wait_for_vsync();
void plot_pixel(int x, int y, unsigned short int color);
void clear_screen();
void draw();
    void draw_sprite(int x, int y, int width, int height, unsigned short int *sprite); 
    void erase_sprite(int x, int y, int width, int height, unsigned short int *sprite); 
        // sprite is the image array, x and y are the top left position of the sprite, width and height are the dimensions of the sprite
    
    void draw_background();

    void spawn_knight();
    bool hasVisibleKnights();
    void draw_knights();
    void erase_knights();
    void update_knights();
    
    void draw_currency();
void intializeSprites();
//void draw();
    //void update_positions --> have different parts of code to update different types of characters

void update_game();

void check_key_press();
void timer_ISR(void);
void init_timer_interrupt(void);
void init_PS2_interrupt(void);
void PS2_ISR(void);

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
    unsigned short *image;
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

/*************************************************************************************************************/
//GLOBAL VARIABLES

// volatile int timer_count = 0;

volatile char key_buffer[KEY_BUFFER_SIZE]; //pointer to the key buffer;
volatile int key_buffer_count = 0; //counter for the key buffer;
int g = 10; // gravity

struct fb_t { unsigned short volatile  pixels[256][512]; };
struct fb_t *const fbp = ((struct fb_t *) 0x8000000);
gameState currentGameState;
const unsigned short int* current_background;

int start_time;
int last_currency_update; 
int currency;
int current_time;

volatile int pixel_buffer_start;  // global variable for the pixel buffer
short int Buffer1[240][512];      // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
int vgaWidth = 320;               // vga dimensions
int vgaHeight = 240;
/*************************************************************************************************************/

#endif  // GLOBAL_H