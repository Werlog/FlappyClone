#include "pipes.h"

void Pipes::initTexture(SpriteLoader& spriteLoader) 
{
	sprite = spriteLoader.getLoadedSprite(RESOURCES_PATH "pipe-green.png");
}

void Pipes::update(float deltaTime, InputHandler& inputHandler) 
{
	x -= 220 * deltaTime;
}