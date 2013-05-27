#include "Sphere.h"
#include "Mesh.h"

extern Mesh* gp_sphere_mesh;

MySphere::MySphere() : Thing(gp_sphere_mesh) {}