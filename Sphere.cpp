#include "Sphere.h"
#include "Mesh.h"

extern Mesh* gp_sphere_mesh;

Sphere::Sphere() : Thing(gp_sphere_mesh) {}