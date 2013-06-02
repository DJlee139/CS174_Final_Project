#ifndef THING_HEADER
#define THING_HEADER

#include "Mesh.h"
#include "Angel.h"
#include <stack>

class World; //Can't include World.h cus there's a circular dependency

class Thing {
	public: 
		Thing(Mesh*);
		void draw();
		//Getter and setter functions
		void setWorld(World* w) { m_world = w; }
		void setColor(const Angel::vec4& c) { m_color = c; }
		//Lots of functions to deal with transformations
		void rotateX(const double);
		void rotateY(const double);
		void rotateZ(const double);
		void translate(const Angel::vec3&);
		void scale(const Angel::vec3&);
		void scale(const double);
		void setIdentity();
		void pushMatrix();
		void popMatrix();
		virtual void step(double dtime) {};//not everything will actually implement this
	protected:
		Mesh* m_mesh;
		Angel::mat4 m_transformation;
		World* m_world;
	private:
		std::stack<Angel::mat4> m_transformation_stack;
		vec4 m_color;
};

#endif
