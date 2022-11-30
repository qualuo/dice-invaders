#include "EnemyController.h"

EnemyController::EnemyController()
{
	currentDirection = Directions::right;
	velocity = currentDirection * (float)(GameConstants::WINDOW_WIDTH * 0.1f);
	timeBetweenMoveDown = 0;
	timeSinceFire = 0;
	fireCooldown = 0.5f;
	currentSprite = 1;
	amountKilled = 0;
	invaded = false;
};

void EnemyController::reset() 
{
	GameObjectController::reset();
	currentDirection = Directions::right;
	velocity = currentDirection * (float)(GameConstants::WINDOW_WIDTH * 0.1f);
	timeBetweenMoveDown = 0;
	timeSinceFire = 0;
	fireCooldown = 0.5f;
	currentSprite = 1;
	amountKilled = 0;
	invaded = false;
}

void EnemyController::update(float deltaTime)
{
	timeSinceFire += deltaTime;
	timeBetweenMoveDown += deltaTime;
	amountKilled += removeUnhealthy();
	updateVelocity();
	handleOutOfBounds();
	updateMovement(velocity * deltaTime);
	if (container.size() == 0)
		spawnEnemies();
}

void EnemyController::fireBombsRandomly(BombController &bombsCtrl)
{
	if (timeSinceFire > fireCooldown)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (rand() % container.size() == 0)
			{
				bombsCtrl.create(container[i].position);
				timeSinceFire = 0;
				break; // With break; one fires at a time. Without, up to all of them can fire.
			}
		}
	}
}

// Handles movement near edges.
void EnemyController::handleOutOfBounds() 
{
	bool beyondX = false;
	for (size_t i = 0; i < container.size(); i++)
	{
		// Successfully invaded if reached bottom.
		if (container[i].position.getY() > GameConstants::WINDOW_HEIGHT - 32) invaded = true;

		// Move down and change direction if beyond X-coordinates.
		if (container[i].position.clampX(
			0,
			GameConstants::WINDOW_WIDTH - 32)) 
		{
			beyondX = true;
		}

	}

	// Change direction and moves all enemies down.
	// Iterate through enemies again to make sure to affect all.
	if (beyondX && timeBetweenMoveDown > 0.2f) // Delay to avoid multiple jumps
	{
		if (currentDirection.equals(Directions::left))
		{
			currentDirection = Directions::right;
		}
		else if (currentDirection.equals(Directions::right))
		{
			currentDirection = Directions::left;
		}
		for (auto & currentEnemy : container)
		{
			currentEnemy.position += (Directions::down * (GameConstants::WINDOW_HEIGHT / 25));
		}
		timeBetweenMoveDown = 0;
	}
}

// Updates velocity. Factors in screen width and enemies remaining.
void EnemyController::updateVelocity()
{
	velocity = currentDirection *
		((float)GameConstants::WINDOW_WIDTH * 0.05f +
			(GameConstants::ENEMY_ROWS * GameConstants::ENEMY_COLUMNS - container.size()) * 2.0f);
	if (container.size() == 1) velocity *= 3; // 3x multiplier for last alive

	// Did not go for multiplier with amountKilled because the game
	// becomes impossible to keep going eventually (because rocket fire is unchanged)
}

// Creates new army if all are dead.
void EnemyController::spawnEnemies()
{
	container.clear();
	currentDirection = Directions::right;
	currentSprite == 0 ? currentSprite = 1 : currentSprite = 0;
	for (int i = 1; i <= GameConstants::ENEMY_ROWS; i++) // Starting at 1 matters here, for offset.
	{
		for (int j = 1; j <= GameConstants::ENEMY_COLUMNS; j++)
		{
			Enemy enemy = { (float)GameConstants::CELL_WIDTH * j,
				GameConstants::ENEMY_Y_OFFSET + (float)GameConstants::CELL_HEIGHT * i };
			container.push_back(enemy);
		}
	}
}
