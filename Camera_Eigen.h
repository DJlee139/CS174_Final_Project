//  Created by 静一 方 on 11/22/11.
//  Copyright 2011 UCLA. All rights reserved.

#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include "Angel.h"

//this class defines the camera's position, lookat point, rotation, etc
//it also defines the kind of projection the camera is using: orthographics or perspective
//currently, only perspective 

class Camera {
public:
	Camera();
	//Getter and setter functions
	void setPosition(vec4& p) { m_position = p; }
	void setAspect(const double a) { m_aspect = a; }
	void setZoom(const double z) { m_zoom = z; }
	Angel::mat4 getProjection() { return m_cMw; }
	Angel::vec4 getPosition() { return m_position; }
	double getAspect() { return m_aspect; }
	double getZoom() { return m_zoom; }
	double getFovy() { return m_fovy; }
	double getZnear() { return m_znear; }
	double getZfar() { return m_zfar; }

    

	void init(double, double, double, double);
	void update(double);//update the m_cMw;
	//My new functions for moving the camera
	void resetView();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveForward();
	void moveBackward();
	void rotateLeft();
	void rotateRight();
	void tiltDown();
	void tiltUp();
private:
		Angel::mat4 m_cMw; //The projection matrix, if we want to call it that.
	    Angel::vec4 m_position;
	    //Define the perspective division:
		double m_fovy;
		double m_aspect;
		double m_znear;
		double m_zfar;
		double m_zoom;
	    //My new variables for camera movement:
		static const double S_XTRANS_DEFAULT = 0;
		static const double S_YTRANS_DEFAULT = 0; //def camera positions
		static const double S_ZTRANS_DEFAULT = 0;
		static const double S_AZIMUTH_DEFAULT = 0;
		static const double S_ALTITUDE_DEFAULT = 0;
		static const double S_CAMERA_INC_DEFAULT = 0.25; //amount to move on key press
		static const double S_ROTATE_AMOUNT = 0.1;
		double m_xtrans, m_ytrans, m_ztrans, m_azimuth, m_altitude;
		double m_camera_inc;
};


#endif
