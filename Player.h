#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Map.h"
#include "Bomb.h"

class Player : public Object 
{
public:
	Player();
	Player(SDL_Renderer *des, std::vector<Bomb*> *list_bomb);
	~Player();

	virtual void HandleInput(SDL_Event e); 
	void HandleObjectCollision(GameMap &MapData); // xu li va cham voi cac vat the
	void Update(GameMap &MapData); // Update vi tri nhan vat va goi cac ham xu li va cham
	void SetBoom(GameMap &MapData);

	void setSpriteClip();
	void Render();

	void set_max_bomb(const int& number) { max_bomb_ = number; }
	void setPlayerNo() { PlayerNo_ = PlayerNo_; }
	int getPlayerNo() const { return PlayerNo_; }
	void Die() { isDied_ = true; }
	bool isDied() const { return isDied_; }
	int get_placed_bomb() const { return placed_bomb_; }
	void set_placed_bomb_down() { placed_bomb_--; }
	void set_inBomb_Object(std::string path);
	bool is_inBomb() const { return is_inBomb_; }
	void set_inBomb(const bool& inBomb);
	//Collect Item
	void set_max_bom_up() ; // tang so luong bom
	void set_length_bom_up(); // tang do dai bom
	void set_speed_boost(); // tang toc do nhan vat

	xy get_pos() const { return pos_; }
	xy set_pos(const xy &pos) { pos_ = pos; }

	
protected:
	int x_val_;
	int y_val_;
	xy pos_;
	
	enum direction {LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3} move_;
	std::vector<Bomb*> *list_bomb_;

	int max_bomb_;
	int length_bomb_;
	int speed_boost_;

	int placed_bomb_;

	bool isDied_;
	bool is_inBomb_;
	int TimeCountDown_;

	int PlayerNo_;
	bool isSetBoom_;
	std::string bomb_path_;

	std::vector<std::vector<SDL_Rect>> SpriteClip;
	int frame_ = 0;
	Object inBomb;
	std::vector<SDL_Rect> Sprite_inBomb;
	
};

class Player1 : public Player
{
public:
	Player1(SDL_Renderer* des, std::vector<Bomb*> *list_bomb, std::string path);
	~Player1();

	void HandleInput(SDL_Event e);
private:

};

class Player2 :public Player
{
public:
	Player2(SDL_Renderer* des, std::vector<Bomb*> *list_bomb, std::string path);
	~Player2();

	void HandleInput(SDL_Event e);

private:

};


#endif // !PLAYER_H
