#include "Player.h"

Player::Player()
{
	x_val_ = 0;
	y_val_ = 0;
	move_ = DOWN;
	isSetBoom_ = 0;
	isDied_ = 0;
	is_inBomb_ = 0;
	placed_bomb_ = 0;
	setSpriteClip();
}

Player::~Player()
{
	;
}

void Player::HandleInput(SDL_Event e)
{
	if (isDied_) return;
	if (e.type == SDL_KEYDOWN)
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			x_val_ = -(speed);
			move_ = LEFT;
			y_val_ = 0;
			break;
		case SDLK_RIGHT:
			x_val_ = speed;
			move_ = RIGHT;
			y_val_ = 0;
			break;
		case SDLK_UP:
			y_val_ = -(speed);
			move_ = UP;
			x_val_ = 0;
			break;
		case SDLK_DOWN:
			y_val_ = speed;
			move_ = DOWN;
			x_val_ = 0;
			break;
		case SDLK_SPACE:
			isSetBoom_ = 1;
		}
	if (e.type == SDL_KEYUP)
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: x_val_ = 0;
			break;
		case SDLK_RIGHT: x_val_ = 0;
			break;
		case SDLK_UP: y_val_ = 0;
			break;
		case SDLK_DOWN: y_val_ = 0;
			break;
		}
}


void Player::HandleObjectCollision(GameMap &MapData)
{
	/*
			        * * * * 
			(x1,y1) * * * * (x2,y1)
					* * * *
			        * * * *
			(x1,y2) * * * * (x2,y2)
	*/

	//horizontal - va cham theo chieu doc
	int x1 = (Rect_.x + (Rect_.w - TILES_SIZE) / 2 - x_val_) / TILES_SIZE;
	int x2 = (Rect_.x + (Rect_.w - TILES_SIZE) / 2 + PLAYER_WIDTH - 1 - x_val_) / TILES_SIZE;
	int y1 = (Rect_.y + (PLAYER_HIGHT - TILES_SIZE)) / TILES_SIZE;
	int y2 = (Rect_.y + PLAYER_HIGHT - 1) / TILES_SIZE;
	if (y_val_ > 0) // di xuong
	{
		if (MapData.getMapStt(y2, x1) > 0 || MapData.getMapStt(y2, x1) == BOMB_FLAG) // va cham ben trai
		{
			Rect_.y = (y2 - 1) * TILES_SIZE - (PLAYER_HIGHT - TILES_SIZE);
			int smooth_move = 1;
			while (smooth_move <= (is_inBomb_ ? 1 : speed) && Rect_.x % TILES_SIZE) // lam cho  other_player di sang ben phai
			{
				Rect_.x++;
				smooth_move++;
			}
		}
		if (MapData.getMapStt(y2, x2) > 0 || MapData.getMapStt(y2, x2) == BOMB_FLAG) // va cham ben phai
		{
			Rect_.y = (y2 - 1) * TILES_SIZE - (PLAYER_HIGHT - TILES_SIZE);
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && Rect_.x % TILES_SIZE) //lam cho other_player di sang ben trai
				{
					Rect_.x--;
					smooth_move++;
				}
			}
		}
	}
	else if (y_val_ < 0) // di len
	{
		if (MapData.getMapStt(y1, x1) > 0 || MapData.getMapStt(y1, x1) == BOMB_FLAG) // va cham ben trai
		{
			Rect_.y = (y1 + 1) * TILES_SIZE - (PLAYER_HIGHT - TILES_SIZE);
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && Rect_.y % TILES_SIZE)
				{
					Rect_.x++;
					smooth_move++;
				}
			}
		}
		if (MapData.getMapStt(y1, x2) > 0 || MapData.getMapStt(y1, x2) == BOMB_FLAG) // va cham ben phai
		{
			Rect_.y = (y1 + 1) * TILES_SIZE - (PLAYER_HIGHT - TILES_SIZE);
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && Rect_.x % TILES_SIZE)
				{
					Rect_.x--;
					smooth_move++;
				}
			}
		}
	}
	//vertical - va cham theo chieu ngang
	x1 = (Rect_.x + (Rect_.w - TILES_SIZE) / 2) / TILES_SIZE;
	x2 = (Rect_.x + (Rect_.w - TILES_SIZE) / 2 + PLAYER_WIDTH - 1) / TILES_SIZE;
	y1 = (Rect_.y + (PLAYER_HIGHT - TILES_SIZE) ) / TILES_SIZE;
	y2 = (Rect_.y + PLAYER_HIGHT - 1 ) / TILES_SIZE;

	if (x_val_ > 0) // sang phai
	{
		if (MapData.getMapStt(y1, x2) > 0 || MapData.getMapStt(y1, x2) == BOMB_FLAG) //va cham  goc tren
		{
			Rect_.x = (x2 - 1)*TILES_SIZE;
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && (Rect_.y+ PLAYER_HIGHT) % TILES_SIZE)
				{
					Rect_.y++;
					smooth_move++;
				}
			}
		}
		if (MapData.getMapStt(y2, x2) > 0 || MapData.getMapStt(y2, x2) == BOMB_FLAG) //va cham  goc duoi
		{
			Rect_.x = (x2 - 1)*TILES_SIZE;
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && (Rect_.y + PLAYER_HIGHT) % TILES_SIZE)
				{
					Rect_.y--;
					smooth_move++;
				}
			}
		}
	}
	else if (x_val_ < 0) // sang trai
	{
		if (MapData.getMapStt(y1, x1) > 0 || MapData.getMapStt(y1, x1) == BOMB_FLAG) //va cham goc tren
		{
			Rect_.x = (x1 + 1)*TILES_SIZE;
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && (Rect_.y + PLAYER_HIGHT) % TILES_SIZE)
				{
					Rect_.y++;
					smooth_move++;
				}
			}
		}
		if (MapData.getMapStt(y2, x1) > 0 || MapData.getMapStt(y2, x1) == BOMB_FLAG) //va cham  goc duoi
		{
			Rect_.x = (x1 + 1)*TILES_SIZE;
			int smooth_move = 1;
			{
				while (smooth_move <= (is_inBomb_ ? 1 : speed) && (Rect_.y + PLAYER_HIGHT) % TILES_SIZE)
				{
					Rect_.y--;
					smooth_move++;
				}
			}
		}
	}
}

