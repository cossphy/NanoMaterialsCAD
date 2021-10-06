//BUGS and TODOS////////////////
//complite vs. copy constructor
//add inverse cut to options (ctrl+v)
//add floats to "plane function
//perspective selection and hover atoms are wrong
//call bonds.findbonds() when translating, rotatign etc
#include <omp.h>
#define JGN_SOURCE_CPP
#include "stdafx.h"

#include "JGN_Build.h"
#include "JGN_Windows.h"
#include "JGN_SolidSphere.h"
#include "JGN_bmpLoader.h"
#include "JGN_StrokeCharacter.h"
#include "Bonds.h"
#include "VSystem.h"
#include "ToolBar.h"
#include "Menu.h"
#include "virtualwindow.h"
#include "Mouse.h"
#include "Cammera.h"

#include "DefectedNPs.h"

#define glutSolidSphere JGN_SolidSphere

int main(int argc, char *argv[])
{
	
	//decahedron(5, 5, 0, 1); //corect
	//getchar();

#if NDEBUG
	FreeConsole();
#endif
	variableinit();
	char s[200];


	sized[0] = 1;
	sized[1] = 1;
	sized[2] = 1;
	sized_old[0] = 1;
	sized_old[1] = 1;
	sized_old[2] = 1;


	JGN_Init();
	JGN_InitWindowPosition(GetSystemMetrics(SM_CXSCREEN)/2 - 500, GetSystemMetrics(SM_CYSCREEN) / 2 - 400);
	JGN_InitWindowSize(1000, 800);
	JGN_CreateWindow(NanoMaterialsCAD);



	JGN_ReshapeFunc(myReshape);//gia to window reshape
	JGN_DisplayFunc(display1);
	JGN_KeyboardFunc(keyboardgl);
	

	JGN_PassiveMotionFunc(mouse_pasive);
	JGN_MouseFunc(mouse_func);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_NORMALIZE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	myinit();

	jgn_initcmd();
	JGN_PostRedisplay();

	CustomSurfacesOn = 1;
	
	LoadBMP("button.bmp", &buttonID);
	LoadBMP("showmore.bmp", &showmoreID);
	LoadBMP("showless.bmp", &showlessID);
	LoadBMP("cm_rotate.bmp", &cursorToolsImg[0]);
	LoadBMP("cm_select.bmp", &cursorToolsImg[1]);
	LoadBMP("cm_translate.bmp", &cursorToolsImg[2]);
	LoadBMP("cm_distance.bmp", &cursorToolsImg[3]);
	LoadBMP("button1.bmp", &button1ID);
	LoadBMP("JGN_Font.bmp", &Font);

	tb.initPositions();


	openfont("JGN_Font.fnt");

	global_hdc = GetDC(jgn_dawfunc_hwnd_map[JGN_Global_Draw[0]]);
	projectionMatrix.perspectiveMatrix.updateMatrix();

	JGN_MainLoop();
	//  Free memory.
	//delete[] xyz;
	closefont();


	return 0;
}



void myReshape(int w, int h)// window reshape
{
	width = w;
	height = h;
	projectionMatrix.perspectiveMatrix.updateMatrix();


	//glLoadIdentity();//load the origin matrix the original place view point etc...
					 // gia na mhn allwienetai h eikona kanw to if
					 //multiply the current matrix with an orthographic matrix
					 //glOrtho(Specify the coordinates for the left and right vertical clipping planes
					 //Specify the coordinates for the bottom and top horizontal clipping planes.
					 //Specify the distances to the nearest and farthest depth clipping planes)
	//cout << w << "X" << h << endl;
	//if (cam.perspective_on)
	//{
		cam.loadorthomatrix();
		//cam.loadperspectivematrix();
	//}
	//else
	//{
	//	cam.loadorthmatrix();
	//}


	//JGN_PostRedisplay();

	return;
}

void drawCubicPlanesCase1_1(int i, int j, int k)
{
	//{110}

//011
	glColor4f(0, 1, 0, 0.5);
	glVertex3f(i*third, j*second, k*second);
	glVertex3f(i*fifth, j*first, k*first);
	glVertex3f(i*second, j*third, k*second);

	glVertex3f(i*third, j*second, k*second);
	glVertex3f(i*second, j*third, k*second);
	glVertex3f(i*second, j*third, 0);

	glVertex3f(i*third, j*second, k*second);
	glVertex3f(i*third, j*second, 0);
	glVertex3f(i*second, j*third, 0);

	glVertex3f(i*fifth, j*first, k*first);
	glVertex3f(i*first, j*fifth, k*first);
	glVertex3f(i*second, j*third, k*second);

	//101
	glVertex3f(i*second, j*third, k*second);
	glVertex3f(i*first, j*fifth, k*first);
	glVertex3f(i*second, j*second, k*third);

	glVertex3f(i*first, j*first, k*fifth);
	glVertex3f(i*first, j*fifth, k*first);
	glVertex3f(i*second, j*second, k*third);

	glVertex3f(0, j*third, k*second);
	glVertex3f(i*second, j*third, k*second);
	glVertex3f(i*second, j*second, k*third);

	glVertex3f(0, j*third, k*second);
	glVertex3f(i*second, j*second, k*third);
	glVertex3f(0, j*second, k*third);


	//110
	glVertex3f(i*second, j*second, k*third);
	glVertex3f(i*first, j*first, k*fifth);
	glVertex3f(i*third, j*second, k*second);

	glVertex3f(i*fifth, j*first, k*first);
	glVertex3f(i*first, j*first, k*fifth);
	glVertex3f(i*third, j*second, k*second);


	glVertex3f(i*second, j*second, k*third);
	glVertex3f(i*third, j*second, k*second);
	glVertex3f(i*third, 0, k*second);

	glVertex3f(i*second, j*second, k*third);
	glVertex3f(i*third, 0, k*second);
	glVertex3f(i*second, 0, k*third);

	//{100}
	glColor4f(1, 0, 0, 0.5);

	//100
	glVertex3f(0, j*second, k*third);
	glVertex3f(i*second, 0, k*third);
	glVertex3f(i*second, j*second, k*third);

	glVertex3f(0, j*second, k*third);
	glVertex3f(i*second, 0, k*third);
	glVertex3f(0, 0, k*third);

	//001
	glVertex3f(i*second, j*third, k*second);
	glVertex3f(0, j*third, k*second);
	glVertex3f(i*second, j*third, 0);

	glVertex3f(0, j*third, k*second);
	glVertex3f(i*second, j*third, 0);
	glVertex3f(0, j*third, 0);

	//010

	glVertex3f(i*third, j*second, k*second);
	glVertex3f(i*third, 0, k*second);
	glVertex3f(i*third, j*second, 0);

	glVertex3f(i*third, 0, k*second);
	glVertex3f(i*third, j*second, 0);
	glVertex3f(i*third, 0, 0);


	//010

	//{111}
	glColor4f(0, 0, 1, 0.5);

	glVertex3f(i*first, j*first, k*fifth);
	glVertex3f(i*fifth, j*first, k*first);
	glVertex3f(i*first, j*fifth, k*first);
}

char *s1itoa = (char*)malloc(sizeof(char) * 5);
int Scounter = 0;
int stroke_c = 0;


