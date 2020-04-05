CC=gcc
CFLAGS=-Wall -ly

ifdef DEBUG
	CC_DEBUG_FLAGS=-g
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