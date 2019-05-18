#include "Menu.h"
#include "Sound.h"

//Init SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event Events;

bool Init()
{
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL  could not initialize! SDL_Error: " << SDL_GetError() << '\n';
		return 0;
	}

	gWindow = SDL_CreateWindow(TITLE_GAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Window could not be create! SDL_Error: " << SDL_GetError() << '\n';
		return 0;
	}
	
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		std::cout << "Renderer could not be create! SDL_Error: " << SDL_GetError() << '\n';
		return 0;
	}

	//Initialize PNG load
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " <<  IMG_GetError() << '\n';
		return 0;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 0;
	}
	LoadSound();
	return 1;
}

void Close()
{ 
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}


int main(int argc, char **argv)
{
	if (Init() == 0) return -1;
	CallMenu(gWindow, gRenderer);
	Close();
	  
	return 0;
}