#ifndef COLLISION
#define COLLISION
#include "AnimateObject.hpp"
#include "GameObject.hpp"
#include <vector>
class AnimateObject;

class CollisionComponent {
public:
	CollisionComponent(AnimateObject* obj);

	~CollisionComponent();

	void handleCollisions(std::vector<GameObject*> objs);

private:
	Vec2 getCorrection(GameObject* obj);

	AnimateObject* m_animateobject;
};

#endif
