#include "AnimateObject.hpp"
#include <iostream>

AnimateObject::AnimateObject(std::string name, float w, float h) : GameObject(name, w, h) {
	m_collisioncomp = new CollisionComponent(this);
}

AnimateObject::~AnimateObject() {
    std::cout << "AnimateObject destructor called for " << m_gameObjectName << std::endl;
	delete m_collisioncomp;
	m_collisioncomp = nullptr;
}

void AnimateObject::updateSprite() {
    if (m_characterSpriteComponent != nullptr) {
        m_characterSpriteComponent->updateFrame();
        // m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

    } else if (m_spriteComponent != nullptr) {
        // m_spriteComponent->updatePosition(m_transformComponent->getPosition());
    }
}

void AnimateObject::updateTransform() {
	m_transformComponent->update();
	if (m_characterSpriteComponent != nullptr) {
		m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

	}
	else if (m_spriteComponent != nullptr) {
		m_spriteComponent->updatePosition(m_transformComponent->getPosition());
	}
}

void AnimateObject::updatePosition(Vec2 pos) {
	m_transformComponent->updatePosition(pos);
	if (m_characterSpriteComponent != nullptr) {
		m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

	}
	else if (m_spriteComponent != nullptr) {
		m_spriteComponent->updatePosition(m_transformComponent->getPosition());
	}
}

void AnimateObject::updateVelocity(Vec2 vel) {
	m_transformComponent->updateVelocity(vel);
}

void AnimateObject::handleCollision(std::vector<GameObject*> objs, std::vector<AnimateObject*> animObjs) {
	//std::cout <<"enter handleCollision" << std::endl;
	std::cout <<"animateObject handleCollision -1" << std::endl;
	bool returned = m_collisioncomp->handleCollisions(objs);
	if (returned) {
		return;
	}
	std::cout <<"animateObject handleCollision 0" << std::endl;
	//std::cout <<"handleCollision for: " << this->getGameObjectName() << std::endl;
	std::vector<GameObject*> gObjs;
	for (auto aObj: animObjs) {
		//std::cout <<"aObj " << aObj->getGameObjectName() << std::endl;
		if (this == aObj) {
			continue;
		} else {
			//Changing animate objects to game objects 
			GameObject* gObj = static_cast<GameObject*>(aObj);
		//	std::cout <<"about to push_back" << std::endl;
		//	std::cout <<"gObj " << gObj->getGameObjectName() << std::endl;
			gObjs.push_back(gObj);
		}
	}
	std::cout <<"animateObject handleCollision 1" << std::endl;
	m_collisioncomp->handleCollisions(gObjs);
	std::cout <<"animateObject handleCollision 2" << std::endl;
}

void AnimateObject::setPosition(Vec2 pos) {
	m_transformComponent->setPosition(pos);
	if (m_characterSpriteComponent != nullptr) {
		m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

	}
	else if (m_spriteComponent != nullptr) {
		m_spriteComponent->updatePosition(m_transformComponent->getPosition());
	}
}

void AnimateObject::setVelocity(Vec2 vel) {
	m_transformComponent->setVelocity(vel);
}

void AnimateObject::Destroy() {
    delete this;
}
void AnimateObject::addCollisionCallback(py::object func) {
	m_collisioncomp->addCollisionCallback(func);
}




