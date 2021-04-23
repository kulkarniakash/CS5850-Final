#ifndef COLLISION
#define COLLISION
#include "AnimateObject.hpp"
#include "GameObject.hpp"
#include <vector>
#include <queue>
#include <pybind11/pybind11.h>

class AnimateObject;

class CollisionComponent {
public:
	CollisionComponent(AnimateObject* obj);

	~CollisionComponent();

	void handleCollisions(std::vector<GameObject*> objs);
	
	void add_collision_callback(py::object func);

private:
	Vec2 getCorrection(GameObject* obj);

	AnimateObject* m_animateobject;

	std::queue<GameObject*> m_collided_objs;
};

#endif
