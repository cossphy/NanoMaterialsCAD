////Virtual System
#include "VSystem.h"
#include "JGN_SolidSphere.h"
#include "ToolBar.h"
#include "JGN_StrokeCharacter.h"
#include "JGN_Windows.h"
#include "Cammera.h"
#include "Bonds.h"

VSystem::VSystem()
{
}


VSystem::~VSystem()
{
}

VSystem::VSystem(VSystem* other)
{//TODO: complite that constructor


}

void VSystem::restart()
{
	jgn_file_dropd = false;
	for (int g = 0; g < this->N_groups; g++)
	{
		this->group[g].N_atoms_per_type.clear();//number of atoms
		this->group[g].color_per_type.clear();//color of atoms
		this->group[g].weight_per_type.clear();
		this->group[g].position.clear();
		this->group[g].fractional.clear();
		this->group[g].type.clear();
		this->group[g]._alltype.clear();//write all the individual types
		this->group[g].selective_dynamics.clear();
		this->group[g].color.clear();
		this->group[g].number.clear();//atomic number
		this->group[g].weight.clear();//atomic weight
		this->group[g].radius.clear();
		this->group[g].isSelected.clear();
		this->group[g].isdeleted.clear();
		this->group[g].ishovered.clear();
		this->group[g].iscut.clear();//if the atoms is cut by a surface
	}

	this->N_types = 0;//#N of different elements
	this->types.clear();//name of different elements
	this->N_atoms = 0;// total #N of the system
	this->N_atoms_per_type.clear();
	this->color_per_type.clear();//color of atoms
	this->weight_per_type.clear();
	this->hoveredatom = jgn::vec2(-1, -1);// group,atoms of the atom that is currently hovered
	this->hoveredatom_prev = jgn::vec2(-1, -1);
	//this->simulationboxVolume = 0;
	this->noupdate = false;


	this->N_groups = 0;//#N of groups
	this->_isimulationBox = 0;//the group that its simulation box is used
	//jgn::vec3 simulationBoxEdges[8];//the simumation box 2 draw;
	this->_sellectHistory.clear();//(group,atom,history)
	this->_sellectHistory2undo = 1;//


	this->group.clear();
	this->deletedHistory.clear();

	this->selected_rotate_ison = false;
	this->selected_translate_ison = false;
	this->selected_translate_sensitivity = 1;
	this->selected_change_hovered_axes = -1;
	this->istranslating_theselected = false;
	this->isrotating_theselected = false;

	//for the original
	for (int g = 0; g < this->original->N_groups; g++)
	{
		this->original->group[g].N_atoms_per_type.clear();//number of atoms
		this->original->group[g].color_per_type.clear();//color of atoms
		this->original->group[g].weight_per_type.clear();
		this->original->group[g].position.clear();
		this->original->group[g].fractional.clear();
		this->original->group[g].type.clear();
		this->original->group[g]._alltype.clear();//write all the individual types
		this->original->group[g].selective_dynamics.clear();
		this->original->group[g].color.clear();
		this->original->group[g].number.clear();//atomic number
		this->original->group[g].weight.clear();//atomic weight
		this->original->group[g].radius.clear();
		this->original->group[g].isSelected.clear();
		this->original->group[g].isdeleted.clear();
		this->original->group[g].ishovered.clear();
		this->original->group[g].iscut.clear();//if the atoms is cut by a surface
	}

	this->original->N_types = 0;//#N of different elements
	this->original->types.clear();//name of different elements
	this->original->N_atoms = 0;// total #N of the system
	this->original->N_atoms_per_type.clear();
	this->original->color_per_type.clear();//color of atoms
	this->original->weight_per_type.clear();
	this->original->hoveredatom = jgn::vec2(-1, -1);// group,atoms of the atom that is currently hovered
	this->original->hoveredatom_prev = jgn::vec2(-1, -1);
	//this->original->simulationboxVolume = 0;
	this->original->noupdate = false;


	this->original->N_groups = 0;//#N of groups
	this->original->_isimulationBox = 0;//the group that its simulation box is used
	//jgn::vec3 simulationBoxEdges[8];//the simumation box 2 draw;
	this->original->_sellectHistory.clear();//(group,atom,history)
	this->original->_sellectHistory2undo = 1;//


	this->original->group.clear();
	this->original->deletedHistory.clear();

	this->original->selected_rotate_ison = false;
	this->original->selected_translate_ison = false;
	this->original->selected_translate_sensitivity = 1;
	this->original->selected_change_hovered_axes = -1;
	this->original->istranslating_theselected = false;
	this->original->isrotating_theselected = false;
	jgnCommands(L"clean", 0);

}

void VSystem::reserve(const unsigned int sx, const unsigned int sy, const unsigned int sz)
{
	//reserve for every group
	for (int i = 0; i < this->N_groups; i++)
	{
		this->group[i].N_atoms = sx * sy * sz * this->original->group[i].N_atoms;
		this->group[i].primitiveVec[0] = this->original->group[i].primitiveVec[0] * sx;
		this->group[i].primitiveVec[1] = this->original->group[i].primitiveVec[1] * sy;
		this->group[i].primitiveVec[2] = this->original->group[i].primitiveVec[2] * sz;
		this->group[i]._reserve(this->group[i].N_atoms);
	}
	//reserve for the whole system
	vs.setSimulationBox(_isimulationBox);
	this->N_atoms = 0;
	for(int i=0;i<vs.N_types;i++)
	{ 
		this->N_atoms_per_type[i] = sx * sy * sz * this->original->N_atoms_per_type[i];
		this->N_atoms += this->N_atoms_per_type[i];
	}
	vs._sellectHistory.clear();
	vs._sellectHistory.reserve(vs.N_atoms);
	
	//prepare the memory
	for (int g = 0; g < vs.N_groups; g++)
	{
		for (int i = 0; i < vs.group[g].N_atoms; i++)
		{
			vs.group[g].position.emplace_back(jgn::vec3(0, 0, 0));
			vs.group[g].type.emplace_back(jgn::string(""));
			vs.group[g].selective_dynamics.emplace_back(jgn::string(""));
			vs.group[g].color.emplace_back(jgn::vec3(0, 0, 0));
			vs.group[g].number.emplace_back(0);
			vs.group[g].weight.emplace_back(0);
			vs.group[g].radius.emplace_back(0);
			vs.group[g].isSelected.emplace_back(false);
			vs.group[g].isdeleted.emplace_back(false);
			vs.group[g].iscut.emplace_back(false);
			vs.group[g].ishovered.emplace_back(false);
		}
	}
	for (int g = 0; g < vs.N_groups; g++)
		for (int i = 0; i < vs.group[g].N_atoms; i++)
		{
			vs._sellectHistory.emplace_back(jgn::vec3(g, i, -1));
		}
}
void Group::_reserve(const unsigned int r)
{
	this->position.clear();
	this->type.clear();
	this->selective_dynamics.clear();
	this->color.clear();
	this->number.clear();
	this->weight.clear();
	this->radius.clear();
	this->isSelected.clear();
	this->isdeleted.clear();
	this->iscut.clear();
	this->ishovered.clear();

	this->position.reserve(r);
	this->type.reserve(r);
	this->selective_dynamics.reserve(r);
	this->color.reserve(r);
	this->number.reserve(r);
	this->weight.reserve(r);
	this->radius.reserve(r);
	this->isSelected.reserve(r);
	this->isdeleted.reserve(r);
	this->iscut.reserve(r);
	this->ishovered.reserve(r);

}

