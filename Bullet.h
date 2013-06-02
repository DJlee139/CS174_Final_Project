#ifndef BULLET_HEADER
#define BULLET_HEADER

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__
#include "Sphere.h"
#include "Angel.h"

class Wall;

class Bullet:  public Sphere {

public:

	Bullet(vec4 coord, double tilt, double yaw);
	virtual void step(double);
	vec4 getCoordinate();
	void splash(Wall*);

private:

	vec4 m_coord;
	double m_xdelta, m_ydelta, m_zdelta;
	double m_yaw, m_tilt;
	double m_velocity;
};

#endif
