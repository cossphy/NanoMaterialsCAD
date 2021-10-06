
#include "stdafx.h"
#include "JGN_StrokeCharacter.h"
#include "fontInfo.h"

#define len 200
#define fontmapwidht 512
#define fontmapheight 512

std::ifstream font;
void openfont(char* f)
{
	font.open(f);

}

void closefont()
{
	font.close();
}

namespace write
{
	
	const float max_height = 0.115234375;
	void character(char c, bool hadv)
	{
		char line[len];
		char* token;
		bool done = false;
		float x, y, w, h, adv, xoffset=0, yoffset=0;
		if (c == 0)
		{
			return;
		}
		else if (c == Angstrom)
		{
			write::character('A');
			glTranslatef(-0.068, 0.082, 0);
			glScalef(0.5, 0.5, 0.5);
			write::character('o', noadv);
			glScalef(2, 2, 2);
			glTranslatef(0.068, -0.082, 0);


			return;
		}
		else if (c == one_bar)
		{
			glTranslatef(0, 0.1, 0);
			write::character('-', noadv);
			glTranslatef(0, -0.1, 0);
			write::character('1');

			return;
		}
		else if (c == two_bar)
		{
			glTranslatef(0, 0.1, 0);
			write::character('-', noadv);
			glTranslatef(0, -0.1, 0);
			write::character('2');

			return;
		}
		///////////////////////
		std::istringstream iss(fontinfo);
		std::string sline;
		while (!done)
		{
			std::getline(iss, sline);
			//font.getline(line, len);

			token = strtok((char*)sline.c_str() , "=");
			token = strtok(NULL, " \t");

			if (atoi(token) == (int)c)
			{

				done = true;

				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				//cout << token << endl;
				
				x = (float)atoi(token) / (float)fontmapwidht;

				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				y = (float)(512 - atoi(token)) / (float)fontmapheight;

				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				w = (float)atoi(token) / (float)fontmapwidht;

				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				h = (float)atoi(token) / (float)fontmapheight;

				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				xoffset= (float)atoi(token) / (float)fontmapwidht;
				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				yoffset = -(float)(atoi(token)) / (float)fontmapheight;
				yoffset = yoffset - h + write::max_height;
				token = strtok(NULL, "=");
				token = strtok(NULL, " \t");
				adv = (float)atoi(token) / (float)fontmapwidht;

				glTranslatef(0, yoffset, 0);
				glEnable(GL_TEXTURE_2D);
				glBegin(GL_QUADS);

				glTexCoord2d(x, y);
				glVertex2d(0, h);

				glTexCoord2d(x + w, y);
				glVertex2d(w, h);

				glTexCoord2d(x + w, y - h);
				glVertex2d(w, 0);

				glTexCoord2d(x, y - h);
				glVertex2d(0, 0);

				glEnd();
				glTranslatef(0, -yoffset, 0);

				if (hadv)
				{
					glTranslatef(adv, 0, 0);
				}

			}
		}
		//font.clear();
		iss.clear();
		//font.seekg(0);
		iss.seekg(0);
	}


	void string(const char* s, int maxchar)
	{
		int counter = 0;

		while (s[counter] != '\0')
		{
			if (counter >= maxchar)
				break;
			write::character(s[counter]);
			counter++;
		}
	}

	namespace rtl//right to left
	{
		void character(char c, bool hadv)
		{
			char line[len];
			char* token;
			bool done = false;
			float x, y, w, h, adv, xoffset, yoffset;
			if (c == 0)
			{
				return;
			}
			else if (c == Angstrom)
			{
				write::rtl::character('A');
				glTranslatef(0.038, 0.082, 0);
				glScalef(0.5, 0.5, 0.5);
				write::character('o', noadv);
				glScalef(2, 2, 2);
				glTranslatef(-0.038, -0.082, 0);


				return;
			}
			else if (c == one_bar)
			{
				glTranslatef(0, 0.1, 0);
				write::rtl::character('-', noadv);
				glTranslatef(0, -0.1, 0);
				write::rtl::character('1');

				return;
			}
			else if (c == two_bar)
			{
				glTranslatef(0, 0.1, 0);
				write::rtl::character('-', noadv);
				glTranslatef(0, -0.1, 0);
				write::rtl::character('2');

				return;
			}
			///////////////////////
			std::istringstream iss(fontinfo);
			std::string sline;
			while (!done)
			{
				std::getline(iss, sline);

				//font.getline(line, len);

				token = strtok((char*)sline.c_str(), "=");
				token = strtok(NULL, " \t");

				if (atoi(token) == (int)c)
				{

					done = true;

					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					//cout << token << endl;
					x = jgn::atof(token) / fontmapwidht;

					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					y = (512 - jgn::atof(token)) / fontmapheight;

					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					w = jgn::atof(token) / fontmapwidht;

					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					h = jgn::atof(token) / fontmapheight;

					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					xoffset = (float)atoi(token) / (float)fontmapwidht;
					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					yoffset = -(float)(atoi(token)) / (float)fontmapheight;
					yoffset = yoffset - h + 0.11;
					token = strtok(NULL, "=");
					token = strtok(NULL, " \t");
					adv = jgn::atof(token) / fontmapwidht;
					if (hadv)
					{
						glTranslatef(-adv, 0, 0);
					}
					glTranslatef(0, yoffset, 0);

					glBegin(GL_QUADS);
					glTexCoord2d(x, y);
					glVertex2d(0, h);
					glTexCoord2d(x + w, y);
					glVertex2d(w, h);
					glTexCoord2d(x + w, y - h);
					glVertex2d(w, 0);
					glTexCoord2d(x, y - h);
					glVertex2d(0, 0);
					glEnd();
					glTranslatef(0, -yoffset, 0);

				}
			}
			//font.clear();
			iss.clear();
			//font.seekg(0);
			iss.seekg(0);
		}

		void string(const char* s, int maxchar)
		{
			int counter = 0;

			while (s[counter] != '\0')
			{
				if (counter >= maxchar)
					break;
				counter++;
			}
			counter--;
			for (int i = counter; i > -1; i--)
			{
				write::rtl::character(s[i]);
			}
		}
	}
}