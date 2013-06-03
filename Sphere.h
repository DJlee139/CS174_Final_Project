#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include "Thing.h"

class Sphere : public Thing {
	public:
		Sphere();
		Sphere(const Angel::vec4&, const Angel::vec3&);
};

#endif