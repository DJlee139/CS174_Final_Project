#version 120

varying vec4 fColor;
varying vec3 fN;
varying vec3 fL;
varying vec3 fV;
uniform int renderType; //Apparently uniforms are ok in frag shaders, too!
uniform bool flipNormals;
uniform bool specularHighlights;
uniform bool whiteOut;

const int GOURARD = 1;
const int PHONG = 2;
const int FLAT_SHADING = 3;

uniform vec4 drawMin;
uniform vec4 drawMax;

void main()
{
   // int renderType = 1; //The old way
    
    //Gouraud Shading
	if ( renderType ==  GOURARD )
        gl_FragColor = fColor;
    //Smooth-Phong Shading
   else{
        vec3 N,V,L,H;
    
        N = normalize(fN);
        V = normalize(fV);
        L = normalize(fL);
        H = normalize(L + V);
    
    	//whiteOut is a uniform that says whether or not to draw objects with full ambient light.
    	//Walls should be, since any shading would make them visible initially; Bullets and spheres should
    	//not be, because we want them to have a 3D look.
    	float ambient_factor = whiteOut ? 1.0 : 0.3;
        vec4 ambient = ambient_factor*fColor;
        vec4 diffuse = max(dot(L,N),0.0)*0.5*fColor*vec4(1,1,1,1); //The light is white
        vec4 specular = specularHighlights ?														//I don't think we want these at all.
        	pow(max(dot(N,H),0.0),20.0)*0.5*vec4(1.0,1.0,1.0,1.0)
        	:
        	vec4(0,0,0,1);
        if(dot(L,N) < 0.0){
            specular = vec4(0.0,0.0,0.0,1.0);
        }
        gl_FragColor = ambient + diffuse + specular;
        gl_FragColor.a = 1.0;
    }
}
