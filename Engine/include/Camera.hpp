// Taken from Akash's previous team assignment (wecook)

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GlobalAttributes.hpp"

// Include our custom headers.
#include <Vec2.hpp>
#include "GameObject.hpp"

// Store screen's width and height into two extern const integers.


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

private:
    /**
     * @brief Constructor for Camera object
     */
	Camera();

	static Camera* instance;

    /**
     * @brief Copy Constructor for Camera Object
     * @param camera: Camera object we want to construct
     */
	Camera(Camera const &);
    
    /**
     * @brief Operator Function to assign a Camera object
     * @param camera: Camera object we want to assign
    */
	void operator=(Camera const&);
public:
    
    /**
     * @brief creates an instance of a Camera object
     */
	static Camera& getInstance();

	/**
	 * @brief Update the camera's position according to the given direction.
	*/
	void update();

	/**
	 * @brief Updates the gameObjects position to be its correct position
     *   @param obj: GameObject we want to correct the position onto our GameObject
	*/
	void correctObj(GameObject* obj);

	/**
	 * @brief Get the camera's top-left corner position.
	 * @return A Vec2 object indicates the camera's top-left corner position.
	*/
	Vec2 getCameraPos();

	
    /**
     * @brief Sets the camera to 'lock' onto an object.
     * @param obj: GameObject that we want the camera to lock onto.
     */
	void bindToObject(GameObject* obj);

private:
	// The speed of the camera.
	// Vec2 speed;
	// The top-left corner position of the of the camera.
	Vec2 pos;
	GameObject* m_gameObject = nullptr;
};

#endif

