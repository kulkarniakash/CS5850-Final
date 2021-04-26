#ifndef CAMERA
#define CAMERA

#include<Direction.h>
#include<Vec2.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/**
*Camera class that keeps track of position of camera (top-left corner)
*and moves the camera when given updated
*/
class Camera {
public:
	// x,y position of camera in absolute coordinates. horizontal and vertical speed of the camera
	Camera(Vec2 pos, float xSpeed, float ySpeed);

	// updatea the camera psotion according to the direction given
	void update(Direction dir);

	// returns the corrected position of the object given its initial position
	Vec2 getObjectPos(Vec2 initialPos);
	// returns the position of the camera
	Vec2 getCameraPos();
private:
	// x,y speed of the camera
	Vec2 speed;
	// position of the top-left corner of the camera
	Vec2 pos;
};

#endif

