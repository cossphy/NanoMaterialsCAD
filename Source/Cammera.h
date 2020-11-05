#pragma once

#include "stdafx.h"

class PROJECTIONMATRIX {
public:
	PROJECTIONMATRIX();
	~PROJECTIONMATRIX();
	class PERSPECTIVEMATRIX {
	public:
		float matrix[16];
		void updateMatrix();
		jgn::vec4* multiply(jgn::vec4 &in);
	} perspectiveMatrix;

}EXT projectionMatrix;

class Cammera
{
public:
	Cammera();
	~Cammera();
	bool perspective_on;
	void loadperspectivematrix();
	void loadorthomatrix();
}EXT cam;

