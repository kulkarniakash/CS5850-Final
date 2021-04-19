#ifndef ENGINE
#define ENGINE
#include <iostream>
#include <stdlib.h>
#include <string>
#include <SDL_Headers.hpp>
#include <unordered_set>
#include <unordered_map>
#include <GameObject.hpp>
#include <string>

//Engine class was taken from Sumanth's assignment-2 repo. Written by Shreyas Shivashankar.
class Engine
{

public:
    /**
   * Constructor of Engine
   */
    Engine();
    /**
   * Destructor
   */
    ~Engine();
    /**
   * Input engine
   */
    void Input();
    /**
   * Per frame update
   * @param dt The delta time between 2 consecutive frames
   */
    void Update(float dt);
    /**
   * Per frame render. Renders everything
   */
    void Render();
    /**
   * Main Game Loop that runs forever
   */
    void MainGameLoop();
    /**
   * Initialization and shutdown pattern
   * Explicitly call 'Start' to launch the engine
   */
    void Start();
    /**
   * Initialization and shutdown pattern
   * Explicitly call 'Shutdown' to terminate the engine
   */
    void Shutdown();
    /**
   * Request to startup the Graphics Subsystem
   */
  //TODO: setup a graphics subsystem
    int InitializeGraphicsSubSystem();

	bool programEnded();

	void clear();

	void delay(int seconds);

	void addGameObject(GameObject* obj);

private:

	bool quit;
	std::unordered_set<GameObject*> gameObjs;
};


#endif