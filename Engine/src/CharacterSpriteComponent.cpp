#include <CharacterSpriteComponent.hpp>
#include <iostream>
// Sprite Animation inspired by Kimin and Danny's assignment 2.
CharacterSpriteComponent::CharacterSpriteComponent(std::string filePath, SDL_Rect src, SDL_Rect dest, int rows, int cols) : SpriteComponent(filePath, src) {
	m_rows = rows;
	m_cols = cols;
	m_dest.w = dest.w;
	m_dest.h = dest.h;
}

CharacterSpriteComponent::~CharacterSpriteComponent() {
	std::cout << "CharacterSpriteComponent destructor called" << std::endl;
	m_texture = nullptr;
	m_renderer = nullptr;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
}


void CharacterSpriteComponent::addAnimation(const std::string& animationName, const int& startFrame, const int& endFrame) {
	const auto& m_frameRange = std::make_pair(startFrame, endFrame);
    m_animations.insert(std::pair<std::string, std::pair<int, int>>(animationName, m_frameRange));
}

void CharacterSpriteComponent::performAnimation(const std::string& animationName, const bool& isFlipped, float animSpeed) {
	m_animationSpeed = animSpeed;
	auto it = m_animations.find(animationName);

	if (it != m_animations.end()) {
		if (m_currentAction != animationName || m_flipped != isFlipped) {
			// reset to first frame of this action
			m_frame = it->second.first * m_animationSpeed;
			// set range of frames to be played
			m_frameRange = it->second;
			// set whether horizontally flipped
			m_flipped = isFlipped;
			// set current action string
			m_currentAction = animationName;
		}
	}
	else {
		std::cout << "Animation not found; could not play: " << animationName << std::endl;
	}
}

void CharacterSpriteComponent::updateFrame() {
    // set frame
    m_frame++;

    // calculate actual frame
    m_actualFrame = m_frame / m_animationSpeed;

    // reset to first frame of our current animation
	if((m_actualFrame > m_frameRange.second || m_actualFrame < m_frameRange.first)){

        if(m_loopAction){
            // reset to first frame of current action
            m_frame = m_frameRange.first * m_animationSpeed;
        }else{
            // stay on last frame of current action
            m_frame -= 1;
        }

        m_actualFrame = m_frame / m_animationSpeed;
    }

}

void CharacterSpriteComponent::updatePosition(Vec2 pos) {
	m_src.x = (m_actualFrame % m_cols) * m_src.w;
    m_src.y = (m_actualFrame / m_cols) * m_src.h;
	m_dest.x = pos.x;
	m_dest.y = pos.y;
}

bool& CharacterSpriteComponent::loopAction(){
    return m_loopAction;
}

void CharacterSpriteComponent::setLoop(bool loop) {
	m_loopAction = loop;
}