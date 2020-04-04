CC=gcc
CFLAGS=-Wall -ly
CC_DEBUG_FLAGS=-g

all: same

src/clex.c: src/clex.l
	flex -o $@ $^

same: src/main.c src/clex.c src/util.c
ifdef DEBUG
	$(CC) -o $@ $^ $(CFLAGS) $(CC_DEBUG_FLAGS)
else
	$(CC) -o $@ $^ $(CFLAGS)
endif

clean:
	rm  src/clex.c same