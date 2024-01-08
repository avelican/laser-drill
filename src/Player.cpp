#include <raylib.h>
#include <raymath.h>

#include "VectorOverload.h"
#include "VectorOverload2.h"

#include "Player.h"

#include <iostream>

#include <math.h>


Player::Player(Vector2 _pos, Vector2 _vel, unsigned int _hp) 
	: ShapeGuy(2*14.1421356, _pos, _vel, _hp) { // first arg is radius.. yeah i don't like it 
	//max_hp = _hp;
	shape = { 
		{-10, -10},
		{0, -5}, 
		{10, -10}, 
		{0, 10},
	};
	shape = shape * 2.f;
	//shape = { {-100, -100},{0, -50}, {100, -100}, {0, 100} };
	alive = true;
	//angle = PI;
	// color = Color{ 28, 128, 255, 255 }; // blue
	color = Color{ 255, 64, 28, 255 }; // reddish
	pos = {
		(float)GetScreenWidth()/2,
		(float)GetScreenHeight()/2
	};

}
void Player::update() {
	if(!alive) return;
	std::cout << "Player::update();\n";
	//const int TAU = PI * 2;
	//const int PI = 3.14159265359f;
	const int TAU = 6.28318530718f;
	const float ACCEL = 3.0f;
	//angle+= 0.05;
	//if (angle > PI)
	//	angle = 0;
	//std::cout << "player angle: " << angle << "\n";
	if (IsKeyDown(KEY_W)) {
		//vel.y++;
		// TODO: apply thrust along ship angle
		vel.x += cos(angle + PI/2) * ACCEL; // NOTE: TAU is one full rotation (2*PI)
		vel.y += sin(angle + PI/2) * ACCEL;

	}

	if (IsKeyDown(KEY_S)) {
		//vel.y--;
		// TODO: apply thrust along ship angle
		vel.x += cos(angle - PI/2) * ACCEL; // NOTE: PI is half of TAU, so opposite angle of forward thrust
		vel.y += sin(angle - PI/2) * ACCEL;
	}

	if (IsKeyDown(KEY_A)) {
		//vel.x--;
		angle -= 0.1f;
		//// TODO: apply STRAFE thrust PERPENDICULAR to ship angle
		//vel.x -= sin(angle * TAU + TAU*0.25) * ACCEL;
		//vel.y -= cos(angle * TAU + TAU*0.25) * ACCEL;
	}

	if (IsKeyDown(KEY_D)) {
		//vel.x++;
		angle += 0.1f;
		//// TODO: apply STRAFE thrust PERPENDICULAR to ship angle
		//vel.x -= sin(angle * TAU + TAU*0.75) * ACCEL;
		//vel.y -= cos(angle * TAU + TAU*0.75) * ACCEL;
	}



	pos += vel;
	const float f = 0.9;
	//const float f = 0; // debug
	vel *= f;
	if (Vector2Length(vel) > 5) {
		vel = Vector2Normalize(vel) * 5;
	}

	//////////////////////////////////////
	// push player away from edges
	// top
	if (pos.y > GetScreenHeight() - r * 2)
		vel.y--;
	// bottom
	if (pos.y < 0 + r * 2)
		vel.y++;
	// right
	if (pos.x > GetScreenWidth() - r * 2)
		vel.x--;
	// left
	if (pos.x < 0 + r * 2)
		vel.x++;

	//////////////////////////////////////////////
	// hard limits have proven to be necessary
	// top
	if (pos.y > GetScreenHeight() - r)
		pos.y = GetScreenHeight() - r;
	// bottom
	if (pos.y < r)
		pos.y = r;
	// right
	if (pos.x > GetScreenWidth() - r)
		pos.x = GetScreenWidth() - r;
	// left
	if (pos.x < 0 + r)
		pos.x = r;
}
void Player::draw() {
	if(!alive) return;
	std::cout << "Player::draw();\n";
	// Draw a color-filled triangle (vertex in counter-clockwise order!)
	// void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
	//for (int i = 0; i < shape.size(); i++) {

	//	Vector2 p1 = shape[i];
	//	Vector2 p2 = shape[(i + 1) % shape.size()]; // wrap around
	//	Vector2 p3 = shape[(i + 2) % shape.size()];

	//	p1 = Vector2Rotate(p1, angle);
	//	p2 = Vector2Rotate(p2, angle);
	//	p3 = Vector2Rotate(p3, angle);

	//	p1 += pos;
	//	p2 += pos;
	//	p3 += pos;

	//	//DrawTriangle(p1, p2, p3, color);
	//	DrawTriangle(p3, p2, p1, color); // it's actually clockwise?

	//	DrawPoly(p1, 6, 4, 0, MAGENTA);
	//	DrawPoly(p2, 6, 4, 0, MAGENTA);
	//	DrawPoly(p3, 6, 4, 0, MAGENTA);
	//}




	Vector2 p0 = shape[0];
	Vector2 p1 = shape[1];
	Vector2 p2 = shape[2];
	Vector2 p3 = shape[3];

	p0 = Vector2Rotate(p0, angle);
	p1 = Vector2Rotate(p1, angle);
	p2 = Vector2Rotate(p2, angle);
	p3 = Vector2Rotate(p3, angle);

	p0 += pos;
	p1 += pos;
	p2 += pos;
	p3 += pos;


	//DrawTriangle(p1, p2, p3, color);
	//DrawTriangle(p3, p0, p1, color);

	//DrawTriangle(p0, p2, p3, RED);
	DrawTriangle(p0, p3, p1, color);
	DrawTriangle(p3, p2, p1, color);



	// debug

	//DrawPoly(p0, 6, 4, 0, MAGENTA);
	//DrawPoly(p1, 6, 4, 0, MAGENTA);
	//DrawPoly(p2, 6, 4, 0, MAGENTA);
	//DrawPoly(p3, 6, 4, 0, MAGENTA);



	// health
	int max_hp = 100;
	// void DrawRectangleV(Vector2 position, Vector2 size, Color color);  
	int margin = GetScreenWidth() / 8;
	int maxWidth = GetScreenWidth() - margin*2;
	int width = maxWidth * ((float)hp/(float)max_hp);
	Vector2 pos = {
		(float)margin,
		(float)GetScreenHeight() - margin
	};
	Vector2 size = {
		(float)width,
		(float)GetScreenWidth() / 32
	};
	DrawRectangleV(pos, size, color);  

	
}
