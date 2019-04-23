#include "Item.h"


Item_Image::Item_Image()
{
}

Item_Image::Item_Image(SDL_Renderer * des, std::string path)
{
	loadIMG(des, path);
}

Item_Image::~Item_Image()
{
}


Item::Item()
{
	type_item_ = NULL;
	pos_ = xy(0, 0);
	is_available_ = 1;
	isHide_ = 0;
}

Item::Item(const int & type_item)
{
	type_item_ = type_item;
	pos_ = xy(0, 0);
	is_available_ = 1;
	isHide_ = 0;
}

Item::~Item()
{
	type_item_ = NULL;
	pos_ = xy(0, 0);
}

void Item::Update(std::vector<Item*>* plist_item, GameMap & MapData, Player * player1, Player * player2)
{
	ifor(plist_item->size())
		if (plist_item->at(i)->is_available() == 0)
		{
			plist_item->erase(plist_item->begin() + i);
		}

	if (MapData.getMapStt(pos_.second, pos_.first) > 0)
	{
		isHide_ = 1;
	}
	else if (MapData.getMapStt(pos_.second, pos_.first) == BOMB_FLAG)
	{
		is_available_ = 0;
	}
	else {
		isHide_ = 0;
	}
	if (isHide_ || !is_available_) return;
	if (pos_ == player1->get_pos())
	{
		switch (type_item_)
		{
		case WATER_BALLON:
			player1->set_max_bom_up();
			break;
		case WATER_BOTTLE:
			player1->set_length_bom_up();
			break;
		case RED_SHOE:
			player1->set_speed_boost();
			break;
		}
		is_available_ = 0;
	}
	else if (pos_ == player2->get_pos())
	{
		switch (type_item_)
		{
		case WATER_BALLON:
			player2->set_max_bom_up();
			break;
		case WATER_BOTTLE:
			player2->set_length_bom_up();
			break;
		case RED_SHOE:
			player2->set_speed_boost();
			break;
		}
		is_available_ = 0;
	}

}

void Item::Render()
{
	if (!isHide_)
	{
		item_img->SetRect(get_pos());
		item_img->Render();
	}
}

void RandomItemMap(GameMap & MapData, std::vector<Item*>* plist_item, std::vector<Item_Image*> *ItemImage)
{
	srand(0);
	ijfor(MAP_ROW, MAP_COL)
	{
		if (i > 0 && i < MAP_ROW - 1 && j > 0 && j < MAP_COL - 1 && MapData.getMapStt(i, j) > 0 && !MapData.get_isHartTiles(MapData.getMapStt(i, j)))
		{
			int random_item = rand()%(NUMBER_ITEM*2 - RATIO_APPEAR_ITEM);
			switch (random_item)
			{
			case WATER_BALLON:
			{
				Item* p_ballon = new Item(WATER_BALLON);
				p_ballon->set_item_img(ItemImage->at(WATER_BALLON));
				p_ballon->set_pos(xy(j, i));
				plist_item->push_back(p_ballon);
				break;
			}
			case WATER_BOTTLE:
			{
				Item* p_bottle = new Item(WATER_BOTTLE);
				p_bottle->set_item_img(ItemImage->at(WATER_BOTTLE));
				p_bottle->set_pos(xy(j, i));
				plist_item->push_back(p_bottle);
				break;
			}
			case RED_SHOE:
			{
				Item* p_red_shoe = new Item(RED_SHOE);
				p_red_shoe->set_item_img(ItemImage->at(RED_SHOE));
				p_red_shoe->set_pos(xy(j, i));
				plist_item->push_back(p_red_shoe);
				break;
			}
			}
		}
	}
}
