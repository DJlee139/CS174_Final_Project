#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

#include "Thing.h"
#include "vec.h"

class Circle : public Thing {
	public:
		Circle();
		Circle(const Angel::vec4&, double);
		virtual void draw(); //This is because splatters need to grab min and max values from attached Wall
};

#endif