void Player::Update(GameMap &MapData, const Player* other_player)
{
	//Update bomb
	if (isSetBoom_) PlaceBoom(MapData);


	ifor(list_bomb_->size()) {
		list_bomb_->at(i)->UpdateMapStt(MapData, pos_);
	}
	if(MapData.getMapStt(pos_.second, pos_.first) == PlayerNo_) MapData.setPlayerPos(pos_, NULL);
	pos_.first = (Rect_.x + PLAYER_WIDTH /2) / TILES_SIZE;
	pos_.second = (Rect_.y + (PLAYER_HIGHT - TILES_SIZE) + TILES_SIZE / 2) / TILES_SIZE;
	MapData.setPlayerPos(pos_, PlayerNo_);

	//Update move
	if (!is_inBomb_) {
		Rect_.x += x_val_;
		Rect_.y += y_val_;
	}
	else {
		if(x_val_ != 0) Rect_.x += (x_val_ > 0 ? 1 : -1);
		if(y_val_ != 0) Rect_.y += (y_val_ > 0 ? 1 : -1);
	}

	HandleObjectCollision(MapData);

	if (is_inBomb_) {
		
		if (TimeCountDown_ == 0 || pos_ == other_player->get_pos()) {
			Die();
			frame_ = 0;
		}
		else TimeCountDown_--;
	}
}

