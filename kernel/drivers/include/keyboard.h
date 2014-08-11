#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <port.h>
#include <pic8259.h>
#include <printf.h>

void keyboard_init();

void keyboard_handler();

#endif