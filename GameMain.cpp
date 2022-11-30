#include <time.h>
#include <sstream> // stringstream
#include <string.h>
#include "DiceInvadersLib.h"
#include "DiceInvaders.h"
#include "GameConstants.h"
#include "ShipController.h"
#include "EnemyController.h"
#include "RocketController.h"
#include "BombController.h"

// Keeps track of state.
class StateMachine {
public:
	enum State { INIT, PLAY, GAMEOVER, RESET };
	StateMachine() { state = INIT; };
	State state;
};

// Helper function.
// Checks if a GameObject container collides with those in another
// by checking distance between them. Decreases health if collided.
// Returns a vector containing the elements collided with
// from v2. Expects GameObject types.
template <typename T, typename T2>
std::vector<T2> checkCollision(std::vector<T> & v1, std::vector<T2> & v2)
{
	std::vector<T2> collidedWith;
	for (auto & t1 : v1)
	{
		for (auto & t2 : v2)
		{
			if (distanceBetween(t1, t2) <= t1.size.getX())
			{
				t1.addHealth(-1);
				t2.addHealth(-1);
				collidedWith.push_back(t2);
				continue;
			}
		}
	}
	return collidedWith;
}

// Dice Invaders interface related
DiceInvadersLib lib("DiceInvaders.dll");
IDiceInvaders* pInterface;			// Library interface
IDiceInvaders::KeyStatus keys;		// Keys status
ISprite* pPlayerSprite;				// Player sprite
ISprite* pEnemySprite;				// Enemy sprite
ISprite* pEnemy2Sprite;				// Second enemy sprite
ISprite* pRocketSprite;				// Rocket sprite 
ISprite* pBombSprite;				// Bomb sprite

// Game variables.
int score;							// Player score.
int startShips;						// Amount of starting ships. Extra feature.
float shipMovementSpeed;			// Movement multiplier for ships.		
float lastTime;						// Latest stored time.

// Utility
StateMachine sm;					// StateMachine manages state. (Just an int.)

// Controllers
ShipController shipsCtrl;			// Manages ships.
EnemyController enemiesCtrl;		// Manages enemies.
RocketController rocketsCtrl;		// Manages rockets.
BombController bombsCtrl;			// Manages bombs.

// Initializes Dice Invaders Library.
void initializeLibrary() 
{
	pInterface = lib.get();
	pInterface->init(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);
	pPlayerSprite = pInterface->createSprite("data/player.bmp");
	pRocketSprite = pInterface->createSprite("data/rocket.bmp");
	pEnemySprite = pInterface->createSprite("data/enemy1.bmp");
	pEnemy2Sprite = pInterface->createSprite("data/enemy2.bmp");
	pBombSprite = pInterface->createSprite("data/bomb.bmp");
}

// Deals with input from Dice Invaders interface.
void doHandleInput() {
	pInterface->getKeyStatus(keys);

	// Slow down velocity if no move keys or both move keys.
	if ((keys.right && keys.left) ||
		(!keys.right && !keys.left))
		shipsCtrl.setVelocity(shipsCtrl.getVelocity() * 0.95f); // Damping effect
	else if (keys.right) shipsCtrl.setVelocity(Directions::right * shipMovementSpeed);
	else if (keys.left) shipsCtrl.setVelocity(Directions::left * shipMovementSpeed);

	// Fire rocket.
	if (keys.fire) shipsCtrl.fireRocket(rocketsCtrl);
}


// Drawn screen during play state.
// Displays HUD and game objects.
void doDrawGameScreen() 
{
	// Draw score text.
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 1,
		GameConstants::TEXT_OFFSET1,
		"SCORE");

	// Convert int (score) to const char* using stringstream, then draw.
	std::stringstream sstream;
	sstream << score;
	std::string st = sstream.str();
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 1,
		GameConstants::TEXT_OFFSET2,
		st.c_str());

	// Draw lives text.
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 7,
		GameConstants::TEXT_OFFSET1,
		"LIVES ");
	// Draws a row of player sprites representing health
	// for every existing ship (managed by ship controller).
	for (std::vector<Ship>::iterator it = shipsCtrl.container.begin();
	it != shipsCtrl.container.end(); ++it)
	{
		for (int j = 0; j < it->getHealth(); j++)
		{
			pPlayerSprite->draw(
				GameConstants::WINDOW_WIDTH / 10 * 7 + it->size.getX() * j,
				GameConstants::TEXT_OFFSET2 * (it - shipsCtrl.container.begin() + 1));
		}
	}

	// Draw game objects.
	for (auto & ship : shipsCtrl.container)
	{
		pPlayerSprite->draw(ship.position.getX(), ship.position.getY());
	}
	for (auto & enemy : enemiesCtrl.container)
	{
		if (enemiesCtrl.getSpriteNumber() == 0)
			pEnemySprite->draw(enemy.position.getX(), enemy.position.getY());
		else if (enemiesCtrl.getSpriteNumber() == 1)
			pEnemy2Sprite->draw(enemy.position.getX(), enemy.position.getY());
	}
	for (auto & rocket : rocketsCtrl.container)
	{
		pRocketSprite->draw(rocket.position.getX(), rocket.position.getY());
	}
	for (auto & bomb : bombsCtrl.container)
	{
		pBombSprite->draw(bomb.position.getX(), bomb.position.getY());
	}

}

