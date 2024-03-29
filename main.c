/*************************************************************************************************************
main.c - main file to run the game

Authors: Raghav Prasad, Marcus Cheung
Last Updated: Mar. 24th, 2024
*************************************************************************************************************/

#include "global.h"

#define MAX_KNIGHTS 20
#define USER_TOWER_X 35
#define USER_TOWER_Y 160
#define KNIGHT_WIDTH 15
#define KNIGHT_HEIGHT 22

// Local Global Variables
struct fb_t { unsigned short volatile  pixels[256][512]; };
struct fb_t *const fbp = ((struct fb_t *) 0x8000000);
gameState currentGameState = Intro;



volatile int pixel_buffer_start;  // global variable for the pixel buffer
short int Buffer1[240][512];      // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
int vgaWidth = 320;               // vga dimensions
int vgaHeight = 240;

// Sprites 
Knight knightList[MAX_KNIGHTS]; 

Knight testdummy; // TESTING

unsigned short (*knightImages[6])[22][15] = {Knight_Walking1, Knight_Walking2, Knight_Walking3, Knight_Walking4, Knight_Walking5, Knight_Walking6};



/*************************************************************************************************************/
//---------------------------------------------MAIN FUNCTION-------------------------------------------------//
int main(){
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020; // base address of the VGA controller


    //TESTING
    
    testdummy.xpos = 35;
    testdummy.ypos = 160;
    testdummy.width = 15;
    testdummy.height = 22;


    // VGA SETUP
        /* 1. set front pixel buffer to Buffer 1 */
        *(pixel_ctrl_ptr + 1) = (int)&Buffer1;  // first store the address in the back buffer
        /* 2. now, swap the front/back buffers, to set the front buffer location */
        wait_for_vsync();
        /* initialize a pointer to the pixel buffer, used by drawing functions */
        pixel_buffer_start = *pixel_ctrl_ptr;
        clear_screen();  // pixel_buffer_start points to the pixel buffer

        /* set back pixel buffer to Buffer 2 */
        *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // we draw on the back buffer
        clear_screen();  // pixel_buffer_start points to the pixel buffer
    

    // Initial setup for the game
    intializeSprites();
    spawn_knight();
    draw_background();

    while (1) {
        /* Erase any boxes and lines that were drawn in the last iteration */
        //draw(x_box, y_box, dx, dy, boxcolour);
        draw();
        // code for drawing the boxes and lines (not shown)
        // code for updating the locations of boxes (not shown)


        // NEED TO DO: create switch case statements for different parts of the game + integrate keyboard usage
        switch (currentGameState){
            case Intro:
                /* code */
                break;
            
            case Game:
                /* code */
                break;
        
        default:
            break;
        }

        wait_for_vsync();  // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // gets the current address of the back buffer
    }


	return 0;
}
/*************************************************************************************************************/




/*************************************************************************************************************/
void plot_pixel(int x, int y, unsigned short int color) {
  volatile short int *one_pixel_address;
  one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
  *one_pixel_address = color;
}


void wait_for_vsync() {
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;  // base address of the VGA controller
  int status;
  *pixel_ctrl_ptr = 1;  // start the synchronization process
  // write 1 into front buffer address register
  status = *(pixel_ctrl_ptr + 3);  // read the status register

  while ((status & 0x01) != 0) {  // polling loop waiting for S bit to go to 0
    status = *(pixel_ctrl_ptr + 3);
  }  // loop/function exits when status bit goes to 0
}


void clear_screen() {
  int y, x;
  for (x = 0; x < vgaWidth; x++)
    for (y = 0; y < vgaHeight; y++) plot_pixel(x, y, 0);
}

void intializeSprites(){
    // Initialize knights
    for (int i = 0; i < MAX_KNIGHTS - 1; i++) {
        knightList[i].xpos = USER_TOWER_X;
        knightList[i].dx = 0;
        knightList[i].ypos = USER_TOWER_Y;
        knightList[i].width = KNIGHT_WIDTH;
        knightList[i].height = KNIGHT_HEIGHT;
        knightList[i].health = 1;
        knightList[i].state = Default;
        knightList[i].image = knightImages[0];
        knightList[i].currentImage = 0;
        knightList[i].isVisible = false;
    }
}

void draw(){
    //first erase old objects
    clear_screen();  // get rid of this later
    //erase_knights();


    //draw objects 
    draw_background();
    // draw_sprite(testdummy.xpos, testdummy.ypos, testdummy.width, testdummy.height, *knightImages[0]); // TESTING (this works)
    draw_sprite(knightList[0].xpos, knightList[0].ypos, knightList[0].width, knightList[0].height, *knightList[0].image); 



    //update positions of everything 
    update_knights();

}


void draw_sprite(int x, int y, int width, int height, unsigned short int sprite[height][width]) {
    int sxi, syi; // sprite pixel position
    int xi, yi;   // current pixel being drawn
	
	for (sxi = 0; sxi < width; sxi++)
		for (syi = 0; syi < height; syi++) {
		   xi = x + sxi;
		   yi = y + syi;
     	   
           // draw the sprite (excluding transparent colour)
           if(sprite[syi][sxi] != TRANSPARENT) plot_pixel(xi, yi, sprite[syi][sxi]);
	}
}


void draw_background(){
    for (int x = 0; x < vgaWidth; x++){
        for (int y = 0; y < vgaHeight; y++){
            plot_pixel(x, y, game_background[y][x]);
        }
    }

}


void spawn_knight(){
    // Find the next knight in the array and 'spawn' him in
    for (int i = 0; i < MAX_KNIGHTS - 1; i++){
        if (knightList[i].isVisible == false){
            knightList[i].isVisible = true;
            knightList[i].image = knightImages[0];
            break;            
        }
        
    }
    
}


void erase_knights(){



}


void update_knights(){
    // check collisions or enemy detection

    // update x and y position as well as currentState 
    for (int i = 0; i < MAX_KNIGHTS - 1; i++) {
        // Only update visible/spawned in knights
        if (knightList[i].isVisible) { 
            // if just spawned in
            if (knightList[i].state == Default && knightList[i].xpos == USER_TOWER_X) {
                knightList[i].state = Walking;
            } else if (knightList[i].state == Walking) {
                // Update the current image index for animation
                knightList[i].currentImage = (knightList[i].currentImage + 1) % 6; 
                // Update the image pointer to the current image
                knightList[i].image = knightImages[knightList[i].currentImage];
                
            }
            

        }
    }
}

/*************************************************************************************************************/

