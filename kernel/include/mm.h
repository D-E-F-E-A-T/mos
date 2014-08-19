#ifndef MM_H
#define MM_H

/**
 * First ~640 KB in physical memory is free for use
 * another free space start from 1M
 * 
 * Base: 00000000 00000000 Limit: 00000000 0009F000 Type: 00000001
 * Base: 00000000 0009F000 Limit: 00000000 00001000 Type: 00000002
 * Base: 00000000 000E8000 Limit: 00000000 00018000 Type: 00000002
 * Base: 00000000 00100000 Limit: 00000000 01EF0000 Type: 00000001
 * Base: 00000000 01FF0000 Limit: 00000000 00010000 Type: 00000003
 * Base: 00000000 FFFC0000 Limit: 00000000 00040000 Type: 00000002
 */

#include <int.h>

#define P_MEM_MAP_ENTRY_COUNT		(0x500)
#define P_MEM_MAP_ENTRY				(0x504)


typedef struct 
{
	u32 base_low;
	u32 base_high;
	u32 limit_low;
	u32 limit_high;
	u32 type;
	u32 extend;
} __attribute__((packed)) MEM_MAP_ENTRY;

// memory mapping information entry array.
MEM_MAP_ENTRY *mem_map_entry;
// The array size of memory mapping information.
u32 *mem_map_entry_count;

// reference to intel 32 bit paging

typedef struct 
{
	u32 ignored_0			: 3;
	u32 pg_write_through	: 1;
	u32 pg_disalbe_cache	: 1;
	u32 ignored_1			: 7;
	u32 pg_dir_base			: 20;		/* 4K aligned directory */
} __attribute__((packed)) dr3_t;

typedef struct 
{
	u32 present : 1;					/* the target table is present or not */
	u32 read_write : 1;					/* set for allow read/write */
	u32 user_privi : 1;					/* set for allow user level access */
	u32 write_through : 1;		
	u32 disable_cache : 1;
	u32 accessed : 1;					//
	u32 ignored_0 : 1;
	u32 page_size : 1;
	u32 ignored_1 : 4;
	u32 pg_table_base : 20;				/* 4K aligned table */
} __attribute__((packed)) pg_dir_entry_t;

typedef struct 
{
	u32 present : 1;
	u32 read_write : 1;
	u32 user_privi : 1;
	u32 write_through : 1;		
	u32 disable_cache : 1;
	u32 accessed : 1;	
	u32 dirty : 1;
	u32 pat : 1;
	u32 global : 1;
	u32 ignored : 3;
	u32 pg_base : 20;
} __attribute__((packed)) pg_table_entry_t;


void setup_sys_param();

#endif