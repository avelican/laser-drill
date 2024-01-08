#include <raylib.h>
#include "Globals.h"
#include "Bullet.h"
#include <iostream>
//Asteroid::Asteroid(Vector2 _pos, Vector2 _vel, unsigned int _hp, float size)
#include "VectorOverload.h"
#include "VectorOverload2.h"

// for random
#include <stdlib.h>
#include <math.h>


Bullet::Bullet()
	: ShapeGuy(0, Vector2{}, Vector2{}, 0) {
	alive = false;

}


Bullet::Bullet( Vector2 _pos, float _angle )
	: ShapeGuy(BULLET_LENGTH/2, Vector2{}, Vector2{}, 0) {
	// TODO: move to initializers?
	color = Color{ 28, 128, 255, 255 };
	
	alive = true;
	hp = 1;
	max_hp = hp;
	// dmg = 30;
	dmg = 1;
	//hp = 1;
	pos = _pos;
	angle = _angle;
	//vel = {
	//	cos(angle + (PI * .5f)),
	//	sin(angle + (PI * .5f))
	//}; // already normalized
	vel = {
			sin(-angle),
			cos(angle)
	}; // already normalized

	//std::cout << "bullet spawn velocity: " << vel << "\n";
	vel *= (BULLET_LENGTH / 2); // bullet moves half its length per frame
	pos += vel;
	// shape.push_back({0,BULLET_LENGTH/2});
	// shape.push_back({ 0,-BULLET_LENGTH/2 });
	
	shape.push_back({0,BULLET_LENGTH/8});
	shape.push_back({ 0,-BULLET_LENGTH/8 });



	//std::cout << "\n  Constructed Bullet!\n";
	//std::cout << "bullet.alive: " << alive << "\n";
	//std::cout << "bullet.pos:   " << pos << "\n";
	//std::cout << "bullet.vel:   " << vel << "\n";
	//std::cout << "bullet.r:     " << r << "\n";
	//std::cout << "bullet.angle: " << angle << "\n";
	//std::cout << "bullet.hp:    " << hp << "\n";
	//std::cout << "bullet.shape: ";
	//for (int i = 0; i < shape.size(); i++) {
	//	std::cout << shape[i] << " ";
	//}
	//std::cout << "\n\n";

}
void Bullet::update() {
	//std::cout << "\nBullet::update()\n";
	//std::cout << "pos " << pos.x << "," << pos.y << "\n";
	//std::cout << "vel " << vel.x << "," << vel.y << "\n";
	//std::cout << "  r " << r << "\n";
	//std::cout << "////\n\n";
	if (!alive) return;
	//const int TAU = PI * 2;
	//angle += 0.05;
	//pos += vel * 0.1f; // debug
	pos += vel;
}
//void Asteroid::draw() {}
