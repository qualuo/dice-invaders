#ifndef DICEINVADERSLIB_H
#define DICEINVADERSLIB_H
#include <windows.h> // winmain
#include <cassert> // assert
#include "DiceInvaders.h"

// Loads Dice Invaders library and provides an interface.
// Manages input, and drawing GUI and sprites.
class DiceInvadersLib
{
public:
	explicit DiceInvadersLib(const char* libraryPath);
	~DiceInvadersLib();
	IDiceInvaders* get() const { return m_interface; }

private:
	DiceInvadersLib(const DiceInvadersLib&);
	DiceInvadersLib& operator=(const DiceInvadersLib&);

private:
	IDiceInvaders* m_interface;
	HMODULE m_lib;
};

#endif