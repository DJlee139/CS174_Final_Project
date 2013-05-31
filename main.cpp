//  Created by Jingyi Fang on 2/10/11.
// Adapted by [Our Team Name?] 5/2013
//  Copyright 2011 Jingyi Fang. All rights reserved.

#include "Camera_Eigen.h"
#include "Light.h"
#include "Timer.h"
#include "MeshMakers.h"
#include "Mesh.h"
#include "Cube.h"
#include "Thing.h"
#include "Thing2D.h"
#include "Sphere.h"
#include "Wall.h"
#include "Circle.h"
#include "World.h"
#include "Angel.h"
using namespace Angel;

// Constants ---------------------------------------------------------------------------------------
int g_window_width = 1200;
int g_window_height = 900;
const int GOURARD = 1;
const int PHONG = 2;
const int FLAT_SHADING = 3;
int g_draw_type = DRAW_PHONG;
double TIME;
double TIME_LAST;
double DTIME;
double FRAME_TIME = 0;
int FRAME_COUNT = 0;
double g_rotation;

// Global objects -----------------------------------------------------------------------------------
World g_timmy;
Camera g_pentax;
Light g_lumia;
Timer g_timer ;
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
    g_pentax.init(70, g_window_width/g_window_height , 0.1, 800); //znear, zfar
    g_pentax.setZoom(g_pentax.getZoom() * 0.25);
    g_rotation = 0;  //Don't use this right now, but it'll be real handy once we have things rotating.
    
    g_lumia.setColor(vec4(1,1,1,1));
    g_lumia.setPosition(vec4(0,0,14,1)); //Let's try to keep the light at the camera ?
   
    //Set up the global drawer. BUT FIRST! We have to link the shaderz because otherwise
    //none of the InitDraws will work.
    g_timmy.linkProgram();

    TIME_LAST = g_timer.getElapsedTime() ;
	DTIME = 0.0;
	FRAME_TIME = 0.0;

	
	initGeometry();
	
	Thing* im_a_sphere = new Sphere();
	im_a_sphere->setColor(vec4(0,1,0,1));
	im_a_sphere->translate(vec3(-7,0,0));
	im_a_sphere->scale(3.5);

	Thing2D* im_a_circle = new Circle();
	im_a_circle->setColor(vec4(0,0,1,1));
	im_a_circle->translate(vec3(2,2,0));

	Thing2D* back_wall = new Wall();
	back_wall->translate(vec3(-1,-1,0)); //Get it centered at the origin
	back_wall->scale(40); //Make it bigger!
	
	im_a_circle->attachTo(*back_wall);
	im_a_circle->scale(0.2); //A much smaller size is appropriate for a paint splatter.
	
	g_timmy.addThing(im_a_sphere);
	g_timmy.addThing((Thing*)im_a_circle);
	g_timmy.addThing((Thing*)back_wall);
}

void drawScene(){
   
    glEnable( GL_DEPTH_TEST );
    glClearColor(0.0, 0.0, 0.0, 0.0);//Black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	g_pentax.update(DTIME);
	
	//Now tell the World object to draw all its Things.
	g_timmy.drawAll();
	g_timmy.drawAxes();
}

void keyboardCallback(int key, int x, int y){
	/* This is a key callback function that accepts the key as an int. You might think most
	keys are chars, but we want this to be both a keyboard callback and a special
	callback..... and it turns out that for ASCII keys, int is the same as char! */
	switch ( key ) {
		case 'q':
		case 'Q':
			exit(0);
			break;
		/*case 'c':
			g_color_offset++;
			break;*/
		case 'r':
			g_pentax.resetView();
			break;
		//Now some cases for dealing with camera movement:
		case 'j':
			g_pentax.moveLeft();
			break;
		case 'k':
			g_pentax.moveRight();
			break;
		case 'i':
			g_pentax.moveForward();
			break;
		case 'm':
			g_pentax.moveBackward();
			break;
		case GLUT_KEY_DOWN:
			g_pentax.moveDown();
			break;
		case GLUT_KEY_UP:
			g_pentax.moveUp();
			break;
		case GLUT_KEY_RIGHT:
			g_pentax.rotateRight();
			break;
		case GLUT_KEY_LEFT:
			g_pentax.rotateLeft();
			break;
		case 'w':
			g_pentax.tiltUp();
			break;
		case 's':
			g_pentax.tiltDown();
			break;
		case '1':
			g_draw_type = DRAW_MESH;
			break;
		case '2':
			g_draw_type = DRAW_PHONG;
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
    
	TIME = g_timer.getElapsedTime() ;
    
	DTIME = TIME - TIME_LAST;
	TIME_LAST = TIME;

    g_rotation += DTIME*100;

    //std::cout<<"Frame Rate"<<FRAME_COUNT/TIME<<"\r";
	glutPostRedisplay(); //draw new frame
	FRAME_COUNT++;
}


int main() {
    glutInit(new int(0), new char*); //These are never used.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(g_window_width,g_window_height);
    glutCreateWindow("Downtreading"); //Random title
    glutIdleFunc(idleCallback);
	glutReshapeFunc (reshapeCallback);
   /* Turns out you don't need a keyboardFunc if the special Func handles normal keys */
    glutSpecialFunc(keyboardCallback);
    glutDisplayFunc(displayCallback);

    initScene();
    glutMainLoop();

}


