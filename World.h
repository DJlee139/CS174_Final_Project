#ifndef WORLD_HEADER
#define WORLD_HEADER

#include <vector>
#include <GLUT/glut.h>

#include "Thing.h"

class World {
	public:
		void linkProgram();
		void addThing(Thing*);
		void drawAll();
		//Getter functions
		GLuint getShaderz() { return m_program; }
	private:
		GLuint m_program;
		std::vector<Thing*> m_things;
};

#endif