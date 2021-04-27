#ifndef INANOBJ
#define INANOBJ
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "CollisionComponent.hpp"
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class CollisionComponent;
class GameObject;
namespace py = pybind11;

/*!
 @brief Class that represents an animate object
 Inherits from GameObject
 Differs by not being allowed to handle input
 */
class AnimateObject : public GameObject {
public:
    
    /*!
     @brief Constrcutor for AnimateObject.
     @param name: string that represents the name of the object.
     @param w: float that represents the width of the object.
     @param h: float that represents the height of the object.
     */
	AnimateObject(std::string name, float w, float h);

	~AnimateObject();
    
    /*!
     @brief Updates the position of the object.
     @param pos: Vec2 that represents the position of the object.
     */
	void updatePosition(Vec2 pos);
    
    /*!
     @brief Updates the velocity of the object.
     @param pos: Vec2 that represents the velocity of the object.
     */
	void updateVelocity(Vec2 vel);

    /*!
     @brief Sets the position of the object.
     @param pos: Vec2 that represents the position of the object we want to change it to.
     */
	void setPosition(Vec2 pos);

    /*!
     @brief Sets the velocity of the object.
     @param pos: Vec2 that represents the velocity of the object we want to change it to.
     */
	void setVelocity(Vec2 vel);
    
    /*!
     @brief Handles and detects the collision of other objects.
     @param objs: A vector of game objects that we want to detect for collision.
     */
	void handleCollision(std::vector<GameObject*> objs, std::vector<AnimateObject*> animObjs);
    
    /*!
    @brief Updates the Sprite Component of this object.
     */
	void updateSprite();

    /*!
     @brief Updates the Transform Component of this object.
     */
	void updateTransform();

	//! Destroys the class
	void Destroy();

    /*!
		@brief Upon a collision, add the inputted argument as a callback.
		@param object: A python function object
     */
    void addCollisionCallback(py::object);

protected:
	CollisionComponent* m_collisioncomp;
};
#endif
