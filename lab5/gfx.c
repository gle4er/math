#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;
double zoom = 50; //масштаб изображения

int pnt_cnt = 0;
double *x_val,
       *y_val,
       *y_intr;

void initGfx(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    printf("Initialisation graphic\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error: %s\n", SDL_GetError());
        exit(3);
	} else {
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!\n");
        printf("Setting window\n");
		gWindow = SDL_CreateWindow("MDA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(gWindow == NULL) {
			printf("Error: %s\n", SDL_GetError());
            exit(3);
		} else {
            printf("Setting renderer\n");
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL) {
				printf("Error: %s\n", SDL_GetError());
                exit(3);
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
}

void drawPoints()
{
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
    for (int i = 0; i < pnt_cnt - 1; i++) {
	    SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0x00);
	    SDL_RenderDrawLine(gRenderer, x_val[i], y_val[i], x_val[i + 1], y_val[i + 1]);
	    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0x00);
	    SDL_RenderDrawLine(gRenderer, x_val[i], y_intr[i], x_val[i + 1], y_intr[i + 1]);
    }
	SDL_RenderPresent(gRenderer);
    SDL_Delay(32);
}

void clear()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void load()
{
	FILE *file = fopen("./data", "r");
    fscanf(file, "%d", &pnt_cnt);
    x_val = (double*) malloc(sizeof(double) * pnt_cnt);
    y_val = (double*) malloc(sizeof(double) * pnt_cnt);
    y_intr = (double*) malloc(sizeof(double) * pnt_cnt);
    for (int i = 0; i < pnt_cnt; i++)
        fscanf(file, "%lf %lf %lf", &x_val[i], &y_intr[i], &y_val[i]);
    return;
}

int main()
{
    load();
    for (int i = 0; i < pnt_cnt; i++) {
        x_val[i] *= zoom;
        y_val[i] *= -zoom;
        y_intr[i] *= -zoom;
        x_val[i] += SCREEN_WIDTH / 2;
        y_val[i] += SCREEN_HEIGHT / 2;
        y_intr[i] += SCREEN_HEIGHT / 2;
    }
    initGfx(SCREEN_WIDTH, SCREEN_HEIGHT);
	int quit = 0;
	SDL_Event e;
	while(!quit) {
	    while(SDL_PollEvent( &e ) != 0)
			if(e.type == SDL_QUIT) 
			    quit++;
        drawPoints();
    }
    clear();
    return 0;
}
