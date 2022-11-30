#ifndef GAMEOBJECTCONTROLLER_H
#define GAMEOBJECTCONTROLLER_H
#include <vector>
#include "GameConstants.h"
#include "GameObjects.h"
#include "Vector2.h"

// Manages any amount of game objects of certain type.
// Provides basic functionality for managing said game objects, including
// instantiating game objects, and movement.
template <class T>
class GameObjectController
{
public:
	std::vector<T> container; // Holds all elements.

	GameObjectController() {};

	// Add a new element this controller manages
	// at specified position.
	void create(Vector2<float> pos)
	{
		T e(pos);
		container.push_back(e);
	}

	// Reinitializes controller.
	void reset() {
		container.clear();
		std::vector<T> v;
		container.swap(v);
	}

	// Erases all elements with 0 or less health.
	// Returns an int indicating number of elements erased.
	int removeUnhealthy() {
		int amountRemoved = 0;
		for (size_t i = 0; i < container.size(); i++)
		{
			// Check if destroyed.
			if (!container[i].isHealthy())
			{
				container.erase(container.begin() + i);
				amountRemoved++;
				continue;
			}
		}
		return amountRemoved;
	}

	// Moves all elements along a 2D vector. (Vector addition)
	// Parameter is the change in movement.
	// Hint: distance = velocity * time
	void updateMovement(Vector2<float> distance)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			container[i].position += distance;
		}
	}

};

// Helper 2d vectors. 
// Used for directions. Up is up on screen.
namespace Directions {
	const Vector2<float> up(0, -1);				// Represents Vector2(0, -1).
	const Vector2<float> down(0, 1);			// Represents Vector2(0, 1).
	const Vector2<float> left(-1, 0);			// Represents Vector2(-1, 0).
	const Vector2<float> right(1, 0);			// Represents Vector2(1, 0).
}

#endif