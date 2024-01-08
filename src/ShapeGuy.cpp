#include <raylib.h>
#include <raymath.h>
#include "VectorOverload.h"
#include "VectorOverload2.h"

#include "ShapeGuy.h"

#include <iostream> // dbg

#include <assert.h>

ShapeGuy::ShapeGuy(float _r, Vector2 _pos, Vector2 _vel, unsigned int _hp) : r(_r), pos(_pos), vel(_vel), hp(_hp) {}
//void ShapeGuy::update() = 0;
void ShapeGuy::draw() 
{	
	if ( ! alive ) return;
	//std::cout << "ShapeGuy::draw()" << "\n";
	//std::cout << "shape.size(): " << shape.size()  << "\n";
	//std::cout << "position: " << pos.x << " " << pos.y << "\n";

	//DrawShape(shape, pos, BLACK, angle, 12.f);
	DrawShape(shape, pos, color, angle, 4.f);
	// for debug: show circle colliders
	//DrawCircleLinesV(pos, r, PURPLE);

}

/*
	bool alive = true;
	Vector2 pos = {0,0};
	Vector2 vel = {0,0};
	float r = 0; // radius. Should be set at shape creation time to dist(pos, "most_distant_point").
	float angle = 0;
	unsigned int hp = 0;
	Color color = LIME;
	std::vector<Vector2> shape;
*/

std::ostream& operator<<(std::ostream& os, const ShapeGuy& sg) {
	// TODO FIXME Why doesn't this work? I just get a memory address
	os << "ShapeGuy.alive: " << sg.alive  << "\n";
	os << "ShapeGuy.pos:   " << sg.pos    << "\n";
	os << "ShapeGuy.vel:   " << sg.vel    << "\n";
	os << "ShapeGuy.r:     " << sg.r      << "\n";
	os << "ShapeGuy.angle: " << sg.angle  << "\n";
	os << "ShapeGuy.hp:    " << sg.hp     << "\n";
	//os << "ShapeGuy.shape; " << sg.shape  << "\n";

	return os;
}

void ShapeGuy::takeDamage(unsigned int _dmg)
{
	//std::cout << "ShapeGuy::takeDamage(" << dmg << ");\n";
	//std::cout << "ShapeGuy::takeDamage: health was: " << hp << "\n";
	hp -= _dmg;
	//std::cout << "ShapeGuy::takeDamage: health is: " << hp << "\n\n";
	if (hp <= 0) {
		alive = false;
		onDie();
	}
}

void ShapeGuy::onDie() {}


inline void ShapeGuy::RotateShape(std::vector<Vector2> &shape, float angle) {
	for (size_t i = 0; i < shape.size(); i++) {
		shape[i] = Vector2Rotate(shape[i], angle);
	}
}

void ShapeGuy::DrawShape(std::vector<Vector2> shape, Vector2 pos, Color color, float angle, float thickness) {
	// so apparently when you pass a std::vector to a function,
	// it creates a new vector and copies all the data.
	// ( hence the &reference )
	// Edit: we need to rotate it anyway, so let's just make a copy.
	
	ShapeGuy::RotateShape(shape, angle);

	// was bottlenecking cpu perf
	size_t lastIndex = shape.size() - 1;
	for (size_t i = 0; i < shape.size(); i++) {
		Vector2 start;
		Vector2 end;
		if (i == lastIndex) {
			start = shape[i];
			end = shape[0]; // close the shape
		}
		else {
			start = shape[i];
			end = shape[i + 1];
		}
		//float thickness = 1.f;
		//float thickness = 3.f;

		// NOTE(andai): rendering offset by position
		//DrawLineEx(start + pos, end + pos, thickness, color);
		//std::cout << "start:" << start.x << " " << start.y << "\n";
		//std::cout << "  end:" <<   end.x << " " <<   end.y << "\n";

		DrawLineEx(start + pos, end + pos, thickness, color);

	}


	// // render with opengl lines instead
	//std::vector<Vector2> shape_render = shape;
	//shape_render += pos;
	//DrawLineStrip(shape_render.data(), shape_render.size(), color);
}

bool ShapeGuy::Overlaps(ShapeGuy& a, ShapeGuy& b) {
	assert(a.alive);
	assert(b.alive);
	bool overlapped = false;
	if (Vector2Distance(a.pos, b.pos) < (a.r + b.r)) {
		//return true;
		// TODO: more sophisticated collision pls
		// EDIT: Apparently there exists CheckCollisionLines()
		// Thanks Ray :)

		// NOTE: this will fail if we have a sharp polygon and movement causes one of its points to
		// "skip" the other polygon. Then the edges overlap but there are no points inside each other.
		// If that becomes an issue, we'll have to add a call to
		// CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint);
		// as well.
		
		//return true;

		// first, offset the shapes by each entity's position
		std::vector<Vector2> shape_a = a.shape;
		std::vector<Vector2> shape_b = b.shape;
		ShapeGuy::RotateShape(shape_a, a.angle); 
		ShapeGuy::RotateShape(shape_b, b.angle);
		shape_a += a.pos;
		shape_b += b.pos;
		//shape_a += Vector2{ 4,4 }; // offset for debug, to make sure it's not overlapping actual render
		//shape_b += Vector2{ 4,4 }; // offset for debug, to make sure it's not overlapping actual render

		

		// debug lines for my sanity
		//const Color cyan = { 0,255,255, 255 };
		//DrawShape(shape_a, Vector2{ 0,0 }, cyan);
		//DrawShape(shape_b, Vector2{ 0,0 }, cyan);
		//std::vector<Vector2> tmp = { Vector2{0,0}, Vector2{200, 100}, Vector2{100, 200} };
		//DrawShape(tmp, Vector2{ 0,0 }, BLUE);

		//Well, I don't know what's wrong with CheckCollisionPointPoly()
		// (or how I'm using it )
		// but it's doing some very strange things.
		//for (int i = 0; i < shape_a.size(); i++) {
		//	//CheckCollisionPointPoly(Vector2 point, Vector2 * points, int pointCount);
		//	if (CheckCollisionPointPoly(shape_a[i], shape_b.data(), shape_b.size())) {
		//		overlapped = true;
		//	}
		//}
		
		size_t lastIndex_a = shape_a.size() - 1;
		for (size_t i = 0; i < shape_a.size(); i++) {
			Vector2 start_a;
			Vector2 end_a;
			if (i == lastIndex_a) {
				start_a = shape_a[i];
				end_a = shape_a[0]; // close the shape
			}
			else {
				start_a = shape_a[i];
				end_a = shape_a[i + 1];
			}

			// now iterate over the line segments in shape b

			size_t lastIndex_b = shape_b.size() - 1;
			for (size_t i = 0; i < shape_b.size(); i++) {
				Vector2 start_b;
				Vector2 end_b;
				if (i == lastIndex_b) {
					start_b = shape_b[i];
					end_b = shape_b[0]; // close the shape
				}
				else {
					start_b = shape_b[i];
					end_b = shape_b[i + 1];
				}

				// Now the actual fun part
				Vector2 dummy;
				if (CheckCollisionLines(start_a, end_a, start_b, end_b, &dummy)) {
					overlapped = true;
				}

			}
		}
	}
	return overlapped;
}