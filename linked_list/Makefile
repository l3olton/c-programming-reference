CFLAGS ?= -W -Wall -Wextra -Werror -Wundef -Wdouble-promotion \
          -Wformat-truncation -fno-common -Wconversion
DEBUGFLAGS ?= -g -O0 -fsanitize=address

ARENA = $(abspath ../arena_allocator)

SOURCES = main.c linkedlist.c $(ARENA)/arena.c

build: linkedlist.out

debug: linkedlist.debug

linkedlist.out: $(SOURCES)
	gcc $(SOURCES) $(CFLAGS) -o $@

linkedlist.debug: $(SOURCES)
	gcc $(SOURCES) $(CFLAGS) $(DEBUGFLAGS) -o $@

clean:
	rm -rf *.out *.debug
