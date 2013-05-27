#include "Cube.h"
#include "Mesh.h"

extern Mesh* gp_cube_mesh;

MyCube::MyCube() : Thing(gp_cube_mesh) {}