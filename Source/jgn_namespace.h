#pragma once
#include "JGN_bmpLoader.h"



extern float *crystal;
extern float *crystal_backup;
extern char *selective_dynamics;
extern bool *isSelected;
extern long int t;
extern long int sized[3];
extern bool *isSelected;
extern bool *isdeleted;
extern int *deletedHistory;
extern bool *isdeleted;
extern int *deletedHistory;
extern int jgn_supercell_xyz[3];


namespace jgn
{
	///////////////////////////////////////////////////////////////////////char[] to float
	float atof(char* c)
#ifdef JGN_SOURCE_CPP
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
#else
		;
#endif// JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////float to char[]
	char *
		ftoa(float f)
#ifdef JGN_SOURCE_CPP
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
#else
		;
#endif// JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////3x3 2x2 determinant

	float Det3x3(float x1, float y1, float z1,
				 float x2, float y2, float z2,
				 float x3, float y3, float z3)
#ifdef JGN_SOURCE_CPP
	{
		float ans = x1 * (y2*z3 - z2 * y3) - y1 * (x2*z3 - x3 * z2) + z1 * (x2*y3 - x3 * y2);

		return ans;

	}
#else
		;
#endif //JGN_SOURCE_CPP

	float Det2x2(float x1, float y1,
				 float x2, float y2)
#ifdef JGN_SOURCE_CPP
	{
		float ans = x1 * y2 - x2 * y1;

		return ans;

	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////my sin cos
//	float sin(float x)
//#ifdef JGN_SOURCE_CPP
//	{
//		return x - x * x*x / 6.0 + x * x*x*x*x / 120.0 - x * x*x*x*x*x*x / 5040.0;
//	}
//#else
//		;
//#endif //JGN_SOURCE_CPP
//		float cos(float x)
//#ifdef JGN_SOURCE_CPP
//		{
//			return 1 - x * x / 2 + x * x*x*x / 24 - x * x*x*x*x*x / 720.0;
//	}
//#else
//			;
//#endif //JGN_SOURCE_CPP
	///////////////////////////////////////////////////////////////////////3d space rotation operation

	void cpu_rotate(float p[3], float a[3], float *out)
#ifdef JGN_SOURCE_CPP

	{
		float p_bck1[3];
		float p_bck2[3];

		//z rotation
		p_bck1[0] = cos(a[2])*p[0] - sin(a[2])*p[1];
		p_bck1[1] = sin(a[2])*p[0] + cos(a[2])*p[1];
		p_bck1[2] = p[2];
	
		//x rotation
		p_bck2[0] = p_bck1[0];
		p_bck2[1] = cos(a[0])*p_bck1[1] - sin(a[0])*p_bck1[2];
		p_bck2[2] = sin(a[0])*p_bck1[1] + cos(a[0])*p_bck1[2];

		//y rotation
		out[0] = cos(a[1])*p_bck2[0] + sin(a[1])*p_bck2[2];
		out[1] = p_bck2[1];
		out[2] = -sin(a[1])*p_bck2[0] + cos(a[1])*p_bck2[2];
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////3d space translation operation
	void cpu_translate(float p[3], float a[3], float *out)
#ifdef JGN_SOURCE_CPP

	{
		out[0] = p[0] + a[0];
		out[1] = p[1] + a[1];
		out[2] = p[2] + a[2];
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////greatest common divisor
	int gcd(int &p1, int &p2)
#ifdef JGN_SOURCE_CPP
	{
		if (p1 == 0)
		{
			return p2;
		}
		else if (p2 == 0)
		{
			return p1;
		}
		else
		{
			int ans = 1;
			int test = 1;
			while (p1 / float(test) > 1 && p2 / float(test) > 1)
			{
				test++;
				if (p1 / float(test) == p1 / test && p2 / float(test) == p2 / test)
				{
					ans = test;
				}
			}
			return ans;
		}
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////least common multiple
	int lcm(int &p1, int &p2)
#ifdef JGN_SOURCE_CPP
	{
		int gcdp1p2 = jgn::gcd(p1, p2);
		if (gcdp1p2 == 0)
		{
			return 0;
		}
		else
		{
			return p1 * p2 / gcdp1p2;
		}
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////2d distance between 2 points
	float dist2d(float* p1, float* p2)
#ifdef JGN_SOURCE_CPP

	{
		return sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]));
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////3d -power of 2- distance between 2 points 
	float dist3dSquare(float const & p1, float const& p2)//I don't use sqrt for optimization
#ifdef JGN_SOURCE_CPP

	{
		return /*sqrt(*/((&p1)[0] - (&p2)[0])*((&p1)[0] - (&p2)[0]) + ((&p1)[1] - (&p2)[1])*((&p1)[1] - (&p2)[1]) + ((&p1)[2] - (&p2)[2])*((&p1)[2] - (&p2)[2])/*)*/;
	}
#else
		;
#endif //JGN_SOURCE_CPP

	//TODO:redo all that with vectors
	///////////////////////////////////////////////////////////////////////heap allocations
	void heapRealloc()
#ifdef JGN_SOURCE_CPP
	{
		crystal = (float*)realloc(crystal, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
		crystal_backup = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
		selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
		isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
		for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
		{
			isSelected[i] = false;
		}
		//isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
		isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2]);
		deletedHistory = (int*)realloc(deletedHistory, sizeof(int)*t*sized[0] * sized[1] * sized[2]);
		for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
		{
			isdeleted[i] = false;
			deletedHistory[i] = 0;
		}
	}
#else
		;
#endif //JGN_SOURCE_CPP


	///////////////////////////////////////////////////////////////////////some extra string functionality
	class string : public std::string {

	public:
		string() {};
		string(char* c) : std::string(c) {};
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
		void eraseblank()
		{
			//get rid of the spaces
			int rstrpos = this->find(" ");
			while (rstrpos != std::string::npos)
			{
				this->erase(rstrpos, 1);
				rstrpos = this->find(" ");
			}
			//get rid of the \t
			rstrpos = this->find("\t");
			while (rstrpos != std::string::npos)
			{
				this->erase(rstrpos, 1);
				rstrpos = this->find("\t");
			}
		}
	};

	///////////////////////////////////////////////////////////////////////LPTSTR to string
	jgn::string LPTSTR2string(LPTSTR inp, char delimiter, int maxchars = 1000)
#ifdef JGN_SOURCE_CPP
	{
		jgn::string out;
		while ((((char*)inp)[0] != delimiter) && maxchars != 0)
		{
			out += ((char*)inp)[0];
			inp = inp + 1;
			maxchars--;
		}
		return out;
	}
#else
		;
#endif// JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////string to LPTSTR
	LPTSTR string2LPTSTR(jgn::string str)
#ifdef JGN_SOURCE_CPP
	{
		LPTSTR out = new TCHAR[100];
		for (int i = 0; i < str.size(); i++)
		{
			out[i] = str.c_str()[i];
		}
		return out;
	}
#else
		;
#endif// JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////just a vec2
	class vec2
	{
	public:
		float x, y;
		vec2() {}
		vec2(float i, float j)
		{
			x = i;
			y = j;
		}
		vec2(const jgn::vec2& other)
		{
			x = other.x;
			y = other.y;
		}
	};
	///////////////////////////////////////////////////////////////////////just a vec4
	class vec4
	{
	public:
		float x, y, z, w;
		vec4() {}
		vec4(float i, float j, float k, float h)
		{
			x = i;
			y = j;
			z = k;
			i = h;
		}
		vec4(const jgn::vec4& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}
	};
	///////////////////////////////////////////////////////////////////////just a vec3
	class vec3
	{
	public:
		float x, y, z;
		vec3() {}
		vec3(float i, float j, float k)
		{
			x = i;
			y = j;
			z = k;
		}
		vec3(const jgn::vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

		float abs()
#ifdef JGN_SOURCE_CPP
		{
			return sqrt(x *  x + y * y + z * z);
		}
#else
		;
#endif// JGN_SOURCE_CPP

		jgn::vec3 translate(jgn::vec3 v);


		jgn::vec3 rotate(jgn::vec3 v)
#ifdef JGN_SOURCE_CPP
		{
			jgn::vec3 p_bck1;
			jgn::vec3 p_bck2;
			jgn::vec3 out;
			//z rotation
			p_bck1.x = cos(v.z)*this->x - sin(v.z)*this->y;
			p_bck1.y = sin(v.z)*this->x + cos(v.z)*this->y;
			p_bck1.z = this->z;
			//x rotation
			p_bck2.x = p_bck1.x;
			p_bck2.y = cos(v.x)*p_bck1.y - sin(v.x)*p_bck1.z;
			p_bck2.z = sin(v.x)*p_bck1.y + cos(v.x)*p_bck1.z;
			//y rotation
			out.x = cos(v.y)*p_bck2.x + sin(v.y)*p_bck2.z;
			out.y = p_bck2.y;
			out.z = -sin(v.y)*p_bck2.x + cos(v.y)*p_bck2.z;
			return out;
		}
#else
			;
#endif// JGN_SOURCE_CPP
	};

	///////////////////////////////////////////////////////////////////////quaternion, a+bi+cj+dk
	class quaternion {
	public:
		float a, b, c, d;
		quaternion() {}
		quaternion(float aa, float bb, float cc, float dd) { this->a = aa; this->b = bb; this->c = cc; this->d = dd; }
		jgn::quaternion conjugate()
		{
			return jgn::quaternion(a, -b, -c, -d);
		}
		jgn::vec3 vec3()
		{
			return jgn::vec3(b, c, d);
		}

	};

	/////////////////////////////////////////////////////////////////////////////a 2d line
	class Line2d
	{
	public:
		Line2d() {}
		Line2d(jgn::vec2 edge1, jgn::vec2 edge2)
		{
			a = edge2.y - edge1.y;
			b = edge1.x - edge2.x;
			c = edge2.x*edge1.y - edge2.y*edge1.x;
		}
		Line2d(float A, float B, float C)
		{
			a = A;
			b = B;
			c = C;
		}
		float a, b, c;
	};

	/////////////////////////////////////////////////////////////////////////////distance of a point to a line 2d
	float distvec2toline(jgn::vec2 p, jgn::Line2d line)
#ifdef JGN_SOURCE_CPP
	{
		return (line.a*p.x + line.b*p.y + line.c) / sqrt(line.a*line.a + line.b*line.b);
	}
#else
		;
#endif// JGN_SOURCE_CPP

	/////////////////////////////////////////////////////////////////////////////Miller notation plane to vector
	jgn::vec3* millerP2V(const jgn::vec3 *hkl /*(h,k,l)*/, const jgn::vec3 *prvec /*primitive vectors*/)
#ifdef JGN_SOURCE_CPP
	{
		/*std::cout << hkl->x << std::endl;
		std::cout << hkl->y << std::endl;
		std::cout << hkl->z << std::endl;
		std::cout << prvec[0].x << std::endl;
		std::cout << prvec[0].y << std::endl;
		std::cout << prvec[0].z << std::endl;
		std::cout << prvec[1].x << std::endl;
		std::cout << prvec[1].y << std::endl;
		std::cout << prvec[1].z << std::endl;
		std::cout << prvec[2].x << std::endl;
		std::cout << prvec[2].y << std::endl;
		std::cout << prvec[2].z << std::endl;*/
		jgn::vec3* out = new jgn::vec3;
		if (hkl->x == 0)
		{
			if (hkl->y == 0)
			{
				if (hkl->z == 0)//000 ok
				{
					*out = jgn::vec3(0, 0, 0);
				}
				else//00l ok
				{
					//CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[1].z - vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[1].y;
					out->x = prvec[0].y*prvec[1].z - prvec[0].z*prvec[1].y;
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[1].z + vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[1].x;
					out->y = -prvec[0].x*prvec[1].z + prvec[0].z*prvec[1].x;
					//CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[1].y - vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[1].x;
					out->z = prvec[0].x*prvec[1].y - prvec[0].y*prvec[1].x;

					//CustomSurfaces[CustomSurfacesCount - 1][0] = crystall * CustomSurfaces[CustomSurfacesCount - 1][0];
					out->x = hkl->z*out->x;
					//CustomSurfaces[CustomSurfacesCount - 1][1] = crystall * CustomSurfaces[CustomSurfacesCount - 1][1];
					out->y = hkl->z*out->y;
					//CustomSurfaces[CustomSurfacesCount - 1][2] = crystall * CustomSurfaces[CustomSurfacesCount - 1][2];
					out->z = hkl->z*out->z;
				}
			}
			else
			{
				if (hkl->z == 0)//0k0 ok
				{
					//CustomSurfaces[CustomSurfacesCount - 1][0] = -vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[2].z + vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[2].y;
					out->x = -prvec[0].y*prvec[2].z + prvec[0].z*prvec[2].z;
					//CustomSurfaces[CustomSurfacesCount - 1][1] = vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[2].z - vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[2].x;
					out->y = prvec[0].x*prvec[2].z - prvec[0].z*prvec[2].x;
					//CustomSurfaces[CustomSurfacesCount - 1][2] = -vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[2].y + vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[2].x;
					out->z = -prvec[0].x*prvec[2].y + prvec[0].y*prvec[2].x;

					//CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][0];
					out->x = hkl->y*out->x;
					//CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][1];
					out->y = hkl->y*out->y;
					//CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][2];
					out->z = hkl->y*out->z;
				}
				else//0kl ok
				{
					//CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[0].y * (vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) - vs.group[vs._isimulationBox].primitiveVec[0].z * (vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall);
					out->x = prvec[0].y * (prvec[1].z / hkl->y - prvec[2].z / hkl->z) - prvec[0].z * (prvec[1].y / hkl->y - prvec[2].y / hkl->z);
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[0].x * (vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) + vs.group[vs._isimulationBox].primitiveVec[0].z * (vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);
					out->y = -prvec[0].x * (prvec[1].z / hkl->y - prvec[2].z / hkl->z) + prvec[0].z * (prvec[1].x / hkl->y - prvec[2].x / hkl->z);
					//CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[0].x * (vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) - vs.group[vs._isimulationBox].primitiveVec[0].y * (vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);
					out->z = prvec[0].x * (prvec[1].y / hkl->y - prvec[2].y / hkl->z) - prvec[0].y * (prvec[1].x / hkl->y - prvec[2].x / hkl->z);


					//CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					//CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					//CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];
					out->x = hkl->y*hkl->z*out->x;
					out->y = hkl->y*hkl->z*out->y;
					out->z = hkl->y*hkl->z*out->z;
				}
			}
		}
		else
		{
			if (hkl->y == 0)
			{
				if (crystall == 0)//h00 ok
				{

					//CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[1].y * vs.group[vs._isimulationBox].primitiveVec[2].z - vs.group[vs._isimulationBox].primitiveVec[1].z * vs.group[vs._isimulationBox].primitiveVec[2].y;
					out->x = prvec[1].y*prvec[2].z - prvec[1].z*prvec[2].y;
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[1].x * vs.group[vs._isimulationBox].primitiveVec[2].z + vs.group[vs._isimulationBox].primitiveVec[1].z * vs.group[vs._isimulationBox].primitiveVec[2].x;
					out->y = -prvec[1].x*prvec[2].z + prvec[1].z*prvec[2].x;
					//CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[1].x * vs.group[vs._isimulationBox].primitiveVec[2].y - vs.group[vs._isimulationBox].primitiveVec[1].y * vs.group[vs._isimulationBox].primitiveVec[2].x;
					out->z = prvec[1].x*prvec[2].y - prvec[1].y*prvec[2].x;

					//CustomSurfaces[CustomSurfacesCount - 1][0] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][0];
					out->x = hkl->x*out->x;
					//CustomSurfaces[CustomSurfacesCount - 1][1] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][1];
					out->y = hkl->x*out->y;
					//CustomSurfaces[CustomSurfacesCount - 1][2] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][2];
					out->z = hkl->x*out->z;

				}
				else//h0l ok
				{


					//CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[1].y * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) - vs.group[vs._isimulationBox].primitiveVec[1].z * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall);
					out->x = prvec[1].y * (prvec[0].z / hkl->x - prvec[2].z / hkl->z) - prvec[1].z * (prvec[0].y / hkl->x - prvec[2].y / hkl->z);
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[1].x * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) + vs.group[vs._isimulationBox].primitiveVec[1].z * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);
					out->y = -prvec[1].x * (prvec[0].z / hkl->x - prvec[2].z / hkl->z) + prvec[1].z * (prvec[0].x / hkl->x - prvec[2].x / hkl->z);
					//CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[1].x * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) - vs.group[vs._isimulationBox].primitiveVec[1].y * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);
					out->z = prvec[1].x * (prvec[0].y / hkl->x - prvec[2].y / hkl->z) - prvec[1].y * (prvec[0].x / hkl->x - prvec[2].x / hkl->z);

					//CustomSurfaces[CustomSurfacesCount - 1][0] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					//CustomSurfaces[CustomSurfacesCount - 1][2] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];
					out->x = hkl->x*hkl->z*out->x;
					out->y = hkl->x*hkl->z*out->y;
					out->z = hkl->x*hkl->z*out->z;


				}
			}
			else
			{
				if (hkl->z == 0)//hk0 ok
				{
					//CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[2].y * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) - vs.group[vs._isimulationBox].primitiveVec[2].z * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk);
					out->x = prvec[2].y * (prvec[0].z / hkl->x - prvec[1].z / hkl->y) - prvec[2].z * (prvec[0].y / hkl->x - prvec[1].y / hkl->y);
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[2].x * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) + vs.group[vs._isimulationBox].primitiveVec[2].z * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);
					out->y = -prvec[2].x * (prvec[0].z / hkl->x - prvec[1].z / hkl->y) + prvec[2].z * (prvec[0].x / hkl->x - prvec[1].x / hkl->y);
					//CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[2].x * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk) - vs.group[vs._isimulationBox].primitiveVec[2].y * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);
					out->z = prvec[2].x * (prvec[0].y / hkl->x - prvec[1].y / hkl->y) - prvec[2].y * (prvec[0].x / hkl->x - prvec[1].x / hkl->y);

					//CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					//CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					//CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];
					out->x = hkl->x*hkl->y*out->x;
					out->y = hkl->x*hkl->y*out->y;
					out->z = hkl->x*hkl->y*out->z;
				}
				else//hkl
				{
					//CustomSurfaces[CustomSurfacesCount - 1][0] = (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) - (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk);
					out->x = (prvec[0].y / hkl->x - prvec[2].y / hkl->z) * (prvec[0].z / hkl->x - prvec[1].z / hkl->y) - (prvec[0].z / hkl->x - prvec[2].z / hkl->z) * (prvec[0].y / hkl->x - prvec[1].y / hkl->y);
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -(vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) + (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);
					out->y = -(prvec[0].x / hkl->x - prvec[2].x / hkl->z) * (prvec[0].z / hkl->x - prvec[1].z / hkl->y) + (prvec[0].z / hkl->x - prvec[2].z / hkl->z) * (prvec[0].x / hkl->x - prvec[1].x / hkl->y);
					//CustomSurfaces[CustomSurfacesCount - 1][2] = (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk) - (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);
					out->z = (prvec[0].x / hkl->x - prvec[2].x / hkl->z) * (prvec[0].y / hkl->x - prvec[1].y / hkl->y) - (prvec[0].y / hkl->x - prvec[2].y / hkl->z) * (prvec[0].x / hkl->x - prvec[1].x / hkl->y);

					//CustomSurfaces[CustomSurfacesCount - 1][0] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					//CustomSurfaces[CustomSurfacesCount - 1][1] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					//CustomSurfaces[CustomSurfacesCount - 1][2] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];
					out->x = -hkl->x*hkl->y*hkl->z*out->x;
					out->y = -hkl->x*hkl->y*hkl->z*out->y;
					out->z = -hkl->x*hkl->y*hkl->z*out->z;

				}
			}
		}
		//float abs = out->abs();
		//if (abs != 0)
		//{
		//	out->x = out->x / abs;
		//	out->y = out->y / abs;
		//	out->z = out->z / abs;
		//}

