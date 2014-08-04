/*
	Abstraction of screen memory at 0xB8000.
*/
#ifndef SCREEN_H
#define SCREEN_H

#include <int.h>
#include <port.h>
#include <status.h>

#define LF	(10)
#define CR 	(13)
#define NUL	(0)


#define SCREEN_BASE		((u8 *)0xB8000)
#define SCREEN_ROWS		(25)
#define SCREEN_COLS		(80)

#define COLOR_SCHEME	(0x0F)	// 	White on Black 0x0F

// from https://github.com/44670/entOS/blob/master/src/kernel/console.cpp
#define GET_ADDR(x, y)	((u8 *)SCREEN_BASE + ((x) + (y) * 80) * 2)


typedef struct
{
	u16 row;
	u16 col;
	u8 color;

} SCREEN;

static SCREEN g_screen;

int get_cursor_row();

int get_cursor_col();

int set_cursor(u16 row, u16 col);

int new_line();

int putc(char c);

int puts(char *s);

int printf(char *fmt, ...);

int clear_screen();

int clear_row();

 /* void update_cursor(int row, int col)
  * by Dark Fiber
  */
 void update_cursor(int row, int col);

#endif