//The shaders have to already be initiated by the time these functions happen!
//This implementation file doesn't #include its own header file. It doesn't need to.
#include "Mesh.h"
#include "Angel.h"
#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__
#include "World.h"
using namespace Angel;

#define V(x,y,z) vec4(x,y,z,1)
#define N(x,y,z) vec3(x,y,z)

const int HIGH_COMPLEXITY = 0;
const int MED_COMPLEXITY = 1;
const int LOW_COMPLEXITY = 2;

extern World g_timmy;
int count; //So it can be used by multiple (recursive) calls to divideTriangle

struct PtrBundle {
	GLuint vao;
	GLuint buffer;
};

GLuint genAndBindVao() {
	/* A helper function to generate and bind one vertex array*/
	GLuint vao;
	#ifdef __APPLE__
		glGenVertexArraysAPPLE(1, &vao);
		glBindVertexArrayAPPLE(vao);
	#else
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	#endif
	return vao;
}

GLuint genAndBindBuffer() {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	return buffer;
}

Mesh* makeCubeMesh() {
	//This will use my hopefully straightforward and simple algorithm for making a cube.
	vec4 points[14]; //We'll need 14 total vertices for our method.
	vec4 corners[8] = {V(-10,10,10), V(10,10,10), V(-10,-10,10), V(10,-10,10), V(-10,10,-10), V(10,10,-10), V(-10,-10,-10), V(10,-10,-10)};
	/* Put the indices of vertices we'll be using for the triangle strip in order
	Then use this ordering to actually put the points in place.*/
	size_t strip_indices[14] = {4, 3, 2, 1, 5, 3, 7, 4, 8, 2, 6, 5, 8, 7};
	for ( size_t i = 0; i < 14; i++ )
		points[i] = corners[strip_indices[i]-1];
	
	/*Now it's time to start sending these things to the shader. Our final mesh only
	needs to include a VAO to remember all these things and the number of vertices.*/
	GLuint vao = genAndBindVao();
	GLuint buffer = genAndBindBuffer();
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(points)*2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(points), points); //normals for now
	
	//There's only one attribute we have to give the shaders here.
	GLuint v_pos = glGetAttribLocation(g_timmy.getShaderz(), "vPosition");
	glEnableVertexAttribArray(v_pos);
	glVertexAttribPointer(v_pos, 4, GL_FLOAT, false, 0, (GLvoid*)0);
	GLuint normal = glGetAttribLocation(g_timmy.getShaderz(), "vNormal"); //janky normals hack
    glEnableVertexAttribArray(normal);
    glVertexAttribPointer(normal, 3, GL_FLOAT, false, 0, (GLvoid*)sizeof(points));

	//Now we'll just return what we were supposed to make, which is a Mesh object.
	return new Mesh(vao, 14, GL_TRIANGLE_STRIP);
}

vec4 unit(const vec4 &p) {
    vec4 c;
    double d=0.0;
    for(int i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d > 0.0) for(int i=0; i<3; i++) c[i] = p[i]/d;
    c[3] = 1.0;
    return c;
}

void divideTriangle(vec4* vertices, vec3* normals, const vec4& a, const vec4& b, const vec4& c, int n){
	vec4 v1, v2, v3;
    if(n>0)
    {
        v1 = unit(a + b);
        v2 = unit(a + c);
        v3 = unit(b + c);   
        divideTriangle(vertices, normals, a , v2, v1, n-1);
        divideTriangle(vertices, normals, c , v3, v2, n-1);
        divideTriangle(vertices, normals, b , v1, v3, n-1);
        divideTriangle(vertices, normals, v1, v2, v3, n-1);
    }
	else{
		vertices[count] = a;
		normals[count] = a.first3();
		count++;
		vertices[count] = b;
		normals[count] = b.first3();
		count++;
		vertices[count] = c;
		normals[count] = c.first3();
		count++;
	}
}

void generateSphere(const int complexity, vec4* vertices, vec3* normals){
	count = 0;
	vec4 v[4];
    v[0] = vec4(0.0, 0.0, 1.0, 1.0);
    v[1] = vec4(0.0, 0.942809, -0.333333, 1.0);
    v[2] = vec4(-0.816497, -0.471405, -0.333333, 1.0);
    v[3] = vec4(0.816497, -0.471405, -0.333333, 1.0);
	
	/* All 3 of our spheres will start at the same spot; they'll just have different
	subdivisions. Since 0 is the most complex, 5-0 will end up with the most vertices. */
	divideTriangle(vertices, normals, v[0], v[1], v[2], 5-complexity);
    divideTriangle(vertices, normals, v[3], v[2], v[1], 5-complexity);
    divideTriangle(vertices, normals, v[0], v[3], v[1], 5-complexity);
    divideTriangle(vertices, normals, v[0], v[3], v[2], 5-complexity);
    //The total number of vertices is 4^(5-complexity+1)*3.
}

