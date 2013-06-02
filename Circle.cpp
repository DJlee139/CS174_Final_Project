#include "Circle.h"
#include "Thing.h"
class Mesh;

extern Mesh* gp_circle_mesh;

Circle::Circle() : Thing(gp_circle_mesh) {}