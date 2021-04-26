#include <UIComponent.hpp>
#include "ResourceManager.hpp"
#include <iostream>

UIComponent::UIComponent(std::string fontPath, SDL_Rect src, std::string displayText, int fontSize) {
    std::cout << fontPath << std::endl;
    if (ResourceManager::getInstance().addResource(fontPath, ResourceType::Font, fontSize) != 0) {
		printf("Error: Could not load font\n");
    }

    m_displayFont = ResourceManager::getInstance().getResourceFont(fontPath);
    White = {255, 255, 255};
    
    m_surface = TTF_RenderText_Solid(m_displayFont, displayText.c_str(), White);
    if (ResourceManager::getInstance().addTexture("displayTexture", "gRenderer", m_surface) != 0) {
        printf("Error: Could not add texture\n");
    }

    m_texture = ResourceManager::getInstance().getResourceSDLTexture("displayTexture");
    if (m_texture == nullptr) {
        printf("texture is null");
    }
    m_renderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
    if (m_renderer == nullptr) {
        printf("Renderer is null");
    }
    m_textRect = &src;
}

void UIComponent::render() {
    printf("render ui");
    SDL_RenderCopy(m_renderer, m_texture, NULL, m_textRect);
}

void UIComponent::update(std::string text) {
    m_surface = TTF_RenderText_Solid(m_displayFont, text.c_str(), White);
    if (ResourceManager::getInstance().addTexture("displayTexture", "gRenderer", m_surface) != 0) {
        printf("Error: Could not add texture\n");
    }

    m_texture = ResourceManager::getInstance().getResourceSDLTexture("displayTexture");
    SDL_RenderCopy(m_renderer, m_texture, NULL, m_textRect);
}