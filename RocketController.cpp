#include "RocketController.h"

RocketController::RocketController() 
{
	velocity = Vector2<float>(0,-1) * (float)(GameConstants::WINDOW_HEIGHT * 1.5f);
	//velocity = Directions::up * (float)(GameConstants::WINDOW_HEIGHT * 1.5f);
	// Couldn't use Directions::up here...
}

void RocketController::update(float deltaTime) 
{
	removeUnhealthy();
	handleOutOfBounds();
	updateMovement(velocity * deltaTime);
}

void RocketController::handleOutOfBounds() 
{
	for (size_t i = 0; i < container.size(); i++)
	{
		if (container[i].position.clampY(0,
			GameConstants::WINDOW_HEIGHT + 32)) 
		{
			container[i].setHealth(0);
		}
	}
}

