#ifndef THING_HEADER
#define THING_HEADER

#include "Mesh.h"
#include "Eigen/dense"
#include <stack>

class World; //Can't include World.h cus there's a circular dependency

class Thing {
	public:
		Thing(Mesh*);
		void draw();
		//Getter and setter functions
		void setWorld(World* w) { m_world = w; }
		void setColor(const Eigen::Vector4f& c) { m_color = c; }
		//Lots of functions to deal with transformations
		void rotateX(const double);
		void rotateY(const double);
		void rotateZ(const double);
		void translate(const Eigen::Vector3f&);
		void scale(const Eigen::Vector3f&);
		void scale(const double);
		void setIdentity();
		void pushMatrix();
		void popMatrix();
	protected:
		Mesh* m_mesh;
	private:
		Eigen::Affine3f m_transformation;
		std::stack<Eigen::Affine3f> m_transformation_stack;
		Eigen::Vector4f m_color;
		World* m_world;
};

#endif