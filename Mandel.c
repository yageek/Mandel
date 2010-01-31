/*
 ============================================================================
 Name        : Mandel.c
 Author      : YaGeek
 Version     :
 Copyright   : GPL
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>

/*
 * DEFINE
 */
#define MAX_ITER 1000
#define WIDTH 640
#define HEIGHT 480
#define XORIGIN WIDTH/2
#define YORIGIN HEIGHT/2
/*
 * Variables
 */
SDL_Surface *ecran;
void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
void affAxis(SDL_Surface * ecran){

	SDL_Rect rect;
	rect.w = 1;
	rect.h = 1;
	int i;
	/*
	 * Vertical AXIS
	 */
	rect.y = YORIGIN;
	for(i=0;i< WIDTH;i++){
		rect.x = i;
		SDL_FillRect(ecran,&rect,SDL_MapRGB(ecran->format,255,0,0));
	}
	/*
	 * HORIZONTAL AXIS
	 */
		rect.x = XORIGIN;
	for(i=0;i < HEIGHT;i++){
		rect.y = i;
		SDL_FillRect(ecran,&rect,SDL_MapRGB(ecran->format,255,0,0));
	}


}

int main(void) {
	/*
	 * SDL INIT
	 */
	 if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur alors...
	    {
	        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Ecriture de l'erreur
	        exit(EXIT_FAILURE); // On quitte le programme
	    }

		 ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE);
		 SDL_WM_SetCaption("Mandel v0.1",NULL);

		 /*
		  * SDL Color
		  */
		 Uint32 blackcolor = SDL_MapRGB(ecran->format,0,0,0);
		 Uint32 itercolor;
		 SDL_Rect rect;
		 rect.h = 1;
		 rect.w = 1;

		 /*
		  * Mandelbrot program
		  */
		 double xtemp,x,y,xp,yp,factor;
		 int i,j,iter;

		 /*
		  * Scale Factor
		  */
		 factor = 200.0;
		 for(i=0; i< WIDTH;i++){
			 for(j=0;j< HEIGHT;j++){
				 //Start with 0;
				 x=0;
				 y=0;
				 iter=0;
				 xp = (i - XORIGIN)/factor;
				 yp = (j - YORIGIN)/factor;
				 while((x*x + y*y <= 4) && iter < MAX_ITER){
					 xtemp = x*x - y*y +xp;
					 y = 2*x*y + yp;
					 x = xtemp;
					 iter++;
				 }
				 //printf("Point (%i,%i) - Iterations %i\n",i,j,iter);
				 rect.x = i;
				 rect.y = j;
				 if(iter == MAX_ITER) SDL_FillRect(ecran,&rect,blackcolor);
				 else{

					 itercolor = SDL_MapRGB(ecran->format,0,0,iter*30);
					 SDL_FillRect(ecran,&rect,itercolor);
				 }
			 }
		 }
		 //affAxis(ecran);
		 SDL_Flip(ecran);
		 pause();

	    SDL_Quit();

	return EXIT_SUCCESS;
}
