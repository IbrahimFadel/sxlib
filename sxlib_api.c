#include "sxlib_api.h"

sxlib_window_t *sxlib_create_window(sxlib_connection_t *c, u16 x, u16 y, u16 w, u16 h, u32 window_parent, u32 visual, u32 value_mask, u32 *value_list)
{
    sxlib_window_t *window = malloc(sizeof(sxlib_window_t));
    window->id = sxlib_generate_id(c);
    window->x = x;
    window->y = y;
    window->width = w;
    window->height = h;

    u16 flag_count = sxlib_popcount(value_mask);
    u16 len = 8 + flag_count;
    u32 packet[8 + 32];

    packet[0] = X11_OPCODE_CREATE_WINDOW | len << 16;
    packet[1] = window->id;
    packet[2] = window_parent;
    packet[3] = x | (y << 16);
    packet[4] = w | (h << 16);
    packet[5] = (0 << 16) | 1;
    packet[6] = visual;
    packet[7] = value_mask;
    for (int i = 0; i < flag_count; ++i)
    {
        packet[8 + i] = value_list[i];
    }

    sxlib_send_request(c, packet, len * 4);

    return window;
}

void sxlib_map_window(sxlib_connection_t *c, sxlib_window_t *window)
{
    const int len = 2;
    u32 packet[len];
    packet[0] = X11_OPCODE_MAP_WINDOW | (len << 16);
    packet[1] = window->id;
    sxlib_send_request(c, packet, 8);
}