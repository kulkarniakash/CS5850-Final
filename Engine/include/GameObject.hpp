#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <stdio.h>
#include <string>
#include <TransformComponent.hpp>
//#include <SpriteComponent.hpp>
#include <ControllerComponent.hpp>
class SpriteComponent;

class GameObject {
public:
    
    //constructs a gameObject with no components
    GameObject(std::string gameObjectName);
    
    //constructs a GameObject with components
    //GameObject(TransformComponent transformComponent, ControllerComponent controllerComponent, SpriteComponent spriteComponent);
    
    ~GameObject();

    void addTransformComponent(TransformComponent* transformComponent);

    void addControllerComponent(ControllerComponent* controllerComponent);

    void addSpriteComponent(SpriteComponent* spriteComponent);
    
    //gets the TransformComponent
    TransformComponent* getTransformComponent();
    
    //gets the ControllerComponent
    ControllerComponent* getControllerComponent();
    
    //gets the SpriteComponent
    SpriteComponent* getSpriteComponent();

	void updatePosition(Vec2 pos);

	void updateVelocity(Vec2 vel);

    void render();

    void update();
    
private:
    std::string m_gameObjectName;
    TransformComponent* m_transformComponent;
    ControllerComponent* m_controllerComponent;
    SpriteComponent* m_spriteComponent;
};
#endif 
