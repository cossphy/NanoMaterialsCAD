#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#define N_OPTIONS 2

class Menu
{
public:
	Menu();
	~Menu();

	enum Options
	{
		EDIT_SELECTED,
		SYSTEM_INFO,
		NONE
	};
	enum EDIT_SELECTED
	{
		TRANSLATE,
		ROTATE,
		CHANGE_ELEMENT,
		CHANGE_RADIUS,
		SELECTIVE_DYNAMICS
	};
	class Element
	{
	public:
		Element() {}
		~Element() {}
		std::string str;
		bool hassubmenu;
		bool isgray;
		Menu* submenu;
		bool hoverstate = false;
		bool prevhoverstate = false;
	};
	Element* parent;
	jgn::vec2 coords;//the top left corner of the menu
	int N_options;
	std::vector<Element> element;
	//subelements
	Menu* mainmenu;
	Menu* editselected;
	bool show = false;
	bool ischild;
	int chosen = -1;//the element that is curently hovered or focused at that specific menu
	int prevchosen = 0;

	float fontscale = 0.4;
	void init();
	void draw();
	void _drawbg(Menu* men);//draw the back ground
	void _drawoptions(Menu* men);//draw the back ground
	bool hoverstatecheck(Menu* men, jgn::vec2 m);
	bool hoverstate;
	void shownon();
	jgn::vec2 clicked(jgn::vec2 m);//mouse as input, (enum mainmOptionsenu, enum EDIT_SELECTED) as outpus

}EXT menu;

