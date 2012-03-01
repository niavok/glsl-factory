CC=gcc
CFLAGS=-W -Wall -pedantic -g  -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pango-1.0 -I /usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0  -I/usr/include/gtkglext-1.0 
LDFLAGS=-g -lgtk-3 -lSDL -lGL
EXEC=glsl-factory
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

glsl-factory: $(OBJ)
	$(CC) -o glsl-factory $(OBJ) $(LDFLAGS)

glsl-factory.o: gui.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o
    
mrproper: clean
	rm $(EXEC)
