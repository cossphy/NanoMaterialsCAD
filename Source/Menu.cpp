#include "Menu.h"
#include "JGN_StrokeCharacter.h"
#include "JGN_Windows.h"
#include <new>
#include "Cammera.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}
void Menu::init()
{
	menu.mainmenu = new Menu;
	menu.mainmenu->N_options = 2;
	menu.mainmenu->ischild = false;
	menu.mainmenu->element.reserve(menu.mainmenu->N_options);
	Menu::Element el;
	menu.mainmenu->element.emplace_back(el);
	menu.mainmenu->element[0].str = std::string("Edit Selected");
	menu.mainmenu->element[0].isgray = true;
	menu.mainmenu->element[0].hassubmenu = true;
	menu.editselected = new Menu;
	menu.editselected->ischild = true;
	menu.mainmenu->element[0].submenu = menu.editselected;
	menu.mainmenu->element[0].submenu->N_options = 5;
	menu.mainmenu->element[0].submenu->element.reserve(5);
	menu.editselected->element.emplace_back(el);
	menu.mainmenu->element[0].submenu->element[0].str = std::string("Translate");
	menu.editselected->element.emplace_back(el);
	menu.mainmenu->element[0].submenu->element[1].str = std::string("Rotate");
	menu.editselected->element.emplace_back(el);
	menu.mainmenu->element[0].submenu->element[2].str = std::string("Change element");
	menu.editselected->element.emplace_back(el);
	menu.mainmenu->element[0].submenu->element[3].str = std::string("Change radius");
	menu.editselected->element.emplace_back(el);
	menu.mainmenu->element[0].submenu->element[4].str = std::string("Selective dynamics");
	for (int i = 0; i < 5; i++)
	{
		menu.mainmenu->element[0].submenu->element[i].isgray = false;
		menu.mainmenu->element[0].submenu->element[i].hassubmenu = false;
		menu.mainmenu->element[0].submenu->parent = &menu.mainmenu->element[0];
	}

	menu.mainmenu->element.emplace_back(el);
	menu.mainmenu->element[1].str = std::string("System Information");
	menu.mainmenu->element[1].hassubmenu = false;
	menu.mainmenu->element[1].isgray = false;
}

void Menu::draw()
{
	if (this->show)
	{
		//draw background
		cam.loadorthomatrix();
		this->_drawbg(this->mainmenu);
		//write options, highlight options
		this->_drawoptions(this->mainmenu);
	}
}


bool Menu::hoverstatecheck(Menu* men, jgn::vec2 m)
{
	if (this->show)
	{

		for (int i = 0; i < men->N_options; i++)
			men->element[i].hoverstate = false;

		for (int i = 0; i < men->N_options; i++)
		{
			//if (m.x > this->coords.x && m.x < this->coords.x + 0.5 && m.y > this->coords.y - write::max_height*0.4 -0.01 - (i)*(write::max_height*0.4 + 0.02) && m.y < this->coords.y - write::max_height*0.4 -0.01 - (i - 1)*(write::max_height*0.4 + 0.02))
			if(m.x > men->coords.x && m.x < men->coords.x + 0.5 && m.y <+men->coords.y - i * (write::max_height*0.4 + 0.02) - write::max_height*0.4 - 0.02 + 1 * (write::max_height*0.4 + 0.02) && m.y > +men->coords.y - i * (write::max_height*0.4 + 0.02) - write::max_height*0.4 -0.015)
			{
				men->chosen = i;
				if(men->element[men->prevchosen].hassubmenu)
					men->element[men->prevchosen].submenu->show = false;
				if (men->element[i].hassubmenu)
					men->element[i].submenu->show = true;

				men->element[i].hoverstate = true;
				men->hoverstate = true;
				if (men->element[i].hoverstate != men->element[i].prevhoverstate)
				{
					men->element[i].prevhoverstate = true;
					JGN_PostRedisplay();
				}
				men->prevchosen = men->chosen;
				return true;
			}
			else if (men->element[i].hoverstate != men->element[i].prevhoverstate)
			{
				men->element[i].prevhoverstate = false;
				men->hoverstate = false;
				if (men->element[i].hassubmenu)
				JGN_PostRedisplay();
			}
		}
	}
	return men->hoverstate;
}

