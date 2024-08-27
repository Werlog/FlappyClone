#include "entity.h"

class Pipes : public Entity
{
public:
	bool shouldBeFlipped;
	bool gaveScore;

	void initTexture(SpriteLoader& spriteLoader);
	void update(float deltaTime, InputHandler& inputHandler);
};