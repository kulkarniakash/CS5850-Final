#include <SpriteComponent.hpp>
#include <iostream>

SpriteComponent::SpriteComponent(GameObject* gameObject, SDL_Renderer * ren, std::string filePath, int width, int height) {
    m_gameObject = gameObject;
    m_renderer = ren;
    m_width = width;
    m_height = height;

    m_spriteSheet = IMG_Load(filePath.c_str());
    if(NULL == m_spriteSheet) {
        SDL_Log("Failed to allocate surface. m_spritesheet is null.");
    } 
    else {
        // Create a texture from our surface
        // Textures run faster and take advantage 
        // of hardware acceleration
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_spriteSheet);
    }
}

SpriteComponent::~SpriteComponent() {
    m_texture = nullptr;
    m_renderer = nullptr;
    SDL_FreeSurface(m_spriteSheet);
    m_spriteSheet = nullptr;
}

void SpriteComponent::performAnimation(const std::string & animationName, int frame) {

}

void SpriteComponent::render() {
    SDL_RenderCopy(m_renderer, m_texture, &m_src, &m_dest);
}

void SpriteComponent::update(int x, int y, int frame) {

    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    m_src.x = x;
    m_src.y = y;
    m_src.w = m_width;
    m_src.h = m_height;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.	
    m_dest.x = m_gameObject->getTransformComponent()->getXPosition();
    m_dest.y = m_gameObject->getTransformComponent()->getYPosition();
    m_dest.w = m_width;
    m_dest.h = m_height;

}