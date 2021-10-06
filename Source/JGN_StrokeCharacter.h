#pragma once


#define Angstrom -1
#define one_bar -2
#define two_bar -3
#define noadv false

void openfont(char* f);

void closefont();

namespace write
{
	extern const float max_height;
	//EXT float index_advanced;
	void character(char c, bool hadv = true);
	void string(const char* s, int maxchar = 100000);
	namespace rtl
	{
		void character(char c, bool hadv = true);
		void string(const char* s, int maxchar = 100000);
	}
}