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
	~Bullet();
	Bullet(vec4 coord, double tilt, double yaw);
	virtual void step(double);
	void splash(Wall*);

private:
	double m_xdelta, m_ydelta, m_zdelta;
	double m_yaw, m_tilt;
	double m_velocity;
	double m_ttl;
	static const double S_VELOCITY = 1.0;
	static const double S_TTL_DEFAULT = 10;

};

#endif
