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
	bool returned = m_collisioncomp->handleCollisions(objs);
	if (returned) {
		return;
	}
	std::vector<GameObject*> gObjs;
	for (auto aObj: animObjs) {
		if (this == aObj) {
			continue;
		} else {
			//Changing animate objects to game objects 
			GameObject* gObj = static_cast<GameObject*>(aObj);
			gObjs.push_back(gObj);
		}
	}
	m_collisioncomp->handleCollisions(gObjs);
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