void sendVerticesAndNormals(vec4* vertices, const int size_v, vec3* normals, const int size_n, GLuint vao, GLuint buffer) {
	//Gotta bind before we can send anything to the GPU
	#ifdef __APPLE__
		glBindVertexArrayAPPLE(vao);
	#else
		glBindVertexArray(vao);
	#endif
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //Send data from CPU to GPU. They're all the same size.
    glBufferData(GL_ARRAY_BUFFER, size_v + size_n, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size_v, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, size_v, size_n, normals);

    // initialize the vertex position attribute from the vertex shader
    GLuint position = glGetAttribLocation(g_timmy.getShaderz(), "vPosition" );
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, 4, GL_FLOAT, false, 0, (GLvoid*)0); 

	GLuint normal = glGetAttribLocation(g_timmy.getShaderz(), "vNormal");
    glEnableVertexAttribArray(normal);
    glVertexAttribPointer(normal, 3, GL_FLOAT, false, 0, (GLvoid*)size_v);
}

Mesh* makeSphereMesh(const int complexity) {
    int num_vert = 4096; //3*pow(4, 5 - complexity + 1);
   vec4 vertices[num_vert]; //For complexity = 1, need 4*4*3 = 48 vectors.
	vec3 normals[num_vert];
   
   //Populate the vertices arrays for each of 3 different sphere complexities.
	generateSphere(complexity, vertices, normals);
	
    //Create the Vertex Array and Buffer.
	GLuint vao = genAndBindVao();
	GLuint buffer = genAndBindBuffer();

	//Now since each of 48 vectors is 4 floats, sizeof(vertices) == 192.
	sendVerticesAndNormals(vertices, sizeof(vertices), normals, sizeof(normals), vao, buffer);
	return new Mesh(vao, num_vert, GL_TRIANGLES);
}

Mesh* makeCircleMesh() {
	const int complexity = 5;
	int num_vert = 3*pow(4, complexity); // ?
	vec4 vertices[num_vert];
	vec3 normals[num_vert];
	
	//Stuff from genSphere, adapted for 2D. Let's keep this simple. The circle has an area of 1!
	vec4 v[3];
    v[0] = V(0, 0.565685, 0); //Multiplied all this by 60%
    v[1] = V(-0.489898, -0.28284, 0);
    v[2] = V(0.489898, -0.28284, 0);
    
    //Now divide up our initial triangle:
    count = 0;
    divideTriangle(vertices, normals, v[0], v[1], v[2], complexity);
	
	//Create the Vertex Array and Buffer.
	GLuint vao = genAndBindVao();
	GLuint buffer = genAndBindBuffer();
   
	sendVerticesAndNormals(vertices, sizeof(vertices), normals, sizeof(normals), vao, buffer);
	return new Mesh(vao, num_vert, GL_TRIANGLES);
}

Mesh* makeWallMesh() {
	vec4 vertices[] = {V(-0.5,0.5,0), V(0.5,0.5,0), V(-0.5,-0.5,0), V(0.5,-0.5,0)};
	vec3 normals[] = {N(0,0,1), N(0,0,1), N(0,0,1), N(0,0,1)};
	
	GLuint vao = genAndBindVao();
	GLuint buffer = genAndBindBuffer();
	
	//Try using this function to send stuff for all the meshes.
	sendVerticesAndNormals(vertices, sizeof(vertices), normals, sizeof(normals), vao, buffer);
	return new Mesh(vao, 4, GL_TRIANGLE_STRIP);
}

Mesh* makeAxesMesh() {
	double l = 100;
	vec4 vertices[] = {V(-l,0,0), V(l,0,0), V(0,-l,0), V(0,l,0), V(0,0,-l), V(0,0,l)};
	vec3 normals[] = {N(0,0,1), N(0,0,1), N(0,0,1), N(0,0,1), N(0,0,1), N(0,0,1)};
	//All normals should probly be pointing in the +Z-direction right now, since the light is there.
	
	GLuint vao = genAndBindVao();
	GLuint buffer = genAndBindBuffer();
	
	sendVerticesAndNormals(vertices, sizeof(vertices), normals, sizeof(normals), vao, buffer);
	return new Mesh(vao, 6, GL_LINES);
}
