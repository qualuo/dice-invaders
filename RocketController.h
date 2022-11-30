#ifndef ROCKETCONTROLLER_H
#define ROCKETCONTROLLER_H
#include "GameObjectController.h"

// Rocket controller processes Rocket movement.
// Moves all managed elements up and destroys them.
class RocketController : public GameObjectController<Rocket>
{
protected:
	Vector2<float> velocity;	/// The 2d vector to move along.
public:
	RocketController();

	void setVelocity(Vector2<float> m) { velocity = m; }

	// Full update.
	// Takes the time since last update.
	void update(float deltaTime);
private:
	void handleOutOfBounds();
};

#endif