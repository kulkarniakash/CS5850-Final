#include "AnimateObject.hpp"
#include <iostream>

AnimateObject::AnimateObject(std::string name) : GameObject(name) {
	m_collisioncomp = new CollisionComponent(this);
}

void AnimateObject::update() {
	m_transformComponent->update();
    if (m_characterSpriteComponent != nullptr) {
        m_characterSpriteComponent->updateFrame();
        m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

    } else if (m_spriteComponent != nullptr) {
        m_spriteComponent->updatePosition(m_transformComponent->getPosition());
    }
}

void AnimateObject::updatePosition(Vec2 pos) {
	m_transformComponent->setPosition(pos);
}

void AnimateObject::updateVelocity(Vec2 vel) {
	m_transformComponent->setVelocity(vel);
}

void AnimateObject::handleCollision(std::vector<GameObject*> objs) {
	m_collisioncomp->handleCollisions(objs);
}