jgn::vec2 VSystem::_hoveringAnatom(jgn::vec2 m)
{
	jgn::vec2 finalclicked = jgn::vec2(-1, -1);//x=group, y=atom
	int iatom = -1;
	int iatomtosellect = -1;


	for (int g = 0; g < vs.N_groups; g++)
	{
		for (int i = 0; i < vs.group[g].N_atoms; i++)
		{
			if (!vs.group[g].isdeleted[i] && !vs.group[g].iscut[i])
			{
				iatom++;
				jgn::vec3 p1;
				jgn::vec3 p2;
				jgn::vec3 prevp1;
				jgn::vec3 theta_rad;
				theta_rad = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
				jgn::vec4 ppers;

				p1 = vs.group[g].position[i] / (Svmax + 5);

				p2 = p1.translate(jgn::vec3(model_translate[0], model_translate[1], model_translate[2]));
				p1 = p2.rotate(theta_rad);
				p1.z = -p1.z;
				if (cam.perspective_on)
				{
					ppers = jgn::vec4(p1.x, p1.y, p1.z, 1);
					jgn::vec4 *out = projectionMatrix.perspectiveMatrix.multiply(ppers);
					p1.x = out->x;
					p1.y = out->y;
					p1.z = out->z;

				}

				//glBegin(GL_POINTS);
				//glVertex3f(p1.x, p1.y, p1.z);
				//glEnd();

				///at this point p1 is the final product


				if (jgn::dist2d((float*)(&(m.x)), &(p1.x)) < vs.group[g].radius[i] / (Svmax + 5))
				{
					if (finalclicked.y == -1)
					{
						finalclicked = jgn::vec2(g, i);
						prevp1 = p1;
						iatomtosellect = iatom;
					}
					else if (p1.z < prevp1.z) {
						finalclicked = jgn::vec2(g, i);
						prevp1 = p1;
						iatomtosellect = iatom;
					}
				}
			}
		}
	}
	if (finalclicked.y != -1)
	{
		vs.group[finalclicked.x].ishovered[finalclicked.y] = true;
	}

	vs.hoveredatom = finalclicked;
	if (!(vs.hoveredatom == vs.hoveredatom_prev))
	{
		if(vs.hoveredatom_prev.x!=-1)
			vs.group[vs.hoveredatom_prev.x].ishovered[vs.hoveredatom_prev.y] = false;
		JGN_PostRedisplay();
	}
	vs.hoveredatom_prev = vs.hoveredatom;
	return finalclicked;
}


void Group::N_types(const unsigned int N_t)
{
	this->_N_types = N_t;
	this->_alltype.reserve(N_t);
}
void VSystem::unsellectAll()
{
	_sellectHistory2undo = -1;
	//tb._sellectedfordistance[0] = jgn::vec2(-1, -1);
	//tb._sellectedfordistance[1] = jgn::vec2(-1, -1);
	for (int g = 0; g < this->N_groups; g++)
	{
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{
			this->group[g].isSelected[i] = false;
			this->_sellectHistory[i].z = -1;
			this->_sellectHistory2undo = -1;
		}
	}
}

void VSystem::draw()
{
	if(cam.perspective_on)
		cam.loadperspectivematrix();

	//Draw atoms
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	if(render_is_on)
		this->_drawatoms();
	//bonds.draw();

	//Draw translate or rotate base if is on
	if (this->selected_translate_ison)
	{
		glDisable(GL_LIGHTING);
		this->selected_change_draw();
		glEnable(GL_LIGHTING);
	}
	else if (this->selected_rotate_ison)
	{
		glDisable(GL_LIGHTING);
		this->selected_change_draw();
		glEnable(GL_LIGHTING);
	}

	//Draw simulation box
	this->_drawSimulationBox();
	cam.loadorthomatrix();
	this->_drawBase();

	//Draw distance tool line
	if (cam.perspective_on)
		cam.loadperspectivematrix();
	this->_drawDistanceToolLine();

	cam.loadorthomatrix();
	//Draw system info
	this->_drawsysteminfo();

	//Draw group list
	this->grouplist.draw();

}

void VSystem::Grouplist::draw()
{
	glLoadIdentity();
	if (vs.N_groups > 1)
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		if(this->open)
		{ 
			//back ground
			glBindTexture(GL_TEXTURE_2D, button1ID);
			glColor3f(0.2, 0.2, 0.2);
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex3f(dipleft + tb.size + 0.4, dipapan - 0.01, 5);
			glTexCoord2d(0.99, 0.99);
			glVertex3f(dipleft + tb.size + 0.4, dipapan - 0.3, 5);
			glTexCoord2d(0.99, 0);
			glVertex3f(dipleft + tb.size + 0.05, dipapan - 0.3, 5);
			glTexCoord2d(0, 0);
			glVertex3f(dipleft + tb.size + 0.05, dipapan - 0.01, 5);
			glEnd();
			//write
			glBindTexture(GL_TEXTURE_2D, Font);
			for (int i = 0; i < vs.N_groups; i++)
			{
				this->options.hovering == i ? glColor3f(1, 0.2, 0.2) : glColor3f(0, 0, 0);
				glTranslatef(dipleft + tb.size + 0.13, dipapan - 0.08 -i*0.05, 5);
				glScalef(0.5, 0.5, 0.5);
				write::string("group ");
				write::character(i + 49);
				glLoadIdentity();
			}
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, showlessID);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, showmoreID);
		}
		this->hovering ? glColor3f(0.2, 0.2, 0.2) : glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2d(0.99, 0.99);
		glVertex3f(dipleft + tb.size + 0.05 + 0.05, dipapan-0.01 , 5);
		glTexCoord2d(0.99, 0);
		glVertex3f(dipleft + tb.size + 0.05 + 0.05, dipapan - 0.06, 5);
		glTexCoord2d(0, 0);
		glVertex3f(dipleft + tb.size + 0.05, dipapan - 0.06, 5);
		glTexCoord2d(0, 1);
		glVertex3f(dipleft + tb.size + 0.05, dipapan- 0.01, 5);
		glEnd();

		
	}
}
void VSystem::selected_change_hover_check(jgn::vec2 m)
{
	if (!this->istranslating_theselected && !this->isrotating_theselected)
	{
		jgn::vec3 v0;
		jgn::vec3 vi;
		jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
		jgn::vec3 t = jgn::vec3(model_translate[0], model_translate[1], model_translate[2]);
		t = t * (Svmax + 5);
		v0 = this->selected_manipulate_base[0];
		vi = this->selected_manipulate_base[1];
		jgn::cpu_translate(&(v0.x), &(t.x), &(v0.x));
		jgn::cpu_rotate(&(v0.x), &(r.x), &(v0.x));
		v0 = v0 / (Svmax + 5);
		jgn::cpu_translate(&(vi.x), &(t.x), &(vi.x));
		jgn::cpu_rotate(&(vi.x), &(r.x), &(vi.x));
		vi = vi / (Svmax + 5);
		jgn::Line2d line(jgn::vec2(v0.x, v0.y), jgn::vec2(vi.x, vi.y));
		if (v0.x > vi.x - 0.0001 && v0.x < vi.x + 0.0001)
		{
			if (abs(jgn::distvec2toline(m, line)) < 0.01 && ((m.y > v0.y && m.y < vi.y) || (m.y < v0.y && m.y > vi.y)))
			{
				this->selected_change_hovered_axes = X_AXIS;
				return;
			}
		}
		else
		{
			if (abs(jgn::distvec2toline(m, line)) < 0.01 && ((m.x > v0.x && m.x < vi.x) || (m.x < v0.x && m.x > vi.x)))
			{
				this->selected_change_hovered_axes = X_AXIS;
				return;
			}
		}
		vi = this->selected_manipulate_base[2];
		jgn::cpu_translate(&(vi.x), &(t.x), &(vi.x));
		jgn::cpu_rotate(&(vi.x), &(r.x), &(vi.x));
		vi = vi / (Svmax + 5);
		line = jgn::Line2d(jgn::vec2(v0.x, v0.y), jgn::vec2(vi.x, vi.y));
		if (v0.x > vi.x - 0.0001 && v0.x < vi.x + 0.0001)
		{
			if (abs(jgn::distvec2toline(m, line)) < 0.01 && ((m.y > v0.y && m.y < vi.y) || (m.y < v0.y && m.y > vi.y)))
			{
				this->selected_change_hovered_axes = Y_AXIS;
				return;
			}
		}
		else
		{
			if (abs(jgn::distvec2toline(m, line)) < 0.01 && ((m.x > v0.x && m.x < vi.x) || (m.x < v0.x && m.x > vi.x)))
			{
				this->selected_change_hovered_axes = Y_AXIS;
				return;
			}
		}
		vi = this->selected_manipulate_base[3];
		jgn::cpu_translate(&(vi.x), &(t.x), &(vi.x));
		jgn::cpu_rotate(&(vi.x), &(r.x), &(vi.x));
		vi = vi / (Svmax + 5);
		line = jgn::Line2d(jgn::vec2(v0.x, v0.y), jgn::vec2(vi.x, vi.y));
		if (abs(jgn::distvec2toline(m, line)) < 0.01 && (((m.y > v0.y && m.y < vi.y) || (m.y < v0.y && m.y > vi.y))))
		{
			this->selected_change_hovered_axes = Z_AXIS;
			return;
		}
		this->selected_change_hovered_axes = NO_AXIS;
	}
}

