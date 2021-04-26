#ifndef INANOBJ
#define INANOBJ
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "CollisionComponent.hpp"
#include <string>
#include <pybind11/pybind11.h>
class CollisionComponent;
class GameObject;
namespace py = pybind11;

class AnimateObject : public GameObject {
public:
	AnimateObject(std::string name, float w, float h);

	void updatePosition(Vec2 pos);

	void updateVelocity(Vec2 vel);

	void setPosition(Vec2 pos);

	void setVelocity(Vec2 vel);

	void handleCollision(std::vector<GameObject*> objs, std::vector<AnimateObject*> animObjs);

	void updateSprite();

	void updateTransform();

	void addCollisionCallback(py::object func);

private:
	CollisionComponent* m_collisioncomp;
};
#endif
