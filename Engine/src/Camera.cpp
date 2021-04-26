// Taken from Akash's previous team assignment (wecook)

#include <Camera.hpp>

Camera* Camera::instance = nullptr;

// Three arguments constructor of camera object.
Camera::Camera() {
}

Camera& Camera::getInstance() {
	if (!instance) {
		instance = new Camera();
	}

	return (*instance);
}

// Get the correct position of the object given its initial position.
Vec2 Camera::correctPosition(GameObject* obj) {
	if (m_gameObject != nullptr) {
		return obj->getTransformComponent()->getPosition() - pos;
	}
	else {
		return obj->getTransformComponent()->getPosition();
	}
}

// Get the camera's top-left corner position.
Vec2 Camera::getCameraPos() {
	return pos;
}

// Update the camera's position according to the given direction.
/*void Camera::update(Direction dir) {
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
}*/

void Camera::update() {
	if (m_gameObject != nullptr) {
		pos = m_gameObject->getTransformComponent()->getPosition() + Vec2(m_gameObject->getWidth() / 2, m_gameObject->getHeight() / 2) - Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}

// Update the camera's top-left corner position according to the input new position.
/*void Camera::updatePosition(Vec2 newPos) {
	pos = newPos;
}*/

void Camera::bindToObject(GameObject* obj) {
	m_gameObject = obj;
}