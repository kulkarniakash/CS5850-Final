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

CharacterSpriteComponent* GameObject::getCharacterSpriteComponent() {
    return m_characterSpriteComponent;
}


void GameObject::addTransformComponent(TransformComponent* transformComponent) {
    m_transformComponent = transformComponent;
}

void GameObject::addSpriteComponent(SpriteComponent* spriteComponent) {
    m_spriteComponent = spriteComponent;
	m_spriteComponent->updatePosition(m_transformComponent->getPosition());
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

