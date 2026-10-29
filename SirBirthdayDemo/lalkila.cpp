// header files
// win32 header files
#include<Windows.h>
#include<stdio.h> // For file I/O operations
#include<stdlib.h> // For exit() function
#include<math.h>
#include <mmsystem.h>

// opengl related header files
#include<gl/GL.h>

// 070928
#include<gl/glu.h>
// standard C header files 220826
#include "coinFlip.h"
#include "Shader.h"
#include "lalkila.h"
#include "HappyBirthday.h"
#include "SirPortrait.h"
#include "MemberName.h"
#include "SpecialThanks.h"
#include "Title.h"
#include "Parnakuti.h"
#include "Map.h"
#include "Scene2.h"
#include "Scene3.h"
#include "sanskrit_lettering.h"

// Link with OpenGL import library
#pragma comment(lib,"opengl32.lib")
//070928
#pragma comment(lib,"glu32.lib")

#pragma comment(lib, "Winmm.lib")

#define M_PI 3.14159265358979323846

// **************************************************
// global variable declarations
//**************************************************
// sky meets ground
const float HORIZON = -0.60f;  
DWORD g_startTime = 0;

// Time and Zoom state variables

float g_zoomScale = 1.0f;

//macros 220826"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations/prototype/signature
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL bFullscreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;
FILE  *gpFile = NULL;
//300826
BOOL bActiveWindow = FALSE; // variable to keep track of window focus
BOOL bEscapeKeyIsPressed = FALSE; // variable to keep track of escape key press

extern GLuint texture_Quote_SM;
//******************************************************************* */
// Function declarations
//******************************************************************* */
void resize(int width, int height);
int initialize(void);
void fortTimer(void);
void showSirsBirthdayGift(void);

//void drawSkyBackground(float elapsedTime);

void displayLalkila(void);
void uninitialize(void);


//******************************************************************* */
// Entry-point function
//******************************************************************* */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declarations
	int initialize(void);
	void render(void);
	void update(void);
	void uninitialize(void);

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd = NULL;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR7_ARB");
	//300826
	BOOL bDone = FALSE; // variable to keep track of message loop termination

	// Create log file for debugging 280826
	gpFile = fopen("Log.txt", "w");
	if (gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log file creation failed."), TEXT("Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Program started successfully.\n");
	}

	// window class initialization
	//ya 12 lines ani register class mhnje OGL.c cha glutInit(&argc, argv);
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc; //function pointer = Name of the function is itself is its address
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wndclass.hIcon = LoadIcon(IDI_APPLICATION);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	//wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Registration of Window Class
	RegisterClassEx(&wndclass);

	// Centering the Window on the screen 220826
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// 290826
	hwnd = CreateWindowEx( WS_EX_APPWINDOW,
						szAppName,
						TEXT("ABHILASH R. BARI"),
						WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
						screenWidth/2 - WIN_WIDTH/2, 
						screenHeight/2 - WIN_HEIGHT/2,
						WIN_WIDTH, //rumalachi rundi
						WIN_HEIGHT, //rumalachi unchi
						NULL,
						NULL,
						hInstance,
						NULL);

	// 6 -7th parameter means OGL.c cha glutInitWindowSize(800, 600);
	// 4 -5th parameter mhnaje OGL.c cha glutInitWindowPosition(100, 100);
	// 2nd parameter mhnnje  OGL.c cha glutCreateWindow("Abhilash R. Bari");
	// 

	// set global window handle
	ghwnd = hwnd;

	//300826
	int iResult = initialize();
	if (iResult != 0)
	{
		fprintf(gpFile, "WinMain(): Failed to initialize.\n");
		DestroyWindow(hwnd);
		hwnd = NULL;
	}
	else
	{
		fprintf(gpFile, "WinMain(): Initialization() successful.\n");
	}

	// show Window
	ShowWindow(hwnd, iCmdShow);

	// Paint background of the window
	UpdateWindow(hwnd);

	//300826
	SetForegroundWindow(hwnd); // bring window to foreground
	SetFocus(hwnd); // set focus to the window

	// messgage loop
	//OGL.c GLUT main() mhnje he while ch sampurn loop
	/*
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	*/
	// Game loop 300826
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // GetMessage() cha alternative, GetMessage() block karte, PeekMessage() block nahi karte
		{
			if (msg.message == WM_QUIT) // WM_QUIT message received, exit the loop
			{
				bDone = TRUE; // exit the loop
			}
			else
			{
				TranslateMessage(&msg); // Translate the message
				DispatchMessage(&msg); // Dispatch the message to WndProc()
			}
		}
		else
		{
			if (bActiveWindow == TRUE) // window is active, so update and render
			{
				if (bEscapeKeyIsPressed == TRUE) // escape key is pressed, exit the loop
				{
					bDone = TRUE; // exit the loop
				}
				// render the scene
				showSirsBirthdayGift();
				//fortTimer();
				//glutTimerFunc(16, fortTimer, 0); // Start fortTimer loop (~60 FPS)
				// update the scene
				update();
			}
		}
	}

	// uninitialization
	uninitialize();
	
	return((int)msg.wParam);
}

