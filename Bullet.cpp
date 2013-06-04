#include "Bullet.h"
#include "World.h"
#include "Circle.h"
using namespace Angel;

extern World g_timmy;

const double GRAVITY = 0.1;

//  Degrees-to-radians constant 
//const GLfloat  cg_DEG2RAD = GLfloat(M_PI) / 180.0f;

Bullet::	~Bullet() {
	g_timmy.removeBullet(this);
	//std::cout << "Destroying Bullet " << this << std::endl;
}

Bullet::Bullet(vec4 coord, double tilt, double yaw) :
//Center it at the coords we're passing in; 1 is a good size for Bullets.
Sphere(coord, 1), m_ttl(10), m_velocity(0.58)  {
	
	m_time = 0;
	m_yaw = yaw;
	m_tilt = tilt;
	//set vector components

	m_xdelta = m_velocity * cos(m_tilt * DegreesToRadians1) * sin(m_yaw *DegreesToRadians1);
	m_ydelta = m_velocity * sin(m_tilt * DegreesToRadians1);
	m_zdelta = m_velocity * cos(m_tilt * DegreesToRadians1) * cos(m_yaw * DegreesToRadians1);
}


void Bullet::step(double dtime){
	/* Now update the bullet's time alive based on the time interval that's being passed in.
	If it's too old, destroy it. Otherwise, move it, keeping gravity in mind. */
	m_time += dtime;
	if ( m_time > m_ttl )
		delete this; //~Bullet() will be called to clean up
		
	m_center.x += m_xdelta;//-
	m_center.y -= m_ydelta + m_time*2*GRAVITY;//+
	m_center.z -= m_zdelta;//+
	translate(m_center.first3());//use the method from grandparent class to change the matrix
}

//crash detection can  use Thing::getCenter and check for collision externally
//if crash detected, call splash()
void Bullet::splash(Wall* w) {
	//The paint splatter is a circle. Just create it at the exact location of the Bullet and make it bigger.
	Circle* p_splatter = new Circle(m_center, 3.3);
	g_timmy.add(p_splatter);
	p_splatter->setColor(vec4(0,0,0,1)); //Black
	//The bullet shall now be destroyed. See ~Bullet() for more details about this exciting new offer.
	delete this;
}
