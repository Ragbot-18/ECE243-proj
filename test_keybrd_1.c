/* function prototypes */
int main();
void interrupt_handler(void);
void PS2_ISR();
void init_PS2_interrupt(void);

/* variable declaration */

#define KEY_BUFFER_SIZE 64

volatile char key_buffer[KEY_BUFFER_SIZE]; //pointer to the key buffer;
volatile int key_buffer_count = 0; //counter for the key buffer;

#ifndef __NIOS2_CTRL_REG_MACROS__
#define __NIOS2_CTRL_REG_MACROS__
/*****************************************************************************/
/* Macros for accessing the control registers. */
/*****************************************************************************/
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
#endif


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
    if (ipending & 0b10000000) // PS2 is interrupt level 7
    {
        PS2_ISR();
    }
    // else, ignore the interrupt
    return;
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
	int ctl3read;
	NIOS2_READ_IENABLE(ctl3read);
    NIOS2_WRITE_IENABLE(ctl3read|0b10000000);
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
void PS2_ISR()
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
            }
        }
    }
    while(RAVAIL > 0);
    return;
}



int main(){
	init_PS2_interrupt();
	while(1){
		while(key_buffer_count!=0){
			char data = key_buffer[key_buffer_count-1];
			volatile int* LEDS = (volatile int*) 0xff200000;
			*(LEDS) = data;
			key_buffer[key_buffer_count-1] = 0;
			key_buffer_count--;
		}
	}
}
	