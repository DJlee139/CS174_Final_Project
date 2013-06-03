#include "Wall.h"
#include "Thing.h"
#include "World.h"
#include "Bullet.h"
#include <vector>
using namespace std;
class Mesh;

extern Mesh* gp_wall_mesh;
extern World g_timmy;

Wall::Wall() : Thing(gp_wall_mesh) {}

Wall::Wall(vec4 center, double x_scale, double y_scale) :
Thing(gp_wall_mesh, center, vec3(x_scale, y_scale, 1)) {
	/* Thing has all the member variables Wall will need to set its boundary, so just pass them through
	to the Thing constructor. Just make sure we scale z by something other than 0, even though it's a 
	2D object. Otherwise it won't have color.*/
	setWallBoundary();
}

void Wall::setWallBoundary(){
	
	m_min.x = m_center.x - (m_scale.x/2);
	m_min.y = m_center.y - (m_scale.y/2);
	m_min.z = m_center.z -1;// - (m_scale/2);

	m_max.x = m_center.x + (m_scale.x/2);
	m_max.y = m_center.y + (m_scale.y/2);
	m_max.z = m_center.z+1;// + (m_scale/2);

}

bool Wall::checkBoundary(vec4 bcoord){
	return (bcoord.x <= m_max.x && bcoord.x >= m_min.x) &&
		(bcoord.y <= m_max.y && bcoord.y >= m_min.y) && 
		(bcoord.z <= m_max.z && bcoord.z >= m_min.z);
}

void Wall::step(double dtime) {
	/*The Wall's job is to check what Bullets might be colliding with it. So we iterate through the list of 
	all Bullets in the World and check to see if each one is within our bounding volume. If it is, we tell it
	to splash, giving it a pointer to us so it can attach to us.*/
	//TODO: See if the player/camera is colliding also; if so, die.
	vector<Bullet*>* p_bullets = g_timmy.getBulletList();
	size_t s = p_bullets->size();
	for ( size_t i = 0; i < s; i++ )
		if ( checkBoundary((*p_bullets)[i]->getCenter()) )
			(*p_bullets)[i]->splash(this);
}