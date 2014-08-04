/*
	Abstraction of screen memory at 0xB8000.
*/
#ifndef SCREEN_H
#define SCREEN_H

#include "../std/int.h"
#include "../std/status.h"

#define LF	(10)
#define CR 	(13)
#define NUL	(0)


#define SCREEN_BASE		(0xB8000)
#define SCREEN_ROWS		(25)
#define SCREEN_COLS		(80)

#define COLOR_SCHEME	(0x0F)	// 	White on Black 0x0F

// from https://github.com/44670/entOS/blob/master/src/kernel/console.cpp
#define GET_ADDR(x, y)	((uint8 *)SCREEN_BASE + ((x) + (y) * 80) * 2)


typedef struct
{
	uint16 row;
	uint16 col;
	uint8 color;

} SCREEN;

static SCREEN g_screen;

int get_cursor(uint16 *row, uint16 *col);

int set_cursor(uint16 row, uint16 col);

int new_line();

int putc(char c);

int puts(char *s);

int printf(char *fmt, ...);

int clear_screen();


#endif