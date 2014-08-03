#define LF	(10)
#define CR 	(13)
#define NUL	(0)


#include "screen.h"

int get_cursor(uint16 *row, uint16 *col)
{
	return STATUS_SUCCESS;
}

int set_cursor(uint16 row, uint16 col)
{
	g_screen.row = row;
	g_screen.col = col;

	return STATUS_SUCCESS;
}

int new_line()
{
	g_screen.row++;
	g_screen.col = 0;
	return STATUS_SUCCESS;
}

int putc(char c)
{
	if (c < ' ') {

		// invisiable characters

		switch (c) {
			case LF:
			case CR:
				new_line();
				break;
				
			default:
				;
		}

	} else {
		
		// visiable characters

		*((uint8 *)SCREEN_BASE + 
			(g_screen.col + g_screen.row * SCREEN_COLS) * 2) = c;

		g_screen.col++;

	}

	return STATUS_SUCCESS;
}

int puts(char *s)
{
	while (*s)
		putc(*s++);

	return STATUS_SUCCESS;
}

int printf(char *fmt, ...)
{
	return STATUS_SUCCESS;
}

int clear_screen()
{
	g_screen.row = 0;
	g_screen.col = 0;
	g_screen.color = COLOR_SCHEME;

	return STATUS_SUCCESS;
}
