#include "AnimateObject.hpp"
#include <iostream>

AnimateObject::AnimateObject(std::string name) : GameObject(name) {
	m_collisioncomp = new CollisionComponent(this);
}

void AnimateObject::updateSprite() {
    if (m_characterSpriteComponent != nullptr) {
        m_characterSpriteComponent->updateFrame();
        m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());

    } else if (m_spriteComponent != nullptr) {
        m_spriteComponent->updatePosition(m_transformComponent->getPosition());
    }
}

void AnimateObject::updateTransform() {
	m_transformComponent->update();
	std::cout << "enter update " << std::endl;
    if (m_characterSpriteComponent != nullptr) {
       std::cout << "enter update m_characterSpriteComponent " << std::endl;
        m_characterSpriteComponent->updateFrame();
        std::cout << "finish update Frame " << std::endl;
        m_characterSpriteComponent->updatePosition(m_transformComponent->getPosition());
        std::cout << "finish updatePosition " << std::endl;

    } else if (m_spriteComponent != nullptr) {
        m_spriteComponent->updatePosition(m_transformComponent->getPosition());
    }
}

void AnimateObject::updatePosition(Vec2 pos) {
	m_transformComponent->updatePosition(pos);
}

void AnimateObject::updateVelocity(Vec2 vel) {
	m_transformComponent->updateVelocity(vel);
}

void AnimateObject::handleCollision(std::vector<GameObject*> objs) {
	m_collisioncomp->handleCollisions(objs);
}

void AnimateObject::setPosition(Vec2 pos) {
	m_transformComponent->setPosition(pos);
}

void AnimateObject::setVelocity(Vec2 vel) {
	m_transformComponent->setVelocity(vel);
}




