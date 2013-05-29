#ifndef WORLD_HEADER
#define WORLD_HEADER

#include <vector>
#include <GLUT/glut.h>

#include "Thing.h"
class Mesh;

class World {
	public:
		World(); //Only needed to set a pointer to NULL.
		void linkProgram();
		void addThing(Thing*);
		void drawAll();
		void drawAxes();
		//Getter functions
		GLuint getShaderz() { return m_program; }
	private:
		Mesh* mp_axes_mesh;
		GLuint m_program;
		std::vector<Thing*> m_things;
};

#endif