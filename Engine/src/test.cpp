#include <iostream>
#include <SDL_Headers.hpp>
#include <GameObject.hpp>
#include <TransformComponent.hpp>
#include <SpriteComponent.hpp>
#include <ControllerComponent.hpp>
#include <Engine.hpp>

/*#if defined(MINGW) || defined(LINUX)
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif*/

int main(int argc, char* argv[])
{
	std::cout << "Running platformer game " << std::endl;
	// Create an instance of an object for our engine
	Engine engine;
	// Initialize the Engine Subsystems
	engine.InitializeGraphicsSubSystem();
	// Once all subsystems have been initialized
	// Start the engine
	engine.Start();
	// Run our program forever
	engine.MainGameLoop();
	// Explicitly call Shutdown to terminate our engine
	engine.Shutdown();
	// When our program ends, it will exit scope,
	// the destructor will then be called
	// and clean up the program.
	return 0;
}