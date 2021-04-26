#ifndef PLAYOBJ
#define PLAYOBJ
#include "AnimateObject.hpp"
#include "ControllerComponent.hpp"

class ControllerComponent;
class AnimateObject;

/*!
 * @brief class that represents a PlayerObject
 * Inherits from AnimateObject, Handles animations based on controller input
 */
class PlayerObject : public AnimateObject {
public:
    
    /*!
     * @brief constructs a PlayerObject
     * @param name: string that represents name of a PlayerObject
     * @param w: float value that represents the width
     * @param h: float value that represents the height
     */
	PlayerObject(std::string name, float w, float h);

	~PlayerObject();

    /*!
     *  @brief adds a ControllerComponent to this Object
     *  @param controllerComponent: A ControllerComponent we want to add
     */
	void addControllerComponent(ControllerComponent* controllerComponent);

    //! @return ControllerComponent of this object
	ControllerComponent* getControllerComponent();

    /*!
     * @brief updates the velocity of our controller
     * @param vel: Vec2 that we want to update in our current controlVelocity
     */
	void updateControllerVelocity(Vec2 vel);

    /*!
     * @brief sets the veloctiy of our controller
     * @param vel: Vec2 that we want to assign our controlVelocity
     */
	void setControllerVelocity(Vec2 vel);

    //! @return Vec2 of our controlVelocity
	Vec2 getControllerVelocity();

    //! Updates this Object's TransformComponent and position of our SpriteComponent
	void updateTransform();

	//! Destroys the class
	void Destroy();

private:
	ControllerComponent* m_controllerComponent;
	Vec2 controlVelocity;
};
#endif
