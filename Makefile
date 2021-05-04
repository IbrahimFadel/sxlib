BIN=sxlib
SRC_FILE=sxlib.c sxlib_conn.c sxlib_io.c sxlib_api.c sxlib_util.c
CC=cc
LDFLAGS=
CFLAGS=-Wextra -Wall -std=c11

all:
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BIN) $(SRC_FILE)