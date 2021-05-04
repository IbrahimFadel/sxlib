#ifndef SXLIB_TYPES_H
#define SXLIB_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define X11_OPCODE_CREATE_WINDOW 1
#define X11_OPCODE_MAP_WINDOW 8
#define X11_OPCODE_CREATE_GC 55

#define X11_CW_BACK_PIXEL 1 << 1
#define X11_GC_GRAPHICS_EXPOSURES 1 << 16
#define X11_EXPOSURES_NOT_ALLOWED 0

typedef struct sxlib_pixmap_format_t
{
    u8 depth;
    u8 bpp;
    u8 scanline_pad;
    u8 pad[5];
} sxlib_pixmap_format_t;

typedef struct sxlib_screen_t
{
    u32 root_id;
    u32 colormap;
    u32 white, black;
    u32 input_mask;
    u16 width, height;
    u16 width_mm, height_mm;
    u16 maps_min, maps_max;
    u32 root_visual_id;
    u8 backing_store;
    u8 save_unders;
    u8 depth;
    u8 allowed_depths_len;
} sxlib_screen_t;

typedef struct sxlib_connection_reply_header_t
{
    u8 status;
    u8 pad0;
    u16 protocol_major_version;
    u16 protocol_minor_version;
    u16 length;
} sxlib_connection_reply_header_t;

typedef struct sxlib_connection_reply_success_body_t
{

    u32 release_number;
    u32 resource_id_base;
    u32 resource_id_mask;
    u32 motion_buffer_size;
    u16 vendor_len;
    u16 maximum_request_length;
    u8 num_screens;
    u8 num_pixmap_formats;
    u8 image_byte_order;
    u8 bitmap_format_bit_order;
    u8 bitmap_format_scanline_unit;
    u8 bitmap_format_scanline_pad;
    u8 min_keycode;
    u8 max_keycode;
    u32 pad1;
    char vendor_string[1];
} sxlib_connection_reply_success_body_t;

typedef struct sxlib_setup_request_t
{
    u8 byte_order;
    u8 pad0;
    u16 major_version;
    u16 minor_version;
    u16 auth_name_len;
    u16 auth_data_len;
    u8 pad1[2];
} sxlib_setup_request_t;

typedef struct sxlib_connection_t
{
    sxlib_connection_reply_header_t reply_header;
    sxlib_connection_reply_success_body_t *reply_body;
    int socket_fd;

    sxlib_pixmap_format_t *pixmap_formats; // Points into connection_reply_success_body.
    sxlib_screen_t *screens;               // Points into connection_reply_success_body.

    u32 next_resource_id;
    u32 graphics_context_id;
} sxlib_connection_t;

typedef struct sxlib_window_t
{
    u32 id;
    u16 x, y;
    u16 width, height;
    int has_error;
} sxlib_window_t;

#endif