//
//  Light.h
//  FEMCloth2D
//
//  Created by 静一 方 on 1/28/12.
//  Copyright 2012 UCLA. All rights reserved.
//

#ifndef FEMCloth2D_Light_h
#define FEMCloth2D_Light_h
#include "Utility.h"

class Light {
public:
	//Getter and setter functions
	void setPosition(const Eigen::Vector4f& p) { m_position = p; }
	void setColor(const Eigen::Vector4f& c) { m_color = c; }
	Eigen::Vector4f getPosition() { return m_position; }
	
private:
    Eigen::Vector4f m_position;
    Eigen::Vector4f m_color;
    
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif
