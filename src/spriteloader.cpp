#pragma once

#include "spriteloader.h"
#include <SDL2/SDL.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include <string>

#define RMASK 0x000000FF
#define GMASK 0x0000FF00
#define BMASK 0x00FF0000
#define AMASK 0xFF000000

SpriteLoader::~SpriteLoader() {
	for (auto it = sprites.begin(); it != sprites.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
}

void SpriteLoader::loadSprites(SDL_Renderer* renderer)
{
	loadSprite(RESOURCES_PATH "background-day.png", renderer);
	loadSprite(RESOURCES_PATH "bird.png", renderer);
	loadSprite(RESOURCES_PATH "pipe-green.png", renderer);
	loadSprite(RESOURCES_PATH "gameover.png", renderer);

	for (int i = 0; i < 10; i++)
	{
		std::string str = RESOURCES_PATH + std::to_string(i) + ".png";
		loadSprite(str.c_str(), renderer);
	}
}

void SpriteLoader::loadSprite(const char* path, SDL_Renderer* renderer)
{
	std::cout << "Loading sprite at " << path << std::endl;
	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

	if (data == NULL) 
	{
		std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
		return;
	}
	
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(data, width, height, channels * 8, width * channels, RMASK, GMASK, BMASK, channels == 4 ? AMASK : 0);

	if (surface == NULL) 
	{
		std::cout << "Failed to load SDL surface: " << SDL_GetError() << std::endl;
		stbi_image_free(data);
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	stbi_image_free(data);

	std::string spritePath = path;

	sprites.insert({spritePath, texture});
}

SDL_Surface* SpriteLoader::loadSurface(const char* path, SDL_Renderer* renderer) 
{
	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

	if (data == NULL)
	{
		std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
		return NULL;
	}

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(data, width, height, channels * 8, width * channels, RMASK, GMASK, BMASK, channels == 4 ? AMASK : 0);
	if (surface == NULL) 
	{
		std::cout << "Failed to load surface" << SDL_GetError() << std::endl;
		return NULL;
	}



	stbi_image_free(data);

	return surface;
}

SDL_Texture* SpriteLoader::getLoadedSprite(std::string path) 
{
	return sprites[path];
}