		//float m = 0;
		//if (out->x == out->y) {
		//	if (out->x == out->z) {//x==y==z
		//		m = 1;
		//		if (out->x != 0)
		//			m *= (1 / out->x);
		//		out->x = out->x*m;
		//		out->y = out->y*m;
		//		out->z = out->z*m;
		//	}
		//	else {//x==y
		//		m = 1;
		//		if (out->x != 0)
		//			m *= (1 / out->x);
		//		if (out->z != 0)
		//			m *= (1 / out->z);
		//		out->x = out->x*m;
		//		out->y = out->y*m;
		//		out->z = out->z*m;
		//	}
		//}
		//else {
		//	if (out->x == out->z) {//x==z
		//		m = 1;
		//		if (out->x != 0)
		//			m *= (1 / out->x);
		//		if (out->y != 0)
		//			m *= (1 / out->y);
		//		out->x = out->x*m;
		//		out->y = out->y*m;
		//		out->z = out->z*m;
		//	}
		//	else if (out->y == out->z) {//y==z
		//		m = 1;
		//		if (out->x != 0)
		//			m *= (1 / out->x);
		//		if (out->z != 0)
		//			m *= (1 / out->z);
		//		out->x = out->x*m;
		//		out->y = out->y*m;
		//		out->z = out->z*m;
		//	}
		//	else {//
		//		m = 1;
		//		if (out->x != 0)
		//			m *= (1 / out->x);
		//		if (out->y != 0)
		//			m *= (1 / out->y);
		//		if (out->z != 0)
		//			m *= (1 / out->z);
		//		out->x = out->x*m;
		//		out->y = out->y*m;
		//		out->z = out->z*m;
		//	}
		//}
		float min = 1000;
		if (out->x != 0 && out->x < min)
			min = out->x;
		if (out->y != 0 && out->y < min)
			min = out->y;
		if (out->z != 0 && out->z < min)
			min = out->z;

