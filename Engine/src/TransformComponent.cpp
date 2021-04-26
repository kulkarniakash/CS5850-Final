#include <iostream>
#include <TransformComponent.hpp>

TransformComponent::TransformComponent(const Vec2 & position, const Vec2 & velocity): m_position(position), m_velocity(velocity) {
    
}


TransformComponent::~TransformComponent() {
    std::cout << "TransformComponent destructor called" << std::endl;
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
	//std::cout << m_velocity.x << std::endl;
	//std::cout << m_velocity.y << std::endl;
	return m_velocity;
}

void TransformComponent::updatePosition(const Vec2& position) {
	m_position += position;
}

void TransformComponent::updateVelocity(const Vec2& velocity) {
	m_velocity += velocity;
}