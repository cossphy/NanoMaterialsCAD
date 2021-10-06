#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

//TODO: custom surface to buildposcar
//TODO: custom surface and vacum^ to buildlammps


#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <ctime>
#include <cctype>
using namespace std;

#include <stdlib.h>
# include <cstdlib>
# include <cmath>
# include <fstream>
# include <iomanip>
//#include ".\include\GL\glew.h"
//# include ".\freeglut\include\GL\freeglut.h"
# include "./include\GL\glut.h"
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <float.h>



//#pragma comment (lib, "lib/glew32.lib")
//#pragma comment (lib, "lib/glut32.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "libcmtd.lib")



// Windows Header Files:
#include <windows.h>
#include <Windowsx.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "opengl32.lib")
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glm\glm.hpp"
#include <commctrl.h>
#include <Shellapi.h>
#include <Shlwapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

char* ftoa(float f)
{
	static char        buf[17];
	char *            cp = buf;
	unsigned long    l, rem;

	if (f < 0) {
		*cp++ = '-';
		f = -f;
	}
	l = (unsigned long)f;
	f -= (float)l;
	rem = (unsigned long)(f * 1e6);
	sprintf(cp, "%lu.%6.6lu", l, rem);
	return buf;
}


namespace jgn
{
	double atof(char* c)
	{
		if (c == NULL)
		{
			return -1.11111;
		}
		else
		{
			return std::atof(c);
		}
	}

	class string : public std::string {

	public:
		bool isnumber()
		{
			std::string::const_iterator it = this->begin();
			int dotread = 0;
			while (it != this->end() && (std::isdigit(*it) || *it == '.'))
			{
				if (*it == '.')
				{
					dotread++;
				}
				if (dotread == 2)break;

				++it;

			}
			return (!(this->empty()) && it == (this->end()));
		}
	};

}

jgn::string LPTSTR2string(LPTSTR inp, char delimiter)
{
	jgn::string out;
	while (((char*)inp)[0] != delimiter)
	{
		out += ((char*)inp)[0];
		inp = inp + 1;
	}
	return out;
}

class ATOM
{
public:
	int atomic_number = 0;
	double atomic_weight = 0.0;
	std::string name;
	int lammps_type = 0;
	double x, y, z;


	class sel_d
	{
	public:
		char x = '\0', y = '\0', z = '\0';
	};

	sel_d selective_dynamics;
};
class ATOMIC_SYSTEM: public ATOM
{
public:
	int number_of_atoms = 0;
	ATOM* atom;

	ATOMIC_SYSTEM(int num_of_atoms=0)
	{
		number_of_atoms = num_of_atoms;
		atom = (ATOM*)malloc(sizeof(ATOM)*num_of_atoms);
	}
	~ATOMIC_SYSTEM()
	{
		number_of_atoms = 0;
		free(atom);
	}

	void realloc(int num_of_atoms)
	{
		number_of_atoms = num_of_atoms;
		atom = (ATOM*)std::realloc(NULL, num_of_atoms);
	}
	
};