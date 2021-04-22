#include "PlayerObject.hpp"

PlayerObject::PlayerObject(std::string name, float w, float h) : AnimateObject(name, w, h) {

}

void PlayerObject::addControllerComponent(ControllerComponent* controllerComponent) {
	m_controllerComponent = controllerComponent;
	m_controllerComponent->addPlayerObject(this);
}

ControllerComponent* PlayerObject::getControllerComponent() {
	return m_controllerComponent;
}