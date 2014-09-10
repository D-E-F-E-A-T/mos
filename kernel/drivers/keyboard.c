#include <keyboard.h>

void keyboard_init()
{
    _enable_irq(1);

    mcpy(
        (u8*)LOWER_DISPLAY_KEY_BUFF,
        (u8*)"XX1234567890-=XXqwertyuiop[]XXasdfghjkl;'`X\\zxcvbnm,./",
        DISPLAY_KEY_BUFF_SIZE);

    mcpy(
        (u8*)UPPER_DISPLAY_KEY_BUFF,
        (u8*)"XX!@#$%^&*()_+XXQWERTYUIOP{}XXASDFGHJKL:\"~X\\ZXCVBNM<>?",
        DISPLAY_KEY_BUFF_SIZE);

    DISPLAY_KEY_BUFF = LOWER_DISPLAY_KEY_BUFF;
}

void make_key(u8 scancode)
{
    switch (scancode) {

    case ENTER:
        putc('\n');
        break;

    case LEFT_SHIFT:
    case RIGHT_SHIFT:
        DISPLAY_KEY_BUFF = UPPER_DISPLAY_KEY_BUFF;
        break;

    case CAPSLOCL:
        // eat the make scancode
        break;

    default:
        putc(DISPLAY_KEY_BUFF[scancode]);
    }
}

void break_key(u8 scancode)
{
    switch (scancode) {

    case ENTER:
        break;

    case LEFT_SHIFT:
    case RIGHT_SHIFT:
        DISPLAY_KEY_BUFF = LOWER_DISPLAY_KEY_BUFF;
        break;

    // bad, should use a flag.
    case CAPSLOCL:
        if (DISPLAY_KEY_BUFF == LOWER_DISPLAY_KEY_BUFF)
            DISPLAY_KEY_BUFF = UPPER_DISPLAY_KEY_BUFF;
        else
            DISPLAY_KEY_BUFF = LOWER_DISPLAY_KEY_BUFF;
        break;
    /*
    case ESC:
        __asm__ __volatile__("cli");
        __asm__ __volatile__("hlt");
        break;*/

    default:
        ;
    }
}

void keyboard_handler()
{

    u8 scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80) {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
        // xprintf("the released key scancode is %X \n", scancode);

        break_key(scancode & 0x7F);
    } else {
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

        make_key(scancode);
    }
}