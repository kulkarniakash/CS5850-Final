#ifndef TIMERCLASS
#define TIMERCLASS

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

class MyTimer {
public:
	MyTimer();

	void start();

	void stop();

	void pause();

	void unpause();

	uint32_t getTicks();

	bool hasStartedF();

	bool isPausedF();

private:
	uint32_t startTicks;
	uint32_t pauseTicks;

	bool isPaused;
	bool hasStarted;

};

#endif 

