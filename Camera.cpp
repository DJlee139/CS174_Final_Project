#include "Camera.h"
#include "Angel.h"
using namespace Angel;

Camera::Camera() {
	resetView();
}

void Camera::init(double fovy, double aspect, double near, double far) {
    m_fovy = fovy;
    m_aspect = aspect;
    m_znear = near;
    m_zfar = far;
	m_zoom = 1.00; //This is cool; maybe make use of it?
   //m_position = (S_XTRANS_DEFAULT, S_YTRANS_DEFAULT, S_ZTRANS_DEFAULT, 1.0);
}

void Camera::update(double dt) {
	//recompute the world to camera matrix in the camera
	m_cMw = RotateX(m_tilt)*RotateY(m_yaw)*Translate(m_xtrans, m_ytrans, m_ztrans);
	m_position = vec4(m_xtrans, m_ytrans, m_ztrans, 1.0); //will be updated everytime that the scene is about to be drawn
}

void Camera::resetView() {
	m_xtrans = S_XTRANS_DEFAULT;
	m_ytrans = S_YTRANS_DEFAULT;
	m_ztrans = S_ZTRANS_DEFAULT;
	m_tilt = S_TILT_DEFAULT;
	m_yaw = S_YAW_DEFAULT;
	m_camera_inc = S_CAMERA_INC_DEFAULT;
	m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);
}

void Camera::moveLeft() {
	m_xtrans += m_camera_inc*cos(m_yaw*M_PI/180);
	m_ztrans += m_camera_inc*sin(m_yaw*M_PI/180);
	//double t_x = m_xtrans- m_camera_inc*cos(m_yaw*M_PI/180);
	//double t_y = m_ytrans - m_camera_inc*sin(m_yaw*M_PI/180); 

m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);
}

void Camera::moveRight() {
	m_xtrans -= m_camera_inc*cos(m_yaw*M_PI/180);
    m_ztrans -= m_camera_inc*sin(m_yaw*M_PI/180);  

m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);		
 }
//TODO delete these functions eventually
void Camera::moveUp() { 
	m_ytrans -= m_camera_inc; 
	m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);
}


void Camera::moveDown() { 
	m_ytrans += m_camera_inc;
	m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);
 }

void Camera::moveForward() { 
	m_xtrans -= m_camera_inc*sin(m_yaw*M_PI/180);
    	m_ztrans += m_camera_inc*cos(m_yaw*M_PI/180);
	m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);
 }

void Camera::moveBackward() {
	m_xtrans += m_camera_inc*sin(m_yaw*M_PI/180);
	m_ztrans -= m_camera_inc*cos(m_yaw*M_PI/180);
	m_position = (m_xtrans, m_ytrans, m_ztrans, 1.0);
 }

void Camera::rotateLeft() { m_yaw += S_ROTATE_AMOUNT; }

void Camera::rotateRight() { m_yaw -= S_ROTATE_AMOUNT; }

void Camera::tiltUp() { m_tilt -= S_TILT_AMOUNT; }

void Camera::tiltDown() { m_tilt += S_TILT_AMOUNT; }
