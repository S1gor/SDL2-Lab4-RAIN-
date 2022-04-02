#include<iostream>
#include<SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

const int win_width = 1500;
const int win_height = 750;

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

	win = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

struct Rain
{
	float x1, y1, x2, y2;
	float speed = 5;
};

void coords(Rain* mas, int i)
{
	mas[i].x1 = rand() % win_width;
	mas[i].y1 = rand() % win_height;
	mas[i].x2 = mas[i].x1 - 100 * sin(2.7);
	mas[i].y2 = mas[i].y1 - 100 * sin(2.7);
}

void drawLine(Rain* mas, int i)
{
	SDL_SetRenderDrawColor(ren, 0, 0, rand() % 255, 255);
	SDL_RenderDrawLine(ren, mas[i].x1, mas[i].y1, mas[i].x2, mas[i].y2);
}

void speedRain(Rain* mas, int i)
{
	mas[i].y1 = mas[i].y1 + 50;
	mas[i].y2 = mas[i].y2 + 50 * 0.9;

	if (mas[i].y1 > win_height)
	{
		mas[i].y1 = rand() % win_height;
		mas[i].y2 = mas[i].y1 - 50* cos(0.5);
	}
}

int main(int args, char* argv[])
{
	Init();

	const int MAX = 100;
	Rain mas[MAX];

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		coords(mas, i);
		drawLine(mas, i);
	}
	while (true)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		for (int i = 0; i < 100; i++)
		{
			drawLine(mas, i);
			SDL_RenderPresent(ren);
			speedRain(mas, i);
		}
	}

	SDL_Delay(10);
	


	DeInit(0);
	return 0;
}