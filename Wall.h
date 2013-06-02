#ifndef WALL_HEADER
#define WALL_HEADER

#include "Thing.h"
#include "Bullet.h"
class Wall : public Thing {
	public:
		Wall();
		Wall(Angel::vec4, double);
		void setWallBoundary();
		virtual void step(double);
		bool checkBoundary(Angel::vec4);//false if NO splash needed, TRUE if splash needed
		bool checkCollision(Angel::vec4);

	private:
		Angel::vec4 m_center;
		double m_scale;
		Angel::vec4 m_min;
		Angel::vec4 m_max;
};

#endif
