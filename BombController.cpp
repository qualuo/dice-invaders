#include "BombController.h"

BombController::BombController()
{
	velocity = Directions::down * (float)(GameConstants::WINDOW_HEIGHT * 0.5f);
}

// Complete update and draw. Takes
// the time since last update.
void BombController::update(float deltaTime)
{
	handleOutOfBounds();
	removeUnhealthy();
	updateMovement(velocity * deltaTime);
}

void BombController::handleOutOfBounds() 
{
	for (size_t i = 0; i < container.size(); i++)
	{
		// Bombs are considered dead when no longer visible.
		if (container[i].position.clampY(0,
			GameConstants::WINDOW_HEIGHT - 32)) 
		{
			container[i].setHealth(0);
		}
	}
}