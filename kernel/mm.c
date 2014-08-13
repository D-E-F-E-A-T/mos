#include <mm.h>

void setup_sys_param()
{
	mem_map_entry = (MEM_MAP_ENTRY *)P_MEM_MAP_ENTRY;
	mem_map_entry_count = (u32 *)P_MEM_MAP_ENTRY_COUNT;
}