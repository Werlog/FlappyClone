#include "bird.h"

Bird::Bird() 
{
	sinceFlapped = 0;
	yVelocity = 0;
}

void Bird::update(float deltaTime, InputHandler& inputHandler)
{
	sinceFlapped += deltaTime;
	yVelocity += 1200 * deltaTime;
	if (sinceFlapped > 0.3f && inputHandler.isKeyPressed(SDLK_w))
	{
		yVelocity = -410;
		sinceFlapped = 0;
	}

	y += yVelocity * deltaTime;
}

void Bird::initTexture(SpriteLoader& spriteLoader) 
{
	sprite = spriteLoader.getLoadedSprite(RESOURCES_PATH "bird.png");
}