#ifndef OBJECT_H
#define OBJECT_H

#include "TextureManager.h"

class Object
{
private:
	SDL_Texture* tex;
public:
	Object();
	SDL_Rect src, dest;
	void setSrc(int x, int y, int w, int h);
	void setDest(int x, int y, int w, int h);
	void set_y_src(int y);
	void set_size(int x, int y);
	void scroll(int x, int k);
	SDL_Texture* getTexture();
	SDL_Rect& getSrc();
	SDL_Rect& getDest();
	void CreateTexture(const char* filepath, SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
};

#endif // OBJECT_H
