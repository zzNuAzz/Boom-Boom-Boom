#include "Object.h"

Object::Object()
{
	pObject_ = NULL;
	Rect_ = { 0,0,0,0 };
}

Object::Object( SDL_Renderer * des,  const std::string& path)
{
	this->Render_des = des; 
	Rect_ = { 0,0,0,0 };
	loadIMG(path);
}

Object::~Object(){
	SDL_DestroyTexture(pObject_);
	pObject_ = NULL;
}

void Object::loadIMG( SDL_Renderer * des,const std::string& path)
{
	this->Render_des = des;
	loadIMG(path);
}

void Object::loadIMG(const std::string& path)
{
	SDL_Surface* loadedSurface = NULL;
	SDL_Texture* newTexture = NULL;
	loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		Rect_.w = loadedSurface->w;
		Rect_.h = loadedSurface->h;
		newTexture = SDL_CreateTextureFromSurface(Render_des, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Could not create texture form surface, IMG_path: " << path << '\n' << SDL_GetError() << '\n';
		}
	}
	else std::cout << "Could not load image: " << path << '\n' << SDL_GetError() << '\n';
	pObject_ = newTexture;
	SDL_FreeSurface(loadedSurface);
	loadedSurface = NULL;
}

void Object::Render(const SDL_Rect* Clips)
{
	SDL_RenderCopy(Render_des, pObject_, Clips, &Rect_);
}

void Object::Render(const SDL_Rect &desRect, const SDL_Rect * Clips)
{
	SDL_RenderCopy(Render_des, pObject_, Clips, &desRect);
}
