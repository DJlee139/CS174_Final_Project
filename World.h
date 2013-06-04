#ifndef WORLD_HEADER
#define WORLD_HEADER

#include <vector>
#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__

#include "Thing.h"
class Bullet;
class Wall;
class Circle;
class Mesh;

class World {
	public:
		World(); //Only needed to set a pointer to NULL.
		void linkProgram();
		void add(Thing*);
		void add(Bullet*);
		void add(Wall*);
		void add(Circle*);
		void removeBullet(Bullet*);
		void drawAll();
		void drawAxes();
		void stepAll(double);
		//Getter functions
		GLuint getShaderz() { return m_program; }
		std::vector<Bullet*>* getBulletList() { return &m_bullets; }
		std::vector<Wall*>* getWallList() { return &m_walls; }
		void removeCircles();
		//std::vector<Circle*>* getCircleList(){ return &m_circles; }
	private:
		Mesh* mp_axes_mesh;
		GLuint m_program;
		std::vector<Thing*> m_things;
		std::vector<Bullet*> m_bullets;
		std::vector<Wall*> m_walls;
		std::vector<Circle*> m_circles;
};

#endif
