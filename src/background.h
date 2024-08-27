#include "entity.h"

class Background : public Entity 
{
public:
	void initTexture(SpriteLoader& spriteLoader);
	void update(float deltaTime, InputHandler& inputHandler);
};