void VSystem::selected_change_draw()
{
	//draw vertices
	glClear(GL_DEPTH_BUFFER_BIT);
	this->selected_change_hovered_axes == X_AXIS ? glLineWidth(10) : glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex3fvec3Svmax(this->selected_manipulate_base[0]);
	glColor3f(1, 0, 0);
	glVertex3fvec3Svmax(this->selected_manipulate_base[1]);
	glEnd();
	this->selected_change_hovered_axes == Y_AXIS ? glLineWidth(10) : glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex3fvec3Svmax(this->selected_manipulate_base[0]);
	glColor3f(0, 1, 0);
	glVertex3fvec3Svmax(this->selected_manipulate_base[2]);
	glEnd();
	this->selected_change_hovered_axes == Z_AXIS ? glLineWidth(10) : glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex3fvec3Svmax(this->selected_manipulate_base[0]);
	glColor3f(0, 0, 1);
	glVertex3fvec3Svmax(this->selected_manipulate_base[3]);
	glEnd();

	//draw scale (the thing in the middle)
	//TODO: change that if possible
	glLoadIdentity();
	jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
	jgn::vec3 v = this->selected_manipulate_base[3];
	jgn::vec3 t = jgn::vec3(model_translate[0], model_translate[1], model_translate[2]);
	t = t * (Svmax + 5);
	jgn::cpu_translate(&(v.x), &(t.x), &(v.x));
	jgn::cpu_rotate(&(v.x), &(r.x), &(v.x));
	v = v / (Svmax + 5);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, buttonID);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(v.x - 0.08, v.y - 0.04, v.z);
	glTexCoord2f(1, 0);
	glVertex3f(v.x + 0.08, v.y - 0.04, v.z );
	glTexCoord2f(1, 1);
	glVertex3f(v.x + 0.08, v.y + 0.04, v.z);
	glTexCoord2f(0, 1);
	glVertex3f(v.x - 0.08, v.y + 0.04, v.z);
	glEnd();

	//write the scale
	glBindTexture(GL_TEXTURE_2D, Font);
	glColor3f(0, 0, 0);
	glTranslatef(v.x - 0.075 , v.y - 0.035, v.z);
	glScalef(0.75, 0.75, 0.75);
	jgn::string s = jgn::ftoa(this->selected_translate_sensitivity);
	write::string(s.c_str(), 3);
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);

		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 0.0, 1.0);

	glTranslatef(model_translate[0], model_translate[1], model_translate[2]);

}

bool VSystem::Grouplist::Options::checkhoverstatus(const jgn::vec2 m)
{
	this->hovering = -1;
	for (int i = 0; i < vs.N_groups; i++)
	{
		if (m.x > dipleft + tb.size + 0.13 && m.x < dipleft + tb.size + 0.3 + 0.05 && m.y>dipapan - 0.08 - i * 0.05 && m.y < dipapan - 0.08 - (i-1) * 0.05)
		{
			this->hovering = i;
			if (this->hovering_prev != i)
				JGN_PostRedisplay();
			this->hovering_prev = this->hovering;
			return true;
		}
	}
	if(this->hovering_prev!=-1)
		JGN_PostRedisplay();
	this->hovering_prev = -1;
		

		return false;
}

bool VSystem::Grouplist::checkhoverstatus(const jgn::vec2 m)
{
	if (m.x > dipleft + tb.size + 0.05 && m.x < dipleft + tb.size + 0.05 + 0.05 && m.y>dipapan - 0.06 && m.y < dipapan - 0.01)
	{
		this->hovering = true;
		if (this->hovering_prev == false)
			JGN_PostRedisplay();
		hovering_prev = hovering;

	}
	else
	{
		this->hovering = false;
		if (this->hovering_prev == true)
			JGN_PostRedisplay();
		hovering_prev = hovering;
	}
		return hovering;
}

void VSystem::_drawatoms()
{


	for (int g = 0; g < this->N_groups; g++)
	{
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{
			if (!vs.group[g].iscut[i])
				if (!vs.group[g].isdeleted[i])
				{
					GLfloat mat_ambient[4];
					GLfloat mat_deffuse[4];
					if (this->group[g].isSelected[i])
					{
						mat_ambient[0] = 0;
						mat_ambient[1] = 0;
						mat_ambient[2] = 0;
						mat_ambient[3] = 1;
						mat_deffuse[0] = 0;
						mat_deffuse[1] = 0;
						mat_deffuse[2] = 0;
						mat_deffuse[3] = 1;
					}
					else
					{
						mat_ambient[0] = this->group[g].color[i].x;
						mat_ambient[1] = this->group[g].color[i].y;
						mat_ambient[2] = this->group[g].color[i].z;
						mat_ambient[3] = 1;
						mat_deffuse[0] = this->group[g].color[i].x;
						mat_deffuse[1] = this->group[g].color[i].y;
						mat_deffuse[2] = this->group[g].color[i].z;
						mat_deffuse[3] = 1;
					}

					if (this->group[g].ishovered[i])
					{
						mat_ambient[0] += 0.3;
						mat_ambient[1] += 0.3;
						mat_ambient[2] += 0.3;
						mat_deffuse[0] += 0.3;
						mat_deffuse[1] += 0.3;
						mat_deffuse[2] += 0.3;
					}
					glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);



					glTranslatefvec3(this->group[g].position[i]);
					glRotatef(-theta[1], 0.0, 0, 1);
					glRotatef(-theta[0], 1.0, 0.0, 0.0);
					glRotatef(90, 1.0, 0.0, 0.0);
					JGN_SolidSphere(this->group[g].radius[i] / (Svmax + 5), sphStacks, sphSides);
					glRotatef(-90, 1.0, 0.0, 0.0);
					glRotatef(theta[0], 1.0, 0.0, 0.0);
					glRotatef(theta[1], 0.0, 0, 1);
					glTranslatefvec3(-this->group[g].position[i]);
				}
		}
	}


}

