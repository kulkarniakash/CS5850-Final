#ifndef CONTROLLER_COMPONENT_HPP
#define CONTROLLER_COMPONENT_HPP
#include <pybind11/pybind11.h>
#include <SDL_Headers.hpp>
#include <string>
#include "GlobalAttributes.hpp"
#include <unordered_map>
#include <string>

namespace py = pybind11;

class ControllerComponent {
public:
    //constructrs a controller
    ControllerComponent();
    //destructs a controller
    ~ControllerComponent();
    
    //handles the input of the controller, returns the string of the event 
    void handleInput();

	void addInputBinding(std::string key, py::object callback);

	std::string* getKeys();

	int getKeysNum();

	void executeCallback(std::string key);

	// void addInputBinding(std::string, py::object)
    
private:
	std::unordered_map<std::string, py::object> keyToFuncMap;
};
#endif 