void display1(void)//generates the graphics output.
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




	for (int ii = 0; ii < a; ii++)
	{
		aatoms[ii] = 0;
	}



	if (cam.perspective_on)
	{
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
			dipapan = 1.05*(GLfloat)height / (GLfloat)width;


		}
		else
		{
			glOrtho(
				-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
				-1.05, +1.05,
				-10.0, 10.0);
			dipleft = -1.05*(GLfloat)width / (GLfloat)height;
			dipapan = 1.05;

		}
		glMatrixMode(GL_MODELVIEW);
	}
	glPointSize(pointsize);

	stroke_c = 0;
	if (cam.perspective_on)
	{
		cam.loadperspectivematrix();
	}
	glLoadIdentity();

	/////////////////
	float p[3];
	float p1[3];
	//int point;

	//  indicates default buffers



	//glRotatef(theta[0], cos((pi*theta[1]) / 180), 0.0, sin((pi*theta[1]) / 180));
	menu.draw();

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 0.0, 1.0);

	glTranslatef(model_translate[0], model_translate[1], model_translate[2]);


		ball_atoms = 0;

		for (int i = 0; i < 3; i++)
			if (prev_sized[i] != sized[i])
			{
				if (render_is_on)
				{
					(prev_sized[i] < sized[i]) ? prev_sized[i] += 1 : prev_sized[i] = sized[i];
					JGN_QRedisplay();
				}
				else
				{
					prev_sized[i] = sized[i];
				}
			}

		//////////////////////TODO: this is ungly
		glColor3f(0, 0, 0);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
	drawMoldsLines(p, p1);
	/////////////////////////////////////
	glEnable(GL_LIGHTING);

	vs.cut();//TODO: move that from here

	vs.draw();
	cam.loadorthomatrix();
	wn.draw();

	cam.loadorthomatrix();
	tb.draw();

	glColor3f(0.0, 0.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, Font);
//// aatoms print
	if (cam.perspective_on)
	{
		glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
		glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me
		glLoadIdentity();
		if (width <= height)
		{
			glOrtho(
				-1.05, +1.05,
				-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
				-10.0, 10.0);
			dipleft = -1;
			dipapan = (GLfloat)height / (GLfloat)width;


		}
		else
		{
			glOrtho(
				-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
				-1.05, +1.05,
				-10.0, 10.0);
			dipleft = -(GLfloat)width / (GLfloat)height;
			dipapan = 1;


		}
		glMatrixMode(GL_MODELVIEW);
	}
