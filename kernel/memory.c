#include <memory.h>

int memcpy(u8 *dst, u8 *src, u32 size)
{
	for (u32 i = 0; i < size; ++i) {
		dst[i] = src[i];
	}
}

int memset(u8 *dst, u8 data, u32 size)
{
	for (u32 i = 0; i < size; ++i) {
		dst[i] = data;
	}
}