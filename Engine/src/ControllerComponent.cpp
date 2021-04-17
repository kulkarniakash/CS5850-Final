#include <ControllerComponent.hpp>

ControllerComponent::ControllerComponent() {
    
}

ControllerComponent::~ControllerComponent() {
    
}

std::string ControllerComponent::handleInput(SDL_Event event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        // perform appropriate action
        switch(event.key.keysym.sym) {
            case SDLK_w:
                return "up";
            case SDLK_s:
                return "down";
            case SDLK_d:
                return "left";
            case SDLK_a:
                return "right";
            case SDLK_SPACE:
                return "jump";
            default:
                return "";
            }
        }
    return "";
}
