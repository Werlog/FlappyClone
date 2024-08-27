#pragma once

#include <SDL2/SDL.h>
#include "inputhandler.h"
#include "spriteloader.h"

class Entity {
public:
	SDL_Texture* sprite;
	float x, y;
	int width, height;

	Entity();

	virtual void initTexture(SpriteLoader& spriteLoader);
	virtual void update(float deltaTime, InputHandler& inputHandler);
};