// Jason Mottershead, 1300455.

// Category header file.
// This is not a class, but just a header file containing some information.
// The information provides what collisions should happen in the game.

// Header guard.
#ifndef _CATEGORY_H_
#define _CATEGORY_H_

enum Category
{

	playerCat =			0x0001,
	otherPlayerCat =	0x0002,
	enemyCat =			0x0003,
	ballCat =			0x0004,
	surfaceCat =		0x0005,
	netCat =			0x0006,

};

#endif