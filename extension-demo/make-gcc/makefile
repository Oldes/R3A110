EXT = demo-ext

CC = gcc
I = ../../src/include
R = ../bin/release
S = ../src

# Linux
#LIB = $(EXT).so
#CFLAGS += -I $I
#LDFLAGS += -shared -Xlinker "-soname=$(LIB)"

# Windows (MinGW):
LIB = $(EXT).dll
CFLAGS += -I $I
LDFLAGS += -mdll

all: $S/$(EXT).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $R/$(LIB) $S/$(EXT).c
	strip $R/$(LIB)
