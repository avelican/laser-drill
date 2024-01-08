#include <raylib.h>
#include <raymath.h>

#include "Globals.h"
#include "Asteroid.h"
#include "VectorOverload.h"
#include "VectorOverload2.h"

#include <iostream>
//Asteroid::Asteroid(Vector2 _pos, Vector2 _vel, unsigned int _hp, float size)

#include <stdlib.h> // rand
#include <assert.h>

int rand_int(int min, int max) {
	if (max < min) {
		int tmp = min;
		min = max;
		max = min;
	}
	int range = max - min + 1; // note: +1 ensures output includes max
	return min + rand() % range; 
	// NOTE: rand() Returns a pseudo-random integer between 0 and RAND_MAX.

}


Asteroid::Asteroid()
	: ShapeGuy(0, Vector2{}, Vector2{}, 0) {
	alive = false;
}

Asteroid::Asteroid( float _r )
	: ShapeGuy(_r, Vector2{}, Vector2{}, 0) {
	alive = true;
	hp = (int)r;
	max_hp = hp;
	dmg = (int)r/2;
	color = Color{ 255, 128, 28, 255 };
	color = RAYWHITE; // icebergs

	float dim = (float)rand_int(80, 100) / 100;
	color.r *= dim;
	color.g *= dim;
	color.b *= dim;

	spin = ((float)(GetRandomValue(0, 10000) - 5000)) / 1000;
	// spin = 14;


	const float circly = .7f; // shove the corners inward, otherwise we get a square
	// I think the exact number is 1/sqrt(2) which is about 0.707, but this is close enough
	// as long as this number is less than or equal to the actual number, all points will be within the phase-1 collision circle
	// and therefore collision will be perfect.

	// // octagon
	//shape = {
	//	{0, r},
	//	{r * circly, r * circly},
	//	{r, 0},
	//	{r * circly, -r * circly},
	//	{0, -r},
	//	{-r * circly, -r * circly},
	//	{-r, 0},
	//	{-r * circly, r * circly},
	//};

	// // todo why is this broken?
	//for (int i = 0; i < 6; i++) {
	//	Vector2 p = {
	//		cos((2 * PI) / (float)i),
	//		sin((2 * PI) / (float)i),
	//	};
	//	shape.push_back(p);
	//}

	//shape = shape * r;

	// hexagon
	const float hexy = 0.2f;
	shape = {
		{0, r},
		{r * (circly + hexy), r * (circly - hexy)},
		{r * (circly + hexy), -r * (circly - hexy)},

		{0, -r},
		{-r * (circly + hexy), -r * (circly - hexy)},
		{-r * (circly + hexy), r * (circly - hexy)},
	};


	//float speed = ((float)rand_int(10, 150)) / 100; // TODO make random float function
	float speedf = ((float)rand_int(10, 60)) / 100; // TODO make random float function
	int speed = (int)(speedf*100); // gets normalized
	
	//int side = rand_int(0, 3);
	int side = rand_int(0, 3);
	// Note: some of these will float offscreen due to random direction. 
	// It's a very small percentage though 
	// (e.g. those at the top that spawn all the way to the left and then go left)
	switch (side) {
		case 0: { // bottom
			pos = {
				(float)rand_int(-r, GetScreenWidth() + r),
				GetScreenHeight() + r // move us radius distance over top of screen, to hide
			};
			vel = {
				(float)rand_int(-speed, speed),
				(float)rand_int(speed/10,-speed)
			};
			//vel = Vector2Normalize(vel) * speed;
		} break;

		case 1: { // top
			pos = {
				(float)rand_int(-r, GetScreenWidth() + r),
				0 - r // move us radius distance uner bottom of screen, to hide
			};
			vel = {
				(float)rand_int(-speed, speed),
				(float)rand_int(-speed/10, speed)
			};
			//vel = Vector2Normalize(vel) * speed;
		} break;

		case 2: { // left
			pos = {
				0 - r, // move us radius distance left of left edge of screen, to hide
				(float)rand_int(-r, GetScreenHeight() + r),
			};
			vel = {
				(float)rand_int(speed/10,speed),
				(float)rand_int(-speed, speed),
			};
			//vel = Vector2Normalize(vel) * speed;
		} break;

		case 3: { // right
			pos = {
				GetScreenWidth() + r, // move us radius distance right of right edge of screen, to hide
				(float)rand_int(-r, GetScreenHeight() + r),
			};
			vel = {
				(float)rand_int(-speed/10,-speed),
				(float)rand_int(-speed, speed),
			};
			//vel = Vector2Normalize(vel) * speed;
		} break;

		default: {
			//assert(side >= 0); // if our RNG is bunk
			//assert(side <= 3);
		} break;

	}

	vel = Vector2Normalize(vel) * speedf;


	//pos = Vector2 {
	//	(float)rand_int(10, SCREEN_WIDTH  - 10),
	//	(float)rand_int(10, SCREEN_HEIGHT - 10),
	//};

}

void Asteroid::update() {
	if (!alive) return;
	//const int TAU = PI * 2;
	//pos.y++;
	pos += vel;
	//angle += 0.05;
	angle += spin;

	const float GUIDE_SPEED = 0.001f;
	if (pos.y > GetScreenHeight() - r * 2)
		vel.y-= GUIDE_SPEED;
	// bottom
	if (pos.y < 0 + r * 2)
		vel.y+= GUIDE_SPEED;
	// right
	if (pos.x > GetScreenWidth() - r * 2)
		vel.x-= GUIDE_SPEED;
	// left
	if (pos.x < 0 + r * 2)
		vel.x+= GUIDE_SPEED;
}
void Asteroid::draw() {
	//DrawPoly(pos, 6, r+4, angle, BLACK);
	DrawPoly(pos, 6, r, angle, color);

}
