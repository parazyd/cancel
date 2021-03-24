all:
	gcc -o cancel $(shell pkg-config --cflags --libs gtk+-3.0) cancel.c

clean:
	rm -f cancel
