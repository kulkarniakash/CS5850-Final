#include <GameObject.hpp>
#include <SpriteComponent.hpp>
#include <CharacterSpriteComponent.hpp>
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
   m_spriteComponent->updatePosition(m_transformComponent->getPosition());
   m_spriteComponent->render();
}

void GameObject::update() {
    m_transformComponent->update();
    
}
