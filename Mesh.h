#ifndef MESH_HEADER
#define MESH_HEADER

#include <GLUT/glut.h>
#include "Eigen/dense"

#define DRAW_MESH 1
#define DRAW_PHONG 2
#define DRAW_TEXTURE 3

class Mesh {
	public:
		Mesh(GLuint, int, GLenum);
		void draw(const Eigen::Affine3f&, const Eigen::Vector4f&);
	private:
		GLuint m_vao;
		int m_num_vertices;
		GLenum m_draw_mode;
};

#endif