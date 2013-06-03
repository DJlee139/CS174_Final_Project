#include "Mesh.h"
#include "World.h"
#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__
#include "Angel.h"
#include "Camera.h"
#include "Light.h"

using namespace Angel;

extern World g_timmy;
extern Camera g_pentax;
extern Light g_lumia;
extern int g_draw_type;

Mesh::Mesh(GLuint vao, int num_vertices, GLenum draw_mode) :
	m_vao(vao), m_num_vertices(num_vertices), m_draw_mode(draw_mode) {}

void Mesh::draw() {
	draw(Angel::identity(), vec4(1,1,1,1), false);
}

void Mesh::draw(const mat4& wMo, const vec4& l_color, bool white_out) {

    mat4 cMw;
    mat4 proj;

    glBindVertexArrayAPPLE(m_vao);

	//Get the locations of all the shader uniforms ready so we can use them later
	GLuint camera_position = glGetUniformLocation(g_timmy.getShaderz(), "cameraPosition");
    GLuint light_position = glGetUniformLocation(g_timmy.getShaderz(), "lightPosition");
	GLuint color = glGetUniformLocation(g_timmy.getShaderz(), "Color");
    GLuint object2world = glGetUniformLocation(g_timmy.getShaderz(), "wMo");
    GLuint world2camera = glGetUniformLocation(g_timmy.getShaderz(), "cMw"); 
	GLuint projection = glGetUniformLocation(g_timmy.getShaderz(), "proj");
	GLuint specular_highlights = glGetUniformLocation(g_timmy.getShaderz(), "specularHighlights");
	GLuint white_out_uniform = glGetUniformLocation(g_timmy.getShaderz(), "whiteOut");

    //This is Angel::Perspective, which is found in mat.h; not Util::Perspective. It's the same.
    proj = Perspective( g_pentax.getFovy(), g_pentax.getAspect(), g_pentax.getZnear(), g_pentax.getZfar() );
    
	cMw = g_pentax.getModelview();
 
    glUniformMatrix4fv( object2world , 1, true, wMo );
    glUniformMatrix4fv( world2camera, 1, true, cMw);
    glUniform1i(specular_highlights, false); //We really don't want this stuff to be shiny.
	glUniform1i(white_out_uniform, white_out); //To make walls invisible and bullets, etc look 3D
    glUniformMatrix4fv( projection, 1, true, proj);
	glUniform4fv(camera_position, 1, g_pentax.getPosition());
    glUniform4fv(light_position, 1, g_lumia.getPosition());
  	glUniform4fv(color,1,l_color);
	
	switch (g_draw_type) {
        case DRAW_MESH:
            glDrawArrays(GL_LINES, 0, m_num_vertices);
            break;
        case DRAW_PHONG:
            glDrawArrays(m_draw_mode, 0, m_num_vertices);
            break;
    }
}
