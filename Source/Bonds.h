#pragma once
#include "stdafx.h"
#include "VSystem.h"

class BOND
{
public:
	BOND() {};
	~BOND() {};
	jgn::vec3 position[4];
	jgn::vec3 color[4];
};

class Bonds
{
public:
	Bonds();
	~Bonds();

	std::vector<BOND> bond;
	void createBond(jgn::vec3 &position1, jgn::vec3 &position2, jgn::vec3 &color1, jgn::vec3 &color2);
	void clean();
	void findBonds();
	void draw();


}EXT bonds;

