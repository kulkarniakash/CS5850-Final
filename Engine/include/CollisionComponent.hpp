#ifndef COLLISION
#define COLLISION
#include "AnimateObject.hpp"
#include "GameObject.hpp"
#include <vector>
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
	void handleCollisions(std::vector<GameObject*> objs);

private:
	Vec2 getCorrection(GameObject* obj);

	AnimateObject* m_animateobject;
};

#endif
