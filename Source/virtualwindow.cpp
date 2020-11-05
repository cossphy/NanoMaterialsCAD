#include "virtualwindow.h"
#include "JGN_StrokeCharacter.h"


virtualwindow::virtualwindow()
{
}


virtualwindow::~virtualwindow()
{
}

void virtualwindow::draw()
{
	glDisable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_1D);
	if (!this->in_message.empty())
	{
		this->in();
		this->show = true;
	}
	else
	{
		this->show = false;
	}
}

void virtualwindow::in()
{
	//background
	glLoadIdentity();
	glColor4f(1, 1, 1, 0.9);
	glBindTexture(GL_TEXTURE_2D, buttonID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 6);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.4, 6);
	glTexCoord2f(1, 1);
	glVertex3f(0.9, 0.4, 6);
	glTexCoord2f(0, 1);
	glVertex3f(0.9, 0, 6);
	glEnd();

	//message
	glTranslatef(this->in_message_translate.x, this->in_message_translate.y, this->in_message_translate.z);
	glScalef(0.6, 0.6, 0.0);
	glColor4f(0, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, Font);
	write::string(this->in_message.c_str());

	glDisable(GL_TEXTURE_2D);
	glLineWidth(1);
	glLoadIdentity();
	glTranslatef(0.45, 0.05, 0);
	//input field
	glBegin(GL_LINES);
	glVertex3f(0, 0, 6);
	glVertex3f(0, 0.1, 6);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0, 0, 7);
	std::cout << wn.in_field << std::endl;
	write::string(this->in_field.c_str());

}
