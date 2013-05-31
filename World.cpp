#include <GLUT/glut.h>

#include <vector>
#include "World.h"
#include "Thing.h"
#include "MeshMakers.h"
#include "Angel.h"
using namespace std;
using namespace Angel;

World::World() : mp_axes_mesh(NULL) {}

void World::linkProgram() {
	m_program = InitShader("vPhong.vert","fPhong.frag");
	glUseProgram(m_program);
}

void World::addThing(Thing* t) {
	/* Each Thing has a pointer to the world it's in. Set that, then push to
	m_things, which will actually make a copy of it. So gotta make all changes
	before that. */
	t->setWorld(this);
	m_things.push_back(t);
}

void World::drawAll() {
	for ( int i = 0; i < m_things.size(); i++ )
		m_things[i]->draw();
}

void World::drawAxes() {
	if (mp_axes_mesh == NULL ) //If this hasn't been created yet. Real janky, I know.
		mp_axes_mesh = makeAxesMesh();
	mp_axes_mesh->draw(identity(), vec4(1,1,1,1));//white; no transformations
}