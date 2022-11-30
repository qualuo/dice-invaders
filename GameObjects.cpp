#include "GameObjects.h"

GameObject::GameObject(float x, float y, int width, int height, int health)
{
	this->position.set(x, y);
	this->size.set(width, height);
	this->health = health;
}

GameObject::GameObject(Vector2<float> position, Vector2<int> size, int health)
{ 
	this->position = position;
	this->size = size;
	this->health = health;
}


Ship::Ship(float x, float y) : GameObject(x, y, 32, 32, 3) 
{
}

Enemy::Enemy(float x, float y) : GameObject(x, y, 32, 32, 1) 
{
}

Bomb::Bomb(float x, float y) : GameObject(x, y, 16, 32, 1) // 16 width, because the image looks thinner
{
}

Rocket::Rocket(float x, float y) : GameObject(x, y, 16, 32, 1) 
{
}

float distanceBetween(GameObject o1, GameObject o2)
{
	return o1.position.distanceTo(o2.position);
}
