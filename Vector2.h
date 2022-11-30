#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>

// Represents a 2D geometric vector. 
template <typename T> 
class Vector2 
{
public:
	Vector2(T x = 0, T y = 0) {
		this->x = x;
		this->y = y;
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	// Sets this vector's components to specified values.
	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}
		
	// Alters vector's components to be within specified ranges (inclusive).
	// Returns true if beyond range and this vector was altered.
	// Returns false if not beyond range, thus no altering.
	bool clamp(T minX, T maxX, T minY, T maxY) {
		bool b = false;
		if (x < minX) { x = minX; b = true; };
		if (x > maxX) { x = maxX; b = true; };
		if (y < minY) { y = minY; b = true; };
		if (y > maxY) { y = maxY; b = true; };
		return b;
	}

	// Modifies vector's components to be within specified ranges (inclusive).
	// Returns true if beyond range and this vector was altered.
	// Returns false if not beyond range, thus no altering.
	bool clampX(T minX, T maxX) {
		bool b = false;
		if (x < minX) { x = minX; b = true; };
		if (x > maxX) { x = maxX; b = true; };
		return b;
	}

	// Modifies vector's components to be within specified ranges (inclusive).
	// Returns true if beyond range and this vector was altered.
	// Returns false if not beyond range, thus no altering.
	bool clampY(T minY, T maxY) {
		bool b = false;
		if (y < minY) { y = minY; b = true; };
		if (y > maxY) { y = maxY; b = true; };
		return b;
	}

	// Multiplies each component of vectors. 
	// Known as entrywise product or Hadamard product.
	Vector2 scale(const Vector2 v) const {
		return (Vector2(x * v, y * v));
	}

	// Returns this vector's magnitude/length.
	// Magnitude = sqrt(x*x + y*y)
	float magnitude() {
		return sqrt(x * x + y * y);
	}

	// Returns true if vector dimensions are equal.
	bool equals(Vector2 v) {
		return (x == v.x && y == v.y);
	}

	Vector2 & operator + (const Vector2 & v) const {
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 & operator - (const Vector2 & v) const {
		return Vector2(x - v.x, y - v.y);
	}

	// Sets this vector.
	Vector2 & operator = (const Vector2 & v) {
		x = v.x; y = v.y;
		return *this;
	}

	// Adds another vector's components to this one.
	Vector2 & operator += (const Vector2 & v) {
		x = x + v.x; y = y + v.y;
		return *this;
	}

	// Multiplies each component of 
	// vector with a scalar. 
	 Vector2 operator * (const float & t) const {
		return Vector2(x * t, y * t);
	}

	 Vector2 operator *= (const float & t) {
		 x = x * t; y = y * t;
		 return *this;
	 }
	
	// Gets distance to another vector.
	// Distance = (vec1 - vec2).magnitude()
	float distanceTo(Vector2 v) {
		return (*this - v).magnitude();
	}

private:
	T x;
	T y;
};

#endif

