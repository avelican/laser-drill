#ifndef PLAYER_H
#define PLAYER_H
#include "ShapeGuy.h"
struct  Player : ShapeGuy
{
	//bool alive = true;
	//float r = 14.14213562373f; // sqrt( 10^2 + 10^2 ) // could have made a base class method but eh
	// debug: large player
	//float r = 141.4213562373f; // sqrt( 10^2 + 10^2 ) // could have made a base class method but eh
	// update: yep ,shadowing again. shadowed the f***ing radius!

	// This wasn't being drawn. I think it's shadowing the base class's shape?
	// I'll move it to the constructor
	//std::vector<Vector2> shape = { {-10, -10},{0, -5}, {10, -10}, {0, 10} };
	//Color color = LIME;
	Player(Vector2 _pos, Vector2 _vel, unsigned int _hp);
	void update();
	void draw();
};

#endif // guard
