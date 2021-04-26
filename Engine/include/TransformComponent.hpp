#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include <stdio.h>
#include <Vec2.hpp>

/*!
 * @brief class that represents the TransformComponent
 * handles creating and updating positions and velocities of object that include this component
 */
class TransformComponent {
public:
    
    //constructs component
    TransformComponent(const Vec2 & position, const Vec2 & velocity);
    
    //! @brief destructs component
    ~TransformComponent();
    
    //! @brief updates this Object's position by the current velocity
    void update();
    
    //! @return Vec2 of this Object's position
	Vec2 getPosition();
    
    /*!
     * @brief sets the position of the object
     * @param position: Vec2 of the position we want to assign to this object
     */
    void setPosition(const Vec2 & position);
    
    /*!
     * @brief sets the velocity of the object
     * @param velocity: Vec2 of the velocity we want to assign to this object
     */
    void setVelocity(const Vec2 & velocity);

    /*!
     * @brief Updates the position of the object
     * @param position: Vec2 of the position we want to update to this object
     */
	void updatePosition(const Vec2& position);

    /*!
     * @brief updates the velocity of the object
     * @param velocity: Vec2 of the velocity we want to update to this object
     */
	void updateVelocity(const Vec2& velocity);

    //! @return Vec2 of this Object's velocity
	Vec2 getVelocity();
    
private:
    Vec2 m_position;
    Vec2 m_velocity;
};
#endif
