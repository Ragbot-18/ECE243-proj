/*************************************************************************************************************
main.c - main file to run the game

Authors: Raghav Prasad, Marcus Cheung
Last Updated: Mar. 24th, 2024
*************************************************************************************************************/

#include "global.h"



// Sprites 
Knight knightList[MAX_KNIGHTS]; 
Knight oldKnightsList[MAX_KNIGHTS];

Knight enemyKnightsList[MAX_KNIGHTS];


// Sprite Arrays
unsigned short *knightDefault[1] = {Knight_Default};
unsigned short *knightWalking[6] = {Knight_Walking1, Knight_Walking2, Knight_Walking3, Knight_Walking4, Knight_Walking5, Knight_Walking6};
unsigned short *knightAttacking[3] = {Knight_Attacking1, Knight_Attacking2, Knight_Attacking3};


unsigned short *e_knightDefault[1] = {Enemy_Knight_Default};
unsigned short *e_knightWalking[6] = {Enemy_Knight_Walking1, Enemy_Knight_Walking2, Enemy_Knight_Walking3, Enemy_Knight_Walking4, Enemy_Knight_Walking5, Enemy_Knight_Walking6};
unsigned short *e_knightAttacking[3] = {Enemy_Knight_Attacking1, Enemy_Knight_Attacking2, Enemy_Knight_Attacking3};


unsigned short *numberImages[10] = {Number_0, Number_1, Number_2, Number_3, Number_4, Number_5, Number_6, Number_7, Number_8, Number_9};
unsigned short *smallNumberImages[10] = {small_Number0, small_Number1, small_Number2, small_Number3, small_Number4, small_Number5, small_Number6, small_Number7, 8, small_Number9};
unsigned short *knightButton[4] = {Knight_Button1, Knight_Button2, Knight_Button3, Knight_Button4};



/*************************************************************************************************************/
//---------------------------------------------PROLOGUE FUNCTION---------------------------------------------//
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
    if (ipending & 0b10000000) // PS2 is interrupt level 7
    {
        PS2_ISR();
    }
    if (ipending & 0x1) // interval timer is interrupt level 0
    {
        timer_ISR();
    }
    // else, ignore the interrupt
    return;
}


