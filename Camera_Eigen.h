//  Created by 静一 方 on 11/22/11.
//  Copyright 2011 UCLA. All rights reserved.

#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include "Eigen/Dense"

//this class defines the camera's position, lookat point, rotation, etc
//it also defines the kind of projection the camera is using: orthographics or perspective
//currently, only perspective 

class Camera {
public:
	Camera();
	//Getter and setter functions
	void setPosition(Eigen::Vector4f& p) { m_position = p; }
	void setAspect(const double a) { m_aspect = a; }
	void setZoom(const double z) { m_zoom = z; }
	Eigen::Affine3f getModelview() { return m_cMw; }
	Eigen::Vector4f getPosition() { return m_position; }
	double getAspect() { return m_aspect; }
	double getZoom() { return m_zoom; }
	double getFovy() { return m_fovy; }
	double getZnear() { return m_znear; }
	double getZfar() { return m_zfar; }

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	void init(double, double, double, double);
	void update(double);//update the m_cMw;
	//My new functions for moving the camera
	void resetView();
	void moveLeft();
	void moveRight();
	void moveUp(); //TODO delete
	void moveDown();  //TODO delet
	void moveForward();
	void moveBackward();
	void rotateLeft();
	void rotateRight();
	void tiltDown();
	void tiltUp();
private:
		Eigen::Affine3f m_cMw; //The projection matrix, if we want to call it that.
	    Eigen::Vector4f m_position;
	    //Define the perspective division:
		double m_fovy, m_aspect, m_znear, m_zfar, m_zoom;
	    //My new variables for camera movement:
		static const double S_XTRANS_DEFAULT = 0;
		static const double S_YTRANS_DEFAULT = -20;
		static const double S_ZTRANS_DEFAULT = -70;
		static const double S_AZIMUTH_DEFAULT = 0;
		static const double S_ALTITUDE_DEFAULT = 0;
		static const double S_TILT_DEFAULT = 30;
		static const double S_YAW_DEFAULT = 0;
		static const double S_CAMERA_INC_DEFAULT = 0.25; //amount to move on key press
		static const double S_ROTATE_AMOUNT = 3;
		static const double S_TILT_AMOUNT = 1;
		double m_xtrans, m_ytrans, m_ztrans, m_azimuth, m_altitude, m_tilt, m_yaw;
		double m_camera_inc;
};


#endif
