#ifndef MM_H
#define MM_H

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

void setup_sys_param();

#endif