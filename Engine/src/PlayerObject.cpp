#include "PlayerObject.hpp"

PlayerObject::PlayerObject(std::string name, float w, float h) : AnimateObject(name, w, h) {
	controlVelocity = Vec2(0, 0);
}

void PlayerObject::addControllerComponent(ControllerComponent* controllerComponent) {
	m_controllerComponent = controllerComponent;
	m_controllerComponent->addPlayerObject(this);
}

ControllerComponent* PlayerObject::getControllerComponent() {
	return m_controllerComponent;
}

void PlayerObject::updateControllerVelocity(Vec2 vel) {
	controlVelocity += vel;
}

void PlayerObject::setControllerVelocity(Vec2 vel) {
	controlVelocity = vel;
}

Vec2 PlayerObject::getControllerVelocity() {
	return controlVelocity;
}

void PlayerObject::updateTransform() {
	m_transformComponent->updateVelocity(controlVelocity);
	m_transformComponent->update();
	m_transformComponent->updateVelocity(Vec2(0,0) - controlVelocity);

	if (m_characterSpriteComponent != nullptr) {
		m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

	}
	else if (m_spriteComponent != nullptr) {
		m_spriteComponent->updatePosition(m_transformComponent->getPosition());
	}
}