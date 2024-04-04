#include "global.h" // defines global values

/*******************************************************************************
 * This function sets up the PS2 keyboard interrupt.
 ********************************************************************************/
void init_PS2_interrupt(void)
{
    volatile int *PS2_ptr = (int *)0xFF200100;              // PS2 base address

    // PS/2 set up interrupts
    *(PS2_ptr+1) = 0x1; // Make RE field 1 to enable interrupts

    /* set interrupt mask bits for IRQ 7 (PS2 interrupt) */
    NIOS2_WRITE_IENABLE(0b1000000);
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
            if(key_buffer_count < 128){
                key_buffer[key_buffer_count+1] = KeyData;
                key_buffer_count++;
            }
            else{
                key_buffer_count = 0;
                key_buffer[key_buffer_count+1] = KeyData;
            }
        }
    }
    while(RAVAIL > 0);
    return;
}


