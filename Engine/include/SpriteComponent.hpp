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
    SpriteComponent(std::string filePath, SDL_Rect dest, SDL_Rect src);
    
    //destructor fpr SpriteComponent
    ~SpriteComponent();

    //renders our sprite
    void render();
    
    //Updates our sprite
    void updateFrame(int frame);

	void updatePosition(Vec2 pos);

	float getWidth();

	float getHeight();
    

protected:
    bool m_flipped;
    int m_frame;
    SDL_Rect m_src;
	SDL_Rect m_dest;
    
    SDL_Texture * m_texture;
    SDL_Renderer * m_renderer;
    
};
#endif
