#include "Bomb.h"
#include "Player.h"
#include "Item.h"

Bomb::Bomb()
{
	pos_ = xy(0, 0);
	CountDown_ = TIME_BOMB_COUNT_DOWN;
	length_bang_ = 0;
	player_own_ = 0;
	frame_ = 0;
}	


Bomb::~Bomb()
{
	player_own_ = 0;
 }

void Bomb::setPos(const int & y, const int & x)
{ 
	pos_ = xy(x, y);
	Rect_.x = x * TILES_SIZE;
	Rect_.y = y * TILES_SIZE;
}



void Bomb::setSpriteClip()
{

	SpriteClip.resize(Rect_.w / TILES_SIZE);
	Rect_.w = TILES_SIZE;
	Rect_.h = TILES_SIZE;
	ifor(SpriteClip.size()) SpriteClip[i] = { i*TILES_SIZE, 0, TILES_SIZE, TILES_SIZE };
}

void Bomb::Render()
{
	frame_ = (frame_ == SpriteClip.size() * 10) ? 0 : frame_ + 1;
	SDL_RenderCopy(Render_des, pObject_, &SpriteClip[((frame_) % (SpriteClip.size()*10)) / 10], &Rect_);

	
}

void Bomb::UpdateMapStt(GameMap & MapData, xy Player_pos)
{
	if (pos_ != Player_pos) MapData.setBomb(pos_.second, pos_.first);
}



void Bomb::CountDown()
{
	if(CountDown_ > 0) 
		CountDown_--;
}

void Bomb::Bang()
{
	CountDown_ = 0;
}

bool Bomb::BomBangLeft(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item, Object & BangLeft, Player* player1, Player* player2)
{
	int mid_x = Rect_.x;
	int mid_y = Rect_.y;
	ifor(length_bang_)
	{
		xy bang_position(pos_.first - (i + 1), pos_.second);
		if (MapData.getMapStt(pos_.second, pos_.first - (i + 1)) == 0) // khong co tiles hoac bom
		{
			BangLeft.SetRect(mid_x - TILES_SIZE * (i + 1), mid_y);
			BangLeft.Render();
			ifor(plist_item->size()) // xoa item
			{
				if (plist_item->at(i)->get_pos() == bang_position) plist_item->at(i)->destroy();
			}
		}
		else if (MapData.getMapStt(pos_.second, pos_.first - (i + 1)) > 0) //va cham tiles
		{
			if (!MapData.get_isHartTiles(MapData.getMapStt(pos_.second, pos_.first - (i + 1)))) //soft tiles
			{
				MapData.removeStatus(pos_.second, pos_.first - (i + 1));
				BangLeft.SetRect(mid_x - TILES_SIZE * (i + 1), mid_y);
				BangLeft.Render();
			}
			else {
				//xu li explosion
			}
			break;
		}
		else //if(MapData.getMapStt(pos_.second, pos_.first - (i + 1)) == BOMB_FLAG)
		{
			//bomb
			bool flag_Collision_bomb = 0;
			ifor(plist_bomb->size())
			{
				if (bang_position == plist_bomb->at(i)->getPos() && plist_bomb->at(i)->getCountDown() != 0)
				{
					flag_Collision_bomb = true;
					plist_bomb->at(i)->Bang();
				}
			}
			if (flag_Collision_bomb) return 1;
			//Player

			if (MapData.getMapStt(pos_.second, pos_.first - (i + 1)) == PLAYER_1)
			{
				player1->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player2->set_inBomb(true);
			}
			if (MapData.getMapStt(pos_.second, pos_.first - (i + 1)) == PLAYER_2)
			{
				player2->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player1->set_inBomb(true);
			}
		}
	}
	return 0;
}

