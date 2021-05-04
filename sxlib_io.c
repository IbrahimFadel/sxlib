#include "sxlib_io.h"

int sxlib_send_request(sxlib_connection_t *c, const void *data, ssize_t size)
{
    int res = write(c->socket_fd, data, size);
    if (res != size)
        return 1;
    return 0;
}

int sxlib_read_reply(sxlib_connection_t *c, void *data, ssize_t size)
{
    int res = recvfrom(c->socket_fd, data, size, 0, NULL, NULL);
    if (res != size)
        return 1;
    return 0;
}