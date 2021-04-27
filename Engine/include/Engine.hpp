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
#include <GraphicsEngineRenderer.hpp>
#include "AnimateObject.hpp"
#include <vector>
#include "PlayerObject.hpp"
#include "UniversalForce.hpp"
#include "TileManager.hpp"
#include "UIComponent.hpp"
#include <map>
#include <pybind11/pybind11.h>

namespace py = pybind11;


/*!
 * @brief class that represents our Engine, handles starting, looping, updating and shutting down our engine
 * taken from Sumanth's assignment-2 repo. Written by Shreyas Shivashankar.
 */
class Engine
{

public:
  //! @brief Constructor of our Engine
  Engine();
    
  //! @brief Destrcutor of our Engine
  ~Engine();
  
  //! @brief Handles all input of our GameObjects
  void Input();
  
  //! @brief Updates all of our Objects
  void update();
  
  //! @brief Renders all of our Objects
  void Render();
    
  //! @brief Handles updating our game until user decides to quit
  void MainGameLoop();
    
  /*!
   * @brief Initialization and shutdown pattern
   * Explicitly call 'Start' to launch the engine
   */
  void Start();
    
  /*!
   * @brief Initialization and shutdown pattern
   * Explicitly call 'Shutdown' to terminate the engine
   */
  void Shutdown();
    
  /*!
    * @brief Request to startup the Graphics Subsystem
    * @return Int that represents whether setting up our graphics was successful or not.
    */
  int InitializeGraphicsSubSystem();

  //! @return Boolean that determine whether the program has ended or not
	bool programEnded();

  //! @brief Clears our renderer
	void clear();

  //! @brief Delays our program until it is within our set number of frames
	void delay(int seconds);

  /*!
    * @brief Adds a GameObject to our vector of GameObjects
    * @param obj: GameObject we want to add
    */
	void addGameObject(GameObject* obj);

  /*!
    * @brief Adds a GameObject to our vector of GameObjects
    * @param obj: AnimateObject we want to add
    */
	void addAnimateObject(AnimateObject* obj);

  /*!
    * @brief Adds a PlayerObject to our vector of GameObjects
    * @param obj: PlayerObject we want to add
    */
	void addPlayerObject(PlayerObject* obj);

  /*!
    * @brief Adds a UniversalForce function object
    * @param object: a python function object we want to add
    */
	void addUFCallback(py::object);

  /*!
    * @brief Add a Tile Manager to the Engine by converting tiles to GameObjects
    * @param tm: TileManager to be added to the Engine
    */
	void addTileManager(TileManager* tm);

  /*!
    * @brief Add a UIComponent to the Engine into the vector field uiComponents.
    * @param ui: UIComponent to be added to the Engine
    */
  void addUIComponent(UIComponent* ui);

  /*!
    * @brief Destroys the specified object
    * @param objectName: Name of the object to be destroyed
    */
  void destroyObject(std::string objectName);

  /*!
    * @brief Return the timer time in a float format.
    * @return float timer time
    */
  float getTime();

  /*!
    * @brief Set the timer to the given miliseconds.
    * @param miliseconds time in miliseconds to set the timer to
    */
  void setTimer(float miliseconds);

  /*!
    * @brief Pause the timer
    */
  void stopTimer();

  /*!
    * @brief Resets the timer to the initial set time.
    */
  void resetTimer();

  /*!
    * @brief Resets the game. Resets the vector fields and the
    */
  void reset();

private:

	bool quit;
	std::vector<PlayerObject*> playerObjs;
	std::vector<AnimateObject*> animateObjs;
	std::vector<GameObject*> gameObjs;
  std::vector<UIComponent*> uiComponents;
  std::map<std::string, int> destroyedObjs;
	UniversalForce uforce;
  float m_timer = 0.0f;
  float m_init_timer = 0.0f;
  bool m_timerStopped = false;
};
#endif

