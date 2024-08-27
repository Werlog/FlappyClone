#include "entity.h"

class Bird : public Entity {
public:
	Bird();
	float yVelocity;
	void initTexture(SpriteLoader& spriteLoader);
	void update(float deltaTime, InputHandler& inputHandler);
private:
	float sinceFlapped;
};