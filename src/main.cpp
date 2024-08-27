#include <SDL2/SDL.h>
#include <iostream>
#undef main


//imgui stuff
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"
#include "imguiThemes.h"
#include "game.h"


int main(int argc, char *argv[])
{
	Game game;
	if (!game.startGame()) 
	{
		std::cout << "Cannot start the game" << std::endl;
		return 1;
	}
}
