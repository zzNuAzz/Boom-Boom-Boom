#include "Map.h"

TilesMap::TilesMap()
{
	isHardTiles_ = 0;
}

TilesMap::~TilesMap()
{
	;
}

ShadowTileMap::ShadowTileMap()
{
}

ShadowTileMap::~ShadowTileMap()
{
}

void ShadowTileMap::Render()
{
	SDL_Rect RenderRect = { Rect_.x, Rect_.y - Rect_.h, Rect_.w, Rect_.h };
	SDL_RenderCopy(Render_des, pObject_, NULL, &RenderRect);
}


GameMap::GameMap(SDL_Renderer* des)
{
	this->Render_des = des;
	std::ifstream map01("Bin//map//01.txt");
	if (map01.is_open())
		ijfor(MAP_ROW, MAP_COL) map01 >> MapStatus[i][j];
	map01.close();

	ijfor(MAP_ROW, MAP_COL)
	{
		mapRect[i][j].y = i * TILES_SIZE;
		mapRect[i][j].x = j * TILES_SIZE;
		mapRect[i][j].w = TILES_SIZE;
		mapRect[i][j].h = TILES_SIZE;
	}
	LoadTiles();
}

GameMap::~GameMap()
{
	;
}

void GameMap::LoadTiles()
{
	Tiles[1].loadIMG(Render_des, "bin\\images\\cay1.png");
	Tiles[2].loadIMG(Render_des, "bin\\images\\goccay1.png");
	Tiles[3].loadIMG(Render_des, "bin\\images\\da1.png");
	Tiles[4].loadIMG(Render_des, "bin\\images\\nam2.png");
	Tiles[5].loadIMG(Render_des, "bin\\images\\goctrentrai.png");
	Tiles[6].loadIMG(Render_des, "bin\\images\\vientren.png");
	Tiles[7].loadIMG(Render_des, "bin\\images\\goctrenphai.png");
	Tiles[8].loadIMG(Render_des, "bin\\images\\vienphai.png");
	Tiles[9].loadIMG(Render_des, "bin\\images\\gocduoiphai.png");
	Tiles[10].loadIMG(Render_des, "bin\\images\\vienduoi.png");
	Tiles[11].loadIMG(Render_des, "bin\\images\\gocduoitrai.png");
	Tiles[12].loadIMG(Render_des, "bin\\images\\vientrai.png");

	Tiles[2].setHardTiles(true);
	Tiles[3].setHardTiles(true);
	Tiles[5].setHardTiles(true);
	Tiles[6].setHardTiles(true);
	Tiles[7].setHardTiles(true);
	Tiles[8].setHardTiles(true);
	Tiles[9].setHardTiles(true);
	Tiles[10].setHardTiles(true);
	Tiles[11].setHardTiles(true);
	Tiles[12].setHardTiles(true);

}

void GameMap::Render()
{
	ijfor(MAP_ROW, MAP_COL) 
		if (MapStatus[i][j] > 0 && MapStatus[i][j] < NUMBER_TILES) {
			Tiles[MapStatus[i][j]].Render(mapRect[i][j]);
		}
}
