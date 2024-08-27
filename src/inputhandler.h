#pragma once

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>

class InputHandler {
public:
	InputHandler() = default;

	std::unordered_map<int, bool> keyStates;

	void SDLKeyEvent(const SDL_Event& e);
	bool isKeyPressed(int keyCode);
};