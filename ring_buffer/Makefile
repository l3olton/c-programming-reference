CFLAGS ?= -W -Wall -Wextra -Werror -Wundef -Wdouble-promotion \
          -Wformat-truncation -fno-common -Wconversion
DEBUGFLAGS ?= -g -O0 -fsanitize=address
SOURCES = main.c ring_buffer.c

build: ringbuf.out

debug: ringubf.debug

ringbuf.out: $(SOURCES)
	gcc $(SOURCES) $(CFLAGS) -o $@

ringbuf.debug: $(SOURCES)
	gcc $(SOURCES) $(CFLAGS) $(DEBUGFLAGS) -o $@

clean:
	rm -rf *.out *.debug
