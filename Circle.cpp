#include "Circle.h"
#include "Thing.h"
class Mesh;
using namespace Angel;

extern Mesh* gp_circle_mesh;

Circle::Circle() : Thing(gp_circle_mesh) {}

//Circles, by definition, are circular, so there can really only be one scale factor (for both x and y)
Circle::Circle(const vec4& center, double scale) : Thing(gp_circle_mesh, center, vec3(scale, scale, 1)) {}