		out->x /= min;
		out->y /= min;
		out->z /= min;
		//std::cout << out->x << " , " << out->y << " , " << out->z << std::endl;

		return out;
	}
#else
		;
#endif// JGN_SOURCE_CPP
	/////////////////////////////////////////////////////////////////////////////xproduct and dotproduct of 2 jgn::vec3
	jgn::vec3 xproduct(jgn::vec3 v1, jgn::vec3 v2)
#ifdef JGN_SOURCE_CPP
	{
		jgn::vec3 ans;
		ans.x = jgn::Det2x2(v1.y, v1.z, v2.y, v2.z);
		ans.y = -jgn::Det2x2(v1.x, v1.z, v2.x, v2.z);
		ans.z = jgn::Det2x2(v1.x, v1.y, v2.x, v2.y);
		return ans;
	}
#else
		;
#endif// JGN_SOURCE_CPP

	float dotproduct(jgn::vec3 v1, jgn::vec3 v2)
#ifdef JGN_SOURCE_CPP
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
#else
		;
#endif// JGN_SOURCE_CPP
	/////////////////////////////////////////////////////////////////////////////volume of 3 jgn::vec3

	float volume(jgn::vec3 v1, jgn::vec3 v2, jgn::vec3 v3)
#ifdef JGN_SOURCE_CPP
	{
		return abs(jgn::dotproduct(v1, jgn::xproduct(v2,v3)));
	}
