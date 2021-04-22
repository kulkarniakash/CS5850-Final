#ifndef GAME_OBJ
#define GAME_OBJ
#include <stdio.h>
#include <string>
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "CharacterSpriteComponent.hpp"

class SpriteComponent;
class CharacterSpriteComponent;

class GameObject {
public:
    
    //constructs a gameObject with no components
    GameObject(std::string gameObjectName, float width, float height);

    //constructs a GameObject with components
    //GameObject(TransformComponent transformComponent, ControllerComponent controllerComponent, SpriteComponent spriteComponent);
    
    ~GameObject();

    void addTransformComponent(TransformComponent* transformComponent);

    // void addControllerComponent(ControllerComponent* controllerComponent);

    void addSpriteComponent(SpriteComponent* spriteComponent);

    void addCharacterSpriteComponent(CharacterSpriteComponent* characterSpriteComponent);
    
    //gets the TransformComponent
    TransformComponent* getTransformComponent();
    
    //gets the ControllerComponent
    // ControllerComponent* getControllerComponent();

    CharacterSpriteComponent* getCharacterSpriteComponent();
    
    //gets the SpriteComponent
    SpriteComponent* getSpriteComponent();

    void render();

	float getWidth();

	float getHeight();

    // void update();
    
protected:
	float width, height;
    std::string m_gameObjectName;
    TransformComponent* m_transformComponent;
    // ControllerComponent* m_controllerComponent;
    SpriteComponent* m_spriteComponent;
    CharacterSpriteComponent* m_characterSpriteComponent;
};
#endif 
