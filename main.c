#include <stdio.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <math.h>

#include "pixel_operations.h"
#include "display.h"

#include "segmentation.h"
#include "pretraitement.h"




int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		if (argc == 1)
		{
			//SDL_Surface* sudoku = pretraitement("images/my_image2.jpg");
			init_sdl();
			SDL_Surface* image = load_image("images/my_image1.jpg");
			doneAll(image);// sudoku);
		}
		else
		{
			SDL_Surface* sudoku = pretraitement(argv[1]);
			doneAll(sudoku);
		}
	}
	else
	{
		errx(1, "put the path of sudoku image");
	}

	return 0;
}


