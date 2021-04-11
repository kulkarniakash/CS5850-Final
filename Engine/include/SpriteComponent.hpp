#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP
#include <stdio.h>
#include <memory>
#include <SDL_Headers.hpp>
#include <Vec2.hpp>
#include <TransformComponent.hpp>
#include <GameObject.hpp>

class SpriteComponent { 
public:
    //constructor for SpriteComponent
    SpriteComponent(GameObject* gameObject, SDL_Renderer* ren, std::string filePath, int width, int height);
    
    //destructor fpr SpriteComponent
    ~SpriteComponent();
    
    //allows that sprite to perform an animation
    void performAnimation(const std::string & animationName, int frame);
    
    //renders our sprite
    void render();
    
    //Updates our sprite
    void update(int x, int y, int frame);
    

private:
    int m_frame = 0;
    int m_width;
    int m_height;

    GameObject* m_gameObject;
    
    // std::string m_filePath;
    std::string m_animationName;
    
    SDL_Surface * m_spriteSheet;
    SDL_Texture * m_texture;
    SDL_Rect m_src;
    SDL_Rect m_dest;
    SDL_Renderer * m_renderer;
};
#endif
