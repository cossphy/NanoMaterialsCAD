#include "Cammera.h"



PROJECTIONMATRIX::PROJECTIONMATRIX()
{
}
PROJECTIONMATRIX::~PROJECTIONMATRIX()
{

}
Cammera::Cammera()
{
}


Cammera::~Cammera()
{
}

void Cammera::loadperspectivematrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window

	glMultMatrixf(projectionMatrix.perspectiveMatrix.matrix);
	glTranslated(0, 0, -3);

	glMatrixMode(GL_MODELVIEW);

}
void Cammera::loadorthomatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window

	if (width <= height)
	{
		glOrtho(
			-1.05, +1.05,
			-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
			-10.0, 10.0);
		dipleft = -1.05;
		dipapan = 1.05*(GLfloat)height / (GLfloat)width;

	}
	else
	{
		glOrtho(
			-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
			-1.05, +1.05,
			-10.0, 10.0);
		dipleft = -1.05*(GLfloat)width / (GLfloat)height;
		dipapan = 1.05;

	}
	glMatrixMode(GL_MODELVIEW);

}


void PROJECTIONMATRIX::PERSPECTIVEMATRIX::updateMatrix()
{
	float ymax = height, xmax = width;
	if (width <= height)
	{

		xmax = 0.0035;
		ymax = 0.0035*height / width;
	}
	else
	{
		xmax = 0.0035*width / height;
		ymax = 0.0035;
	}

	float temp, temp2, temp3, temp4;
	float znear = 0.01;
	float fovyInDegrees = 60;
	// ymin = -ymax;
	// xmin = -ymax * aspectRatio;
	float left = -xmax;
	float right = xmax;
	float top = ymax;
	float bottom = -ymax;
	float zfar = 100;

	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;

	this->matrix[0] = znear/right;		this->matrix[4] = 0.0;				this->matrix[8] = 0.0f;								this->matrix[12] = 0.0;
	this->matrix[1] = 0.0;				this->matrix[5] = znear / top;		this->matrix[9] = 0.0f;								this->matrix[13] = 0.0;
	this->matrix[2] = 0.0;				this->matrix[6] = 0.0;				this->matrix[10] = (-zfar - znear) / temp4;			this->matrix[14] = (-temp * zfar) / temp4;
	this->matrix[3] = 0.0;				this->matrix[7] = 0.0;				this->matrix[11] = -1.0;							this->matrix[15] = 0.0;
}
jgn::vec4* PROJECTIONMATRIX::PERSPECTIVEMATRIX::multiply(jgn::vec4 &in)
{

	jgn::vec4 *out = new jgn::vec4;

	out->x = (in.x*this->matrix[0] + in.y*this->matrix[4] + (in.z)*(this->matrix[8]))*(-dipleft)/3.f;//+ in.w*0.1 ;
	out->y = (in.x*this->matrix[1] + in.y*this->matrix[5] + (in.z)*this->matrix[9])*dipapan/3.f;//+ in.w*this->matrix[13];
	out->z = (in.x*this->matrix[2] + in.y*this->matrix[6] + (in.z)*this->matrix[10]);// +in.w*this->matrix[14];
	out->w =  in.x*this->matrix[3] + in.y*this->matrix[7] + in.z*this->matrix[11] + in.w*this->matrix[15];
	out->x /= (1 - out->w*0.33);
	out->y /= (1 - out->w*0.33);

	return out;

}