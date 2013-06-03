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
	Camera(double, double, double, double);
	//Getter and setter functions
	void setPosition(vec4& p) { m_position = p; }
	void setAspect(const double a) { m_aspect = a; }
	void setZoom(const double z) { m_zoom = z; }
	Angel::mat4 getModelview() { return m_cMw; }
	Angel::vec4 getPosition() { return m_position; }
	double getAspect() { return m_aspect; }
	double getZoom() { return m_zoom; }
	double getFovy() { return m_fovy; }
	double getZnear() { return m_znear; }
	double getZfar() { return m_zfar; }

	double getTilt(){ return m_tilt;}
	double getYaw(){ return m_yaw;}

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
		double m_fovy, m_aspect, m_znear, m_zfar, m_zoom;
	    //My variables for camera movement:
		static const int S_XTRANS_DEFAULT = 0;
		static const int S_YTRANS_DEFAULT = 0; //-20;
		static const int S_ZTRANS_DEFAULT = -280; //-70
		static const int S_TILT_DEFAULT = 0;
		static const int S_YAW_DEFAULT = 0;
		static const int S_CAMERA_INC_DEFAULT = 1; //amount to move on key press
		static const int S_ROTATE_AMOUNT = 3; //This is left/right rotation
		static const int S_TILT_AMOUNT = 1; //Up/down
		double m_xtrans, m_ytrans, m_ztrans, m_tilt, m_yaw;
		double m_camera_inc;
};


#endif
