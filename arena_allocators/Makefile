CFLAGS ?= -W -Wall -Wextra -Werror -Wundef -Wdouble-promotion \
          -Wformat-truncation -fno-common -Wconversion
DEBUGFLAGS ?= -g -O0 -fsanitize=address
SOURCES = main.c arena.c str.c

build: arena.out

debug: arena.debug

arena.out: $(SOURCES)
	gcc $(SOURCES) $(CFLAGS) -o $@

arena.debug: $(SOURCES)
	gcc $(SOURCES) $(CFLAGS) $(DEBUGFLAGS) -o $@

clean:
	rm -rf *.out *.debug
