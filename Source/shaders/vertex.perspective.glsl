#version 410 core
//fovy 45
//aspect ration 16:9
//znear 0.1
//zfar 10
//This is the gluperspective code
//TODO: optimize
#define M_PI 3.1415926535897932384626433832795

layout(location = 0) in vec3 position;


void main()
{
	vec4 pos4 = vec4(position, 1);
	float fovyInDegrees = 54;
	float aspectRatio = 0x3fe38e39;
	float znear = 0.1;
	float zfar = 10;
	float ymax, xmax;
	float temp, temp2, temp3, temp4;
	mat4 matrix;
	float left, right, top, bottom;
	ymax = znear * tan(fovyInDegrees * M_PI / 360.0);
	// ymin = -ymax;
	// xmin = -ymax * aspectRatio;
	xmax = ymax * aspectRatio;
	left = -xmax;
	right = xmax;
	bottom = -ymax;
	top = ymax;
	
	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;
	matrix[0][0] = temp / temp2;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = temp / temp3;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = (right + left) / temp2;
	matrix[2][1] = (top + bottom) / temp3;
	matrix[2][2] = (-zfar - znear) / temp4;
	matrix[2][3] = -1.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = (-temp * zfar) / temp4;
	matrix[3][3] = 0.0;
   
	pos4 = pos4 * matrix;
	gl_Position = pos4;
}

