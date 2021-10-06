#pragma once
#include "stdafx.h"


class virtualwindow
{
public:
	virtualwindow();
	~virtualwindow();

	void in();
	bool show = false;
	jgn::string in_message;
	jgn::vec3 in_message_translate;
	jgn::string in_field = "";
	void draw();
}EXT wn;

