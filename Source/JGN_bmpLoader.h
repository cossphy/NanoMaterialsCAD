#pragma once



EXT int JGN_bmpWidth;
EXT int JGN_bmpHeight;
EXT char* JGN_bmpData;

#define JGN_RGB 0
#define JGN_RGBA 1

void JGN_bmpLoad(char filename[], int A);
