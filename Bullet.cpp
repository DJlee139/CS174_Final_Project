#include "Bullet.h"
#include "World.h"
#include "Circle.h"
using namespace Angel;

extern World g_timmy;

//  Degrees-to-radians constant 
//const GLfloat  cg_DEG2RAD = GLfloat(M_PI) / 180.0f;

const double cg_VELOCITY = 1.0;

Bullet::Bullet(vec4 coord, double tilt, double yaw) : m_coord(coord) {

	translate(m_coord.first3());	
	
	m_velocity = cg_VELOCITY;
	m_yaw = yaw;
	m_tilt = tilt;
	//set vector components

	m_xdelta = m_velocity * cos(m_tilt * DegreesToRadians1) * sin(m_yaw *DegreesToRadians1);
	m_ydelta = m_velocity * sin(m_tilt * DegreesToRadians1);
	m_zdelta = m_velocity * cos(m_tilt * DegreesToRadians1) * cos(m_yaw * DegreesToRadians1);
}


void Bullet::step(double dtime){
	m_coord.x += m_xdelta;//-
	m_coord.y -= m_ydelta;//+
	m_coord.z -= m_zdelta;//+
	translate(m_coord.first3());//use the method from grandparent class to change the matrix
	
	//TODO Also update its ttl so it can die if it's too old.
	//TODO maybe think about implementing gravity
}


//crash detection can  use getCoordinates and check for collision externally
//if crash detected, call splash()
vec4 Bullet::getCoordinate() { return m_coord; } 

void Bullet::splash(Wall* w) {
	g_timmy.removeBullet(this);
	Circle* p_splatter = new Circle;
	g_timmy.add(p_splatter);
	p_splatter->setColor(vec4(1,0,0,1));
	//Maybe try and see if just setting its coord will be good enough; kinda weird to attach
	p_splatter->translate(m_coord.first3());
//	p_splatter->attachTo((Thing2D&)(*w));
	//IF we attached to the Wall, would need to scale by 0.05
	delete this;
}