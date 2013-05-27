#include "Thing.h"
#include "Eigen/dense"
#include "World.h"
using namespace Eigen;

Thing::Thing(Mesh* m) : m_mesh(m) {
	//To build a thing, start by setting its transformation matrix to identity.
	m_transformation.setIdentity();
	m_color = Vector4f(1,1,1,1); //Default color is white.
}

void Thing::draw() {
	m_mesh->draw(m_transformation, m_color);
}

//All the transformation functions

void Thing::rotateX(const double a_angle){
	m_transformation.rotate(AngleAxisf(a_angle*M_PI/180, Vector3f::UnitX()));
}

void Thing::rotateY(const double a_angle){
    m_transformation.rotate(AngleAxisf(a_angle*M_PI/180, Vector3f::UnitY()));

}

void Thing::rotateZ(const double a_angle){
	m_transformation.rotate(AngleAxisf(a_angle*M_PI/180, Vector3f::UnitZ()));
}

void Thing::translate(const Vector3f& a_translation){
	m_transformation.translate(a_translation);
}

void Thing::scale(const Vector3f& a_scale){
	m_transformation.scale(a_scale);
}

void Thing::scale(const double a_scale){
	m_transformation.scale(a_scale);
}
	
void Thing::setIdentity(){
	m_transformation.setIdentity();
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