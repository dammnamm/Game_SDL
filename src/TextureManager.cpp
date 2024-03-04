#include "TextureManager.h"

SDL_Texture* TextureManager::Texture(const char* filepath, SDL_Renderer* renderer)
{
    SDL_Surface* surface;
    surface = IMG_Load(filepath);
    if(surface == NULL) {
        std::cout << "Unable to load img!" <<  IMG_GetError() << std::endl;
    }
    SDL_Texture* tex;
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    return tex;
}