/*************************************************************************************************************/
//---------------------------------------------MAIN FUNCTION-------------------------------------------------//
int main(){
    init_PS2_interrupt();
    init_timer_interrupt();
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020; // base address of the VGA controller

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
    gameState currentGameState = Intro;
    current_background = game_background; // TESTING - set this intro background when made

    intializeSprites();
    // spawn_knight(); // TESTING 
    draw_background(); // TESTING - will switch to draw appropriate background depending on currentGameState

    knightButtonPressed = false;
    spawnEnemyKnight = false;
    start_time = 0;
    current_time = start_time;
    currency = 0;
    last_currency_update = start_time; 


    while (1) {
        check_key_press();
        draw();        // TESTING - move this into the Game case below

        // INTRO - draw intro background, wait until certain key is pressed
        // GAME - regular draw function

        // NEED TO DO: create switch case statements for different parts of the game + integrate keyboard usage
        switch (currentGameState){
            case Intro:
                /* code */ 
                // wait for certain key to be pressed then switch to game state and start the game (maybe add instructions page?)
            case Game:
                /* code */
        
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
        // Initialize user knights
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

        // Initialize enemy knights
        enemyKnightsList[i].xpos = ENEMY_TOWER_X;
        enemyKnightsList[i].dx = 0;
        enemyKnightsList[i].ypos = ENEMY_TOWER_Y;
        enemyKnightsList[i].width = KNIGHT_DEFAULT_WIDTH;
        enemyKnightsList[i].height = KNIGHT_DEFAULT_HEIGHT;
        enemyKnightsList[i].health = 1;
        enemyKnightsList[i].hitbox = enemyKnightsList[i].xpos + enemyKnightsList[i].width; // can maybe just set the hitbox to the xpos
        enemyKnightsList[i].detectionRange = 10; // might need to set this to be negative OR just subtract when using it
        enemyKnightsList[i].state = Default;
        enemyKnightsList[i].image = e_knightDefault[0];
        enemyKnightsList[i].currentImage = 0;
        enemyKnightsList[i].isVisible = false;

    }

}

void draw(){
    //first erase old objects
    //clear_screen();  // get rid of this later
    //erase_knights(); -- doesnt do anything at the moment because we are drawing the background in this loop
    if (spawnEnemyKnight) {
        spawn_enemy_knight();
    }

    //draw objects 
    draw_background(); 
    draw_currency(20, 10);
    draw_knight_button();

    // draw_sprite(knightList[0].xpos, knightList[0].ypos, knightList[0].width, knightList[0].height, knightList[0].image); // MANUAL TESTING -- WORKS
    draw_knights();


    //update everything 
    update_knights();

}


void draw_sprite(int x, int y, int width, int height, unsigned short int *sprite) {
    int sxi, syi; // sprite pixel position
    int xi, yi;   // current pixel being drawn
	
	for (sxi = 0; sxi < width; sxi++){
		for (syi = 0; syi < height; syi++) {
		   xi = x + sxi;
		   yi = y + syi;
     	   
           int index = syi * width + sxi;
           if(sprite[index] != TRANSPARENT)
                plot_pixel(xi, yi, sprite[index]);
           
	    }
    }
}


void erase_sprite(int x, int y, int width, int height, unsigned short int *sprite) {
    int sxi, syi; // sprite pixel position
    int xi, yi;   // current pixel being drawn
	
	for (sxi = 0; sxi < width; sxi++){
		for (syi = 0; syi < height; syi++) {
		   xi = x + sxi;
		   yi = y + syi;
     	   
           int index = syi * width + sxi;
           if(sprite[index] != TRANSPARENT)
                plot_pixel(xi, yi, current_background[index]);
           
	    }
    }
}

void draw_background(){
    for (int x = 0; x < vgaWidth; x++){
        for (int y = 0; y < vgaHeight; y++){
            plot_pixel(x, y, current_background[y * vgaWidth + x]);
        }
    }
}


void spawn_enemy_knight(){
    // spawn in an enemy knight every 15 seconds (can change this/potentially make it decrease over time)
    for (int i = 0; i < MAX_KNIGHTS - 1; i++){
        if (enemyKnightsList[i].isVisible == false){
            enemyKnightsList[i].isVisible = true;
            enemyKnightsList[i].image = e_knightDefault[0];
            spawnEnemyKnight = false;
            break;
        }
    }
}


void draw_knight_button(){
    if (currency < 10){
        if (knightButtonPressed){
            draw_sprite(KNIGHT_BUTTON_X, KNIGHT_BUTTON_Y, KNIGHT_BUTTON_WIDTH, KNIGHT_BUTTON_HEIGHT, knightButton[1]);
            knightButtonPressed = false;
        } else {
            draw_sprite(KNIGHT_BUTTON_X, KNIGHT_BUTTON_Y, KNIGHT_BUTTON_WIDTH, KNIGHT_BUTTON_HEIGHT, knightButton[0]);
        }
        
    } else if (currency >= 10){
        if (knightButtonPressed){
            draw_sprite(KNIGHT_BUTTON_X, KNIGHT_BUTTON_Y, KNIGHT_BUTTON_WIDTH, KNIGHT_BUTTON_HEIGHT, knightButton[3]);
            knightButtonPressed = false;   
            spawn_knight();
        } else {
            draw_sprite(KNIGHT_BUTTON_X, KNIGHT_BUTTON_Y, KNIGHT_BUTTON_WIDTH, KNIGHT_BUTTON_HEIGHT, knightButton[2]);
        }
    }
    
    


}

void spawn_knight(){
    // Subtract the cost of the knight
    currency -= 10; 
    // Find the next knight in the array and 'spawn' him in
    for (int i = 0; i < MAX_KNIGHTS - 1; i++){
        if (knightList[i].isVisible == false){
            knightList[i].isVisible = true;
            knightList[i].image = knightDefault[0];
            break;            
        }
        
    }
    
}


bool hasVisibleKnights() {
    for (int i = 0; i < MAX_KNIGHTS - 1; i++) {
        if (knightList[i].isVisible) {
            return true; 
        }
    }
    return false; // No visible knights found
}


void draw_knights(){
    for (int i = 0; i < MAX_KNIGHTS - 1; i++){
        if (knightList[i].isVisible){
            draw_sprite(knightList[i].xpos, knightList[i].ypos, knightList[i].width, knightList[i].height, knightList[i].image);
        }
        if (enemyKnightsList[i].isVisible){
            draw_sprite(enemyKnightsList[i].xpos, enemyKnightsList[i].ypos, enemyKnightsList[i].width, enemyKnightsList[i].height, enemyKnightsList[i].image);
        }
    }
}


void erase_knights(){
    if (hasVisibleKnights){
        for (int i = 0; i < MAX_KNIGHTS - 1; i++){
            if (knightList[i].isVisible){
                erase_sprite(oldKnightsList[i].xpos, oldKnightsList[i].ypos, oldKnightsList[i].width, oldKnightsList[i].height, oldKnightsList[i].image);
            }
        }
    }
    
        
}


void update_knights(){
    // NEED TO DO: check collisions or enemy detection

    
    for (int i = 0; i < MAX_KNIGHTS - 1; i++) {
        // USER KNIGHTS 
        if (knightList[i].isVisible) {
            oldKnightsList[i] = knightList[i]; // save the old position to erase

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
            
        // 2. Collision Detection (might need to move this to the bottom / write detection code at the bottom once enemy knights updated as well)
            
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

        // ENEMY KNIGHTS
        if (enemyKnightsList[i].isVisible) {
            // oldKnightsList[i] = knightList[i]; // save the old position to erase

        // 1. Update variables depending on the current state
            // if just spawned in, update to walking state
            if (enemyKnightsList[i].state == Default && enemyKnightsList[i].xpos == ENEMY_TOWER_X) {
                enemyKnightsList[i].state = Walking;
                enemyKnightsList[i].width = KNIGHT_WALKING_WIDTH;
                enemyKnightsList[i].height = KNIGHT_WALKING_HEIGHT;
                enemyKnightsList[i].image = e_knightWalking[0];
                enemyKnightsList[i].dx = 2;
            } 
            // if in walking state
            else if (enemyKnightsList[i].state == Walking) {
                // Update the current image index for animation
                enemyKnightsList[i].currentImage = (enemyKnightsList[i].currentImage + 1) % 6; 
                // Update the image pointer to the current image
                enemyKnightsList[i].image = e_knightWalking[enemyKnightsList[i].currentImage];
                // Update the position of the knight
                enemyKnightsList[i].xpos = enemyKnightsList[i].xpos - enemyKnightsList[i].dx; // moving left so we subtract dx instead of adding
            } else if (enemyKnightsList[i].state == Attacking){
                enemyKnightsList[i].currentImage = (enemyKnightsList[i].currentImage + 1) % 3;
                enemyKnightsList[i].image = e_knightAttacking[enemyKnightsList[i].currentImage];
            }

        // 2. Collision Detection (might need to move this to the bottom / write detection code at the bottom once all knights have been updated)


            if (enemyKnightsList[i].xpos <= USER_TOWER_X_EDGE && enemyKnightsList[i].state != Attacking){
                enemyKnightsList[i].state = Attacking;
                enemyKnightsList[i].dx = 0; 
                enemyKnightsList[i].width = KNIGHT_ATTACKING_WIDTH;
                enemyKnightsList[i].height = KNIGHT_ATTACKING_HEIGHT;
                enemyKnightsList[i].image = e_knightAttacking[0];
            }
            


            // Update hitboxes
            // enemyKnightsList[i].hitbox = enemyKnightsList[i].xpos + enemyKnightsList[i].width; // this would be calculating the right hand side hit box
            
            // for enemy knights, can probably just set hitbox to xpos for left hand side boundary but you can decide how you want to do this

        }
    }
}



void draw_currency(int x, int y) {
    int temp_currency = currency;
    int digit_width_with_spacing = DIGIT_WIDTH + 2; // Assuming 2 pixel space between digits for clarity

    // If currency is 0, directly draw the '0' digit
    if (temp_currency == 0) {
        draw_sprite(x, y, DIGIT_WIDTH, DIGIT_HEIGHT, numberImages[0]);
        return;
    }

    // Calculate the number of digits in the currency to adjust starting x position
    int num_digits = 0;
    for (int temp = temp_currency; temp > 0; temp /= 10) {
        num_digits++;
    }
    
    // Adjust the starting x position based on the number of digits to draw from left to right
    int adjusted_x = x + (num_digits - 1) * digit_width_with_spacing;
    
    while (temp_currency > 0) {
        int digit = temp_currency % 10; // Extract the rightmost digit
        temp_currency /= 10; // Remove the rightmost digit
        
        // Draw the current digit
        // Note: numberImages array is indexed correctly with 0 being the first element
        draw_sprite(adjusted_x, y, DIGIT_WIDTH, DIGIT_HEIGHT, numberImages[digit]);
        
        // Move to the next position on the left
        adjusted_x -= digit_width_with_spacing;
    }
}

/*******************************************************************************
 * This function sets up the PS2 keyboard interrupt.
 ********************************************************************************/
void init_PS2_interrupt(void)
{
    volatile int *PS2_ptr = (int *)0xFF200100;              // PS2 base address

    // PS/2 set up interrupts
    *(PS2_ptr+1) = 0x1; // Make RE field 1 to enable interrupts

    /* set interrupt mask bits for IRQ 7 (PS2 interrupt) */
    NIOS2_WRITE_IENABLE(0b10000000);
    int ctl0status;
    NIOS2_READ_STATUS(ctl0status);
    if( ctl0status & 0x1);// check Nios II status to see if interrupts are currently enabled
    else
        NIOS2_WRITE_STATUS(1); // enable Nios II interrupts if they are currently disabled
    return;
}


/*******************************************************************************
 * This function is the PS2 interrupt service routine.
 ********************************************************************************/
void PS2_ISR(void)
{
    /* Declare volatile pointers to I/O registers (volatile means that IO load
and store instructions will be used to access these pointer locations,
instead of regular memory loads and stores) */
    volatile int *PS2_ptr = (int *)0xFF200100;
    int PS2_data, RVALID, RAVAIL;
    char KeyData;
    // PS/2 mouse needs to be reset (must be already plugged in)
    //  *(PS2_ptr) = 0xFF; // reset
    do // loop while RVALID is 1
    {   
        PS2_data = *(PS2_ptr);      // read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000; // extract the RVALID field
        RAVAIL = (PS2_data & 0xFFFF0000)>>16; // extract the RAVAIL field
        if (RVALID)
        {   
            KeyData = PS2_data & 0xFF; // get the keycode
            if(key_buffer_count < KEY_BUFFER_SIZE){
                key_buffer[key_buffer_count] = KeyData;
                key_buffer_count++;
            }
            else{
                key_buffer_count = 0;
                key_buffer[key_buffer_count] = KeyData;
                key_buffer_count++;
            }
        }
    }
    while(RAVAIL > 0);
    
    return;
}


void check_key_press(){
    int valid_input = 0;
    for (int i = key_buffer_count-1; i>=0; i--, key_buffer_count--){
        char check = 0xF0;
        if( i>0  && key_buffer[i-1] == check){      
            valid_input = 1;
        }
        else{
            valid_input = 0;
        }
        if(valid_input == 1){
            if(currentGameState == Intro){
                if(key_buffer[i] == 0x5A){ // ENTER key
                    currentGameState = Game;
                    printf("Hello there, new to gamee?? \n"); // TESTING - (working) will remove 
                }
            }
            else if(currentGameState == Game){
                if(key_buffer[i] == 0x16){ // 1 key
                        knightButtonPressed = true;
                        // spawn_knight(); 
                        printf("Spawned Knight\n"); // TESTING - (working) will remove
                   
                }
            }
        }
    }
	return;
}


void init_timer_interrupt(void){
    volatile int *timer_ptr = (volatile int *)0xFF202000; // timer base address
    *(timer_ptr + 1) = 0x8; // stop timer
    int data = 0x5F5E100;
    *(timer_ptr + 2) = data&0xFFFF; // write to control register to set the timer period
    *(timer_ptr + 3) = data>>16; // start timer
	    /* set interrupt mask bits for IRQ 7 (PS2 interrupt) */
	int ctl3read;
	NIOS2_READ_IENABLE(ctl3read);
    NIOS2_WRITE_IENABLE(ctl3read|0b1);
    int ctl0status;
    NIOS2_READ_STATUS(ctl0status);
    if(ctl0status & 0x1);// check Nios II status to see if interrupts are currently enabled
    else
        NIOS2_WRITE_STATUS(1); // enable Nios II interrupts if they are currently disabled
    *(timer_ptr + 1) = 0x7; // start timer
    return;
}

void timer_ISR(){
    volatile int *timer_ptr = (int *)0xFF202000; // timer base address
    *(timer_ptr) = 0; // clear the interrupt
    current_time++;
    currency++;

    if ((current_time & ENEMY_KNIGHT_SPAWN_INTERVAL) == 0){
        spawnEnemyKnight = true;
    }
    

    printf("Timer Count: %d\n", current_time);
    printf("Currency: %d\n", currency);
    return;
}

/*************************************************************************************************************/

