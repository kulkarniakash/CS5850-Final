#ifndef INANOBJ
#define INANOBJ
#include "GameObject.hpp"
#include "Vec2.hpp"
#include <string>

class GameObject;

class AnimateObject : public GameObject {
public:
	AnimateObject(std::string name);

	void updatePosition(Vec2 pos);

	void updateVelocity(Vec2 vel);

	void update();
};
#endif
