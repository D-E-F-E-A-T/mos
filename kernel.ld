
ENTRY(start)

SECTIONS
{
	. = 0x00100000;
	PROVIDE( kern_start = 0xC0000000 );
	PAGING_OFFSET = 0xC0000000;

	.init.text BLOCK(4K) :
	{
		*(.init.text)
		. = ALIGN(4K);
	}

	.init.data BLOCK(4K) :
	{
		*(.init.data)
		. = ALIGN(4K);
	}

	. += PAGING_OFFSET;
	.text BLOCK(4K) : AT(ADDR(.text) - PAGING_OFFSET)
	{
		*(.text)
		. = ALIGN(4K);
	}
	
	
	/* Read-write data (initialized) */
	.data BLOCK(4K) : AT(ADDR(.data) - PAGING_OFFSET)
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4K);
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : AT(ADDR(.bss) - PAGING_OFFSET)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
		. = ALIGN(4K);
	}

	PROVIDE( kern_end = . );

	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}