#ifndef MEMORY_H
#define MEMORY_H
#include <int.h>

int memcpy(uint8 *dst, uint8 *src, uint16 size)
{

}

int memset(uint8 *dst, uint8 data, uint16 size)
{
	for (int i = 0; i < size; ++i) {
		dst[i] = data;
	}
}

#endif