void VSystem::_drawDistanceToolLine()
{
	if (tb._sellectedfordistance[1].y != -1)
	{
		glDisable(GL_LIGHTING);

		jgn::vec3 p1 = vs.group[tb._sellectedfordistance[0].x].position[tb._sellectedfordistance[0].y] / (Svmax + 5);
		jgn::vec3 p2 = vs.group[tb._sellectedfordistance[1].x].position[tb._sellectedfordistance[1].y] / (Svmax + 5);

		glColor3f(0, 1, 0);
		//write the distance
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, button1ID);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex3f(dipleft + tb.size + 0.027, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y-0.055, 5);
		glTexCoord2d(1, 1);

		glVertex3f(dipleft + tb.size + 0.36, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.055, 5);
		glTexCoord2d(1, 0);

		glVertex3f(dipleft + tb.size + 0.36, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.125, 5);
		glTexCoord2d(0, 0);

		glVertex3f(dipleft + tb.size + 0.027, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.125, 5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, Font);
		glColor3f(0, 0, 0);
		glTranslatef(dipleft + tb.size + 0.027, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.12, 6);
		glScalef(0.5, 0.5, 0.5);
		float d = sqrt(jgn::dist3dSquare((vs.group[tb._sellectedfordistance[0].x].position[tb._sellectedfordistance[0].y].x), (vs.group[tb._sellectedfordistance[1].x].position[tb._sellectedfordistance[1].y].x)));
		int di = (int)d;
		char dia[30];
		itoa(di, dia, 10);
		write::string(dia);
		write::character('.');
		d -= di;
		write::string(&(jgn::ftoa(d))[2], 5);
		write::character(Angstrom);
		glLoadIdentity();



		glColor3f(0, 0, 0);

			glRotatef(theta[0], 1.0, 0.0, 0.0);
			glRotatef(theta[1], 0.0, 0.0, 1.0);

		glTranslatef(model_translate[0], model_translate[1], model_translate[2]);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
		glVertex3fvec3(p1);
		glVertex3fvec3(p2);
		glEnd();
		glEnable(GL_LIGHTING);
	}
}
void VSystem::_drawsysteminfo()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Font);
	glDisable(GL_LIGHTING);
	int stroke_c = 0;
	//write the element type
	for (int ff = 0; ff < this->N_types; ff++)
	{
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-dipleft - 0.4, dipapan - 0.08 - 0.1*ff, 6);
		glScalef(0.5, 0.5, 0.5);
		itoa(vs.N_atoms_per_type[ff], ss, 10);
		stroke_c = 0;
		while (ss[stroke_c] != '\0')
		{
			write::character(ss[stroke_c]);
			stroke_c++;
		}
		stroke_c = 0;
	}
	////////////write custom surfaces
	glColor3f(0, 0, 0);
	for (int i = 0; i < CustomSurfacesCount; i++)
	{
		glLoadIdentity();
		glTranslatef(dipleft + 1.5 * tb.size, dipapan - 0.1 - 0.06*i, 6);
		glScalef(0.5, 0.5, 0);
		i == CustomSurfaceSelected ? glColor3f(1.0, 0.0, 0.0) : glColor3f(0.0, 0.0, 0.0);

		write::character('(');
		char buf[100];
		itoa(CustomSurfaces_hkl[i][0], buf, 10);
		write::string(buf);
		itoa(CustomSurfaces_hkl[i][1], buf, 10);
		write::string(buf);
		itoa(CustomSurfaces_hkl[i][2], buf, 10);
		write::string(buf);
		write::character(')');
		write::character(' ');
		itoa(CustomSurfaces[i][3], buf, 10);
		write::string(buf);
		write::character(Angstrom);

	}
	glEnable(GL_LIGHTING);
	glPointSize(10);
	//draw sphere color and write the number of atoms per type
	for (int ff = 0; ff < this->N_types; ff++)
	{
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-dipleft - 0.25, dipapan - 0.1 - 0.1*ff, 6);
		glDisable(GL_LIGHTING);
		write::string(std::string(vs.types[ff]).c_str());
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glLoadIdentity();
		if (shperes_on)
		{
			colr[0] = vs.color_per_type[ff].x;
			colr[1] = vs.color_per_type[ff].y;
			colr[2] = vs.color_per_type[ff].z;
			GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
			GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
			glTranslatef(-dipleft - 0.42, dipapan - 0.06 - 0.1*ff, 6);


			glRotatef(90, 1.0, 0.0, 0.0);
			JGN_SolidSphere(20 * 0.001, 32, 32);
			
		}
		else
		{
			glBegin(GL_POINTS);
			colr[0] = fmod(aweights[ff], 1.5);
			colr[1] = fmod(anumber[ff], 0.92);
			colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
			glColor3fv(colr);
			glVertex3f(-dipleft, float(ff) / float(vs.N_types), 0);
			glEnd();
		}

	}
	////////////write simulation box volume
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, button1ID);
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.99, 0.99);
	glVertex3f(-dipleft - 0.4, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]), 5);
	glTexCoord2d(0.99, 0);
	glVertex3f(-dipleft - 0.4, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]) + 0.07, 5);
	glTexCoord2d(0, 0);
	glVertex3f(-dipleft, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]) + 0.07, 5);
	glTexCoord2d(0, 1);
	glVertex3f(-dipleft, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]), 5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Font);
	glColor3f(0, 0, 0);
	glLoadIdentity();
	glTranslatef(-dipleft, -dipapan + 2 * dipapan*(40.0 / mainwndsize[1]), 6);
	glScalef(0.4, 0.4, 0.2);

	glTranslatef(-0.02, 0.06, 0);
	glScalef(0.8, 0.8, 0.8);
	write::rtl::character('3');
	glScalef(1.25, 1.25, 1.25);
	glTranslatef(0.02, -0.06, 0);

	write::rtl::character(Angstrom);
	write::rtl::string(jgn::ftoa(vs.simulationboxVolume));
	glEnable(GL_LIGHTING);
}

void VSystem::_drawBase()
{
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	//glTranslatef(0.2, 0, 0);
	glLineWidth(5);
	//GLfloat mat_ambient[] = { 1,0,0,1 };
	//GLfloat mat_deffuse[] = { 1,0,0,1 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

	unsigned int indexes[6] = { 0,1,
								0,2,
								0,3};

	jgn::vec3 sb[4];
	sb[0] = jgn::vec3(0, 0, 0);
	sb[1] = this->group[this->_isimulationBox].primitiveBase[0];
	sb[2] = this->group[this->_isimulationBox].primitiveBase[1];
	sb[3] = this->group[this->_isimulationBox].primitiveBase[2];

	glVertexPointer(3, GL_FLOAT, 0, &sb[0].x);
	glNormalPointer(GL_FLOAT, 0, &sb[0].x);
	glTranslatef(dipleft+0.08, -dipapan + 2*dipapan*(70.0/mainwndsize[1]), 7);

		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 0.0, 1.0);

	glScalef(0.07, 0.07, 0.07);
	//glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	glBegin(GL_LINES);
	glColor4f(0., 0., 0., 1);
	glVertex3fvec3(sb[0]);
	glColor4f(1, 0, 0,1);
	glVertex3fvec3(sb[1]);
	glEnd();

	//glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	glBegin(GL_LINES);
	glColor4f(0., 0., 0., 1);
	glVertex3fvec3(sb[0]);
	glColor4f(0, 1, 0,1);
	glVertex3fvec3(sb[2]);
	glEnd();
	//mat_ambient[1] = 0;
	//mat_deffuse[1] = 0;
	//mat_ambient[2] = 1;
	//mat_deffuse[2] = 1;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
	//glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	glBegin(GL_LINES);
	glColor4f(0., 0., 0., 1);
	glVertex3fvec3(sb[0]);
	glColor4f(0, 0, 1, 1);
	glVertex3fvec3(sb[3]);
	glEnd();
	glLoadIdentity();

}

