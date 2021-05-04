#ifndef SXLIB_API_H
#define SXLIB_API_H

#include "sxlib_types.h"
#include "sxlib_util.h"
#include "sxlib_io.h"
#include <stdlib.h>

sxlib_window_t *sxlib_create_window(sxlib_connection_t *c, u16 x, u16 y, u16 w, u16 h, u32 window_parent, u32 visual, u32 value_mask, u32 *value_list);
void sxlib_map_window(sxlib_connection_t *c, sxlib_window_t *window);

#endif