void toggleFullscreen(void)
{
	// variable declarations
	MONITORINFO mi;
	//code
	if(bFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if(dwStyle & WS_OVERLAPPEDWINDOW)
		{
			memset(&mi, 0, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);
			if(GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW); //style negate keli
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW); // style add keli
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	// function declarations
	void resize(int, int);
	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	g_startTime = (int)timeGetTime();
	float elapsedTime = ((int)timeGetTime() - g_startTime) / 1000.0f;

	// code
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1; // Convention
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;
	
	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		return(-1);
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		return(-2);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return(-3);
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		return(-4);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		return(-5);
	}

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Load Textures
	BOOL bResult = FALSE;
	bResult = loadGLTexture(&texture_Quote_SM, MAKEINTRESOURCE(IDBITMAP_QUOTE));
	if (bResult == FALSE)
		return(-6);

	// Enable Texturing
	// glEnable(GL_TEXTURE_2D);

	// choose screen clearing color as blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// warmup resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
	{
		height = 1; // to avoid infinity
	}

	// set the viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective projection
	//fovy 45.0f is standard
	// zNear = dolyala chiktlela square standard 0.1
	//zfar = 100.0f standard value
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void fortTimer()
{
    if (g_startTime == 0)
    {
        g_startTime = timeGetTime();
    }

    DWORD currentTime = timeGetTime();
    float elapsedTime = (currentTime - g_startTime) / 1000.0f; // seconds

	const float PHASE0_CoinFlip_DUR        = 20.0f;  // 0s - 20s: Coin Flip Animation
	const float PHASE1_Shader_DUR          = 4.0f;  // 21s - 24s: Shaders Presents
	const float PHASE2_Title_DUR           = 4.0f;  // 25s - 28s: Title
	const float PHASE3_KILLA_DUR           = 6.0f;  
	const float PHASE4_Darbar_DUR          = 4.0f; 
	const float PHASE5_Parnakuti_DUR       = 4.0f;
	const float PHASE6_Map_DUR             = 8.0f;
	const float PHASE7_SanskritQuote_DUR   = 4.0f;
	const float PHASE8_HAPPYBIRTHDAY_DUR   = 3.0f;
	const float PHASE9_Portrait_DUR        = 4.0f;
	const float PHASE10_Members_DUR        = 4.0f;
	const float PHASE11_SpecialThanks_DUR  = 3.0f;
	const float PHASE12_IgnitedBy_DUR      = 3.0f;

	  

	float t0 = PHASE0_CoinFlip_DUR;					
	float t1 = t0 + PHASE1_Shader_DUR;     				
	float t2 = t1 + PHASE2_Title_DUR;                     
	float t3 = t2 + PHASE3_KILLA_DUR;                      
	float t4 = t3 + PHASE4_Darbar_DUR;
	float t5 = t4 + PHASE5_Parnakuti_DUR;
	float t6 = t5 + PHASE6_Map_DUR;
	float t7 = t6 + PHASE7_SanskritQuote_DUR; 				
	float t8 = t7 + PHASE8_HAPPYBIRTHDAY_DUR;				
	float t9 = t8 + PHASE9_Portrait_DUR;				
	float t10 = t9 + PHASE10_Members_DUR;      					
	float t11 = t10 + PHASE11_SpecialThanks_DUR;                
	float t12 = t11 + PHASE12_IgnitedBy_DUR;

	if (elapsedTime < t0)
    {
        // 0s to 4s: Happy Birthday
        g_zoomScale = 1.0f;
    }
	else if (elapsedTime < t1)
	{
		// 4s to 8s: CoinFlip
		g_zoomScale = 1.0f;
	}
    else if (elapsedTime < t2)
    {
        // 4s to 8s: Kila
        g_zoomScale = 1.0f;
    }
	else 
    {
        g_zoomScale = 1.0f;
    }

	if (elapsedTime < t3)
    {
        // 0s to 4s:darber
        g_zoomScale = 1.0f;
    }


	if (elapsedTime < t4)
    {
        // 0s to 4s:parnakuti
        g_zoomScale = 1.0f;
    }

	if (elapsedTime < t5)
    {
        // 0s to 4s:Map
        g_zoomScale = 1.0f;
    }
	if (elapsedTime < t6)
    {
        // 0s to 4s:Sanskrit
        g_zoomScale = 1.0f;
    }
	if (elapsedTime < t7)
    {
        // 0s to 4s:Portrait
        g_zoomScale = 1.0f;
    }

	if (elapsedTime < t8)
    {
        // 0s to 4s:members Name
        g_zoomScale = 1.0f;
    }

	if (elapsedTime < t9)
    {
        // 0s to 4s:Special Thanks
        g_zoomScale = 1.0f;
    }

	if (elapsedTime < t10)
    {
        // 0s to 4s:Shader
        g_zoomScale = 1.0f;
    }

	if (elapsedTime < t11)
    {
        // 0s to 3s:title
        g_zoomScale = 1.0f;
    }

	/*
    // Phase Durations
    const float PHASE0_ASTROMEDICOMP_DUR    = 4.0f;  // 0s - 4s: AstroMediComp Screen
    const float PHASE1_SHADER_DURATION      = 4.0f;  // 4s - 8s: Display Shader
    const float PHASE2_CALL_FOR_FREEDOM_DUR = 4.0f;  // 8s - 12s: Call for Freedom
    const float PHASE3_BRS_DURATION         = 6.0f;  // 12s - 18s: BRS Screen
    const float PHASE4_DANDI_DURATION       = 6.0f;  // 18s - 24s: Dandi March
    const float PHASE5_ZOOM_OUT_DURATION    = 4.0f;  // 24s - 28s: Zoom-out transition to Lalkila
    const float PHASE6_FORT_DURATION        = 10.0f; // 28s - 38s: Lalkila normal screen
    const float PHASE7_FORT_ZOOM_DURATION    = 4.0f;  // 38s - 42s: Zoom-in transition
    const float TARGET_SCALE                = 60.0f;
    
    // Cumulative Time Markers
    float t0 = PHASE0_ASTROMEDICOMP_DUR;                           // 4.0s
    float t1 = t0 + PHASE1_SHADER_DURATION;                       // 8.0s
    float t2 = t1 + PHASE2_CALL_FOR_FREEDOM_DUR;                  // 12.0s
    float t3 = t2 + PHASE3_BRS_DURATION;                          // 18.0s
    float t4 = t3 + PHASE4_DANDI_DURATION;                        // 24.0s
    float t5 = t4 + PHASE5_ZOOM_OUT_DURATION;                    // 28.0s
    float t6 = t5 + PHASE6_FORT_DURATION;                        // 38.0s
    float t7 = t6 + PHASE7_FORT_ZOOM_DURATION;                    // 42.0s

    if (elapsedTime < t0)
    {
        // 0s to 4s: AstroMediComp
        g_zoomScale = 1.0f;
    }
    else if (elapsedTime < t1)
    {
        // 4s to 8s: Display Shader
        g_zoomScale = 1.0f;
    }
    else if (elapsedTime < t2)
    {
        // 8s to 12s: Call for Freedom
        g_zoomScale = 1.0f;
    }
    else if (elapsedTime < t3)
    {
        // 12s to 18s: Bhagat Singh, Rajguru, Sukhdev (BRS)
        g_zoomScale = 1.0f;
    }
    else if (elapsedTime < t4)
    {
        // 18s to 24s: Dandi March Scene
        g_zoomScale = 1.0f;
    }
    else if (elapsedTime < t5)
    {
        // 24s to 28s: Zoom out to reveal Lalkila
        float progress = (elapsedTime - t4) / PHASE5_ZOOM_OUT_DURATION;
        g_zoomScale = powf(TARGET_SCALE, 1.0f - progress);
    }
    else if (elapsedTime < t6)
    {
        // 28s to 38s: Lalkila Normal Screen
        g_zoomScale = 1.0f;
        update(0);
    }
    else if (elapsedTime <= t7)
    {
        // 38s to 42s: Zoom In transition
        float progress = (elapsedTime - t6) / PHASE7_FORT_ZOOM_DURATION;
        g_zoomScale = powf(TARGET_SCALE, progress);
    }
    else
    {
        g_zoomScale = 1.0f;
    }
	*/

   // glutPostRedisplay();
   // glutTimerFunc(16, fortTimer, 0);
	InvalidateRect(ghwnd, NULL, FALSE);

}

void displayLalkila(void)
{
	// RED FORT (Shifted UP and scaled to fit)
	glPushMatrix();
	//glTranslatef(0.0f, 0.22f, 0.0f); // Move Fort UP
	//glScalef(0.82f, 0.82f, 1.0f);     // Scale to fit minarets within window

	glTranslatef(0.0f, 0.06f, 0.0f);   // move a bit down/up as needed
	glScalef(1.12f, 1.12f, 1.0f);      // enlarge the fort

	// MAIN WALL - full width orange base
	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f(-1.00f, -0.85f, 0.0f);
		glVertex3f( 1.00f, -0.85f, 0.0f);
		glVertex3f( 1.00f, -0.10f, 0.0f);
		glVertex3f(-1.00f, -0.10f, 0.0f);
	glEnd();

	// WALL - left light panel
	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f(-1.00f, -0.85f, 0.0f);
		glVertex3f(-0.82f, -0.85f, 0.0f);
		glVertex3f(-0.82f, 0.03f, 0.0f);
		glVertex3f(-1.00f, 0.03f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.55f, 0.28f);
		glVertex3f(-0.82f, -0.85f, 0.0f);
		glVertex3f(-0.64f, -0.85f, 0.0f);
		glVertex3f(-0.64f, 0.03f, 0.0f);
		glVertex3f(-0.82f, 0.03f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f(-0.64f, -0.85f, 0.0f);
		glVertex3f(-0.46f, -0.85f, 0.0f);
		glVertex3f(-0.46f, 0.03f, 0.0f);
		glVertex3f(-0.64f, 0.03f, 0.0f);
	glEnd();

	// WALL - right light panel
	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f(0.82f, -0.85f, 0.0f);
		glVertex3f(1.00f, -0.85f, 0.0f);
		glVertex3f(1.00f, 0.03f, 0.0f);
		glVertex3f(0.82f, 0.03f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.55f, 0.28f);
		glVertex3f(0.64f, -0.85f, 0.0f);
		glVertex3f(0.82f, -0.85f, 0.0f);
		glVertex3f(0.82f, 0.03f, 0.0f);
		glVertex3f(0.64f, 0.03f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f(0.46f, -0.85f, 0.0f);
		glVertex3f(0.64f, -0.85f, 0.0f);
		glVertex3f(0.64f, 0.03f, 0.0f);
		glVertex3f(0.46f, 0.03f, 0.0f);
	glEnd();

	// WALL - centre darker block
	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f(-0.42f, -0.85f, 0.0f);
		glVertex3f( 0.42f, -0.85f, 0.0f);
		glVertex3f( 0.42f, -0.10f, 0.0f);
		glVertex3f(-0.42f, -0.10f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f(-0.46f, -0.85f, 0.0f);
		glVertex3f(-0.16f, -0.85f, 0.0f);
		glVertex3f(-0.16f, -0.10f, 0.0f);
		glVertex3f(-0.46f, -0.10f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.55f, 0.28f);
		glVertex3f(-0.16f, -0.85f, 0.0f);
		glVertex3f(0.16f, -0.85f, 0.0f);
		glVertex3f(0.16f, -0.10f, 0.0f);
		glVertex3f(-0.16f, -0.10f, 0.0f);
	glEnd();

	// DARK HORIZONTAL TRIM BANDS
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-1.00f, -0.87f, 0.0f);
		glVertex3f(-0.46f, -0.87f, 0.0f);
		glVertex3f(-0.46f, -0.84f, 0.0f);
		glVertex3f(-1.00f, -0.84f, 0.0f);
	glEnd();
		
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(0.46f, -0.87f, 0.0f);
		glVertex3f(1.00f, -0.87f, 0.0f);
		glVertex3f(1.00f, -0.84f, 0.0f);
		glVertex3f(0.46f, -0.84f, 0.0f);
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.46f, -0.10f, 0.0f);
		glVertex3f( 0.46f, -0.10f, 0.0f);
		glVertex3f( 0.46f, -0.07f, 0.0f);
		glVertex3f(-0.46f, -0.07f, 0.0f);
	glEnd();
     
	glBegin(GL_QUADS);
		glColor3f(0.50f, 0.18f, 0.07f);
		glVertex3f(-0.46f, -0.74f, 0.0f);
		glVertex3f( 0.46f, -0.74f, 0.0f);
		glVertex3f( 0.46f, -0.68f, 0.0f);
		glVertex3f(-0.46f, -0.68f, 0.0f);
	glEnd();

	// SMALL ARCHES - left wall block
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.96f, -0.48f, 0.0f);
		glVertex3f(-0.86f, -0.48f, 0.0f);
		glVertex3f(-0.86f, -0.35f, 0.0f);
		glVertex3f(-0.96f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.96f, -0.35f, 0.0f);
		glVertex3f(-0.86f, -0.35f, 0.0f);
		glVertex3f(-0.91f, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.78f, -0.48f, 0.0f);
		glVertex3f(-0.68f, -0.48f, 0.0f);
		glVertex3f(-0.68f, -0.35f, 0.0f);
		glVertex3f(-0.78f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.78f, -0.35f, 0.0f);
		glVertex3f(-0.68f, -0.35f, 0.0f);
		glVertex3f(-0.73f, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.60f, -0.48f, 0.0f);
		glVertex3f(-0.50f, -0.48f, 0.0f);
		glVertex3f(-0.50f, -0.35f, 0.0f);
		glVertex3f(-0.60f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.60f, -0.35f, 0.0f);
		glVertex3f(-0.50f, -0.35f, 0.0f);
		glVertex3f(-0.55f, -0.25f, 0.0f);
	glEnd();

	// SMALL ARCHES - right wall block
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.86f, -0.48f, 0.0f);
		glVertex3f( 0.96f, -0.48f, 0.0f);
		glVertex3f( 0.96f, -0.35f, 0.0f);
		glVertex3f( 0.86f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.86f, -0.35f, 0.0f);
		glVertex3f( 0.96f, -0.35f, 0.0f);
		glVertex3f( 0.91f, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.68f, -0.48f, 0.0f);
		glVertex3f( 0.78f, -0.48f, 0.0f);
		glVertex3f( 0.78f, -0.35f, 0.0f);
		glVertex3f( 0.68f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.68f, -0.35f, 0.0f);
		glVertex3f( 0.78f, -0.35f, 0.0f);
		glVertex3f( 0.73f, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.50f, -0.48f, 0.0f);
		glVertex3f( 0.60f, -0.48f, 0.0f);
		glVertex3f( 0.60f, -0.35f, 0.0f);
		glVertex3f( 0.50f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.50f, -0.35f, 0.0f);
		glVertex3f( 0.60f, -0.35f, 0.0f);
		glVertex3f( 0.55f, -0.25f, 0.0f);
	glEnd();

	// LARGE ARCHES - centre block
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.40f, -0.65f, 0.0f);
		glVertex3f(-0.22f, -0.65f, 0.0f);
		glVertex3f(-0.22f, -0.30f, 0.0f);
		glVertex3f(-0.40f, -0.30f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.40f, -0.30f, 0.0f);
		glVertex3f(-0.22f, -0.30f, 0.0f);
		glVertex3f(-0.31f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.10f, -0.65f, 0.0f);
		glVertex3f( 0.10f, -0.65f, 0.0f);
		glVertex3f( 0.10f, -0.30f, 0.0f);
		glVertex3f(-0.10f, -0.30f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.10f, -0.30f, 0.0f);
		glVertex3f( 0.10f, -0.30f, 0.0f);
		glVertex3f( 0.00f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.22f, -0.65f, 0.0f);
		glVertex3f( 0.40f, -0.65f, 0.0f);
		glVertex3f( 0.40f, -0.30f, 0.0f);
		glVertex3f( 0.22f, -0.30f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.22f, -0.30f, 0.0f);
		glVertex3f( 0.40f, -0.30f, 0.0f);
		glVertex3f( 0.31f, -0.13f, 0.0f);
	glEnd();

	// CENTRAL PAVILION BACK WALL
	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f(-0.36f, -0.07f, 0.0f);
		glVertex3f( 0.36f, -0.07f, 0.0f);
		glVertex3f( 0.36f,  0.22f, 0.0f);
		glVertex3f(-0.36f,  0.22f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.36f,  0.20f, 0.0f);
		glVertex3f( 0.36f,  0.20f, 0.0f);
		glVertex3f( 0.36f,  0.22f, 0.0f);
		glVertex3f(-0.36f,  0.22f, 0.0f);
	glEnd();

	// CENTRAL PAVILION - 7 white arches
	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.33f, -0.07f, 0.0f);
		glVertex3f(-0.24f, -0.07f, 0.0f);
		glVertex3f(-0.24f,  0.12f, 0.0f);
		glVertex3f(-0.33f,  0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.33f,  0.12f, 0.0f);
		glVertex3f(-0.24f,  0.12f, 0.0f);
		glVertex3f(-0.285f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.22f, -0.07f, 0.0f);
		glVertex3f(-0.13f, -0.07f, 0.0f);
		glVertex3f(-0.13f,  0.12f, 0.0f);
		glVertex3f(-0.22f,  0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.22f,  0.12f, 0.0f);
		glVertex3f(-0.13f,  0.12f, 0.0f);
		glVertex3f(-0.180f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.11f, -0.07f, 0.0f);
		glVertex3f(-0.02f, -0.07f, 0.0f);
		glVertex3f(-0.02f,  0.12f, 0.0f);
		glVertex3f(-0.11f,  0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.11f,  0.12f, 0.0f);
		glVertex3f(-0.02f,  0.12f, 0.0f);
		glVertex3f(-0.070f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.02f, -0.07f, 0.0f);
		glVertex3f( 0.11f, -0.07f, 0.0f);
		glVertex3f( 0.11f,  0.12f, 0.0f);
		glVertex3f( 0.02f,  0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.02f,  0.12f, 0.0f);
		glVertex3f( 0.11f,  0.12f, 0.0f);
		glVertex3f( 0.065f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.13f, -0.07f, 0.0f);
		glVertex3f( 0.22f, -0.07f, 0.0f);
		glVertex3f( 0.22f,  0.12f, 0.0f);
		glVertex3f( 0.13f,  0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.13f,  0.12f, 0.0f);
		glVertex3f( 0.22f,  0.12f, 0.0f);
		glVertex3f( 0.175f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.24f, -0.07f, 0.0f);
		glVertex3f( 0.33f, -0.07f, 0.0f);
		glVertex3f( 0.33f,  0.12f, 0.0f);
		glVertex3f( 0.24f,  0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.24f,  0.12f, 0.0f);
		glVertex3f( 0.33f,  0.12f, 0.0f);
		glVertex3f( 0.285f, 0.20f, 0.0f);
	glEnd();

	// CENTRAL PAVILION - 6 small chattri domes
	{
		int i;
		float cx[6] = { -0.31f, -0.19f, -0.08f, 0.08f, 0.19f, 0.31f };

		for (i = 0; i < 6; i++)
		{
			glBegin(GL_QUADS);
				glColor3f(0.99f, 0.95f, 0.90f);
				glVertex3f(cx[i] - 0.03f, 0.22f, 0.0f);
				glVertex3f(cx[i] + 0.03f, 0.22f, 0.0f);
				glVertex3f(cx[i] + 0.03f, 0.30f, 0.0f);
				glVertex3f(cx[i] - 0.03f, 0.30f, 0.0f);
			glEnd();

			glBegin(GL_TRIANGLES);
				glColor3f(0.98f, 0.78f, 0.58f);
				glVertex3f(cx[i] - 0.05f, 0.30f, 0.0f);
				glVertex3f(cx[i] + 0.05f, 0.30f, 0.0f);
				glVertex3f(cx[i],          0.42f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
				glColor3f(0.62f, 0.22f, 0.08f);
				glVertex3f(cx[i] - 0.05f, 0.28f, 0.0f);
				glVertex3f(cx[i] + 0.05f, 0.28f, 0.0f);
				glVertex3f(cx[i] + 0.05f, 0.30f, 0.0f);
				glVertex3f(cx[i] - 0.05f, 0.30f, 0.0f);
			glEnd();
		}
	}

	// MINARETS & TOWER SHAFTS
	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.55f, 0.28f);
		glVertex3f(-0.44f, -0.10f, 0.0f);
		glVertex3f(-0.38f, -0.10f, 0.0f);
		glVertex3f(-0.38f,  0.72f, 0.0f);
		glVertex3f(-0.44f,  0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f(-0.42f, -0.10f, 0.0f);
		glVertex3f(-0.40f, -0.10f, 0.0f);
		glVertex3f(-0.40f,  0.72f, 0.0f);
		glVertex3f(-0.42f,  0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.55f, 0.28f);
		glVertex3f( 0.38f, -0.10f, 0.0f);
		glVertex3f( 0.44f, -0.10f, 0.0f);
		glVertex3f( 0.44f,  0.72f, 0.0f);
		glVertex3f( 0.38f,  0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f( 0.40f, -0.10f, 0.0f);
		glVertex3f( 0.42f, -0.10f, 0.0f);
		glVertex3f( 0.42f,  0.72f, 0.0f);
		glVertex3f( 0.40f,  0.72f, 0.0f);
	glEnd();

	// LEFT MINARET CHATTRI
	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.95f, 0.90f);
		glVertex3f(-0.47f, 0.72f, 0.0f);
		glVertex3f(-0.35f, 0.72f, 0.0f);
		glVertex3f(-0.35f, 0.82f, 0.0f);
		glVertex3f(-0.47f, 0.82f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.98f, 0.78f, 0.58f);
		glVertex3f(-0.50f, 0.82f, 0.0f);
		glVertex3f(-0.32f, 0.82f, 0.0f);
		glVertex3f(-0.41f, 0.98f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.50f, 0.80f, 0.0f);
		glVertex3f(-0.32f, 0.80f, 0.0f);
		glVertex3f(-0.32f, 0.82f, 0.0f);
		glVertex3f(-0.50f, 0.82f, 0.0f);
	glEnd();

	// RIGHT MINARET CHATTRI
	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.95f, 0.90f);
		glVertex3f( 0.35f, 0.72f, 0.0f);
		glVertex3f( 0.47f, 0.72f, 0.0f);
		glVertex3f( 0.47f, 0.82f, 0.0f);
		glVertex3f( 0.35f, 0.82f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.98f, 0.78f, 0.58f);
		glVertex3f( 0.32f, 0.82f, 0.0f);
		glVertex3f( 0.50f, 0.82f, 0.0f);
		glVertex3f( 0.41f, 0.98f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.32f, 0.80f, 0.0f);
		glVertex3f( 0.50f, 0.80f, 0.0f);
		glVertex3f( 0.50f, 0.82f, 0.0f);
		glVertex3f( 0.32f, 0.82f, 0.0f);
	glEnd();

	// LEFT CORNER PAVILION
	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f(-0.98f, 0.03f, 0.0f);
		glVertex3f(-0.48f, 0.03f, 0.0f);
		glVertex3f(-0.48f,  0.42f, 0.0f);
		glVertex3f(-0.98f,  0.42f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.95f, 0.05f, 0.0f);
		glVertex3f(-0.82f, 0.05f, 0.0f);
		glVertex3f(-0.82f,  0.27f, 0.0f);
		glVertex3f(-0.95f,  0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.95f,  0.27f, 0.0f);
		glVertex3f(-0.82f,  0.27f, 0.0f);
		glVertex3f(-0.885f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.80f, 0.05f, 0.0f);
		glVertex3f(-0.67f, 0.05f, 0.0f);
		glVertex3f(-0.67f,  0.27f, 0.0f);
		glVertex3f(-0.80f,  0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.80f,  0.27f, 0.0f);
		glVertex3f(-0.67f,  0.27f, 0.0f);
		glVertex3f(-0.735f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.65f, 0.05f, 0.0f);
		glVertex3f(-0.52f, 0.05f, 0.0f);
		glVertex3f(-0.52f,  0.27f, 0.0f);
		glVertex3f(-0.65f,  0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f(-0.65f,  0.27f, 0.0f);
		glVertex3f(-0.52f,  0.27f, 0.0f);
		glVertex3f(-0.585f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f(-0.98f,  0.40f, 0.0f);
		glVertex3f(-0.48f,  0.40f, 0.0f);
		glVertex3f(-0.48f,  0.42f, 0.0f);
		glVertex3f(-0.98f,  0.42f, 0.0f);
	glEnd();
	
	// RIGHT CORNER PAVILION
	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f( 0.48f, 0.03f, 0.0f);
		glVertex3f( 0.98f, 0.03f, 0.0f);
		glVertex3f( 0.98f,  0.42f, 0.0f);
		glVertex3f( 0.48f,  0.42f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.52f, 0.05f, 0.0f);
		glVertex3f( 0.65f, 0.05f, 0.0f);
		glVertex3f( 0.65f,  0.27f, 0.0f);
		glVertex3f( 0.52f,  0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.52f,  0.27f, 0.0f);
		glVertex3f( 0.65f,  0.27f, 0.0f);
		glVertex3f( 0.585f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.67f, 0.05f, 0.0f);
		glVertex3f( 0.80f, 0.05f, 0.0f);
		glVertex3f( 0.80f,  0.27f, 0.0f);
		glVertex3f( 0.67f,  0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.67f,  0.27f, 0.0f);
		glVertex3f( 0.80f,  0.27f, 0.0f);
		glVertex3f( 0.735f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.82f, 0.05f, 0.0f);
		glVertex3f( 0.95f, 0.05f, 0.0f);
		glVertex3f( 0.95f,  0.27f, 0.0f);
		glVertex3f( 0.82f,  0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(0.99f, 0.97f, 0.95f);
		glVertex3f( 0.82f,  0.27f, 0.0f);
		glVertex3f( 0.95f,  0.27f, 0.0f);
		glVertex3f( 0.885f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.62f, 0.22f, 0.08f);
		glVertex3f( 0.48f,  0.40f, 0.0f);
		glVertex3f( 0.98f,  0.40f, 0.0f);
		glVertex3f( 0.98f,  0.42f, 0.0f);
		glVertex3f( 0.48f,  0.42f, 0.0f);
	glEnd();

	/*
		// CENTRAL STAIRS FROM FORT TO LOWER AREA
	// top step just below center gate, then widening downward

	glBegin(GL_QUADS);

		// Step 1
		glColor3f(0.82f, 0.38f, 0.14f);
		glVertex3f(-0.12f, -0.85f, 0.0f);
		glVertex3f( 0.12f, -0.85f, 0.0f);
		glVertex3f( 0.10f, -0.92f, 0.0f);
		glVertex3f(-0.10f, -0.92f, 0.0f);

		// Step 2
		glColor3f(0.86f, 0.42f, 0.16f);
		glVertex3f(-0.16f, -0.92f, 0.0f);
		glVertex3f( 0.16f, -0.92f, 0.0f);
		glVertex3f( 0.14f, -0.99f, 0.0f);
		glVertex3f(-0.14f, -0.99f, 0.0f);

		// Step 3
		glColor3f(0.82f, 0.38f, 0.14f);
		glVertex3f(-0.20f, -0.99f, 0.0f);
		glVertex3f( 0.20f, -0.99f, 0.0f);
		glVertex3f( 0.18f, -1.06f, 0.0f);
		glVertex3f(-0.18f, -1.06f, 0.0f);

		// Step 4
		glColor3f(0.86f, 0.42f, 0.16f);
		glVertex3f(-0.24f, -1.06f, 0.0f);
		glVertex3f( 0.24f, -1.06f, 0.0f);
		glVertex3f( 0.22f, -1.13f, 0.0f);
		glVertex3f(-0.22f, -1.13f, 0.0f);

		// Step 5
		glColor3f(0.82f, 0.38f, 0.14f);
		glVertex3f(-0.28f, -1.13f, 0.0f);
		glVertex3f( 0.28f, -1.13f, 0.0f);
		glVertex3f( 0.26f, -1.20f, 0.0f);
		glVertex3f(-0.26f, -1.20f, 0.0f);

	glEnd();
*/

		// =========================================================
	// GROUND PLAIN - full width sandy base
	// =========================================================
	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.75f, 0.35f);
		glVertex3f(-1.60f, -1.40f, 0.0f);
		glVertex3f( 1.60f, -1.40f, 0.0f);
		glVertex3f( 1.60f, -0.85f, 0.0f);
		glVertex3f(-1.60f, -0.85f, 0.0f);
	glEnd();

	// =========================================================
	// LEFT SIDE PERIMETER WALL
	// gap of ~0.18 from fort left edge (-1.00)
	// wall sits at x = -1.18 to -1.60
	// =========================================================

	// Left wall - main body
	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);   // same fort orange
		glVertex3f(-1.60f, -0.85f, 0.0f);
		glVertex3f(-1.18f, -0.85f, 0.0f);
		glVertex3f(-1.18f,  0.25f, 0.0f);
		glVertex3f(-1.60f,  0.25f, 0.0f);
	glEnd();

	// Left wall - light accent strip (front face)
	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f(-1.60f, -0.85f, 0.0f);
		glVertex3f(-1.52f, -0.85f, 0.0f);
		glVertex3f(-1.52f,  0.25f, 0.0f);
		glVertex3f(-1.60f,  0.25f, 0.0f);
	glEnd();

	// Left wall - dark accent strip (inner face)
	glBegin(GL_QUADS);
		glColor3f(0.80f, 0.38f, 0.12f);
		glVertex3f(-1.18f, -0.85f, 0.0f);
		glVertex3f(-1.26f, -0.85f, 0.0f);
		glVertex3f(-1.26f,  0.25f, 0.0f);
		glVertex3f(-1.18f,  0.25f, 0.0f);
	glEnd();

	// Left wall - battlements top (5 merlons)
	{
		int m;
		for (m = 0; m < 5; m++)
		{
			float mx = -1.60f + (m * 0.085f);
			glBegin(GL_QUADS);
				glColor3f(0.88f, 0.44f, 0.18f);
				glVertex3f(mx,        0.25f, 0.0f);
				glVertex3f(mx+0.06f,  0.25f, 0.0f);
				glVertex3f(mx+0.06f,  0.35f, 0.0f);
				glVertex3f(mx,        0.35f, 0.0f);
			glEnd();
		}
	}

	// Left wall - 2 arched windows
	// window 1
	glBegin(GL_POLYGON);
		glColor3f(0.65f, 0.28f, 0.08f);
		glVertex3f(-1.56f, -0.60f, 0.0f);
		glVertex3f(-1.38f, -0.60f, 0.0f);
		glVertex3f(-1.38f, -0.30f, 0.0f);
		glVertex3f(-1.47f, -0.18f, 0.0f);
		glVertex3f(-1.56f, -0.30f, 0.0f);
	glEnd();

	// window 2
	glBegin(GL_POLYGON);
		glColor3f(0.65f, 0.28f, 0.08f);
		glVertex3f(-1.56f, -0.80f, 0.0f);
		glVertex3f(-1.38f, -0.80f, 0.0f);
		glVertex3f(-1.38f, -0.68f, 0.0f);
		glVertex3f(-1.47f, -0.62f, 0.0f);
		glVertex3f(-1.56f, -0.68f, 0.0f);
	glEnd();

	// =========================================================
	// SANDY PLAIN GAP - left (between left wall and fort)
	// =========================================================
	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.75f, 0.35f);
		glVertex3f(-1.18f, -1.40f, 0.0f);
		glVertex3f(-1.00f, -1.40f, 0.0f);
		glVertex3f(-1.00f, -0.85f, 0.0f);
		glVertex3f(-1.18f, -0.85f, 0.0f);
	glEnd();

	// =========================================================
	// RIGHT SIDE PERIMETER WALL
	// gap of ~0.18 from fort right edge (1.00)
	// wall sits at x = 1.18 to 1.60
	// =========================================================

	// Right wall - main body
	glBegin(GL_QUADS);
		glColor3f(0.88f, 0.44f, 0.18f);
		glVertex3f( 1.18f, -0.85f, 0.0f);
		glVertex3f( 1.60f, -0.85f, 0.0f);
		glVertex3f( 1.60f,  0.25f, 0.0f);
		glVertex3f( 1.18f,  0.25f, 0.0f);
	glEnd();

	// Right wall - light accent strip (front face)
	glBegin(GL_QUADS);
		glColor3f(0.98f, 0.66f, 0.42f);
		glVertex3f( 1.52f, -0.85f, 0.0f);
		glVertex3f( 1.60f, -0.85f, 0.0f);
		glVertex3f( 1.60f,  0.25f, 0.0f);
		glVertex3f( 1.52f,  0.25f, 0.0f);
	glEnd();

	// Right wall - dark accent strip (inner face)
	glBegin(GL_QUADS);
		glColor3f(0.80f, 0.38f, 0.12f);
		glVertex3f( 1.18f, -0.85f, 0.0f);
		glVertex3f( 1.26f, -0.85f, 0.0f);
		glVertex3f( 1.26f,  0.25f, 0.0f);
		glVertex3f( 1.18f,  0.25f, 0.0f);
	glEnd();

	// Right wall - battlements top (5 merlons)
	{
		int m;
		for (m = 0; m < 5; m++)
		{
			float mx = 1.18f + (m * 0.085f);
			glBegin(GL_QUADS);
				glColor3f(0.88f, 0.44f, 0.18f);
				glVertex3f(mx,        0.25f, 0.0f);
				glVertex3f(mx+0.06f,  0.25f, 0.0f);
				glVertex3f(mx+0.06f,  0.35f, 0.0f);
				glVertex3f(mx,        0.35f, 0.0f);
			glEnd();
		}
	}

	// Right wall - 2 arched windows
	// window 1
	glBegin(GL_POLYGON);
		glColor3f(0.65f, 0.28f, 0.08f);
		glVertex3f( 1.38f, -0.60f, 0.0f);
		glVertex3f( 1.56f, -0.60f, 0.0f);
		glVertex3f( 1.56f, -0.30f, 0.0f);
		glVertex3f( 1.47f, -0.18f, 0.0f);
		glVertex3f( 1.38f, -0.30f, 0.0f);
	glEnd();

	// window 2
	glBegin(GL_POLYGON);
		glColor3f(0.65f, 0.28f, 0.08f);
		glVertex3f( 1.38f, -0.80f, 0.0f);
		glVertex3f( 1.56f, -0.80f, 0.0f);
		glVertex3f( 1.56f, -0.68f, 0.0f);
		glVertex3f( 1.47f, -0.62f, 0.0f);
		glVertex3f( 1.38f, -0.68f, 0.0f);
	glEnd();

	// =========================================================
	// SANDY PLAIN GAP - right (between fort and right wall)
	// =========================================================
	glBegin(GL_QUADS);
		glColor3f(0.95f, 0.75f, 0.35f);
		glVertex3f( 1.00f, -1.40f, 0.0f);
		glVertex3f( 1.18f, -1.40f, 0.0f);
		glVertex3f( 1.18f, -0.85f, 0.0f);
		glVertex3f( 1.00f, -0.85f, 0.0f);
	glEnd();

	// =========================================================
	// LEFT SUPPORT WALL (below fort, left of stairs)
	// =========================================================
	glBegin(GL_QUADS);
		glColor3f(0.76f, 0.62f, 0.46f);
		glVertex3f(-1.00f, -1.22f, 0.0f);
		glVertex3f(-0.48f, -1.22f, 0.0f);
		glVertex3f(-0.48f, -0.85f, 0.0f);
		glVertex3f(-1.00f, -0.85f, 0.0f);
	glEnd();

	// LEFT WALL - brick horizontal lines
	{
		int j;
		for (j = 0; j < 6; j++)
		{
			float wallY = -0.85f - (j * 0.062f);
			glBegin(GL_LINES);
				glColor3f(0.55f, 0.42f, 0.28f);
				glVertex3f(-1.00f, wallY, 0.0f);
				glVertex3f(-0.48f, wallY, 0.0f);
			glEnd();
		}
	}

	// LEFT WALL - vertical brick dividers
	{
		int k;
		float divX;
		for (k = 0; k < 4; k++)
		{
			divX = -1.00f + (k * 0.135f);
			glBegin(GL_LINES);
				glColor3f(0.55f, 0.42f, 0.28f);
				glVertex3f(divX, -0.85f, 0.0f);
				glVertex3f(divX, -1.22f, 0.0f);
			glEnd();
		}
	}

	// =========================================================
	// RIGHT SUPPORT WALL (below fort, right of stairs)
	// =========================================================
	glBegin(GL_QUADS);
		glColor3f(0.76f, 0.62f, 0.46f);
		glVertex3f( 0.48f, -1.22f, 0.0f);
		glVertex3f( 1.00f, -1.22f, 0.0f);
		glVertex3f( 1.00f, -0.85f, 0.0f);
		glVertex3f( 0.48f, -0.85f, 0.0f);
	glEnd();

	// RIGHT WALL - brick horizontal lines
	{
		int j;
		for (j = 0; j < 6; j++)
		{
			float wallY = -0.85f - (j * 0.062f);
			glBegin(GL_LINES);
				glColor3f(0.55f, 0.42f, 0.28f);
				glVertex3f(0.48f, wallY, 0.0f);
				glVertex3f(1.00f, wallY, 0.0f);
			glEnd();
		}
	}

	// RIGHT WALL - vertical brick dividers
	{
		int k;
		float divX;
		for (k = 0; k < 4; k++)
		{
			divX = 0.48f + (k * 0.135f);
			glBegin(GL_LINES);
				glColor3f(0.55f, 0.42f, 0.28f);
				glVertex3f(divX, -0.85f, 0.0f);
				glVertex3f(divX, -1.22f, 0.0f);
			glEnd();
		}
	}

	// =========================================================
	// LEFT STAIR CHEEK WALL
	// =========================================================
	glBegin(GL_POLYGON);
		glColor3f(0.68f, 0.54f, 0.38f);
		glVertex3f(-0.48f, -1.22f, 0.0f);
		glVertex3f(-0.40f, -1.22f, 0.0f);
		glVertex3f(-0.34f, -1.10f, 0.0f);
		glVertex3f(-0.28f, -1.00f, 0.0f);
		glVertex3f(-0.24f, -0.92f, 0.0f);
		glVertex3f(-0.18f, -0.85f, 0.0f);
		glVertex3f(-0.22f, -0.85f, 0.0f);
		glVertex3f(-0.30f, -0.92f, 0.0f);
		glVertex3f(-0.36f, -1.00f, 0.0f);
		glVertex3f(-0.42f, -1.10f, 0.0f);
	glEnd();

	// =========================================================
	// RIGHT STAIR CHEEK WALL
	// =========================================================
	glBegin(GL_POLYGON);
		glColor3f(0.68f, 0.54f, 0.38f);
		glVertex3f( 0.48f, -1.22f, 0.0f);
		glVertex3f( 0.40f, -1.22f, 0.0f);
		glVertex3f( 0.34f, -1.10f, 0.0f);
		glVertex3f( 0.28f, -1.00f, 0.0f);
		glVertex3f( 0.24f, -0.92f, 0.0f);
		glVertex3f( 0.18f, -0.85f, 0.0f);
		glVertex3f( 0.22f, -0.85f, 0.0f);
		glVertex3f( 0.30f, -0.92f, 0.0f);
		glVertex3f( 0.36f, -1.00f, 0.0f);
		glVertex3f( 0.42f, -1.10f, 0.0f);
	glEnd();

	// =========================================================
	// TOP LANDING
	// =========================================================
	glBegin(GL_QUADS);
		glColor3f(0.80f, 0.66f, 0.48f);
		glVertex3f(-0.22f, -0.85f, 0.0f);
		glVertex3f( 0.22f, -0.85f, 0.0f);
		glVertex3f( 0.20f, -0.90f, 0.0f);
		glVertex3f(-0.20f, -0.90f, 0.0f);
	glEnd();

	// =========================================================
	// CENTER STAIRCASE - 10 thin widening steps
	// =========================================================
	{
		float topY   = -0.90f;
		float stepH  =  0.035f;
		float leftX  = -0.18f;
		float rightX =  0.18f;
		float expand =  0.014f;
		int i;

		for (i = 0; i < 10; i++)
		{
			float y1  = topY - (i * stepH);
			float y2  = y1 - stepH + 0.003f;
			float lx1 = leftX  - (i * expand);
			float rx1 = rightX + (i * expand);
			float lx2 = leftX  - ((i + 1) * expand);
			float rx2 = rightX + ((i + 1) * expand);

			glBegin(GL_QUADS);
				if (i % 2 == 0)
					glColor3f(0.88f, 0.72f, 0.52f);
				else
					glColor3f(0.80f, 0.65f, 0.46f);
				glVertex3f(lx1, y1, 0.0f);
				glVertex3f(rx1, y1, 0.0f);
				glVertex3f(rx2, y2, 0.0f);
				glVertex3f(lx2, y2, 0.0f);
			glEnd();

			glBegin(GL_LINES);
				glColor3f(0.48f, 0.34f, 0.20f);
				glVertex3f(lx1, y1, 0.0f);
				glVertex3f(rx1, y1, 0.0f);
			glEnd();
		}
	}

	glPopMatrix();
}
/*
void drawSkyBackground(float elapsedTime)
{
    float progress = 0.0f;
    
    // Smooth transition during flag unfolding (13.25s to 15.0s)
    /*
	//if (elapsedTime >= 28.25f)
    //{
    //    progress = (elapsedTime - 28.25f) / 1.75f;
   //     if (progress > 1.0f) progress = 1.0f;
   // }

    // Color transition: Dark Orange -> Sky Blue
    float r = 0.85f * (1.0f - progress) + 0.40f; //* progress;
    float g = 0.30f * (1.0f - progress) + 0.70f; //* progress;
    float b = 0.10f * (1.0f - progress) + 0.95f;// * progress;

    // Upper half background quad (Y: 0.0 to 1.0)
    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex2f(-1.0f, -0.3f);
        glVertex2f( 1.0f, -0.3f);
        glVertex2f( 1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();
}
*/

