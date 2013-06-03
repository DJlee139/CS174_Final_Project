#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

#include "Thing.h"
#include "vec.h"

class Circle : public Thing {
	public:
		Circle();
		Circle(const Angel::vec4&, double);
};

#endif