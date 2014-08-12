#ifndef STRING_H
#define STRING_H

#include <int.h>

int mcpy(u8 *dst, u8 *src, u32 size);

int mset(u8 *dst, u8 data, u32 size);

int mcmp(u8 *m1, u8 *m2, u32 size);

#endif