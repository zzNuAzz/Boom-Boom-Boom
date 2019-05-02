#ifndef MAP_H
#define MAP_H

#include "Object.h"

class TilesMap : public Object
{
public:
	TilesMap();
	~TilesMap();

	void setHardTiles(const bool& isHard) { isHardTiles_ = isHard; }
	bool isHardTiles() const { return isHardTiles_; }

private:
	bool isHardTiles_;
};
class ShadowTileMap : public Object
{
public:
	ShadowTileMap();
	~ShadowTileMap();
	void Render();
	void setShadow() { shadow = 1; }
private:
	bool shadow;
};

class Player;
class GameMap
{
public:
	GameMap(SDL_Renderer* des, const std::string& path, Player* Player_1, Player* Player_2);
	~GameMap();
	void Load();
	void Render();
	void DrawShadow();

	int getMapStt(const int& i, const int& j) const { return MapStatus[i][j]; }

	void setPlayerPos(xy player_pos, const int& player_no) { MapStatus[player_pos.second][player_pos.first] = player_no; }

	void setBomb(const int& i, const int& j) { MapStatus[i][j] = BOMB_FLAG; }
	void removeStatus(const int& i, const int& j) { MapStatus[i][j] = 0; }
	

	bool get_isHartTiles(const int& number_of_tiles) { return Tiles[number_of_tiles].isHardTiles(); }


private:

	TilesMap Tiles[NUMBER_TILES];
	ShadowTileMap Shadow[NUMBER_TILES];
	int MapStatus[MAP_ROW][MAP_COL];
	SDL_Rect mapRect[MAP_ROW][MAP_COL];
	SDL_Renderer* Render_des;

};


#endif // !MAP_H
