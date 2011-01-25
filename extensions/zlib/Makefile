CC = gcc
CFLAGS = -DTO_WIN32 -I F:/git/R3/R3A110/src/include -I include 
LDFLAGS = -mdll -L . lib/zdll.lib

zlib-rxt.dll: zlib-rxt.c
	$(CC) $(CFLAGS) $(LDFLAGS) -O2 -o $@ $< .\lib\zdll.lib
