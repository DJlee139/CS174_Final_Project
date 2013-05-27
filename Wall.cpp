#include "Wall.h"
#include "Mesh.h"

extern Mesh* gp_wall_mesh;

Wall::Wall() : Thing(gp_wall_mesh) {}