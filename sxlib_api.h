#ifndef SXLIB_API_H
#define SXLIB_API_H

#include "sxlib_types.h"
#include "sxlib_util.h"
#include "sxlib_io.h"
#include <stdlib.h>
#include <string.h>

sxlib_window_t *sxlib_create_window(sxlib_connection_t *c, u16 x, u16 y, u16 w, u16 h, u32 window_parent, u32 visual, u32 value_mask, u32 *value_list);
void sxlib_destroy_window(sxlib_connection_t *c, sxlib_window_t *window);
void sxlib_map_window(sxlib_connection_t *c, sxlib_window_t *window);
void sxlib_unmap_window(sxlib_connection_t *c, sxlib_window_t *window); // idk why it still shows when this is called lol -- TODO read up on unmap request
void sxlib_change_window_attributes(sxlib_connection_t *c, sxlib_window_t *window, u32 value_mask, u32 *value_list);
sxlib_window_attributes_t sxlib_get_window_attributes(sxlib_connection_t *c, sxlib_window_t *window);
// void sxlib_change_property(sxlib_connection_t *c, sxlib_window_t *window, u8 mode, u32 property, u32 type, u8 format, void *data);
void sxlib_change_property(sxlib_connection_t *c, sxlib_window_t *window, u32 property, u32 type, u8 format, u8 mode, void *data);

#endif