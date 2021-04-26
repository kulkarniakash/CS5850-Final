#ifndef CHARACTER_SPRITE_COMPONENT_HPP
#define CHARACTER_SPRITE_COMPONENT_HPP
#include "SpriteComponent.hpp"

class CharacterSpriteComponent : public SpriteComponent { 
public:
    //constructor for CharacterSpriteComponent
    CharacterSpriteComponent(std::string filePath, SDL_Rect src, SDL_Rect dest, int rows, int cols);
    
    //destructor fpr CharacterSpriteComponent
    ~CharacterSpriteComponent();

    /*! Registers an action (a named range of frames) with given properties.
        *  @param animationName name of action
        *  @param startFrame index of first frame of action
        *  @param endFrame index of last frame of action
    */
    void addAnimation(const std::string& animationName, const int& startFrame, const int& endFrame);
    
    /*! Plays an action with given name.
        *  @param animationName name of action to play
        *  @param isFlipped whether to play the action while rendering frames flipped around
        *  @param animSpeed speed of the animation
    */
    void performAnimation(const std::string & animationName, const bool& isFlipped, float animSpeed);
    
    //Updates our sprite
    void updateFrame();

	void updatePosition(Vec2 pos);

    //! Sets whether the action should loop upon reaching its last frame or not.
    bool& loopAction();

    void setLoop(bool loop);
    

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
