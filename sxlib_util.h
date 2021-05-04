#ifndef SXLIB_UTIL_H
#define SXLIB_UTIL_H

#include "sxlib_types.h"

int sxlib_popcount(u32 mask);
u32 sxlib_generate_id(sxlib_connection_t *c);

#endif