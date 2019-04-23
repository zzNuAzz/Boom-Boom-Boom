#ifndef MENU_H
#define MENU_H
#include "ConstAndGlobalVar.h"

namespace MenuCharator {
	const SDL_Rect  Character_Pick[5]  = {/* x,   y,   w,  h*/
										 {   0,   0, 131, 302},
										 { 131,   0, 185, 278},
										 { 316,   0, 217, 316},
										 { 533,   0, 196, 316},
										 { 729,   0, 186, 266} };
	const SDL_Rect Character_Lock[5] = { {  0, 302, 131, 302},
										 { 131, 277, 185, 278},
										 { 316, 316, 217, 316},
										 { 533, 316, 196, 316},
										 { 729, 266, 186, 266} };
	const SDL_Rect  CharacterRect[5] = { {  81, 127, 131, 302},
										 { 161, 152, 185, 278},
										 { 284, 108, 217, 316},
										 { 432, 109, 196, 316},
										 { 544, 163, 186, 266} };
	const SDL_Rect  PickRect[5][5] = { { // Mo_Mang
										 { 155, 129,  33,  46} , 
										 { 114, 174, 101,  46} ,
										 {  88, 185,  27,  78} ,
										 { 114, 219,  62, 108} , 
										 { 175, 291,  42,  25} },
										 // Be_Bong
										{{ 167, 219,  40,  73} , 
										 { 200, 160,  54, 144} , 
										 { 253, 160,  53,  26} ,
										 { 248, 185,  66, 151} , 
										 { 313, 283,  37,  53} },
										 // Kho_Kho
										{{ 290, 120, 155,  55} , 
										 { 444, 113,  64,  62} , 
										 { 304, 174, 141, 110} , 
										 { 344, 283, 101,  62} , 
										 { 444, 174,  43,  89} },
										 // Nhanh_Nhau
										{{ 487, 113,  97, 174} ,
										 { 475, 174,  22, 173} , 
										 { 450, 250,  43,  97} , 
										 { 583, 160,  40,  90} , 
										 { 497, 254,  70,  93}},
										 // Thit_Mo
										{{ 556, 315, 173,  34} ,
										 { 572, 254, 134,  62} ,
										 { 600, 245, 100,  10} ,
										 { 620, 160,  42,  85} ,
										 { 658, 179,  71,  67} } };
	bool Point_In_Character(const SDL_Point& mouse, const Charactors& Charactor);
	Charactors getMousePointTo(SDL_Point &mouse);
}

struct GameOption{
	enum GameMode { TwoPlayer, KillEnemy} mode = TwoPlayer;
	int NumOfPlayer = 1;
	Charactors Player[2] = { NONE, NONE };
};
#endif // !MENU_H
