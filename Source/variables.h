#pragma once


//#define DOUBLE_MOD

#ifdef DOUBLE_MOD

#define float double
#define glColor3fv glColor3dv
#define glVertex3fv glVertex3dv
#define glNormal3fv glNormal3dv
#define glNormal3f glNormal3d
#define glVertex3f glVertex3d
#define printformat 15
#define fl_max DBL_MAX
#define fl_min DBL_MIN

#else

#define printformat 6
#define fl_max FLT_MAX
#define fl_min FLT_MIN


#endif


void myReshape(int w, int h);
void display1();
void spin_image();
void mouse_pasive(int x, int y);
void myinit();
void keyboardgl(int key, int s, int x, int y);
void menuf(int c);
void BuildPoscar(char* a);
void BuildLammps(char* a);
void Sub_Menu(int c);
void mouse_func(int b, int s, int x, int y);
void lines_param();
void jgnCommands(LPTSTR ttt, int d);
void variableinit();
void JGN_QRedisplay();
void deleteSelected();
//
//  Global data.
//

EXT std::size_t found;
EXT char ftype;// p=poscar, l=lammps
#define SBYTES 200


EXT char* NewPC;

EXT char* PCtype;

EXT float ttest[81000000];
EXT int lmb;//left mouse button
EXT bool capson;
EXT int wasfullscreenflagin;
EXT int wasfullscreenflagout;
EXT GLuint Font;
EXT GLuint button1ID;
EXT GLuint buttonID;
EXT GLuint cursorToolsImg[4];
EXT GLuint showmoreID;
EXT GLuint showlessID;
EXT GLuint vboId;
EXT float dipleft;
EXT float dipapan;
EXT GLfloat theta[3];
EXT int flagmax;
EXT GLfloat first;
EXT GLfloat second;
EXT GLfloat third;
EXT GLfloat forth;
EXT GLfloat fifth;
EXT GLfloat sixth;
EXT GLfloat seventh;
EXT GLfloat eighth;
EXT GLfloat nineth;
EXT GLfloat tenth;
EXT GLfloat eleventh;
EXT std::chrono::time_point<std::chrono::steady_clock> cl_start;
EXT std::chrono::time_point<std::chrono::steady_clock> cl_end;
EXT std::chrono::duration<float> cl_duration;
EXT int sphStacks;
EXT int sphSides;
EXT bool qredisplay;
EXT double xyz_range[3];
EXT double xyz_scale;
EXT double xyz_center[3];
EXT int allatoms;
EXT long int sized[3];
EXT long int t/*how many atoms in the unit cell*/;
EXT long int prev_sized[3];
EXT float Truncated_Cube_max[3];
EXT float min_xyz[3];
EXT float max_xyz[3];
EXT int mouse_check;
EXT float mouse_y, mouse_x;
EXT long int ole, ole1, ole2, ole3, ole4, ole5;
EXT float *crystal;
EXT float *crystal_backup;
EXT char *selective_dynamics;
EXT bool* isSelected;
//float tube_rin = 20, tube_rout = 30, tube_param = 80;
EXT float colr[3];
EXT float rad;
EXT char want_cyrcle[5];
EXT int nanotube;
EXT int full;
EXT char mouse_mode;// 's'elect, 'r'otate, 't'ranclate, 
//					// selected r'o'tate, selected tr'a'nslate
EXT float model_translate[3];
EXT float selected_rotate[3];
EXT float selected_translate[3];
EXT int selected_rotate_axes;//1=x,2=y,3=z
EXT int ClickedForDistance[2];
EXT float Dist2Disp;
EXT int iClickedForDistance;
EXT bool DrawDistanceLine;
EXT float pForDistance[6];
EXT int selected_translate_direction;//0=x,1=y,2=z
EXT bool *isdeleted;
EXT int *deletedHistory;//which atom is deleted
EXT int Ndeletes;//how many time did I delete? help to ctrl+z
EXT float sinTable32[31], cosTable32[31], sincurTheta32[32], coscurTheta32[32];//Hard codes sin and cos for JGN_SolidSphere performance

class MOUSECLICK
{
public:
	float start[2];
	float finish[2];
}EXT leftClick;
EXT float zmax100111[3];
EXT float zmax100111_[3];
EXT int Scase;
EXT float figure_1;
EXT float Right_Hexagonal;
EXT float Right_Hexagonal_height;
EXT float *aweights;
EXT float pointsize;
EXT float truepointsize;
EXT bool vacuum;// 0=false, 1=true
EXT int *anumber;//atomic number
EXT char ss[20];
EXT int *aatoms;// real time atoms cound
EXT int Svmax_buckup;
EXT float Rod_like;
EXT int width, height;
EXT int jgn_supercell;
EXT int jgn_supercell_xyz[3];
EXT float *my_direct, *uccartesian;
EXT float ijk[3][3];//ta 3 dianismata symmetrias
				//dn kserw posa diaforetika atoma 9a exei...
				//o kristallos. ypo8etw oti dn 8a einai panw apo 5
				//kai ka8e ena exei 3 bytes gia na xwresei kai to \0

EXT int xexe[3];
EXT int sized_old[3];
EXT int was_supercell;
EXT HWND hWndCommandLine;
EXT HWND hWndList;
EXT HDC global_hdc;


