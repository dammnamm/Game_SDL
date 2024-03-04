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


SDL_Texture* Object::getTexture()
{
    return tex;
}

void Object::CreateTexture(const char* filepath, SDL_Renderer* renderer)
{
    tex = TextureManager::Texture(filepath, renderer);
}
