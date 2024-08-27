#include <stdint.h>

class Timer {
public:
	Timer(int maxFramerate);

	float deltaTime;

	void tick();
private:
	uint64_t lastTicks;
	float minDeltaTime;
};