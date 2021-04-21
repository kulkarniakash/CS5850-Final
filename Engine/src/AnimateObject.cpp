#include "AnimateObject.hpp"
#include <iostream>

AnimateObject::AnimateObject(std::string name) : GameObject(name) {

}

void AnimateObject::update() {
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
	m_transformComponent->setPosition(pos);
}

void AnimateObject::updateVelocity(Vec2 vel) {
	m_transformComponent->setVelocity(vel);
}
