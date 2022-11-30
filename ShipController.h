#ifndef SHIPCONTROLLER_H
#define SHIPCONTROLLER_H
#include "GameConstants.h"
#include "GameObjectController.h"
#include "RocketController.h"

// Ship controller processes ship movement.
// Moves all managed elements left and right and handles firing rockets.
class ShipController : public GameObjectController<Ship>
{
protected:
	Vector2<float> velocity;	// The 2d vector to move along.
	float timeSinceFire;		// Time since last fire.
	float fireCooldown;			// Cooldown for rocket fire.
public:
	ShipController();

	void setVelocity(Vector2<float> m) { velocity = m; }
	Vector2<float> getVelocity() { return velocity; }

	// Reinitializes controller.
	void reset();

	// Full update.
	// Takes the time since last update.
	void update(float deltaTime);

	// Fires rocket from all ships managed by this controller.
	// Takes a rocket controller to manage the rockets.
	void fireRocket(RocketController &rocketsCtrl);
private:
	// Keeps ships within visible area.
	void handleOutOfBounds();

};

#endif