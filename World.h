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
		void addThing(Thing*);
		void addBullet(Bullet*);
		void addWall(Wall*);
		void addCircle(Circle*);
		void add
		void drawAll();
		void drawAxes();
		void moveAll();
		//Getter functions
		GLuint getShaderz() { return m_program; }
		std::vector<Bullet*>* getBulletList() { return &m_bullets; }
		std::vector<Wall*>* getWallList() { return &m_walls; }
	private:
		Mesh* mp_axes_mesh;
		GLuint m_program;
		std::vector<Thing*> m_things;
		std::vector<Bullet*> m_bullets;
		std::vector<Wall*> m_walls;
		std::vector<Circle*> m_circles;
};

#endif
