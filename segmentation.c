# include "pixel_operations.h"
# include <err.h>	
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
#include "display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//to print a case of the sudoku matrice
/*void printcase(double casee[], int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%d", (int)casee[i * width + j]);
		}
		printf("\n");
	}
}*/

//trying to save a case into a .jpg
/*void savecase(double Cases[], int width, int height)
{
	Uint8 color;
	Uint32 pixel;
	init_sdl();

	SDL_Surface* image = load_image("images/my_image1.jpg");
	SDL_Surface* screen = display_image(image);

	int w = image->w;
	int h = image->h;
	
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (i < height && j < width)
			{
				color = (Uint8)Cases[i * width + j];
			}
			else
			{
				color = 0;
			}
			pixel = SDL_MapRGB(image->format, color, color, color);
			put_pixel(image, j, i, pixel);
		}
	}
	update_surface(screen, image);
	SDL_FreeSurface(image);

	SDL_FreeSurface(screen);
}*/

int savecasee(double casee[], int width, int height, char* filename)
{
	FILE* filedone;
	filedone = fopen(filename, "w");

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			fprintf(filedone, "%d", (int)casee[i * width + j]);
		}
		fprintf(filedone, "\n");
	}

	fclose(filedone);
	return 0;
}

int doneAll(SDL_Surface* image_surface)
{

	int width = image_surface->w;
	int height = image_surface->h;

	int tableau[height][width];

	Uint8 r, g, b;
	Uint32 pixel;
	printf("loading SUDOKU in matrice :\n");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			pixel = get_pixel(image_surface, x, y);
			SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			if (r > 127)
			{
				// We have a white pixel
				tableau[y][x] = (int) 1;
			}
			else
			{
				// We have a black pixel
				tableau[y][x] = (int) 0;
			}
		}
	}
	printf("SUDOKU LOADED !\n");


	//////////////////////////////////////////////////////////////
	//PRINT LE SUDOKU ENTIER

	//uncomment to print the all matrice of sudoku on the terminal
	/*
	printf("Do you want to print the matrice : for yes press 1");
	int print;
	scanf("%d", &print);
	printf("%d", print);
	if (print == 1)
	{
		printf("Print SUDOKU :\n");

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j % 5 == 0)
					printf("%d", tableau[i][j]);
			}

			printf("\n");
		}
	}*/


	///////////////////////////
	/// LINES

	int indexL[9];//index of each lines
	int find = 0; //looking for 0 when we found the first line of the case and 1 for the last line
	int tmp;
	int linenumber = 0;
	int vallooked;
	for (int i = 0; i < height; i++)
	{
		tmp = 0;
		vallooked = 1;

		for (int j = 0; j < width; j++)
		{
			if (tableau[i][j] == vallooked)
			{
				// We have a white pixel
				tmp += 1;
			}
		}
		if (tmp == 0)
		{
			find = 0;
		}
		if (tmp >3* height / 5 && find == 0)
		{
			indexL[linenumber] = i;
			find = 1;
			linenumber++;
			i += height * 0.015;
		}
	}
	//////////////////////////////
	/// COLUMNS
	int indexC[9]; // index of each columns
	find = 0; //looking for 0 when we found the first column of the case and 1 for the last column
	int columnnumber = 0;
	for (int i = 0; i < width; i++)
	{
		tmp = 0;
		vallooked = 1;//looking for a white pixel

		for (int j = 0; j < height; j++)
		{
			if (tableau[i][j] == vallooked)
			{
				// We have a white pixel
				tmp += 1;
			}
		}
		if (tmp == 0)
		{
			find = 0;
		}
		if (tmp >  3*width / 5 && find == 0)
		{
			indexC[columnnumber] = i;
			find = 1;
			columnnumber++;
			i += height * 0.015;
		}
	}

	// We have the coordonate of the lines and columns
	// now lets save the cases into images

	int addedy = 1;
	int addedx;
	tmp = 0;
	while (addedy < 9)
	{
		addedx = 1;
		int cols = (indexC[addedx] - indexC[addedx - 1]);
		while (addedx < 9)
		{

			int lines = (indexL[addedy] - indexL[addedy - 1]);
			double casee[lines * cols];
			for (int x = indexC[addedx - 1]; x < indexC[addedx]; x++)
			{
				for (int y = indexL[addedy - 1]; y < indexL[addedy]; y++)
				{
					casee[(x-indexC[addedy-1])*cols+y-indexL[addedx-1]]=(int)tableau[x][y];
				}

			}
			char filename[20];
			sprintf(filename, "%s%d%s%d%s","cases/caseL" , addedy, "_C", addedx,".txt");
			savecasee(casee, cols, lines, filename); //save the case in a txt
			addedx++;
		}
		addedy++;
	}
	return 0;
}


