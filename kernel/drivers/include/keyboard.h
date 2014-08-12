#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <port.h>
#include <pic8259.h>
#include <printf.h>

// bad, testing hack
#define DISPLAY_KEY_BUFF	((u8 *)0x20000)

// Nonvisiable Keys scancode
#define ENTER				(0x1C)

void keyboard_init();

void keyboard_handler();

void do_key(u8 scancode);

#endif