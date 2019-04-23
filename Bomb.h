#ifndef BOMB_H
#define BOMB_H

#include "Object.h"
#include "Map.h"

class Player;
class Item;

class Bomb : public Object
{
public:
	Bomb();
	~Bomb();

	void setPos(const int& x, const int& y);
	xy getPos() const { return pos_; }
	void setCountDown(const int& time) { CountDown_ = time; }
	int getCountDown() const { return CountDown_; }
	void setLength_bang(const int& length) { length_bang_ = length; }
	void set_player_own(const int& player_no) { player_own_ = player_no; }
	int get_player_own() const { return player_own_; }

	
	void setSpriteClip();
	void Render();
	void UpdateMapStt(GameMap &MapData, xy Player_pos);

	void CountDown();
	void Bang();
	
	void BomBangMid(GameMap &MapData, std::vector<Bomb*> *plist_bomb, Object& BangMid, Player* player1, Player* player2);
	bool BomBangLeft(GameMap &MapData, std::vector<Bomb*> *plist_bomb, std::vector<Item*>* plist_item, Object& BangLeft, Player* player1, Player* player2);
	bool BomBangRight(GameMap &MapData, std::vector<Bomb*> *plist_bomb, std::vector<Item*>* plist_item, Object & BangRight, Player* player1, Player* player2);
	bool BomBangUp( GameMap &MapData, std::vector<Bomb*> *plist_bomb, std::vector<Item*>* plist_item, Object& BangUp, Player* player1, Player* player2);
	bool BomBangDown(GameMap &MapData, std::vector<Bomb*> *plist_bomb, std::vector<Item*>* plist_item, Object & BangDown, Player* player1, Player* player2);
	bool BombBang(GameMap &MapData, std::vector<Bomb*> *plist_bomb, std::vector<Item*>* plist_item, Object & BangMid,
		Object& BangLeft, Object & BangRight, Object& BangUp, Object & BangDown, Player* Player1, Player* Player2);

private:
	xy pos_;
	int CountDown_;
	int length_bang_;
	int player_own_;

	std::vector<SDL_Rect> SpriteClip;
	int frame_;

};

void bomb_Update(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item, Object & BangMid,
	Object & BangLeft, Object & BangRight, Object & BangUp, Object & BangDown, Player* player1, Player* player2, bool& isRenderBombBang);
#endif // !BOMB_H
