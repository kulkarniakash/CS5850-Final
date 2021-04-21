#ifndef PLAYOBJ
#define PLAYOBJ
#include "AnimateObject.hpp"
#include "ControllerComponent.hpp"

class PlayerObject : public AnimateObject {
public:
	PlayerObject(std::string name);

	void addControllerComponent(ControllerComponent* controllerComponent);

	ControllerComponent* getControllerComponent();

private:
	ControllerComponent* m_controllerComponent;
};
#endif