//




	if (shperes_on)
		glDisable(GL_LIGHTING);

	if (tb.sellectedTool==ToolBar::Tool::SELECT)
	{//select
		glLoadIdentity();
		glColor3f(0, 0, 0);


		glLineWidth(1);
		glBegin(GL_LINE_STRIP);
		glVertex2f(leftClick.start[0], leftClick.start[1]);
		glVertex2f(leftClick.start[0], leftClick.finish[1]);
		glVertex2f(leftClick.finish[0], leftClick.finish[1]);
		glVertex2f(leftClick.finish[0], leftClick.start[1]);
		glVertex2f(leftClick.start[0], leftClick.start[1]);
		glEnd();
		glLineWidth(4);


		//glTranslatef(-0.2, 0.95, 0);
		//write::string("Select");


	}
	//else if (tb.sellectedTool == ToolBar::Tool::TRANSLATE)
	//{//translate
	//	glLoadIdentity();
	//	glColor3f(0, 0, 0);

	//	glTranslatef(-0.3, 0.95, 0);
	//	write::string("Translate");
	//}
	//else if (tb.sellectedTool == ToolBar::Tool::DISTANCE)
	//{//distance
	//	glLoadIdentity();
	//	glColor3f(0, 0, 0);

	//	glTranslatef(-0.3, 0.95, 0);
	//	write::string("Distance");
	//}
	//else if (mouse_mode == 'o')
	//{//selected rotate

	//	glLoadIdentity();
	//	glColor3f(0, 0, 0);


	//	glTranslatef(-0.2, 0.95, 0);
	//	write::string("x    y    z");
	//	glLoadIdentity();
	//	glTranslatef(-0.25, 0.85, 0);
	//	if (selected_rotate_axes == 1)
	//	{
	//		glColor4f(0, 0, 0, 1);
	//	}
	//	else
	//	{
	//		glColor4f(0, 0, 0, 0.5);
	//	}
	//	write::string(jgn::ftoa(selected_rotate[0]), 3);
	//	write::character(' ');
	//	if (selected_rotate_axes == 2)
	//	{
	//		glColor4f(0, 0, 0, 1);
	//	}
	//	else
	//	{
	//		glColor4f(0, 0, 0, 0.5);
	//	}
	//	write::string(jgn::ftoa(selected_rotate[1]), 3);
	//	write::character(' ');
	//	if (selected_rotate_axes == 3)
	//	{
	//		glColor4f(0, 0, 0, 1);
	//	}
	//	else
	//	{
	//		glColor4f(0, 0, 0, 0.5);
	//	}
	//	write::string(jgn::ftoa(selected_rotate[2]), 3);



	//}
	//else if (mouse_mode == 'a')
	//{//selected translate
	//	glLoadIdentity();
	//	glColor3f(0, 0, 0);


	//	glTranslatef(-0.2, 0.95, 0);
	//	if (selected_translate_direction == 0)
	//	{
	//		glColor4f(0, 0, 0, 1);
	//	}
	//	else
	//	{
	//		glColor4f(0, 0, 0, 0.5);
	//	}
	//	write::string("x ");
	//	if (selected_translate_direction == 1)
	//	{
	//		glColor4f(0, 0, 0, 1);
	//	}
	//	else
	//	{
	//		glColor4f(0, 0, 0, 0.5);
	//	}
	//	write::string("y ");
	//	if (selected_translate_direction == 2)
	//	{
	//		glColor4f(0, 0, 0, 1);
	//	}
	//	else
	//	{
	//		glColor4f(0, 0, 0, 0.5);
	//	}
	//	write::string("z ");



	//}

	//print custom surfaces

	////test
	//glLoadIdentity();
	//glLineWidth(1);
	//for (i = 0; i < CustomSurfacesCount; i++)
	//{
	//	glBegin(GL_LINES);
	//	glVertex2d(dipleft, dipapan-0.01 - i*(0.075) );
	//	glVertex2d(dipleft+0.2, dipapan-0.01 - i*(0.075));
	//	glEnd();
	//}
	

	if (nanotube)
	{


		glLoadIdentity();

		glTranslatef(dipleft + tb.size + 0.05, 0.8, 0);
		write::character('R');
		write::character('1');
		write::character(' ');




		itoa(S1v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{
			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);


		glLoadIdentity();

		glTranslatef(dipleft + tb.size + 0.05, 0.6, 0);


		write::character('R');
		write::character('2');
		write::character(' ');


		itoa(S2v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);

	}

	else if (CustomSurfacesOn)
	{

	}
	else if (Rod_like == -1)
	{
		//
		glLoadIdentity();
		if (S1v >= S2v || S1v >= S3v)
		{
			glColor3f(.8, .8, .8);
		}
		else
		{
			glColor3f(0, 0, 0);

		}
		glTranslatef(dipleft + tb.size + 0.05, 0.8, 0);

		write::character('{');
		write::character('1');
		write::character('0');
		write::character('0');
		write::character('}');
		write::character(' ');

		itoa(S1v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);



		glLoadIdentity();

		if (S2v >= 2 * S1v || S3v <= S2v)
		{
			glColor3f(.8, .8, .8);
		}
		else
		{
			glColor3f(0, 0, 0);
		}


		glTranslatef(dipleft + tb.size + 0.05, 0.6, 0);

		write::character('{');
		write::character('1');
		write::character('1');
		write::character('0');
		write::character('}');
		write::character(' ');

		itoa(S2v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);

		glLoadIdentity();


		glTranslatef(dipleft + tb.size + 0.05, 0.4, 0);

		glColor3f(0, 0, 0);
		write::character('{');
		write::character('1');
		write::character('1');
		write::character('1');
		write::character('}');
		write::character(' ');

		itoa(S3v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);

	}
	else if (Right_Hexagonal == -1)
	{
		glLoadIdentity();
		glTranslatef(dipleft + tb.size + 0.05, 0.8, 0);
		if (float(S1v) / float(S2v) > 1.14814814815)

		{
			glColor3f(.8, .8, .8);
		}
		else
		{
			glColor3f(0, 0, 0);

		}

		write::character('{');
		write::character('1');
		write::character('0');
		write::character(one_bar);
		write::character('0');
		write::character('}');
		write::character(' ');

		itoa(S1v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);



		glLoadIdentity();

		glTranslatef(dipleft + tb.size + 0.05, 0.6, 0);


		if (float(S1v) / float(S2v) < 0.86842105263)
		{
			glColor3f(.8, .8, .8);

		}
		else
		{

			glColor3f(0, 0, 0);
		}


		write::character('{');
		write::character('1');
		write::character('1');
		write::character(two_bar);
		write::character('0');
		write::character('}');
		write::character(' ');

		itoa(S2v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);


		glLoadIdentity();


		glTranslatef(dipleft + tb.size + 0.05, 0.4, 0);


		glColor3f(0, 0, 0);

		write::character('{');
		write::character('0');
		write::character('0');
		write::character('0');
		write::character('1');
		write::character('}');
		write::character(' ');

		itoa(Right_Hexagonal_height, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);
	}
	else if (want_cyrcle[0] == 'y')
	{
		glLoadIdentity();
		glTranslatef(dipleft + tb.size + 0.05, 0.8, 0);

		glColor3f(0, 0, 0);

		write::character('R');
		write::character(' ');


		itoa((int)rad, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			write::character(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		write::character(Angstrom);

	}
	else
	{
		if (S1[0] != '0')
		{
			glLoadIdentity();
			glTranslatef(dipleft +  tb.size + 0.05, 0.8, 0);


			if (Scase == 1 || Scase == 2 || Scase == 3 || Scase == 4)
			{

				glColor3f(0, 0, 0);
			}
			else
			{
				glColor3f(0.8, 0.8, 0.8);

			}

			write::character('{');
			write::character('1');
			write::character('0');
			write::character('0');
			write::character('}');
			write::character(' ');

			itoa(S1v, s1itoa, 10);

			for (Scounter = 0; Scounter < 5; Scounter++)
			{

				write::character(s1itoa[Scounter]);
				if (s1itoa[Scounter] == '\0')
				{
					break;
				}
			}
			write::character(Angstrom);
		}

		if (S2[0] != '0')
		{

			glLoadIdentity();

			glTranslatef(dipleft + tb.size + 0.05, 0.6, 0);


			if (Scase == 1 || Scase == 2 || Scase == 5 || Scase == 6)
			{
				glColor3f(0, 0, 0);

			}
			else
			{
				glColor3f(0.8, 0.8, 0.8);

			}

			write::character('{');
			write::character('1');
			write::character('1');
			write::character('0');
			write::character('}');
			write::character(' ');

			itoa(S2v, s1itoa, 10);

			for (Scounter = 0; Scounter < 5; Scounter++)
			{

				write::character(s1itoa[Scounter]);
				if (s1itoa[Scounter] == '\0')
				{
					break;
				}
			}
			write::character(Angstrom);
		}
		if (S3[0] != '0')
		{
			glLoadIdentity();


			glTranslatef(dipleft + tb.size + 0.05, 0.4, 0);


			if (Scase == 1 || Scase == 3 || Scase == 5 || Scase == 7)
			{
				glColor3f(0, 0, 0);

			}
			else
			{
				glColor3f(0.8, 0.8, 0.8);

			}

			write::character('{');
			write::character('1');
			write::character('1');
			write::character('1');
			write::character('}');
			write::character(' ');

			itoa(S3v, s1itoa, 10);

			for (Scounter = 0; Scounter < 5; Scounter++)
			{

				write::character(s1itoa[Scounter]);
				if (s1itoa[Scounter] == '\0')
				{
					break;
				}
			}
			write::character(Angstrom);
		}
	}
	if (shperes_on)
		glEnable(GL_LIGHTING);

	//bonds.CalcBonds(3);
	//cout << 3 << endl;

	//return;

}


void spin_image()

{

}

float theta_start[2];
float theta_prev[2] = { 0,0 };
float translate_prev[3] = { 0,0,0 };
float translate_start[3];








void myinit(void)//initialize OpenGL

{
	glLineWidth(4.0);

	//  Set the background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//  The default size is 1.0.

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_deffuse[] = {1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 120.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnable(GL_DEPTH_TEST);

	truepointsize = 1000.0;
	pointsize = truepointsize / (Svmax + 5);
	glPointSize(pointsize);


	return;

}

void variableinit()
{

	/////////////////global variables

	for (i = 1; i < 32; i++)
	{
		float coef = (3.141 / 2.0) - i * M_PI / 32;
		sinTable32[i-1] = sin(coef);
		cosTable32[i-1] = cos(coef);

	}
	for (i = 0; i < 32; i++)
	{
		sincurTheta32[i] = sin(i * (2 * M_PI) / 32);
		coscurTheta32[i] = cos(i * (2 * M_PI) / 32);
	}

	for (i = 0; i < 81000000; i++)
	{
		ttest[i] = 0;
	}

	DrawDistanceLine = false;
	Ndeletes = 0;
	ClickedForDistance[0] = -1;
	ClickedForDistance[1] = -1;
	Dist2Disp = 0;
	iClickedForDistance = 2;
	selected_rotate_axes = 1;
	model_translate[0] = 0;
	model_translate[1] = 0.0;
	model_translate[2] = 0;
	leftClick.start[0] = 0;
	leftClick.start[1] = 0;
	leftClick.finish[0] = 0;
	leftClick.finish[1] = 0;
	mouse_mode = 'r';
	crystal = NULL;
	crystal_backup = NULL;
	selective_dynamics = NULL;


	Truncated_Cube_max[0] = 0.0;
	Truncated_Cube_max[1] = 0.0;
	Truncated_Cube_max[2] = 0.0;

	min_xyz[0] = FLT_MAX;
	min_xyz[1] = FLT_MAX;
	min_xyz[2] = FLT_MAX;

	max_xyz[0] = FLT_MIN;
	max_xyz[1] = FLT_MIN;
	max_xyz[2] = FLT_MIN;

	NewPC = (char*)malloc(sizeof(char)*(200));
	PCtype = (char*)malloc(sizeof(char) * 100);

	lmb = 0;
	wasfullscreenflagin = 0;
	wasfullscreenflagout = -1;


	dipleft = -1000.0 / 800.0;
	dipapan = 1;
	cam.perspective_on = false;
	theta[0] = 0.0;
	theta[1] = 0.0;
	theta[2] = 0.0;
	flagmax = 0;
	first = 0;
	second = 0;
	third = 0;
	forth = 0;
	fifth = 0;
	sixth = 0;
	seventh = 0;
	eighth = 0;
	nineth = 0;
	tenth = 0;
	eleventh = 0;

	mouse_check = 0;

	sphStacks = 32;
	sphSides = 32;
	qredisplay = false;

	prev_sized[0] = 1.0;
	prev_sized[1] = 1.0;
	prev_sized[2] = 1.0;

	rad = 20;

	want_cyrcle[0] = 'n';
	want_cyrcle[1] = 'o';
	want_cyrcle[2] = 'l';
	want_cyrcle[3] = 'l';
	want_cyrcle[4] = 'l';


	nanotube = 0;
	full = 0;
	zmax100111[0] = 0.0;
	zmax100111[1] = 0.0;
	zmax100111[2] = 0.0;
	zmax100111_[0] = 0.0;
	zmax100111_[1] = 0.0;
	zmax100111_[2] = 0.0;
	Scase = 1000;
	figure_1 = 1.0;
	Right_Hexagonal = 1.0;
	Right_Hexagonal_height = 20.0;


	vacuum = false;


	Rod_like = 1.0;
	width = 1000;
	height = 800;
	jgn_supercell = 0;
	jgn_supercell_xyz[0] = 10;
	jgn_supercell_xyz[1] = 10;
	jgn_supercell_xyz[2] = 10;
	my_direct = NULL;
	uccartesian = NULL;

	xexe[0] = 0;
	xexe[1] = 0;
	xexe[2] = 0;

	was_supercell = 0;

	hWndCommandLine = NULL;
	hWndList = NULL;

	S1 = (char*)malloc(sizeof(char) * 4);
	S2 = (char*)malloc(sizeof(char) * 4);
	S3 = (char*)malloc(sizeof(char) * 4);
	s1 = (char*)malloc(sizeof(char) * 50);
	render_is_on = true;
	S1v = 25;
	S2v = 30;
	S3v = 40;
	S1i[0] = 0;
	S1i[1] = 0;
	S1i[2] = 0;
	S2i[0] = 0;
	S2i[1] = 0;
	S2i[2] = 0;
	S3i[0] = 0;
	S3i[1] = 0;
	S3i[2] = 0;

	Svmax = 0;

	jgn_file_dropd = 0;
	lpszFile = (LPTSTR)malloc(sizeof(char) * 500);
	inpf[0] = 0;

#if !defined(JGN_NO_CMD_HISTORY) 
	CommandTextHistory = NULL;
#endif
	my_postmessages_count = 0;
	CustomSurfacesCount = 0;
	CustomSurfaces = NULL;
	CustomSurfaceSelected = -1;
	CustomSurfacesOn = 0;

	loop = 0;
	sizedprotector[0] = 0;
	anotherokrender = 0;
	wait = 0;
	custom_sized[0] = 1;
	custom_sized[1] = 1;
	custom_sized[2] = 1;
	itemsel = -1;
	predicted = 0;
	listboxcurent = 0;

	mainwndsize[0] = 1016;
	mainwndsize[1] = 858;


	cmdwndh = 300;


	CommandTextField = NULL;
	glb_rct = (LPRECT)malloc(sizeof(RECT));


	ball_atoms = 0;
	ballflag = 0;
	theta_pr[0] = 0;
	theta_pr[1] = 0;
	atomic_number = NULL;
	new_num_atoms = NULL;
	i = 1;
	j = 1;
	k = 1;
	shelp = 0;
	atomshelp = NULL;
	token3 = 0;

	shperes_on = 1;// render as spheres or points

	inptype = '\0';


	crystalh = 0;
	crystalk = 0;
	crystall = 0;
	atomscc = 0;

	atoms_to_print = NULL;

	t = 0;


	atoms_to_print_c = 0;
	atoms = NULL;
	a = 0;//a: posa eidi atomwn
	an_and_aw = NULL;


	shift_down = false;
	glob_translate[0] = 0;
	glob_translate[1] = 0;
	glob_translate[2] = 0;
	glob_translate_prev[0] = 0;
	glob_translate_prev[1] = 0;
	glob_translate_prev[2] = 0;
	db = 0;

	ea = NULL;

	line = 2;
	p = 0;


	alloena = 0;
	ka8isterimenoflag = 0;

	sph_pnt_flag = 0;

	jgn_wndcnt = 0;								
	jgn_glbrect = { 0,0,0,0 };					
	jgn_runing = 0;								
	jgn_init_wind_size[0][0] = 0;

	jgn_curent_window_to_edit = NULL;	
	jgn_Child_C = 0;	

	jgn_help_to_map_the_draw_func = NULL;		// saves the hwnd of the most recent parent window created... helps to map the draw functions to the hwnd
	jgn_trayhwnd = NULL;						// tray hwnd
	hInst = GetModuleHandle(NULL);								// current instance

	hook1 = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);

	jgn_start_time_frame = GetTickCount();				 ////for the frame limit


	jgn_start_time = 0;					//// gose to GetTickCount() every time a frame is drawn
	cbc = 0;							////to print frames/sec to the cmd

	endcheck = 0;
	okrender = 0;

	points[0] = { 0,1,0 };
	for (int i = 0; i < 100; i++)
		triangles_indices[i] = i;

	vs.simulationBoxEdges[0].abs();
	vs.original = &__backup;
	vs.original->original = vs.original;
	jgn::vec3 irot = jgn::vec3(0, 0, 0);
	irot.rotate(irot);
	tb._sellectedfordistance[0] = jgn::vec2(-1, -1);
	tb._sellectedfordistance[1] = jgn::vec2(-1, -1);
	menu.init();
}

void translateTheSelected(char op)
{
	int asdf = t * sized[0] * sized[1] * sized[2];
	for (int i = 0; i < asdf; i++)
	{
		if (isSelected[i])
		{
			float inp[3];
			float trn[3];
			float out[3];

			inp[0] = crystal[2 + 5 * i] / (Svmax + 5);
			inp[1] = crystal[3 + 5 * i] / (Svmax + 5);
			inp[2] = crystal[4 + 5 * i] / (Svmax + 5);

			trn[0] = 0;
			trn[1] = 0;
			trn[2] = 0;

			if (op == '+')
			{
				trn[selected_translate_direction] = 0.5 / (Svmax + 5);
			}
			else
			{
				trn[selected_translate_direction] = -0.5 / (Svmax + 5);
			}
			jgn::cpu_translate(inp, trn, out);

			crystal[2 + 5 * i] = out[0] * (Svmax + 5);
			crystal[3 + 5 * i] = out[1] * (Svmax + 5);
			crystal[4 + 5 * i] = out[2] * (Svmax + 5);
		}
	}
}

void rotateTheSelected(char op)
{
	float mean_coords[3];
	for (int i = 0; i < 3; i++)
	{
		mean_coords[i] = 0;
	}	
	int asdf = t * sized[0] * sized[1] * sized[2];
	int counter = 0;
	for (int i = 0; i < asdf; i++)
	{
		if (isSelected[i])
		{
			counter++;
			mean_coords[0] += crystal[2 + 5 * i] / (Svmax + 5);
			mean_coords[1] += crystal[3 + 5 * i] / (Svmax + 5);
			mean_coords[2] += crystal[4 + 5 * i] / (Svmax + 5);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		mean_coords[i] /= counter;
	}
	for (int i = 0; i < asdf; i++)
	{
		if (isSelected[i])
		{
			float inp[3];
			float rot[3];
			float out[3];

			inp[0] = crystal[2 + 5 * i] / (Svmax + 5);
			inp[1] = crystal[3 + 5 * i] / (Svmax + 5);
			inp[2] = crystal[4 + 5 * i] / (Svmax + 5);

			rot[0] = 0;
			rot[1] = 0;
			rot[2] = 0;
			if (op == '+')
			{
				rot[selected_rotate_axes - 1] = 0.5 * M_PI / 180;
			}
			else
			{
				rot[selected_rotate_axes - 1] = -0.5 * M_PI / 180;
			}
			for (int i = 0; i < 3; i++)
			{
				mean_coords[i] = -mean_coords[i];
			}
			jgn::cpu_translate(inp, mean_coords, out);
			jgn::cpu_rotate(out, rot, inp);
			for (int i = 0; i < 3; i++)
			{
				mean_coords[i] = -mean_coords[i];
			}
			jgn::cpu_translate(inp, mean_coords, out);


			crystal[2 + 5 * i] = out[0] * (Svmax + 5);
			crystal[3 + 5 * i] = out[1] * (Svmax + 5);
			crystal[4 + 5 * i] = out[2] * (Svmax + 5);
		}
	}
}

void deleteSelected()
{
	Ndeletes++;
	bool atleast1 = false;
	for (int g = 0; g < vs.N_groups; g++)
	{
		for (int i = 0; i < vs.group[g].N_atoms; i++)
		{
			if (vs.group[g].isSelected[i])
			{
				atleast1 = true;
				vs.group[g].isdeleted[i] = true;
				//deletedHistory[i] = Ndeletes;
			}
		}
	}

	if (!atleast1)
		Ndeletes--;
}

void UndoDeleted()
{
	if (Ndeletes > 0)
	{
		for (int g = 0; g < vs.N_groups; g++)
		{
			for (int i = 0; i < vs.group[g].N_atoms; i++)
			{
				if (deletedHistory[i] == Ndeletes)
				{
					deletedHistory[i] = 0;
					vs.group[g].isdeleted[i] = false;
				}
			}
			Ndeletes--;
		}
	}
}



int ctrl_down = 0;
int s_down = 0;
int r_down = 0;
int t_down = 0;
bool z_down = false;

void keyboardgl(int key, int s, int x, int y)
{
	if (key == VK_CONTROL)
	{
		if (s == JGN_DOWN)
		{
			ctrl_down = JGN_DOWN;
		}
		else
		{
			ctrl_down = JGN_UP;
		}

	}
	else if (key == VK_SHIFT && s == JGN_DOWN)
	{
		shift_down = true;
	}
	else if (key == VK_SHIFT && s == JGN_UP)
	{
		shift_down = false;
	}
	else if (key == 's' || key == 'S')
	{
		if (s == JGN_DOWN)
		{
			s_down = JGN_DOWN;
		}
		else
		{
			s_down = JGN_UP;
		}

	}
	else if (key == 'r' || key == 'R')
	{
		if (s == JGN_DOWN)
		{
			r_down = JGN_DOWN;
		}
		else
		{
			r_down = JGN_UP;
		}

	}
	else if (key == 't' || key == 'T')
	{
		if (s == JGN_DOWN)
		{
			t_down = JGN_DOWN;
		}
		else
		{
			t_down = JGN_UP;
		}

	}
	else if (key == 'z' || key == 'Z')
	{
		s == JGN_DOWN ? z_down = JGN_DOWN : z_down = JGN_UP;
	}

	if (ctrl_down && s_down)
	{
		ctrl_down = 0;
		s_down = 0;
		DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE_OUT), jgn_help_to_map_the_draw_func, Choose_Format);


		DialogBox(hInst, MAKEINTRESOURCE(IDD_BUILD_POSCAR), jgn_help_to_map_the_draw_func, Poscar_Build);


	}
	else if (CustomSurfaceSelected != -1 && (isdigit(key) || key == VK_BACK || (key >= VK_NUMPAD0 && key <= VK_NUMPAD9)) && s == JGN_DOWN)
	{
		char buf[100];
		itoa(CustomSurfaces[CustomSurfaceSelected][3], buf, 10);
		int len = strlen(buf);
		if (key == VK_BACK)
		{
			buf[len - 1] = '\0';
			CustomSurfaces[CustomSurfaceSelected][3] = atoi(buf);
		}
		else if (key >= VK_NUMPAD0 && key <= VK_NUMPAD9)
		{
			buf[len] = key - 48;
			buf[len + 1] = '\0';
			CustomSurfaces[CustomSurfaceSelected][3] = atoi(buf);
		}
		else if (key == VK_ADD)
		{
			CustomSurfaces[CustomSurfaceSelected][3]++;
		}
		else if (key == VK_SUBTRACT)
		{
			CustomSurfaces[CustomSurfaceSelected][3]--;
			if (CustomSurfaces[CustomSurfaceSelected][3] < 0)
				CustomSurfaces[CustomSurfaceSelected][3] = 0;
		}
		else
		{
			buf[len] = key;
			buf[len + 1] = '\0';
			CustomSurfaces[CustomSurfaceSelected][3] = atoi(buf);
		}
		JGN_PostRedisplay();
	}
	else if (ctrl_down && r_down)
	{
		mouse_mode = 'o';
		selected_rotate[0] = 0;
		selected_rotate[1] = 0;
		selected_rotate[2] = 0;

		JGN_PostRedisplay();
	}
	else if (ctrl_down && t_down)
	{
		//mouse_mode = 'a';
		//selected_rotate[0] = 0;
		//selected_rotate[1] = 0;
		//selected_rotate[2] = 0;
		tb.sellectedTool = ToolBar::Tool::ROTATE;
		vs.toggleselected_translate(true);
		menu.show = false;

		JGN_PostRedisplay();
	}
	else if (ctrl_down && z_down)
	{
		//UndoDeleted();
		vs.updateinfo();
		JGN_PostRedisplay();
	}
	else if (key == VK_DELETE && s == JGN_DOWN)
	{
		deleteSelected();
		vs.updateinfo();
		JGN_PostRedisplay();
	}
	else
	{
		int check_if_to_redisplay = 0;
		if (wn.show)
		{
			if (s == JGN_DOWN)
			{
				if ((key >= 'A' && key <= 'Z'))
				{//capital letters
					if (capson)
					{
						if(!shift_down)
							wn.in_field.push_back(key);
						else
							wn.in_field.push_back(key + 32);
					}
					else
					{
						if (!shift_down)
							wn.in_field.push_back(key + 32);
						else
							wn.in_field.push_back(key);
					}

					check_if_to_redisplay = 1;
				}
				else if (key >= '0' && key <= '9')
				{//0 to 1
					wn.in_field.push_back(key);
					check_if_to_redisplay = 1;
				}
				else if (key >= VK_NUMPAD0 && key <= VK_NUMPAD9)
				{//0 to 1 numpad
					wn.in_field.push_back(key-48);
					check_if_to_redisplay = 1;
				}
				else if (key == 46 || key == 110 || key == 190)
				{//the DOT.... got it? :D
					wn.in_field.push_back('.');
					check_if_to_redisplay = 1;
				}
				else if (key == VK_BACK)
				{
					if (!wn.in_field.empty())
					{
						wn.in_field.erase(wn.in_field.length() - 1, 1);
						check_if_to_redisplay = 1;
					}
				}
				else if (key == VK_RETURN)
				{
					if (!wn.in_message.compare("Give the element"))
					{
						wn.in_message = "";
						vs.selected_change_element(wn.in_field);
						wn.in_field = "";
						vs.updateinfo();
					}
					else if (!wn.in_message.compare("Give the radius"))
					{
						wn.in_message = "";
						vs.selected_change_radius(wn.in_field);
						wn.in_field = "";
						vs.updateinfo();
					}
					else if (!wn.in_message.compare("Selective dynamics"))
					{
						wn.in_message = "";
						vs.selected_change_sd(wn.in_field);
						wn.in_field = "";
						vs.updateinfo();
					}
					check_if_to_redisplay = 1;
				}

			}
		}
		else if ((key == 'q' || key == 'Q') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[0]++;
				sized[0]++;

				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[0] / 2 == jgn_supercell_xyz[0] / 2.0)
				{
					xexe[0] = 0;
				}
				else
				{
					xexe[0] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																												 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																												 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																															//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				rad++;
				S1v = S1v + 1;
				if (nanotube)
				{
					MakeScroll();
				}
			}
			check_if_to_redisplay = 1;

		}
		else if ((key == 'v' || key == 'V') && s == JGN_DOWN)
		{
			vacuum = vacuum ^ true;
			JGN_PostRedisplay();
		}
		else if (key == VK_ADD && s == JGN_DOWN)
		{
			if (mouse_mode == 'o')
			{
				selected_rotate[selected_rotate_axes - 1] += 0.5;
				rotateTheSelected('+');

			}
			else if (mouse_mode == 'a')
			{
				selected_translate[selected_translate_direction] += 0.5;
				translateTheSelected('+');

			}
			else
			{
				truepointsize = truepointsize + 100;
				pointsize = truepointsize / (Svmax + 5);
				glPointSize(pointsize);
			}
			JGN_PostRedisplay();
		}
		else if (key == VK_SUBTRACT && s == JGN_DOWN)
		{
			if (mouse_mode == 'o')
			{
				selected_rotate[selected_rotate_axes - 1] -= 0.5;
				rotateTheSelected('-');
			}
			else if (mouse_mode == 'a')
			{
				selected_translate[selected_translate_direction] -= 0.5;
				translateTheSelected('-');

			}
			else
			{
				truepointsize = truepointsize - 100;
				if (truepointsize < 0)
					truepointsize = 0;
				pointsize = truepointsize / (Svmax + 5);

				glPointSize(pointsize);
			}
			JGN_PostRedisplay();
		}	
		else if (mouse_mode == 'o' && (key == '1' || key == VK_NUMPAD1))
		{
			selected_rotate_axes = 1;
			JGN_PostRedisplay();

		}
		else if (key == '1' || key == VK_NUMPAD1)
		{
			if (mouse_mode == 'a')
			{
				selected_translate_direction = 0;
			}
			else
			{
				theta[0] = -90;
				theta[1] = -90;
			}
			JGN_PostRedisplay();
		}
		else if (mouse_mode == 'o' && (key == '2' || key == VK_NUMPAD2))
		{
			selected_rotate_axes = 2;
			JGN_PostRedisplay();

		}
		else if (key == '2' || key == VK_NUMPAD2)
		{
			if (mouse_mode == 'a')
			{
				selected_translate_direction = 1;
			}
			else
			{
				theta[0] = -90;
				theta[1] = -180;
			}
			JGN_PostRedisplay();
		}
		else if (mouse_mode == 'o' && (key == '3' || key == VK_NUMPAD3))
		{
			selected_rotate_axes = 3;
			JGN_PostRedisplay();

		}
		else if (key == '3' || key == VK_NUMPAD3)
		{
			if (mouse_mode == 'a')
			{
				selected_translate_direction = 2;
			}
			else
			{
				theta[0] = 0;
				theta[1] = 0;
			}
			JGN_PostRedisplay();
		}
		else if ((key == 'w' || key == 'W') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[0]--;
				if (jgn_supercell_xyz[0] < 0)
				{
					jgn_supercell_xyz[0] = 0;
				}
				sized[0]= jgn_supercell_xyz[0];


				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[0] / 2 == jgn_supercell_xyz[0] / 2.0)
				{
					xexe[0] = 0;
				}
				else
				{
					xexe[0] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				rad--;
				S1v = S1v - 1;
				if (S1v < 0)
				{
					S1v = 0;
				}
				if (rad < 0)
				{
					rad = 0;
				}
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		else if ((key == 'a' || key == 'A') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[1]++;
				sized[1]++;


				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[1] / 2 == jgn_supercell_xyz[1] / 2.0)
				{
					xexe[1] = 0;
				}
				else
				{
					xexe[1] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				S2v = S2v + 1;
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		else if((key == 'r' || key == 'R') && s == JGN_DOWN)
		{
			tb.sellectedTool = ToolBar::Tool::ROTATE;
			JGN_PostRedisplay();
		}
		else if ((key == 't' || key == 'T') && s == JGN_DOWN)
		{
			tb.sellectedTool = ToolBar::Tool::TRANSLATE;
			JGN_PostRedisplay();
		}
		else if ((key == 'd' || key == 'D') && s == JGN_DOWN)
		{
			vs.unsellectAll();
			tb._Nsellectedfordistance = 0;
			tb.sellectedTool = ToolBar::Tool::DISTANCE;
			tb._Nsellectedfordistance = 0;
			tb._sellectedfordistance[0] = jgn::vec2(-1, -1);
			tb._sellectedfordistance[1] = jgn::vec2(-1, -1);
			iClickedForDistance = 2;
			JGN_PostRedisplay();
		}
		else if ((key == 's' || key == 'S') && s == JGN_DOWN)
		{
			if (CustomSurfacesOn)
			{
				tb.sellectedTool = ToolBar::Tool::SELECT;
				vs.unsellectAll();
				//int asdf = t * sized[0] * sized[1] * sized[2];
				//for (int i = 0; i < asdf; i++)
				//{
				//	isSelected[i] = false;
				//}
			}
			else
			{
				S2v = S2v - 1;
				if (S2v < 0)
				{
					S2v = 0;
				}
				if (nanotube)
				{
					MakeScroll();
				}
			}


			
			check_if_to_redisplay = 1;

		}
		else if ((key == 'z' || key == 'Z') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[2]++;
				sized[2]++;


				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[2] / 2 == jgn_supercell_xyz[2] / 2.0)
				{
					xexe[2] = 0;
				}
				else
				{
					xexe[2] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				Right_Hexagonal_height++;
				S3v = S3v + 1;
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		else if ((key == 'x' || key == 'X') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[2]--;
				if (jgn_supercell_xyz[2] < 0)
				{
					jgn_supercell_xyz[2] = 0;
				}
				sized[2] = jgn_supercell_xyz[2];



				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[2] / 2 == jgn_supercell_xyz[2] / 2.0)
				{
					xexe[2] = 0;
				}
				else
				{
					xexe[2] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{

					Right_Hexagonal_height--;
					if (Right_Hexagonal_height < 0)
					{
						Right_Hexagonal_height = 0;
					}
					S3v = S3v - 1;
					if (S3v < 0)
					{
						S3v = 0;
					}
					if (nanotube)
					{
						MakeScroll();
					}

				}
			check_if_to_redisplay = 1;

		}
		if (S1[0] == '1')
		{
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*100 110 111*/Scase = 1;
				if (2 * S1v <= S2v && S3v >= 3 * S1v && figure_1 != -1)
				{
					Scase = 4;
				}
				else if (S1v >= S2v && float(S3v) >= (float(S2v) * 3) / 2)
				{
					Scase = 6;
				}
				else if (S1v >= S3v && S3v <= S2v)
				{
					Scase = 7;
				}
				else if (S1v >= S2v)
				{///////
					Scase = 5;
				}
				else if ((S2v >= 2 * S1v && figure_1 != -1)|| S3v <= S2v)
				{
					Scase = 3;
				}
				else if ((float(S3v) >= (float(S2v) * 3) / 2 && figure_1 != -1) || (figure_1 == -1 && S3v>=2*S2v))
				{

					Scase = 2;
				}

				}
				else {/* 100 110*/Scase = 2;/*done*/
				if (S1v >= S2v)
				{
					Scase = 6;
				}
				else if (S2v >= 2 * S1v)
				{
					Scase = 4;
				}


				}
			}
			else {
				if (S3[0] == '1') {/*100 111*/Scase = 3;/*done*/
				if (S1v >= S3v)
				{
					Scase = 7;
				}
				else if (S3v >= 3 * S1v)
				{
					Scase = 4;
				}

				}
				else {/* 100*/Scase = 4;/*done*/


				}
			}
		}
		else {
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*110 111*/Scase = 5;/*done*/
				if (float(S3v) >= (float(S2v) * 3) / 2)
				{

					Scase = 6;
				}
				else if (S3v <= S2v) {
					Scase = 7;
				}
				}
				else {/*110*/Scase = 6;/*done*/


				}
			}
			else {
				if (S3[0] == '1') {/*111*/Scase = 7;/*done*/

				}
				else {/**/Scase = 0;


				}
			}
		}


		lines_param();

	
		if (check_if_to_redisplay)
		{
			JGN_PostRedisplay();
		}
		
	}

	
}


