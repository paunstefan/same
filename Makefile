CC=gcc
CFLAGS=-Wall
PREFIX=/usr/local
NAME=same
SRC=src/main.c src/util.c src/hashtable.c
LEX_FILE=src/clex.l
LEX_SRC=src/clex.c

ifdef DEBUG
	CC_DEBUG_FLAGS=-g -DS_DEBUG=1
else
	CC_DEBUG_FLAGS=
endif

all: $(NAME)

$(LEX_SRC): $(LEX_FILE)
	flex -o $@ $^

$(NAME): $(SRC) $(LEX_SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(CC_DEBUG_FLAGS)

install: $(NAME)
	cp $< $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(NAME)

clean:
	rm $(LEX_SRC) $(NAME)