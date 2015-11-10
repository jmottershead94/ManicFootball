// Jason Mottershead, 1300455.

// Category header file.
// This is not a class, but just a header file containing some information.
// The information provides what collisions should happen in the game.

// Header guard.
#ifndef _CATEGORY_H_
#define _CATEGORY_H_

enum Category
{

	player =		0x0001,
	otherPlayer =	0x0002,
	enemy =			0x0003,
	ball =			0x0004,
	surface =		0x0005,
	net =			0x0006,

};

#endif