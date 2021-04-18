#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP
#include <stdio.h>
#include <memory>
#include <SDL_Headers.hpp>
#include <Vec2.hpp>
#include <TransformComponent.hpp>
#include <GameObject.hpp>
#include "ResourceManager.hpp"

class SpriteComponent { 
public:
    //constructor for SpriteComponent
    SpriteComponent(std::string filePath, Vec2 pos, float width, float height);
    
    //destructor fpr SpriteComponent
    ~SpriteComponent();
    
    //allows that sprite to perform an animation
    void performAnimation(const std::string & animationName, int frame);
    
    //renders our sprite
    void render();
    
    //Updates our sprite
    void update(Vec2 pos, int frame);
    

private:
    int m_frame = 0;
    float m_width;
    float m_height;

	SDL_Rect m_src;
	SDL_Rect m_dest;

    // std::string m_filePath;
    std::string m_animationName;
    
    SDL_Texture * m_texture;
    SDL_Renderer * m_renderer;
};
#endif
