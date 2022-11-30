#ifndef BOMBCONTROLLER_H
#define BOMBCONTROLLER_H
#include "GameObjectController.h"

// Bomb controller processes bomb movement.
// Moves all managed elements down and destroys them.
class BombController : public GameObjectController<Bomb>
{
protected:
	Vector2<float> velocity;	// The 2d vector to move along.
public:
	BombController();

	void setVelocity(Vector2<float> m) { velocity = m; }
	
	// Complete update and draw. Takes
	// the time since last update.
	void update(float deltaTime);

	void handleOutOfBounds();

};

#endif