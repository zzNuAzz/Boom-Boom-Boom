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



class GameMap
{
public:
	GameMap(SDL_Renderer* des);
	~GameMap();
	void LoadTiles();
	void Render();
	
	int getMapStt(const int& i, const int& j) const { return MapStatus[i][j]; }

	void setPlayerPos(xy player_pos, const int& player_no) { MapStatus[player_pos.second][player_pos.first] = player_no; }

	void setBomb(const int& i, const int& j) { MapStatus[i][j] = BOMB_FLAG; }
	void removeStatus(const int& i, const int& j) { MapStatus[i][j] = 0; }
	

	bool get_isHartTiles(const int& number_of_tiles) { return Tiles[number_of_tiles].isHardTiles(); }


private:
	TilesMap Tiles[NUMBER_TILES];
	int MapStatus[MAP_ROW][MAP_COL];
	SDL_Rect mapRect[MAP_ROW][MAP_COL];
	SDL_Renderer* Render_des;

};


#endif // !MAP_H
