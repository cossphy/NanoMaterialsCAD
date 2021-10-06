// Win32Lesson1.cpp : Defines the entry point for the application.
//
#define JGN_WINDOWS_CPP
#include "stdafx.h"
#include "JGN_Resource.h"
#include "JGN_DropFile.h"
#include "JGN_Windows.h"
#include "ToolBar.h"
#include "JGN_DropFile.h"
#include "Cammera.h"
#include "DefectedNPs.h"
#define JGN_CMD_PLANE

/////////////////////////////////////////////////
//
//Window
//


HWND JGN_CreateWindow(char* EszTitle,
	int       nCmdShow,
	HINSTANCE hInstance
)
{
	if (jgn_wndcnt > 9)
	{
		perror("Max Number Of Windows Has Reached");
		return NULL;
	}

	int i = 0;
	while (EszTitle[i] != '\0' && i < 100)
	{
		szTitle[i] = EszTitle[i];
		i++;
	}




	// Initialize global strings
	LoadString(hInstance, jgn_int_macro_map[jgn_wndcnt], szWindowClass, MAX_LOADSTRING);


	JGN_RegisterClass(hInstance);


	// Perform application initialization:




	// Main message loop:

	jgn_help_to_map_the_draw_func = InitInstance(hInstance, nCmdShow);


	DragAcceptFiles(jgn_help_to_map_the_draw_func, TRUE);
	//wglDeleteContext(hglrc);

	return jgn_help_to_map_the_draw_func;
}
void JGN_InitOpenGL()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

}


void JGN_CreateChild(char* txt,
	int x, int y, int w, int h,
	char* clas,
	DWORD style, HWND hWnd1)
{

	jgn_Child_C++;
	jgn_ChildWin = (HWND*)realloc(jgn_ChildWin, jgn_Child_C * sizeof(HWND));

	TCHAR wclass[20];
	for (int i = 0; i < 20; i++)
	{
		wclass[i] = clas[i];
		if (clas[i] == '\0')
		{
			i = 100;
		}
	}

	TCHAR wtxt[1000];
	for (int i = 0; i < 1000; i++)
	{
		wtxt[i] = txt[i];
		if (txt[i] == '\0')
		{
			i = 2000;
		}
	}
	jgn_ChildWin[jgn_Child_C - 1] = CreateWindow(wclass,
		wtxt, style,
		x, y, w, h,
		hWnd1, NULL, NULL, NULL);

	UpdateWindow(jgn_ChildWin[jgn_Child_C - 1]);


}

void JGN_ClearColor(BYTE r, BYTE g, BYTE  b, BYTE a)
{
	RECT rect = { 0,0,0,0 };
	COLORREF crColor = RGB(r, g, b);
	HBRUSH brush = CreateSolidBrush(crColor);
	HDC hdc = GetDC(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit]);

	GetClientRect(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit], &rect);
	FillRect(hdc, &rect, brush);

	DeleteDC(hdc);


}




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
ATOM JGN_RegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS; //CS_HREDRAW | CS_VREDRAW | redraws the hall screen when resized, couses flicks
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JGNICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = MAKEINTRESOURCE(jgn_int_macro_map[jgn_wndcnt]);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_JGNSMALL));

	return RegisterClassEx(&wcex);
}


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

void JGN_InitWindowSize(int w, int h)
{
	jgn_init_wind_size[jgn_wndcnt][0] = w;
	jgn_init_wind_size[jgn_wndcnt][1] = h;

	jgn_glbrect = { jgn_glbrect.left,jgn_glbrect.top,jgn_glbrect.right + w , jgn_glbrect.bottom + h };
	return;
}
void JGN_InitWindowPosition(int x, int y)
{
	jgn_glbrect = { jgn_glbrect.left + x, jgn_glbrect.top + y, jgn_glbrect.right + x, jgn_glbrect.bottom + y };
	return;
}



HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND h = hWnd[jgn_wndcnt] = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_COMPOSITED,//WS_CLIPCHILDREN WS_CLIPSIBLINGS WS_EX_COMPOSITED(double buffer)
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	mnhwnd = h;
	PIXELFORMATDESCRIPTOR pfd;
	HDC hdc;
	int nPixelFormat;
	hdc = GetDC(h);

	pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,0,0,0,0,0,0,0, // useles parameters
		16,
		0,0,0,0,0,0,0
	};
	nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, nPixelFormat, &pfd);


	hglrc = wglCreateContext(hdc);


	wglMakeCurrent(hdc, hglrc);


	DeleteDC(hdc);
	int w = jgn_init_wind_size[jgn_wndcnt][0];
	int he = jgn_init_wind_size[jgn_wndcnt][1];
	glViewport(0, 0, w, he);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= he)
	{
		glOrtho(
			-1.05, +1.05,
			-1.05 * (GLfloat)he / (GLfloat)w, +1.05 * (GLfloat)he / (GLfloat)w,
			-10.0, 10.0);
		dipleft = -1.05;
		dipapan = -1.05 * (GLfloat)he / (GLfloat)w;
	}
	else
	{
		glOrtho(
			-1.05 * (GLfloat)w / (GLfloat)he, +1.05 * (GLfloat)w / (GLfloat)he,
			-1.05, +1.05,
			-10.0, 10.0);
		dipleft = -1.05*(GLfloat)w / (GLfloat)he;
		dipapan = 1.05;
	}
	glMatrixMode(GL_MODELVIEW);

	JGN_InitOpenGL();


	if (h != NULL)
	{
		ShowWindow(h, SW_SHOW);
		UpdateWindow(h);

		jgn_hwnd_int_map[h] = jgn_wndcnt;

		jgn_wndcnt++;
	}
	else
	{
		perror("CreateWindow Function Could Not Create Window");
		return NULL;
	}

	DWORD dwStyle = GetWindowLongPtr(h, GWL_STYLE);
	DWORD dwExStyle = GetWindowLongPtr(h, GWL_EXSTYLE);
	HMENU menu = GetMenu(h);



	RECT rc = jgn_glbrect;

	AdjustWindowRectEx(&rc, dwStyle, !(menu == 0), dwExStyle);

	if (menu == 0)
	{
		SetWindowPos(h, NULL, rc.left + 8, rc.top + 30, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	}
	else
	{
		SetWindowPos(h, NULL, rc.left + 8, rc.top + 50, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
	}

	jgn_glbrect = { 0,0,0,0 };

	hdc = GetDC((HWND)menu);
	SetTextColor(hdc, RGB(0, 255, 255));
	SetBkColor(hdc, RGB(50, 50, 50));
	DeleteDC(hdc);


	return h;
}

void JGN_QRedisplay()
{
	qredisplay = true;
	if (my_postmessages_count == 0)
	{
		PostMessage(jgn_help_to_map_the_draw_func, WM_MOUSEMOVE, -1, rand());
		my_postmessages_count++;
	}

}

void JGN_PostRedisplay()
{

	if (jgn_file_dropd)
	{

		____JGN_DisplayF();


	}
	else
	{
		HDC global_hdc = GetDC(jgn_dawfunc_hwnd_map[JGN_Global_Draw[0]]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tb.draw();

		SwapBuffers(global_hdc);

		DeleteDC(global_hdc);

	}

}
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

void JGN_DisplayFunc(void JDS())
{
	JGN_Global_Draw[jgn_wndcnt - 1] = JDS;
	jgn_dawfunc_hwnd_map[JDS] = jgn_help_to_map_the_draw_func;
}

void JGN_ReshapeFunc(void RSF(int w, int h))
{
	JGN_User_ReshapeFunc[jgn_wndcnt - 1] = RSF;
	return;

}
void JGN_PassiveMotionFunc(void JPMF(int x, int y))
{
	JGN_User_PassiveMotionFunc[jgn_wndcnt - 1] = JPMF;
	return;
}

void JGN_MotionFunc(void JPMF(int x, int y))
{
	JGN_User_MotionFunc[jgn_wndcnt - 1] = JPMF;
	return;
}

void JGN_MouseFunc(void JMF(int button, int state, int x, int y))
{
	JGN_User_MouseFunc[jgn_wndcnt - 1] = JMF;
	return;

}
void JGN_KeyboardFunc(void JKF(int button, int state, int x, int y))
{
	JGN_User_KeyboardFunc[jgn_wndcnt - 1] = JKF;
	return;
}

void ____JGN_PassiveMotionFunc(int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];

	if (JGN_User_PassiveMotionFunc[xx] == NULL)
	{
	}
	else
	{
		JGN_User_PassiveMotionFunc[xx](x, y);
	}
	return;
}

void ____JGN_MotionFunc(int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];

	if (JGN_User_MotionFunc[xx] == NULL)
	{
	}
	else
	{
		JGN_User_MotionFunc[xx](x, y);
	}
	return;
}


void ____JGN_MouseFunc(int button, int state, int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];
	if (JGN_User_MouseFunc[xx] == NULL)
	{

	}
	else
	{
		JGN_User_MouseFunc[xx](button, state, x, y);
	}
	return;
}
void ____JGN_KeyboardFunc(int button, int state, int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];

	if (JGN_User_KeyboardFunc[xx] == NULL)
	{

	}
	else
	{
		JGN_User_KeyboardFunc[xx](button, state, x, y);
	}
	return;
}

void ____JGN_ReshapeFunc(int w, int h, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];


	if (JGN_User_ReshapeFunc[xx] == NULL)
	{

	}
	else
	{
		JGN_User_ReshapeFunc[xx](w, h);
	}
	return;
}
void ____JGN_DisplayF()
{


	for (int i = 0; i < jgn_wndcnt; i++)
	{
	

		JGN_Global_Draw[0]();

		SwapBuffers(global_hdc);

		//DeleteDC(global_hdc);

	}

	//RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);



	return;
}
LRESULT CALLBACK WndProcEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case VK_RETURN:
			return 0;
			break;
		}
		break;
	}

	return CallWindowProc(oldEditProc, hWnd, message, wParam, lParam);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{



	switch (message)
	{
	case WM_CTLCOLORSTATIC://////paint child
	{

		hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(0, 255, 255));
		SetBkColor(hdc, RGB(50, 50, 50));
		return (INT_PTR)CreateSolidBrush(RGB(50, 50, 50));
	}
	break;

	case WM_CTLCOLOREDIT://///paint child
	{

		hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(0, 255, 255));
		SetBkColor(hdc, RGB(50, 50, 50));
		return (INT_PTR)CreateSolidBrush(RGB(50, 50, 50));
	}
	break;
	case WM_SIZING:

		//JGN_PostRedisplay();

		break;
	case WM_DROPFILES:

		CustomSurfacesOn = 1;
		was_supercell = 0;
		jgn_supercell = 0;
		Right_Hexagonal = 1;
		want_cyrcle[0] = 'n';
		figure_1 = 1;
		Rod_like = 1;
		nanotube = 0;


		//initialize min and max coordinates of the volum of crystal in Angstrom
		min_xyz[0] = 10000;
		min_xyz[1] = 10000;
		min_xyz[2] = 10000;
		max_xyz[0] = -10000;
		max_xyz[1] = -10000;
		max_xyz[2] = -10000;

		//read the path of the droped file
		DragQueryFile((HDROP)wParam, 0, lpszFile, 500);

		//initialize facetes
		S1 = "100";
		S2 = "110";
		S3 = "111";

		//buffer
		delete s;
		s = new char[SBYTES];

		//LPTSTR to char*
		for (int i = 0; i < 500; i++)
		{
			inpf[i] = (char)lpszFile[i];
			if (inpf[i] == 0)
			{
				i = 1000;
			}
		}







		JGN_DropFile(inpf);

		DragFinish((HDROP)wParam);

		lines_param();
		jgn_file_dropd = 1;


		JGN_PostRedisplay();
		SetForegroundWindow(hWnd);

		break;
	case WM_MOVE:
		GetWindowRect(mnhwnd, glb_rct);
		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
#if !defined(JGN_NO_CMD_HISTORY) 
		SetWindowPos(CommandTextHistory, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242, SWP_ASYNCWINDOWPOS);
#endif
		//JGN_PostRedisplay();
		break;
	case WM_MOVING:

		GetWindowRect(mnhwnd, glb_rct);
		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
#if !defined(JGN_NO_CMD_HISTORY) 
		SetWindowPos(CommandTextHistory, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242, SWP_ASYNCWINDOWPOS);
