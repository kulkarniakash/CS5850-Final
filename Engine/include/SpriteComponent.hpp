#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP
#include <stdio.h>
#include <memory>
#include <SDL_Headers.hpp>
#include <Vec2.hpp>
#include <TransformComponent.hpp>

class SpriteComponent { 
public:
    //constructor for SpriteComponent
    SpriteComponent(std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<SDL_Texture> texture, std::shared_ptr<SDL_Renderer> * ren, std::string filePath);
    
    //destructor fpr SpriteComponent
    ~SpriteComponent();
    
    //allows that sprite to perform an animation
    void performAnimation(const std::string & animationName, int frame);
    
    //renders our sprite
    void render();
    
    //Updates our sprite
    void update(int x, int y, int frame);
    
    //loads the image of our sprite
    void loadImage(std::string filePath, SDL_Renderer * ren);
    
    

private:
    int m_frame = 0;
    
    std::string m_filePath;
    std::string m_animationName;

    std::shared_ptr<TransformComponent> m_transformComponent;
    
    SDL_Surface * m_spriteSheet;
    SDL_Texture * m_texture;
    SDL_Rect m_src;
    SDL_Rect m_dest;
    SDL_Renderer * m_renderer;
};
#endif
