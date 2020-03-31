CC=gcc
CFLAGS=-Wall -ll -ly
BISON_DEBUG_FLAGS=--debug --verbose
CC_DEBUG_FLAGS=-g

all: same

src/parser.c: src/parser.y
ifdef YDEBUG
	bison -d -o $@ $^ $(BISON_DEBUG_FLAGS)
else
	bison -d -o $@ $^
endif
	
src/parser.h: src/parser.c

src/tokens.c: src/tokens.l
	flex -o $@ $^

same: src/parser.c src/main.c src/tokens.c src/util.c
ifdef DEBUG
	$(CC) -o $@ $^ $(CFLAGS) $(CC_DEBUG_FLAGS)
else
	$(CC) -o $@ $^ $(CFLAGS)
endif

clean:
	rm src/parser.c src/parser.h src/tokens.c same