void lines_param()
{
	if (figure_1 == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;
		int S3vb = S3v;





		if (2 * S2v - S3v >= S1v)
		{
			if (S3v < S2v)
			{
				S2v = S3v;
			}
			if (S3v < S1v)
			{
				S1v = S3v;
			}


			first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
			second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
			third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
			forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
			fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);
			sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);



		}
		else
		{
			if (2 * S2v < S3v)
			{
				S3v = S2v * 2;

			}
			if (S2v < S1v)
			{
				S1v = S2v;
			}


			first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
			second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
			third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
			forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
			fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);
			sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);







		}


		S1v = S1vb;
		S2v = S2vb;
		S3v = S3vb;

	}
	else if (Rod_like == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;

		if (S3v < S2v)
		{
			S2v = S3v;
		}
		if (S2v < S1v)
		{
			S1v = S2v;
		}
		if (2 * S1v < S2v)
		{
			S2v = 2 * S1v;

		}


		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);


		sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);

		eighth = (GLfloat)1.0*float(S3v) / (Svmax + 5);



		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Right_Hexagonal == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;


		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Scase == 1)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);

		fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);


	}
	else if (Scase == 2)
	{

		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);


		seventh = (GLfloat)1.0*float(S2v) / 2 / (Svmax + 5);
	}
	else if (Scase == 3)
	{


		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);


		sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);
		nineth = (GLfloat)1.0*float(S3v - 2 * S1v) / (Svmax + 5);
		tenth = (GLfloat)1.0*float((S1v)) / (Svmax + 5);


	}
	else if (Scase == 4)
	{


		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);




	}
	else if (Scase == 5)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);


		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
		fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);


	}
	else if (Scase == 6)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);


		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);

		eleventh = 1.0*float(S2v) / ((Svmax + 5) * 2);



	}
	else if (Scase == 7)
	{






		eighth = (GLfloat)1.05*float(S3v) / (Svmax + 5);
	}
	else if (Scase == 0)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
		fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);
		sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);
		seventh = (GLfloat)1.0*float(S2v) / 2 / (Svmax + 5);
		eighth = (GLfloat)1.0*float(S3v) / (Svmax + 5);
	}


}

