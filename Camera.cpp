#include "Camera.h"
#include "Angel.h"
#include "World.h"
#include "Wall.h"
#include <iostream>
using namespace std;
using namespace Angel;

extern World g_timmy;


Camera::Camera(double fovy, double aspect, double znear, double zfar) :
m_fovy(fovy), m_aspect(aspect), m_znear(znear), m_zfar(zfar), m_zoom(1) {
	resetView();
}

void Camera::checkCollision(vec4 ccoord){
	vector<Wall*>* p_walls = g_timmy.getWallList();
	size_t s = p_walls->size();
	for ( size_t i = 0; i < s; i++ ){
		bool steve = (*p_walls)[i]->checkBoundary(-ccoord);
		
		if ( steve  ) {
			cout << "RESET"<<endl;
			g_timmy.removeCircles();
			resetView();
			
			break;
		}//end if
	}//end for loop
}



void Camera::update(double dt) {
	//recompute the world to camera matrix in the camera
	m_cMw = RotateX(m_tilt)*RotateY(m_yaw)*Translate(m_xtrans, m_ytrans, m_ztrans);
	m_position = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0); //will be updated everytime that the scene is about to be drawn
	//cout << m_position << endl;
}

void Camera::resetView() {
	m_xtrans = S_XTRANS_DEFAULT;
	m_ytrans = S_YTRANS_DEFAULT;
	m_ztrans = S_ZTRANS_DEFAULT;
	m_tilt = S_TILT_DEFAULT;
	m_yaw = S_YAW_DEFAULT;
	m_camera_inc = S_CAMERA_INC_DEFAULT;
	m_position = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0);
}

void Camera::moveLeft() {
	if ( m_xtrans <= 50.0 ) {
		m_xtrans += m_camera_inc*cos(m_yaw*M_PI/180);
		m_ztrans += m_camera_inc*sin(m_yaw*M_PI/180);
		vec4 temp = (m_xtrans, m_ytrans, m_ztrans, 1.0);
		checkCollision(temp);
	}
}

void Camera::moveRight() {
	if ( m_xtrans >= -50.0 ) {
		m_xtrans -= m_camera_inc*cos(m_yaw*M_PI/180);
    		m_ztrans -= m_camera_inc*sin(m_yaw*M_PI/180);  
		vec4 temp = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0);
		checkCollision(temp);
    }
 }


void Camera::moveUp() { 
if ( m_ytrans >= -50.0 ) 
	m_ytrans -= m_camera_inc; 
	vec4 temp = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0);
	checkCollision(temp);
}


void Camera::moveDown() { 
if ( m_ytrans <= 50.0 ) 
	m_ytrans += m_camera_inc;
	vec4 temp = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0);
	checkCollision(temp);
 }

void Camera::moveForward() { 
	m_xtrans -= m_camera_inc*sin(m_yaw*M_PI/180);
    	m_ztrans += m_camera_inc*cos(m_yaw*M_PI/180);

	vec4 temp = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0);
		checkCollision(temp);
 }

void Camera::moveBackward() {
	m_xtrans += m_camera_inc*sin(m_yaw*M_PI/180);
	m_ztrans -= m_camera_inc*cos(m_yaw*M_PI/180);

	vec4 temp = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0);
		checkCollision(temp);
 }

void Camera::rotateLeft() { m_yaw += S_ROTATE_AMOUNT; }

void Camera::rotateRight() { m_yaw -= S_ROTATE_AMOUNT; }

void Camera::tiltUp() { m_tilt -= S_TILT_AMOUNT; }

void Camera::tiltDown() { m_tilt += S_TILT_AMOUNT; }