void VSystem::translate_selected(jgn::vec2& m, jgn::vec2& mprev)
{
	if (this->istranslating_theselected)
	{
		if (this->selected_change_hovered_axes == X_AXIS)
		{
			jgn::vec3 dm = jgn::vec3(m.x - mprev.x, m.y - mprev.y, 0);
			jgn::vec3 b = this->selected_manipulate_base[1] - this->selected_manipulate_base[0];
			jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
			jgn::cpu_rotate(&b.x, &r.x, &b.x);
			float d = jgn::dotproduct(dm, b)*this->selected_translate_sensitivity;

			for (int i = 0; i < this->N_atoms; i++)
			{//for every atom
				if (this->_sellectHistory[i].z != -1)
				{//if it is sellected
					this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y] = this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y] + jgn::vec3(d, 0, 0);
				}
			}
		}
		else if (this->selected_change_hovered_axes == Y_AXIS)
		{
			jgn::vec3 dm = jgn::vec3(m.x - mprev.x, m.y - mprev.y, 0);
			jgn::vec3 b = this->selected_manipulate_base[2] - this->selected_manipulate_base[0];
			jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
			jgn::cpu_rotate(&b.x, &r.x, &b.x);
			float d = jgn::dotproduct(dm, b)*this->selected_translate_sensitivity;

			for (int i = 0; i < this->N_atoms; i++)
			{//for every atom
				if (this->_sellectHistory[i].z != -1)
				{//if it is sellected
					this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y] = this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y] + jgn::vec3(0, d, 0);
				}
			}
		}
		else if (this->selected_change_hovered_axes == Z_AXIS)
		{
			jgn::vec3 dm = jgn::vec3(m.x - mprev.x, m.y - mprev.y, 0);
			jgn::vec3 b = this->selected_manipulate_base[3] - this->selected_manipulate_base[0];
			jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
			jgn::cpu_rotate(&b.x, &r.x, &b.x);
			float d = jgn::dotproduct(dm, b)*this->selected_translate_sensitivity;

			for (int i = 0; i < this->N_atoms; i++)
			{//for every atom
				if (this->_sellectHistory[i].z != -1)
				{//if it is sellected
					this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y] = this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y] + jgn::vec3(0, 0, d);
				}
			}
		}
		this->toggleselected_translate(true);
	}

}

void VSystem::rotate_selected(jgn::vec2& m /*mouse*/, jgn::vec2& mprev, float angle)
{
	if (this->isrotating_theselected)
	{
		if (this->selected_change_hovered_axes == X_AXIS)
		{
			jgn::vec3 dm = jgn::vec3(m.x - mprev.x, m.y - mprev.y, 0);
			jgn::vec3 b = this->selected_manipulate_base[1] - this->selected_manipulate_base[0];
			jgn::vec3 c = this->selected_manipulate_base[0];
			jgn::vec3 c_negative = jgn::vec3(0, 0, 0) - c;
			jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
			jgn::cpu_rotate(&b.x, &r.x, &b.x);
			jgn::vec3 dd = jgn::xproduct(dm, b)*this->selected_translate_sensitivity;
			float d = sqrt(jgn::dotproduct(dd, dd));
			if (dd.z < 0)
				d = -d;
			jgn::vec3 rs = jgn::vec3(d, 0, 0);
			if (angle != 0)
			{
				rs.x = angle;
			}

			for (int i = 0; i < this->N_atoms; i++)
			{//for every atom
				if (this->_sellectHistory[i].z != -1)
				{//if it is sellected
					jgn::cpu_translate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &c_negative.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
					jgn::cpu_rotate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &rs.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
					jgn::cpu_translate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &c.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
				}
			}
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[0].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[0].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[0].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[1].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[1].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[1].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[2].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[2].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[2].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//
			//vs.setSimulationBox(vs._isimulationBox);
		}
		else if (this->selected_change_hovered_axes == Y_AXIS)
		{
			jgn::vec3 dm = jgn::vec3(m.x - mprev.x, m.y - mprev.y, 0);
			jgn::vec3 b = this->selected_manipulate_base[2] - this->selected_manipulate_base[0];
			jgn::vec3 c = this->selected_manipulate_base[0];
			jgn::vec3 c_negative = jgn::vec3(0, 0, 0) - c;
			jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
			jgn::cpu_rotate(&b.x, &r.x, &b.x);
			jgn::vec3 dd = jgn::xproduct(dm, b)*this->selected_translate_sensitivity;
			float d = sqrt(jgn::dotproduct(dd, dd));
			if (dd.x < 0)
				d = -d;
			jgn::vec3 rs = jgn::vec3(0, d, 0);
			if (angle != 0)
			{
				rs.y = angle;
			}

			for (int i = 0; i < this->N_atoms; i++)
			{//for every atom
				if (this->_sellectHistory[i].z != -1)
				{//if it is sellected
					jgn::cpu_translate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &c_negative.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
					jgn::cpu_rotate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &rs.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
					jgn::cpu_translate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &c.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
				}
			}
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[0].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[0].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[0].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[1].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[1].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[1].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[2].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[2].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[2].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//
			//vs.setSimulationBox(vs._isimulationBox);
		}
		else if (this->selected_change_hovered_axes == Z_AXIS)
		{
			jgn::vec3 dm = jgn::vec3(m.x - mprev.x, m.y - mprev.y, 0);
			jgn::vec3 b = this->selected_manipulate_base[3] - this->selected_manipulate_base[0];
			jgn::vec3 c = this->selected_manipulate_base[0];
			jgn::vec3 c_negative = jgn::vec3(0, 0, 0) - c;
			jgn::vec3 r = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);
			jgn::cpu_rotate(&b.x, &r.x, &b.x);
			jgn::vec3 dd = jgn::xproduct(dm, b)*this->selected_translate_sensitivity;
			float d = sqrt(jgn::dotproduct(dd, dd));
			if (dd.y < 0)
				d = -d;
			jgn::vec3 rs = jgn::vec3(0, 0, d);
			if (angle != 0)
			{
				rs.z = angle;
			}

			for (int i = 0; i < this->N_atoms; i++)
			{//for every atom
				if (this->_sellectHistory[i].z != -1)
				{//if it is sellected
					jgn::cpu_translate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &c_negative.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
					jgn::cpu_rotate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &rs.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);
					jgn::cpu_translate(&this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x, &c.x, &this->group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x);

				}
			}
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[0].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[0].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[0].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[0].x);
			//
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[1].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[1].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[1].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[1].x);
			//
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[2].x, &c_negative.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//jgn::cpu_rotate(&this->group[this->_isimulationBox].primitiveVec[2].x, &rs.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//jgn::cpu_translate(&this->group[this->_isimulationBox].primitiveVec[2].x, &c.x, &this->group[this->_isimulationBox].primitiveVec[2].x);
			//
			//vs.setSimulationBox(vs._isimulationBox);
		}
		this->toggleselected_rotate(true);
	}
}


void VSystem::setSimulationBox(int s)
{
	this->_isimulationBox = s;
	this->_updateSimulationBox();
	vs.simulationboxVolume = jgn::volume(vs.simulationBoxEdges[1], vs.simulationBoxEdges[2], vs.simulationBoxEdges[3]);
}
void VSystem::undoSellect()
{
	if (_sellectHistory2undo > -1)
	{
		for (int i = 0; i < this->N_atoms; i++)
		{
			if (this->_sellectHistory[i].z == this->_sellectHistory2undo)
			{
				this->_sellectHistory[i].z = -1;
				this->group[this->_sellectHistory[i].x].isSelected[this->_sellectHistory[i].y] = false;
			}
		}
		this->_sellectHistory2undo--;
	}
}
void VSystem::_updateSimulationBox()
{
	this->simulationBoxEdges[0] = jgn::vec3(0, 0, 0);
	this->simulationBoxEdges[1] = this->group[this->_isimulationBox].primitiveVec[0];
	this->simulationBoxEdges[2] = this->group[this->_isimulationBox].primitiveVec[1];
	this->simulationBoxEdges[3] = this->group[this->_isimulationBox].primitiveVec[2];
	this->simulationBoxEdges[4] = this->group[this->_isimulationBox].primitiveVec[0];
	this->simulationBoxEdges[4] = this->simulationBoxEdges[4] + this->group[this->_isimulationBox].primitiveVec[2];
	this->simulationBoxEdges[5] = this->group[this->_isimulationBox].primitiveVec[1];
	this->simulationBoxEdges[5] = this->simulationBoxEdges[5] + this->group[this->_isimulationBox].primitiveVec[2];
	this->simulationBoxEdges[6] = this->simulationBoxEdges[5] + this->simulationBoxEdges[1];
	this->simulationBoxEdges[7] = this->simulationBoxEdges[2] + this->simulationBoxEdges[1];

}

