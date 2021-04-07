#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <stdio.h>
#include <string>
#include <TransformComponent.hpp>
#include <SpriteComponent.hpp>
#include <ControllerComponent.hpp>


class GameObject {
public:
    
    //constructs a gameObject with no components
    GameObject();
    
    //constructs a GameObject with components
    GameObject(std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<ControllerComponent> controllerComponent, std::shared_ptr<SpriteComponent> spriteComponent);
    
    ~GameObject();
    
    //gets the TransformComponent
    std::shared_ptr<TransformComponent> getTransformComponent();
    
    //gets the ControllerComponent
    std::shared_ptr<ControllerComponent> getControllerComponent();
    
    //gets the SpriteComponent
    std::shared_ptr<SpriteComponent> getSpriteComponent();
    
private:
    std::shared_ptr<TransformComponent> m_transformComponent;
    std::shared_ptr<ControllerComponent> m_controllerComponent;
    std::shared_ptr<SpriteComponent> m_spriteComponent;
};
#endif 
