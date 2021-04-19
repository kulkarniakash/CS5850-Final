#ifndef CONTROLLER_COMPONENT_HPP
#define CONTROLLER_COMPONENT_HPP
#include <SDL_Headers.hpp>
#include <string>

class ControllerComponent {
public:
    //constructrs a controller
    ControllerComponent();
    //destructs a controller
    ~ControllerComponent();
    
    //handles the input of the controller, returns the string of the event 
    std::string handleInput(SDL_Event event);

	// void addInputBinding(std::string, py::object)
    
private:
};
#endif 
