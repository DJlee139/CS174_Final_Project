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

Wall::Wall(vec4 center, double t_scale) : Thing(gp_wall_mesh, center, t_scale) {

	translate(center.first3());
	scale(vec3(t_scale, t_scale, 1));
	setWallBoundary();
}

void Wall::setWallBoundary(){
	
	m_min.x = m_center.x - (m_scale/2);
	m_min.y = m_center.y - (m_scale/2);
	m_min.z = m_center.z -1;// - (m_scale/2);

	m_max.x = m_center.x + (m_scale/2);
	m_max.y = m_center.y + (m_scale/2);
	m_max.z = m_center.z+1;// + (m_scale/2);

}

bool Wall::checkBoundary(vec4 bullet_coord){

	vec3 bcoord;
	bcoord.x = bullet_coord.x;
	bcoord.y = bullet_coord.y;
	bcoord.z = bullet_coord.z;
	
	if(bcoord.x <= m_max.x && bcoord.x >= m_min.x){
		if(bcoord.y <= m_max.y && bcoord.y >= m_min.y){
			if(bcoord.z <= m_max.z && bcoord.z >= m_min.z){
				return true;//true = splash the bullet!
			}
			else return false;
		}
		else return false;
	}
	else
		return false;
}

void Wall::step(double dtime) {
	/*The Wall's job is to check what Bullets might be colliding with it. So we iterate through the list of 
	all Bullets in the World and check to see if each one is within our bounding volume. If it is, we tell it
	to splash, giving it a pointer to us so it can attach to us.*/
	//TODO: See if the player/camera is colliding also; if so, die.
	vector<Bullet*>* p_bullets = g_timmy.getBulletList();
	size_t s = p_bullets->size();
	for ( size_t i = 0; i < s; i++ )
		if ( checkCollision((*p_bullets)[i]->getCoordinate()) )
			(*p_bullets)[i]->splash(this);
}

bool Wall::checkCollision(vec4 c) {
	//TEMP function until Anvay gets his awesome one in here.
	return c.z > -1.0 && c.z < 1.0;
}