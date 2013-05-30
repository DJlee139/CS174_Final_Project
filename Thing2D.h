#ifndef THING2D_HEADER
#define THING2D_HEADER

#include "Thing.h"
class Mesh;

class Thing2D : public Thing {
	public:
		Thing2D(Mesh*);
		void attachTo(Thing2D&);
};

#endif