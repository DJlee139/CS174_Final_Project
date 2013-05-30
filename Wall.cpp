#include "Wall.h"
#include "Thing2D.h"
class Mesh;

extern Mesh* gp_wall_mesh;

Wall::Wall() : Thing2D(gp_wall_mesh) {}