EXT char *S1;
EXT char *S2;
EXT char *S3;
EXT char *s1;
EXT bool render_is_on;
EXT int S1v, S2v, S3v;
EXT int S1i[3], S2i[3], S3i[3];
EXT char S1a;
EXT int Svmax;
EXT jmp_buf  build_posc_jmp;
EXT int jgn_file_dropd;
EXT LPTSTR lpszFile;
EXT char inpf[500];
EXT TCHAR CommandBuffer[500];
EXT INPUT keybinp;
#if !defined(JGN_NO_CMD_HISTORY) 
EXT HWND CommandTextHistory;
#endif
EXT int my_postmessages_count;
EXT int CustomSurfacesCount;
EXT int CustomSurfaceSelected;
EXT float **CustomSurfaces;
EXT int **CustomSurfaces_hkl;
EXT int CustomSurfacesOn;
EXT HBRUSH brush;
EXT HFONT fOnt;
EXT char *help;
EXT int loop;
EXT int sizedprotector[3];
EXT int anotherokrender;
EXT int wait;
EXT int custom_sized[3];
EXT int itemsel;
EXT int predicted;
EXT wchar_t widechar[50];
EXT char* listboxcurent;
EXT std::map<int, char*> boxlistmap;					// map hwnd of the parent windows created to an int counter
EXT wchar_t ucender[2];
EXT WNDPROC oldEditProc;
EXT int mainwndsize[2];
EXT int cmdwndh;
EXT long* mnrcpt;
EXT HWND hwndcmdjgn;
EXT HWND mnhwnd;
EXT HWND CommandTextField;
EXT LPRECT glb_rct;


EXT int ball_atoms;
EXT int ballflag;
EXT char *uc_file_input;
EXT float theta_pr[2];
EXT int *atomic_number;
EXT int *new_num_atoms;
EXT int i, j, k;
EXT float fak;
EXT char *shelp;
EXT char *atomshelp;
EXT char* token3;
EXT float sim_box_lo[3];

EXT int shperes_on;// render as spheres or points

#ifdef JGN_WINDOWS_CPP

static const int testsc = 25;
static char *test1[testsc] = { "vector(",
"clean",
"undo",
"supercell(",
"cut(",
"script(",
"spheres",
"points",
"phonon(",
"render ",
"randSelection%(",
"changeElement(",
"save(",
"loadOrigin",
"rotate(",
"randSelection(",
"delete",
"restart",
"fopen(",
"mkfacet(",
"randstress",
"placerandomly(",
"magmomup(",
"icosahedron(",
"decahedron("
};
static char *test1low[testsc] = { "vector(",
"clean",
"undo",
"supercell(",
"cut(",
"script(",
"spheres",
"points",
"phonon(",
"render ",
"randSelection%(",
"changeElement(",
"save(",
"loadOrigin",
"rotate(",
"randSelection(",
"delete",
"restart",
"fopen(",
"mkfacet(",
"randstress",
"placerandomly(",
"magmomup(",
"icosahedron(",
"decahedron("
};
static wchar_t *helplist[testsc] = { L"vector(int h,int c,int l,int A)",
L"clean",
L"undo",
L"supercell(int a1,int a2,int a3)",
L"cut(int u,int v,int w,int A)",
L"script(\"file path\")",
L"spheres",
L"points",
L"phonon(float r)",
L"render on/off",
L"randSelection%(float (0-1))",// randomly select atoms with change from 0-1
L"changeElement( e.x Fe )",
L"save(string path file e.x \"POSCAR\")",//save the data to a POSCAR format at the specified location
L"loadOrigin",//load the orginal data as befor the user changes
L"rotate(axes (x,y or z), float z)",//rotates the selected
L"randSelection(int)",//select int random atoms
L"delete",//delete selecte atoms
L"restart",
L"fopen(\"data path\")",
L"mkfacet(h,k,l)",//places the <hkl> vector perpendicular to z-axis
L"randstress",
L"placerandomly(element, min distance",//randomly place an "element" atom to the system with a minimum distance of # from evry atom
L"magmomup(h,k,l)",//rotate the atoms and the unit vectors of a surface, so that magmom looks upwards
L"icosahedron(lattice constant, int noshells)",
L"decahedron(int p, int q, int r, float lattice_constant)"
};
#endif	// JGN_SOURCE_CPP



EXT bool selective_dynamics_bool;
EXT char* jgncmdfpath;
EXT FILE* jgncmdfile;
EXT char jgncmdfline[500];
EXT char inptype;
EXT float vec[3];
EXT int crystalh;
EXT int crystalk;
EXT int crystall;
EXT int atomscc;
EXT float* atoms_to_print;
EXT int atoms_to_print_c;
EXT char* atoms;
EXT int a;//a: posa eidi atomwn
EXT float *an_and_aw;
EXT float helping1, helping2, helping3;
EXT float helpme34[3][4];
EXT float helpme14[1][4];
EXT bool shift_down;
EXT float glob_translate[3];
EXT float glob_translate_prev[3];
EXT int db;


//////////////////////////////////////////////////////////////winproc
EXT HDC hdc;
EXT LARGE_INTEGER lpPerformanceCount;

//QueryPerformanceCounter(&lpPerformanceCount);

EXT int wmId, wmEvent;
EXT char* token, *token1, *s;
EXT int *ea;
EXT FILE* uc_file;

EXT int line, p;//line: gia na kserw se poia gramh eimai
					//p:diksths gia ta dianismata

					//t:ari8mos olwn twn atomwn sto unit cell
					//ole1: voi8itikos
EXT float actor;//actor: einai aytos o pollaplasiasths panw apo ta vectors						


EXT FILE* periodic_table;
EXT int alloena;
EXT int ka8isterimenoflag;
EXT FILE *NewPCF;
EXT int help0;
EXT int help1;
