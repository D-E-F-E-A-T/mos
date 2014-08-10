#include <string.h>

int mcpy(u8 *dst, u8 *src, u32 size)
{
	for (u32 i = 0; i < size; ++i) {
		dst[i] = src[i];
	}

	return 0;
}

int mset(u8 *dst, u8 data, u32 size)
{
	for (u32 i = 0; i < size; ++i) {
		dst[i] = data;
	}

	return 0;
}