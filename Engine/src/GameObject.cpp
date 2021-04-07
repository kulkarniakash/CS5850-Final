#include <GameObject.hpp>

GameObject::GameObject() {
    
}

GameObject::GameObject(std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<ControllerComponent> controllerComponent, std::shared_ptr<SpriteComponent> spriteComponent): m_transformComponent(transformComponent), m_spriteComponent(spriteComponent), m_controllerComponent(controllerComponent) {
    
}

GameObject::~GameObject() {
    
}

std::shared_ptr<TransformComponent> GameObject::getTransformComponent() {
    return m_transformComponent;
}
std::shared_ptr<SpriteComponent> GameObject::getSpriteComponent() {
    return m_spriteComponent;
}
std::shared_ptr<ControllerComponent> GameObject::getControllerComponent() {
    return m_controllerComponent;
}
