#include <SpriteComponent.hpp>
#include <iostream>

SpriteComponent::SpriteComponent(std::string filePath, SDL_Rect dest, SDL_Rect src) {
	m_dest = dest;
	m_src = src;
	m_renderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
	if (!m_renderer) {
		std::cout<<"Error: failed to load renderer\n";
	}

	if (ResourceManager::getInstance().hasResource(filePath, ResourceType::SDLTexture)) {
		m_texture = ResourceManager::getInstance().getResourceSDLTexture(filePath);
	}
	else {
		ResourceManager::getInstance().addJPG(filePath, "gRenderer");
		m_texture = ResourceManager::getInstance().getResourceSDLTexture(filePath);
	}
}

SpriteComponent::~SpriteComponent() {
    m_texture = nullptr;
    m_renderer = nullptr;
    // SDL_FreeSurface(m_spriteSheet);
}

<<<<<<< 7e4adf9134a517667099ccd0838ce25962b250a8
=======
void SpriteComponent::addAnimation(const std::string& animationName, const int& startFrame, const int& endFrame) {
	const auto& m_frameRange = std::make_pair(startFrame, endFrame);
    m_animations.insert(std::pair<std::string, std::pair<int, int>>(animationName, m_frameRange));
}

void SpriteComponent::performAnimation(const std::string & animationName, const bool& isFlipped) {
    auto r = m_animations.find(animationName);

	if(r != m_animations.end()){
		if(m_currentAction != animationName || m_flipped != isFlipped){
            // reset to first frame of this action
            m_frame = r->second.first * m_animationSpeed;
            // set range of frames to be played
            m_frameRange = r->second;
            // set whether horizontally flipped
            m_flipped = isFlipped;
            // set current action string
            m_currentAction = animationName;
        } else {
			std::cout << "Animation not found; could not play: " << animationName << std::endl;
		}
	}
}

>>>>>>> addAnimation and performAnimation
float SpriteComponent::getWidth() {
	return m_dest.w;
}

float SpriteComponent::getHeight() {
	return m_dest.h;
}

void SpriteComponent::render() {
	// change later!!!
	SDL_Rect* dest;
	SDL_Rect* src;

	if (m_dest.w == -1) {
		dest = NULL;
	}
	else {
		dest = &m_dest;
	}

	if (m_src.w == -1) {
		src = NULL;
	}
	else {
		src = &m_src;
	}
    SDL_RenderCopyEx(m_renderer, m_texture, src, dest, 0.0f, nullptr, (m_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
	// REMOVE AFTER TESTING CLASS
	// SDL_RenderPresent(m_renderer);
}

void SpriteComponent::updatePosition(Vec2 pos) {
	m_dest.x = pos.x;
	m_dest.y = pos.y;
}