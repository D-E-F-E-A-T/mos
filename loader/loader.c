extern void switch_to_pm();
extern void read_memory_map();

void _loader()
{
	read_memory_map();
	switch_to_pm();
}

