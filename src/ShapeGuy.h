#ifndef SHAPE_GUY_H
#define SHAPE_GUY_H
#include <raylib.h>
#include <vector>
#include <iostream>
struct  ShapeGuy
{
	bool alive = true;
	int dmg = 0; // how much damage this entity deals
	Vector2 pos = {0,0};
	Vector2 vel = {0,0};
	float r = 0; // radius. Should be set at shape creation time to dist(pos, "most_distant_point").
	float angle = 0;
	int hp = 0; // pro tip: do NOT make this unsigned... LOL
	int max_hp = 0;
	Color color = MAGENTA;
	std::vector<Vector2> shape;
	//ShapeGuy() {};
	ShapeGuy(float _r, Vector2 _pos, Vector2 _vel, unsigned int _hp);
	friend std::ostream& operator<<(std::ostream& os, const ShapeGuy& obj);
	virtual void update() = 0;
	void draw();
	void takeDamage(unsigned int dmg);
	void onDie();
	static void RotateShape(std::vector<Vector2> &shape, float angle);
	static void DrawShape(std::vector<Vector2> shape, Vector2 pos, Color color, float angle, float thickness);
	static bool Overlaps(ShapeGuy& a, ShapeGuy& b);
};

#endif // guard
