all:
	gcc -o cancel cancel.c -Wall -Wextra $(shell pkg-config --cflags --libs gtk+-2.0)

clean:
	rm -f cancel
