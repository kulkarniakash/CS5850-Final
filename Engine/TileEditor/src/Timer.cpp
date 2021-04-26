#include<cstdint>
#include "Timer.h"

// used advanced timer link (lazy foo) given in the readme of the assignment as a guide
MyTimer::MyTimer() {
	startTicks = 0;
	pauseTicks = 0;
	isPaused = false;
	hasStarted = false;
}

void MyTimer::start() {
	startTicks = SDL_GetTicks();
	pauseTicks = 0;
	isPaused = false;
	hasStarted = true;
}

void MyTimer::stop() {
	startTicks = 0;
	pauseTicks = 0;
	isPaused = false;
	hasStarted = false;
}

void MyTimer::pause() {
	if (hasStarted && !isPaused) {
		isPaused = true;
		pauseTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void MyTimer::unpause() {
	if (hasStarted && isPaused) {
		isPaused = false;
		startTicks = SDL_GetTicks() - pauseTicks;
		pauseTicks = 0;
	}
}

uint32_t MyTimer::getTicks() {
	if (hasStarted) {
		if (isPaused) {
			return pauseTicks;
		}
		else {
			return SDL_GetTicks() - startTicks;
		}
	}

	return 0;
}

bool MyTimer::hasStartedF() {
	return hasStarted;
}

bool MyTimer::isPausedF() {
	return isPaused;
}