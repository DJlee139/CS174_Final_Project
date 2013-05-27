//The shaders have to already be initiated by the time this happens!

#ifndef MESHMAKERS_HEADER
#define MESHMAKERS_HEADER

#include "Mesh.h"
#include "Eigen/dense"
#include <GLUT/glut.h>
#include "World.h"
using namespace Eigen;

#define V(x,y,z) Vector4f(x,y,z,1)
#define N(x,y,z) Vector3f(x,y,z)

const int HIGH_COMPLEXITY = 0;
const int MED_COMPLEXITY = 1;
const int LOW_COMPLEXITY = 2;

extern World g_timmy;

inline Mesh* makeCubeMesh() {
	//This will use my hopefully straightforward and simple algorithm for making a cube.
	Vector4f points[14]; //We'll need 14 total vertices for our method.
	Vector4f corners[8] = {V(-10,10,10), V(10,10,10), V(-10,-10,10), V(10,-10,10), V(-10,10,-10), V(10,10,-10), V(-10,-10,-10), V(10,-10,-10)};
	/* Put the indices of vertices we'll be using for the triangle strip in order
	Then use this ordering to actually put the points in place.*/
	size_t strip_indices[14] = {4, 3, 2, 1, 5, 3, 7, 4, 8, 2, 6, 5, 8, 7};
	for ( size_t i = 0; i < 14; i++ )
		points[i] = corners[strip_indices[i]-1];
	
	/*Now it's time to start sending these things to the shader. Our final mesh only
	needs to include a VAO to remember all these things and the number of vertices.*/
	GLuint vao;
	glGenVertexArraysAPPLE(1, &vao);
	glBindVertexArrayAPPLE(vao);
	
	GLuint buffer; //We use this buffer only to send data; we don't keep it.
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
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

Vector4f unit(const Vector4f &p) {
    Vector4f c;
    double d=0.0;
    for(int i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d > 0.0) for(int i=0; i<3; i++) c[i] = p[i]/d;
    c[3] = 1.0;
    return c;
}

int count = 0;
void divideTriangle(Vector4f* vertices, Vector3f* normals, const Vector4f& a, const Vector4f& b, const Vector4f& c, int n){
	Vector4f v1, v2, v3;
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
		normals[count] = a.head(3);
		count++;
		vertices[count] = b;
		normals[count] = b.head(3);
		count++;
		vertices[count] = c;
		normals[count] = c.head(3);
		count++;
	}
}

void generateSphere(const int complexity, Vector4f* vertices, Vector3f* normals){
	Vector4f v[4];
    v[0] = Vector4f(0.0, 0.0, 1.0, 1.0);
    v[1] = Vector4f(0.0, 0.942809, -0.333333, 1.0);
    v[2] = Vector4f(-0.816497, -0.471405, -0.333333, 1.0);
    v[3] = Vector4f(0.816497, -0.471405, -0.333333, 1.0);
	
	/* All 3 of our spheres will start at the same spot; they'll just have different
	subdivisions. Since 0 is the most complex, 5-0 will end up with the most vertices. */
	divideTriangle(vertices, normals, v[0], v[1], v[2], 5-complexity);
    divideTriangle(vertices, normals, v[3], v[2], v[1], 5-complexity);
    divideTriangle(vertices, normals, v[0], v[3], v[1], 5-complexity);
    divideTriangle(vertices, normals, v[0], v[3], v[2], 5-complexity);
    //The total number of vertices is 4^(5-complexity+1)*3.
}

void sendVerticesAndNormals(Vector4f* vertices, const int size_v, Vector3f* normals, const int size_n, GLuint vao, GLuint buffer) {
	//Gotta bind before we can send anything to the GPU
	glBindVertexArrayAPPLE(vao);
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

inline Mesh* makeSphereMesh(const int complexity) {
    // Initialize the data arrays on CPU. Make them all the same size cus it's simpler.
    int num_vert = 3*pow(4, 5 - complexity + 1);
   Vector4f vertices[num_vert]; //For complexity = 1, need 4*4*3 = 48 vectors.
	Vector3f normals[num_vert];
   
   //Populate the vertices arrays for each of 3 different sphere complexities.
	generateSphere(complexity, vertices, normals);
	
    //Create the Vertex Array and Buffer.
    GLuint vao, buffer;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
    glGenBuffers(1, &buffer);

	//Now since each of 48 vectors is 4 floats, sizeof(vertices) == 192.
	sendVerticesAndNormals(vertices, sizeof(vertices), normals, sizeof(normals), vao, buffer);
	return new Mesh(vao, num_vert, GL_TRIANGLES);
}

inline Mesh* makeWallMesh() {
	Vector4f vertices[] = {V(0,1,0), V(1,1,0), V(0,0,0), V(1,0,0)};
	Vector3f normals[] = {N(0,0,-1), N(0,0,-1), N(0,0,-1), N(0,0,-1)};
	
	GLuint vao, buffer;
	glGenVertexArraysAPPLE(1, &vao);
	glBindVertexArrayAPPLE(vao);
	glGenBuffers(1, &buffer);
	
	//Try using this function to send stuff for all the meshes.
	sendVerticesAndNormals(vertices, sizeof(vertices), normals, sizeof(normals), vao, buffer);
	return new Mesh(vao, 4, GL_TRIANGLE_STRIP);
}
	
#endif