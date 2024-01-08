#ifndef BULLET_H
#define BULLET_H

#include "ShapeGuy.h"

#define BULLET_LENGTH 40

struct  Bullet : ShapeGuy
{
	//bool alive = false;
	Bullet();
	Bullet(Vector2 _pos, float _angle);
	//Asteroid(Vector2 _pos, Vector2 _vel, unsigned int _hp, float size);
	void update();
	//void draw();
};

#endif // guard
