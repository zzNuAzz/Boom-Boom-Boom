#ifndef MENU_H
#define MENU_H
#include "ConstAndGlobalVar.h"


namespace MenuCharator {
	const SDL_Rect  Character_Pick[4]  = {/* x,   y,   w,  h*/
										 { 131,   0, 185, 278},
										 { 316,   0, 217, 316},
										 { 533,   0, 196, 316},
										 { 729,   0, 186, 266} };
	const SDL_Rect Character_Lock[4] = { { 131, 277, 185, 278},
										 { 316, 316, 217, 316},
										 { 533, 316, 196, 316},
										 { 729, 266, 186, 266} };
	const SDL_Rect  CharacterRect[4] = { { 115, 152, 185, 278},
										 { 238, 108, 217, 316},
										 { 386, 109, 196, 316},
										 { 498, 163, 186, 266} };

	const SDL_Rect  PickRect[4][5] = { // Be_Bong
										{{ 121, 219,  40,  73}, 
										 { 154, 160,  54, 144}, 
										 { 207, 160,  53,  26},
										 { 202, 185,  66, 151}, 
										 { 267, 283,  37,  53}},
										 // Kho_Kho
										{{ 244, 120, 155,  55}, 
										 { 398, 113,  64,  62}, 
										 { 258, 174, 141, 110}, 
										 { 298, 283, 101,  62}, 
										 { 398, 174,  43,  89}},
										 // Nhanh_Nhau
										{{ 441, 113,  97, 174},
										 { 429, 174,  22, 173}, 
										 { 404, 250,  43,  97},
										 { 537, 160,  40,  90}, 
										 { 451, 254,  70,  93}},
										 // Thit_Mo
										{{ 510, 315, 173,  34},
										 { 526, 254, 134,  62},
										 { 554, 245, 100,  10},
										 { 574, 160,  42,  85},
										 { 612, 179,  71,  67}} };

	const SDL_Rect ArrowPick[4] =	   { { 204, 345,  41,  47}, //Be_Bong
										 { 324, 345,  41,  47}, //Kho_Kho
										 { 444, 345,  41,  47}, //Nhanh_Nhau
										 { 574, 345,  41,  47}};//Thit_Mo

	const SDL_Rect ArrowClip[2] =	   { {   0,   0,  41,  47} , //1P
										 {  41,   0,  41,  47} };//2P
	bool Point_In_Character(const SDL_Point& mouse, const Charactors& Charactor);
	Charactors getMousePointTo(SDL_Point &mouse);
}
namespace MapMenu {
	const std::vector<std::string> map_path = { "Bin/map/01.txt", "Bin/map/02.txt", "Bin/map/03.txt", "Bin/map/04.txt" };
	const SDL_Rect MAP_RECT[5] =  { {10,30,220,200},
									{580,30,220,200},
									{40,240,220,200},
									{540,240,220,200},
									{290,150,220,200} };
	const SDL_Rect MAP_CLIP[2][5] = { { //InActive
										{   0,   0, 220, 200} ,
										{ 220,   0, 220, 200},
										{ 440,   0, 220, 200},
										{ 660,   0, 220, 200},
										{ 880,   0, 220, 200} },
										//Active
									  { {   0, 200, 220, 200},
										{ 220, 200, 220, 200},
										{ 440, 200, 220, 200},
										{ 660, 200, 220, 200}, 
										{ 880, 200, 220, 200}} };
}

struct GameOption{
	enum GameMode { TwoPlayer, KillEnemy} mode = TwoPlayer;
	Charactors Player[2] = { NONE, NONE };
	int map = 4;
	std::string getMap() const;
};
void CallMenu(SDL_Window* gWindow, SDL_Renderer* gRenderer);
#endif // !MENU_H