void Menu::_drawbg(Menu* men)
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);
	glLoadIdentity();
	glTranslatef(men->coords.x, men->coords.y - write::max_height*0.4, 5);
	glBegin(GL_QUADS);
	glVertex2f(0, write::max_height*0.4);
	glVertex2f(0.5, write::max_height*0.4);
	glVertex2f(0.5, -0.01 - ((*men).N_options - 1)*(write::max_height*0.4 + 0.02));
	glVertex2f(0, -0.01 - ((*men).N_options - 1)*(write::max_height*0.4 + 0.02));
	glEnd();
	glColor3f(1, 0, 0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(0, write::max_height*0.4);
	glVertex2f(0.5, write::max_height*0.4);
	glVertex2f(0.5, -0.01 - ((*men).N_options - 1)*(write::max_height*0.4 + 0.02));
	glVertex2f(0, -0.01 - ((*men).N_options - 1)*(write::max_height*0.4 + 0.02));
	glVertex2f(0.5, write::max_height*0.4);
	glVertex2f(0.5, -0.01 - ((*men).N_options - 1)*(write::max_height*0.4 + 0.02));
	glVertex2f(0, -0.01 - ((*men).N_options - 1)*(write::max_height*0.4 + 0.02));
	glVertex2f(0, write::max_height*0.4);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Font);
	glScalef(0.4, 0.4, 0.4);
}

void Menu::_drawoptions(Menu* men)
{
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < (*men).N_options; i++)
	{
		glLoadIdentity();
		glTranslatef(men->coords.x, men->coords.y - i * (write::max_height*0.4 + 0.02) - write::max_height*0.4, 6);
		glColor3f(1, 0, 0);
		//highlight
		if (men->element[i].hoverstate)
		{
			glBindTexture(GL_TEXTURE_2D, button1ID);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(0, -0.015);
			glTexCoord2f(1, 0);
			glVertex2f(0.5, -0.015);
			glTexCoord2f(1, 1);
			glVertex2f(0.5, -0.02 + 1 * (write::max_height*0.4 + 0.02));
			glTexCoord2f(0, 1);
			glVertex2f(0, -0.02 + 1 * (write::max_height*0.4 + 0.02));
			glEnd();
			glBindTexture(GL_TEXTURE_2D, Font);

		}
		if (men->element[i].hassubmenu) 
			if( men->element[i].submenu->show)
		{
				//draw background
				menu._drawbg(men->element[i].submenu);

				//write options, highlight options
				menu._drawoptions(men->element[i].submenu);
		}
		glLoadIdentity();
		glTranslatef(men->coords.x, men->coords.y - i * (write::max_height*0.4 + 0.02) - write::max_height*0.4, 6);
		glScalef(0.4, 0.4, 0.4);
		glColor3f(1, 1, 1);
		write::string(men->element[i].str.c_str());
		if (men->element[i].hassubmenu)
		{
			glLoadIdentity();
			glTranslatef(men->coords.x + 0.5, men->coords.y - i * (write::max_height*0.4 + 0.02) - write::max_height*0.4, 6);
			glScalef(0.4, 0.4, 0.4);
			write::rtl::character('>');
		}
	}
	glLoadIdentity();
}

void Menu::shownon()
{
	this->mainmenu->show = false;
	for (int i = 0; i < this->mainmenu->N_options; i++)
	{
		if (this->mainmenu->element[i].hassubmenu)
			this->mainmenu->element[i].submenu->show = false;
	}
}

jgn::vec2 Menu::clicked(jgn::vec2 m)
{
	jgn::vec2 out = jgn::vec2(Menu::NONE, Menu::NONE);
	for (int i = 0; i < menu.mainmenu->N_options; i++)
	{
		if (menu.mainmenu->element[i].hoverstate)
		{
			out.x = i;
			return out;
		}
	}
	if(menu.editselected->show)
		for (int i = 0; i < menu.editselected->N_options; i++)
		{
			if (menu.editselected->element[i].hoverstate)
			{
				out.x = Menu::EDIT_SELECTED;
				out.y = i;
				return out;
			}
		}
}
