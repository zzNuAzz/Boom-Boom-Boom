#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Object.h"

namespace Explosions{
	enum Type{LEFT, RIGHT, UP, DOWN, MID};
}
extern Object BangMid;
extern Object BangLeft;
extern Object BangRight;
extern Object BangUp;
extern Object BangDown;
class Explosion;
extern std::vector<Explosion*> ExplosionQueue;
class Explosion
{
public:
	Explosion(Explosions::Type type);
	~Explosion();

	void Render();
	bool Finished() const { return (frame_ > 16); }
	void setRect(const int& x, const int& y) { Rect_.x = x; Rect_.y = y;}

private:
	int frame_;
	SDL_Rect Rect_;
	SDL_Rect Sprite_clips[2];
	Object* pObject;

};

void LoadExplosion(SDL_Renderer* gRenderer);

#endif // !EXPLOSION_H
