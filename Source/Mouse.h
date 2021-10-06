#pragma once
#include "stdafx.h"

class Mouse
{
public:
	Mouse();
	~Mouse();
	jgn::vec2 pos;
	jgn::vec2 prevpos;
	bool isInside(jgn::vec4 sq);

}EXT mouse;

