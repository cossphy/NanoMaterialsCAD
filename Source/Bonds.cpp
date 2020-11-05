#include "Bonds.h"

Bonds::Bonds()
{
	
}


Bonds::~Bonds()
{
}

void Bonds::findBonds()
{
	this->clean();
	for (int g0 = 0; g0 < vs.N_groups; g0++)
	{
		for (int i0 = 0; i0 < vs.group[g0].N_atoms; i0++)
		{
			for (int g = g0; g < vs.N_groups; g++)
			{
				int istart;
				g == g0 ? istart = i0+1 : istart = 0;
				for (int i = istart; i < vs.group[g].N_atoms; i++)
				{
					float dist = jgn::dist3dSquare(vs.group[g0].position[i0].x, vs.group[g].position[i].x);
					if (dist < 14)
					{
						this->createBond(vs.group[g0].position[i0], vs.group[g].position[i], vs.group[g0].color[i0], vs.group[g].color[i]);
					}
				}
			}
		}
	}
}

void Bonds::createBond(jgn::vec3 &position1, jgn::vec3 &position2, jgn::vec3 &color1, jgn::vec3 &color2)
{
	BOND b;
	b.position[0] = position1;
	b.position[1] = (position1 + position2) / 2.f;
	b.position[2] = b.position[1];
	b.position[3] = position2;

	b.color[0] = color1;
	b.color[1] = color1;
	b.color[2] = color2;
	b.color[3] = color2;

	this->bond.push_back(b);

}

void Bonds::clean()
{
	this->bond.clear();
}

void Bonds::draw()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE);
	glEnableClientState(GL_COLOR_ARRAY);
	glLineWidth(100.f / (Svmax + 5));
	int indices[4] = { 0,1,2,3 };
	for (int b = 0; b < this->bond.size(); b++)
	{
		jgn::vec3 p[4];
		p[0] = this->bond[b].position[0] / (Svmax + 5);
		p[1] = this->bond[b].position[1] / (Svmax + 5);
		p[2] = this->bond[b].position[2] / (Svmax + 5);
		p[3] = this->bond[b].position[3] / (Svmax + 5);
		glVertexPointer(3, GL_FLOAT, 0, &p[0].x);
		glNormalPointer(GL_FLOAT, 0, &this->bond[b].position[0].x);
		glColorPointer(3, GL_FLOAT, 0, &this->bond[b].color[0].x);

		glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, indices);

	}
}