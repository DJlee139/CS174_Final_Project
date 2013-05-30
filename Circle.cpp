#include "Circle.h"
#include "Thing2D.h"
class Mesh;

extern Mesh* gp_circle_mesh;

Circle::Circle() : Thing2D(gp_circle_mesh) {}