#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <port.h>
#include <pic8259.h>
#include <printf.h>

// bad, testing hack
#define DISPLAY_KEY_BUFF	((u8 *)0x20000)

void keyboard_init();

void keyboard_handler();

void display_key(u8 scancode);

#endif