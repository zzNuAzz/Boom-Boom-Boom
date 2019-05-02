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


GameMap::GameMap(SDL_Renderer* des, const std::string& path, Player* Player_1, Player* Player_2)
{
	this->Render_des = des;
	std::ifstream map(path);
	if (map.is_open()) {
		int x1, y1, x2, y2;
		map >> x1 >> y1 >> x2 >> y2;
		Player_1->SetRect(x1*TILES_SIZE, y1*TILES_SIZE - 15);
		Player_2->SetRect(x2*TILES_SIZE, y2*TILES_SIZE - 15);
		ijfor(MAP_ROW, MAP_COL) map >> MapStatus[i][j];

		while (!map.eof()) {
			int i;
			std::string tile_path, shadow_path, state;
			map >> i;
			std::getline(map, tile_path, ':');
			std::getline(map, shadow_path, ':');
			std::getline(map, state);
			Tiles[i].loadIMG(des, tile_path);
			if (state == "hard") Tiles[i].setHardTiles(true);
			if (shadow_path != "") {
				Shadow[i].loadIMG(des, shadow_path);
				Shadow[i].setShadow();
			}
		}

		map.close();
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
	ijfor(MAP_ROW, MAP_COL) 
		if (MapStatus[i][j] > 0 && MapStatus[i][j] < NUMBER_TILES) {
			Tiles[MapStatus[i][j]].Render(mapRect[i][j]);
		}
}

void GameMap::DrawShadow()
{
	ijfor(MAP_ROW, MAP_COL) {
		int k = MapStatus[i][j];
		if (k > 0 && k < NUMBER_TILES) {
			Shadow[k].SetRect(mapRect[i][j].x, mapRect[i][j].y);
			Shadow[k].Render();
		}
	}
}

