#include "spriteloader.h"
#include <vector>

class ScoreRenderer {
public:
	ScoreRenderer();

	void init(SpriteLoader& spriteLoader);
	void renderText(SDL_Renderer* renderer, int x, int y, int score);
private:
	std::vector<SDL_Texture*> numberSprites;
};