#endif

		//JGN_PostRedisplay();

		break;
		//////////////////////////////////////
		//
		//Mouse messages
		//

	case WM_LBUTTONDBLCLK:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_LEFT_MOUSE_BUTTON, JGN_DOUBLE_CLICK, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_RBUTTONDBLCLK:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_RIGHT_MOUSE_BUTTON, JGN_DOUBLE_CLICK, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MBUTTONDOWN:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_MIDDLE_MOUSE_BUTTON, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MBUTTONDBLCLK:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_MIDDLE_MOUSE_BUTTON, JGN_DOUBLE_CLICK, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MBUTTONUP:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_MIDDLE_MOUSE_BUTTON, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MOUSEWHEEL:
		help0 = HIWORD(wParam);
		if ((JGN_CHECK_NEGATIVE_16BIT & help0) == JGN_CHECK_NEGATIVE_16BIT)
		{
			____JGN_MouseFunc(JGN_MOUSE_WHEEL, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		}
		else
		{
			____JGN_MouseFunc(JGN_MOUSE_WHEEL, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		}
		break;
	case WM_MOUSEMOVE:

		if (wParam == -1)
		{

			my_postmessages_count--;

			JGN_PostRedisplay();

		}
		else
		{
			jgn_GlobalMouseCooX = LOWORD(lParam);
			jgn_GlobalMouseCooY = HIWORD(lParam);
			if ((JGN_CHECK_NEGATIVE_16BIT & jgn_GlobalMouseCooX) == JGN_CHECK_NEGATIVE_16BIT)
			{
				jgn_GlobalMouseCooX = jgn_GlobalMouseCooX & 0x7fff;
				help0 = 0x00007fff;
			}
			else
			{
				help0 = 0x00000000;

			}
			if ((JGN_CHECK_NEGATIVE_16BIT & jgn_GlobalMouseCooY) == JGN_CHECK_NEGATIVE_16BIT)
			{
				jgn_GlobalMouseCooY = jgn_GlobalMouseCooY & 0x7fff;
				help1 = 0x00007fff;

			}
			else
			{
				help1 = 0x00000000;
			}
			____JGN_PassiveMotionFunc((int)jgn_GlobalMouseCooX - help0, (int)jgn_GlobalMouseCooY - help1, hWnd);
		}

		break;
	case WM_LBUTTONDOWN:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_LEFT_MOUSE_BUTTON, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		____JGN_PassiveMotionFunc((int)jgn_GlobalMouseCooX, (int)jgn_GlobalMouseCooY, hWnd);

		SetCapture(hWnd);
		break;
	case WM_LBUTTONUP:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_LEFT_MOUSE_BUTTON, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		SetCapture(NULL);
		break;
	case WM_RBUTTONDOWN:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_RIGHT_MOUSE_BUTTON, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		SetCapture(hWnd);
		break;
	case WM_RBUTTONUP:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_RIGHT_MOUSE_BUTTON, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		SetCapture(NULL);
		break;
		//////////////////////////////////////////
		//
		//Keyboard Messages
		//
	case WM_KEYDOWN:
		if (wParam == VK_CAPITAL)
		{
			if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
				capson = true;
			else
				capson = false;
		}
		else
		{
			____JGN_KeyboardFunc(wParam, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		}
		break;
	case WM_KEYUP:
		____JGN_KeyboardFunc(wParam, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
		//////////////////////////////////////////
		////////////////////////////////////////////////
		////////////////////////////////////////////
	case WM_SIZE:
		____JGN_ReshapeFunc(LOWORD(lParam), HIWORD(lParam), hWnd);
		GetWindowRect(mnhwnd, glb_rct);
		//width = - (*glb_rct).left + (*glb_rct).right - 20;
		//height =  (*glb_rct).bottom - (*glb_rct).top - 50;
		//__asm {
		//	mov esi, [glb_rct]
		//	mov[mnrcpt], esi
		//}
		mnrcpt = (long*)glb_rct;

		mainwndsize[0] = *(mnrcpt + 2) - *mnrcpt;
		mainwndsize[1] = *(mnrcpt + 3) - *(mnrcpt + 1);

		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
#if !defined(JGN_NO_CMD_HISTORY) 
		SetWindowPos(CommandTextHistory, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242, SWP_ASYNCWINDOWPOS);
#endif
		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
		DestroyWindow(hWndList);
		RedrawWindow(CommandTextField, 0, 0, RDW_NOERASE);

		wasfullscreenflagout++;
		tb.initPositions();

		if (wParam == SIZE_MAXIMIZED)
		{
			wasfullscreenflagin++;
			JGN_PostRedisplay();
		}
		if (wasfullscreenflagin == 0)
		{
			wasfullscreenflagout = -1;

		}
		if (wasfullscreenflagout == wasfullscreenflagin)
		{
			JGN_PostRedisplay();
			wasfullscreenflagin = 0;
			wasfullscreenflagout = -1;

		}

		

		break;
	case WM_EXITSIZEMOVE:
		JGN_PostRedisplay();

		break;
	case WM_COMMAND:

		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:

			hdc = GetDC(hWnd);
			wglMakeCurrent(hdc, NULL);		// release current device context			THIS IS FOR ONE WINDOW ONLY
			wglDeleteContext(hglrc);		// delete rendering context					CHANGE IT
			DeleteDC(hdc);

			if (jgn_trayhwnd != NULL)
			{
				DestroyWindow(jgn_trayhwnd);
			}

			DestroyWindow(hWnd);
			exit(0);
			break;
		case IDM_BUILD_POSCAR:


			DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE_OUT), hWnd, Choose_Format);

			DialogBox(hInst, MAKEINTRESOURCE(IDD_BUILD_POSCAR), hWnd, Poscar_Build);


			break;
		case IDM_NT:

			//max_xyz[0] = crystal[2 + 5 * 0];
			//min_xyz[0] = crystal[2 + 5 * 0];

			/*for (ole3 = 0; ole3 < t * (sized[0])*(sized[1])*(sized[2]); ole3++)
			{
				if (crystal[2 + 5 * ole3] > max_xyz[0])
				{
					max_xyz[0] = crystal[2 + 5 * ole3];
				}
				else if (crystal[2 + 5 * ole3] < min_xyz[0])
				{
					min_xyz[0] = crystal[2 + 5 * ole3];

				}

			}*/
			max_xyz[0] = vs.group[0].position[0].x;
			min_xyz[0] = vs.group[0].position[0].x;
			for (int g = 0; g < vs.N_groups; g++)
			{
				for (int i = 0; i < vs.group[g].N_atoms; i++)
				{
					if (vs.group[g].position[i].x > max_xyz[0])
					{
						max_xyz[0] = vs.group[g].position[i].x;
					}
					else if (vs.group[g].position[i].x < min_xyz[0])
					{
						min_xyz[0] = vs.group[g].position[i].x;
					}
				}
			}

			sized[0] = custom_sized[0];
			sized[1] = custom_sized[1];
			sized[2] = custom_sized[2];
			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];
			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;


			CustomSurfacesOn = 0;
			was_supercell = 1;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			want_cyrcle[0] = 'n';
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 1;

			S1v = 0;
			S2v = 25;
			S3v = 159;
			MakeScroll();

			JGN_PostRedisplay();

			break;
		case IDM_CUSTOM:


			sized[0] = custom_sized[0];
			sized[1] = custom_sized[1];
			sized[2] = custom_sized[2];
			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];
			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			if (sized[0] / 2 != sized[0] / 2.0)
			{
				xexe[0] = 1;
			}

			if (sized[1] / 2 != sized[1] / 2.0)
			{
				xexe[1] = 1;
			}

			if (sized[2] / 2 != sized[2] / 2.0)
			{
				xexe[2] = 1;
			}

			periodic_table = fopen("periodic_table.jgn", "r");

			jgn::heapRealloc();
			/*crystal = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(sized[0] * sized[1] * sized[2] * t * 3));
			isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
			for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
			{
				isSelected[i] = false;
			}
			isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
			for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
			{
				isdeleted[i] = false;
			}*/


			//crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

						//selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}



							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);




			CustomSurfacesOn = 1;
			was_supercell = 1;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			want_cyrcle[0] = 'n';
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 0;

			JGN_PostRedisplay();


			break;
		case IDM_SUPERCELL:

			CustomSurfacesOn = 0;
			was_supercell = 1;
			jgn_supercell = 1;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;
			want_cyrcle[0] = 'n';
			jgn_supercell_xyz[0] = 10;
			jgn_supercell_xyz[1] = 10;
			jgn_supercell_xyz[2] = 10;
			sized[0] = jgn_supercell_xyz[0];
			sized[1] = jgn_supercell_xyz[1];
			sized[2] = jgn_supercell_xyz[2];

			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			periodic_table = fopen("periodic_table.jgn", "r");


			jgn::heapRealloc();
			/*crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
			isSelected = (bool*)realloc(isSelected, sizeof(bool)*t);
			for (int i = 0; i < t; i++)
			{
				isSelected[i] = false;
			}
			isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
			for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
			{
				isdeleted[i] = false;
			}*/


			//crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}



							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);

			JGN_PostRedisplay();

			break;
		case IDM_PERSPECTIVE_TUGLE:
			if (cam.perspective_on)
			{

				cam.perspective_on = 0;
				glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
				glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me
				glLoadIdentity();
				if (width <= height)
				{
					glOrtho(
						-1.05, +1.05,
						-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
						-10.0, 10.0);
					dipleft = -1.05;
					dipapan = -1.05 * (GLfloat)height / (GLfloat)width;

				}
				else
				{
					glOrtho(
						-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
						-1.05, +1.05,
						-10.0, 10.0);
					dipleft = -1.05*(GLfloat)width / (GLfloat)height;
					dipapan = 1.05 * (GLfloat)width / (GLfloat)height;
				}
				glMatrixMode(GL_MODELVIEW);


			}
			else
			{
				cam.perspective_on = 1;

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				//gluPerspective(60, (float)width / (float)height, 0.001, 100);
				glMatrixMode(GL_MODELVIEW);

			}

			JGN_PostRedisplay();
			break;
		case IDM_ROD_LIKE:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];


				periodic_table = fopen("periodic_table.jgn", "r");

				jgn::heapRealloc();
				/*crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
				isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isSelected[i] = false;
				}
				isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isdeleted[i] = false;
				}*/


				//crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			CustomSurfacesOn = 0;
			Right_Hexagonal = 1;
			jgn_supercell = 0;
			figure_1 = 1;
			Rod_like = -1;
			nanotube = 0;
			Svmax = 50;
			S1v = 11;
			S2v = 17;
			S3v = 23;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 1;
			S1 = "100";
			S2 = "110";
			S3 = "111";
			want_cyrcle[0] = 'n';

			lines_param();

			JGN_PostRedisplay();

			break;
		case IDM_NORMAL:
			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];

				periodic_table = fopen("periodic_table.jgn", "r");

				jgn::heapRealloc();
				/*crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
				isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isSelected[i] = false;
				}
				isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isdeleted[i] = false;
				}*/


				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			Scase = 1;
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 0;

			Svmax = 40;
			S1v = 25;
			S2v = 30;
			S3v = 40;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 1;
			S1 = "100";
			S2 = "110";
			S3 = "111";
			want_cyrcle[0] = 'n';

			Scase = 1;

			lines_param();

			JGN_PostRedisplay();
			break;
		case IDM_RIGHT_HEXAGONAL:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];

				periodic_table = fopen("periodic_table.jgn", "r");

				jgn::heapRealloc();
				/*crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
				isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isSelected[i] = false;
				}
				isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isdeleted[i] = false;
				}*/


				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Rod_like = 1;
			figure_1 = 1;
			Right_Hexagonal = -1;
			Svmax = 50;
			S1v = 8;
			S2v = 8;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 0;
			Right_Hexagonal_height = 20;
			S1 = "100";
			S2 = "110";
			S3 = "000";
			want_cyrcle[0] = 'n';

			lines_param();

			JGN_PostRedisplay();



			break;

		case IDM_FIGURE_1:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];

				periodic_table = fopen("periodic_table.jgn", "r");

				jgn::heapRealloc();
				/*crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
				isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isSelected[i] = false;
				}
				isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isdeleted[i] = false;
				}*/


				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Scase = 1;
			figure_1 = -1;
			Right_Hexagonal = 1;
			Rod_like = 1;
			nanotube = 0;

			Svmax = 50;
			S1v = 15;
			S2v = 30;
			S3v = 40;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 1;
			S1 = "100";
			S2 = "110";
			S3 = "111";
			want_cyrcle[0] = 'n';

			lines_param();

			JGN_PostRedisplay();

			break;

		case IDM_TUT:

			DialogBox(hInst, MAKEINTRESOURCE(IDD_TUT), hWnd, TUT);

			break;


		case IDM_WANT_SPHERE:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];


				periodic_table = fopen("periodic_table.jgn", "r");

				jgn::heapRealloc();
				/*crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
				isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isSelected[i] = false;
				}
				isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
				for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
				{
					isdeleted[i] = false;
				}*/


				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			rad = 20;
			want_cyrcle[0] = 'y';
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 0;


			JGN_PostRedisplay();
			break;


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_ERASEBKGND: // return 1 so it doesnt flick, prevents to erase window content
		return 1;
		break;

	case WM_DESTROY:
		//PostQuitMessage(0);


		hdc = GetDC(hWnd);
		wglMakeCurrent(hdc, NULL);		// release current device context			THIS IS FOR ONE WINDOW ONLY
		wglDeleteContext(hglrc);		// delete rendering context					CHANGE IT
		DeleteDC(hdc);



		if (jgn_trayhwnd != NULL)
		{
			DestroyWindow(jgn_trayhwnd);
		}
		if (hWndCommandLine != 0)
		{
			DestroyWindow(hWndCommandLine);

		}
		//delete(S1);
		//delete(S2);
		//delete(S3);
		//delete(s1);
		//delete(NewPC);
		//delete(PCtype);
		//delete(lpszFile);
		//delete(new_num_atoms);
		//delete(atomic_number);
		//delete(an_and_aw);
		//delete(atoms);
		//delete(ea);
		//delete(my_direct);
		//delete(uccartesian);
		//delete(crystal);
		//delete(atoms_to_print);



		exit(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}



	//JGN_DisplayF(JGN_Global_Draw);

	return 0;
}


LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{

	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	LPTSTR  ttt = CommandBuffer;
	FILE* periodic_table;
	loop = 0;
	int isngtv = 0;


	int listwrite[testsc];

	for (int i = 0; i < testsc; i++)
	{
		listwrite[i] = 1;
	}

	if (GetFocus() == CommandTextField)
	{
		GetWindowText(CommandTextField, ttt, 500);
		int len = lstrlen(ttt);
		if (len == 0)
		{
			for (int i = 0; i < testsc; i++)
			{
				listwrite[i] = 0;
			}
		}

		for (int j = 0; j < testsc; j++)
		{
			for (int i = 0; i < len; i++)
			{

				if (ttt[i] != test1[j][i] && ttt[i] != test1low[j][i])
				{
					listwrite[j] = 0;
				}
			}
		}



		DestroyWindow(hWndList);
		int itemscnt = 0;
		for (int i = 0; i < testsc; i++)
		{
			if (listwrite[i] == 1)
			{
				itemscnt++;
			}
		}
		//if (itemscnt > 6)
		//{
			HINSTANCE hinst111 = (HINSTANCE)GetWindowLong(mnhwnd, GWLP_HINSTANCE);
			hWndList = CreateWindow(L"LISTBOX",
				0, WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | WS_VSCROLL,
				0, mainwndsize[1] -90 - 20 * itemscnt, 350, 20 * itemscnt,
				mnhwnd, NULL, hinst111, NULL);
			//hWndList = CreateWindow(L"LISTBOX",
			//	0, WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | WS_VSCROLL,
			//	0, 222 - 20 * 6, 250, 20 * 6,
			//	mnhwnd, NULL, hinst111, NULL);
		//}
#if !defined(JGN_NO_CMD_HISTORY) 
		else
		{
			/////////////////////////////////////////////
						//HINSTANCE hinst111 = (HINSTANCE)GetWindowLong(mnhwnd, GWL_HINSTANCE);

			hWndList = CreateWindow(L"LISTBOX",
				0, WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | WS_VSCROLL,
				0, 222 - 20 * itemscnt, 250, 20 * itemscnt,
				CommandTextHistory, NULL, NULL, NULL);
			///////////////////////////////////////////

		}
#endif


		ShowWindow(hWndList, SW_HIDE);

		int another1 = 0;

		for (int i = 0; i < testsc; i++)
		{
			if (listwrite[i] == 1)
			{
				boxlistmap[another1] = test1[i];
				another1++;
				SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)helplist[i]);

			}
		}



		if (wParam == 256)
		{

			if (p->vkCode == 40)
			{
				itemsel++;
				if (itemsel > itemscnt - 1)
				{
					itemsel = itemscnt - 1;
				}
				SendMessage(hWndList, LB_SETSEL, TRUE, itemsel);

			}
			else if (p->vkCode == 38)
			{

				itemsel--;
				if (itemsel < 0)
				{
					itemsel = 0;
				}
				SendMessage(hWndList, LB_SETSEL, TRUE, itemsel);

			}
			else if (p->vkCode == 13)
			{

				if (itemsel != -1)
				{
					predicted = 1;
					SendMessage(CommandTextField, EM_SETSEL, 0, -1);
					char *hasdlf = boxlistmap[itemsel];
					mbstowcs(widechar, hasdlf, 50);
					i = 0;
					while (hasdlf[i] != '\0')
					{

						SendMessage(CommandTextField, WM_CHAR, (TCHAR)hasdlf[i], 0);
						itemsel = -1;

						i++;
					}
					db = 1;
					JGN_PostRedisplay();

					goto peintit1;
				}
			}

		}
		else
		{
			if (itemsel != -1)
			{
				SendMessage(hWndList, LB_SETSEL, TRUE, itemsel);

			}


		}

		ShowWindow(hWndList, SW_SHOW);
		ole5 = 0;
		for (int i = 0; i < testsc; i++)
		{
			if (listwrite[i] == 1)
			{
				ole5++;
			}
		}

		if (ole5 == 0)
		{
			if (hWndList != 0)
			{
				DestroyWindow(hWndList);
				itemsel = -1;
				JGN_PostRedisplay();
			}
		}

	}





	if (wParam == 256)
	{
		if (p->vkCode == 13)
		{
			if (GetFocus() == CommandTextField)
			{
				GetWindowText(CommandTextField, ttt, 500);

				endcheck = 1;


				//char *test1 = "script(";
				for (i = 0; i < 7; i++)
				{
					if (test1[5][i] == ttt[i])
					{

					}
					else
					{
						i = 100;

					}
				}
				if (i == 7)
				{
					okrender = 1;

					help = (char*)(ttt + 7);

					if (help[0] != '\"')
					{
						//std::cout << "expecting a \"" << std::endl;
						okrender = 0;
						goto peintit;
					}

					help = help + 2;
					ole = 0;
					ole1 = 0;
					while (help[0] != '\"')
					{
						ole++;
						help = help + 2;
						if (help[0] == '\0')
						{

							ole1 = 1;
						}
					}
					if (ole1 == 1)
					{
						//std::cout << "expecting a \"" << std::endl;
						okrender = 0;
						goto peintit;
					}
					else
					{
						//std::cout << ole << std::endl;
						help = help - 2 * ole;
						jgncmdfpath = (char*)malloc(sizeof(char)*(ole + 1));

						for (int i = 0; i < ole; i++)
						{
							jgncmdfpath[i] = help[0];
							help = help + 2;
						}
						jgncmdfpath[ole] = 0;
						jgncmdfile = fopen(jgncmdfpath, "r");


						fgets(jgncmdfline, 500, jgncmdfile);

						while ((jgncmdfline[0] != 'e' || jgncmdfline[1] != 'x' || jgncmdfline[2] != 'i' || jgncmdfline[3] != 't'))
						{
							for (i = 0; i < 500; i++)
							{
								ttt[i] = jgncmdfline[i];
								if (jgncmdfline[i] == 0)
								{
									break;
								}
							}
							if (jgncmdfline[0] == 'f' && jgncmdfline[1] == 'o' && jgncmdfline[2] == 'r')
							{//now execute the for loop (if there is one)
								jgn::string curentLine = jgncmdfline;
								//get rid of the spaces
								int pos_token = curentLine.find(" ");
								if (pos_token != std::string::npos)
								{
									curentLine.erase(pos_token, 1);
									pos_token = curentLine.find(" ");
								}
								//get rid of the "for"
								pos_token = curentLine.find("for");
								curentLine.erase(pos_token, 3);
								//extract the istart
								pos_token = curentLine.find(":");
								int istart = std::stof(curentLine.substr(0, pos_token));
								//extract the ifin
								int ifin = std::stof(curentLine.substr(pos_token + 1, curentLine.size() - 1));
								//extract the starting file pointer
								fpos_t forBeggining;
								fgetpos(jgncmdfile, &forBeggining);//this is the line that says "for"
								//start the actual for loop
								for (int i = istart; i <= ifin; i++)
								{
									fsetpos(jgncmdfile, &forBeggining);
									fgets(jgncmdfline, 500, jgncmdfile);
									jgn::string curentLine = jgncmdfline;
									//std::cout << i << std::endl;
									while (curentLine.find("endfor") == std::string::npos)
									{
										pos_token = curentLine.find("$i");
										if (pos_token != std::string::npos)
										{//replace $i
											char ireplace[10];
											itoa(i, ireplace, 10);
											curentLine.replace(pos_token, 2, ireplace);
										}
										//erase the spaces at the beggining of the line
										while (curentLine.c_str()[0] == ' ' || curentLine.c_str()[0] == '\t')
											curentLine.erase(0, 1);
										strcpy(jgncmdfline, curentLine.c_str());
										for (int j = 0; j < 500; j++)
										{
											ttt[j] = jgncmdfline[j];
											if (jgncmdfline[j] == 0)
											{
												break;
											}
										}
										//std::wcout << ttt << std::endl;
										//getchar();
										jgnCommands(ttt, 0);
										//std::cout << "done" << std::endl;
										//getchar();
										fgets(jgncmdfline, 500, jgncmdfile);
										curentLine = jgncmdfline;
									}
								}
							}
							else
							{
								jgnCommands(ttt, 0);
								fgets(jgncmdfline, 500, jgncmdfile);
							}

						}
						fclose(jgncmdfile);
						free(jgncmdfpath);
						//jgncmdfpath = 0;
					}
					//goto peintit;

					//return 0;
				}
				else
				{

					jgnCommands(ttt, 1);
				}

			peintit:

				DestroyWindow(CommandTextField);



				CommandTextField = CreateWindow(L"EDIT",
					0, WS_VISIBLE | WS_POPUP | ES_MULTILINE | ES_AUTOHSCROLL,
					(*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35,
					mnhwnd, NULL, NULL, NULL);

				oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

				SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

			peintit1:

				if (okrender)
				{
#if !defined(JGN_NO_CMD_HISTORY) 

					SendMessage(CommandTextHistory, EM_SETREADONLY, FALSE, NULL);
#endif
					okrender = 0;

#if !defined(JGN_NO_CMD_HISTORY) 
					SendMessage(CommandTextHistory, EM_SETSEL, 0, -1);
					SendMessage(CommandTextHistory, EM_SETSEL, -1, 0);
#endif

					for (i = 0; i < 50; i++)
					{

						if (i == 0 && ttt[0] == 13)
						{

						}
						else
						{
							if (ttt[i] == 0)
							{
								i = 100;
							}
#if !defined(JGN_NO_CMD_HISTORY) 
							else
							{
								SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ttt[i], 0);


							}
#endif
						}
					}
#if !defined(JGN_NO_CMD_HISTORY) 

					SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ucender[0], 0);
#endif
					SetFocus(CommandTextField);

#if !defined(JGN_NO_CMD_HISTORY) 
					SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);
#endif

					for (i = 0; i < 50; i++)
					{
						CommandBuffer[i] = 0;

					}

				}
				else
				{
					SetFocus(CommandTextField);
				}



			}
		}

	}



	return 0;
}
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
HWND JGN_CreateTray(std::string traytitle, HINSTANCE hInstance)
{
	// prepare for XP style controls
	InitCommonControls();

	// store instance handle and create dialog
	HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DLG_DIALOG),
		NULL, (DLGPROC)DlgProc);

	if (!hWnd)
	{
		perror("Could Not Create System Tray");
		return FALSE;
	}

	jgn_trayhwnd = hWnd;

	// Fill the NOTIFYICONDATA structure and call Shell_NotifyIcon

	// zero the structure - note:	Some Windows funtions require this but
	//								I can't be bothered which ones do and
	//								which ones don't.
	ZeroMemory(&niData, sizeof(NOTIFYICONDATA));

	// get Shell32 version number and set the size of the structure
	//		note:	the MSDN documentation about this is a little
	//				dubious and I'm not at all sure if the method
	//				bellow is correct

	ULONGLONG ullVersion = GetDllVersion(_T("Shell32.dll"));

	if (ullVersion >= MAKEDLLVERULL(5, 0, 0, 0))
		niData.cbSize = sizeof(NOTIFYICONDATA);
	else niData.cbSize = NOTIFYICONDATA_V2_SIZE;

	// the ID number can be anything you choose
	niData.uID = JGN_TRAYICON;

	// state which structure members are valid
	niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	// load the icon
	niData.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(JGN_TRAYICON),
		IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	// the window to send messages to and the message to send
	//		note:	the message value should be in the
	//				range of WM_APP through 0xBFFF
	niData.hWnd = hWnd;
	niData.uCallbackMessage = JGN_TRAYMSG;

	// tooltip message
	int i = 0;
	while (traytitle[i] != '\0' && i < 100)
	{
		szTitle[i] = traytitle[i];
		i++;
	}
	lstrcpyn(niData.szTip, szTitle, sizeof(niData.szTip) / sizeof(TCHAR));

	Shell_NotifyIcon(NIM_ADD, &niData);

	// free icon handle
	if (niData.hIcon && DestroyIcon(niData.hIcon))
		niData.hIcon = NULL;

	// call ShowWindow here to make the dialog initially visible

	return hWnd;
}