bool Bomb::BomBangRight(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item, Object & BangRight, Player* player1, Player* player2)
{

	int mid_x = Rect_.x;
	int mid_y = Rect_.y;
	ifor(length_bang_)
	{
		xy bang_position(pos_.first + (i + 1), pos_.second);
		if (MapData.getMapStt(pos_.second, pos_.first + (i + 1)) == 0)
		{
			BangRight.SetRect(mid_x + TILES_SIZE * (i + 1), mid_y);
			BangRight.Render();
			ifor(plist_item->size()) // xoa item
			{
				if (plist_item->at(i)->get_pos() == bang_position) plist_item->at(i)->destroy();
			}
		}
		else if (MapData.getMapStt(pos_.second, pos_.first + (i + 1)) > 0)
		{
			if (!MapData.get_isHartTiles(MapData.getMapStt(pos_.second, pos_.first + (i + 1))))
			{
				MapData.removeStatus(pos_.second, pos_.first + (i + 1));
				BangRight.SetRect(mid_x + TILES_SIZE * (i + 1), mid_y);
				BangRight.Render();
			}
			else {
				//xu li explosion
			}
			break;
		}
		else //if (MapData.getMapStt(pos_.second, pos_.first + (i + 1)) == BOMB_FLAG)
		{
			//bomb
			
			bool flag_Collision_bomb = 0;
			ifor(plist_bomb->size())
			{
				if (bang_position == plist_bomb->at(i)->getPos() && plist_bomb->at(i)->getCountDown() != 0)
				{
					flag_Collision_bomb = 1;
					plist_bomb->at(i)->Bang();
				}
			}
			if (flag_Collision_bomb) return 1;;
			if (MapData.getMapStt(pos_.second, pos_.first + (i + 1)) == player1->getPlayerNo())
			{
				player1->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player2->set_inBomb(true);
			}
			if (MapData.getMapStt(pos_.second, pos_.first + (i + 1)) == player2->getPlayerNo())
			{
				player2->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player1->set_inBomb(true);
			}
		}
	}
	return 0;
}

bool Bomb::BomBangUp(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item, Object & BangUp, Player* player1, Player* player2)
{
	int mid_x = Rect_.x;
	int mid_y = Rect_.y;
	ifor(length_bang_)
	{
		xy bang_position(pos_.first, pos_.second - (i + 1));
		if (MapData.getMapStt(pos_.second - (i + 1), pos_.first) == 0)
		{
			BangUp.SetRect(mid_x, mid_y - TILES_SIZE * (i + 1));
			BangUp.Render();
			ifor(plist_item->size()) // xoa item
			{
				if (plist_item->at(i)->get_pos() == bang_position) plist_item->at(i)->destroy();
			}
		}

		else if (MapData.getMapStt(pos_.second - (i + 1), pos_.first) > 0)
		{
			if (!MapData.get_isHartTiles(MapData.getMapStt(pos_.second - (i + 1), pos_.first)))
			{
				MapData.removeStatus(pos_.second - (i + 1), pos_.first);
				BangUp.SetRect(mid_x, mid_y - TILES_SIZE * (i + 1));
				BangUp.Render();
			}
			else {
				//xu li explosion
			}
			break;
		}
		else// if (MapData.getMapStt(pos_.second - (i + 1), pos_.first) == BOMB_FLAG)
		{
			bool flag_Collision_bomb = 0;
			ifor(plist_bomb->size())
			{
				if (bang_position == plist_bomb->at(i)->getPos() && plist_bomb->at(i)->getCountDown() != 0)
				{
					flag_Collision_bomb = true;
					plist_bomb->at(i)->Bang();
				}
			}
			if (flag_Collision_bomb) return 1;

			if (MapData.getMapStt(pos_.second - (i + 1), pos_.first) == player1->getPlayerNo())
			{
				player1->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player2->set_inBomb(true);
			}
			if (MapData.getMapStt(pos_.second - (i + 1), pos_.first) == player2->getPlayerNo())
			{
				player2->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player1->set_inBomb(true);
			}
		}
	}
	return 0;
}

