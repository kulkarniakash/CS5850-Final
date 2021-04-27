#ifndef COLLISION
#define COLLISION
#include "AnimateObject.hpp"
#include "GameObject.hpp"
#include <vector>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class AnimateObject;

/*!
 *  @brief class that represents the Colloision Component of our GameObject
 *  Handles Collisions of our GameObject
 */
class CollisionComponent {
public:
    
    /*!
     *  @brief Constructor of our CollisionComponent
     *  @param obj: AnimateObject that we want to detect colloision for
     */
	CollisionComponent(AnimateObject* obj);

    //! @brief Destructor of our CollisionComponent
	~CollisionComponent();
    
    /*!
     *  @brief handles the collision of our Object
     *  @param objs: A vector of game objects we want to test collisions against
     */
	bool handleCollisions(std::vector<GameObject*> objs);
	
	 /*!
     *  @brief  Upon a collision, add the inputted argument as a callback.
     *  @param func: A python function object
     */
    void addCollisionCallback(py::object func);

private:
	Vec2 getCorrection(GameObject* obj);

	AnimateObject* m_animateobject;
    std::vector<py::object> m_callbacks;
};

#endif
