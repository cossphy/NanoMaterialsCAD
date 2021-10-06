#include "stdafx.h"
#include "VSystem.h"
#include "DefectedNPs.h"

Group icosahedral(float lattice_constant, int noshells)
{//Fix this
	Group groupInit;
	groupInit.N_atoms = 0;


	if (noshells < 1)
		return groupInit;
	groupInit.position.push_back(jgn::vec3(0, 0, 0));
	groupInit.N_atoms++;
	float t = 0.5 + sqrt(5.0) / 2.0;
	jgn::vec3 verticies[12];
	verticies[0] = jgn::vec3(t, 0., 1.);
	verticies[1] = jgn::vec3(t, 0., -1.);
	verticies[2] = jgn::vec3(-t, 0., 1.);
	verticies[3] = jgn::vec3(-t, 0., -1.);
	verticies[4] = jgn::vec3(1., t, 0.);
	verticies[5] = jgn::vec3(-1., t, 0.);
	verticies[6] = jgn::vec3(1., -t, 0.);
	verticies[7] = jgn::vec3(-1., -t, 0.);
	verticies[8] = jgn::vec3(0., 1., t);
	verticies[9] = jgn::vec3(0., -1., t);
	verticies[10] = jgn::vec3(0., 1., -t);
	verticies[11] = jgn::vec3(0., -1., -t);



	for (int n = 1; n < noshells; n++)
	{	
		for (int k = 0; k < 12; k = k + 2)
		{//Construct square edges(6)
			jgn::vec3 v1 = verticies[k];
			jgn::vec3 v2 = verticies[k + 1];
			for (int i = 0; i < n + 1; i++)
			{
				jgn::vec3 newpos = v1 * i + v2 * (n - i);
				groupInit.position.push_back(newpos);
				groupInit.N_atoms++;
			}
		}
		// Construct triangle planes(12)
		if (n > 1)
		{
			int map[12][2];
			map[0][0] = 8; map[0][1] = 9;
			map[1][0] = 10; map[1][1] = 11;
			map[2][0] = 8; map[2][1] = 9;
			map[3][0] = 10; map[3][1] = 11;
			map[4][0] = 0; map[4][1] = 1;
			map[5][0] = 2; map[5][1] = 3;
			map[6][0] = 0; map[6][1] = 1;
			map[7][0] = 2; map[7][1] = 3;
			map[8][0] = 4; map[8][1] = 5;
			map[9][0] = 6; map[9][1] = 7;
			map[10][0] = 4; map[10][1] = 5;
			map[11][0] = 6; map[11][1] = 7;
			for (int k = 0; k < 12; k++)
			{
				jgn::vec3 v0 = verticies[k] * n;
				jgn::vec3 v1 = verticies[map[k][0]] - verticies[k];
				jgn::vec3 v2 = verticies[map[k][1]] - verticies[k];
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n - i; j++)
					{
						if (i == 0 && j == 0)
							continue;
						jgn::vec3 newpos = v0 + v1 * i + v2 * j;
						groupInit.position.push_back(newpos);
						groupInit.N_atoms++;
					}
				}
			}
		}
		// Fill missing triangle planes(8)
		if (n > 2)
		{
			int map[4][4];
			map[0][0] = 9; map[0][1] = 6; map[0][2] = 8; map[0][3] = 4;
			map[1][0] = 11; map[1][1] = 6; map[1][2] = 10; map[1][3] = 4;
			map[2][0] = 9; map[2][1] = 7; map[2][2] = 8; map[2][3] = 5;
			map[3][0] = 11; map[3][1] = 7; map[3][2] = 10; map[3][3] = 5;
			for (int k = 0; k < 4; k++)
			{
				jgn::vec3 v0 = verticies[k] * n;
				jgn::vec3 v1 = verticies[map[k][0]] - verticies[k];
				jgn::vec3 v2 = verticies[map[k][1]] - verticies[k];
				jgn::vec3 v3 = verticies[map[k][2]] - verticies[k];
				jgn::vec3 v4 = verticies[map[k][3]] - verticies[k];
				for (int i = 1; i < n; i++)
				{
					for (int j = 1; j < n - i; j++)
					{
						jgn::vec3 newpos = v0 + v1 * i + v2 * j;
						groupInit.position.push_back(newpos);
						groupInit.N_atoms++;
						newpos = v0 + v3 * i + v4 * j;
						groupInit.position.push_back(newpos);
						groupInit.N_atoms++;
					}
				}
			}
		}
	}
	// Scale the positions
	float scaling_factor = lattice_constant / sqrt(2.0 * (1.0 + pow(t, 2)));
	float x_max = groupInit.position[0].x, x_min = groupInit.position[0].x, y_max = groupInit.position[0].y, y_min = groupInit.position[0].y, z_max = groupInit.position[0].z, z_min = groupInit.position[0].z;
	for (int i = 0; i < groupInit.N_atoms; i++)
	{
		groupInit.position[i] = groupInit.position[i] * scaling_factor;
		if (groupInit.position[i].x > x_max)
			x_max = groupInit.position[i].x;
		if (groupInit.position[i].x < x_min)
			x_min = groupInit.position[i].x;
		if (groupInit.position[i].y > y_max)
			y_max = groupInit.position[i].y;
		if (groupInit.position[i].y < y_min)
			y_min = groupInit.position[i].y;
		if (groupInit.position[i].z > z_max)
			z_max = groupInit.position[i].z;
		if (groupInit.position[i].z < z_min)
			z_min = groupInit.position[i].z;
	}
	groupInit.primitiveVec[0] = jgn::vec3(x_max - x_min + 15, 0, 0);
	groupInit.primitiveVec[1] = jgn::vec3(0, y_max - y_min + 15, 0);
	groupInit.primitiveVec[2] = jgn::vec3(0, 0, z_max - z_min + 15);

	return groupInit;
}

