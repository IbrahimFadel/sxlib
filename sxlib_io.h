#ifndef SXLIB_OUT_H
#define SXLIB_OUT_H

#include <sys/socket.h>
#include <unistd.h>
#include "sxlib_types.h"

int sxlib_send_request(sxlib_connection_t *c, const void *data, ssize_t size);
int sxlib_read_reply(sxlib_connection_t *c, void *data, ssize_t size);

// typedef struct iovec
// {
//     void *iov_base; /* Pointer to data.  */
//     size_t iov_len; /* Length of data.  */
// } iovec;

#endif