void menuf(int c)
{
	if (c == 0)
	{
		BuildPoscar(NewPC);
	}
	if (c == 1)
	{

		if (cam.perspective_on)
		{
			truepointsize = 1000.0;
			pointsize = truepointsize / (Svmax + 5);
			glPointSize(pointsize);

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
				dipleft = -1;
				dipapan = (GLfloat)height / (GLfloat)width;

			}
			else
			{
				glOrtho(
					-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
					-1.05, +1.05,
					-10.0, 10.0);
				dipleft = -(GLfloat)width / (GLfloat)height;
				dipapan = 1;


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
			truepointsize = 1000.0;
			pointsize = truepointsize / (Svmax + 5);
			glPointSize(pointsize);

		}

		
	}

	JGN_PostRedisplay();
}

void Sub_Menu(int c)
{
	if (c == 1)
	{
		Rod_like = 1;
		figure_1 = 1;
		Right_Hexagonal = -1 ;
		Svmax = 50;
		S1v = 25;
		S2v = 35;
		S1i[0] = 1;
		S2i[0] = 1;
		S3i[0] = 0;
		S1 = "100";
		S2 = "110";
		S3 = "000";

	}
	if (c == 2)
	{
		Right_Hexagonal = 1;
		figure_1 = 1;
		Rod_like = -1;
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
	}
	if (c == 3)
	{
		figure_1 = -1;
		Right_Hexagonal = 1;
		Rod_like = 1;
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

	}

	JGN_PostRedisplay();


}