void Player::PlaceBoom(GameMap &MapData)
{
	isSetBoom_ = 0;
	if (!(placed_bomb_ < max_bomb_) || is_inBomb_) return;
	int x = 0, y = 0;

	x = (Rect_.x + TILES_SIZE / 2) / TILES_SIZE;
	y = (Rect_.y + (PLAYER_HIGHT - TILES_SIZE) + TILES_SIZE / 2) / TILES_SIZE;
	
	int flag = true;
	ifor(list_bomb_->size())
		if (xy(x, y) == list_bomb_->at(i)->getPos()) flag = false;
	if (flag)
	{
		placed_bomb_++;
		MapData.setBomb(y, x);
 		Bomb* newBomb = new Bomb();
		newBomb->set_player_own(PlayerNo_);
		newBomb->loadIMG(Render_des, bomb_path_);
		newBomb->setSpriteClip();
		newBomb->setPos(y, x);
		newBomb->setLength_bang(length_bomb_);
		list_bomb_->push_back(newBomb);
	}
}

void Player::setSpriteClip()
{

	SpriteClip.resize(4);
	ifor(4) SpriteClip[i].resize(5);
	ijfor(4, 5) 
		SpriteClip[i][j] = { j * PLAYER_WIDTH, i * PLAYER_HIGHT, PLAYER_WIDTH, PLAYER_HIGHT };

	Sprite_inBomb.resize(SPRITE_CLIPS_IN_BOMB);
	ijfor(2, 5) {
		Sprite_inBomb[5 * i + j] = { j * IN_BOMB_SIZE, i*IN_BOMB_SIZE + 260, IN_BOMB_SIZE, IN_BOMB_SIZE };
	}
	

	
}

void Player::Render()
{
	//Render other_player
	if (!isDied_)
	{
		if (!is_inBomb_)
		{
			set_Size(PLAYER_WIDTH, PLAYER_HIGHT);
			if (x_val_ || y_val_)
			{
				frame_ %= 40;
				SDL_RenderCopy(Render_des, pObject_, &SpriteClip[move_][frame_++ / 10 + 1], &Rect_);
				// reset frame
			}
			else
				SDL_RenderCopy(Render_des, pObject_, &SpriteClip[move_][0], &Rect_);
		}
		else
		{
			set_Size(IN_BOMB_SIZE, IN_BOMB_SIZE);
			//5 giai doan animation
			if (TimeCountDown_ > PLAYER_IN_BOMB_COUNT_DOWN - FRAME_INBOM_STEP1)
			{
				
				SDL_RenderCopy(Render_des, pObject_, &Sprite_inBomb[(frame_++ / (FRAME_INBOM_STEP1 / 3)) % 3], &Rect_);
			}
			else if (TimeCountDown_ > PLAYER_IN_BOMB_COUNT_DOWN - FRAME_INBOM_STEP2)
			{
				
				SDL_RenderCopy(Render_des, pObject_, &Sprite_inBomb[(frame_++ / 10) % 2 + 3], &Rect_);
			}
			else if (TimeCountDown_ > PLAYER_IN_BOMB_COUNT_DOWN - FRAME_INBOM_STEP3)
			{
				
				SDL_RenderCopy(Render_des, pObject_, &Sprite_inBomb[(frame_++ / 10) % 2 + 5], &Rect_);
			}
			else if (TimeCountDown_ > PLAYER_IN_BOMB_COUNT_DOWN - FRAME_INBOM_STEP4)
			{
				SDL_RenderCopy(Render_des, pObject_, &Sprite_inBomb[(frame_++ / 10) % 2 + 7], &Rect_);
			}
			else {
				SDL_RenderCopy(Render_des, pObject_, &Sprite_inBomb[9], &Rect_);
			}
		}
	}
}


void Player::set_inBomb(const bool & inWater)
{
	if (!is_inBomb_)
	{
		TimeCountDown_ = PLAYER_IN_BOMB_COUNT_DOWN;
		is_inBomb_ = 1;
		frame_ = 0;
	}
}

