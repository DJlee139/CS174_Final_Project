#include "Thing2D.h"
class Mesh;

Thing2D::Thing2D(Mesh* m) : Thing(m) {} //Just sort of a pass-through constructor

void Thing2D::attachTo(Thing2D& other) {
	/* this function sounds super-sophisticated, but really it just sets the two Things' transformation
	matrices equal. This can be used for putting a Circle on a Wall or something like that.*/
	//TODO: Make it able to attach to the (flat) surface of a 3D object.
	m_transformation = other.m_transformation;
}