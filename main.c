/*************************************************************************************************************
main.c - main file to run the game

Authors: Raghav Prasad, Marcus Cheung
Last Updated: Mar. 24th, 2024
*************************************************************************************************************/

#include "global.h"

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
Knight oldKnightsList[MAX_KNIGHTS];

Knight testdummy; // TESTING

// Sprite Arrays
unsigned short (*knightDefault[1])[19][15] = {Knight_Default};
unsigned short (*knightWalking[6])[22][15] = {Knight_Walking1, Knight_Walking2, Knight_Walking3, Knight_Walking4, Knight_Walking5, Knight_Walking6};
unsigned short (*knightAttacking[3])[19][27] = {Knight_Attacking1, Knight_Attacking2, Knight_Attacking3};


unsigned short (*e_knightDefault[1])[19][15] = {Enemy_Knight_Default};
unsigned short (*e_knightWalking[6])[22][15] = {Enemy_Knight_Walking1, Enemy_Knight_Walking2, Enemy_Knight_Walking3, Enemy_Knight_Walking4, Enemy_Knight_Walking5, Enemy_Knight_Walking6};
unsigned short (*e_knightAttacking[3])[19][27] = {Enemy_Knight_Attacking1, Enemy_Knight_Attacking2, Enemy_Knight_Attacking3};


/* function prototypes */
int main();
void interrupt_handler(void);



/*************************************************************************************************************/
//--------------------------------------------- PROLOGUE FUNCTION-------------------------------------------------//
/* The assembly language code below handles CPU reset processing */
void the_reset(void) __attribute__((section(".reset")));
void the_reset(void)
/*******************************************************************************
 * Reset code. By giving the code a section attribute with the name ".reset" we
 * allow the linker program to locate this code at the proper reset vector
 * address. This code just calls the main program.
 ******************************************************************************/
{
    asm(".set noat");      /* Instruct the assembler NOT to use reg at (r1) as
                            * a temp register for performing optimizations */
    asm(".set nobreak");   /* Suppresses a warning message that says that
                            * some debuggers corrupt regs bt (r25) and ba
                            * (r30)
                            */
    asm("movia r2, main"); // Call the C language main program
    asm("jmp r2");
}
/* The assembly language code below handles CPU exception processing. This
 * code should not be modified; instead, the C language code in the function
 * interrupt_handler() can be modified as needed for a given application.
 */
void the_exception(void) __attribute__((section(".exceptions")));
void the_exception(void)
/*******************************************************************************
 * Exceptions code. By giving the code a section attribute with the name
 * ".exceptions" we allow the linker program to locate this code at the proper
 * exceptions vector address.
 * This code calls the interrupt handler and later returns from the exception.
 ******************************************************************************/
{
    asm("subi sp, sp, 128");
    asm("stw et, 96(sp)");
    asm("rdctl et, ctl4");
    asm("beq et, r0, SKIP_EA_DEC"); // Interrupt is not external
    asm("subi ea, ea, 4");          /* Must decrement ea by one instruction
                                     * for external interupts, so that the
                                     * interrupted instruction will be run */
    asm("SKIP_EA_DEC:");
    asm("stw r1, 4(sp)"); // Save all registers
    asm("stw r2, 8(sp)");
    asm("stw r3, 12(sp)");
    asm("stw r4, 16(sp)");
    asm("stw r5, 20(sp)");
    asm("stw r6, 24(sp)");
    asm("stw r7, 28(sp)");
    asm("stw r8, 32(sp)");
    asm("stw r9, 36(sp)");
    asm("stw r10, 40(sp)");
    asm("stw r11, 44(sp)");
    asm("stw r12, 48(sp)");
    asm("stw r13, 52(sp)");
    asm("stw r14, 56(sp)");
    asm("stw r15, 60(sp)");
    asm("stw r16, 64(sp)");
    asm("stw r17, 68(sp)");
    asm("stw r18, 72(sp)");
    asm("stw r19, 76(sp)");
    asm("stw r20, 80(sp)");
    asm("stw r21, 84(sp)");
    asm("stw r22, 88(sp)");
    asm("stw r23, 92(sp)");
    asm("stw r25, 100(sp)"); // r25 = bt (skip r24 = et, because it is saved
    // above)
    asm("stw r26, 104(sp)"); // r26 = gp
    // skip r27 because it is sp, and there is no point in saving this
    asm("stw r28, 112(sp)"); // r28 = fp
    asm("stw r29, 116(sp)"); // r29 = ea
    asm("stw r30, 120(sp)"); // r30 = ba
    asm("stw r31, 124(sp)"); // r31 = ra
    asm("addi fp, sp, 128");
    asm("call interrupt_handler"); // Call the C language interrupt handler
    asm("ldw r1, 4(sp)");          // Restore all registers
    asm("ldw r2, 8(sp)");
    asm("ldw r3, 12(sp)");
    asm("ldw r4, 16(sp)");
    asm("ldw r5, 20(sp)");
    asm("ldw r6, 24(sp)");
    asm("ldw r7, 28(sp)");
    asm("ldw r8, 32(sp)");
    asm("ldw r9, 36(sp)");
    asm("ldw r10, 40(sp)");
    asm("ldw r11, 44(sp)");
    asm("ldw r12, 48(sp)");
    asm("ldw r13, 52(sp)");
    asm("ldw r14, 56(sp)");
    asm("ldw r15, 60(sp)");
    asm("ldw r16, 64(sp)");
    asm("ldw r17, 68(sp)");
    asm("ldw r18, 72(sp)");
    asm("ldw r19, 76(sp)");
    asm("ldw r20, 80(sp)");
    asm("ldw r21, 84(sp)");
    asm("ldw r22, 88(sp)");
    asm("ldw r23, 92(sp)");
    asm("ldw r24, 96(sp)");
    asm("ldw r25, 100(sp)"); // r25 = bt
    asm("ldw r26, 104(sp)"); // r26 = gp
    // skip r27 because it is sp, and we did not save this on the stack
    asm("ldw r28, 112(sp)"); // r28 = fp
    asm("ldw r29, 116(sp)"); // r29 = ea
    asm("ldw r30, 120(sp)"); // r30 = ba
    asm("ldw r31, 124(sp)"); // r31 = ra
    asm("addi sp, sp, 128");
    asm("eret");
}
/******************************************************************************
 * Interrupt Service Routine
 * Determines what caused the interrupt and calls the appropriate
 * subroutine.
 *
 * ipending - Control register 4 which has the pending external interrupts
 ******************************************************************************/
