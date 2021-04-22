#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP
#include <stdio.h>
#include <memory>
#include <map>
#include <SDL_Headers.hpp>
#include <Vec2.hpp>
#include "ResourceManager.hpp"



class SpriteComponent { 
public:
    //constructor for SpriteComponent
    SpriteComponent(std::string filePath, SDL_Rect src);
    
    //destructor fpr SpriteComponent
    ~SpriteComponent();

    //renders our sprite
    void render();

	void updatePosition(Vec2 pos);

	float getWidth();

	float getHeight();

	void setDim(float width, float height);

protected:
    bool m_flipped;
    int m_frame=0;
    SDL_Rect m_src;
    std::map<std::string, std::pair<int, int>> m_animations;
    std::pair<int, int> m_frameRange;
    int m_animationSpeed;
    std::string m_currentAction;
	SDL_Rect m_dest;
    
    SDL_Texture * m_texture;
    SDL_Renderer * m_renderer;
    
};
#endif
