#include "PlayerObject.hpp"

PlayerObject::PlayerObject(std::string name) : AnimateObject(name) {

}

void PlayerObject::addControllerComponent(ControllerComponent* controllerComponent) {
	m_controllerComponent = controllerComponent;
	m_controllerComponent->addPlayerObject(this);
}

ControllerComponent* PlayerObject::getControllerComponent() {
	return m_controllerComponent;
}