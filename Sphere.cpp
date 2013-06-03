#include "Sphere.h"
#include "Mesh.h"

extern Mesh* gp_sphere_mesh;

//These are just pass-through constructors
Sphere::Sphere() : Thing(gp_sphere_mesh) {}

Sphere::Sphere(const vec4& center, const vec3& scale) : Thing(gp_sphere_mesh, center, scale) {}