#include "game.h"
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"
#include "imguiThemes.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

bool Game::startGame() 
{
	if (!init()) return false;
	gameLoop();
}

bool Game::init() 
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Flappy", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) 
	{
		std::cout << "Failed to create a SDL Window" << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) 
	{
		std::cout << "Failed to create a SDL Renderer" << std::endl;
		return false;
	}

	ImGui::CreateContext();
	imguiThemes::gray();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg].w = 0.5f;

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	spriteLoader.loadSprites(renderer);

	gameOverTexture = spriteLoader.getLoadedSprite(RESOURCES_PATH "gameover.png");

	scoreRenderer.init(spriteLoader);

	background1.initTexture(spriteLoader);
	background2.initTexture(spriteLoader);

	background1.height = WINDOW_HEIGHT;
	background2.height = WINDOW_HEIGHT;
	background1.width = WINDOW_WIDTH;
	background2.width = WINDOW_WIDTH;
	background1.x = 0;
	background2.x = WINDOW_WIDTH;

	gameData.bird.initTexture(spriteLoader);
	gameData.bird.x = 50;
	gameData.bird.y = 150;
	gameData.bird.width = 51;
	gameData.bird.height = 36;

	gameData.score = 0;

	SDL_Surface* surface = spriteLoader.loadSurface(RESOURCES_PATH "bird.png", renderer);
	if (surface != NULL)
		SDL_SetWindowIcon(window, surface);

	srand(time(NULL));

	return true;
}

bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	float maxx1 = x1 + w1;
	float maxy1 = y1 + h1;
	float maxx2 = x2 + w2;
	float maxy2 = y2 + h2;

	return x1 < maxx2 && maxx1 > x2 && y1 < maxy2 && maxy1 > y2;
}

void Game::gameLoop() 
{
	Timer timer(250);

	bool running = true;
	bool gameOver = false;
	while (running) {
		timer.tick();

		//std::cout << timer.deltaTime << std::endl;
		sinceSpawnedPipes += timer.deltaTime;

		if (sinceSpawnedPipes > 1.5f) 
		{
			spawnPipes();

			sinceSpawnedPipes -= 1.3f + (rand() % 10) / (float)10;
		}
		
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			switch (event.type) 
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				inputHandler.SDLKeyEvent(event);
				break;
			case SDL_KEYUP:
				inputHandler.SDLKeyEvent(event);
				break;
			}
		}
		if (!gameOver)
		{
			gameData.bird.update(timer.deltaTime, inputHandler);

			background1.update(timer.deltaTime, inputHandler);
			background2.update(timer.deltaTime, inputHandler);

			if (gameData.bird.y > WINDOW_HEIGHT || gameData.bird.y < -20)
			{
				gameOver = true;
				continue;
			}

			for (int i = 0; i < gameData.pipes.size(); i++)
			{
				Pipes* pipe = gameData.pipes[i];
				pipe->update(timer.deltaTime, inputHandler);

				if (checkCollision(gameData.bird.x, gameData.bird.y, gameData.bird.width, gameData.bird.height, pipe->x, pipe->y, pipe->width, pipe->height))
				{
					gameOver = true;
					break;
				}

				if (!pipe->gaveScore && pipe->x < gameData.bird.x)
				{
					gameData.score++;
					pipe->gaveScore = true;
				}

				if (pipe->x < -pipe->width)
				{
					gameData.pipes.erase(gameData.pipes.begin() + i);
					i--;
					delete pipe;
					continue;
				}
			}
		}
		else
		{
			if (inputHandler.isKeyPressed(SDLK_SPACE) || inputHandler.isKeyPressed(SDLK_e))
			{
				resetGame();
				gameOver = false;
			}
		}

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
		/*
		ImGui::Begin("debug");

		ImGui::Text("amount of pipes: %d", gameData.pipes.size());

		ImGui::End();
		*/

		renderGame(gameOver);
	}
}

void Game::renderGame(bool isGameOver) 
{
	SDL_RenderClear(renderer);

	SDL_Rect rect = SDL_Rect();

	adjustRect(background1, rect);
	SDL_RenderCopy(renderer, background1.sprite, NULL, &rect);
	adjustRect(background2, rect);
	SDL_RenderCopy(renderer, background2.sprite, NULL, &rect);

	adjustRect(gameData.bird, rect);

	float angle = gameData.bird.yVelocity / 15.0f;

	SDL_RenderCopyEx(renderer, gameData.bird.sprite, NULL, &rect, angle, NULL, SDL_FLIP_NONE);


	for (auto it = gameData.pipes.begin(); it != gameData.pipes.end(); it++)
	{
		Pipes* pipe = *it;
		adjustRect(*pipe, rect);

		SDL_RenderCopyEx(renderer, pipe->sprite, NULL, &rect, 0, NULL, pipe->shouldBeFlipped ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
	}

	scoreRenderer.renderText(renderer, WINDOW_WIDTH / 2, 100, gameData.score);

	if (isGameOver)
	{
		rect.w = 220;
		rect.h = 50;
		rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
		rect.y = WINDOW_HEIGHT / 2 - rect.h / 2;
		SDL_RenderCopy(renderer, gameOverTexture, NULL, &rect);
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(renderer);
}

void Game::spawnPipes()
{
	float y = rand() % 400;

	Pipes* pipe1 = new Pipes();
	pipe1->initTexture(spriteLoader);
	pipe1->gaveScore = true;
	pipe1->x = 800;
	pipe1->y = y - 390;
	pipe1->width = 100;
	pipe1->height = 600;
	pipe1->shouldBeFlipped = true;
	gameData.pipes.push_back(pipe1);

	Pipes* pipe2 = new Pipes();
	pipe2->initTexture(spriteLoader);
	pipe2->gaveScore = false;
	pipe2->x = 800;
	pipe2->y = y + 390 - (rand() % 41);
	pipe2->width = 100;
	pipe2->height = 600;
	gameData.pipes.push_back(pipe2);
}

void Game::adjustRect(Entity& en, SDL_Rect& rect) 
{
	rect.x = en.x;
	rect.y = en.y;
	rect.w = en.width;
	rect.h = en.height;
}

void Game::resetGame() 
{
	for (Pipes* pipe : gameData.pipes) 
	{
		delete pipe;
	}

	gameData.pipes.clear();

	gameData = GameData{};
	gameData.bird.initTexture(spriteLoader);
	gameData.bird.x = 50;
	gameData.bird.y = 150;
	gameData.bird.width = 51;
	gameData.bird.height = 36;

	sinceSpawnedPipes = 0;
}