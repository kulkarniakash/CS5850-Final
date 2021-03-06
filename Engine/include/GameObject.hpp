#ifndef GAME_OBJ
#define GAME_OBJ
#include <stdio.h>
#include <string>
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "CharacterSpriteComponent.hpp"
#include "Camera.hpp"
#include "SoundComponent.hpp"

class SpriteComponent;
class CharacterSpriteComponent;
class Camera;


//! @brief class that Represents a GameObject, which contains all of the components
class GameObject {
public:
    
    //! @brief constructs our GameObject
	GameObject();

    /*!
     * @brief constructs our GameObject
     * @param gameObjectName: string that represents the GameObject's Name
     * @param width: float value of the GameObject's width
     * @param height: float value of the GameObject's height
     */
    
    GameObject(std::string gameObjectName, float width, float height);

    
    /*!
     * @brief Destructs our GameObject
     */
    ~GameObject();

    
    /*!
     * @brief adds a transformComponent to our GameObject
     * @param transformComponent: the TransformComponent Object we want to add
     */
    void addTransformComponent(TransformComponent* transformComponent);

    
    /*!
     * @brief adds a SpriteComponent to our GameObject
     * @param spriteComponent: the SpriteComponent Object we want to add
     */
    void addSpriteComponent(SpriteComponent* spriteComponent);

    /*!
     * @brief adds a CharacterSpriteComponent to our GameObject
     * @param characterSpriteComponent: the characterSpriteComponent Object we want to add
     */
    void addCharacterSpriteComponent(CharacterSpriteComponent* characterSpriteComponent);
    
    
    /*!
     * @brief adds a SoundComponent to our GameObject
     * @param soundComponent: the SoundComponent Object we want to add
     */
    void addSoundComponent(SoundComponent * soundComponent);
    
    //! @return a pointer of our TransformComponent
    TransformComponent* getTransformComponent();
    
    //! @return a pointer of our CharacterSpriteComponent
    CharacterSpriteComponent* getCharacterSpriteComponent();
    
    //! @return a pointer of our SpriteComponent
    SpriteComponent* getSpriteComponent();
    
    //! @return a pointer of our Sound Component
    SoundComponent * getSoundComponent();

    //! @brief renders this GameObject
    void render();

    //! @return float value that represents the width of this GameObject
	float getWidth();

    //! @return float value that represents the height of this GameObject
	float getHeight();

    //! Destroys the class
    void Destroy();

    //! Returns the name of the GameObject as a string
    std::string getGameObjectName();

    
protected:
	float width, height;
    std::string m_gameObjectName;
    TransformComponent* m_transformComponent;
    SpriteComponent* m_spriteComponent;
    CharacterSpriteComponent* m_characterSpriteComponent;
    SoundComponent * m_soundComponent;
};
#endif 
