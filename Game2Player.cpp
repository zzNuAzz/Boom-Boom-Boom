#include "Game2Player.h"

void NewGame_2Player(SDL_Window* gWindow, SDL_Renderer* gRenderer, const GameOption& Option)
{
//window size and posiotion
	SDL_SetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
	int screen_cordinate_x, screen_cordinate_y;
	SDL_GetWindowPosition(gWindow, &screen_cordinate_x, &screen_cordinate_y);
	SDL_SetWindowPosition(gWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
//Init Object
	Object BackGround(gRenderer, "Bin//Images//background.png");

	GameMap gameMap(gRenderer);
//	gameMap.LoadTiles();

	std::vector<Bomb*> list_bomb;

	std::vector<Item*> list_item;


	Player* RedBoomer = new Player1(gRenderer, &list_bomb, "Bin//Images//Yellowbebong.png");
	RedBoomer->SetRect(750, 635);
	RedBoomer->set_inBomb_Object("Bin//Images//Khokho_sacnuoc.png");

	Player* GreenBoomer = new Player2(gRenderer, &list_bomb, "Bin//Images//RedBoomer.png");
	GreenBoomer->SetRect(100, 85);


	GreenBoomer->set_inBomb_Object("Bin//Images//Khokho_sacnuoc.png");
	//Object Player::inBomb

	std::vector<Item_Image*> *ItemImage = new std::vector<Item_Image*>;
	ItemImage->resize(NUMBER_ITEM);
	ItemImage->at(WATER_BOTTLE) = new Item_Image(gRenderer, "Bin//Images//WaterBottle.png");
	ItemImage->at(WATER_BALLON) = new Item_Image(gRenderer, "Bin//Images//WaterBallon.png");
	ItemImage->at(RED_SHOE) = new Item_Image(gRenderer, "Bin//Images//RedShoe.png");

	RandomItemMap(gameMap, &list_item, ItemImage);

	//bomb bang
	Object BangMid(gRenderer, "Bin//Images//BangMid.png");
	Object BangLeft(gRenderer, "Bin//Images//BangLeft.png");
	Object BangRight(gRenderer, "Bin//Images//BangRight.png");
	Object BangUp(gRenderer, "Bin//Images//BangUp.png");
	Object BangDown(gRenderer, "Bin//Images//BangDown.png");

	bool running = 1;
	while (running)
	{
		//Handle Input
		while (SDL_PollEvent(&Events))
		{
			if (Events.type == SDL_QUIT || Events.key.keysym.sym == SDLK_ESCAPE) {
				running = 0;
			}
			RedBoomer->HandleInput(Events);
			GreenBoomer->HandleInput(Events);
		}
		//Update

		RedBoomer->Update(gameMap);
		GreenBoomer->Update(gameMap);

		ifor(list_item.size())
			list_item[i]->Update(&list_item, gameMap, RedBoomer, GreenBoomer);

		bool isRenderBombBang = 0;
		bomb_Update(gameMap, &list_bomb, &list_item, BangMid, BangLeft, BangRight, BangUp, BangDown, RedBoomer, GreenBoomer, isRenderBombBang);
		if (isRenderBombBang)
		{
			SDL_RenderPresent(gRenderer);
			SDL_Delay(50);
		}
		SDL_RenderClear(gRenderer);
		//Render Object

		BackGround.Render();
		gameMap.Render();
		// Bomb
		ifor((int)list_bomb.size())
			list_bomb[i]->Render();

		// Boomer
		RedBoomer->Render();
		GreenBoomer->Render();
		// Item
		ifor((int)list_item.size())
			list_item[i]->Render();

		SDL_RenderPresent(gRenderer);
		//FPS
		SDL_Delay(20);
		//console
		if (RedBoomer->isDied() || GreenBoomer->isDied())
		{
			std::string notification = "";
			if (RedBoomer->isDied()) notification += "Player1 died\n";
			if (GreenBoomer->isDied())notification += "Player2 died\n";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Noti", notification.c_str(), gWindow);
			running = false;
		}
	}
	delete RedBoomer;
	RedBoomer = NULL;
	delete GreenBoomer;
	GreenBoomer = NULL;
	delete ItemImage;
	ItemImage = NULL;
	ifor(list_bomb.size()) delete list_bomb[i];
	ifor(list_item.size()) delete list_item[i];

	SDL_SetWindowSize(gWindow, MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT);
	SDL_SetWindowPosition(gWindow, screen_cordinate_x, screen_cordinate_y);
}
