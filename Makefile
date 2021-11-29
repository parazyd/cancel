LIBS=`pkg-config --cflags --libs gtk+-2.0`

all: cancel

cancel: cancel.c
	gcc -o $@ $^ -Wall -Wextra $(LIBS)

uninstall:
	rm -f /usr/share/applications/cancel.desktop
	rm -f /usr/bin/cancel
	rm -rf /usr/share/karens

install: uninstall
	cp cancel.desktop /usr/share/applications/cancel.desktop
	cp cancel /usr/bin/cancel
	cp -r karens /usr/share/karens

clean:
	rm -f cancel
