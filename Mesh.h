#ifndef MESH_HEADER
#define MESH_HEADER

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__
#include "Angel.h"
#include <float.h>

#define DRAW_MESH 1
#define DRAW_PHONG 2
#define DRAW_TEXTURE 3

class Mesh {
	public:
		Mesh(GLuint, int, GLenum);
		//This function has all default parameters. When calling, gotta add from left to right.
		void draw(const Angel::mat4& = Angel::identity(), const Angel::vec4& = Angel::vec4(1,1,1,1),
			bool = false, vec4 = vec4(-100000), vec4 = vec4(100000));
	private:
		GLuint m_vao;
		int m_num_vertices;
		GLenum m_draw_mode;
};

#endif
