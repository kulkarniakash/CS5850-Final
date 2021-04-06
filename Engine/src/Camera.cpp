// Taken from Akash's previous team assignment (wecook)

#include <Camera.hpp>

// Three arguments constructor of camera object.
Camera::Camera(Vec2 pos, float xSpeed, float ySpeed) {
	this->pos = pos;
	speed = Vec2(xSpeed, ySpeed);
}

// Get the correct position of the object given its initial position.
Vec2 Camera::getObjectPos(Vec2 initialPos) {
	return initialPos - pos;
}

// Get the camera's top-left corner position.
Vec2 Camera::getCameraPos() {
	return pos;
}

// Update the camera's position according to the given direction.
void Camera::update(Direction dir) {
	switch (dir) {
	case Direction::Up:
		pos -= Vec2(0, speed.y);
		break;
	case Direction::Down:
		pos += Vec2(0, speed.y);
		break;
	case Direction::Left:
		pos -= Vec2(speed.x, 0);
		break;
	case Direction::Right:
		pos += Vec2(speed.x, 0);
		break;
	default:
		break;
	}
}

// Update the camera's top-left corner position according to the input new position.
void Camera::updatePosition(Vec2 newPos) {
	pos = newPos;
}