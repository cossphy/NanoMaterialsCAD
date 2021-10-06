#pragma once

//https://stackoverflow.com/questions/28806871/how-to-render-sphere-using-open-gl-c-and-not-glut-glu
//hint: use GL_NORMALIZE

#define CONST_COE 0.0222222222


typedef struct {
	GLfloat x, y, z;
}vec3;

EXT vec3 points[10000];
EXT unsigned int triangles_indices[101];
EXT unsigned int quads_indices[40000];


void JGN_SolidSphere(float radius, int numStacks, int numSides);


EXT int sph_pnt_flag;
void JGN_SolidSphereFpsCalibration();