//  Created by Jingyi Fang on 2/10/11.
// Adapted by [Our Team Name?] 5/2013
//  Copyright 2011 Jingyi Fang. All rights reserved.

#include "Camera.h"
#include "Light.h"
#include "MeshMakers.h"
#include "Mesh.h"
#include "Cube.h"
#include "Thing.h"
#include "Sphere.h"
#include "Wall.h"
#include "Circle.h"
#include "World.h"
#include "Angel.h"
#include "Bullet.h"
using namespace Angel;

// Constants ---------------------------------------------------------------------------------------
int g_window_width = 1200;
int g_window_height = 900;
const int GOURARD = 1;
const int PHONG = 2;
const int FLAT_SHADING = 3;
int g_draw_type = DRAW_PHONG;
const double DTIME = 0.0061;
double g_rotation;

// Global objects -----------------------------------------------------------------------------------
World g_timmy;
Camera g_pentax(70, g_window_width/g_window_height , 0.1, 800);
Light g_lumia;
Mesh* gp_cube_mesh, *gp_sphere_mesh, *gp_wall_mesh, *gp_circle_mesh;

void initGeometry() {
	/*I just call functions that assign vertices and normals to all the global
	Mesh objects. Pointers to these guys are used to provide all the geometry
	in one location for each of the various types of Things (cube, sphere, wall).*/
	gp_cube_mesh = makeCubeMesh();
    gp_sphere_mesh = makeSphereMesh(1);
    gp_wall_mesh = makeWallMesh();
    gp_circle_mesh = makeCircleMesh();
}

void initScene(){
    g_rotation = 0;  //Don't use this right now, but it'll be real handy once we have things rotating.
    
    g_lumia.setColor(vec4(1,1,1,1));
    g_lumia.setPosition(vec4(0,0,14,1)); //Let's try to keep the light at the camera ?
   
    //Set up the global drawer. BUT FIRST! We have to link the shaderz because otherwise
    //none of the InitDraws will work.
    g_timmy.linkProgram();
	
	initGeometry();
	
	Thing* im_a_sphere = new Sphere(vec4(-7,0,0,1), vec3(3.5, 3.5, 3.5));
	im_a_sphere->setColor(vec4(0,1,0,1));

	Thing* im_a_circle = new Circle(vec4(2,2,0,1), 1);
	im_a_circle->setColor(vec4(0,0,1,1));

	Thing* back_wall = new Wall(vec4(-1,-1,0,1), 36, 38);
	
	im_a_circle->attachTo(*back_wall);
	im_a_circle->scale(0.2); //A much smaller size is appropriate for a paint splatter.
	
	g_timmy.add(im_a_sphere);
	g_timmy.add(im_a_circle);
	g_timmy.add(back_wall);
}

void drawScene(){
    glEnable( GL_DEPTH_TEST );
    glClearColor(1,1,1,1);//Black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_timmy.stepAll(DTIME);
	g_pentax.update(DTIME);
	//Now tell the World object to draw all its Things.
	g_timmy.drawAll();
	g_timmy.drawAxes();
}

void keyboard(unsigned char key, int x, int y){

	switch(key){
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'r':
			g_pentax.resetView();
			break;
		//Now some cases for dealing with camera movement:
		case ' ':
			//bullets[iter] = new Bullet(-g_pentax.getPosition(), g_pentax.getTilt(), g_pentax.getYaw());
			//std::cout << x.x + " " + x.y + " " + x.z + "\n";
			g_timmy.add(new Bullet(-g_pentax.getPosition(), g_pentax.getTilt(), g_pentax.getYaw()));//(Thing*)bullets[iter++]);
			break;
		case 'j':
			g_pentax.moveLeft();
			break;
		case 'l':
			g_pentax.moveRight();
			break;
		case 'i':
			g_pentax.moveForward();
			break;
		case 'k':
			g_pentax.moveBackward();
			break;
		case 'w':
			g_pentax.moveUp();
			break;
		case 's':
			g_pentax.moveDown();
			break;
		case '1':
			g_draw_type = DRAW_MESH;
			break;
		case '2':
			g_draw_type = DRAW_PHONG;
			break;
	}
}

void specKeyboardCallback(int key, int x, int y){
	switch ( key ) {
		case GLUT_KEY_DOWN:
			g_pentax.tiltDown();
			break;
		case GLUT_KEY_UP:
			g_pentax.tiltUp();
			break;
		case GLUT_KEY_RIGHT:
			g_pentax.rotateLeft();
			break;
		case GLUT_KEY_LEFT:
			g_pentax.rotateRight();
			break;
	}
	glutPostRedisplay();
}

void displayCallback(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScene();
	glutSwapBuffers();
}

void reshapeCallback(int w, int h){
    g_window_width = w;
    g_window_height = h;
    
    glViewport(0, 0, w, h);
	g_pentax.setAspect((float)w/(float)h);
	glutPostRedisplay() ;
}

void idleCallback(){
	//g_rotation += DTIME*100;
	glutPostRedisplay(); //draw new frame
}


int main() {
    glutInit(new int(0), new char*); //These are never used.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(g_window_width,g_window_height);
    glutCreateWindow("Downtreading"); //Random title

	#ifndef __APPLE__ //Because Apple doesn't need GLEW and I can't #include it.
		glewExperimental = GL_TRUE;
		glewInit();
	#endif

    glutIdleFunc(idleCallback);
	glutReshapeFunc (reshapeCallback);

   glutKeyboardFunc(keyboard);
    glutSpecialFunc(specKeyboardCallback);
    glutDisplayFunc(displayCallback);

    initScene();
    glutMainLoop();

}