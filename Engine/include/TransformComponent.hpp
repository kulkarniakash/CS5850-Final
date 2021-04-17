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
    
    //updates position();
    void update();
    
    //get our x position
    float getXPosition();
    
    //get our y position
    float getYPosition();
    
    //sets the position of the object
    void setPosition(const Vec2 & position);
    
    //sets the velocity of the object
    void setVelocity(const Vec2 & velocity);
    
private:
    Vec2 m_position;
    Vec2 m_velocity;
};
#endif
