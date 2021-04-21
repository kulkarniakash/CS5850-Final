#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include <stdio.h>
#include <Vec2.hpp>

class TransformComponent {
public:
    //constructs component
    TransformComponent(const Vec2 & position, const Vec2 & velocity);
    
    //destructs component
    ~TransformComponent();
    
    void update();
    
	Vec2 getPosition();
    
    //sets the position of the object
    void setPosition(const Vec2 & position);
    
    //sets the velocity of the object
    void setVelocity(const Vec2 & velocity);

	void updatePosition(const Vec2& position);

	void updateVelocity(const Vec2& velocity);

	Vec2 getVelocity();
    
private:
    Vec2 m_position;
    Vec2 m_velocity;
};
#endif
