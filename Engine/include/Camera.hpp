// Taken from Akash's previous team assignment (wecook)

#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

// Include our custom headers.
#include <Vec2.hpp>

// Store screen's width and height into two extern const integers.
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/**
 * @brief A enum class for direction.
*/
enum Direction {
	Up = 0,
	Down,
	Left,
	Right,
	No
};

/**
 * @brief Camera class that keeps track of position of camera (top-left corner) and moves the camera when given updated.
*/
class Camera {
public:

	/**
	 * @brief Three arguments constructor of camera object.
	 * @param pos A Vec2 object indicates the top-left corner position of current camera object in absolute coordinates.
	 * @param xSpeed A float indicates the horizontal speed of the current camera object.
	 * @param ySpeed A float indicates the vertical speed of the current camera object.
	*/
	Camera(Vec2 pos, float xSpeed, float ySpeed);

	/**
	 * @brief Update the camera's position according to the given direction.
	 * @param dir A Direction enum indicates the direction of the current camera object.
	*/
	void update(Direction dir);

	/**
	 * @brief Get the correct position of the object given its initial position.
	 * @param initialPos A Vec2 object indicates the position of the input object.
	 * @return A Vec2 object indicates the input object's correct position.
	*/
	Vec2 getObjectPos(Vec2 initialPos);

	/**
	 * @brief Get the camera's top-left corner position.
	 * @return A Vec2 object indicates the camera's top-left corner position.
	*/
	Vec2 getCameraPos();

	/**
	 * @brief Update the camera's top-left corner position according to the input new position.
	 * @param newPos A Vec2 object indicates the camera's new top-left corner position.
	*/
	void updatePosition(Vec2 newPos);

private:
	// The speed of the camera.
	Vec2 speed;
	// The top-left corner position of the of the camera.
	Vec2 pos;
};

#endif

