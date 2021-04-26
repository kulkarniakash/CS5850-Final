#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include<Camera.h>
#include "tst_GraphicsEngineRenderer.hpp"
#include "ResourceManager.hpp"

//! @brief This class sets up the main game engine
class Engine{
public:
    
    //! Constructor of Engine
    Engine();
    
    //! Destructor
    ~Engine();
    /*!
     * @brief handles input of our engine
     * @param quit: boolean to determine if the user quits
     * @param code: SDL_Keycode determining the key the user inputted
     */
    void Input(bool *quit, SDL_Keycode& code);
    
    /*!
     * @brief Updates our camera
     * @param code: SDL_Keycode to determine the Direction the user inputted
     */
    void Update(SDL_Keycode code);
    
    //! @brief Renders everything per frame
    void Render();
    
    //! @brief Main Game Loop that runs forever
    void MainGameLoop();
    
    //! @brief Explicitly call 'Start' to launch the engine
    void Start();
    
    
    //! @brief Explicitly call 'Shutdown' to terminate the engine
    void Shutdown();

    //! @brief Request to startup the Graphics Subsystem
	void InitializeGraphicsSubSystem();


private:
    // Engine Subsystem
    // Setup the Graphics Rendering Engine
    GraphicsEngineRenderer* m_renderer = nullptr;
	Camera* camera;
	SDL_Texture* text;
};

#endif
