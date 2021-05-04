#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sxlib_types.h"
#include "sxlib_conn.h"
#include "sxlib_api.h"

// enum
// {
//     X11_DEFAULT_BORDER = 0,
//     X11_DEFAULT_GROUP = 0,
//     X11_EXPOSURES_NOT_ALLOWED = 0,
//     X11_GC_GRAPHICS_EXPOSURES = 1 << 16,

//     X11_OPCODE_CREATE_WINDOW = 1,
//     X11_OPCODE_MAP_WINDOW = 8,
//     X11_OPCODE_CREATE_GC = 16,
//     X11_OPCODE_UNMAP_WINDOW = 10,
//     X11_OPCODE_GET_WINDOW_ATTRIBUTES = 3,

//     X11_CW_BACK_PIXEL = 1 << 1,
//     X11_CW_EVENT_MASK = 1 << 11,

//     X11_EVENT_MASK_KEY_PRESS = 1,
//     X11_EVENT_MASK_POINTER_MOTION = 1 << 6,
// };

// #define FATAL_ERROR(msg, ...)                     \
//     {                                             \
//         fprintf(stderr, msg "\n", ##__VA_ARGS__); \
//         exit(-1);                                 \
//     }

// static unsigned popcnt(uint32_t value)
// {
//     int count = 0;
//     while (value)
//     {
//         count += value & 1;
//         value >>= 1;
//     }
//     return count;
// }

// static void fatal_write(int fd, const void *buf, ssize_t count)
// {
//     if (write(fd, buf, count) != count)
//     {
//         FATAL_ERROR("Failed to write.");
//     }
// }

// static void fatal_read(int fd, void *buf, ssize_t count)
// {
//     if (recvfrom(fd, buf, count, 0, NULL, NULL) != count)
//     {
//         FATAL_ERROR("Failed to read.");
//     }
// }

// static uint32_t generate_id(sxlib_connection_t *conn)
// {
//     return conn->next_resource_id++;
// }

// conn->pixmap_formats = (sxlib_pixmap_format_t *)(conn->reply_body->vendor_string + conn->reply_body->vendor_len);
// conn->screens = (sxlib_screen_t *)(conn->pixmap_formats + conn->reply_body->num_pixmap_formats);
// conn->next_resource_id = conn->reply_body->id_base;
// return conn;

void init_gc(sxlib_connection_t *c, u32 value_mask, u32 *value_list)
{
    c->graphics_context_id = sxlib_generate_id(c);
    u16 flag_count = sxlib_popcount(value_mask);
    u16 len = 4 + flag_count;
    u32 packet[4 + 32]; // Ideally length would be 'len' but use 4 + 32 to keep length fixed.
    packet[0] = X11_OPCODE_CREATE_GC | (len << 16);
    packet[1] = c->graphics_context_id;
    packet[2] = c->screens[0].root_id;
    packet[3] = value_mask;
    for (int i = 0; i < flag_count; ++i)
    {
        packet[4 + i] = value_list[i];
    }

    sxlib_send_request(c, packet, len * 4);

    // const int response_len = 8;
    // u8 response[response_len];
    // read(conn->socket_fd, response, sizeof(response));
    // int i;
    // for (i = 0; i < response_len; i++)
    // {
    //     if (i > 0)
    //         printf(":");
    //     printf("%02X", response[i]);
    // }
    // printf("\n");
}

// sxlib_window_t *init_window(sxlib_connection_t *conn, u16 x, u16 y, u16 w, u16 h, u32 window_parent, u32 visual, u32 value_mask, u32 *value_list)
// {
//     sxlib_window_t *window = malloc(sizeof(sxlib_window_t));
//     window->id = generate_id(conn);
//     window->x = x;
//     window->y = y;
//     window->width = w;
//     window->height = h;

//     u16 flag_count = popcnt(value_mask);
//     u16 len = 8 + flag_count;
//     u32 packet[8 + 32];

//     packet[0] = X11_OPCODE_CREATE_WINDOW | len << 16;
//     packet[1] = window->id;
//     packet[2] = window_parent;
//     packet[3] = x | (y << 16);
//     packet[4] = w | (h << 16);
//     packet[5] = (X11_DEFAULT_BORDER << 16) | X11_DEFAULT_GROUP;
//     packet[6] = visual;
//     packet[7] = value_mask;
//     for (int i = 0; i < flag_count; ++i)
//     {
//         packet[8 + i] = value_list[i];
//     }

