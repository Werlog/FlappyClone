#include "entity.h"
#include <SDL2/SDL.h>

Entity::Entity() 
{
	x = 0;
	y = 0;
	width = 50;
	height = 50;
}

void Entity::update(float deltaTime, InputHandler& inputHandler)
{
	
}

void Entity::initTexture(SpriteLoader& spriteLoader)
{

}