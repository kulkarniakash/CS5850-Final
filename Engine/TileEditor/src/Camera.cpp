#include<Camera.h>

Camera::Camera(Vec2 pos, float xSpeed, float ySpeed) {
	this->pos = pos;
	speed = Vec2(xSpeed, ySpeed);
}

Vec2 Camera::getObjectPos(Vec2 initialPos) {
	return initialPos - pos;
}

Vec2 Camera::getCameraPos() {
	return pos;
}

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