// Drawn when game over. Diplays
// score, texts.
void doDrawGameOverScreen()
{
	// Draw score texts.
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 1,
		GameConstants::TEXT_OFFSET1,
		"SCORE");
	// Convert int (score) to const char* using stringstream.
	std::stringstream sstream;
	sstream << score;
	std::string st = sstream.str();
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 1,
		GameConstants::TEXT_OFFSET2,
		st.c_str());

	// Draw lives text.
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 7,
		GameConstants::TEXT_OFFSET1,
		"SHIPS");
	// Convert int (startShips) to const char* using stringstream.
	sstream.str("");
	sstream << startShips;
	std::string st2 = sstream.str();
	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 10 * 7,
		GameConstants::TEXT_OFFSET2,
		st2.c_str());

	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 2 - 40,
		GameConstants::WINDOW_HEIGHT / 2 - 32,
		"GAME OVER");

	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 2 - 78,
		GameConstants::WINDOW_HEIGHT / 2 + 32,
		"Press space to play again.");

	pInterface->drawText(
		GameConstants::WINDOW_WIDTH / 2 - 130,
		GameConstants::WINDOW_HEIGHT / 2 + 82,
		"Press left/right to change number of ships.");

}

int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{
	// Init library.
	initializeLibrary();

	// Seed random number generator.
	srand(time(NULL));								

	startShips = 6;	

	while (pInterface->update()) // The returned bool dictates when to terminate.
	{
		// Update time.
		float currentTime = pInterface->getElapsedTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Limit FPS. A targeted 120 fps halved CPU use.
		// This seems to cause some noticeable stutter though.
		if (deltaTime < GameConstants::SEC_PER_FRAME)
			Sleep((GameConstants::SEC_PER_FRAME - deltaTime) * 1000);

		if (sm.state == StateMachine::INIT)
		{
			// Initialize game variables.
			score = 0;
			shipMovementSpeed = (float)GameConstants::WINDOW_WIDTH * 0.4f;

			// It's dangerous to go alone.
			for (int i = 0; i < startShips; i++) {
				Vector2<float> startPos(
				GameConstants::WINDOW_WIDTH / 4 + 32 * i,
				GameConstants::WINDOW_HEIGHT - 32);
				shipsCtrl.create(startPos);
			}

			sm.state = StateMachine::PLAY;
		}
		else if (sm.state == StateMachine::PLAY)
		{
			doHandleInput();

			// Update game objects.
			shipsCtrl.update(deltaTime);
			enemiesCtrl.update(deltaTime);
			enemiesCtrl.fireBombsRandomly(bombsCtrl);
			rocketsCtrl.update(deltaTime);
			bombsCtrl.update(deltaTime);

			// Check for collisions.
			checkCollision(bombsCtrl.container, shipsCtrl.container);
			checkCollision(enemiesCtrl.container, shipsCtrl.container);
			std::vector<Enemy> ve = checkCollision(rocketsCtrl.container, enemiesCtrl.container);
			for (size_t i = 0; i < ve.size(); i++) {
				score += 50 / shipsCtrl.container.size(); // Reward less with more ships.
			}

			// Game Over when no ships left or reach bottom (invade).
			if (shipsCtrl.container.size() <= 0 || 
				enemiesCtrl.getInvaded())
			{
				sm.state = StateMachine::GAMEOVER;
			}

			// Drawing (seen as View of MVC pattern) is completely seperate
			// from the controllers that maintain the model.
			// Without the graphics, the state of the game still exists (logically).
			doDrawGameScreen();

		}
		else if (sm.state == StateMachine::GAMEOVER) 
		{
			doDrawGameOverScreen();

			// Continue if fire key is pressed.
			pInterface->getKeyStatus(keys);

			if (keys.fire)
			{
				sm.state = StateMachine::RESET;
			}
			else if (keys.left) startShips = 1;
			else if (keys.right) startShips = 6;
		}
		else if (sm.state == StateMachine::RESET) 
		{
			// Free resources between games. 

			// Without reset(), the std::vector keeps its allocated memory from dynamic sizing.
			// That memory will still be needed to store objects,
			// but might as well free it for good practice.
			shipsCtrl.reset();
			enemiesCtrl.reset();
			rocketsCtrl.reset();
			bombsCtrl.reset();

			sm.state = StateMachine::INIT;
		}

	} // End of game loop.
	
	// Clean up.
	pPlayerSprite->destroy();
	pRocketSprite->destroy();
	pEnemySprite->destroy();
	pEnemy2Sprite->destroy();
	pBombSprite->destroy();
	pInterface->destroy();

	return 0;
}