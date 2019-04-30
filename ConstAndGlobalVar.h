#ifndef CONST_AND_GLOBAL_VAR_H
#define CONST_AND_GLOBAL_VAR_H

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>

#define ifor(n) for(int i = 0; i < n; i++)
#define ijfor(m,n) for(int i = 0; i < m; i++) for(int j = 0; j < n; j++)

#define PLAYER_1 -1
#define PLAYER_2 -2
#define BOMB_FLAG -3

#define WATER_BALLON 0 // ITEM tang them 1 bom
#define WATER_BOTTLE 1 // ITEM tang do dai bom them 1
#define RED_SHOE 2 // ITEM tang toc nguoi choi


//Character
enum Charactors {
	BE_BONG,
	KHO_KHO,
	NHANH_NHAU,
	THIT_MO,
	NONE // chua pick charactor
}; 

typedef std::pair<int, int> xy;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

static SDL_Event Events;

const int RENDERER_DRAW_COLOR_R = 0xFF; //255	
const int RENDERER_DRAW_COLOR_G = 0xFF; //255
const int RENDERER_DRAW_COLOR_B = 0xFF; //255
const int RENDERER_DRAW_COLOR_A = 0xFF; //255

const int MAP_ROW = 13 + 2; // so hang cua ban do + 2 hang vien
const int MAP_COL = 15 + 2; // so cot cua ban do + 2 hang vien
const int NUMBER_TILES = 13; // so luong vien gach + bom
const int TILES_SIZE = 50; // pixels


const std::string TITLE_GAME = "Boom - Tuan Anh #K63-CACLC1";
//menu window
const int MENU_SCREEN_WIDTH = 800;
const int MENU_SCREEN_HEIGHT = 450; 

//game window
const int SCREEN_WIDTH = MAP_COL * TILES_SIZE;
const int SCREEN_HEIGHT = MAP_ROW * TILES_SIZE;

//player
const int PLAYER_WIDTH = 50;
const int PLAYER_HIGHT = 65;

const int PLAYER_BASIC_SPEED = 3; //pixels per frame
const int MAX_SPEED_BOOST = 6;
const int limit_bomb = 10;
const int MAX_LENGTH_BOMB_PER_DIRECT = 6;
const int TIME_BOMB_COUNT_DOWN = 150;

const int SPRITE_CLIPS_IN_BOMB = 10;
const int FRAME_INBOM_STEP1 = 18; // giai doan 1 frame 0->29, sprite 0->2
const int FRAME_INBOM_STEP2 = 70; // giai doan 2 frame 30->69, sprite 3->4
const int FRAME_INBOM_STEP3 = 120; // giai doan 3 frame 70->119, sprite 5->6
const int FRAME_INBOM_STEP4 = 150; // giai doan 4 frame 120->159, sprite 7->8
const int PLAYER_IN_BOMB_COUNT_DOWN = 180; // giai doan 5 frame 160->179, sprite 9
const int IN_BOMB_SIZE = 65; // pixels
 struct CharatorInfo {
	std::string path;
	int Start_Bomb;
	int Start_Length;
	int Start_Speed;

	int Limit_Bomb;
	int Limit_Length;
	int Limit_Speed;
};
 
 const CharatorInfo Info[4] = { /*          path        ,  Start (Bomb, length, speed), Limit (Bomb, length, speed)*/	
								{"Bin/Images/BeBong.png",		  1,	 2,		4,				6,	  8,	8},
								{"Bin/Images/KhoKho.png",		  1,	 1,		4,				7,	  7,	8},
								{"Bin/Images/NhanhNhau.png",	  1,	 1,     6,			    6,    6,   10},
								{"Bin/Images/ThitMo.png",		  2,     1,     4,              8,    6,    8} };
//item
const int NUMBER_ITEM = 3;
const int RATIO_APPEAR_ITEM = 0; // ti le xuat hien = 1 - ratio / soluongitem


#endif // !DEFINE_CONST_AND_VAR_H
