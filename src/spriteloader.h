#pragma once

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>

class SpriteLoader {
public:
	SpriteLoader() = default;

	~SpriteLoader();

	std::unordered_map<std::string, SDL_Texture*> sprites;

	void loadSprites(SDL_Renderer* renderer);
	void loadSprite(const char* path, SDL_Renderer* renderer);
	SDL_Surface* loadSurface(const char* path, SDL_Renderer* renderer);

	SDL_Texture* getLoadedSprite(std::string path);
};