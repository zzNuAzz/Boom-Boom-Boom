#include "GameMode.h"

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


	Player* Player_1 = new Player1(gRenderer, Option.Player[0], &list_bomb);
	
	Player_1->set_inBomb_Object("Bin//Images//BeBong_sacnuoc.png");
	Player_1->SetRect(100, 85);
	Player* Player_2 = new Player2(gRenderer,Option.Player[1], &list_bomb);
	 Player_2->SetRect(750, 635);


	Player_2->set_inBomb_Object("Bin//Images//Khokho_sacnuoc.png");
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
			Player_1->HandleInput(Events);
			Player_2->HandleInput(Events);
		}
		//Update

		Player_1->Update(gameMap);
		Player_2->Update(gameMap);

		ifor(list_item.size())
			list_item[i]->Update(&list_item, gameMap, Player_1, Player_2);

		bool isRenderBombBang = 0;
		bomb_Update(gameMap, &list_bomb, &list_item, BangMid, BangLeft, BangRight, BangUp, BangDown, Player_1, Player_2, isRenderBombBang);
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
		Player_1->Render();
		Player_2->Render();
		// Item
		ifor((int)list_item.size())
			list_item[i]->Render();

		SDL_RenderPresent(gRenderer);
		//FPS
		SDL_Delay(20);
		//console
		if (Player_1->isDied() || Player_2->isDied())
		{
			std::string notification = "";
			if (Player_1->isDied()) notification += "Player1 died\n";
			if (Player_2->isDied())notification += "Player2 died\n";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Noti", notification.c_str(), gWindow);
			running = false;
		}
	}
	delete Player_1;
	Player_1 = NULL;
	delete Player_2;
	Player_2 = NULL;
	delete ItemImage;
	ItemImage = NULL;
	ifor(list_bomb.size()) delete list_bomb[i];
	ifor(list_item.size()) delete list_item[i];

	SDL_SetWindowSize(gWindow, MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT);
	SDL_SetWindowPosition(gWindow, screen_cordinate_x, screen_cordinate_y);
}