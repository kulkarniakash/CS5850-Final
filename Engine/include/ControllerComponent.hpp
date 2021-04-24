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

class ControllerComponent {
public:
    //constructrs a controller
    ControllerComponent();
    //destructs a controller
    ~ControllerComponent();
    
    //handles the input of the controller, returns the string of the event 
    void handleInput();

	void addInputBinding(std::string key, py::object callback, bool isPersistent);

	void addInputReleaseBinding(std::string key, py::object callback, bool isPersistent);

	std::string* getKeys();

	int getKeysNum();

	void executeCallback();

	void executeUnCallback();

	void setKeyTo(int key, bool value);

	void addPlayerObject(PlayerObject* obj);

	int getUnKeysNum();

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
