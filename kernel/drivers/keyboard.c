#include <keyboard.h>



void keyboard_init()
{
	_enable_irq(1);
    char *display_key_buff = DISPLAY_KEY_BUFF;
    mcpy(
        (u8 *)display_key_buff, 
        (u8 *)"XX1234567890-=XXqwertyuiop[]XXasdfghjkl;'`X\\zxcvbnm,./",
        0x200);
}

void do_key(u8 scancode)
{
    switch (scancode) {

    case ENTER:
        putc('\n');
        break;

    default:
        putc(DISPLAY_KEY_BUFF[scancode]);
    }
}

void keyboard_handler()
{
    
	u8 scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
        // xprintf("the released key scancode is %X \n", scancode);
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        // xprintf("the pressed key scancode is %X the ascii is %c \n", scancode, display_lower_ascii[scancode]);

        do_key(scancode);
    }
}