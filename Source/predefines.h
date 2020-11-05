#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

//don't compile old code
#define JGN_NO_CMD_HISTORY
#define JGN_CMD_PLANE


#ifdef JGN_SOURCE_CPP
#define EXT 
#else
#define EXT extern
#endif //SOURCE_CPP


//TODO: custom surface to buildposcar
//TODO: custom surface and vacum^ to buildlammps


#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#pragma warning (disable : 4996)

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define NO_AXIS -1
