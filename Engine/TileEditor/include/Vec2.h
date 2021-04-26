#ifndef VEC2
#define VEC2


//! @brief Class that represents a Vec2 containing an Object's x and y values
class Vec2 {
public:

    //! @brief Constructs a Vec2 object
	Vec2();

    /*!
     * @brief Constructs a Vec2 object
     * @param x: x position of an object
     * @param y: y position of an object
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

#endif 

