#include "Explosion.h"

Object BangMid;
Object BangLeft;
Object BangRight;
Object BangUp;
Object BangDown;

Explosion::Explosion(Explosions::Type type)
{
	frame_ = 0;
	Rect_ = { 0,0,TILES_SIZE, TILES_SIZE };
	ifor(2) Sprite_clips[i] = { i * TILES_SIZE, 0, TILES_SIZE, TILES_SIZE };
	switch (type)
	{
	case Explosions::LEFT:
		pObject = &BangLeft;
		break;
	case Explosions::RIGHT:
		pObject = &BangDown;
		break;
	case Explosions::UP:
		pObject = &BangUp;
		break;
	case Explosions::DOWN:
		pObject = &BangDown;
		break;
	case Explosions::MID:
		pObject = &BangMid;
		break;
	}
}
std::vector<Explosion*> ExplosionQueue;

Explosion::~Explosion()
{
}

void Explosion::Render()
{
	pObject->Render(Rect_, &Sprite_clips[frame_++ % 4/2]);
}

void LoadExplosion(SDL_Renderer * gRenderer)
{
	BangMid.loadIMG(gRenderer, "Bin//Images//BangMid.png");
	BangLeft.loadIMG(gRenderer, "Bin//Images//BangLeft.png");
	BangRight.loadIMG(gRenderer, "Bin//Images//BangRight.png");
	BangUp.loadIMG(gRenderer, "Bin//Images//BangUp.png");
	BangDown.loadIMG(gRenderer, "Bin//Images//BangDown.png");
	
}
