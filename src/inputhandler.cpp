#include "inputhandler.h"

void InputHandler::SDLKeyEvent(const SDL_Event& e) 
{
	keyStates[e.key.keysym.sym] = e.type == SDL_KEYDOWN;
}

bool InputHandler::isKeyPressed(int keyCode)
{
	return keyStates[keyCode];
}