#pragma once

#include "JGN_Resource.h"

EXT LARGE_INTEGER lpFrequency;

EXT int jgn_start_time;					//// gose to GetTickCount() every time a frame is drawn
EXT int cbc;							////to print frames/sec to the cmd


EXT int jgn_start_time_frame;				 ////for the frame limit
EXT int ct;									//// curent time in ms

#define MAX_LOADSTRING 100

// Global Variables:
EXT LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
EXT HHOOK hook1;
EXT LRESULT CALLBACK WndProcEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
EXT HINSTANCE hInst;								// current instance
EXT TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
EXT TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
EXT NOTIFYICONDATA	niData;							// Data for the tray
EXT HWND jgn_trayhwnd;						// tray hwnd
EXT HWND* jgn_ChildWin;								// a pointer to allocate all the child windows
EXT HWND jgn_help_to_map_the_draw_func;		// saves the hwnd of the most recent parent window created... helps to map the draw functions to the hwnd

EXT void* jgn_curent_window_to_edit;			// the pointer to the draw func that it is about to be used
EXT int jgn_Child_C;							// how many child windows?
EXT std::map<HWND,int> jgn_hwnd_int_map;					// map hwnd of the parent windows created to an int counter
EXT std::map<int,int> jgn_int_macro_map;					// maps a number to a macro class so every window has its own class		
EXT HGLRC  hglrc;
//#define JGN_Init() \
// ( \
//  (jgn_int_macro_map[0] = IDC_JGNCLASS0), \
//  (jgn_int_macro_map[1] = IDC_JGNCLASS1), \
//  (jgn_int_macro_map[2] = IDC_JGNCLASS2), \
//  (jgn_int_macro_map[3] = IDC_JGNCLASS3), \
//  (jgn_int_macro_map[4] = IDC_JGNCLASS4), \
//  (jgn_int_macro_map[5] = IDC_JGNCLASS5), \
//  (jgn_int_macro_map[6] = IDC_JGNCLASS6), \
//  (jgn_int_macro_map[7] = IDC_JGNCLASS7), \
//  (jgn_int_macro_map[8] = IDC_JGNCLASS8), \
//  (jgn_int_macro_map[9] = IDC_JGNCLASS9), \
//  (void)0 \
// )
EXT std::map<void* , HWND> jgn_dawfunc_hwnd_map;			// maps the draw func that the user created, to the hwnd
EXT HWND hWnd[10];									// hwnd of the parent window up to 10
EXT int jgn_wndcnt;								// how many parent wnd?
EXT RECT jgn_glbrect;							// a global rect to init window position and size
EXT int jgn_GlobalMouseCooX, jgn_GlobalMouseCooY;	// global mouse logical coords... the same for all the windows
EXT int jgn_runing ;								// init to 0 when a parent window is about to be created and 1 when it finished and it's ready for use
EXT int jgn_init_wind_size[10][2];


