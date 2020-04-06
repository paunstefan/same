CC=gcc
CFLAGS=-Wall

ifdef DEBUG
	CC_DEBUG_FLAGS=-g -DS_DEBUG=1
else
	CC_DEBUG_FLAGS=
endif

all: same

src/clex.c: src/clex.l
	flex -o $@ $^

same: src/main.c src/clex.c src/util.c src/hashtable.c
	$(CC) -o $@ $^ $(CFLAGS) $(CC_DEBUG_FLAGS)


clean:
	rm src/clex.c same