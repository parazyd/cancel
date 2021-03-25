all:
	gcc -o cancel $(shell pkg-config --cflags --libs gtk+-2.0) -Wall -Wextra cancel.c

clean:
	rm -f cancel
