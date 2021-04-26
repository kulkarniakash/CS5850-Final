#include "CollisionComponent.hpp"
#include <algorithm>
#include <iostream>

CollisionComponent::CollisionComponent(AnimateObject* obj) {
	m_animateobject = obj;
}

CollisionComponent::~CollisionComponent() {
	std::cout << "CollisionComponent destructor called" << std::endl;
	m_animateobject = nullptr;
}

bool CollisionComponent::handleCollisions(std::vector<GameObject*> objs) {
	std::cout <<"enter handleCollision in CollisionComponent" << std::endl;
	bool collided = false;
	Vec2 corr;
	for (auto obj : objs) {
		std::cout <<"current m_animateobject: " << m_animateobject->getGameObjectName() << std::endl;
		 std::cout <<"current obj: " << obj->getGameObjectName() << std::endl;
		corr = getCorrection(obj);
	//	std::cout <<"getCorrection passed" << std::endl;
		if (corr != Vec2(0, 0)) {
			//std::cout <<"m_callbacks passed" << std::endl;
			//std::cout <<"current m_animateobject: " << m_animateobject->getGameObjectName() << std::endl;
			TransformComponent* trans = m_animateobject->getTransformComponent();
		//	std::cout <<"trans passed" << std::endl;
			Vec2 curr_vel = trans->getVelocity();
			//std::cout <<"getVelocity passed" << std::endl;
			if (corr.x == 0) {
				m_animateobject->setVelocity(Vec2(curr_vel.x, 0));
			}
			else if (corr.y == 0) {
				m_animateobject->setVelocity(Vec2(0, curr_vel.y));
			}
			else {
				m_animateobject->setVelocity(Vec2(0, 0));
			}
		}
	//	std::cout <<"about to call updatePosition" << std::endl;
		m_animateobject->updatePosition(corr);
		//std::cout <<"updatePosition passed" << std::endl;
		 
		if (corr != Vec2(0, 0)) {
			if (m_callbacks.size() > 0) {
				std::cout <<"about to do m_callbacks " << std::endl;
				m_callbacks[0](obj);
				std::cout <<"m_callbacks returned " << std::endl;
				return true;
			}
		}
	}
	return false;
	// for (auto obj:objs) {
	// 	corr = getCorrection(obj);
	// 	if (corr != Vec2(0, 0)) {
	// 		if (m_callbacks.size() > 0 && doCallback) {
	// 			m_callbacks[0](obj);
	// 		}
	// 	}
	// }
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

	/*if (prevRight <= leftOther) {
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
	}*/

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

void CollisionComponent::addCollisionCallback(py::object func) {
	m_callbacks.push_back(func);
}