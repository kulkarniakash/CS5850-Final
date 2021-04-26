#ifndef CHARACTER_SPRITE_COMPONENT_HPP
#define CHARACTER_SPRITE_COMPONENT_HPP
#include "SpriteComponent.hpp"

/**
 *  @brief Class that represents our CharacterSpriteComonent
 *  Inherits from our Sprite Component Class
 *  Handles performing animations of this object
 */
class CharacterSpriteComponent : public SpriteComponent { 
public:
    /**
     * @brief contstructor of our CharacterSpriteComponent
     * @param filepath: string that represents the file path of our sprite
     * @param src: An SDL_Rect representing a rectangle containing our Character Sprite
     * @param rows: int that represents the number of rows in our sprite sheet
     * @param cols: int that represents the number of cols in our sprite sheet
     */
    CharacterSpriteComponent(std::string filePath, SDL_Rect src, int rows, int cols);
    
    //! @brief Destructor fpr CharacterSpriteComponent
    ~CharacterSpriteComponent();

    /*!
     *  @brief Registers an action (a named range of frames) with given properties.
     *  @param animationName: string that represents the name of action
     *  @param startFrame: index that represnts the first frame of action
     *  @param endFrame: index of last frame of action
    */
    void addAnimation(const std::string& animationName, const int& startFrame, const int& endFrame);
    
    /*!
     *  @briefPlays an action with given name.
     *  @param animationName: string that represents the name of action to play
     *  @param isFlipped: boolean to determine whether to play the action while rendering frames flipped around
     *  @param animSpeed: float that represents speed of the animation
    */
    void performAnimation(const std::string & animationName, const bool& isFlipped, float animSpeed);
    
    //! Updates our sprite, moving onto the next frame of our spritesheet
    void updateFrame();

    /*!
     *  @brief Updates the position of our Sprite
     *  @param pos: Vec2 that represents the position we want to update our object to.
     */
	void updatePosition(Vec2 pos);

    //! Sets whether the action should loop upon reaching its last frame or not.
    bool& loopAction();
    

private:
    std::map<std::string, std::pair<int, int>> m_animations;
    std::pair<int, int> m_frameRange;
    int m_actualFrame = 0;
    float m_animationSpeed = 1;
    bool m_loopAction = true;
    std::string m_currentAction;

    int m_cols;
    int m_rows;

};
#endif
