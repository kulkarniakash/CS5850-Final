
#include <TransformComponent.hpp>

TransformComponent::TransformComponent(const Vec2 & position, const Vec2 & velocity): m_position(position), m_velocity(velocity) {
    
}


TransformComponent::~TransformComponent() {
    
}

void TransformComponent::update() {
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;
}

void TransformComponent::setPosition(const Vec2 & position) {
    m_position.x = position.x;
    m_position.y = position.y;
}

void TransformComponent::setVelocity(const Vec2 & velocity) {
    m_velocity.x = velocity.x;
    m_velocity.y = velocity.y;
}

float TransformComponent::getXPosition() {
    return m_position.x;
}
float TransformComponent::getYPosition() {
    return m_position.y;
}