ULONGLONG GetDllVersion(LPCTSTR lpszDllName)
{
	ULONGLONG ullVersion = 0;
	HINSTANCE hinstDll;
	hinstDll = LoadLibrary(lpszDllName);
	if (hinstDll)
	{
		DLLGETVERSIONPROC pDllGetVersion;
		pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");
		if (pDllGetVersion)
		{
			DLLVERSIONINFO dvi;
			HRESULT hr;
			ZeroMemory(&dvi, sizeof(dvi));
			dvi.cbSize = sizeof(dvi);
			hr = (*pDllGetVersion)(&dvi);
			if (SUCCEEDED(hr))
				ullVersion = MAKEDLLVERULL(dvi.dwMajorVersion, dvi.dwMinorVersion, 0, 0);
		}
		FreeLibrary(hinstDll);
	}
	return ullVersion;
}




INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case JGN_TRAYMSG:
		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case WM_RBUTTONDOWN:
		case WM_CONTEXTMENU:
			ShowContextMenu(hWnd);
		}
		break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xFFF0) == SC_MINIMIZE)
		{
			ShowWindow(hWnd, SW_HIDE);
			return 1;
		}
		else if (wParam == IDM_ABOUT)
		{
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
		}



		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case SWM_SHOW:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case SWM_HIDE:
		case IDOK:
			ShowWindow(hWnd, SW_HIDE);
			break;
		case SWM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		}
		return 1;
	case WM_INITDIALOG:
		return OnInitDialog(hWnd);
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		niData.uFlags = 0;
		Shell_NotifyIcon(NIM_DELETE, &niData);
		PostQuitMessage(0);
		break;
	}
	return 0;
}


void ShowContextMenu(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	HMENU hMenu = CreatePopupMenu();
	if (hMenu)
	{
		if (IsWindowVisible(hWnd))
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_HIDE, _T("Hide"));
		else
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SHOW, _T("Show"));
		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, _T("Exit"));

		// note:	must set window to the foreground or the
		//			menu won't disappear when it should
		SetForegroundWindow(hWnd);

		TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
			pt.x, pt.y, 0, hWnd, NULL);
		DestroyMenu(hMenu);
	}
}


