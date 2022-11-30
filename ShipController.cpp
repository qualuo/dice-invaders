#include "ShipController.h"

ShipController::ShipController()
{
	velocity = Vector2<float>(0, 0);
	timeSinceFire = 0;
	fireCooldown = 0.5f;
}

void ShipController::reset() 
{
	GameObjectController::reset();
	velocity = Vector2<float>(0, 0);
	timeSinceFire = 0;
}

void ShipController::update(float deltaTime) 
{
	timeSinceFire += deltaTime;
	removeUnhealthy();
	updateMovement(velocity * deltaTime);
	handleOutOfBounds();
}

void ShipController::fireRocket(RocketController &rocketsCtrl)
{
	if (timeSinceFire > fireCooldown)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			rocketsCtrl.create(container[i].position);
			timeSinceFire = 0;
		}
	}
}

void ShipController::handleOutOfBounds()
{
	for (size_t i = 0; i < container.size(); i++)
	{
		container[i].position.clamp(
			32 * i,
			GameConstants::WINDOW_WIDTH - 32 * (i + 1),
			0,
			GameConstants::WINDOW_HEIGHT - 32);
		// i multiplier allows multiple ships that
		// gain smaller and smaller borders. Prevents
		// them from stacking. When minX < maxX, things get problematic.
		// Not that the game is supposed to have multiple ships anyway.
	}
}
