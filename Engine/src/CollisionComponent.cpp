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
		}
		m_animateobject->getTransformComponent()->updatePosition(corr);
	}

	if (collided) {
		m_animateobject->getTransformComponent()->setVelocity(Vec2(0, 0));
	}
}

Vec2 CollisionComponent::getCorrection(GameObject* obj) {
	TransformComponent* trans = m_animateobject->getTransformComponent();
	TransformComponent* transOther = obj->getTransformComponent();
	SpriteComponent* sprite = m_animateobject->getSpriteComponent();
	SpriteComponent* spriteOther = obj->getSpriteComponent();

	float left = trans->getPosition().x;
	float right = trans->getPosition().x + sprite->getWidth();
	float top = trans->getPosition().y;
	float bottom = trans->getPosition().y + sprite->getHeight();

	float leftOther = transOther->getPosition().x;
	float rightOther = transOther->getPosition().x + spriteOther->getWidth();
	float topOther = transOther->getPosition().y;
	float bottomOther = transOther->getPosition().y + spriteOther->getHeight();

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
	float prevRight = prevPos.x + sprite->getWidth();
	float prevTop = prevPos.y;
	float prevBottom = prevPos.y + sprite->getHeight();

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