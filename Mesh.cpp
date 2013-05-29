#include "Mesh.h"
#include "World.h"
#include <GLUT/glut.h>
#include "Eigen/dense"
#include "Camera_Eigen.h"
#include "Light.h"
#include "Utility.h"
using namespace Eigen;

extern World g_timmy;
extern Camera g_pentax;
extern Light g_lumia;
extern int g_draw_type;

Mesh::Mesh(GLuint vao, int num_vertices, GLenum draw_mode) :
	m_vao(vao), m_num_vertices(num_vertices), m_draw_mode(draw_mode) {}

void Mesh::draw(const Affine3f& wMo, const Vector4f& l_color) {

    Affine3f cMw;
    Affine3f proj;

    glBindVertexArrayAPPLE(m_vao);

	GLuint camera_position = glGetUniformLocation(g_timmy.getShaderz(), "cameraPosition");
    GLuint light_position = glGetUniformLocation(g_timmy.getShaderz(), "lightPosition");
	GLuint color = glGetUniformLocation(g_timmy.getShaderz(), "Color");
    GLuint object2world = glGetUniformLocation(g_timmy.getShaderz(), "wMo");
    GLuint world2camera = glGetUniformLocation(g_timmy.getShaderz(), "cMw"); 
	GLuint projection = glGetUniformLocation(g_timmy.getShaderz(), "proj");

    //wMo.setIdentity(); //No transformations for a plain mesh
    proj = Util::Perspective( g_pentax.getFovy(), g_pentax.getAspect(), g_pentax.getZnear(), g_pentax.getZfar() );
	cMw = g_pentax.getProjection();
 
    glUniformMatrix4fv( object2world , 1, false, wMo.data() );
    glUniformMatrix4fv( world2camera, 1, false, cMw.data());
    glUniformMatrix4fv( projection, 1, false, proj.data());
	glUniform4fv(camera_position, 1, g_pentax.getPosition().data());
    glUniform4fv(light_position, 1, g_lumia.getPosition().data());
  	glUniform4fv(color,1,l_color.data());
	
	switch (g_draw_type) {
        case DRAW_MESH:
            glDrawArrays(GL_LINES, 0, m_num_vertices);
            break;
        case DRAW_PHONG:
            glDrawArrays(m_draw_mode, 0, m_num_vertices);
            break;
    }
}