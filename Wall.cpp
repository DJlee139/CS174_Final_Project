#include "Wall.h"
#include "Thing2D.h"
#include "World.h"
#include "Bullet.h"
#include <vector>
using namespace std;
class Mesh;

extern Mesh* gp_wall_mesh;
extern World g_timmy;

Wall::Wall() : Thing2D(gp_wall_mesh) {}

void Wall::step(double dtime) {
	/*The Wall's job is to check what Bullets might be colliding with it. So we iterate through the list of 
	all Bullets in the World and check to see if each one is within our bounding volume. If it is, we tell it
	to splash, giving it a pointer to us so it can attach to us.*/
	//TODO: See if the player/camera is colliding also; if so, die.
	vector<Bullet*>* p_bullets = g_timmy.getBulletList();
	for ( size_t i = 0; i < p_bullets->size(); i++ )
		if ( checkCollision((*p_bullets)[i]->getCoordinate()) )
			(*p_bullets)[i]->splash(this);
}

bool Wall::checkCollision(vec4 c) {
	//TEMP function until Anvay gets his awesome one in here.
	return c.z > -1.0 && c.z < 1.0;
}