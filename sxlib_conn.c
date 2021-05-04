#include "sxlib_conn.h"

int sxlib_connect_to_display(int display)
{
    int fd;
    char display_string[16];
    char file[17 + 16] = "/tmp/.X11-unix/X";

    sprintf(display_string, "%d", display);
    strcat(file, display_string);

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
        FATAL_ERROR("Could not create socket");

    struct sockaddr_un serv_addr = {0};
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file);
    int _conn = connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (_conn < 0)
        FATAL_ERROR("Could not connect");

    return fd;
}

void sxlib_init_gc(sxlib_connection_t *c)
{
    c->graphics_context_id = sxlib_generate_id(c);
    u16 flag_count = sxlib_popcount(X11_GC_GRAPHICS_EXPOSURES);
    u16 len = 4 + flag_count;
    u32 packet[4 + 32];
    packet[0] = X11_OPCODE_CREATE_GC | (len << 16);
    packet[1] = c->graphics_context_id;
    packet[2] = c->screens[0].root_id;
    packet[3] = X11_GC_GRAPHICS_EXPOSURES;
    packet[4] = X11_EXPOSURES_NOT_ALLOWED;

    sxlib_send_request(c, packet, len * 4);
}

sxlib_connection_t *sxlib_connect()
{
    sxlib_connection_t *c = malloc(sizeof(sxlib_connection_t));
    c->socket_fd = sxlib_connect_to_display(0);

    if (sxlib_write_setup(c))
        FATAL_ERROR("Error writing setup");
    if (sxlib_read_setup(c))
        FATAL_ERROR("Error reading setup reply");

    c->pixmap_formats = (sxlib_pixmap_format_t *)(c->reply_body->vendor_string + c->reply_body->vendor_len);
    c->screens = (sxlib_screen_t *)(c->pixmap_formats + c->reply_body->num_pixmap_formats);
    c->next_resource_id = c->reply_body->resource_id_base;

    sxlib_init_gc(c);

    return c;
}

int sxlib_write_setup(sxlib_connection_t *c)
{
    sxlib_setup_request_t req;

    char xauth_cookie[4096];
    FILE *xauth_file = fopen("/home/ibrahim/.Xauthority", "rb");
    if (!xauth_file)
    {
        FATAL_ERROR("Couldn't open .Xauthority.");
    }
    size_t xauth_len = fread(xauth_cookie, 1, sizeof(xauth_cookie), xauth_file);
    if ((int)xauth_len < 0)
    {
        FATAL_ERROR("Couldn't read from .Xauthority.");
    }
    fclose(xauth_file);

    req.byte_order = 'l'; // Little endian
    req.major_version = 11;
    req.minor_version = 0; // X Protocol 11.0
    req.auth_name_len = 18;
    req.auth_data_len = 16;

    if (sxlib_send_request(c, &req, sizeof(req)))
        return 1;
    if (sxlib_send_request(c, "MIT-MAGIC-COOKIE-1\0\0", 20))
        return 1;
    if (sxlib_send_request(c, xauth_cookie + xauth_len - 16, 16))
        return 1;

    return 0;
}

int sxlib_read_setup(sxlib_connection_t *c)
{
    if (sxlib_read_reply(c, &c->reply_header, sizeof(sxlib_connection_reply_header_t)))
        return 1;

    if (c->reply_header.status == 0)
        return 1;

    c->reply_body = malloc(c->reply_header.length * 4);

    switch (c->reply_header.status)
    {
    case 0: // Failed
        return 1;
    case 2: // Authenticate
        return 1;
    }

    if (sxlib_read_reply(c, c->reply_body, c->reply_header.length * 4))
        return 1;

    return 0;
}