# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: main -lm

main: main.o pixel_operations.o display.o segmentation.o pretraitement.o -lm
#display: display.o
#pixel_operations: pixel_operations.o
pretraitement: display.o pixel_operations.o pretraitement.o -lm
segmentation: display.o pixel_operations.o segmentation.o  

pretraitement.o: pixel_operations.h
segmentation.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} cases/*.txt
	${RM} display
	${RM} main
	${RM} pixel_operations
	${RM} segmentation
	${RM} pretraitement

# END