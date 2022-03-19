#include<iostream>
#include<SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

const int win_width = 1240;
const int win_height = 620;

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}
void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Не удалось инициализировать SDL!");
		DeInit(1);
	}

	win = SDL_CreateWindow("s1mple", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("Не удалось создать окно!");
		DeInit(1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("не удалось создать рисовальщик!");
		DeInit(1);
	}
}

int main(int args, char* argv[])
{
	Init();
	
	SDL_SetRenderDrawColor(ren, 170, 170, 170, 255);
	SDL_RenderClear(ren);

	srand(time(NULL));
	for (int i = rand() % 10; i < win_height; i += rand() % 20)
	{
		if (i % 2 == 0)
		{
			SDL_SetRenderDrawColor(ren, 225, 225, 225, 255);
			SDL_RenderClear(ren);
		}

		for (int j = rand() % 10; j < win_width; j += rand() % 80)
		{
			SDL_SetRenderDrawColor(ren, 0, 0, 200, 255);
			SDL_RenderDrawLine(ren, j, i, j + 50, i + 50);
			SDL_RenderDrawLine(ren, j, i, j + 55, i + 55);
			SDL_RenderDrawLine(ren, j, i, j + 60, i + 60);

			SDL_RenderPresent(ren);
		}
		SDL_Delay(20);
	}


	SDL_Delay(1000);

	DeInit(0);
	return 0;
}