BOOL OnInitDialog(HWND hWnd)
{
	HMENU hMenu = GetSystemMenu(hWnd, FALSE);
	if (hMenu)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, IDM_ABOUT, _T("About"));
	}
	HICON hIcon = (HICON)LoadImage(hInst,
		MAKEINTRESOURCE(JGN_TRAYICON),
		IMAGE_ICON, 0, 0, LR_SHARED | LR_DEFAULTSIZE);
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	return TRUE;
}
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
void JGN_MainLoop()
{
	MSG msg;

	HACCEL hAccelTable;

	hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_JGNCLASS0));

	jgn_runing = 1;

	//UINT_PTR timerId = SetTimer(NULL, NULL, 1, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
		//while (PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE))
	{

		if ((!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) || !IsDialogMessage(msg.hwnd, &msg)))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Poscar_Build(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{

			EndDialog(hDlg, LOWORD(wParam));

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Choose_Format(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_CHOOSE_POSCAR)
		{
			EndDialog(hDlg, LOWORD(wParam));
			BuildPoscar(NewPC);


			return (INT_PTR)1;
		}
		else if (LOWORD(wParam) == ID_CHOOSE_LAMMPS)
		{
			EndDialog(hDlg, LOWORD(wParam));
			BuildLammps(NewPC);


			return (INT_PTR)2;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			return (INT_PTR)-1;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TUT(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void jgnCommands(LPTSTR ttt, int d)
{
	FILE* periodic_table;
	int isngtv = 0;
	//char *test1 = "Vector(";
	for (i = 0; i < 7; i++)
	{
		if (test1[0][i] == ttt[i])
		{

		}
		else
		{
			i = 100;

		}
	}
	if (i == 7)
	{

		okrender = 1;
		CustomSurfacesCount++;

		CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces_hkl = (int**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
		CustomSurfaces_hkl[CustomSurfacesCount - 1] = (int*)malloc(sizeof(float) * 3);
		CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0;
		help = (char*)(ttt + 7);
		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalh = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalh = 10 * crystalh + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalh = -crystalh;
		}

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[0][0] * crystalh;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[0][1] * crystalh;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[0][2] * crystalh;

		help += 2;
		isngtv = 0;


		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalk = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalk = 10 * crystalk + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalk = -crystalk;
		}
		help += 2;
		isngtv = 0;

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[1][0] * crystalk;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[1][1] * crystalk;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[1][2] * crystalk;

		if (help[0] >= 48 && help[0] <= 57)
		{
			crystall = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystall = 10 * crystall + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			crystall = -crystall;
		}

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[2][0] * crystall;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[2][1] * crystall;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[2][2] * crystall;

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));

		help += 2;
		isngtv = 0;



		if (help[0] >= 48 && help[0] <= 57)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;

		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
		}
		help += 2;
		isngtv = 0;


		if (okrender == 0)
		{
			CustomSurfacesCount--;
		}

		goto peintit;


	}
	//render on/off
	for (i = 0; i < 6; i++)
	{
		if (test1[9][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		help = (char*)(ttt + 7);

		jgn::string option = jgn::LPTSTR2string((LPTSTR)help, ')', 2);

		if (option == "on")
		{
			render_is_on = true;
		}
		else if (option == "of")
		{
			render_is_on = false;
		}
		else
		{
			okrender = 0;
			return;
		}
		goto peintit;

	}
	//"phonon("
	for (i = 0; i < 7; i++)
	{

		if (test1[8][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 7)
	{
		okrender = 1;

		float r = 0;

		help = (char*)(ttt + 7);

		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');

		if (rstr.isnumber())
		{
			ole = t * sized[0] * sized[1] * sized[2];

			r = stof(rstr);
			srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
			for (int g = 0; g < vs.N_groups; g++)
			{
				for (int i = 0; i < vs.group[g].N_atoms; i++)
				{
					vs.group[g].position[i].x = vs.group[g].position[i].x + r * (2 * (rand() / (float)RAND_MAX) - 1);
					vs.group[g].position[i].y = vs.group[g].position[i].y + r * (2 * (rand() / (float)RAND_MAX) - 1);
					vs.group[g].position[i].z = vs.group[g].position[i].z + r * (2 * (rand() / (float)RAND_MAX) - 1);
				}
			}
//#pragma omp parallel for firstprivate(ole, r)
//			for (int ole1 = 0; ole1 < ole; ole1++)
//			{
//				
//				crystal[2 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
//				crystal[3 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
//				crystal[4 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
//			}
		}
		else
		{
			okrender = 0;
			return;
		}

		goto peintit;

	}
	//"cut("
	bool cont = true;
	int Nnumbs = 0;//count 3 numbers
	int ibuff = 0;
	char buffer[10];
	int iintbuff = 0;
	int intbuff[3];
	i = 6;
	j = 0;
	while (Nnumbs!=3)
	{
		if (isdigit(ttt[j]) )
		{
			Nnumbs++;
			buffer[ibuff] = ttt[j];
			buffer[ibuff + 1] = '\0';

			intbuff[iintbuff] = atoi(buffer);
			iintbuff++;
			ibuff = 0;
			j++;
		}
		else if (ttt[j] == '-')
		{
			buffer[ibuff] = ttt[j];
			ibuff++;
			j++;
		}
		else
		{
			Nnumbs = 3;
			i = 0;
		}
	}


#if defined(JGN_CMD_PLANE) 
	for (i = 0; i < 4; i++)
	{
		if (test1[4][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
#endif
	if (i == 4)
	{

		okrender = 1;
		CustomSurfacesCount++;

		CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces_hkl = (int**)realloc(CustomSurfaces_hkl, sizeof(int*)*CustomSurfacesCount);
		CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
		CustomSurfaces_hkl[CustomSurfacesCount - 1] = (int*)malloc(sizeof(int) * 3);
		CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0;


#if defined(JGN_CMD_PLANE)
		crystalh = 0;
		crystalk = 0;
		crystall = 0;
		help = (char*)(ttt + 4);
		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalh = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalh = 10 * crystalh + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;


			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalh = -crystalh;
		}




		help += 2;
		isngtv = 0;


		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalk = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;

		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalk = 10 * crystalk + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalk = -crystalk;
		}
		help += 2;
		isngtv = 0;





		if (help[0] >= 48 && help[0] <= 57)
		{
			crystall = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystall = 10 * crystall + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystall = -crystall;
		}

#endif
		CustomSurfaces_hkl[CustomSurfacesCount - 1][0] = crystalh;
		CustomSurfaces_hkl[CustomSurfacesCount - 1][1] = crystalk;
		CustomSurfaces_hkl[CustomSurfacesCount - 1][2] = crystall;

		if (crystalh == 0)
		{
			if (crystalk == 0)
			{
				if (crystall == 0)//000 ok
				{
					CustomSurfacesCount--;
					okrender = 0;
					return;
				}
				else//00l ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[1].z - vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[1].y;
					CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[1].z + vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[1].x;
					CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[1].y - vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[1].x;


					CustomSurfaces[CustomSurfacesCount - 1][0] = crystall * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystall * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystall * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
			}
			else
			{
				if (crystall == 0)//0k0 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = -vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[2].z + vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[2].y;
					CustomSurfaces[CustomSurfacesCount - 1][1] = vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[2].z - vs.group[vs._isimulationBox].primitiveVec[0].z * vs.group[vs._isimulationBox].primitiveVec[2].x;
					CustomSurfaces[CustomSurfacesCount - 1][2] = -vs.group[vs._isimulationBox].primitiveVec[0].x * vs.group[vs._isimulationBox].primitiveVec[2].y + vs.group[vs._isimulationBox].primitiveVec[0].y * vs.group[vs._isimulationBox].primitiveVec[2].x;

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
				else//0kl ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[0].y * (vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) - vs.group[vs._isimulationBox].primitiveVec[0].z * (vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[0].x * (vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) + vs.group[vs._isimulationBox].primitiveVec[0].z * (vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[0].x * (vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) - vs.group[vs._isimulationBox].primitiveVec[0].y * (vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);


					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];
				}
			}
		}
		else
		{
			if (crystalk == 0)
			{
				if (crystall == 0)//h00 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[1].y * vs.group[vs._isimulationBox].primitiveVec[2].z - vs.group[vs._isimulationBox].primitiveVec[1].z * vs.group[vs._isimulationBox].primitiveVec[2].y;
					CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[1].x * vs.group[vs._isimulationBox].primitiveVec[2].z + vs.group[vs._isimulationBox].primitiveVec[1].z * vs.group[vs._isimulationBox].primitiveVec[2].x;
					CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[1].x * vs.group[vs._isimulationBox].primitiveVec[2].y - vs.group[vs._isimulationBox].primitiveVec[1].y * vs.group[vs._isimulationBox].primitiveVec[2].x;

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
				else//h0l ok
				{


					CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[1].y * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) - vs.group[vs._isimulationBox].primitiveVec[1].z * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[1].x * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) + vs.group[vs._isimulationBox].primitiveVec[1].z * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[1].x * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) - vs.group[vs._isimulationBox].primitiveVec[1].y * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall);

					CustomSurfaces[CustomSurfacesCount - 1][0] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];


				}
			}
			else
			{
				if (crystall == 0)//hk0 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = vs.group[vs._isimulationBox].primitiveVec[2].y * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) - vs.group[vs._isimulationBox].primitiveVec[2].z * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -vs.group[vs._isimulationBox].primitiveVec[2].x * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) + vs.group[vs._isimulationBox].primitiveVec[2].z * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][2] = vs.group[vs._isimulationBox].primitiveVec[2].x * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk) - vs.group[vs._isimulationBox].primitiveVec[2].y * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];
				}
				else//hkl
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) - (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -(vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].z / crystalk) + (vs.group[vs._isimulationBox].primitiveVec[0].z / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].z / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][2] = (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].x / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].y / crystalk) - (vs.group[vs._isimulationBox].primitiveVec[0].y / crystalh - vs.group[vs._isimulationBox].primitiveVec[2].y / crystall) * (vs.group[vs._isimulationBox].primitiveVec[0].x / crystalh - vs.group[vs._isimulationBox].primitiveVec[1].x / crystalk);

					CustomSurfaces[CustomSurfacesCount - 1][0] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];



				}
			}
		}

		
		/*jgn::vec3 p1 = vs.group[vs._isimulationBox].primitiveVec[0];
		std::cout << p1 << std::endl;
		if (crystalh == 0) {
			p1 = p1 * crystalh;
		}
		else
		{
			p1 = p1 * (1.f / crystalh);
		}
		jgn::vec3 p2 = vs.group[vs._isimulationBox].primitiveVec[1];
		std::cout << p2 << std::endl;
		if (crystalk == 0) {
			p2 = p2 * crystalk;
		}
		else
		{
			p2 = p2 * (1.f / crystalk);
		}
		jgn::vec3 p3 = vs.group[vs._isimulationBox].primitiveVec[2];
		std::cout << p3 << std::endl;
		if (crystall == 0) {
			p3 = p3 * crystall;
		}
		else
		{
			p3 = p3 * (1.f / crystall);
		}
		jgn::vec3 p12 = p2 - p1;
		jgn::vec3 p13 = p3 - p1;

		CustomSurfaces[CustomSurfacesCount - 1][0] = p12.y * p13.z - p12.z * p13.y;
		CustomSurfaces[CustomSurfacesCount - 1][1] = p12.z * p13.x - p12.x * p13.z;
		CustomSurfaces[CustomSurfacesCount - 1][2] = p12.x * p13.y - p12.y * p13.x;*/

		//CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] * vs.group[vs._isimulationBox].primitiveVec[0].abs();
		//CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] * vs.group[vs._isimulationBox].primitiveVec[1].abs();
		//CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] * vs.group[vs._isimulationBox].primitiveVec[2].abs();



		/*if (crystalh == 0)
		{
		if (JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[0][1], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0], 0, -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0], -ijk[0][0], 0) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[0][0], 0, ijk[0][2], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0] , -ijk[0][0], ijk[0][1], helping1*ijk[0][1] - helping2*ijk[0][0], 0) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[0][0], ijk[0][1], 0, ijk[0][2], 0, helping1*ijk[0][2] - helping3*ijk[0][0] , ijk[0][1], -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0]) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[0][2]-helping3*ijk[0][1], ijk[0][2], -ijk[0][1], 0, ijk[0][1], ijk[0][2], helping1*ijk[0][1]-helping2*ijk[0][0], -ijk[0][0], 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[0][2] - helping3*ijk[0][1], -ijk[0][1], ijk[0][0], 0, ijk[0][2], ijk[0][1], helping1*ijk[0][1] - helping2*ijk[0][0] , 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[0][2], helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][0], ijk[0][1], 0, ijk[0][1], -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][2], -ijk[0][1], helping1*ijk[0][2] - helping3*ijk[0][0], 0, -ijk[0][0], 0, ijk[0][1], ijk[0][2]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[0][2] - helping3*ijk[0][1], -ijk[0][1], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0], -ijk[0][0], ijk[0][0], 0, ijk[0][2]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[0][2], helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][2], 0, helping1*ijk[0][2] - helping3*ijk[0][0], ijk[0][0], ijk[0][1], 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		}

		}

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		if (crystalk == 0)
		{
		if (JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[1][1], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], 0, -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0], -ijk[1][0], 0) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[1][0], 0, ijk[1][2], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], -ijk[1][0], ijk[1][1], helping1*ijk[1][1] - helping2*ijk[1][0], 0) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[1][0], ijk[1][1], 0, ijk[1][2], 0, helping1*ijk[1][2] - helping3*ijk[1][0], ijk[1][1], -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0]) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], -ijk[1][1], 0, ijk[1][1], ijk[1][2], helping1*ijk[1][1] - helping2*ijk[1][0], -ijk[1][0], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[1][2] - helping3*ijk[1][1], -ijk[1][1], ijk[1][0], 0, ijk[1][2], ijk[1][1], helping1*ijk[1][1] - helping2*ijk[1][0], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[1][2], helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][0], ijk[1][1], 0, ijk[1][1], -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], -ijk[1][1], helping1*ijk[1][2] - helping3*ijk[1][0], 0, -ijk[1][0], 0, ijk[1][1], ijk[1][2]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[1][2] - helping3*ijk[1][1], -ijk[1][1], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], -ijk[1][0], ijk[1][0], 0, ijk[1][2]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[1][2], helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], 0, helping1*ijk[1][2] - helping3*ijk[1][0], ijk[1][0], ijk[1][1], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		}
		}

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		if (crystall == 0)
		{
		if (JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[2][1], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], 0, -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0], -ijk[2][0], 0) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[2][0], 0, ijk[2][2], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], -ijk[2][0], ijk[2][1], helping1*ijk[2][1] - helping2*ijk[2][0], 0) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[2][0], ijk[2][1], 0, ijk[2][2], 0, helping1*ijk[2][2] - helping3*ijk[2][0], ijk[2][1], -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0]) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], -ijk[2][1], 0, ijk[2][1], ijk[2][2], helping1*ijk[2][1] - helping2*ijk[2][0], -ijk[2][0], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[2][2] - helping3*ijk[2][1], -ijk[2][1], ijk[2][0], 0, ijk[2][2], ijk[2][1], helping1*ijk[2][1] - helping2*ijk[2][0], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[2][2], helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][0], ijk[2][1], 0, ijk[2][1], -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], -ijk[2][1], helping1*ijk[2][2] - helping3*ijk[2][0], 0, -ijk[2][0], 0, ijk[2][1], ijk[2][2]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[2][2] - helping3*ijk[2][1], -ijk[2][1], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], -ijk[2][0], ijk[2][0], 0, ijk[2][2]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[2][2], helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], 0, helping1*ijk[2][2] - helping3*ijk[2][0], ijk[2][0], ijk[2][1], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		}
		}*/


		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));

		//std::cout << CustomSurfaces[CustomSurfacesCount - 1][0] << " " << CustomSurfaces[CustomSurfacesCount - 1][1] << " " << CustomSurfaces[CustomSurfacesCount - 1][2] << std::endl;
		help += 2;
		isngtv = 0;



		if (help[0] >= 48 && help[0] <= 57)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
		}
		help += 2;
		isngtv = 0;

		if (okrender == 0)
		{
			CustomSurfacesCount--;
		}



		goto peintit;


	}








	//char *test2 = "Clean";
	for (i = 0; i < 5; i++)
	{
		if (test1[1][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}

	if (i == 5)
	{
		okrender = 1;
		CustomSurfacesCount = 0;
		for (i = 0; i < CustomSurfacesCount; i++)
		{
			delete(CustomSurfaces[i]);
		}
		delete(CustomSurfaces);
		CustomSurfaces = NULL;
		goto peintit;



	}

	//char *test3 = "Undo";
	for (i = 0; i < 4; i++)
	{
		if (test1[2][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 4)
	{
		okrender = 1;
		CustomSurfacesCount--;
		if (CustomSurfacesCount < 0)
		{
			CustomSurfacesCount = 0;
		}

		goto peintit;


	}
	//char *test4 = "spheres";
	for (i = 0; i < 7; i++)
	{
		if (test1[6][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 7)
	{
		okrender = 1;
		shperes_on = 1;
		glEnable(GL_LIGHTING);

		sphStacks = 2;
		sphSides = 3;

		goto peintit;

	}

	//char *test4 = "points";
	for (i = 0; i < 6; i++)
	{
		if (test1[7][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		shperes_on = 0;
		glDisable(GL_LIGHTING);

		goto peintit;

	}

	//char *test4 = "SuperCell(";
	for (i = 0; i < 10; i++)
	{
		if (test1[3][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 10)
	{
		okrender = 1;
		tb._sellectedfordistance[1].y = -1;
		help = (char*)(ttt + 10);
		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[0] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[0] = 10 * sizedprotector[0] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		help += 2;




		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[1] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[1] = 10 * sizedprotector[1] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		help += 2;



		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[2] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[2] = 10 * sizedprotector[2] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;

				return;
			}
		}
		loop = 0;
		help += 2;



		if (okrender)
		{


			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			sized[0] = sizedprotector[0];
			sized[1] = sizedprotector[1];
			sized[2] = sizedprotector[2];
			custom_sized[0] = sizedprotector[0];
			custom_sized[1] = sizedprotector[1];
			custom_sized[2] = sizedprotector[2];

			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];

			if (sized[0] / 2 != sized[0] / 2.0)
			{
				xexe[0] = 1;
			}

			if (sized[1] / 2 != sized[1] / 2.0)
			{
				xexe[1] = 1;
			}

			if (sized[2] / 2 != sized[2] / 2.0)
			{
				xexe[2] = 1;
			}
			//periodic_table = fopen("periodic_table.jgn", "r");

			//jgn::heapRealloc();
			//double ttest = omp_get_wtime();
			int sx = sized[0];
			int sy = sized[1];
			int sz = sized[2];
								
			vs.N_atoms = sx * sy * sz * vs.original->N_atoms;
			vs.reserve(sx, sy, sz);

			/*std::cout << vs.group[0].position[0]			<<  std::endl;
			std::cout << vs.group[0].type[0]				<<  std::endl;
			std::cout << vs.group[0].selective_dynamics[0] 	<<  std::endl;
			std::cout << vs.group[0].color[0] 				<<  std::endl;
			std::cout << vs.group[0].number[0] 				<<  std::endl;
			std::cout << vs.group[0].weight[0] 				<<  std::endl;
			std::cout << vs.group[0].radius[0] 				<<  std::endl;
			std::cout << vs.group[0].isSelected[0] 			<<  std::endl;
			std::cout << vs.group[0].isdeleted[0] 			<<  std::endl;
			std::cout << vs.group[0].iscut[0] 				<<  std::endl;*/

			int as = 0;//atom position starts at
			for (int g = 0; g < vs.N_groups; g++)
			{//for every group
				for (int k = 0; k < sz; k++)
				{
					for (int j = 0; j < sy; j++)
					{
						for (int i = 0; i < sx; i++)
						{
							for (int a = 0; a < vs.original->group[g].N_atoms; a++)
							{//for every atom within the group
								//std::cout << g << " " << k << " " << j << " " << i << " " << a << std::endl;
								vs.group[g].position[a + as] = vs.original->group[g].position[a] +vs.original->group[vs._isimulationBox].primitiveVec[0] * i + vs.original->group[vs._isimulationBox].primitiveVec[1] * j + vs.original->group[vs._isimulationBox].primitiveVec[2] * k;
								vs.group[g].type[a + as] = vs.original->group[g].type[a];
								vs.group[g].selective_dynamics[a + as] = vs.original->group[g].selective_dynamics[a];
								vs.group[g].color[a + as] = vs.original->group[g].color[a];
								vs.group[g].number[a + as] = vs.original->group[g].number[a];
								vs.group[g].weight[a + as] = vs.original->group[g].weight[a];
								vs.group[g].radius[a + as] = vs.original->group[g].radius[a];
								vs.group[g].isSelected[a + as] = vs.original->group[g].isSelected[a];
								vs.group[g].isdeleted[a + as] = vs.original->group[g].isdeleted[a];
								vs.group[g].iscut[a + as] = vs.original->group[g].iscut[a];
							}
							as += vs.original->group[g].N_atoms;
						}
					}
				}
			}
		}
		if (d == 0)
			okrender = 0;
		goto peintit;

	}
	//char *test4 = "randSelection%(";
	for (i = 0; i < 15; i++)
	{
		if (test1[10][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 15)
	{
		okrender = 1;
		help = (char*)(ttt + 15);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		float percent = 0;//0-1
		int pos_token = rstr.find(")");
		//extract the percentage
		jgn::string percent_input = (char*)rstr.substr(0, pos_token - 1).c_str();
		if (percent_input.isnumber())
		{
			percent = std::stof(percent_input);
		}
		else
		{
			return;
		}

		vs.unsellectAll();
		vs._sellectHistory2undo = 0;
		ole = 0;
		//random sellect %
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		for (int g = 0; g < vs.N_groups; g++)
		{
			for (int i = 0; i < vs.group[g].N_atoms; i++)
			{
				ole++;
				if (((float)rand() / (float)RAND_MAX) < percent)
				{
					vs.group[g].isSelected[i] = true;
				}
			}
		}
		//change element type
		//vs.selected_change_element(element_input);
		//vs.updateinfo();
		goto peintit;
	}

	//char *test4 = "randSelection(";
	for (i = 0; i < 14; i++)
	{
		if (test1[15][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 14)
	{
		okrender = 1;
		help = (char*)(ttt + 14);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		float Natoms = 0;//0-1
		int pos_token = rstr.find(")");
		//extract the percentage
		jgn::string percent_input = (char*)rstr.substr(0, pos_token - 1).c_str();
		if (percent_input.isnumber())
		{
			Natoms = std::stof(percent_input);
		}
		else
		{
			return;
		}

		vs.unsellectAll();
		vs._sellectHistory2undo = 0;
		ole = 0;
		//random sellect
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		for (int i = 0; i < Natoms; i++)
		{
			int atos = vs.N_atoms * rand() / (float)RAND_MAX;
			if (vs._sellectHistory[atos].z != -1)
			{
				i--;
			}
			else
			{
				vs._sellectHistory[atos].z = 0;
				vs.group[vs._sellectHistory[atos].x].isSelected[vs._sellectHistory[atos].y] = true;
			}
		}
		//change element type
		//vs.selected_change_element(element_input);
		//vs.updateinfo();
		goto peintit;
	}

	//char *test4 = "changeElement(";
	for (i = 0; i < 14; i++)
	{
		if (test1[11][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 14)
	{
		okrender = 1;
		help = (char*)(ttt + 14);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		//get rid of the spaces
		int rstrpos = rstr.find(" ");
		while (rstrpos != std::string::npos)
		{
			rstr.erase(rstrpos, 1);
			rstrpos = rstr.find(" ");
		}
		vs.selected_change_element(rstr);
		vs.updateinfo();
		vs.unsellectAll();
		goto peintit;
	}

	//char *test4 = "save(";
	for (i = 0; i < 5; i++)
	{
		if (test1[12][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 5)
	{
		okrender = 1;
		help = (char*)(ttt + 5);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		rstr.erase(0, 1);
		rstr.erase(rstr.size() - 1, 1);
		//TODO: do a stupid proof test
		BuildPoscar((char*)rstr.c_str());

		goto peintit;

	}

	//char *test4 = "loadOrigin";
	for (i = 0; i < 10; i++)
	{
		if (test1[13][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 10)
	{
		okrender = 1;
		//vs = vs.original;

		jgnCommands(L"supercell(1,1,1)", 1);
		jgnCommands(L"clean", 1);
		

		goto peintit;
	}
	//char *test4 = "rotate(";
	for (i = 0; i < 7; i++)
	{

		if (test1[14][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 7)
	{
		okrender = 1;
		help = (char*)(ttt + 7);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		rstr.erase();
		int rstrpos = rstr.find(",");
		jgn::string raxes = (char*)rstr.substr(0, rstrpos).c_str();
		if (raxes.compare("x") == 0)
		{
			vs.selected_change_hovered_axes = X_AXIS;
		}
		else if (raxes.compare("y") == 0)
		{
			vs.selected_change_hovered_axes = Y_AXIS;
		}
		else if (raxes.compare("z") == 0)
		{
			vs.selected_change_hovered_axes = Z_AXIS;
		}
		rstr.erase(0, rstrpos + 1);
		float rangle = atof(rstr.substr(0, rstr.size()).c_str());
		rangle = M_PI * rangle / 180;

		vs.toggleselected_rotate(true);
		vs.isrotating_theselected = true;
		vs.rotate_selected(jgn::vec2(0, 0), jgn::vec2(0, 0), rangle);
		vs.isrotating_theselected = false;
		vs.toggleselected_rotate(false);

		goto peintit;
	}

	//char *test4 = "decahedron(";
	for (i = 0; i < 11; i++)
	{
		if (test1[24][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 11)
	{
		okrender = 1;
		help = (char*)(ttt + 11);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		//(int p, int q, int r, float lattice_constant)
		int p, q, r;
		float lattice_constant;
		// get p
		int rstrpos = rstr.find(",");
		jgn::string substr = (char*)rstr.substr(0, rstrpos).c_str();
		p = std::stoi(substr.c_str());
		rstr.erase(0, rstrpos + 1);
		// get q
		rstrpos = rstr.find(",");
		substr = (char*)rstr.substr(0, rstrpos).c_str();
		q = std::stoi(substr.c_str());
		rstr.erase(0, rstrpos + 1);
		// get r
		rstrpos = rstr.find(",");
		substr = (char*)rstr.substr(0, rstrpos).c_str();
		r = std::stoi(substr.c_str());
		rstr.erase(0, rstrpos + 1);
		// get lattice_constant
		lattice_constant = std::stof(rstr.c_str());

		jgnCommands(L"restart", 1);
		Group mygroup = decahedron(p, q, r, lattice_constant);
		std::ofstream decahedron_file;
		decahedron_file.open("decahedron.todel");
		decahedron_file << "This should not be here. Pls delete it" << std::endl;
		decahedron_file << "1.0" << std::endl;
		decahedron_file << mygroup.primitiveVec[0] << std::endl;
		decahedron_file << mygroup.primitiveVec[1] << std::endl;
		decahedron_file << mygroup.primitiveVec[2] << std::endl;
		decahedron_file << "H\n" << mygroup.N_atoms << "\nCartesian" << std::endl;
		for (int i = 0; i < mygroup.N_atoms; i++)
		{
			decahedron_file << mygroup.position[i] << std::endl;
		}
		decahedron_file.close();
		JGN_DropFile("decahedron.todel");
		remove("decahedron.todel");
		jgn_file_dropd = true;
		goto peintit;
	}

	//char *test4 = "icosahedron(";
	for (i = 0; i < 12; i++)
	{
		if (test1[23][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 12)
	{
		okrender = 1;
		help = (char*)(ttt + 12);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		float lattice_constant;
		int noshells;
		// get lattice_constant
		int rstrpos = rstr.find(",");
		jgn::string lc = (char*)rstr.substr(0, rstrpos).c_str();
		lattice_constant = std::stof(lc.c_str());
		rstr.erase(0, rstrpos + 1);
		// get noshells
		noshells = std::stoi(rstr.c_str());

		jgnCommands(L"restart", 1);
		Group mygroup = icosahedral(lattice_constant, noshells);
		std::ofstream icosahedral_file;
		icosahedral_file.open("icosahedral.todel");
		icosahedral_file << "This should not be here. Pls delete it" << std::endl;
		icosahedral_file << "1.0" << std::endl;
		icosahedral_file << mygroup.primitiveVec[0] << std::endl;
		icosahedral_file << mygroup.primitiveVec[1] << std::endl;
		icosahedral_file << mygroup.primitiveVec[2] << std::endl;
		icosahedral_file << "H\n" << mygroup.N_atoms << "\nCartesian" << std::endl;
		for (int i = 0; i < mygroup.N_atoms; i++)
		{
			icosahedral_file << mygroup.position[i] << std::endl;
		}
		icosahedral_file.close();
		JGN_DropFile("icosahedral.todel");
		remove("icosahedral.todel");
		jgn_file_dropd = true;
		goto peintit;
	}
	//char *test4 = "magmomup(";
	for (i = 0; i < 9; i++)
	{

		if (test1[22][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 9)
	{
		okrender = 1;
		help = (char*)(ttt + 9);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		float h, k, l;
		jgn::vec3 vr;//rotate everything around vr
		float theta;//for that amount of rad
		jgn::quaternion vrq;//the equivalent of vr for quaternion
		jgn::quaternion atomq;//the equivalent quartenion of every atomic position

		int rstrpos = rstr.find(",");
		jgn::string raxes = (char*)rstr.substr(0, rstrpos).c_str();
		h = std::stof(raxes.c_str());
		rstr.erase(0, rstrpos + 1);

		rstrpos = rstr.find(",");
		raxes = (char*)rstr.substr(0, rstrpos).c_str();
		k = std::stoi(raxes.c_str());
		rstr.erase(0, rstrpos + 1);

		l= std::stoi(rstr.c_str());
		//h k l are good up till here

		jgn::quaternion millervec(0, 0, 0, 0);
		//works only for cubic TODO
		if (h != 0)
		{
			millervec.b = h;
		}
		else
		{
			millervec.b = 0;
		}
		if (k != 0)
		{
			millervec.c = k;
		}
		else
		{
			millervec.c = 0;
		}
		if (l != 0)
		{
			millervec.d = l;
		}
		else
		{
			millervec.d = 0;
		}
		//find the angle between vec3(0,0,1) and millervec
		theta = std::acos(millervec.d / millervec.vec3().abs())*0.72;//in rad
		//angle correct so far
		
		vr = jgn::xproduct(jgn::vec3(0, 0, 1), millervec.vec3());
		//now we have vr
		float vrabs = vr.abs();
		vr.x = vr.x / vrabs;
		vr.y = vr.y / vrabs;
		vr.z = vr.z / vrabs;
		//now we have vr as a unit vector
		vrq.a = cos(theta / 2.f);
		vrq.b = vr.x*sin(theta / 2.f);
		vrq.c = vr.y*sin(theta / 2.f);
		vrq.d = vr.z*sin(theta / 2.f);
		//now we have the quartenion
		//we will now make the rotation of the atoms
		for (int g = 0; g < vs.N_groups; g++)
		{//for every group
			for (int i = 0; i < vs.group[g].N_atoms; i++)
			{//for every atom
				//create the quartenion
				atomq.a = 0;
				atomq.b = vs.group[g].position[i].x;
				atomq.c = vs.group[g].position[i].y;
				atomq.d = vs.group[g].position[i].z;
				jgn::quaternion ans = (vrq*atomq)*vrq.conjugate();
				vs.group[g].position[i].x = ans.b;
				vs.group[g].position[i].y = ans.c;
				vs.group[g].position[i].z = ans.d;
			}
		}
		//we will now rotate the primitive vectors
		//first vector
		//create the quartenion
		for (i = 0; i < 3; i++)
		{
			atomq.a = 0;
			atomq.b = vs.group[vs._isimulationBox].primitiveVec[i].x;
			atomq.c = vs.group[vs._isimulationBox].primitiveVec[i].y;
			atomq.d = vs.group[vs._isimulationBox].primitiveVec[i].z;
			jgn::quaternion ans = (vrq*atomq)*vrq.conjugate();
			vs.group[vs._isimulationBox].primitiveVec[i].x = ans.b;
			vs.group[vs._isimulationBox].primitiveVec[i].y = ans.c;
			vs.group[vs._isimulationBox].primitiveVec[i].z = ans.d;
			vs.setSimulationBox(vs._isimulationBox);
		}
		goto peintit;
	}

	//char *test4 = "delete";
	for (i = 0; i < 6; i++)
	{
		if (test1[16][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		deleteSelected();
		vs.updateinfo();
		goto peintit;
	}

	//char *test4 = "restart";
	for (i = 0; i < 7; i++)
	{
		if (test1[17][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 7)
	{
		okrender = 1;
		vs.restart();
		goto peintit;
	}

	//char *test4 = "fopen(";
	for (i = 0; i < 6; i++)
	{
		if (test1[18][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		help = (char*)(ttt + 7);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, '"');
		strcpy(inpf, rstr.c_str());//for legacy reasons
		JGN_DropFile(rstr.c_str());
		jgn_file_dropd = true;
		goto peintit;
	}

	//char *test4 = "placerandomly(";
	for (i = 0; i < 14; i++)
	{
		if (test1[21][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 14)
	{
		//TODO: stupid proof
		okrender = 1;

		help = (char*)(ttt + 14);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		float min_dist = std::stoi(rstr.c_str());
		
		jgn::vec3 x, y, z;
		jgn::vec3 position;

		bool done = false;

		while (!done)
		{
			//assume we are done
			done = true;

			srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
			x = vs.group[vs._isimulationBox].primitiveVec[0] * (rand() / (float)RAND_MAX) * 0.8;
			srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 1);
			y = vs.group[vs._isimulationBox].primitiveVec[1] * (rand() / (float)RAND_MAX) * 0.8;
			srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 2);
			z = vs.group[vs._isimulationBox].primitiveVec[2] * (rand() / (float)RAND_MAX) * 0.8;

			//this is the random position
			position = x + y + z;

			for (int g = 0; g < vs.N_groups; g++)
			{
				for (int i = 0; i < vs.group[g].N_atoms; i++)
				{
					if (jgn::dist3dSquare(position.x, vs.group[g].position[i].x) < min_dist)
					{
						done = false;
					}
				}
			}
		}
		
		vs.group[0].N_atoms++;
		vs.group[0].color.push_back(vs.group[0].color[vs.group[0].N_atoms - 2]);
		vs.group[0].iscut.push_back(false);
		vs.group[0].isdeleted.push_back(false);
		vs.group[0].ishovered.push_back(false);
		vs.group[0].isSelected.push_back(false);
		vs.group[0].number.push_back(vs.group[0].number[vs.group[0].N_atoms - 2]);
		vs.group[0].N_atoms_per_type[vs.group[0]._N_types - 1]++;
		vs.group[0].position.push_back(position);
		vs.group[0].radius.push_back(vs.group[0].radius[vs.group[0].N_atoms - 2]);
		vs.group[0].selective_dynamics.push_back(vs.group[0].selective_dynamics[vs.group[0].N_atoms - 2]);
		vs.group[0].type.push_back(vs.group[0].type[vs.group[0].N_atoms - 2]);
		vs.group[0].weight.push_back(vs.group[0].weight[vs.group[0].N_atoms - 2]);
		goto peintit;
	}

	//char *test4 = "mkfacet(";
	for (i = 0; i < 8; i++)
	{
		if (test1[19][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 8)
	{
		okrender = 1;
		help = (char*)(ttt + 8);
		jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, ')');
		rstr.eraseblank();

		int h, k, l;
		jgn::vec3 v0;//the vector that will become perpendicular to z-axis
		jgn::quaternion atomq;//the equivalent quartenion of every atomic position
		jgn::vec3 vr;//we will rotate everything around this vector
		jgn::quaternion vrq;//the equivalent of vr for quaternion
		float theta;//rotate everything by theta around vr
		jgn::quaternion fvpr[3];//here we will construct the new primitive vectors
		jgn::quaternion fvpr0[3];//same but keeping the initial values
		//h
		int pos_token = rstr.find(",");
		if (pos_token == std::string::npos || !((jgn::string)((char*)rstr.substr(0, pos_token).c_str())).isnumber())
		{
			okrender = 0;
			goto peintit;
		}
		h = std::stoi(rstr.substr(0, pos_token).c_str());
		rstr.erase(0, pos_token + 1);
		//k
		pos_token = rstr.find(",");
		if (pos_token == std::string::npos || !((jgn::string)((char*)rstr.substr(0, pos_token).c_str())).isnumber())
		{
			okrender = 0;
			goto peintit;
		}
		k = std::stoi(rstr.substr(0, pos_token).c_str());
		rstr.erase(0, pos_token + 1);
		//l
		if (!((jgn::string)((char*)rstr.substr(0, pos_token).c_str())).isnumber())
		{
			okrender = 0;
			goto peintit;
		}
		l = std::stoi(rstr.c_str());
		//TODO:reduce the indexes
		//now we have    h k l
		jgn::vec3* vpr = vs.original->group[vs._isimulationBox].primitiveVec;//primitive vectors
		jgn::vec3 hkl = jgn::vec3(h, k, l);
		v0 = *jgn::millerP2V(&hkl, vpr);
		//std::cout << "m" << *m << std::endl;
		//std::cout << v0 << std::endl;
		//now we have v0
		vr.x = v0.y;
		vr.y = -v0.x;
		vr.z = 0;
		//now we have vr
		if (vr.abs() == 0)
		{
			okrender = 0;
			goto peintit;
		}
		float vrabs = vr.abs();
		vr.x = vr.x / vrabs;
		vr.y = vr.y / vrabs;
		//now we have vr as a unit vector
		theta = std::acos((v0.z) / v0.abs());
		//now we have theta in radians
		vrq.a = cos(theta / 2.f);
		vrq.b = vr.x*sin(theta / 2.f);
		vrq.c = vr.y*sin(theta / 2.f);
		vrq.d = vr.z*sin(theta / 2.f);
		//now we have the quartenion
		//first create a big bulk 
		jgnCommands(L"supercell(10,10,10)", 0);
		//we will now make the rotation
		for (int g = 0; g < vs.N_groups; g++)
		{//for every group
			for (int i = 0; i < vs.group[g].N_atoms; i++)
			{//for every atom
				//create the quartenion
				//first center the bulk at the origin
				vs.group[g].position[i] = vs.group[g].position[i].translate(vs.group[vs._isimulationBox].primitiveVec[0] * (-0.5));
				vs.group[g].position[i] = vs.group[g].position[i].translate(vs.group[vs._isimulationBox].primitiveVec[1] * (-0.5));
				vs.group[g].position[i] = vs.group[g].position[i].translate(vs.group[vs._isimulationBox].primitiveVec[2] * (-0.5));
				atomq.a = 0;
				atomq.b = vs.group[g].position[i].x;
				atomq.c = vs.group[g].position[i].y;
				atomq.d = vs.group[g].position[i].z;
				jgn::quaternion ans = (vrq*atomq)*vrq.conjugate();
				vs.group[g].position[i].x = ans.b;
				vs.group[g].position[i].y = ans.c;
				vs.group[g].position[i].z = ans.d;
			}
		}
		//lets prepare the primitive vectors
		//create a grid of duplicated (0,0,0) points and rotate it
		jgn::quaternion duplicateO[10][10][10];
		for (int i = -5; i < 5; i++)
		{
			for (int j = -5; j < 5; j++)
			{
				for (int k = -5; k < 5; k++)
				{
					duplicateO[i + 5][j + 5][k + 5] = jgn::quaternion(0,
						vpr[0].x*i + vpr[1].x*j + vpr[2].x*k,
						vpr[0].y*i + vpr[1].y*j + vpr[2].y*k,
						vpr[0].z*i + vpr[1].z*j + vpr[2].z*k);
					duplicateO[i + 5][j + 5][k + 5] = (vrq*duplicateO[i + 5][j + 5][k + 5])*vrq.conjugate();
				}
			}
		}
		//z
		//x
		//y
		fvpr[0] = jgn::quaternion(0, 1000, 1000, 1000);
		for (int i = 9 ; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)
			{
				for (int k = 9; k >= 0; k--)
				{
					if (duplicateO[i][j][k].vec3().abs() != 0)
					{
						if (abs(duplicateO[i][j][k].b) < 0.01 && abs(duplicateO[i][j][k].c) < 0.01)
						{
							if (duplicateO[i][j][k].vec3().abs() < fvpr[0].vec3().abs())
							{
								fvpr[0] = duplicateO[i][j][k];
							}
						}
					}
				}
			}
		}

		fvpr[1] = jgn::quaternion(0, 1000, 1000, 1000);
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)
			{
				for (int k = 9; k >= 0; k--)
				{
					if (duplicateO[i][j][k].vec3().abs() != 0)
						if (abs(duplicateO[i][j][k].d) < 0.01)
						{
							if (duplicateO[i][j][k].vec3().abs() < fvpr[1].vec3().abs())
							{
								fvpr[1] = duplicateO[i][j][k];
							}
						}
				}
			}
		}

		fvpr[2] = jgn::quaternion(0, 1000, 1000, 1000);
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)
			{
				for (int k = 9; k >= 0; k--)
				{
					if (duplicateO[i][j][k].vec3().abs() != 0)
						if (abs(duplicateO[i][j][k].d) < 0.01)
						{
							if (duplicateO[i][j][k].vec3().abs() < fvpr[2].vec3().abs())
							{
								if (!(abs(fvpr[1].b / duplicateO[i][j][k].b - fvpr[1].c / duplicateO[i][j][k].c) < 0.01))
								{
									fvpr[2] = duplicateO[i][j][k];
								}
							}
						}
				}
			}
		}



		sized[0] = 1;
		sized[1] = 1;
		sized[2] = 1;

		//the primitive vectors are ready... put them in the vs.group[...
		vs.group[vs._isimulationBox].primitiveVec[2].x = fvpr[0].b;
		vs.group[vs._isimulationBox].primitiveVec[2].y = fvpr[0].c;
		vs.group[vs._isimulationBox].primitiveVec[2].z = fvpr[0].d;

		vs.group[vs._isimulationBox].primitiveVec[0].x = fvpr[1].b;
		vs.group[vs._isimulationBox].primitiveVec[0].y = fvpr[1].c;
		vs.group[vs._isimulationBox].primitiveVec[0].z = fvpr[1].d;

		vs.group[vs._isimulationBox].primitiveVec[1].x = fvpr[2].b;
		vs.group[vs._isimulationBox].primitiveVec[1].y = fvpr[2].c;
		vs.group[vs._isimulationBox].primitiveVec[1].z = fvpr[2].d;

		if (vs.group[vs._isimulationBox].primitiveVec[0].x < 0)
		{
			vs.group[vs._isimulationBox].primitiveVec[0].x = -fvpr[1].b;
			vs.group[vs._isimulationBox].primitiveVec[0].y = -fvpr[1].c;
			vs.group[vs._isimulationBox].primitiveVec[0].z = -fvpr[1].d;
		}
		if (vs.group[vs._isimulationBox].primitiveVec[1].y < 0)
		{
			vs.group[vs._isimulationBox].primitiveVec[1].x = -fvpr[2].b;
			vs.group[vs._isimulationBox].primitiveVec[1].y = -fvpr[2].c;
			vs.group[vs._isimulationBox].primitiveVec[1].z = -fvpr[2].d;
		}

		vs._updateSimulationBox();
		//cut every atom outside of the unit cell
		//x
		jgn::string tocut = test1[4];
		char *buf = new char[100];
		float tantheta = vs.group[vs._isimulationBox].primitiveVec[1].x / vs.group[vs._isimulationBox].primitiveVec[1].y;
		tocut += "1,0,0,";
		itoa((int)abs((vs.group[vs._isimulationBox].primitiveVec[0].x) - (vs.group[vs._isimulationBox].primitiveVec[0].y*tantheta) - 1), buf, 10);
		tocut += buf;
		tocut += ')';
		jgnCommands(jgn::string2LPTSTR(tocut), 0);
		CustomSurfaces[CustomSurfacesCount - 1][3] = vs.group[vs._isimulationBox].primitiveVec[0].x*CustomSurfaces[CustomSurfacesCount - 1][0] + vs.group[vs._isimulationBox].primitiveVec[0].y*CustomSurfaces[CustomSurfacesCount - 1][1] + vs.group[vs._isimulationBox].primitiveVec[0].z*CustomSurfaces[CustomSurfacesCount - 1][2] - 0.1;
		//-x
		tocut = test1[4];
		tocut += "-1,0,0,1)";
		jgnCommands(jgn::string2LPTSTR(tocut), 0);
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0.1;
		//y
		tantheta = vs.group[vs._isimulationBox].primitiveVec[0].y / vs.group[vs._isimulationBox].primitiveVec[0].x;
		tocut = test1[4];
		tocut += "0,1,0,";
		itoa((int)abs((vs.group[vs._isimulationBox].primitiveVec[1].y) - (vs.group[vs._isimulationBox].primitiveVec[1].x*tantheta) - 1), buf, 10);
		tocut += buf;
		tocut += ')';
		jgnCommands(jgn::string2LPTSTR(tocut), 0);
		CustomSurfaces[CustomSurfacesCount - 1][3] = vs.group[vs._isimulationBox].primitiveVec[1].x*CustomSurfaces[CustomSurfacesCount - 1][0] + vs.group[vs._isimulationBox].primitiveVec[1].y*CustomSurfaces[CustomSurfacesCount - 1][1] + vs.group[vs._isimulationBox].primitiveVec[1].z*CustomSurfaces[CustomSurfacesCount - 1][2] - 0.1;
		//-y
		tocut = test1[4];
		tocut += "0,-1,0,1)";
		jgnCommands(jgn::string2LPTSTR(tocut), 0);
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0.1;
		//z
		tocut = test1[4];
		tocut += "0,0,1,";
		itoa((int)(vs.group[vs._isimulationBox].primitiveVec[2].z - 1), buf, 10);
		tocut += buf;
		tocut += ')';
		jgnCommands(jgn::string2LPTSTR(tocut), 0);
		CustomSurfaces[CustomSurfacesCount - 1][3] = vs.group[vs._isimulationBox].primitiveVec[2].z - 0.1;
		//-z
		tocut = test1[4];
		tocut += "0,0,-1,1)";
		jgnCommands(jgn::string2LPTSTR(tocut), 0);
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0.1;

		goto peintit;
	}

	//char *test4 = "randstress";
	for (i = 0; i < 10; i++)
	{
		if (test1[20][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 10)
	{
		okrender = 1;
		//help = (char*)(ttt + 7);
		//jgn::string rstr = jgn::LPTSTR2string((LPTSTR)help, '"');
		//strcpy(inpf, rstr.c_str());//for legacy reasons
		//JGN_DropFile(rstr.c_str());
		//jgn_file_dropd = true;
		///1-x
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		float stress = vs.group[vs._isimulationBox].primitiveVec[0].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[0].x += stress;
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()+1);
		stress = vs.group[vs._isimulationBox].primitiveVec[0].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[0].y += stress;
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 2);
		stress = vs.group[vs._isimulationBox].primitiveVec[0].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[0].z += stress;

		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 3);
		stress = vs.group[vs._isimulationBox].primitiveVec[1].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[1].x += stress;
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 4);
		stress = vs.group[vs._isimulationBox].primitiveVec[1].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[1].y += stress;
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 5);
		stress = vs.group[vs._isimulationBox].primitiveVec[1].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[1].z += stress;

		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 6);
		stress = vs.group[vs._isimulationBox].primitiveVec[2].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[2].x += stress;
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 7);
		stress = vs.group[vs._isimulationBox].primitiveVec[2].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[2].y += stress;
		srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 8);
		stress = vs.group[vs._isimulationBox].primitiveVec[2].abs()*(rand() / (float)RAND_MAX * 2 - 1) * 0.04;
		vs.group[vs._isimulationBox].primitiveVec[2].z += stress;

		vs._updateSimulationBox();

		for (int g = 0; g<vs.N_groups; g++)
		{
			for (int i = 0; i < vs.group[g].N_atoms; i++)
			{
				vs.group[g].position[i].x = vs.group[g].fractional[i].x*vs.group[vs._isimulationBox].primitiveVec[0].x + vs.group[g].fractional[i].y*vs.group[vs._isimulationBox].primitiveVec[1].x + vs.group[g].fractional[i].z*vs.group[vs._isimulationBox].primitiveVec[2].x;
				vs.group[g].position[i].y = vs.group[g].fractional[i].x*vs.group[vs._isimulationBox].primitiveVec[0].y + vs.group[g].fractional[i].y*vs.group[vs._isimulationBox].primitiveVec[1].y + vs.group[g].fractional[i].z*vs.group[vs._isimulationBox].primitiveVec[2].y;
				vs.group[g].position[i].z = vs.group[g].fractional[i].x*vs.group[vs._isimulationBox].primitiveVec[0].z + vs.group[g].fractional[i].y*vs.group[vs._isimulationBox].primitiveVec[1].z + vs.group[g].fractional[i].z*vs.group[vs._isimulationBox].primitiveVec[2].z;
			}
		}

		//uccartesian[i * 3 + 0] = my_direct[2 + i * 5 + 0] * ijk[0][0] + my_direct[2 + i * 5 + 1] * ijk[1][0] + my_direct[2 + i * 5 + 2] * ijk[2][0];
		//uccartesian[i * 3 + 1] = my_direct[2 + i * 5 + 0] * ijk[0][1] + my_direct[2 + i * 5 + 1] * ijk[1][1] + my_direct[2 + i * 5 + 2] * ijk[2][1];
		//uccartesian[i * 3 + 2] = my_direct[2 + i * 5 + 0] * ijk[0][2] + my_direct[2 + i * 5 + 1] * ijk[1][2] + my_direct[2 + i * 5 + 2] * ijk[2][2];


		goto peintit;
	}


peintit:

	DestroyWindow(CommandTextField);



	CommandTextField = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL,
		0, 735, 300, 40,
		hWndCommandLine, NULL, NULL, NULL);

	oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

	SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

peintit1:


	if (okrender)
	{
#if !defined(JGN_NO_CMD_HISTORY) 
		SendMessage(CommandTextHistory, EM_SETREADONLY, FALSE, NULL);
#endif

		okrender = 0;

#if !defined(JGN_NO_CMD_HISTORY) 
		SendMessage(CommandTextHistory, EM_SETSEL, 0, -1);
		SendMessage(CommandTextHistory, EM_SETSEL, -1, 0);
#endif

		for (i = 0; i < 50; i++)
		{

			if (i == 0 && ttt[0] == 13)
			{

			}
			else
			{
				if (ttt[i] == 0)
				{
					i = 100;
				}
#if !defined(JGN_NO_CMD_HISTORY) 
				else
				{
					SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ttt[i], 0);


				}
#endif
			}
		}

#if !defined(JGN_NO_CMD_HISTORY) 
		if (d == 1)
		{
			SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ucender[0], 0);
		}
#endif

		SetFocus(CommandTextField);
#if !defined(JGN_NO_CMD_HISTORY) 
		SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);
#endif

		for (i = 0; i < 50; i++)
		{
			CommandBuffer[i] = 0;

		}

		JGN_PostRedisplay();

	}
	else
	{
		SetFocus(CommandTextField);
	}

}




void jgn_initcmd()
{
	HINSTANCE hinst111 = (HINSTANCE)GetWindowLong(hWndCommandLine, GWLP_HINSTANCE);

	char *enderrr = "\n";
	mbstowcs(ucender, enderrr, 2);


	GetWindowRect(mnhwnd, glb_rct);
#if !defined(JGN_NO_CMD_HISTORY) 
	CommandTextHistory = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_POPUP | WS_VSCROLL | ES_MULTILINE,
		(*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242,
		mnhwnd, NULL, hinst111, NULL);
#endif

	fOnt = CreateFont(30, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Arial");

#if !defined(JGN_NO_CMD_HISTORY) 
	SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);
	SendMessage(CommandTextHistory, WM_SETFONT, (WPARAM)fOnt, TRUE);
#endif


	CommandTextField = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_POPUP | ES_MULTILINE | ES_AUTOHSCROLL,
		(*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35,
		mnhwnd, NULL, hinst111, NULL);


	oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

	SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

	//create tool bar
	//HWND ToolBar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_DLGFRAME | TBSTYLE_TOOLTIPS, 0, 0, 0, 0, mnhwnd, NULL, GetModuleHandle(NULL), NULL);
	//SendMessage(ToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);



	JGN_PostRedisplay();
}


float f(float x, float R)
{

	return (max_xyz[0] - min_xyz[0]) - (R / (x * 2))*(x*sqrt(1 + x * x) + log(x + sqrt(1 + x * x)));
}

float df(float x, float R)
{
	return (R / (2 * x*x))*(-x * sqrt(1 + x * x) + asinh(x));
}
float find_theta(float R)
{
	//float x0 = 1;
	//float x1 = 100;
	//Bisection
	//for (int i = 0; i < 100; i++)
	//{
	//
	//	//std::cout << f(x0, R)*f(x1, R) << std::endl;
	//	float xnew = (x0 + x1) / 2.0;
	//	if (f(x0,R)*f(xnew,R) <= 0)
	//	{
	//		x1 = xnew;
	//	}
	//	else
	//	{
	//		x0 = xnew;
	//	}
	//}
	//float xnew = (x0 + x1) / 2;

	//Newton Raphson

	float xnew = 200 + f(200, R) / (R*0.5);


	return xnew;
}
void MakeScroll()
{
	//S1v=tube_rin
	//S2v=tube_rout
	//S3v=tube_param

	int S2vforreal = S2v - S1v;
	//std::cout << S1v << ' ' << S2v << ' ' << S3v << std::endl;
	//std::cout << (max_xyz[0] - min_xyz[0]) << ' ' << S3v << std::endl;
	//int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);

	//Bisection to find max_theta
	float max_theta = find_theta(float(S2v));
	float min_theta = find_theta(float(S1v));



	S3v = ((max_xyz[0] - min_xyz[0]) * 2 * M_PI) / max_theta;
	S3v = S3v + ((max_xyz[0] - min_xyz[0]) * 2 * M_PI) / min_theta;


	sized[0] = vs.group[0].primitiveVec[0].abs() / vs.original->group[0].primitiveVec[0].abs();
	sized[1] = vs.group[0].primitiveVec[1].abs() / vs.original->group[0].primitiveVec[1].abs();
	sized[2] = vs.group[0].primitiveVec[2].abs() / vs.original->group[0].primitiveVec[2].abs();
	//std::cout << sized[0] << " " << sized[1] << " " << sized[2] << std::endl;
	//S3v = max_theta / (max_xyz[0]);
	int as = 0;//atom position starts at
	for (int g = 0; g < vs.N_groups; g++)
	{//for every group
		for (int k = 0; k < sized[2]; k++)
		{
			for (int j = 0; j < sized[1]; j++)
			{
				for (int i = 0; i < sized[0]; i++)
				{
					for (int a = 0; a < vs.original->group[g].N_atoms; a++)
					{//for every atom within the group
						vs.group[g].position[a + as] = vs.original->group[g].position[a] + vs.original->group[vs._isimulationBox].primitiveVec[0] * i + vs.original->group[vs._isimulationBox].primitiveVec[1] * j + vs.original->group[vs._isimulationBox].primitiveVec[2] * k;
						
						float R = S1v + S2vforreal * (vs.group[g].position[a + as].x- min_xyz[0]) / (max_xyz[0] - min_xyz[0]);
						float theta = vs.group[g].position[a + as].x * (2 * M_PI / S3v);
						vs.group[g].position[a + as].z = R * sin(theta);

						vs.group[g].position[a + as].x = R * cos(theta);

					}
					as += vs.original->group[g].N_atoms;
				}
			}
		}
	}
	//for (ole3 = 0; ole3 < ajklsdfl; ole3++)
	//{
	//	crystal[2 + 5 * ole3] = crystal_backup[2 + 5 * ole3];
	//	crystal[4 + 5 * ole3] = crystal_backup[4 + 5 * ole3];

	//	double R = S1v + S2vforreal * (crystal[2 + 5 * ole3] - min_xyz[0]) / (max_xyz[0] - min_xyz[0]);

	//	//Archimedes' Spiral
	//	//http://mathworld.wolfram.com/ArchimedesSpiral.html

	//	float theta = crystal[2 + 5 * ole3] * (2 * M_PI / S3v);


	//	crystal[4 + 5 * ole3] = R * sin(theta);

	//	crystal[2 + 5 * ole3] = R * cos(theta);
	//}


}