void VSystem::_drawSimulationBox()
{
	glLineWidth(1);
	GLfloat mat_ambient[] = { 0,0,0,1 };
	GLfloat mat_deffuse[] = { 0,0,0,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

	unsigned int indexes[24] = {0,1,
								0,2,
								0,3,
								3,5,
								2,5, 
								3,4,
								4,6,
								5,6,
								2,7,
								7,1,
								4,1,
								6,7 };

	jgn::vec3 sb[8];
	sb[0] = this->simulationBoxEdges[0] / (Svmax + 5);
	sb[1] = this->simulationBoxEdges[1] / (Svmax + 5);
	sb[2] = this->simulationBoxEdges[2] / (Svmax + 5);
	sb[3] = this->simulationBoxEdges[3] / (Svmax + 5);
	sb[4] = this->simulationBoxEdges[4] / (Svmax + 5);
	sb[5] = this->simulationBoxEdges[5] / (Svmax + 5);
	sb[6] = this->simulationBoxEdges[6] / (Svmax + 5);
	sb[7] = this->simulationBoxEdges[7] / (Svmax + 5);
	glVertexPointer(3, GL_FLOAT, 0, &sb[0].x);
	glNormalPointer(GL_FLOAT, 0, &sb[0].x);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, indexes);

}


void VSystem::cut()
{
	for (int g = 0; g < this->N_groups; g++)
	{
		//#pragma omp parallel for firstprivate(g, S1v, S2v, S3, S1i, S2i, S3i, CustomSurfacesCount, i, CustomSurfaces, shperes_on, Right_Hexagonal, nanotube, CustomSurfacesOn, vacuum, Right_Hexagonal_height, figure_1, Rod_like)
		for (int ii = 0; ii < this->group[g].N_atoms; ii++)
		{
			float tr[] = { -(sized[0] / 2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].x + vs.original->group[vs._isimulationBox].primitiveVec[1].x + vs.original->group[vs._isimulationBox].primitiveVec[2].x),
				-(sized[1] / 2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].y + vs.original->group[vs._isimulationBox].primitiveVec[1].y + vs.original->group[vs._isimulationBox].primitiveVec[2].y),
				-(sized[2] / 2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].z + vs.original->group[vs._isimulationBox].primitiveVec[1].z + vs.original->group[vs._isimulationBox].primitiveVec[2].z) };
			jgn::cpu_translate(&this->group[g].position[ii].x, tr, &this->group[g].position[ii].x);


			float *p = &(this->group[g].position[ii].x);
			if (nanotube)
			{
				this->group[g].iscut[ii] = false;
			}
			else if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
			{
				float ori[] = { 0,0,0 };
				if (vacuum^(sqrt(jgn::dist3dSquare(this->group[g].position[ii].x, ori[0])) < rad))
				{
					this->group[g].iscut[ii] = false;
				}
				else
				{
					this->group[g].iscut[ii] = true;
				}
			}
			else if (CustomSurfacesOn)
			{
				//std::cout << CustomSurfacesCount << std::endl;
				if (CustomSurfacesCount == 0)
				{
					this->group[g].iscut[ii] = false;
				}
				else
				{

					for (i = 0; i < CustomSurfacesCount; i++)
					{
						if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) < 0)
						{

						}
						else
						{
							i = 1000;
						}

					}

					if (i == CustomSurfacesCount)
					{
						this->group[g].iscut[ii] = false;
					}
					else {
						this->group[g].iscut[ii] = true;
					}
				}
			}
			//else if (jgn_supercell)			
			else
			{

				if (Right_Hexagonal == -1)
				{
					if (vacuum ^ (abs(p[2]) < Right_Hexagonal_height && (S1i[0] * abs(p[0]) <= S2v * 0.86602540378) && S2i[0] * abs(p[0]) / 1.73205 + S2i[0] * abs(p[1]) <= S2v &&
						(S1i[0] * abs(p[1]) < S1v *0.86602540378) && S2i[0] * abs(p[0]) + S1i[0] * abs(p[1]) / 1.73205 < S1v))
					{
						for (i = 0; i < CustomSurfacesCount; i++)
						{
							if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
							{

							}
							else
							{
								i = 1000;
							}

						}

						if (i == CustomSurfacesCount)
						{
							this->group[g].iscut[ii] = false;
						}
						else {
							this->group[g].iscut[ii] = true;
						}
					}
					else {
						this->group[g].iscut[ii] = true;
					}
				}
				else
				{
					if (vacuum ^ ((S1i[0] * figure_1*abs(p[0]) <= S1v) &&
						(S1i[0] * Right_Hexagonal*Rod_like* abs(p[2]) <= S1v) &&
						(S1i[0] * figure_1*abs(p[1]) <= S1v) &&
						Rod_like*(S2i[0] * abs(p[0]) + S2i[0] * Right_Hexagonal* abs(p[2])) <= S2v &&
						S2i[0] * figure_1* abs(p[0]) + S2i[0] * figure_1* abs(p[1]) <= S2v &&
						Rod_like*(S2i[0] * Right_Hexagonal* abs(p[2]) + S2i[0] * abs(p[1])) <= S2v &&
						Right_Hexagonal*(S3i[0] * abs(p[0]) + S3i[1] * abs(p[2]) + S3i[2] * abs(p[1])) <= S3v))
					{
						for (i = 0; i < CustomSurfacesCount; i++)
						{
							if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
							{
								
							}
							else
							{
								i = 1000;
							}

						}

						if (i == CustomSurfacesCount)
						{
							this->group[g].iscut[ii] = false;
						}
						else {
							this->group[g].iscut[ii] = true;
						}
					}
					else {
						this->group[g].iscut[ii] = true;
					}

				}
			}

			tr[0] = -tr[0];
			tr[1] = -tr[1];
			tr[2] = -tr[2];
			jgn::cpu_translate(&this->group[g].position[ii].x, tr, &this->group[g].position[ii].x);
		}
	}
	this->updateinfo();
}

void VSystem::selected_change_radius(jgn::string r)
{
	float newradius = 0;
	//check if is number
	if (r.isnumber())
	{
		newradius = std::stof(r);
	}
	else {
		return;
	}

	for (int g = 0; g < this->N_groups; g++)
	{//for every group
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{//for every atom of the group
			if (this->group[g].isSelected[i])
			{//if it is selected
				this->group[g].radius[i] = newradius;
			}
		}
	}
	//for (int i = 0; i < this->N_atoms; i++)
	//{//for every atom
	//	if (this->_sellectHistory[i].z != -1)
	//	{//if it is sellected
	//		this->group[this->_sellectHistory[i].x].radius[this->_sellectHistory[i].y] = newradius;
	//	}
	//}
}

void VSystem::selected_change_sd(jgn::string sd)
{
	//check if we have 3 letter T or F
	for (int i = 0; i < 3; i++)
	{
		if (sd.at(i) != 't' && sd.at(i) != 'T' && sd.at(i) != 'f' && sd.at(i) != 'F')
		{
			return;
		}
	}

	for (int i = 0; i < this->N_atoms; i++)
	{//for every atom
		if (this->_sellectHistory[i].z != -1)
		{//if it is sellected
			for (int j = 0; j < 3; j++)//stupid proof
				sd.at(j) == 't' || sd.at(j) == 'T' ? this->group[this->_sellectHistory[i].x].selective_dynamics[this->_sellectHistory[i].y].at(j) = 'T' : this->group[this->_sellectHistory[i].x].selective_dynamics[this->_sellectHistory[i].y].at(j) = 'F';
		}
	}
}
void VSystem::toggleselected_translate(bool state)
{
	this->selected_translate_ison = state;
	if (selected_translate_ison)
	{//calculate selected_translate_base axis
		this->selected_rotate_ison = false;
		jgn::vec3 v = jgn::vec3(0.0, 0.0, 0.0);
		int Nsellected = 0;
		float max_x = FLT_MIN;
		float max_y = FLT_MIN;
		float max_z = FLT_MIN;

		for (int i = 0; i < this->N_atoms; i++)
		{//for every atom
			if (this->_sellectHistory[i].z != -1)
			{//if it is sellected
				Nsellected++;
				v = v + vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y];
				if (vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x > max_x)
					max_x = vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x;
				if (vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].y > max_y)
					max_y = vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].y;
				if (vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].z > max_z)
					max_z = vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].z;
			}
		}
		v = v / Nsellected;
		max_x -= v.x;
		max_y -= v.y;
		max_z -= v.z;
		this->selected_manipulate_base[0] = v;
		this->selected_manipulate_base[1] = v + jgn::vec3(max_x + 10, 0, 0);
		this->selected_manipulate_base[2] = v + jgn::vec3(0, max_y + 10, 0);
		this->selected_manipulate_base[3] = v + jgn::vec3(0, 0, max_z + 10);
	}
}

