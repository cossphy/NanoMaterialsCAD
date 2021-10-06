#pragma once

#include "stdafx.h"

////////////////////////////////
//helping classes
class Group
{
public:
	Group() {};
	void _Group(int N_a, int N_t) { N_atoms = N_a; _N_types = N_t; _reserve(N_a); };/*(number_of_atoms, number_of_types)*/
	~Group() {};

	unsigned int N_atoms;//number of atoms
	std::vector<unsigned int> N_atoms_per_type;//number of atoms
	std::vector<jgn::vec3> color_per_type;//color of atoms
	std::vector<float> weight_per_type;
	jgn::vec3 primitiveVec[3];//the primitiveVec
	jgn::vec3 primitiveBase[3];//the primitiveVec/|primitiveVec|
	std::vector<jgn::vec3> position;
	std::vector<jgn::vec3> fractional;//fractional coordinats
	std::vector<jgn::string> type;
	int _N_types;
	int _prev_N_types;
	std::vector<jgn::string> _alltype;//write all the individual types
	std::vector<jgn::string> selective_dynamics;
	std::vector<jgn::vec3> color;
	std::vector<float> number;//atomic number
	std::vector<float> weight;//atomic weight
	std::vector<float> radius;
	std::vector<bool> isSelected;
	std::vector<bool> isdeleted;
	std::vector<bool> ishovered;
	std::vector<bool> iscut;//if the atoms is cut by a surface

	void _reserve(const unsigned int N_a);
	void N_types(const unsigned int N_t);
	
};


class VSystem
{
public:

	VSystem();
	VSystem(VSystem* other);
	~VSystem();

	VSystem* original;//this is the original system without the edit of the user
	int N_types = 0;//#N of different elements
	std::vector<jgn::string> types;//name of different elements
	int N_atoms = 0;// total #N of the system
	std::vector<int> N_atoms_per_type;
	std::vector<jgn::vec3> color_per_type;//color of atoms
	std::vector<float> weight_per_type;
	jgn::vec2 hoveredatom = jgn::vec2(-1, -1);// group,atoms of the atom that is currently hovered
	jgn::vec2 hoveredatom_prev = jgn::vec2(-1, -1);
	float simulationboxVolume;
	bool noupdate = false;


	int N_groups = 0;//#N of groups
	int _isimulationBox = 0;//the group that its simulation box is used
	jgn::vec3 simulationBoxEdges[8];//the simumation box 2 draw;
	std::vector<jgn::vec3> _sellectHistory;//(group,atom,history)
	int _sellectHistory2undo = 1;//


	std::vector<Group> group;
	std::vector<int> deletedHistory;

	void draw();
	void cut();
	void _drawSimulationBox();
	void _updateSimulationBox();
	void setSimulationBox(int s);
	void _drawBase();
	void _drawDistanceToolLine();
	void _drawatoms();
	void _drawsysteminfo();
	void unsellectAll();
	void undoSellect();
	void selected_change_element(jgn::string elem);
	void selected_change_radius(jgn::string r);
	void selected_change_sd(jgn::string sd);
	void toggleselected_translate(bool state);
	void toggleselected_rotate(bool state);
	bool selected_rotate_ison = false;
	void rotate_selected(jgn::vec2& m, jgn::vec2& mprev, float angle = 0);//take the mouse - mouse.prev, optional angle input
	bool selected_translate_ison = false;
	jgn::vec3 selected_manipulate_base[4];
	float selected_translate_sensitivity = 1;
	int selected_change_hovered_axes = -1;
	bool istranslating_theselected = false;
	bool isrotating_theselected = false;
	void translate_selected(jgn::vec2& m, jgn::vec2& mprev);//take the mouse - mouse.prev
	void selected_change_hover_check(jgn::vec2 m);
	jgn::vec2 _hoveringAnatom(jgn::vec2 m);
	void selected_change_draw();
	void updateinfo();
	void restart();
	void reserve(const unsigned int sx, const unsigned int sy, const unsigned int sz);// reserve for supercell sx,sy,sz
	class Grouplist
	{
	public:
		bool hovering_prev = false;
		bool hovering = false;
		bool open = false;//if the list is showing
		void draw();
		bool checkhoverstatus(const jgn::vec2 m);// the input is the mouse
		class Options
		{
		public:
			int hovering_prev = -1;
			int hovering = -1;
			bool checkhoverstatus(const jgn::vec2 m);// the input is the mouse
		} options;
	} grouplist;
}EXT vs;

EXT VSystem __backup;


