#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include "GameObjectController.h"
#include "BombController.h"

// Enemy controller processes enemy movement and behaviour.
// Moves all managed elements left, right, down (when switching direction),
// changes their velocity, handles random bomb fire.
class EnemyController : public GameObjectController<Enemy>
{
protected:
	Vector2<float> currentDirection;// Current moving direction.
	Vector2<float> velocity;		// Velocity. A vector to move along.
	float timeBetweenMoveDown;		// Delay for enemies moving down.
	float timeSinceFire;			// Time since last fire.
	float fireCooldown;				// Cooldown for rocket fire.
	int currentSprite;				// Selected enemy sprite. Is toggled between new armies.
	int amountKilled;				// Number of enemies that died.
	bool invaded;					// Flag indicating enemies reached bottom of screen. (Game over condition)
public:
	EnemyController();

	void setVelocity(Vector2<float> m) { velocity = m; }
	int getSpriteNumber() { return currentSprite; }
	bool getInvaded() { return invaded; }

	// Reinitializes controller.
	void reset();

	// Full update.
	// Takes the time since last update.
	void update(float deltaTime);

	// Fire bombs. Maybe. 
	// Needs a bomb controller to manage the bombs.
	void fireBombsRandomly(BombController &bombsCtrl);

private:
	// Handles movement near edges.
	void handleOutOfBounds();

	// Updates velocity. Factors in screen width and enemies remiaining.
	void updateVelocity();

	// Creates new army if all are dead
	void spawnEnemies();
};

#endif