#include "Object.h"

Object::Object()
{
    tex = NULL;
}
void Object::setSrc(int x, int y, int w, int h)
{
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}
SDL_Rect& Object::getSrc()
{
    return src;
}
void Object::setDest(int x, int y, int w, int h)
{
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}
SDL_Rect& Object::getDest()
{
    return dest;
}

void Object::scroll(int x, int k)
{
    src.x += x;
    if(src.x + src.w >k)
    {
        src.x = 0;
    }
    if(src.x < 0)
    {
        src.x = k+x;
    }
}


SDL_Texture* Object::getTexture()
{
    return tex;
}

void Object::set_y_src(int y)
{
    src.y = y;
}


void Object::CreateTexture(const char* filepath, SDL_Renderer* renderer)
{
    tex = TextureManager::Texture(filepath, renderer);
}

void Object::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}
