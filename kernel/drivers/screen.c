#include <screen.h>

int get_cursor_row()
{
	return g_screen.row;
}

int get_cursor_col()
{
	return g_screen.col;
}

int set_cursor(u16 row, u16 col)
{
	g_screen.row = row;
	g_screen.col = col;

	update_cursor(row, col);

	return STATUS_SUCCESS;
}

int new_line()
{
	set_cursor(get_cursor_row() + 1, 0);
	
	if (get_cursor_row() >= SCREEN_ROWS)
		scroll_up(1);

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

		*(SCREEN_BASE + 
			(get_cursor_col() + get_cursor_row() * SCREEN_COLS) * 2) = c;

		// g_screen.col++;
		set_cursor(get_cursor_row(), get_cursor_col() + 1);

	}

	return STATUS_SUCCESS;
}

int puts(char *s)
{
	while (*s)
		putc(*s++);

	return STATUS_SUCCESS;
}

int clear_screen()
{
	int i;

	set_cursor(0, 0);
	g_screen.color = COLOR_SCHEME;

	for (i = 0; i < SCREEN_ROWS; ++i)
		clear_row(i);
			
	return STATUS_SUCCESS;
}

/**
 * scroll up the screen in specific rows.
 * @param rows [how many row will scroll up]
 */
void scroll_up(int rows)
{
	u8 *src = SCREEN_BASE + rows * SCREEN_COLS * 2;
	u8 *dst = SCREEN_BASE;

	set_cursor(get_cursor_row() - rows, get_cursor_col());
	mcpy(dst, src, SCREEN_COLS * SCREEN_ROWS * 2);

	for (int i = 0; i < rows; i++)
		clear_row(SCREEN_ROWS - 1 - i);
}

/**
 * clear content in a specific row.
 * @param  row [line number]
 * @return     [kernel status]
 */
int clear_row(int row)
{
	for (int i = 0; i < SCREEN_COLS; ++i) {
			*(SCREEN_BASE + (row * SCREEN_COLS + i) * 2 + 1)	= g_screen.color;
			*(SCREEN_BASE + (row * SCREEN_COLS + i) * 2)		= ' ';
	}
	return STATUS_SUCCESS;
}


void update_cursor(int row, int col)
{
    unsigned short position=(row*80) + col;
 
    // cursor LOW port to vga INDEX register
    outportb(0x3D4, (u8)0x0F);
    outportb(0x3D5, (u8)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    outportb(0x3D4, (u8)0x0E);
    outportb(0x3D5, (u8)((position>>8)&0xFF));
}