void VSystem::toggleselected_rotate(bool state)
{
	this->selected_rotate_ison = state;
	if (selected_rotate_ison)
	{//calculate rotate_translate_base axis
		this->selected_translate_ison = false;
		jgn::vec3 v = jgn::vec3(0.0, 0.0, 0.0);
		int Nsellected = 0;
		float max_x = FLT_MIN;
		float max_y = FLT_MIN;
		float max_z = FLT_MIN;

		for (int i = 0; i < this->N_atoms; i++)
		{//for every atom
			if (this->_sellectHistory[i].z != -1)
			{//if it is sellected
				Nsellected++;
				v = v + vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y];
				if (vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x > max_x)
					max_x = vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].x;
				if (vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].y > max_y)
					max_y = vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].y;
				if (vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].z > max_z)
					max_z = vs.group[this->_sellectHistory[i].x].position[this->_sellectHistory[i].y].z;
			}
		}
		v = v / Nsellected;
		max_x -= v.x;
		max_y -= v.y;
		max_z -= v.z;
		this->selected_manipulate_base[0] = v;
		this->selected_manipulate_base[1] = v + jgn::vec3(max_x + 10, 0, 0);
		this->selected_manipulate_base[2] = v + jgn::vec3(0, max_y + 10, 0);
		this->selected_manipulate_base[3] = v + jgn::vec3(0, 0, max_z + 10);
	}
}

void VSystem::selected_change_element(jgn::string elem)
{
	//for (int i = 0; i < this->group[0]._N_types; i++)
	//{
	//	std::cout << this->group[0]._alltype[i] << std::endl;
	//	std::cout << this->group[0].N_atoms_per_type[i] << std::endl;
	//}
	float atomic_number = 0;
	float atomic_weight = 0;
	ole1 = 0;
	periodic_table = fopen("periodic_table.jgn", "r");
	//find atomic number and weight
	while (ole1 == 0) {
		if (!std::fgets(s1, 50, periodic_table) || std::ferror(periodic_table) || std::feof(periodic_table))
			return;
		token1 = strtok(s1, " ");
		if (strcmp(elem.c_str(), token1) == 0) {

			token1 = strtok(NULL, " ");
			my_direct[0 + 5 * ole] = std::atof(token1);
			atomic_number = std::atof(token1);
			token1 = strtok(NULL, " ");
			atomic_weight = std::atof(token1);
			ole1 = 1;
		}
	}
	fclose(periodic_table);



	//for (int i = 0; i < this->N_atoms; i++)
	for (int g = 0; g < vs.N_groups; g++)
		for (int i = 0; i < vs.group[g].N_atoms; i++)
	{//for every atom
		if (this->group[g].isSelected[i])
		{//if it is sellected

			int exists = -1;
			for (int j = 0; j < this->group[g]._N_types; j++)
			{
				//std::cout << elem << " " << this->group[this->_sellectHistory[i].x]._alltype[j] << std::endl;
				//if (!std::strcmp(this->group[this->_sellectHistory[i].x]._alltype[j].c_str(), elem.c_str()))
				if (this->group[g]._alltype[j].compare(elem) == 0)
				{
					exists = j;
					break;
				}
			}

			if (exists != -1)
			{
				this->group[g].N_atoms_per_type[exists]++;
				for (int j = 0; j < this->group[g]._N_types; j++)
				{
					if (!std::strcmp(this->group[g].type[i].c_str(), this->group[g]._alltype[j].c_str()))
					{
						this->group[g].N_atoms_per_type[j]--;
						if (this->group[g].N_atoms_per_type[j] == 0)
						{
							this->group[g].N_atoms_per_type.erase(this->group[g].N_atoms_per_type.begin() + j);
							this->group[g]._N_types--;
						}
						break;
					}
				}
			}
			else
			{//if it doesn't exist
				this->group[g]._N_types += 1;
				exists = this->group[g]._N_types - 1;
				this->group[g].N_types(this->group[g]._N_types);
				this->group[g].N_atoms_per_type.reserve(this->group[g]._N_types);
				this->group[g]._alltype.emplace_back(elem);
				this->group[g].N_atoms_per_type.emplace_back(1);
				for (int j = 0; j < this->group[g]._N_types; j++)
				{
					if (!std::strcmp(this->group[g].type[i].c_str(), this->group[g]._alltype[j].c_str()))
					{
						this->group[g].N_atoms_per_type[j]--;
						if (this->group[g].N_atoms_per_type[j] == 0)
						{
							this->group[g].N_atoms_per_type.erase(this->group[g].N_atoms_per_type.begin() + j);
							this->group[g]._N_types--;
						}
						break;
					}
				}
			}
			this->group[g].type[i] = elem;
			this->group[g].number[i] = atomic_number;
			this->group[g].weight[i] = atomic_weight;
			this->group[g].color[i] = jgn::vec3(fmod(atomic_weight, 1.5), fmod(atomic_number, 0.92), fmod(100 * fmod(atomic_weight, 1.5) * fmod(atomic_number, 0.92), 0.8));
		}
	}
	this->unsellectAll();

	//for (int i = 0; i < this->group[0]._N_types; i++)
	//{
	//	std::cout << this->group[0]._alltype[i] << std::endl;
	//	std::cout << this->group[0].N_atoms_per_type[i] << std::endl;
	//}
}

void VSystem::updateinfo()
{

	//zero all counts
	for (int i = 0; i < this->N_types; i++)
	{
		this->N_atoms_per_type[i] = 0;
	}
	//check if number of types changed inside the groups
	int more_memory = 0;
	for (int g = 0; g < this->N_groups; g++)
	{
		if (this->group[g]._N_types != this->group[g].N_atoms_per_type.size())
		{
			more_memory += this->group[g]._N_types - this->group[g].N_atoms_per_type.size();
		}
	}
	//if we need more memory allocate it
	if (more_memory > 0)
	{
		///this->N_types += more_memory;
		this->N_atoms_per_type.reserve(this->N_types + more_memory);
		this->color_per_type.reserve(this->N_types + more_memory);
		this->weight_per_type.reserve(this->N_types + more_memory);
		this->types.reserve(this->N_types + more_memory);
	}
	//now count the atoms
	for (int g = 0; g < this->N_groups; g++)
	{
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{
			if (!this->group[g].iscut[i] && !this->group[g].isdeleted[i])
			{
			
			bool exists = false;
			for (int j = 0; j < this->N_types; j++)
			{//check if this element if new
				if (std::strcmp(this->types[j].c_str(), this->group[g].type[i].c_str()) == 0)
				{//if not
					this->N_atoms_per_type[j]++;
					exists = true;
					break;
				}
			}
			if (!exists)
			{
				this->N_types++;
				this->N_atoms_per_type.emplace_back(1);
				this->color_per_type.emplace_back(this->group[g].color[i]);
				this->weight_per_type.emplace_back(this->group[g].weight[i]);
				this->types.emplace_back(this->group[g].type[i]);
			}
		}
		}
	}
	//delete elements with 0 count
	for (int g = 0; g < vs.N_groups; g++)
		for (int i = 0; i < vs.group[g]._N_types; i++)
		{
			if (this->group[g].N_atoms_per_type[i] == 0)
			{
				this->group[g]._N_types -= 1;
				this->group[g].color_per_type.erase(this->group[g].color_per_type.begin() + i);
				this->group[g].weight_per_type.erase(this->group[g].weight_per_type.begin() + i);
				this->group[g].N_atoms_per_type.erase(this->group[g].N_atoms_per_type.begin() + i);
				this->group[g]._alltype.erase(this->group[g]._alltype.begin() + i);
				i--;
			}
		}
	for (int i = 0; i < this->N_types; i++)
	{
		//std::cout << this->N_atoms_per_type[i] << std::endl;
		if (this->N_atoms_per_type[i] == 0)
		{
			this->N_types -= 1;
			this->N_atoms_per_type.erase(this->N_atoms_per_type.begin() + i);
			this->types.erase(this->types.begin() + i);
			this->color_per_type.erase(this->color_per_type.begin() + i);
			this->weight_per_type.erase(this->weight_per_type.begin() + i);
			i--;
		}
	}
}





