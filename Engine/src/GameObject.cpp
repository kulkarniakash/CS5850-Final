#include "SpriteComponent.hpp"
#include "CharacterSpriteComponent.hpp"
#include <iostream>
#include "GameObject.hpp"

GameObject::GameObject(std::string gameObjectName, float w, float h) {
    m_gameObjectName = gameObjectName;
	width = w;
	height = h;
	m_characterSpriteComponent = nullptr;
	m_spriteComponent = nullptr;
}

GameObject::~GameObject() {
    std::cout << "GameObject destructor called for " << m_gameObjectName << std::endl;
    if (m_spriteComponent != nullptr) {
        delete m_spriteComponent;
        m_spriteComponent = nullptr;
    } else {
        delete m_characterSpriteComponent;
        m_characterSpriteComponent = nullptr;
    }
    delete m_transformComponent;
    m_transformComponent = nullptr;
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
	m_spriteComponent->setDim(width, height);
}

void GameObject::addCharacterSpriteComponent(CharacterSpriteComponent* characterSpriteComponent) {
    m_characterSpriteComponent = characterSpriteComponent;
	m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());
	m_characterSpriteComponent->setDim(width, height);
}

void GameObject::render() {
    // m_spriteComponent->updatePosition(m_transformComponent->getPosition());
    // m_spriteComponent->render();
    // have one m_spriteComponent and just call it (since characterspritecomponent is inherited from spritecomponent)
    if (m_characterSpriteComponent != nullptr) {
		m_characterSpriteComponent->updatePosition(Camera::getInstance().correctPosition(this));
        m_characterSpriteComponent->render();
    } else if (m_spriteComponent != nullptr) {
		m_spriteComponent->updatePosition(Camera::getInstance().correctPosition(this));
        m_spriteComponent->render();
    }
}

float GameObject::getHeight()
{
	return height;
}

float GameObject::getWidth() {
	return width;
}

void GameObject::Destroy() {
    delete this;
}

std::string GameObject::getGameObjectName() {
    return m_gameObjectName;
}