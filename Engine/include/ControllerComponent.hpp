#ifndef CONTROLLER_COMPONENT_HPP
#define CONTROLLER_COMPONENT_HPP
#include <SDL_Headers.hpp>
#include <string>
#include "GlobalAttributes.hpp"
#include <unordered_map>
#include <string>
#include "PlayerObject.hpp"



class PlayerObject;

#include <pybind11/pybind11.h>
namespace py = pybind11;


/*!
 *  @brief Class that represents the ControllerComponent of our GameObject
 *  Handles controller input
 */
class ControllerComponent {
public:
    
    //! @brief constructrs a ControllerComponent.
    ControllerComponent();
    
    //! @brief destructs a ControllerComponent.
    ~ControllerComponent();
    
    //! @brief handles the input of our ControllerComponent
    void handleInput();

	/*!
	* @brief adds in a keybinding to this object
	* @param key: string that represents the key we want to bind
	* @param callback: a python function that we want the object to perform upon pressing the key
	* @param isPersistent: whether to call the callback function persistently for a key press
	*/
	void addInputBinding(std::string key, py::object callback, bool isPersistent);

	/*!
	 * @brief adds in a keybinding upon releasing to this object
	 * @param key: string that represents the key we want to bind when released
	 * @param callback: a python function that we want the object to perform upon releasing the key
	 * @param isPersistent: whether to call the callback function persistently for a key press
	 */
	void addInputReleaseBinding(std::string key, py::object callback, bool isPersistent);

    /*!
     * @brief goes through our map of keys and gives us a pointer of those keys
     * @return a string pointer of our keys that are binded
     */
	std::string* getKeys();

    /*!
     *  @brief iterates through our mapping of keys
     *  @return int representing the size of our map
     */
	int getKeysNum();

    //! @brief executes the python function of the key that was pressed
	void executeCallback();

    //! @brief executes the python function of the key that was released
	void executeUnCallback();

    /*!
     * @brief sets the key to determine whether it was pressed or not
     * @param key: index of our keymap
     * @param value: boolean we want to change the key to
     */
	void setKeyTo(int key, bool value);

    /*!
     * @brief sets our PlayerObject.
     * @param obj: PlayerObject we want this object to have.
     */
	void addPlayerObject(PlayerObject* obj);

    /*!
     * @return int: size of our map of keys released.
     */
	int getUnKeysNum();

    /*!
     * @return bool: determines whether any keys were pressed.
     */
	bool noKeyPressed();
    
private:
	void executeNonPersistCallback(int key);

	void executeNonPersistUnCallback(int key);

	std::unordered_map<std::string, py::object> keyToFuncMap;
	std::unordered_map<std::string, bool> keyToPersist;
	std::unordered_map<std::string, py::object> unkeyToFuncMap;
	std::unordered_map<std::string, bool> unkeyToPersist;
	std::unordered_map<std::string, bool> keypressed;
	std::unordered_map<std::string, bool> prevKeyPressed;
	PlayerObject* m_gameobject;
	bool no_key_pressed = true;
};
#endif 