Group decahedron(int p, int q, int r, float lattice_constant)
// p: Number of atoms on the (100) facets perpendicular to the five fold axis
// q: Number of atoms on the (100) facets parallel to the five fold axis.q = 1 corresponds to no visible(100) facets.
// r: Depth of the Marks re-entrence at the pentagon corners. r = 0 corresponds to no re - entrence.
// Source code from ASE https://wiki.fysik.dtu.dk/ase/_modules/ase/cluster/decahedron.html
{
	Group groupInit;
	groupInit.N_atoms = 0;

	// Check values of p, q, r
	if (p < 1 || q < 1)
		return groupInit;
	if (r < 0)
		return groupInit;

	// Defining constants
	float t = 2.0 * M_PI / 5.0;
	float b = lattice_constant / sqrt(2.0);
	float a = b * sqrt(3.0) / 2.0;
	jgn::vec3 verticies[5];
	verticies[0] = jgn::vec3(cos(M_PI / 2.0), sin(M_PI / 2.0), 0.0) * a;
	verticies[1] = jgn::vec3(cos(t * 1. + M_PI / 2.), sin(t * 1. + M_PI / 2.), 0.) * a;
	verticies[2] = jgn::vec3(cos(t * 2. + M_PI / 2.), sin(t * 2. + M_PI / 2.), 0) * a;
	verticies[3] = jgn::vec3(cos(t * 3. + M_PI / 2.), sin(t * 3. + M_PI / 2.), 0.) * a;
	verticies[4] = jgn::vec3(cos(t * 4. + M_PI / 2.), sin(t * 4. + M_PI / 2.), 0.) * a;
	// Number of atoms on the five fold axisand a nice constant
	int h = p + q + 2 * r - 1;
	int g = h - q + 1;
	// Make the five fold axis
	for (j = 0; j < h; j++)
	{
		jgn::vec3 newpos(0., 0., j * b - (h - 1) * b / 2.0);
		groupInit.position.push_back(newpos);
		groupInit.N_atoms++;
	}
	// Make pentagon rings around the five fold axis
	for (int n = 1; n < h; n++)
	{// from inside to outside i.e from small (x,y) to larger (x,y)
		if (n < g)
		{// Condition for (100)-planes
			for (int m = 0; m < 5; m++)
			{// the five identical pieces
				jgn::vec3 v1;
				if (m == 0)
				{
					v1 = verticies[4];
				}
				else
				{
					v1 = verticies[m - 1];
				}
				jgn::vec3 v2 = verticies[m];
				for (int i = 0; i < n; i++)
				{// move around the 5-fold axis 
					if (n - i < g - r && i < g - r)
					{// Condition for marks re-entrence
						for (int j = 0; j < h - n; j++)
						{// from negative z to positive z
								jgn::vec3 newpos = v1 * (n - i) + v2 * i;
								newpos = newpos + jgn::vec3(0.0, 0.0, j * b - (h - n - 1) * b / 2.0);
								groupInit.position.push_back(newpos);
								groupInit.N_atoms++;
						}
					}
				}
			}
		}
	}
	float x_max = groupInit.position[0].x, x_min = groupInit.position[0].x, y_max = groupInit.position[0].y, y_min = groupInit.position[0].y, z_max = groupInit.position[0].z, z_min = groupInit.position[0].z;
	for (int i = 0; i < groupInit.N_atoms; i++)
	{
		if (groupInit.position[i].x > x_max)
			x_max = groupInit.position[i].x;
		if (groupInit.position[i].x < x_min)
			x_min = groupInit.position[i].x;
		if (groupInit.position[i].y > y_max)
			y_max = groupInit.position[i].y;
		if (groupInit.position[i].y < y_min)
			y_min = groupInit.position[i].y;
		if (groupInit.position[i].z > z_max)
			z_max = groupInit.position[i].z;
		if (groupInit.position[i].z < z_min)
			z_min = groupInit.position[i].z;
	}
	groupInit.primitiveVec[0] = jgn::vec3(x_max - x_min + 15, 0, 0);
	groupInit.primitiveVec[1] = jgn::vec3(0, y_max - y_min + 15, 0);
	groupInit.primitiveVec[2] = jgn::vec3(0, 0, z_max - z_min + 15);

	return groupInit;
}

