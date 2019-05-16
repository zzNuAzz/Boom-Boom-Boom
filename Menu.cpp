#include "Menu.h"
#include "Sound.h"
#include "Object.h"
#include "GameMode.h"

bool MenuCharator::Point_In_Character(const SDL_Point & mouse, const Charactors & Charactor)
{
	for (int i = 0; i < 5; i++)
		if (SDL_PointInRect(&mouse, &MenuCharator::PickRect[Charactor][i])) return 1;
	return 0;

}

Charactors MenuCharator::getMousePointTo(SDL_Point & mouse)
{
	//if (Point_In_Character(mouse, MO_MANG)) return MO_MANG;
	if (Point_In_Character(mouse, BE_BONG)) return BE_BONG;
	if (Point_In_Character(mouse, KHO_KHO)) return KHO_KHO;
	if (Point_In_Character(mouse, NHANH_NHAU)) return NHANH_NHAU;
	if (Point_In_Character(mouse, THIT_MO)) return THIT_MO;
	return NONE;
}

void CallMenu(SDL_Window* gWindow, SDL_Renderer* gRenderer)
{

	Object Background(gRenderer, "Bin/Images/menu_background.png");
	Object CharacterSelection(gRenderer, "Bin/Images/CharacterSelection.png");
	Object Selection(gRenderer, "Bin/Images/Selection.png");
	Object PlayButton(gRenderer, "Bin/Images/PlayButton.png");
	Object ArrowPlayer(gRenderer, "Bin/Images/arrow_player.png");
	Object MapBackGround(gRenderer, "Bin/Images/MapBackGround.png");
	Object MapSelection(gRenderer, "Bin/Images/MapSelection.png");

	PlayButton.SetRect(20, 300);
	GameOption Option;
	enum { MainMenu, SelectionCharMenu, SelectionMapMenu } Screen;
	Screen = MainMenu;
	Charactors Mouse_Point_To = NONE;

	Mix_FadeInMusic(Music_Background, -1, 2000);
	bool running = 1;
	while (running) {
		SDL_Event Events;
		while (SDL_PollEvent(&Events)) {

			if (Events.type == SDL_EventType::SDL_QUIT) {
				running = 0;
			}
			//sound
			if (Events.type == SDL_MOUSEBUTTONDOWN) {
				Mix_PlayChannel(-1, Chunk_Touch, 0);
			}
			//HandleInput
			if (Screen == MainMenu) {
				if (Events.type == SDL_MOUSEBUTTONDOWN) {

					SDL_Point mouse = { Events.button.x, Events.button.y };
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
							Screen = SelectionMapMenu;
						}
						else {
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Information", "You must pick 2 charactors.", gWindow);
						}
					}
					else if (Events.key.keysym.sym == SDLK_ESCAPE) {
						Screen = MainMenu;
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
			else if (Screen == SelectionMapMenu) {
				if (Events.type == SDL_KEYDOWN) {
					if (Events.key.keysym.sym == SDLK_RETURN) {
						Mix_PlayMusic(Music_Start, 0);
						int buttonid = 1;
						while(buttonid == 1) NewGame_2Player(gWindow, gRenderer, Option, &buttonid); 
						if (buttonid == 0) {
							running = 0;
						}
						Option.Player[0] = NONE;
						Option.Player[1] = NONE;
						Screen = MainMenu;

						Mix_FadeInMusic(Music_Background, -1, 2000);
					}
					else if (Events.key.keysym.sym == SDLK_ESCAPE) {
						Screen = SelectionCharMenu;
					}
				}
				else if (Events.type == SDL_MOUSEBUTTONDOWN) {
					SDL_Point mouse = { Events.motion.x, Events.motion.y };
					ifor(5) if (SDL_PointInRect(&mouse, &MapMenu::MAP_RECT[i])) {
						Option.map = i; break;
					}
				}
			}
		}

		//Draw Menu
		if (Screen == MainMenu) {
			Background.Render();
			PlayButton.Render();
		}
		else if (Screen == SelectionCharMenu) {
			CharacterSelection.Render();

			ifor(2) if (Option.Player[i] != NONE) {
				Selection.Render(MenuCharator::CharacterRect[Option.Player[i]], &MenuCharator::Character_Lock[Option.Player[i]]);
				ArrowPlayer.Render(MenuCharator::ArrowPick[Option.Player[i]], &MenuCharator::ArrowClip[i]);
			}
			if (Mouse_Point_To != NONE) {
				if (Option.Player[0] != Mouse_Point_To && Option.Player[1] != Mouse_Point_To)
					Selection.Render(MenuCharator::CharacterRect[Mouse_Point_To], &MenuCharator::Character_Pick[Mouse_Point_To]);
			}
		}
		else if (Screen == SelectionMapMenu) {
			MapBackGround.Render();
			ifor(5) MapSelection.Render(MapMenu::MAP_RECT[i], &MapMenu::MAP_CLIP[(i == Option.map) ? 1 : 0][i]);
		}

		SDL_RenderPresent(gRenderer);
		SDL_Delay(30);
		SDL_RenderClear(gRenderer);
	}
	Mix_PlayMusic(Music_Goodbye, 0);
	SDL_Delay(850);
}

std::string GameOption::getMap() const
{
	if (map == 4) return MapMenu::map_path[rand() % 4];
	else return MapMenu::map_path[map];
}
