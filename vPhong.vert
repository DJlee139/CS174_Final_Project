#version 120

attribute vec4 vPosition;
attribute vec3 vNormal;

varying vec3 fN; //normal at current position
varying vec3 fV; //vector from point to viewer
varying vec3 fL; //vector from point to light
varying vec4 fColor;

uniform mat4 cMw;
uniform mat4 wMo;
uniform mat4 proj;

uniform vec4 cameraPosition;
uniform vec4 lightPosition;
uniform vec4 Color;
uniform vec4 drawMin;
uniform vec4 drawMax;

/* Our shader will take 2 values: int shading type (flat, Gourard, or Phong) and bool
for whether or not to make specular highlights. These will be passed in when calling the
DrawSphere function. */
uniform int renderType;
uniform bool specularHighlights;
uniform bool flipNormals;
const int GOURARD = 1;
const int PHONG = 2;
const int FLAT_SHADING = 3;

void main()
{
    gl_Position = proj*cMw*wMo*vPosition;
    
    float flipFactor = flipNormals ? -1.0 : 1.0;
    fN = (wMo*vec4(vNormal.x,vNormal.y,vNormal.z,0.0)).xyz * flipFactor;
    fV = (cameraPosition - wMo*vPosition).xyz;
    fL = (lightPosition - wMo*vPosition).xyz;

    //Gouraud Shading 
    if( renderType == GOURARD )
    {
       vec3 N,V,L,H;

        N = normalize(fN);
        V = normalize(fV);
        L = normalize(fL);
        
        H = normalize(L + V);

        vec4 ambient = 0.2*Color;
        vec4 diffuse = max(dot(L,N),0.0)*0.5*Color*vec4(1,1,1,1);
        vec4 specular = (specularHighlights) ?
        	pow(max(dot(N,H),0.0),50.0)*0.5*vec4(1,1,1,1)
        	:
        	vec4(0, 0, 0, 1);

        if(dot(L,N) < 0.0){
            specular = vec4(0,0,0,1);
        }

        fColor = ambient + diffuse + specular;
        fColor.a = 1;
    }
    else { //smooth-phong shading
    	/*
    	Here we'll test to see if the vertex is inside the volume we want drawn. If not, make it white.
    	vec4 steve = proj*cMw*wMo*vPosition;
    	if ( (steve.x <= drawMax.x && steve.x >= drawMin.x) &&
		(steve.y <= drawMax.y && steve.y >= drawMin.y) && 
		(steve.z <= drawMax.z && steve.z >= drawMin.z) )
	        fColor = Color; //Let the frag shader do all the rest of the work.
	    else*/
	    	fColor = Color; //Otherwise it's white
	}
	    	
        
        //Make sure the fragment shader gets this
}
