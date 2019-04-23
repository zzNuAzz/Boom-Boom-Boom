#ifndef ITEM_H
#define ITEM_H
#include "Object.h"
#include "Player.h"

class Item_Image : public Object
{
public:
	Item_Image();
	Item_Image(SDL_Renderer* des, std::string path);
	~Item_Image();

private:

};

class Item 
{
public:
	Item();
	Item(const int& type_item);
	~Item();


	void Update(std::vector<Item*>* plist_item, GameMap &MapData, Player* player1, Player* player2);
	void Show() { isHide_ = 0; }
	void Hide() { isHide_ = 1; }
	void Render();

	void set_type_item(const int& type) {int type_item_ = type; }
	void set_pos(const xy& pos) { pos_ = pos; }
	xy get_pos() const { return pos_; }
	void set_item_img(Item_Image* Item_Image) { item_img = Item_Image; }
	Item_Image* get_item_img() const { return item_img; }
	

	bool is_available() const { return is_available_; }
	void destroy() { is_available_ = 0; Hide(); }
	
private:
	int type_item_;
	xy pos_;
	Item_Image* item_img;
	int isHide_;
	bool is_available_;
};


void RandomItemMap(GameMap &MapData, std::vector<Item*>* plist_item, std::vector<Item_Image*> *ItemImage);

#endif // !ITEM_H


