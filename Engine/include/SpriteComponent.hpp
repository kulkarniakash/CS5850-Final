#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP
#include <stdio.h>
#include <memory>
#include <map>
#include <SDL_Headers.hpp>
#include <Vec2.hpp>
#include <TransformComponent.hpp>
#include <GameObject.hpp>
#include "ResourceManager.hpp"



class SpriteComponent { 
public:
    //constructor for SpriteComponent
    SpriteComponent(std::string filePath, SDL_Rect dest, SDL_Rect src);
    
    //destructor fpr SpriteComponent
    ~SpriteComponent();


    void addAnimation(const std::string& animationName, const int& startFrame, const int& endFrame);
    
    //allows that sprite to perform an animation
    void performAnimation(const std::string & animationName, const bool& isFlipped);
    
    //renders our sprite
    void render();
    
    //Updates our sprite
    void updateFrame(int frame);

	void updatePosition(Vec2 pos);
    

private:
    std::map<std::string, std::pair<int, int>> m_animations;
    std::pair<int, int> m_frameRange;
    int m_frame = 0;
    int m_animationSpeed;
    std::string m_currentAction;
    bool m_flipped;

	SDL_Rect m_src;
	SDL_Rect m_dest;

    // std::string m_filePath;
    std::string m_animationName;
    
    SDL_Texture * m_texture;
    SDL_Renderer * m_renderer;
};
#endif
