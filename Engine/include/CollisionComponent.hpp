#ifndef COLLISION
#define COLLISION
#include "AnimateObject.hpp"
#include "GameObject.hpp"
#include <vector>
#include <queue>
#include <pybind11/pybind11.h>
#include <stdlib.h>
#include <iostream>

class AnimateObject;

namespace py = pybind11;

class CollisionComponent {
public:
	CollisionComponent(AnimateObject* obj);

	~CollisionComponent();

	void handleCollisions(std::vector<GameObject*> objs);
	
	void add_collision_callback(py::object func);

private:
	Vec2 getCorrection(GameObject* obj);

	AnimateObject* m_animateobject;

	std::vector<py::object> callbacks;
};

#endif
