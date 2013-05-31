#include "Thing.h"
#include "Angel.h"
#include "World.h"
using namespace Angel;

extern World g_timmy;

Thing::Thing(Mesh* m) : mp_mesh(m) {
	//To build a thing, start by setting its transformation matrix to identity.
	m_transformation = identity();
	m_color = vec4(1,1,1,1); //Default color is white.
}

void* Thing::operator new(size_t s) {
	//All Things automatically add themselves to the World
	void* p = malloc(s);
	g_timmy.addThing((Thing*)p);
	return p;
}

void Thing::draw() {
	mp_mesh->draw(m_transformation, m_color);
}

//All the transformation functions

void Thing::rotateX(const double a_angle){
	m_transformation *= RotateX(a_angle*M_PI/180);
}

void Thing::rotateY(const double a_angle){
    m_transformation *= RotateY(a_angle*M_PI/180);

}

void Thing::rotateZ(const double a_angle){
	m_transformation *= RotateZ(a_angle*M_PI/180);
}

void Thing::translate(const vec3& a_translation){
	m_transformation *= Translate(a_translation);
}

void Thing::scale(const vec3& a_scale){
	m_transformation *Scale(a_scale);
}

void Thing::scale(const double a_scale){
	m_transformation *= Scale(a_scale);
}
	
void Thing::setIdentity(){
	m_transformation = identity();
}

void Thing::pushMatrix(){
	m_transformation_stack.push(m_transformation);
}

void Thing::popMatrix(){
	if( !m_transformation_stack.empty() ){
		m_transformation = m_transformation_stack.top();
		m_transformation_stack.pop();
	}
}