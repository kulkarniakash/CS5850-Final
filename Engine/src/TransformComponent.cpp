
#include <TransformComponent.hpp>

TransformComponent::TransformComponent(const Vec2 & position, const Vec2 & velocity): m_position(position), m_velocity(velocity) {
    
}


TransformComponent::~TransformComponent() {
    
}

void TransformComponent::update() {
	m_position += m_velocity;
}

void TransformComponent::setPosition(const Vec2 & position) {
	m_position = position;
}

void TransformComponent::setVelocity(const Vec2 & velocity) {
	m_velocity = velocity;
}

Vec2 TransformComponent::getPosition() {
	return m_position;
}

Vec2 TransformComponent::getVelocity() {
	return m_velocity;
}
