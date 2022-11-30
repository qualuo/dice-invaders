#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "Vector2.h"

// A GameObject is part of the game world.
// Considered Model and is separated from any logic.
class GameObject
{
protected:
	int health;				 // Hit points.

	// Only allow subclasses to instantiate.
	GameObject(float x, float y, int width, int height, int health);
	GameObject(Vector2<float> position, Vector2<int> size, int health);
public:
	Vector2<float> position;	// Horizontal and vertical coordinates.
	Vector2<int> size;			// Width and height.
	
	// Sets position.
	void setPosition(Vector2<float> position) { this->position = position; }
	
	// Sets health.
	void setHealth(int health) { this->health = health; }

	// Adds to health.
	void addHealth(int health) { this->health += health; }

	// Returns health.
	int getHealth() { return this->health; }

	// Returns true if health above 0.
	bool isHealthy() { return (health > 0) ? true : false; }

};

// Following derived classes are so small,
// giving them their own files would be more of an inconvenience at this stage.

class Ship : public GameObject
{
public:
	Ship(float x, float y);
	Ship(Vector2<float> v) : Ship(v.getX(), v.getY()) {};
};

class Enemy : public GameObject
{
public:
	Enemy(float x, float y);
	Enemy(Vector2<float> v) : Enemy(v.getX(), v.getY()) {};
};

class Bomb : public GameObject
{
public:
	Bomb(float x, float y);
	Bomb(Vector2<float> v) : Bomb(v.getX(), v.getY()) {};
};

class Rocket : public GameObject
{
public:
	Rocket(float x, float y);
	Rocket(Vector2<float> v) : Rocket(v.getX(), v.getY()) {};
};

// Get distance between two objects.
float distanceBetween(GameObject o1, GameObject o2);

#endif