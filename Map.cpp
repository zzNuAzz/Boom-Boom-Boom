#include "Map.h"
#include "Player.h"

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
	shadow = 0;
}

ShadowTileMap::~ShadowTileMap()
{
}

void ShadowTileMap::Render()
{
	if (!shadow) return;
	SDL_Rect RenderRect = { Rect_.x, Rect_.y - Rect_.h, Rect_.w, Rect_.h };
	SDL_RenderCopy(Render_des, pObject_, NULL, &RenderRect);
}


GameMap::GameMap(SDL_Renderer* des, const std::string& path, std::string& Background_path, Player* Player_1, Player* Player_2)
{
	this->Render_des = des;
	std::ifstream MapFile(path);
	if (MapFile.is_open()) {
		int x1, y1, x2, y2;
		MapFile >> x1 >> y1 >> x2 >> y2;
		Player_1->SetRect(x1*TILES_SIZE, y1*TILES_SIZE - 15);
		Player_2->SetRect(x2*TILES_SIZE, y2*TILES_SIZE - 15);
		ijfor(MAP_ROW, MAP_COL) {
			MapFile >> MapStatus[i][j];
		}
		MapFile >> Background_path;
		MapFile >> Number_tiles;
		Number_tiles++;
		Tiles.resize(Number_tiles);
		Shadow.resize(Number_tiles);
		while (!MapFile.eof()) {
			int i;
			std::string tile_path, shadow_path, state;
			MapFile >> i;
			std::getline(MapFile, tile_path, ':');
			std::getline(MapFile, shadow_path, ':');
			std::getline(MapFile, state);
			Tiles[i].loadIMG(des, tile_path);
			if (state == "hard") Tiles[i].setHardTiles(true);
			if (shadow_path != "") {
				Shadow[i].loadIMG(des, shadow_path);
				Shadow[i].setShadow();
			}
		}

		MapFile.close();
	}
	ijfor(MAP_ROW, MAP_COL)
	{
		mapRect[i][j].y = i * TILES_SIZE;
		mapRect[i][j].x = j * TILES_SIZE;
		mapRect[i][j].w = TILES_SIZE;
		mapRect[i][j].h = TILES_SIZE;
	}
}

GameMap::~GameMap()
{
	;
}

void GameMap::Render()
{
	ijfor(MAP_ROW, MAP_COL) {
		int k = MapStatus[i][j];
		if (k > 0 && k < Number_tiles) {
			Tiles[k].Render(mapRect[i][j]);
		}
	}
}

void GameMap::DrawShadow()
{
	ijfor(MAP_ROW, MAP_COL) {
		int k = MapStatus[i][j];
		if (k > 0 && k < Number_tiles) {
			Shadow[k].SetRect(mapRect[i][j].x, mapRect[i][j].y);
			Shadow[k].Render();
		}
	}
}

