#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__

#include <vector>
#include "World.h"
#include "Thing.h"
#include "MeshMakers.h"
#include "Angel.h"
#include "Bullet.h"
#include "Wall.h"
#include "Circle.h"
using namespace Angel;
using namespace std;

World::World() : mp_axes_mesh(NULL) {}

void World::linkProgram() {
	m_program = InitShader("vPhong.vert","fPhong.frag");
	glUseProgram(m_program);
}

void World::add(Thing* t) {
	//TODO Maybe delete this if we stop having generic Things be in our scene.
	/* Each Thing has a pointer to the world it's in. Set that, then push to
	m_things, which will actually make a copy of it. So gotta make all changes
	before that. */
	t->setWorld(this);
	m_things.push_back(t);
}

void World::add(Bullet* b) {
	b->setWorld(this);
	m_bullets.push_back(b);
}

void World::add(Wall* w) {
	w->setWorld(this);
	m_walls.push_back(w);
}

void World::add(Circle* c) {
	c->setWorld(this);
	m_circles.push_back(c);
}

void World::removeBullet(Bullet* b) {
	//This janky line just removes all Bullet pointers equal to b from m_bullets
	for ( size_t i = 0; i < m_bullets.size(); i++ )
		if ( m_bullets[i] == b )
			m_bullets.erase(m_bullets.begin() + i );
}


void World::removeCircles(){
	//m_circles.erase(m_circles.begin(), m_circles.begin() + m_circles.size() );
	m_circles.clear();
}
void World::drawAll() {
	for ( int i = 0; i < m_bullets.size(); i++ )
		m_bullets[i]->draw();
	for ( int i = 0; i < m_walls.size(); i++ )
		m_walls[i]->draw();
	for ( int i = 0; i < m_circles.size(); i++ )
		m_circles[i]->draw();
	for(int i = 0; i < m_things.size(); i++)
		m_things[i]->draw();
}

void World::stepAll(double dtime){
	for ( int i = 0; i < m_bullets.size(); i++ )
		m_bullets[i]->step(dtime);
	for ( int i = 0; i < m_walls.size(); i++ )
		m_walls[i]->step(dtime);
	for ( int i = 0; i < m_circles.size(); i++ )
		m_circles[i]->step(dtime);
	for(int i = 0; i < m_things.size(); i++)
		m_things[i]->step(dtime);
}

void World::drawAxes() {
	if (mp_axes_mesh == NULL ) //If this hasn't been created yet. Real janky, I know.
		mp_axes_mesh = makeAxesMesh();
	mp_axes_mesh->draw(Angel::identity(), vec4(1,1,1,1), false);//white; no transformations
}
