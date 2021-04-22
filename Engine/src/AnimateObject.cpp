#include "AnimateObject.hpp"
#include <iostream>

AnimateObject::AnimateObject(std::string name, float w, float h) : GameObject(name, w, h) {
	m_collisioncomp = new CollisionComponent(this);
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

void AnimateObject::handleCollision(std::vector<GameObject*> objs) {
	m_collisioncomp->handleCollisions(objs);
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