#else
		;
#endif// JGN_SOURCE_CPP
	///////////////////////////////////////////////////////////////////////just a vec6
	class vec6d
	{
	public:
		vec3 start;
		vec3 fin;

		vec6d(float i, float j, float k, float ii, float jj, float kk)
		{
			this->start.x = i;
			this->start.y = j;
			this->start.z = k;

			this->fin.z = ii;
			this->fin.z = jj;
			this->fin.z = kk;

		}
		vec6d(const vec6d& other)
		{
			this->start = other.start;
			this->fin = other.fin;
		}
	};

	///////////////////////////////////////////////////////////////////////
#if NDEBUG
#else
	void debug(int num)
#ifdef JGN_SOURCE_CPP
	{
		std::cout << "debug: " << num << std::endl;
		getchar();
	}
#else
		;
#endif// JGN_SOURCE_CPP
#endif// NDEBUG
};




//////////////operators overload/////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

jgn::quaternion operator+(const jgn::quaternion& q1, const jgn::quaternion& q2)
#ifdef JGN_SOURCE_CPP

{
	jgn::quaternion out;
	out.a = q1.a + q2.a;
	out.b = q1.b + q2.b;
	out.c = q1.c + q2.c;
	out.d = q1.d + q2.d;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::quaternion operator*(const jgn::quaternion& q1, const jgn::quaternion& q2)
#ifdef JGN_SOURCE_CPP

{
	return jgn::quaternion(q1.a*q2.a - q1.b*q2.b - q1.c*q2.c - q1.d*q2.d, q1.a*q2.b + q1.b*q2.a + q1.c*q2.d - q1.d*q2.c, q1.a*q2.c - q1.b*q2.d + q1.c*q2.a + q1.d*q2.b, q1.a*q2.d + q1.b*q2.c - q1.c*q2.b + q1.d*q2.a);
}
#else
;

#endif// JGN_SOURCE_CPP

jgn::quaternion operator*(const jgn::quaternion& q, const float& f)
#ifdef JGN_SOURCE_CPP

{
	return jgn::quaternion(q.a*f, q.b*f, q.c*f, q.d*f);
}
#else
;

#endif// JGN_SOURCE_CPP

std::ostream& operator<<(std::ostream& stream, const jgn::quaternion& q)
#ifdef JGN_SOURCE_CPP

{
	stream << q.a << " , " << q.b << " , " << q.c << " , " << q.d;
	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

std::ostream& operator<<(std::ostream& stream, const jgn::vec3& vect)
#ifdef JGN_SOURCE_CPP

{
	stream << vect.x << "\t" << vect.y << "\t" << vect.z;
	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

std::ostream& operator<<(std::ostream& stream, const jgn::vec6d& vect)
#ifdef JGN_SOURCE_CPP

{
	stream << vect.start << vect.fin;
	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

std::ostream& operator<<(std::ostream& stream, const std::vector<jgn::vec6d>& vect)
#ifdef JGN_SOURCE_CPP

{
	for (std::vector<jgn::vec6d>::const_iterator i = vect.begin(); i != vect.end(); i++)
	{
		stream << " , " << *i;
	}

	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

bool operator==(const jgn::vec2& v1, const jgn::vec2& v2)
#ifdef JGN_SOURCE_CPP

{
	return (v1.x == v2.x && v1.y == v2.y);
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator/(const jgn::vec3& v, const float& i)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v.x/i;
	out.y = v.y/i;
	out.z = v.z/i;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator*(const jgn::vec3& v, const float& i)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v.x*i;
	out.y = v.y*i;
	out.z = v.z*i;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator+(const jgn::vec3& v1, const jgn::vec3& v2)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator-(const jgn::vec3& v1, const jgn::vec3& v2)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v1.x - v2.x;
	out.y = v1.y - v2.y;
	out.z = v1.z - v2.z;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec2 operator-(const jgn::vec2& v1, const jgn::vec2& v2)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec2 out;
	out.x = v1.x - v2.x;
	out.y = v1.y - v2.y;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec2 operator+(const jgn::vec2& v1, const jgn::vec2& v2)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec2 out;
	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////functions body

#ifdef JGN_SOURCE_CPP
jgn::vec3 jgn::vec3::translate(jgn::vec3 v)
{
	return (*this) + v;
}
#endif// JGN_SOURCE_CPP

#define vec3ToGlfloat4(v) {v.x, v.y, v.z, 1.0}
#define glTranslatefvec3(v) glTranslatef(v.x/(Svmax + 5) , v.y/(Svmax + 5) , v.z/(Svmax + 5))
#define glVertex3fvec3Svmax(v) glVertex3f(v.x/(5+Svmax), v.y/(5+Svmax), v.z/(5+Svmax))
#define glVertex3fvec3(v) glVertex3f(v.x, v.y, v.z)
#define glVertex2fvec3(v) glVertex2f(v.x, v.y)




void drawMoldsLines(float *p, float *p1);


void LoadBMP(char* file, unsigned int* ID)
#ifdef JGN_SOURCE_CPP
{
	JGN_bmpLoad(file, JGN_RGBA);
	glGenTextures(1, ID);
	glBindTexture(GL_TEXTURE_2D, *ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, JGN_bmpWidth, JGN_bmpHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, JGN_bmpData);
}
#else
;
#endif// JGN_SOURCE_CPP