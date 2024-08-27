#include "timer.h"
#include <SDL2/SDL.h>

Timer::Timer(int maxFramerate) {
	deltaTime = 0;
	lastTicks = 0;
	minDeltaTime = (float)1 / maxFramerate;
}

void Timer::tick() {
	uint64_t currentTicks = SDL_GetTicks64();

	deltaTime = (currentTicks - lastTicks) / (float)1000;

	if (deltaTime < minDeltaTime) 
	{
		SDL_Delay((uint32_t)((minDeltaTime - deltaTime) * 1000));

		currentTicks = SDL_GetTicks64();
		deltaTime = (currentTicks - lastTicks) / (float)1000;
	}

	lastTicks = currentTicks;
}