// Forward declarations of functions included in this code module:
ATOM				JGN_RegisterClass(HINSTANCE hInstance);
HWND				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Poscar_Build(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Choose_Format(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK TUT(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ULONGLONG GetDllVersion(LPCTSTR lpszDllName);
BOOL OnInitDialog(HWND hWnd);
void ShowContextMenu(HWND hWnd);
void MakeScroll();



/////////////////////////////
HWND JGN_CreateWindow(char* EszTitle,int nCmdShow,HINSTANCE hInstance );
HWND JGN_CreateTray(std::string traytitle, HINSTANCE hInstance);
void JGN_MainLoop();
void JGN_CreateChild(char* txt, int x, int y, int w, int h, char* clas, DWORD, HWND);
EXT void(*JGN_Global_Draw[10])();
void JGN_DisplayFunc(void JDS());
void ____JGN_DisplayF();
void JGN_PassiveMotionFunc(void JPMF(int x, int y));
EXT void(*JGN_User_PassiveMotionFunc[10])(int x, int y);
void ____JGN_PassiveMotionFunc(int x, int y, HWND hwnd);
void JGN_MouseFunc(void JMF(int button , int state, int x, int y));
EXT void(*JGN_User_MouseFunc[10])(int button, int state, int x, int y);
void ____JGN_MouseFunc(int button, int state, int x, int y, HWND hwnd1);
void JGN_InitWindowSize(int w, int h);
void JGN_InitWindowPosition(int x, int y);
void JGN_KeyboardFunc(void JKF(int button, int state, int x, int y));
EXT void(*JGN_User_KeyboardFunc[10])(int button, int state, int x, int y);
void ____JGN_KeyboardFunc(int button, int state, int x, int y, HWND hwnd1);
void JGN_PostRedisplay();
void JGN_ClearColor(BYTE r, BYTE g, BYTE  b, BYTE a);
void JGN_ReshapeFunc(void RSF(int w, int h));
EXT void (*JGN_User_ReshapeFunc[10])(int w, int h);
void ____JGN_ReshapeFunc(int w, int h, HWND hwnd);
void JGN_InitOpenGL();
void JGN_MotionFunc(void JPMF(int x, int y));
EXT void(*JGN_User_MotionFunc[10])(int x, int y);
void ____JGN_MotionFunc(int x, int y, HWND hwnd);



/////////////////////////////////////////////////
//
//Window
//


HWND JGN_CreateWindow(char* EszTitle,
	int       nCmdShow = SW_SHOW,
	HINSTANCE hInstance = hInst
);
void JGN_InitOpenGL();


void JGN_CreateChild(char* txt,
	int x, int y, int w, int h,
	char* clas = "STATIC",
	DWORD style = WS_VISIBLE | WS_CHILD | WS_BORDER, HWND hWnd1 = jgn_help_to_map_the_draw_func);

void JGN_ClearColor(BYTE r, BYTE g, BYTE  b, BYTE a = 0);




//static stuf... will be there from the begining to the end


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM JGN_RegisterClass(HINSTANCE hInstance);


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

void JGN_InitWindowSize(int w, int h);
void JGN_InitWindowPosition(int x, int y);



HWND InitInstance(HINSTANCE hInstance, int nCmdShow);

void JGN_QRedisplay();

void JGN_PostRedisplay();
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//  WM_SETREDRAW
//	

void JGN_DisplayFunc(void JDS());

void JGN_ReshapeFunc(void RSF(int w, int h));
void JGN_PassiveMotionFunc(void JPMF(int x, int y));

void JGN_MotionFunc(void JPMF(int x, int y));

void JGN_MouseFunc(void JMF(int button, int state, int x, int y));
void JGN_KeyboardFunc(void JKF(int button, int state, int x, int y));

void ____JGN_PassiveMotionFunc(int x, int y, HWND hwnd1);

void ____JGN_MotionFunc(int x, int y, HWND hwnd1);


void ____JGN_MouseFunc(int button, int state, int x, int y, HWND hwnd1);
void ____JGN_KeyboardFunc(int button, int state, int x, int y, HWND hwnd1);

void ____JGN_ReshapeFunc(int w, int h, HWND hwnd1);
void ____JGN_DisplayF();
LRESULT CALLBACK WndProcEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

EXT int endcheck;
EXT int okrender;
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////////
//
//Tray
//
HWND JGN_CreateTray(std::string traytitle, HINSTANCE hInstance = hInst);



ULONGLONG GetDllVersion(LPCTSTR lpszDllName);




INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void ShowContextMenu(HWND hWnd);


BOOL OnInitDialog(HWND hWnd);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////
//
//General
//


//The Main Loop
void JGN_MainLoop();

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK Poscar_Build(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK Choose_Format(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK TUT(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


void jgnCommands(LPTSTR ttt, int d);




void jgn_initcmd();


float f(float x, float R);

float df(float x, float R);
float find_theta(float R);
void MakeScroll();