void Player::set_max_bom_up()
{
	if (max_bomb_ < Info[Charactor].Limit_Bomb)
	{
		max_bomb_++;
	}
}

void Player::set_length_bom_up()
{
	if (length_bomb_ < Info[Charactor].Limit_Length)
	{
		length_bomb_++;
	}
}

void Player::set_speed_boost()
{
	if (speed < Info[Charactor].Limit_Speed)
	{
		speed++;
	}
}


Player1::Player1(SDL_Renderer* des, Charactors Charactor, std::vector<Bomb*> *list_bomb)
{
	

	this->Charactor = Charactor;
	length_bomb_ = Info[Charactor].Start_Length;
	max_bomb_ = Info[Charactor].Start_Bomb;
	speed = Info[Charactor].Start_Speed;

	
	PlayerNo_ = PLAYER_1;

	this->list_bomb_ = list_bomb;

	bomb_path_ = "Bin/Images/bomb.png";
	loadIMG(des, Info[Charactor].path);
	Rect_.w = PLAYER_WIDTH;
	Rect_.h = PLAYER_HIGHT;

	this->Render_des = des;
}

Player1::~Player1()
{
}


void Player1::HandleInput(SDL_Event e)
{
	if (isDied_) return;
	if (e.type == SDL_KEYDOWN)
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			x_val_ = -(speed);
			move_ = LEFT;
			y_val_ = 0;
			break;
		case SDLK_d:
			x_val_ = speed;
			move_ = RIGHT;
			y_val_ = 0;
			break;
		case SDLK_w:
			y_val_ = -(speed);
			move_ = UP;
			x_val_ = 0;
			break;
		case SDLK_s:
			y_val_ = speed;
			move_ = DOWN;
			x_val_ = 0;
			break;
		case SDLK_SPACE:
			isSetBoom_ = 1;
		}
	if (e.type == SDL_KEYUP)
		switch (e.key.keysym.sym)
		{
		case SDLK_a: x_val_ = 0;
			break;
		case SDLK_d: x_val_ = 0;
			break;
		case SDLK_w: y_val_ = 0;
			break;
		case SDLK_s: y_val_ = 0;
			break;
		}
}

Player2::Player2(SDL_Renderer* des, Charactors Charactor, std::vector<Bomb*> *list_bomb)
{

	this->Charactor = Charactor;
	length_bomb_ = Info[Charactor].Start_Length;
	max_bomb_ = Info[Charactor].Start_Bomb;
	speed = Info[Charactor].Start_Speed;

	PlayerNo_ = PLAYER_2;
	this->list_bomb_ = list_bomb;

	bomb_path_ = "Bin/Images/bomb3.png";
	loadIMG(des, Info[Charactor].path);
	Rect_.w = PLAYER_WIDTH;
	Rect_.h = PLAYER_HIGHT;

	this->Render_des = des;
}

Player2::~Player2()
{
}

void Player2::HandleInput(SDL_Event e)
{
	if (isDied_) return;
	if (e.type == SDL_KEYDOWN)
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			x_val_ = -(speed);
			move_ = LEFT;
			y_val_ = 0;
			break;
		case SDLK_RIGHT:
			x_val_ = speed;
			move_ = RIGHT;
			y_val_ = 0;
			break;
		case SDLK_UP:
			y_val_ = -(speed);
			move_ = UP;
			x_val_ = 0;
			break;
		case SDLK_DOWN:
			y_val_ = speed;
			move_ = DOWN;
			x_val_ = 0;
			break;
		case SDLK_RSHIFT:
			isSetBoom_ = 1;
		}
	if (e.type == SDL_KEYUP)
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: x_val_ = 0;
			break;
		case SDLK_RIGHT: x_val_ = 0;
			break;
		case SDLK_UP: y_val_ = 0;
			break;
		case SDLK_DOWN: y_val_ = 0;
			break;
		}
}
