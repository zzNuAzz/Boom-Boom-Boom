#include "GameMode.h"
#include "Menu.h"

//Init SDL 
bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
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
	srand(time(NULL));
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
}


int main(int argc, char **argv)
{
	if (Init() == 0) return -1;
	
	Object Background(gRenderer, "Bin/Images/menu_background.png");
	Object CharacterSelection(gRenderer, "Bin/Images/CharacterSelection.png");
	Object Seletion(gRenderer, "Bin/Images/Selection.png");
	Object PlayButton(gRenderer, "Bin/Images/PlayButton.png");
	Object ArrowPlayer(gRenderer, "Bin/Images/arrow_player.png");

	PlayButton.SetRect(20, 300);
	GameOption Option;
	enum {MainMenu, SelectionCharMenu} Screen;
	Screen = MainMenu; 
	Charactors Mouse_Point_To = NONE;

	bool running = 1;
	while (running) {
		while (SDL_PollEvent(&Events)) {

			if (Events.type == SDL_EventType::SDL_QUIT) {
				running = 0;
			}
			if (Screen == MainMenu) {
				if (Events.type == SDL_MOUSEBUTTONDOWN) {
					SDL_Point mouse = { Events.button.x, Events.button.y};
					SDL_Rect Rect = PlayButton.GetRect();
					int offset = 35;
					Rect = { Rect.x, Rect.y + offset, Rect.w, Rect.h - offset };
					if (SDL_PointInRect(&mouse, &Rect)) {
						Screen = SelectionCharMenu;
					}
				}
			}
			else if (Screen == SelectionCharMenu) {
				if (Events.type == SDL_KEYDOWN) {
					if (Events.key.keysym.sym == SDLK_RETURN) {
						if (Option.Player[0] != NONE && Option.Player[1] != NONE) {
							NewGame_2Player(gWindow, gRenderer, Option); Option.Player[0] = NONE;
							Option.Player[1] = NONE;
							Screen = MainMenu;
						}
						else {
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Information", "You must pick 2 charactors.", gWindow);
						}
					}
				}
				if (Events.type == SDL_MOUSEMOTION) {
					SDL_Point mouse = { Events.motion.x, Events.motion.y };
					Mouse_Point_To = MenuCharator::getMousePointTo(mouse);
				}
				if (Events.type == SDL_MOUSEBUTTONDOWN) {
					if (Events.button.button == SDL_BUTTON_LEFT && Mouse_Point_To != NONE && Option.Player[1] != Mouse_Point_To) {
						Option.Player[0] = Mouse_Point_To;
					}
					else if (Events.button.button == SDL_BUTTON_RIGHT && Mouse_Point_To != NONE && Option.Player[0] != Mouse_Point_To) {
						Option.Player[1] = Mouse_Point_To;
					}
				}
			}
		}
		if (Screen == MainMenu) {
			Background.Render();
			PlayButton.Render();
		}
		else if (Screen == SelectionCharMenu) {
			CharacterSelection.Render(); 
			
			ifor(2) if (Option.Player[i] != NONE) {
				Seletion.Render(MenuCharator::CharacterRect[Option.Player[i]], &MenuCharator::Character_Lock[Option.Player[i]]);
				ArrowPlayer.Render(MenuCharator::ArrowPick[Option.Player[i]], &MenuCharator::ArrowClip[i]);
			}
			if (Mouse_Point_To != NONE) {
				if (Option.Player[0] != Mouse_Point_To && Option.Player[1] != Mouse_Point_To)
					Seletion.Render(MenuCharator::CharacterRect[Mouse_Point_To], &MenuCharator::Character_Pick[Mouse_Point_To]);
			}
		}
		SDL_RenderPresent(gRenderer);
		SDL_Delay(30);
		SDL_RenderClear(gRenderer);
	}
	
	Close();

	return 0;
}