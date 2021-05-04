# sxlib (simple x library)

An X client library written in C

This is just my attempt at implementing the X client protocol. I probably won't implement too much, or make it extremely good.
Here's what I've got so far:

```c
int main()
{
    // Connect to X server
    sxlib_connection_t *c = sxlib_connect();
    sxlib_screen_t scr = c->screens[0];
    
    // Create a window at X:Y - 0:0, W:H - 320:240, BG COLOR - 0xcccccc
    sxlib_window_t *window = sxlib_create_window(c, 0, 0, 320, 240,
                                                 scr.root_id, scr.root_visual_id,
                                                 X11_CW_BACK_PIXEL, (u32[]){0xcccccc});
    // Map the window (make it visible)
    sxlib_map_window(c, window);

    // Wait so you can see the window
    while (1)
        sleep(1);

    return 0;
}
```
