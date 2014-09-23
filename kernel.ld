
ENTRY(start)

SECTIONS
{
	. = 0x00100000;
	PROVIDE( kern_start = . );

	.text BLOCK(1K) : ALIGN(1K)
	{
		*(.text)
	}
	
	
	/* Read-only data. */
	.rodata BLOCK(1K) : ALIGN(1K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(1K) : ALIGN(1K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(1K) : ALIGN(1K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	PROVIDE( kern_end = . );

	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}