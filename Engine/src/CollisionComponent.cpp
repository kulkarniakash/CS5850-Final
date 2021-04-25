#include "CollisionComponent.hpp"
#include <algorithm>

CollisionComponent::CollisionComponent(AnimateObject* obj) {
	m_animateobject = obj;
}

void CollisionComponent::handleCollisions(std::vector<GameObject*> objs) {
	bool collided = false;
	for (auto obj : objs) {
		Vec2 corr = getCorrection(obj);
		if (corr != Vec2(0, 0)) {
			collided = true;
			//TODO: call callback functions
			for (auto callback: callbacks) {
				callback(obj);
			}
		}
		m_animateobject->updatePosition(corr);
	}

	if (collided) {
		m_animateobject->setVelocity(Vec2(0, 0));
	}
}

Vec2 CollisionComponent::getCorrection(GameObject* obj) {
	TransformComponent* trans = m_animateobject->getTransformComponent();
	TransformComponent* transOther = obj->getTransformComponent();

	float left = trans->getPosition().x;
	float right = trans->getPosition().x + m_animateobject->getWidth();
	float top = trans->getPosition().y;
	float bottom = trans->getPosition().y + m_animateobject->getHeight();

	float leftOther = transOther->getPosition().x;
	float rightOther = transOther->getPosition().x + obj->getWidth();
	float topOther = transOther->getPosition().y;
	float bottomOther = transOther->getPosition().y + obj->getHeight();

	if (right <= leftOther) {
		return Vec2(0, 0);
	}

	if (left >= rightOther) {
		return Vec2(0, 0);
	}

	if (top >= bottomOther) {
		return Vec2(0, 0);
	}

	if (bottom <= topOther) {
		return Vec2(0, 0);
	}

	Vec2 prevPos = trans->getPosition() - trans->getVelocity();

	float prevLeft = prevPos.x;
	float prevRight = prevPos.x + m_animateobject->getWidth();
	float prevTop = prevPos.y;
	float prevBottom = prevPos.y + m_animateobject->getHeight();

	if (prevRight <= leftOther) {
		return Vec2(-(right - leftOther), 0);
	}

	if (prevLeft >= rightOther) {
		return Vec2(rightOther - left, 0);
	}

	if (prevTop >= bottomOther) {
		return Vec2(0, bottomOther - top);
	}

	if (prevBottom <= topOther) {
		return Vec2(0, -(bottom - topOther));
	}

	float leftCorr = right - leftOther;
	float rightCorr = rightOther - left;
	float upCorr = bottom - topOther;
	float downCorr = bottomOther - top;

	float minDist = std::min(leftCorr, std::min(rightCorr, std::min(upCorr, downCorr)));

	if (leftCorr == minDist) {
		return Vec2(-leftCorr, 0);
	}
	else if (rightCorr == minDist) {
		return Vec2(rightCorr, 0);
	}
	else if (upCorr == minDist) {
		return Vec2(0, -upCorr);
	}
	else {
		return Vec2(0, downCorr);
	}

	return Vec2(-(right - leftOther), 0);
}

//TODO: store callbacks in a vector
void CollisionComponent::add_collision_callback(py::object func) {
	callbacks.push_back(func);
}