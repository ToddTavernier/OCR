 #include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "pixel_operations.h"
#include "display.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>




SDL_Surface* rotate(SDL_Surface* image, double angle)
{
    int width = image->w;
    int height = image->h;
    int x_center = width / 2;
    int y_center = height / 2;
    Uint8 r, g, b;
    Uint32 pixel;
    SDL_Surface* image2=SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    //Create a new image of Uint32  and r,g,g=0
    double angle2 = (angle / 180) * 3.14;
    //degree to rad
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            int nvx = ceil(((x - x_center) * cos(angle2) -
                (y - y_center) * sin(angle2)) + x_center);
            int nvy = ceil(((x - x_center) * sin(angle2) +
                (y - y_center) * cos(angle2)) + y_center);

            r = g = b = 255;
            pixel = SDL_MapRGB(image->format, r, g, b);
            if ((0 <= nvx && nvx < width) && (nvy >= 0 && nvy <= height))
                //if this place exist on the image
            {
                pixel = get_pixel(image, nvx, nvy);
            }

            put_pixel(image2, x, y, pixel);
        }
    }

    return image2;
}




void binarise(SDL_Surface* image)
{
    int w = image->w;
    int h = image->h;

    int xcount = 0;
    int ycount = 0;

    int blocx = w / 6;
    int blocy = h / 9;
    //to make the binarisation in a different way according to the place
    for (; xcount + blocx < w; xcount += blocx)
    {
        ycount = 0;
        for (; ycount + blocy < h; ycount += blocy)
        {
            int ave = 0;
            for (int x = 0; x < blocx; x++)
            {
                for (int y = 0; y < blocy; y++)
                {
                    Uint8 r, g, b;
                    Uint32 pixel = get_pixel(image, x + xcount, y + ycount);
                    SDL_GetRGB(pixel, image->format, &r, &g, &b);
                    ave += r;

                }
            }
            ave = ave / (blocx * blocy);
            ave += 18;
            for (int x = 0; x < blocx; x++)
            {
                for (int y = 0; y < blocy; y++)
                {
                    Uint8 r, g, b;
                    Uint32 pixel = get_pixel(image, x + xcount, y + ycount);
                    SDL_GetRGB(pixel, image->format, &r, &g, &b);
                    if (ave < r)
            //If the pixel is darker than the average put rgb to have black
                    {
                        r = 0;
                        g = 0;
                        b = 0;
                    }
                    else
                    {
                        r = 255;
                        g = 255;
                        b = 255;
                    }
                    pixel = SDL_MapRGB(image->format, r, g, b);
                    put_pixel(image, x + xcount, y + ycount, pixel);
                }
            }
        }
    }
}

SDL_Surface* pretraitement(char* path)
{
        SDL_Surface* image_surface;
        SDL_Surface* screen_surface;

        image_surface = load_image(path);
        screen_surface = display_image(image_surface);

        image_surface = rotate(image_surface,180);
		//the rest of the main work on a new image witch is a BMP
        wait_for_keypressed();

        int w = image_surface->w;
        int h = image_surface->h;
        Uint32 pixel;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {

                Uint8 r, g, b;
                pixel = get_pixel(image_surface, x, y);
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                int ave = 0.3 * r + 0.59 * g + 0.11 * b;
				//grayscale of the pixel
                pixel = SDL_MapRGB(image_surface->format,1 -ave, 1-ave,1-ave);
                put_pixel(image_surface, x, y, pixel);
            }
        }
        binarise(image_surface);

        update_surface(screen_surface, image_surface);

        update_surface(screen_surface, image_surface);
        wait_for_keypressed();

        /*SDL_FreeSurface(image_surface);

        SDL_FreeSurface(screen_surface);*/

        return image_surface;
   
}
