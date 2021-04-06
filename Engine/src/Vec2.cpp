// Taken from Akash's previous team assignment (wecook)
#include <Vec2.hpp>

// Default constructor of Vec2 class.
Vec2::Vec2() : x(0.0f), y(0.0f) {

}

// Two arguments constructor of Vec2 class.
Vec2::Vec2(float x, float y) : x(x), y(y) {

}

// Operator overloading of +=.
Vec2& Vec2::operator+=(Vec2 const& rhs) {
	x += rhs.x;
	y += rhs.y;

	return *this;
}

// Operator overloading of -=.
Vec2& Vec2::operator-=(Vec2 const& rhs) {
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

// Operator overloading of* .
Vec2 Vec2::operator*(float rhs) {
	return Vec2(x * rhs, y * rhs);
}