void findClicked()
{
	int asdfjlk = t * sized[0] * sized[1] * sized[2];

	iClickedForDistance++;
	if (iClickedForDistance > 1)
	{
		iClickedForDistance = 0;
		isSelected[ClickedForDistance[0]] = false;
		isSelected[ClickedForDistance[1]] = false;
		ClickedForDistance[0] = -1;
		ClickedForDistance[1] = -1;
		DrawDistanceLine = false;
		JGN_PostRedisplay();
	}
	else if (iClickedForDistance == 1)
	{
		DrawDistanceLine = true;
	}
	float prevp1[3];
	prevp1[0] = 0;
	prevp1[1] = 0;
	prevp1[2] = 0;
	for (int i = 0; i < asdfjlk; i++)
	{
		float p1[3];
		float p2[3];
		float theta_rad[3];

		p1[0] = crystal[2 + 5 * i] / (Svmax + 5);
		p1[1] = crystal[3 + 5 * i] / (Svmax + 5);
		p1[2] = crystal[4 + 5 * i] / (Svmax + 5);

		theta_rad[0] = theta[0] * M_PI / 180;
		theta_rad[1] = 0;
		theta_rad[2] = theta[1] * M_PI / 180;



		jgn::cpu_translate(p1, (float*)model_translate, p2);
		jgn::cpu_rotate(p2, (float*)theta_rad, p1);
		p1[2] = -p1[2];

		///at this point p1 is the final product


		if (jgn::dist2d(leftClick.finish, p1) < pointsize*0.001)
		{
			if (ClickedForDistance[iClickedForDistance] == -1)
			{
				ClickedForDistance[iClickedForDistance] = i;
				prevp1[0] = p1[0];
				prevp1[1] = p1[1];
				prevp1[2] = p1[2];


			}
			else if(p1[2]<prevp1[2]){
				ClickedForDistance[iClickedForDistance] = i;
				prevp1[0] = p1[0];
				prevp1[1] = p1[1];
				prevp1[2] = p1[2];

			}
		}



	}
	if (ClickedForDistance[iClickedForDistance] != -1)
	{
		isSelected[ClickedForDistance[iClickedForDistance]] = true;


	}

	if (iClickedForDistance == 1)
	{
		tb.sellectedTool = ToolBar::Tool::ROTATE;
		pForDistance[ 0] = crystal[2 + 5 * ClickedForDistance[0]];
		pForDistance[ 1] = crystal[3 + 5 * ClickedForDistance[0]];
		pForDistance[ 2] = crystal[4 + 5 * ClickedForDistance[0]];
		pForDistance[3] = crystal[2 + 5 * ClickedForDistance[1]];
		pForDistance[4] = crystal[3 + 5 * ClickedForDistance[1]];
		pForDistance[5] = crystal[4 + 5 * ClickedForDistance[1]];
		//TODO:
		//correct distance clean the trash!!!!
		Dist2Disp = sqrt(jgn::dist3dSquare(crystal[2 + 5 * ClickedForDistance[0]], crystal[2 + 5 * ClickedForDistance[1]]));
	}
}


