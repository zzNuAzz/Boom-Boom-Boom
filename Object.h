#ifndef OBJECT_H
#define OBJECT_H

#include "ConstAndGlobalVar.h"

class Object
{
public:
	Object();
	Object(SDL_Renderer *des, const std::string& path);
	~Object();
	void loadIMG(SDL_Renderer* des,const std::string& path);
	void loadIMG(const std::string& path);
	virtual	void Render(const SDL_Rect* Clips = NULL);
	virtual void Render(const SDL_Rect &desRect, const SDL_Rect* Clips = NULL);
	void set_Size(const int& w, const int& h) { Rect_.w = w; Rect_.h = h; }
	void SetRect(const int& x, const int &y) { Rect_.x = x; Rect_.y = y; }
	void SetRect(const xy& pos) { Rect_.x = pos.first*TILES_SIZE; Rect_.y = pos.second*TILES_SIZE; }
	SDL_Rect GetRect() const { return Rect_; }
	SDL_Texture* get_pObject() const { return pObject_; }

protected:
	SDL_Renderer* Render_des;
	SDL_Texture* pObject_;
	SDL_Rect Rect_;

};


#endif // !OBJECT_H
