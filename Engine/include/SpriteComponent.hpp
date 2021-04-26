#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP
#include <stdio.h>
#include <memory>
#include <map>
#include <SDL_Headers.hpp>
#include <Vec2.hpp>
#include "ResourceManager.hpp"


/*!
 * @brief Class that represents our SpriteComponent
 * handles performing certain animations of this object
 */
class SpriteComponent { 
public:
    /*!
     * @brief constructor for SpriteComponent
     * @param filepath: string that Represents the filepath of our sprite
     * @param src: SDL_rect representing the rectangle we want to create
     */
    SpriteComponent(std::string filePath, SDL_Rect src);
    
    //!destructor fpr SpriteComponent
    ~SpriteComponent();

    //!renders our sprite
    void render();

    /*!
     * @brief updates the position of this object
     * @param pos: Vec2 that we want to apply changes to
     */
	void updatePosition(Vec2 pos);

    //! @return float value that represents the width of this object
	float getWidth();

    //! @return float value that represents the height of this object
	float getHeight();

    /*!
     * @brief sets the Dimensions of this object
     * @param width: float value we want this object's width to be
     * @param height: float value we want this object's height to be
     */
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