void showSirsBirthdayGift(void)
{
      //int currentTime = glutGet(GLUT_ELAPSED_TIME);
	DWORD currentTime = timeGetTime();
      // DWORD subtraction safely handles timer rollover.
    DWORD elapsedMilliseconds = currentTime - g_startTime;
    float elapsedTime = elapsedMilliseconds / 1000.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// mage ghyava lagel karan perspectivemode.
	glTranslatef(0.0f, 0.0f, -3.0f);

	if (elapsedTime < 20.0f)
    {
        // 0s to 4s: Shader screen
		coinFlip();

    }
	else if (elapsedTime < 24.0f)                  		
	{
		// 4s to 8s: coin flip
		happyBirthday();
	}
	else if (elapsedTime < 28.0f)
    {
        // 4s to 8s: Shader screen
        displayLalkila();
    }
	else if (elapsedTime < (28.0f + SCENE2_DURATION))
    {
        // 16.0s to 30.0s: Scene 2 - Royal Darbar & Chanakya Entry (Doors open, walks inside)
        renderScene2();
    }
	else if (elapsedTime < (28.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        // 30.0s to (30.0s + SCENE3_DURATION): Scene 3 - Royal Darbar Dialogue (King, Chanakya, Minister, Audio)
        renderScene3();
    }
	else if (elapsedTime < (32.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        stopScene3Audio(); // Ensure dialogue audio stops before next scene
        displayParnakuti();
    }
	else if (elapsedTime < (36.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        Map();
    }
	else if (elapsedTime < (40.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        sanskrit_lettering();
    }
	else if (elapsedTime < (44.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        DrawPortrait();
    }
	else if (elapsedTime < (48.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        MembersName();
    }
	else if (elapsedTime < (52.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        SpecialThanks();
    }
	else if (elapsedTime < (56.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        Shader();
    }
	else if (elapsedTime < (60.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        Title();
    }

	/*
	else if (elapsedTime <= 12.0f)
    {
        // 8s to 12s: Call for Freedom screen
        display_CallForFreedom();
    }
	else if (elapsedTime <= 18.0f)
    {
        // 12s to 18s: Render Dandi March full screen
        displayBRS();
    }
    else if (elapsedTime < 24.0f)
    {
        // 18s to 24s: Render Dandi March full screen
        displayDandiMarch();
    }
    else if (elapsedTime < 42.0f)
    {
        // 24s to 42s: Render Lalkila with center zoom transformation
        glPushMatrix();

            glTranslatef(0.07f, 0.68f, 0.0f);
            glScalef(g_zoomScale, g_zoomScale, 1.0f);
            glTranslatef(-0.07f, -0.68f, 0.0f);
			
			drawSkyBackground(elapsedTime); // Upper half background
            displayLalkila();
            drawCrowd();
			displayFlag();
			
        glPopMatrix();
    }
	*/
	else
	{
		//display_post_independence();
	}

    // Do double buffering
	// swap the buffers
	SwapBuffers(ghdc);
}

// Callback function
LRESULT CALLBACK WndProc(HWND hwnd,
						UINT iMsg,
						WPARAM wParam,
						LPARAM lParam)
{
	// function declarations
	void toggleFullscreen(void);
	void resize(int, int);
	void uninitialize(void);
	//code
	//case WM_DESTROY: he OGL.exe cha (GLUT) glutLeaveMainLoop();
	switch (iMsg)
	{
		//ekdach yeto, pahila yeto
	case WM_CREATE:
		//290826
		memset(&wpPrev, 0, sizeof(WINDOWPLACEMENT));
		wpPrev.length = sizeof(WINDOWPLACEMENT);
		break;
	case WM_SETFOCUS:
		bActiveWindow = TRUE; // window is active
		break;
	case WM_KILLFOCUS:
		bActiveWindow = FALSE; // window is not active
		break;
		//second yeto, resize la yeto
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			bEscapeKeyIsPressed = TRUE;
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'F':
		case 'f':
			// 290826
			if(bFullscreen == FALSE)
			{
				toggleFullscreen();
				bFullscreen = TRUE;
			}
			else
			{
				toggleFullscreen();
				bFullscreen = FALSE;
			}
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		uninitialize();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void update(void)
{
	static DWORD lastTime = 0;
    DWORD now = timeGetTime();
    if (lastTime == 0) lastTime = now;
    float dt = (now - lastTime) / 1000.0f;
    lastTime = now;
    if (dt > 0.05f) dt = 0.016f; // Clamp large frame time jumps
    float elapsedTime = (now - g_startTime) / 1000.0f;
    // 1. Only animate coin when CoinFlip is on screen (4s to 12s)
    if (elapsedTime >= 0.0f && elapsedTime < 20.0f)
    {
        UpdateCoinAnimation(0.010f); // 0.010f is the original designed physics delta
    }

    // 2. Animate Scene 2 when active (Doors opening, Chanakya walking cycle)
    if (elapsedTime >= 28.0f && elapsedTime < (28.0f + SCENE2_DURATION))
    {
        updateScene2();
    }

    // 3. Animate Scene 3 when active (King emotions, Minister mouth speech, camera director)
    if (elapsedTime >= (16.0f + SCENE2_DURATION) && elapsedTime < (16.0f + SCENE2_DURATION + SCENE3_DURATION))
    {
        updateScene3();
    }
}

void uninitialize(void)
{
	stopScene3Audio();
		//code
	// if exiting in fullscreen first restore and then proceed
	if (bFullscreen == TRUE)
	{
		toggleFullscreen();
		bFullscreen = FALSE;
	}

	if (texture_Quote_SM)
	{
		glDeleteTextures(1, &texture_Quote_SM);
		texture_Quote_SM = 0;
	}
	// first check the current context and if it is then unmake it
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// Delete the rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// release the Device Context
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// destroy window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "Program terminated successfully.\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
