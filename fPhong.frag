#version 120

varying vec4 fColor;
varying vec3 fN;
varying vec3 fL;
varying vec3 fV;
uniform int renderType; //Apparently uniforms are ok in frag shaders, too!
uniform bool flipNormals;

const int GOURARD = 1;
const int PHONG = 2;
const int FLAT_SHADING = 3;

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
    
        vec4 ambient = 0.5*fColor;
        vec4 diffuse = max(dot(L,N),0.0)*0.5*fColor*vec4(1,1,1,1);
        vec4 specular = pow(max(dot(N,H),0.0),20.0)*0.5*vec4(1.0,1.0,1.0,1.0);
        if(dot(L,N) < 0.0){
            specular = vec4(0.0,0.0,0.0,1.0);
        }
        gl_FragColor = ambient + diffuse + specular;
        gl_FragColor.a = 1.0;
    }
}
