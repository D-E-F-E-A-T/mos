#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <port.h>
#include <pic8259.h>
#include <printf.h>

#define DISPLAY_KEY_BUFF_SIZE (0x200)

// Invisiable Keys scancode
#define ESC (0x01)
#define ENTER (0x1C)
#define CAPSLOCL (0x3A)
#define RIGHT_SHIFT (0x36)
#define LEFT_SHIFT (0x2A)

char UPPER_DISPLAY_KEY_BUFF[DISPLAY_KEY_BUFF_SIZE];
char LOWER_DISPLAY_KEY_BUFF[DISPLAY_KEY_BUFF_SIZE];
char* DISPLAY_KEY_BUFF;

void keyboard_init();

void keyboard_handler();

void make_key(u8 scancode);

void break_key(u8 scancode);

#endif
