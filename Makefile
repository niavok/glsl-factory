CC=gcc
CFLAGS=-W -Wall -pedantic -g
LDFLAGS=-g -lSDL -lGL -lGLU
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
	rm $(OBJ)
    
mrproper: clean
	rm $(EXEC)
