#ifndef INANOBJ
#define INANOBJ
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "CollisionComponent.hpp"
#include <string>
class CollisionComponent;

class AnimateObject : public GameObject {
public:
	AnimateObject(std::string name);

	void updatePosition(Vec2 pos);

	void updateVelocity(Vec2 vel);

	void handleCollision(std::vector<GameObject*> objs);

	void updateSprite();

	void updateTransform();

private:
	CollisionComponent* m_collisioncomp;
};
#endif
