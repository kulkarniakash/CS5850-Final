#ifndef CAMERA
#define CAMERA

#include<Direction.h>
#include<Vec2.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/*!
 * @brief Camera class that keeps track of position of camera (top-left corner)
 * and moves the camera when given updated
 */
class Camera {
public:
	/*! @brief Constructs our Camera
     @param pos: Vec2 that represents the position of our Camera
     @param xSpeed: float that represents the Horzizontal speed of our Camera
     @param ySpeed: float that represents the Vertical speed of our Camera
     */
	Camera(Vec2 pos, float xSpeed, float ySpeed);

	/*! @brief updatea the camera psotion according to the direction given
     @param dir: Direction that we want to update our Camera's Position towards
     */
	void update(Direction dir);

	//! @return Vec2 that is the corrected position of the object given its initial position
	Vec2 getObjectPos(Vec2 initialPos);
    
	//! @return Vec2 that is the position of the camera
	Vec2 getCameraPos();
private:
	// x,y speed of the camera
	Vec2 speed;
	// position of the top-left corner of the camera
	Vec2 pos;
};

#endif