void interrupt_handler(void)
{
    int ipending;
    NIOS2_READ_IPENDING(ipending);
    if (ipending & 0x7) // PS2 is interrupt level 7
    {
        PS2_ISR();
    }
    // else, ignore the interrupt
    return;
}


/*************************************************************************************************************/
//---------------------------------------------MAIN FUNCTION-------------------------------------------------//
int main(){
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020; // base address of the VGA controller


    //TESTING
    
    // testdummy.xpos = 35;
    // testdummy.ypos = 160;
    // testdummy.width = 15;
    // testdummy.height = 22;


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
    spawn_knight(); //TESTING - will link this with appropriate keyboard press within Game case below
    draw_background(); // TESTING - will switch to draw appropriate background depending on currentGameState

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
                // wait for certain key to be pressed then switch to game state and start the game (maybe add instructions page?)
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
        knightList[i].width = KNIGHT_DEFAULT_WIDTH;
        knightList[i].height = KNIGHT_DEFAULT_HEIGHT;
        knightList[i].health = 1;
        knightList[i].hitbox = knightList[i].xpos + knightList[i].width;
        knightList[i].detectionRange = 10;
        knightList[i].state = Default;
        knightList[i].image = knightDefault[0];
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
    // draw_sprite(testdummy.xpos, testdummy.ypos, testdummy.width, testdummy.height, *knightWalking[0]); // TESTING (this works)
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
            knightList[i].image = knightDefault[0];
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
        // 1. Update variables depending on the current state
            // if just spawned in, update to walking state
            if (knightList[i].state == Default && knightList[i].xpos == USER_TOWER_X) {
                knightList[i].state = Walking;
                knightList[i].width = KNIGHT_WALKING_WIDTH;
                knightList[i].height = KNIGHT_WALKING_HEIGHT;
                knightList[i].image = knightWalking[0];
                knightList[i].dx = 2;
            } 
            // if in walking state
            else if (knightList[i].state == Walking) {
                // Update the current image index for animation
                knightList[i].currentImage = (knightList[i].currentImage + 1) % 6; 
                // Update the image pointer to the current image
                knightList[i].image = knightWalking[knightList[i].currentImage];
                // Update the position of the knight
                knightList[i].xpos = knightList[i].xpos + knightList[i].dx;
            } else if (knightList[i].state == Attacking){
                knightList[i].currentImage = (knightList[i].currentImage + 1) % 3;
                knightList[i].image = knightAttacking[knightList[i].currentImage];
            }
            
        // 2. Collision Detection
            
            if (knightList[i].xpos >= ENEMY_TOWER_X_EDGE && knightList[i].state != Attacking){
                knightList[i].state = Attacking;
                knightList[i].dx = 0; 
                knightList[i].width = KNIGHT_ATTACKING_WIDTH;
                knightList[i].height = KNIGHT_ATTACKING_HEIGHT;
                knightList[i].image = knightAttacking[0];
            }
            


            // Update hitboxes
            knightList[i].hitbox = knightList[i].xpos + knightList[i].width;
        }
    }
}

/*************************************************************************************************************/

