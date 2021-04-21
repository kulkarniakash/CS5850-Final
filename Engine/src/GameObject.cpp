#include <GameObject.hpp>
#include <SpriteComponent.hpp>
#include <CharacterSpriteComponent.hpp>
#include <iostream>
GameObject::GameObject(std::string gameObjectName) {
    m_gameObjectName = gameObjectName;
}

GameObject::~GameObject() {
    
}

TransformComponent* GameObject::getTransformComponent() {
    return m_transformComponent;
}
SpriteComponent* GameObject::getSpriteComponent() {
    return m_spriteComponent;
}
ControllerComponent* GameObject::getControllerComponent() {
    return m_controllerComponent;
}

CharacterSpriteComponent* GameObject::getCharacterSpriteComponent() {
    return m_characterSpriteComponent;
}


void GameObject::addTransformComponent(TransformComponent* transformComponent) {
    m_transformComponent = transformComponent;
}

void GameObject::addControllerComponent(ControllerComponent* controllerComponent) {
    m_controllerComponent = controllerComponent;
}

void GameObject::addSpriteComponent(SpriteComponent* spriteComponent) {
    m_spriteComponent = spriteComponent;
}

void GameObject::addCharacterSpriteComponent(CharacterSpriteComponent* characterSpriteComponent) {
    m_characterSpriteComponent = characterSpriteComponent;
}

void GameObject::render() {
    // have one m_spriteComponent and just call it (since characterspritecomponent is inherited from spritecomponent)
    if (m_characterSpriteComponent != nullptr) {
        m_characterSpriteComponent->render();
    } else if (m_spriteComponent != nullptr) {
        m_spriteComponent->render();
    }
}

void GameObject::update() {
                            std::cout << "enter update " << std::endl;
    m_transformComponent->update();
    if (m_characterSpriteComponent != nullptr) {
                        std::cout << "enter update m_characterSpriteComponent " << std::endl;
        m_characterSpriteComponent->updateFrame();
        std::cout << "finish update Frame " << std::endl;
        m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());
                std::cout << "finish updatePosition " << std::endl;

    } else if (m_spriteComponent != nullptr) {
        m_spriteComponent->updatePosition(m_transformComponent->getPosition());
    }
    
}