//     fatal_write(conn->socket_fd, packet, len * 4);

//     return window;
// }

// void map_window(x11_state_t *state, sxlib_window_t *window)
// {
//     int const len = 2;
//     u32 packet[len];
//     packet[0] = X11_OPCODE_MAP_WINDOW | (len << 16);
//     packet[1] = window->id;
//     fatal_write(state->socket_fd, packet, 8);

//     // u8 response[32];
//     // fatal_read(state->socket_fd, &response, sizeof(response));

//     // int i;
//     // for (i = 0; i < 32; i++)
//     // {
//     //     if (i > 0)
//     //         printf(":");
//     //     printf("%02X", response[i]);
//     // }
//     // printf("\n");
// }

// void unmap_window(x11_state_t *state, sxlib_window_t *window)
// {
//     int const len = 2;
//     u32 packet[len];
//     packet[0] = X11_OPCODE_UNMAP_WINDOW | (len << 16);
//     packet[1] = window->id;
//     fatal_write(state->socket_fd, packet, 8);
// }

// void get_window_attributes(x11_state_t *state, sxlib_window_t *window)
// {
//     const int len = 2;
//     u32 packet[len];
//     packet[0] = X11_OPCODE_GET_WINDOW_ATTRIBUTES | (len << 16);
//     packet[1] = window->id;
//     fatal_write(state->socket_fd, packet, 8);

//     // printf("Conn success: %d\n", state->connection_reply_header.success);
//     // printf("Conn version maj: %d\n", state->connection_reply_header.major_version);
//     // printf("Conn version min: %d\n", state->connection_reply_header.minor_version);

//     // const int response_len = 8;
//     // u8 response[response_len];
//     // read(state->socket_fd, response, sizeof(response));
//     // read(state->socket_fd, &response, sizeof(response));
//     // read(state->socket_fd, &response, sizeof(response));
//     // read(state->socket_fd, &response, sizeof(response));
//     // fatal_read(state->socket_fd, &response, sizeof(response));

//     // int i;
//     // for (i = 0; i < response_len; i++)
//     // {
//     //     if (i > 0)
//     //         printf(":");
//     //     printf("%02X", response[i]);
//     // }
//     // printf("\n");

//     // sxlib_get_window_attributes_response_t response;
//     // fatal_read(state->socket_fd, &response, sizeof(sxlib_get_window_attributes_response_t));

//     // printf("Win ID: %d\n", window->id);
//     // printf("Reply: %d\n", response.reply);
//     // printf("Backing store: %u\n", response.backing_store);
//     // printf("Sequence num: %d\n", response.sequence_number);
//     // printf("Reply len: %d\n", response.reply_length);

//     // sxlib_get_window_attributes_response_success_t *data = malloc(sizeof(sxlib_get_window_attributes_response_success_t));
//     // fatal_read(state->socket_fd, data, response.reply_length);

//     // printf("Vis id: %d\n", data->visual_id);

//     // printf("Visual ID: %d\n", response.visual_id);
//     // printf("Win ID: %d\n", response.id);
//     // if == 0)
//     // FATAL_ERROR("Connection reply indicated failure");
//     // int other = 40;
//     // u8 response[other];
//     // read(state->socket_fd, response, sizeof(response));
//     // // u8 response[32];
//     // // fatal_read(state->socket_fd, &response, sizeof(response));

//     // int i;
//     // for (i = 0; i < other; i++)
//     // {
//     //     if (i > 0)
//     //         printf(":");
//     //     printf("%02X", response[i]);
//     // }
//     // printf("\n");
// }

int main()
{
    sxlib_connection_t *c = sxlib_connect();
    sxlib_screen_t scr = c->screens[0];
    sxlib_window_t *window = sxlib_create_window(c, 0, 0, 320, 240,
                                                 scr.root_id, scr.root_visual_id,
                                                 X11_CW_BACK_PIXEL, (u32[]){0xcccccc});
    sxlib_map_window(c, window);

    while (1)
        sleep(1);

    return 0;
}