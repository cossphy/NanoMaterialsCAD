#pragma once

//menu
#define IDM_PIE  1 
#define IDM_LINE 2 
#define IDM_BAR  3

#define PIE  1 
#define LINE 2 
#define BAR  3 

#define CPENS 5 

////////////

#define IDR_DLL1 144

#define IDI_JGNICON		                101
#define IDI_JGNSMALL                    102

#define IDC_JGNCLASS0			        103
#define IDC_JGNCLASS1			        104
#define IDC_JGNCLASS2			        105
#define IDC_JGNCLASS3			        106
#define IDC_JGNCLASS4			        107
#define IDC_JGNCLASS5			        108
#define IDC_JGNCLASS6			        109
#define IDC_JGNCLASS7			        110
#define IDC_JGNCLASS8			        111
#define IDC_JGNCLASS9			        112

#define IDD_ABOUTBOX                    113
#define IDM_ABOUT                       114
#define IDM_EXIT                        115
#define IDM_BUILD_POSCAR				120
#define IDM_TUT							122
#define ID_CHOOSE_POSCAR				132
#define ID_CHOOSE_LAMMPS				133
#define IDD_BUILD_POSCAR                121
#define IDD_CHOOSE_OUT					134///////
#define IDD_TUT							123

#define IDM_PERSPECTIVE_TUGLE			124
#define IDM_ROD_LIKE					125
#define IDM_RIGHT_HEXAGONAL				126
#define IDM_FIGURE_1					127
#define IDM_NORMAL						128
#define IDM_WANT_SPHERE					123
#define IDM_SUPERCELL					129
#define IDM_CUSTOM						130
#define IDM_NT							131

#define IDD_DLG_DIALOG					116
#define JGN_TRAYICON					118
#define JGN_TRAYMSG						119

#define SWM_SHOW	WM_APP + 1//	show the window
#define SWM_HIDE	WM_APP + 2//	hide the window
#define SWM_EXIT	WM_APP + 3//	close the window

#define JGN_Init() \
 ( \
  (jgn_int_macro_map[0] = IDC_JGNCLASS0), \
  (jgn_int_macro_map[1] = IDC_JGNCLASS1), \
  (jgn_int_macro_map[2] = IDC_JGNCLASS2), \
  (jgn_int_macro_map[3] = IDC_JGNCLASS3), \
  (jgn_int_macro_map[4] = IDC_JGNCLASS4), \
  (jgn_int_macro_map[5] = IDC_JGNCLASS5), \
  (jgn_int_macro_map[6] = IDC_JGNCLASS6), \
  (jgn_int_macro_map[7] = IDC_JGNCLASS7), \
  (jgn_int_macro_map[8] = IDC_JGNCLASS8), \
  (jgn_int_macro_map[9] = IDC_JGNCLASS9), \
  (QueryPerformanceFrequency(&lpFrequency)),\
  (void)0 \
 )


#define JGN_CHECK_NEGATIVE_16BIT		0x8000	// 1000 0000 0000 0000
///////////////////////////////////
//JGN macros

//buttons
#define JGN_LEFT_MOUSE_BUTTON			0
#define JGN_RIGHT_MOUSE_BUTTON			1
#define JGN_MIDDLE_MOUSE_BUTTON			2
#define JGN_MOUSE_WHEEL					3

//states
#define JGN_UP							0
#define JGN_DOWN						1
#define JGN_DOUBLE_CLICK				2

#define IDR_MAINFRAME                   128
//#define ID_FILE_HELLO                   32771
#define IDC_STATIC                      -1

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NO_MFC                     1
#define _APS_NEXT_RESOURCE_VALUE        129
#define _APS_NEXT_COMMAND_VALUE         32772
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           110
#endif
#endif

