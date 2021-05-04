#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sxlib_types.h"
#include "sxlib_conn.h"
#include "sxlib_api.h"

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