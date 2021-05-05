#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sxlib_types.h"
#include "sxlib_conn.h"
#include "sxlib_api.h"

// #include <X11/Xatom.h>

int main()
{
    sxlib_connection_t *c = sxlib_connect();
    sxlib_screen_t scr = c->screens[0];
    sxlib_window_t *window = sxlib_create_window(c, 0, 0, 320, 240,
                                                 scr.root_id, scr.root_visual_id,
                                                 X11_BACKGROUND_PIXEL, (u32[]){0xcccccc});
    sxlib_map_window(c, window);
    sxlib_change_property(c, window, XA_WM_CLASS, XA_STRING, 8, 0, (u8 *)"hi");

    sleep(1);

    sxlib_window_attributes_t attribs = sxlib_get_window_attributes(c, window);

    u32 value_mask = X11_BORDER_PIXEL;
    u32 value_list[1] = {0xff0000};
    sxlib_change_window_attributes(c, window, value_mask, value_list);

    // u32 value_mask = X11_BACKGROUND_PIXEL;
    // u32 value = 0x000000;
    // sxlib_change_window_attributes(c, window, X11_BACKGROUND_PIXEL, (u32[]){0xff0000});

    sleep(1);

    // sxlib_change_property(c, window, 0, XA_WM_CLASS, XA_STRING, 8, "hi");

    // sxlib_destroy_window(c, window);

    while (1)
        sleep(1);

    return 0;
}