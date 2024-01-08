#ifndef ASTEROID_H
#define ASTEROID_H

#include "ShapeGuy.h"

struct  Asteroid : ShapeGuy
{
	float spin = 0;
	//bool alive = false;
	Asteroid();
	Asteroid(float _r);
	//Asteroid(Vector2 _pos, Vector2 _vel, unsigned int _hp, float size);
	void update();
	void draw();
};

#endif // guard
