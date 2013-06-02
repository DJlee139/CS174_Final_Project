#ifndef WALL_HEADER
#define WALL_HEADER

#include "Thing2D.h"
#include "vec.h"

class Wall : public Thing2D {
	public:
		Wall();
		virtual void move();
		bool checkCollision(vec4);
};

#endif