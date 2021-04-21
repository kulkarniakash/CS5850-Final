#include <GameObject.hpp>
#include <SpriteComponent.hpp>

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

void GameObject::addTransformComponent(TransformComponent* transformComponent) {
    m_transformComponent = transformComponent;
}

void GameObject::addSpriteComponent(SpriteComponent* spriteComponent) {
    m_spriteComponent = spriteComponent;
}

void GameObject::render() {
   m_spriteComponent->updatePosition(m_transformComponent->getPosition());
   m_spriteComponent->render();
}

