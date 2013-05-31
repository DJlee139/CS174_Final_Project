#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "Timer.h"
#include "Drawer.h"
#include "Mesh.h"

//Global Variables
int Window_Width = 1200;
int Window_Height = 900;

const int GOURARD = 1;
const int PHONG = 2;
const int FLAT_SHADING = 3;

Camera Pentax;
Light Lumia;
Drawer* myDrawer = NULL;

int DRAW_TYPE = DRAW_PHONG;

Timer TM ;
double TIME;
double TIME_LAST;
double DTIME;
double FRAME_TIME = 0;
int FRAME_COUNT = 0;

bool drawFlag = true;

void initScene();
void drawScene();
void keyboardCallback(unsigned char key, int x, int y);
void specialCallback(int key, int x, int y);
void displayCallback();
void reshapeCallback(int w, int h);
void idleCallback();
void writeBestGenome();