///////////////////////////////////////////////////////////////////////////////////////////
//TODO: a huge funtion that needs to be changes

void drawMoldsLines(float *p, float *p1)
{

	glTranslatef((sized[0]/2)*(vs.original->group[vs._isimulationBox].primitiveVec[0].x + vs.original->group[vs._isimulationBox].primitiveVec[1].x + vs.original->group[vs._isimulationBox].primitiveVec[2].x)/(Svmax+5),
		(sized[1]/2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].y + vs.original->group[vs._isimulationBox].primitiveVec[1].y + vs.original->group[vs._isimulationBox].primitiveVec[2].y) / (Svmax + 5),
		(sized[2]/2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].z + vs.original->group[vs._isimulationBox].primitiveVec[1].z + vs.original->group[vs._isimulationBox].primitiveVec[2].z) / (Svmax + 5)) ;
	glRotatef(90, 1, 0, 0);
	glBegin(GL_LINES);
	if (jgn_supercell || nanotube)
	{
	}
	else if (CustomSurfacesOn)
	{
		if (DrawDistanceLine)
		{
			colr[0] = 0;
			colr[1] = 0;
			colr[2] = 0;
			GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
			GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
			ole3 = ClickedForDistance[0];
			p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
			p[1] = crystal[3 + 5 * ole3] / (Svmax + 5);
			p[2] = crystal[4 + 5 * ole3] / (Svmax + 5);
			//cout << ClickedForDistance[0] << " " << ClickedForDistance[1] << endl;
			//cout << "p = " << p[0] << " " << p[1] << " " << p[2] << endl;
			ole3 = ClickedForDistance[1];
			glVertex3fv(p1);
			glEnd();

		}
	}
	else if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
	{
		glColor3f(0, 0, 0);

		vec[0] = 0;
		vec[1] = (rad + 5) / (Svmax + 5);
		vec[2] = 0;

		glVertex3fv(vec);
		vec[1] = -(rad + 5) / (Svmax + 5);
		glVertex3fv(vec);

		vec[0] = (rad + 5) / (Svmax + 5);
		vec[1] = 0;
		glVertex3fv(vec);
		vec[0] = -(rad + 5) / (Svmax + 5);

		glVertex3fv(vec);
	}
	else if (figure_1 == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;
		int S3vb = S3v;



		if (2 * S2v - S3v >= S1v)
		{
			if (S3v < S2v)
			{
				S2v = S3v;
			}
			if (S3v < S1v)
			{
				S1v = S3v;
			}

			i = 1;
			j = 1;
			k = 1;

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);

			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			S1v = S1vb;
			S2v = S2vb;
		}
		else
		{
			if (2 * S2v < S3v)
			{
				S3v = S2v * 2;

			}
			if (S2v < S1v)
			{
				S1v = S2v;
			}

			i = 1;
			j = 1;
			k = 1;



			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			i = -1;
			j = 1;
			k = 1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = 1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = 1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = 1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = 1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			S1v = S1vb;
			S2v = S2vb;
			S3v = S3vb;

		}


	}
	else if (Rod_like == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;

		if (S3v < S2v)
		{
			S2v = S3v;
		}
		if (S2v < S1v)
		{
			S1v = S2v;
		}
		if (2 * S1v < S2v)
		{
			S2v = 2 * S1v;

		}


		i = 1;
		j = 1;
		k = 1;

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);



		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);

		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);

		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Right_Hexagonal == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;

		float asdf = (Right_Hexagonal_height + 0.5) / (Svmax + 5);


		if (float(S1v) / float(S2v) > 1.14814814815)
		{
			for (i = -1; i < 2; i = i + 2)
			{
				for (j = -1; j < 2; j = j + 2)
				{


					for (k = -1; k < 2; k = k + 2)
					{
						glVertex3f(i*float(S2v*0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));
						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, 0);

						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));
						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), 0, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));


						glVertex3f(0, j*asdf, k*float(S2v) / ((Svmax + 5)));
						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, -k * 0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));

						glVertex3f(0, j*asdf, k*float(S2v) / ((Svmax + 5)));
						glVertex3f(0, 0, k*float(S2v) / ((Svmax + 5)));
					}
				}
			}

		}
		else if (float(S1v) / float(S2v) < 0.86842105263)
		{
			for (i = -1; i < 2; i = i + 2)
			{
				for (j = -1; j < 2; j = j + 2)
				{
					for (k = -1; k < 2; k = k + 2)
					{
						glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));
						glVertex3f(0, j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));

						glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));
						glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), 0, i*float(S1v *0.866025404) / (Svmax + 5));


						glVertex3f(k*float(S1v) / ((Svmax + 5)), j*asdf, 0);
						glVertex3f(-k * 0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));

						glVertex3f(k*float(S1v) / ((Svmax + 5)), j*asdf, 0);
						glVertex3f(k*float(S1v) / ((Svmax + 5)), 0, 0);
					}
				}
			}

		}
		else
		{
			for (i = -1; i < 2; i = i + 2)
			{
				for (j = -1; j < 2; j = j + 2)
				{


					for (k = -1; k < 2; k = k + 2)
					{
						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), j*asdf, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));
						glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));


						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), j*asdf, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));

						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), j*asdf, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));
						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), 0, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));


						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, 0);
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));




						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), 0, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));


						glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));
						glVertex3f(0, j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));


						glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));
						glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), 0, k*(float(S1v) *0.866025404) / (Svmax + 5));

					}
				}
			}

		}



		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Scase == 1)
	{


		if (2 * S2v - S3v >= S1v)
		{



			i = 1;
			j = 1;
			k = 1;


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);


			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);

			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
		}

		else
		{
			i = 1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);


			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);

		}

	}
	else if (Scase == 2)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
	}
	else if (Scase == 3)
	{
		if (2 * S1v >= S3v)
		{
			i = 1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);

			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);

		}
		else {
			i = 1;
			j = 1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);



			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);

		}
	}
	else if (Scase == 4)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
	}
	else if (Scase == 5)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
	}
	else if (Scase == 6)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);


		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);
	}
	else if (Scase == 7)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);

		i = -1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
	}
	else if (Scase == 0)
	{

	}

	glEnd();

	glRotatef(-90, 1, 0, 0);
	glTranslatef(-(sized[0]/2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].x + vs.original->group[vs._isimulationBox].primitiveVec[1].x + vs.original->group[vs._isimulationBox].primitiveVec[2].x) / (Svmax + 5),
		-(sized[1]/2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].y + vs.original->group[vs._isimulationBox].primitiveVec[1].y + vs.original->group[vs._isimulationBox].primitiveVec[2].y) / (Svmax + 5),
		-(sized[2]/2) * (vs.original->group[vs._isimulationBox].primitiveVec[0].z + vs.original->group[vs._isimulationBox].primitiveVec[1].z + vs.original->group[vs._isimulationBox].primitiveVec[2].z) / (Svmax + 5));
}