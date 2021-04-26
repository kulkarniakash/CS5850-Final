#ifndef TIMERCLASS
#define TIMERCLASS

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

//! @brief Class that represents a timer, handles setting and retriving information regarding ticks
class MyTimer {
public:
    
    //! @brief constructor for MyTimer
	MyTimer();

    //! @brief starts the timer
	void start();

    
    //! @brief stops the timer
	void stop();

    //! @brief pauses the timer
	void pause();

    //! @brief unpauses the Timer
	void unpause();

    //! @return the number of ticks that passed by
	uint32_t getTicks();

    //! @return boolean value whether the timer has started or not
	bool hasStartedF();

    //! @return boolean value whether the timer is paused or not
	bool isPausedF();

private:
	uint32_t startTicks;
	uint32_t pauseTicks;

	bool isPaused;
	bool hasStarted;

};

#endif 

