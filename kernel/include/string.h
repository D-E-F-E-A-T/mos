#ifndef STRING_H
#define STRING_H

/**
 * Get first argument address form ... list 
 * by adding 4 for first 32bit char * pointer 
 * @param  va_list
 * @param  arg0
 * @return
 */
#define va_strat(arg1, arg0) (arg1 = ((char *)&arg0) + sizeof(char *))


#define va_arg(pArg, data_type) ()


#include <int.h>

int memcpy(u8 *dst, u8 *src, u32 size);

int memset(u8 *dst, u8 data, u32 size);

#endif