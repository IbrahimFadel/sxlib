#ifndef SXLIB_CONN_H
#define SXLIB_CONN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <assert.h>
#include "sxlib_types.h"
#include "sxlib_io.h"
#include "sxlib_util.h"

#define FATAL_ERROR(msg, ...)                     \
    {                                             \
        fprintf(stderr, msg "\n", ##__VA_ARGS__); \
        exit(-1);                                 \
    }

#define SXLIB_PAD(i) (-(i)&3)

int sxlib_connect_to_display(int display);
sxlib_connection_t *sxlib_connect();
int sxlib_write_setup(sxlib_connection_t *c);
int sxlib_read_setup(sxlib_connection_t *c);
void sxlib_init_gc(sxlib_connection_t *c);

#endif