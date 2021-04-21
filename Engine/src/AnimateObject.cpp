#include "AnimateObject.hpp"

AnimateObject::AnimateObject(std::string name) : GameObject(name) {

}

void AnimateObject::update() {
	m_transformComponent->update();
}

void AnimateObject::updatePosition(Vec2 pos) {
	m_transformComponent->setPosition(pos);
}

void AnimateObject::updateVelocity(Vec2 vel) {
	m_transformComponent->setVelocity(vel);
}
