#pragma once
#include "stdafx.h"
#include "VSystem.h"
#include "JGN_Resource.h"

class Utool
{//use tool
public:
	bool sellect();
	void distance();
	jgn::vec2 _singlesellect();//single select and returns if there group,atom that was clicked
	bool _multisellect();//real time select and returns if there are any sellected items
};

class ToolBar
{
public:
	ToolBar();
	~ToolBar();

	enum class Tool
	{
		ROTATE,
		SELECT,
		TRANSLATE,
		DISTANCE,
		NONE
	};
	const int N_tools = 4;//Number of tools
	jgn::vec3 position[4/*N_tools*/][4];//all corners of the button//1 2
																   //0 3
	const float size = 0.15;
	Tool sellectedTool = Tool::ROTATE;//0=rotate 1=
	Tool downclicked = Tool::NONE;
	Utool usetool;
	int _Nsellectedfordistance = 0;//how many atoms are currently sellected for distance? values:0,1,2
	jgn::vec2 _sellectedfordistance[2];//group,atom that is sellected. -1=non sellected
	int hoveringTool = -1;
	int prevhoveringTool = -1;


	void draw();
	void _drawButton(const int i);
	void initPositions();
	bool toolclicked(const float x, const float y);//takes the mouse parameters, returns if the user clicked a tool
	bool tooldownclicked(const float x, const float y);
	bool hoveringAtool(const float x, const float y);//takes the mouse parameters, returns if the user hovers a tool
}EXT tb;

