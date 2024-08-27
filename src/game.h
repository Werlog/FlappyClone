#include <SDL2/SDL.h>
#include "timer.h"
#include "spriteloader.h"
#include "inputhandler.h"
#include "bird.h"
#include "pipes.h"
#include "scoreRenderer.h"
#include "background.h"
#include <vector>

struct GameData 
{
	int score;
	std::vector<Pipes*> pipes;
	Bird bird;
};

class Game
{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteLoader spriteLoader;
	InputHandler inputHandler;
	ScoreRenderer scoreRenderer;
	Background background1;
	Background background2;
	GameData gameData;
	

	Game() = default;

	bool startGame();
private:
	float sinceSpawnedPipes = 0;
	SDL_Texture* gameOverTexture;

	bool init();
	void gameLoop();
	void renderGame(bool isGameOver);
	void spawnPipes();
	void resetGame();
	void adjustRect(Entity& en, SDL_Rect& rect);
};