bool Bomb::BomBangDown(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item, Object & BangDown, Player* player1, Player* player2)
{
	int mid_x = Rect_.x;
	int mid_y = Rect_.y; 
	ifor(length_bang_)
	{
		xy bang_position(pos_.first, pos_.second + (i + 1));
		if (MapData.getMapStt(pos_.second + (i + 1), pos_.first) == 0)
		{
			BangDown.SetRect(mid_x, mid_y + TILES_SIZE * (i + 1));
			BangDown.Render();
			ifor(plist_item->size()) // xoa item
			{
				if (plist_item->at(i)->get_pos() == bang_position) plist_item->at(i)->destroy();
			}
		}

		else if (MapData.getMapStt(pos_.second + (i + 1), pos_.first) > 0)
		{
			if (!MapData.get_isHartTiles(MapData.getMapStt(pos_.second + (i + 1), pos_.first)))
			{
				MapData.removeStatus(pos_.second + (i + 1), pos_.first);
				BangDown.SetRect(mid_x, mid_y + TILES_SIZE * (i + 1));
				BangDown.Render();
			}
			else {
				//xu li explosion
			}
			break;
		}
		else //if (MapData.getMapStt(pos_.second + (i + 1), pos_.first) == BOMB_FLAG)
		{
			xy position(pos_.first, pos_.second + (i + 1));
			bool flag_Collision_bomb = 0;
			ifor(plist_bomb->size())
			{
				if (position == plist_bomb->at(i)->getPos() && plist_bomb->at(i)->getCountDown() != 0)
				{
					flag_Collision_bomb = true;
					plist_bomb->at(i)->Bang();
				}
			}
			if (flag_Collision_bomb) return 1;

			if (MapData.getMapStt(pos_.second + (i + 1), pos_.first) == player1->getPlayerNo())
			{
				player1->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player2->set_inBomb(true);
			}
			if (MapData.getMapStt(pos_.second + (i + 1), pos_.first) == player2->getPlayerNo())
			{
				player2->set_inBomb(true);
				if (player1->get_pos() == player2->get_pos())
					player1->set_inBomb(true);
			}
		}
	}
	return 0;
}

void Bomb::BomBangMid(GameMap & MapData, std::vector<Bomb*>* plist_bomb, Object & BangMid, Player * player1, Player * player2)
{
	int mid_x = Rect_.x;
	int mid_y = Rect_.y;
	BangMid.SetRect(mid_x, mid_y);
	BangMid.Render();
	//colision with bomber
	if (pos_ == player1->get_pos())
	{
		player1->set_inBomb(true);
		if (player1->get_pos() == player2->get_pos())
			player2->set_inBomb(true);
	}
	if (pos_ == player2->get_pos())
	{
		player2->set_inBomb(true);
		if (player1->get_pos() == player2->get_pos())
			player1->set_inBomb(true);
	}
}

bool Bomb::BombBang(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item,
	Object & BangMid, Object & BangLeft, Object & BangRight, Object & BangUp, Object & BangDown, Player* player1, Player* player2)
{
	MapData.removeStatus(pos_.second, pos_.first);
	bool flagBomBangBang = 0;
	//bom no o giua	
	BomBangMid(MapData, plist_bomb, BangMid, player1, player2);
	//bom no sang trai
	if (BomBangLeft(MapData, plist_bomb, plist_item, BangLeft, player1, player2)) flagBomBangBang = 1;
	//bom no sang phai
	if (BomBangRight(MapData, plist_bomb, plist_item, BangRight, player1, player2)) flagBomBangBang = 1;
	//bom no len tren
	if (BomBangUp(MapData, plist_bomb, plist_item, BangUp, player1, player2)) flagBomBangBang = 1;
	//bom no xuong duoi
	if (BomBangDown(MapData, plist_bomb, plist_item, BangDown, player1, player2)) flagBomBangBang = 1;
	return flagBomBangBang;
}

void bomb_Update(GameMap & MapData, std::vector<Bomb*>* plist_bomb, std::vector<Item*>* plist_item, Object & BangMid,
	Object & BangLeft, Object & BangRight, Object & BangUp, Object & BangDown, Player* player1, Player* player2, bool& isRenderBombBang)
{
	ifor((int)plist_bomb->size())
	{
		Bomb* p_bomb = plist_bomb->at(i);
		if (p_bomb != NULL)
		{
			if (p_bomb->getCountDown() == 0)
			{
				isRenderBombBang = 1;
				int x = p_bomb->getPos().first;
				int y = p_bomb->getPos().second;
				bool flag = p_bomb->BombBang(MapData, plist_bomb, plist_item, BangMid, BangLeft, BangRight, BangUp, BangDown, player1, player2);
				if (p_bomb->get_player_own() == player1->getPlayerNo()) player1->set_placed_bomb_down();
				else if (p_bomb->get_player_own() == player2->getPlayerNo()) player2->set_placed_bomb_down();
				plist_bomb->erase(plist_bomb->begin() + i);
				delete p_bomb;
				p_bomb = NULL;
				if (flag) bomb_Update(MapData, plist_bomb, plist_item, BangMid, BangLeft, BangRight, BangUp, BangDown, player1, player2, isRenderBombBang);

			}
			else p_bomb->CountDown();
		}
	}
}