#include "sxlib_util.h"

int sxlib_popcount(u32 mask)
{
    uint32_t y;
    y = (mask >> 1) & 033333333333;
    y = mask - y - ((y >> 1) & 033333333333);
    return ((y + (y >> 3)) & 030707070707) % 077;
}

u32 sxlib_generate_id(sxlib_connection_t *c)
{
    return c->next_resource_id++;
}