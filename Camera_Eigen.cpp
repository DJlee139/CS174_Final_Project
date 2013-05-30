#include "Camera_Eigen.h"
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
}

void Camera::update(double dt) {
	//recompute the world to camera matrix in the camera
	m_cMw  = Translate(vec3(m_xtrans,m_ytrans,m_ztrans-10));
	m_cMw *= Scale(m_zoom);
	m_cMw *= RotateX(m_altitude);
	m_cMw *= RotateY(m_azimuth);

}

void Camera::resetView() {
	m_xtrans = S_XTRANS_DEFAULT;
	m_ytrans = S_YTRANS_DEFAULT;
	m_ztrans = S_ZTRANS_DEFAULT;
	m_azimuth = S_AZIMUTH_DEFAULT;
	m_altitude = S_ALTITUDE_DEFAULT;
	m_camera_inc = S_CAMERA_INC_DEFAULT;
}

void Camera::moveLeft() { m_xtrans += m_camera_inc; }

void Camera::moveRight() { m_xtrans -= m_camera_inc; }

void Camera::moveUp() { m_ytrans -= m_camera_inc; }

void Camera::moveDown() { m_ytrans += m_camera_inc; }

void Camera::moveForward() { m_ztrans += m_camera_inc; }

void Camera::moveBackward() { m_ztrans -= m_camera_inc; }

void Camera::rotateLeft() { m_azimuth += S_ROTATE_AMOUNT; }

void Camera::rotateRight() { m_azimuth -= S_ROTATE_AMOUNT; }

void Camera::tiltUp() { m_altitude += S_ROTATE_AMOUNT; }

void Camera::tiltDown() { m_altitude -= S_ROTATE_AMOUNT; }
