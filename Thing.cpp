#include "Thing.h"
#include "Angel.h"
#include "World.h"
using namespace Angel;

Thing::Thing(Mesh* m) : m_mesh(m), m_draw_whiteout(false) {
	//To build a thing, start by setting its transformation matrix to identity.
	m_transformation = identity();
	m_color = vec4(1,1,1,1); //Default color is white.
}

Thing::Thing(Mesh* m, const vec4& center, const vec3& t_scale) :
m_mesh(m), m_center(center), m_scale(t_scale), m_draw_whiteout(false) {
	m_transformation = identity();
	m_color = vec4(1,1,1,1);
	translate(m_center.first3());	
	scale(m_scale);
}

void Thing::draw() {
	m_mesh->draw(m_transformation, m_color, m_draw_whiteout);
}

void Thing::attachTo(Thing& other) {
	/* this function sounds super-sophisticated, but really it just sets the two Things' transformation
	matrices equal. This can be used for putting a Circle on a Wall or something like that.*/
	m_transformation = other.m_transformation;
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
	m_transformation = Translate(a_translation); //was *=
}

void Thing::scale(const vec3& a_scale){
	m_transformation *= Scale(a_scale);
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
