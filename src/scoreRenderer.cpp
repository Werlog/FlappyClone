#include "scoreRenderer.h"
#include <string>

ScoreRenderer::ScoreRenderer()
{

}

void ScoreRenderer::init(SpriteLoader& spriteLoader)
{
	numberSprites.clear();
	for (int i = 0; i < 10; i++)
	{
		std::string str = RESOURCES_PATH + std::to_string(i) + ".png";
		numberSprites.push_back(spriteLoader.getLoadedSprite(str));
	}
}

void ScoreRenderer::renderText(SDL_Renderer* renderer, int x, int y, int score)
{
	int numWidth = 30;
	int numHeight = 45;

	std::string scoreText = std::to_string(score);

	SDL_Rect rect = {x, y, numWidth, numHeight};

	rect.x -= (scoreText.length() * numWidth) / 2;

	for (int i = 0; i < scoreText.length(); i++)
	{
		int num = int(scoreText[i] - '0');
		SDL_RenderCopy(renderer, numberSprites[num], NULL, &rect);
		rect.x += 30;
	}
}