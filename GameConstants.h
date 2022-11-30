#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

namespace GameConstants
{
	// Target frames per second.
	const float TARGET_FPS = 120.0f;
	const float SEC_PER_FRAME = 1.0f / TARGET_FPS;

	// Window size
	const int WINDOW_WIDTH = 640; // 640
	const int WINDOW_HEIGHT = 480; // 480

	// Grid size for offsets
	const int CELL_WIDTH = 42; //  42
	const int CELL_HEIGHT = 30; // 30

	// Text y-offset
	const int TEXT_OFFSET1 = 10;
	const int TEXT_OFFSET2 = 25;
	const int ENEMY_Y_OFFSET = WINDOW_HEIGHT / 11; // Enemy y-offset, to keep away from text.


	// Following could be variables.

	const int ENEMY_ROWS = 5; // 5
	const int ENEMY_COLUMNS = 11; // 11

	const int BOMBS_LIMIT = 12;
	const float BOMB_COOLDOWN = 0.5f;


}

#endif