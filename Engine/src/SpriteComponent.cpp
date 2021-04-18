#include <SpriteComponent.hpp>
#include <iostream>

SpriteComponent::SpriteComponent(std::string filePath, Vec2 pos, float width, float height) {
    m_width = width;
    m_height = height;
	m_renderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
	if (!m_renderer) {
		printf("Error: failed to load renderer\n");
	}
	printf("entered\n");

	m_dest = SDL_Rect();

	m_dest.x = pos.x;
	m_dest.y = pos.y;
	m_dest.w = width;
	m_dest.h = height;

	if (ResourceManager::getInstance().hasResource(filePath, ResourceType::SDLTexture)) {
		m_texture = ResourceManager::getInstance().getResourceSDLTexture(filePath);
	}
	else {
		ResourceManager::getInstance().addJPG(filePath, "gRenderer");
	}



    /*m_spriteSheet = IMG_Load(filePath.c_str());
    if(NULL == m_spriteSheet) {
        SDL_Log("Failed to allocate surface. m_spritesheet is null.");
    } 
    else {
        // Create a texture from our surface
        // Textures run faster and take advantage 
        // of hardware acceleration
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_spriteSheet);
    }*/
}

SpriteComponent::~SpriteComponent() {
    m_texture = nullptr;
    m_renderer = nullptr;
    // SDL_FreeSurface(m_spriteSheet);
}

void SpriteComponent::performAnimation(const std::string & animationName, int frame) {

}

void SpriteComponent::render() {
	// change later!!!
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	// REMOVE AFTER TESTING CLASS
	SDL_RenderPresent(m_renderer);
}

void SpriteComponent::update(Vec2 pos, int frame) {

    // change later!!!
    /*m_src.x = pos.x;
    m_src.y = pos.y;
    m_src.w = m_width;
    m_src.h = m_height;*/

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.	
    m_dest.x = pos.x;
    m_dest.y = pos.y;
    m_dest.w = m_width;
    m_dest.h = m_height;

}