void mouse_pasive(int x, int y)
{
	float jgn_x;
	float jgn_y;
	if (width <= height)
	{

		jgn_x = 2.1 * ((x / (float)width) - 0.5);
		jgn_y = 2 * (1.05 * (GLfloat)height / (GLfloat)width) * (-((y / (float)height) - 0.5));

	}
	else
	{
		jgn_x = 2 * (1.05 * (GLfloat)width / (GLfloat)height) * ((x / (float)width) - 0.5);
		jgn_y = 2.1 * (-((y / (float)height) - 0.5));
	}

	mouse.pos.x = jgn_x;
	mouse.pos.y = jgn_y;

	tb.hoveringAtool(jgn_x, jgn_y);
	vs._hoveringAnatom(jgn::vec2(jgn_x, jgn_y));
	vs.grouplist.checkhoverstatus(jgn::vec2(jgn_x, jgn_y));
	vs.grouplist.options.checkhoverstatus(jgn::vec2(jgn_x, jgn_y));
	menu.hoverstatecheck(menu.editselected, jgn::vec2(jgn_x, jgn_y));
	menu.hoverstatecheck(menu.mainmenu, jgn::vec2(jgn_x, jgn_y));
	if (vs.selected_translate_ison || vs.selected_rotate_ison)
		vs.selected_change_hover_check(jgn::vec2(jgn_x, jgn_y));
	if (lmb == JGN_UP)
	{
		if ((tb.sellectedTool == ToolBar::Tool::SELECT || tb.sellectedTool == ToolBar::Tool::DISTANCE) && !wn.show)
		{
			if (tb.sellectedTool == ToolBar::Tool::SELECT && mouse_check == 1)
			{
				//if (leftClick.start[0] == leftClick.finish[0] && leftClick.start[1] == leftClick.finish[1])
				//{
					if (!(shift_down || wn.show))
						vs.unsellectAll();
					tb.usetool.sellect();
				//}

			}
			else if (tb.sellectedTool == ToolBar::Tool::DISTANCE && mouse_check == 1)
			{
				tb._sellectedfordistance[tb._Nsellectedfordistance] = tb.usetool._singlesellect();
				if (tb._sellectedfordistance[tb._Nsellectedfordistance].y != -1)
					tb._Nsellectedfordistance++;
				if (tb._Nsellectedfordistance == 2)
				{
					tb._Nsellectedfordistance = 0;
					tb.sellectedTool = ToolBar::Tool::ROTATE;
				}
			}
			leftClick.start[0] = jgn_x;
			leftClick.start[1] = jgn_y;
			leftClick.finish[0] = jgn_x;
			leftClick.finish[1] = jgn_y;


			JGN_PostRedisplay();
		}
		else if (tb.sellectedTool == ToolBar::Tool::ROTATE || mouse_mode == 'o' || mouse_mode == 'a' || tb.sellectedTool == ToolBar::Tool::DISTANCE)
		{
			if (!vs.noupdate)
			{
				theta_prev[0] = -theta[0];
				theta_prev[1] = -theta[1];
			}

		}		
		else if (tb.sellectedTool == ToolBar::Tool::TRANSLATE)
		{
			if (!vs.noupdate)
			{
				translate_prev[0] = -model_translate[0];
				translate_prev[1] = -model_translate[1];
				translate_prev[2] = -model_translate[2];
			}
		}
			mouse_check = 0;
		mouse_x = x;
		mouse_y = y;
	}
	else
	{
		if (vs.istranslating_theselected)
		{
			vs.translate_selected(mouse.pos, mouse.prevpos);
		}
		else if (vs.isrotating_theselected)
		{
			vs.rotate_selected(mouse.pos, mouse.prevpos);

		}
		if((tb.sellectedTool == ToolBar::Tool::SELECT || tb.sellectedTool == ToolBar::Tool::DISTANCE) && !wn.show)
		{
			if (mouse_check == 0)
			{
				leftClick.start[0] = jgn_x;
				leftClick.start[1] = jgn_y;
				leftClick.finish[0] = jgn_x;
				leftClick.finish[1] = jgn_y;


			}
			else
			{
				leftClick.finish[0] = jgn_x;
				leftClick.finish[1] = jgn_y;


			}
			mouse_check = 1;
			if (tb.sellectedTool == ToolBar::Tool::SELECT)
			{
				if (!(leftClick.start[0] == leftClick.finish[0] && leftClick.start[1] == leftClick.finish[1]))
				{
					if (!(shift_down || wn.show))
						vs.unsellectAll();
					tb.usetool.sellect();
				}
			}
		}
		else if (tb.sellectedTool == ToolBar::Tool::ROTATE || mouse_mode == 'o' || mouse_mode == 'a' || tb.sellectedTool == ToolBar::Tool::DISTANCE)
		{
			if (mouse_check == 0)
			{
				if (!vs.noupdate)
				{
					theta_start[0] = y * 0.2 + theta_prev[0];
					theta_start[1] = 0.2*x + theta_prev[1];
				}
			}
			mouse_check = 1;
			if (!vs.noupdate)
			{
				theta[0] = y * .2 - theta_start[0];
				theta[1] = x * .2 - theta_start[1];
			}


		}
		else if (tb.sellectedTool == ToolBar::Tool::TRANSLATE)
		{
			if (mouse_check == 0)
			{
				translate_start[0] = jgn_x* cos(theta[1] * M_PI / 180) + jgn_y * cos(theta[0] * M_PI / 180)*sin(theta[1] * M_PI / 180) + translate_prev[0];
				translate_start[1] = -jgn_x * sin(theta[1] * M_PI / 180) + jgn_y * cos(theta[0] * M_PI / 180)*cos(theta[1] * M_PI / 180) + translate_prev[1];
				translate_start[2] = -sin(theta[0] * M_PI / 180)*jgn_y + translate_prev[2];
			}
			mouse_check = 1;
			if (!vs.noupdate)
			{
				model_translate[0] = jgn_x * cos(theta[1] * M_PI / 180) + jgn_y * cos(theta[0] * M_PI / 180)*sin(theta[1] * M_PI / 180) - translate_start[0];
				model_translate[1] = -jgn_x * sin(theta[1] * M_PI / 180) + jgn_y * cos(theta[0] * M_PI / 180)*cos(theta[1] * M_PI / 180) - translate_start[1];
				model_translate[2] = -jgn_y * sin(theta[0] * M_PI / 180) - translate_start[2];
			}
		}
		

		JGN_PostRedisplay();
	}
	mouse.prevpos = mouse.pos;

	JGN_PostRedisplay();
}


