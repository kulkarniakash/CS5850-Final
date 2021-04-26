#include <UIComponent.hpp>
#include "ResourceManager.hpp"
#include <iostream>

UIComponent::UIComponent(std::string fontPath, SDL_Rect dest, std::string displayText, int fontSize) {
    std::cout << fontPath << std::endl;
    if (ResourceManager::getInstance().addResource(fontPath, ResourceType::Font, fontSize) != 0) {
        std::cout << "Error: Could not load font" << std::endl;
    }
    std::cout << SDL_GetError() << std::endl;

    m_displayFont = ResourceManager::getInstance().getResourceFont(fontPath);
    if (m_displayFont == NULL || m_displayFont == nullptr) {
        std::cout << "Font is null" << std::endl;
    }
    White = {255, 255, 255};
    
    m_surface = TTF_RenderText_Solid(m_displayFont, displayText.c_str(), White);
    if (ResourceManager::getInstance().addTexture("displayTexture", "gRenderer", m_surface) != 0) {
        std::cout << "Error: Could not add texture" << std::endl;
    }
    std::cout << SDL_GetError() << std::endl;

    m_texture = ResourceManager::getInstance().getResourceSDLTexture("displayTexture");
    if (m_texture == NULL || m_texture == nullptr) {
        std::cout << "Texture is null" << std::endl;
    }
    m_renderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
    if (m_renderer == NULL || m_renderer == nullptr) {
        std::cout << "Renderer is null" << std::endl;
    }
    m_textRect = dest;
    // if (m_textRect == NULL || m_textRect == nullptr) {
    //    std::cout << "m_textRect is null" << std::endl;
    // }
}

void UIComponent::render() {
    // std::cout << "in render" << std::endl;
    if (m_texture == NULL || m_texture == nullptr) {
        std::cout << "Texture is null" << std::endl;
    }
    if (m_renderer == NULL || m_renderer == nullptr) {
        std::cout << "Renderer is null" << std::endl;
    }
    // if (m_textRect == NULL  || m_textRect == nullptr) {
    //    std::cout << "m_textRect is null" << std::endl;
    // }
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textRect);
     std::cout << SDL_GetError() << std::endl;
}

void UIComponent::update(std::string text) {
    m_surface = TTF_RenderText_Solid(m_displayFont, text.c_str(), White);
    if (ResourceManager::getInstance().addTexture("displayTexture", "gRenderer", m_surface) != 0) {
        printf("Error: Could not add texture\n");
    }

    m_texture = ResourceManager::getInstance().getResourceSDLTexture("displayTexture");
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_textRect);
}