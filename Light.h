//
//  Light.h
//  FEMCloth2D
//
//  Created by 静一 方 on 1/28/12.
//  Copyright 2012 UCLA. All rights reserved.
//

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "Angel.h"

class Light {
public:
	//Getter and setter functions
	void setPosition(const Angel::vec4& p) { m_position = p; }
	void setColor(const Angel::vec4& c) { m_color = c; }
	vec4 getPosition() { return m_position; }
	
private:
    Angel::vec4 m_position;
    Angel::vec4 m_color;
    
};


#endif