void mouse_func(int b, int s, int x, int y)
{
	float xnorm = -((float)x / (float)width - 0.5)*2*dipleft;
	float ynorm = -((float)y / (float)height - 0.5)*2*dipapan;
	glLoadIdentity();

	if (b == JGN_LEFT_MOUSE_BUTTON)
	{
		//CustomSurfaceSelected = -1;
		//for (i = 0; i < CustomSurfacesCount; i++)
		//{//select a surface
		//	if (xnorm < dipleft + 0.4 && ynorm< dipapan - 0.01 - (i - 1) * (0.075) && ynorm>dipapan - 0.01 - i * (0.075))
		//	{
		//		CustomSurfaceSelected = i;

		//		
		//	}
		//}
		if (s == JGN_DOWN)
		{
			if (vs.selected_change_hovered_axes != NO_AXIS)
			{
				if (vs.selected_translate_ison)
				{
					vs.noupdate = true;
					vs.istranslating_theselected = true;
				}
				else if (vs.selected_rotate_ison)
				{
					vs.noupdate = true;
					vs.isrotating_theselected = true;
				}
			}
			else if (tb.tooldownclicked(xnorm, ynorm))
			{
			}
			else if (vs.grouplist.hovering)
			{
				vs.grouplist.open = vs.grouplist.open ^ true;
			}
			else if (vs.grouplist.options.hovering != -1)
			{
				vs.unsellectAll();
				tb.sellectedTool = ToolBar::Tool::ROTATE;
				for (int i = 0; i < vs.group[vs.grouplist.options.hovering].N_atoms; i++)
				{
					vs.group[vs.grouplist.options.hovering].isSelected[i] = true;
				}
				vs._sellectHistory2undo++;
				for (int i = 0; i < vs.N_atoms; i++)
				{
					if (vs._sellectHistory[i].x == vs.grouplist.options.hovering)
					{
						vs._sellectHistory[i].z = vs._sellectHistory2undo;
					}
				}
			}
		}
		else
		{
			if (vs.selected_translate_ison && vs.noupdate==true)
			{
				vs.noupdate = false;
				vs.istranslating_theselected = false;
			}
			else if (vs.selected_rotate_ison && vs.noupdate == true)
			{
				vs.noupdate = false;
				vs.isrotating_theselected = false;
			}
			else if (menu.show)
			{
				jgn::vec2 cl = menu.clicked(jgn::vec2(xnorm, ynorm));
				if (cl.x == Menu::NONE && cl.y == Menu::NONE)
				{
					//std::cout << "NONE" << std::endl;
					menu.show = false;
				}
				else if (cl.y == Menu::TRANSLATE)
				{
					tb.sellectedTool = ToolBar::Tool::ROTATE;
					vs.toggleselected_translate(true);
					menu.show = false;
				}
				else if (cl.y == Menu::ROTATE)
				{
					tb.sellectedTool = ToolBar::Tool::ROTATE;
					vs.toggleselected_rotate(true);
					menu.show = false;
				}
				else if (cl.y == Menu::CHANGE_ELEMENT)
				{
					wn.in_message = "Give the element";
					wn.in_message_translate = jgn::vec3(0.12, 0.25, 7);
					menu.show = false;
				}
				else if (cl.y == Menu::CHANGE_RADIUS)
				{
					wn.in_message = "Give the radius";
					wn.in_message_translate = jgn::vec3(0.17, 0.25, 7);
					menu.show = false;
				}
				else if (cl.y == Menu::SELECTIVE_DYNAMICS)
				{
					wn.in_message = "Selective dynamics";
					wn.in_message_translate = jgn::vec3(0.1, 0.25, 7);
					menu.show = false;
				}
			}
			else if (tb.toolclicked(xnorm, ynorm))
			{
				if (tb.sellectedTool == ToolBar::Tool::DISTANCE)
				{
					vs.unsellectAll();
					tb._Nsellectedfordistance = 0;
				}
			}
			menu.shownon();
		}

		lmb = s;

		JGN_PostRedisplay();
	}
	else if (b == JGN_RIGHT_MOUSE_BUTTON && s == JGN_UP)
	{
		menu.show = true;
		menu.mainmenu->coords = jgn::vec2(xnorm, ynorm);
		menu.editselected->coords = jgn::vec2(xnorm+0.5, ynorm);
		JGN_PostRedisplay();
	}
	else if (b == JGN_MOUSE_WHEEL && s == JGN_UP)//zoom out
	{
		Svmax = Svmax - 5;
		if (Svmax < 0)
		{
			Svmax = 0;
		}
		pointsize = truepointsize/(Svmax + 5);
		JGN_PostRedisplay();

	}
	else if (b == JGN_MOUSE_WHEEL)//zoom in
	{

		Svmax = Svmax + 5;

		pointsize = truepointsize/(Svmax + 5);

		JGN_PostRedisplay();

	}




	lines_param();




}




