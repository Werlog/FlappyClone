#include "background.h"

void Background::initTexture(SpriteLoader& spriteLoader) 
{
	sprite = spriteLoader.getLoadedSprite(RESOURCES_PATH "background-day.png");
}

void Background::update(float deltaTime, InputHandler& inputHandler) 
{
	x -= 30 * deltaTime;

	if (x < -width) {
		x = width;
	}
}