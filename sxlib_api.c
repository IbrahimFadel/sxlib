#include "sxlib_api.h"
#include <stdio.h>

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
    packet[5] = 10 | (1 << 16);
    packet[6] = visual;
    packet[7] = value_mask;
    for (int i = 0; i < flag_count; ++i)
    {
        packet[8 + i] = value_list[i];
    }

    sxlib_send_request(c, packet, len * 4);

    return window;
}

void sxlib_destroy_window(sxlib_connection_t *c, sxlib_window_t *window)
{
    const int len = 2;
    u32 packet[len];
    packet[0] = X11_OPCODE_DESTROY_WINDOW | (len << 16);
    packet[1] = window->id;
    sxlib_send_request(c, packet, sizeof(packet));
}

void sxlib_map_window(sxlib_connection_t *c, sxlib_window_t *window)
{
    const int len = 2;
    u32 packet[len];
    packet[0] = X11_OPCODE_MAP_WINDOW | (len << 16);
    packet[1] = window->id;
    sxlib_send_request(c, packet, sizeof(packet));
}

void sxlib_unmap_window(sxlib_connection_t *c, sxlib_window_t *window)
{
    const int len = 2;
    u32 packet[len];
    packet[0] = X11_OPCODE_UNMAP_WINDOW | (len << 16);
    packet[1] = window->id;
    sxlib_send_request(c, packet, sizeof(packet));
}

void sxlib_change_window_attributes(sxlib_connection_t *c, sxlib_window_t *window, u32 value_mask, u32 *value_list)
{
    u16 flag_count = sxlib_popcount(value_mask);
    const int len = 3 + flag_count;
    u32 packet[len];
    packet[0] = X11_OPCODE_CHANGE_WINDOW_ATTRIBUTES | (len << 16);
    packet[1] = window->id;
    packet[2] = value_mask;
    for (int i = 0; i < flag_count; ++i)
    {
        packet[3 + i] = value_list[i];
    }

    sxlib_send_request(c, packet, sizeof(packet));
}

sxlib_window_attributes_t sxlib_get_window_attributes(sxlib_connection_t *c, sxlib_window_t *window)
{
    const int len = 2;
    u32 packet[len];
    packet[0] = X11_OPCODE_GET_WINDOW_ATTRIBUTES | (len << 16);
    packet[1] = window->id;

    sxlib_send_request(c, packet, sizeof(packet));

    sxlib_reply_t reply;
    sxlib_read_reply(c, &reply, sizeof(reply));

    sxlib_window_attributes_t attribs;
    sxlib_read_reply(c, &attribs, sizeof(attribs));

    return attribs;
}

void sxlib_change_property(sxlib_connection_t *c, sxlib_window_t *window, u32 property, u32 type, u8 format, u8 mode, void *data)
{
    // const char *str1 = "hello";
    // const char *str2 = "Hello";

    // size_t len_str1 = strlen(str1);
    // size_t len_str2 = strlen(str2);

    // char *class_string;
    // char *s;

    // if ((class_string = s = malloc(len_str1 + len_str2 + 2)))
    // {
    //     if (len_str1)
    //     {
    //         strcpy(s, str1);
    //         s += len_str1 + 1;
    //     }
    //     else
    //         *s++ = '\0';
    //     if (len_str2)
    //         strcpy(s, str2);
    //     else
    //         *s = '\0';
    // }

    const char *class_string = "hel\0Hel";

    printf("class string: %s\n", class_string);

    sxlib_change_property_request_t req;
    req.opcode = X11_OPCODE_CHANGE_PROPERTY;
    req.mode = mode;
    // req.req_len = 7;
    // req.req_len = 6 + (len_str1 + len_str2 + 2 + 0) / 4;
    // req.req_len = ((long)(len_str1 + len_str2 + 2) + 3) >> 2;
    req.req_len = (24 + 8);
    req.window = window->id;
    req.property = property;
    req.type = type;
    req.format = format;
    req.data_len = 8;
    req.data = (u8 *)class_string;
    // req.data = (u8 *)class_string;

    sxlib_send_request(c, &req, sizeof(req));
}