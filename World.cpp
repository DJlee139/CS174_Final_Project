#include <GLUT/glut.h>
#include "Utility.h"
#include <vector>
#include "World.h"
#include "Thing.h"
using namespace std;

void World::linkProgram() {
	m_program = Util::InitShader("vPhong.vert","fPhong.frag");
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