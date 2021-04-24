#ifndef VEC2
#define VEC2

class Vec2 {
public:

	Vec2();

	Vec2(float x, float y);

	Vec2& operator+=(Vec2 const&);
	Vec2& operator-=(Vec2 const&);

	Vec2 operator*(float);

	float x, y;
};

inline Vec2 operator+(Vec2 const& a, Vec2 const& b) {
	return Vec2(a.x + b.x, a.y + b.y);
}

inline Vec2 operator-(Vec2 const& a, Vec2 const& b) {
	return Vec2(a.x - b.x, a.y - b.y);
}

#endif 

