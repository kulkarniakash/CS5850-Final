// Taken from Akash's previous team assignment (wecook)

#ifndef VEC2_H
#define VEC2_H
#pragma once

/*!
 * @brief This class represents all behaviors of 2d vectors needed in this game.
*/
class Vec2 {
public:

	//! @brief Default constructor of Vec2 class.
	Vec2();

	/*!
	 * @brief Two arguments constructor of Vec2 class.
	 * @param x A float indicates the x value of the Vec2 object.
	 * @param y A float indicates the y value of the Vec2 object.
	*/
	Vec2(float x, float y);

	/*!
	 * @brief Operator overloading of +=.
	 * @param  A const reference of a Vec2 object indicates another Vec2 object.
	 * @return A reference of a Vec2 object indicates the result after += operation.
	*/
	Vec2& operator+=(Vec2 const&);

	/*!
	 * @brief Operator overloading of -=.
	 * @param  A const reference of a Vec2 object indicates another Vec2 object.
	 * @return A reference of a Vec2 object indicates the result after -= operation.
	*/
	Vec2& operator-=(Vec2 const&);

	/*!
	 * @brief Operator overloading of *.
	 * @param  A float indicates the magnitude.
	 * @return A Vec2 object indicates the result after * operation.
	*/
	Vec2 operator*(float);

	// Two float indicate the Vec2 object's x and y values.
	float x, y;
};

/*!
 * @brief Inline function of + operator overloading.
 * @param a A const reference of a Vec2 object indicates one Vec2 object.
 * @param b A const reference of a Vec2 object indicates another one Vec2 object.
 * @return A Vec2 object indicates the result after adding two Vec2 objects.
*/
inline Vec2 operator+(Vec2 const& a, Vec2 const& b) {
	return Vec2(a.x + b.x, a.y + b.y);
}

/*!
 * @brief Inline function of - operator overloading.
 * @param a A const reference of a Vec2 object indicates one Vec2 object.
 * @param b A const reference of a Vec2 object indicates another one Vec2 object.
 * @return A Vec2 object indicates the result after minusing two Vec2 objects.
*/
inline Vec2 operator-(Vec2 const& a, Vec2 const& b) {
	return Vec2(a.x - b.x, a.y - b.y);
}

/*!
 * @brief Inline function of == operator overloading.
 * @param a A const reference of a Vec2 object indicates one Vec2 object.
 * @param b A const reference of a Vec2 object indicates another one Vec2 object.
 * @return A boolean to determine if both of the Vec2 objects are equal
*/
inline bool operator==(Vec2 const& a, Vec2 const& b) {
	return a.x == b.x && a.y == b.y;
}

/*!
 * @brief Inline function of != operator overloading.
 * @param a A const reference of a Vec2 object indicates one Vec2 object.
 * @param b A const reference of a Vec2 object indicates another one Vec2 object.
 * @return A boolean to determine if both of the Vec2 objects are not equal
*/
inline bool operator!=(Vec2 const& a, Vec2 const& b) {
	return !(a.x == b.x && a.y == b.y);
}

#endif 

