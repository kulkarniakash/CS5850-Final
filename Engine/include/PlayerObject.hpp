#ifndef PLAYOBJ
#define PLAYOBJ
#include "AnimateObject.hpp"
#include "ControllerComponent.hpp"

class ControllerComponent;
class AnimateObject;

class PlayerObject : public AnimateObject {
public:
	PlayerObject(std::string name, float w, float h);

	void addControllerComponent(ControllerComponent* controllerComponent);

	ControllerComponent* getControllerComponent();

	void updateControllerVelocity(Vec2 vel);

	void setControllerVelocity(Vec2 vel);

	Vec2 getControllerVelocity();

	void updateTransform();

private:
	ControllerComponent* m_controllerComponent;
	Vec2 controlVelocity;
};
#endif
