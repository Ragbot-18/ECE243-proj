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
#define MAX_KNIGHTS 50

#define USER_TOWER_X 35
#define USER_TOWER_X_EDGE 45
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

#define ENEMY_KNIGHT_SPAWN_INTERVAL 15

#define KNIGHT_BUTTON_X 100
#define KNIGHT_BUTTON_Y 190
#define KNIGHT_BUTTON_WIDTH 38
#define KNIGHT_BUTTON_HEIGHT 43
#define CURRENCY_BUTTON_X 40
#define CURRENCY_BUTTON_Y 190
#define CURRENCY_BUTTON_WIDTH 38
#define CURRENCY_BUTTON_HEIGHT 43

#define DIGIT_WIDTH 6
#define DIGIT_HEIGHT 10

#define SMALL_DIGIT_WIDTH 3
#define SMALL_DIGIT_HEIGHT 5
#define SMALL_PERCENTAGE_WIDTH 7

/*************************************************************************************************************/

/*************************************************************************************************************/
//FUNCTION HEADERS
int main();
void interrupt_handler(void);
void wait_for_vsync();
void plot_pixel(int x, int y, unsigned short int color);
void clear_screen();

void initializeGame();
void intializeSprites();
void spawn_enemy_knight();
void spawn_knight();
void erase_knights(); // currently useless
    bool hasVisibleKnights(); // used for erase_knights (so also currently useless)

void draw();
    void draw_sprite(int x, int y, int width, int height, unsigned short int *sprite); 
    void erase_sprite(int x, int y, int width, int height, unsigned short int *sprite); 
        // sprite is the image array, x and y are the top left position of the sprite, 
        // width and height are the dimensions of the sprite

    void draw_background();
    void draw_currency();
    void draw_knight_button();
    void draw_currency_button();

    void draw_knights();
    void draw_health_bar();
        void draw_box(int x, int y, int width, int height, short int color, int type);
        void draw_health_number(int health, int x, int y);

    void update_knights();
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
    GameWin,
    GameLoss
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
    int damage;
    int hitbox; // this is the right hand hitbox of the knight (xpos + width)
    int detectionRange; // this is the range past the hitbox that the knight will be scanning for entities
    spriteState state;
    unsigned short *image;
    int currentImage;
    bool isVisible;
    int fight_type; // 0 for no fight, 1 for for enemy knights and 2 for enemy towers
    int enemy_knight_number; // this is the index of the enemy knight that the knight is fighting

} Knight;

typedef struct Tower { // might be able to remove this
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

typedef struct Projectile { // probably can get rid of this
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

volatile char key_buffer[KEY_BUFFER_SIZE]; //pointer to the key buffer;
volatile int key_buffer_count = 0; //counter for the key buffer;
int g = 10; // gravity (can probably remove)

struct fb_t { unsigned short volatile  pixels[256][512]; };
struct fb_t *const fbp = ((struct fb_t *) 0x8000000);
volatile int pixel_buffer_start;  // global variable for the pixel buffer
short int Buffer1[240][512];      // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
int vgaWidth = 320;               // vga dimensions
int vgaHeight = 240;

gameState currentGameState;
const unsigned short int* current_background;\

bool knightButtonPressed;
bool currencyButtonPressed;
bool spawnEnemyKnight;
bool gameStart = false;

int start_time;
int last_currency_update; 
int currency;
int current_time;
volatile int timer_count = 0; // unused

int user_tower_health;
int enemy_tower_health;

int currencyIncreasingFactor;
/*************************************************************************************************************/

#endif  // GLOBAL_H