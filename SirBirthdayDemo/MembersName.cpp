// Header Files 
#include <windows.h>
#include <stdio.h> //for file I/O
#include <stdlib.h> // for exit

//OpenGl Related Header files
#include <gl\GL.h>

//Link with OpenGl import library
#pragma comment(lib,"opengl32.lib")

/*

//Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//GLOBAL VARIABLE DECLARATIONS
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL bFullscreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;
FILE *gpFile = NULL;
BOOL bActiveWindow = FALSE;
BOOL bEscapeKeyIsPressed = FALSE;

//Entry-Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Function Declarations
	int initialize(void);
	void render(void);
	void update(void);
	void uninitialize(void);

	// Variable Declarations
	WNDCLASSEX wndclass;
	HWND hwnd = NULL;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR7_SHS");
	BOOL bDone = FALSE;

	// code
	// Create Log File
	gpFile = fopen("Log.txt", "w");
	if (gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log File Creation Failed"), TEXT("Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "SHS : Program Started Successfully\n");
	}

	// WNDCLASSEX iNITIALIZATION
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register Above WNDCLASS
	RegisterClassEx(&wndclass);

	//Centering
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Create The Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("My Frist RTR7 Program : Saeed Haroon Shaikh"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		ScreenWidth/2 - WIN_WIDTH/2,
		ScreenHeight/2 - WIN_HEIGHT/2,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//SET GLOBAL WINDOW HANDLE
	ghwnd = hwnd;

	int iResult = initialize();
	if (iResult != 0)
	{
		fprintf(gpFile, "SHS : WinMain() : initialize() Failed");
		DestroyWindow(hwnd);
		hwnd = NULL;
	}
	else
	{
		fprintf(gpFile, "SHS : WinMain() : initialize() Succeded");
	}
	// Show Window
	ShowWindow(hwnd, iCmdShow);

	//Update The Window To Point Its Background
	UpdateWindow(hwnd);

	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Game Loop
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (bActiveWindow == TRUE)
			{
				if (bEscapeKeyIsPressed == TRUE)
					bDone = TRUE;
				//Render
				render();
				//Update
				update();
			}
		}
	}

	//uninitialize
	uninitialize();

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//FUNCTION DECLARATIONS
	void resize(int, int);
	void toggleFullScreen(void);
	void uninitialize(void);

	// Code
	switch (iMsg)
	{
	case WM_CREATE:
		memset(&wpPrev, 0, sizeof(WINDOWPLACEMENT));
		wpPrev.length = sizeof(WINDOWPLACEMENT);
			break;
		case WM_SETFOCUS:
			bActiveWindow = TRUE;
			break;
		case WM_KILLFOCUS:
			bActiveWindow = FALSE;
			break;
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
			if (bFullscreen == FALSE)
			{
				toggleFullScreen();
				bFullscreen = TRUE;
			}
			else
			{
				toggleFullScreen();
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
		PostQuitMessage(100);
		break;

	default:
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullScreen(void)
{
	//Variable Declarations
	MONITORINFO mi;

	//CODE
	if (bFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			memset(&mi, 0, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}

		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	
}

int initialize(void)
{
	//Function Declarations
	void resize(int, int);
	void printGLInfo(void);

	//Variable Declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1; //Conventional
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |	PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		return -1;
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd); //Index is 1 based not 0 based

	if (iPixelFormatIndex == 0)
		return -2;

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
		return -3;

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
		return -4;

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
		return -5;

	//print Opengl Info
	printGLInfo();

	//Choose Screen clearing color as blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Warmup resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void printGLInfo(void)
{
	//Code
	fprintf(gpFile, "OpenGL Vendor : %s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL	Version : %s\n", glGetString(GL_VERSION));
}

void resize(int width, int height)
{
	//code
	if (height <= 0)
		height = 1;

	glViewport(0, 0, width, height);
	(GLsizei)width, (GLsizei)height;

}
*/

void MembersName(void)
{
	//code
	// glClear(GL_COLOR_BUFFER_BIT);

	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();

	glPushMatrix();
	glTranslatef(-0.0f, 0.15f, 0.0f);
	glScalef(1.1f, 1.0f, 0.0f);
	{

			glPushMatrix();
			glTranslatef(-0.85f, 1.0f, 0.0f);
			glScalef(0.9f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.46f, -0.15f, 0.0f);
			glVertex3f(0.47f, -0.19f, 0.0f);
			glVertex3f(0.78f, -0.19f, 0.0f);
			glVertex3f(0.77f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.53f, -0.19f, 0.0f);
			glVertex3f(0.56f, -0.19f, 0.0f);
			glVertex3f(0.57f, -0.28f, 0.0f);
			glVertex3f(0.54f, -0.28f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.57f, -0.28f, 0.0f);
			glVertex3f(0.54f, -0.28f, 0.0f);
			glVertex3f(0.51f, -0.285f, 0.0f);
			glVertex3f(0.55f, -0.33f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.6f, -0.19f, 0.0f);
			glVertex3f(0.6f, -0.39f, 0.0f);
			glVertex3f(0.62f, -0.39f, 0.0f);
			glVertex3f(0.62f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.6f, -0.32f, 0.0f);
			glVertex3f(0.6f, -0.35f, 0.0f);
			glVertex3f(0.55f, -0.38f, 0.0f);
			glVertex3f(0.53f, -0.36f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.185f, 0.725f, 0.0f);
			glScalef(0.9f, 1.0f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.14f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.08f, 0.0f);
			glVertex3f(-0.12f, -0.07f, 0.0f);
			glVertex3f(-0.1f, -0.09f, 0.0f);
			glVertex3f(-0.11f, -0.1f, 0.0f);
			glVertex3f(-0.12f, -0.11f, 0.0f);
			glVertex3f(-0.12f, -0.09f, 0.0f);
			glVertex3f(-0.14f, -0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.09f, 0.0f);
			glVertex3f(-0.13f, -0.11f, 0.0f);
			glVertex3f(-0.14f, -0.13f, 0.0f);
			glVertex3f(-0.11f, -0.13f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.14f, -0.13f, 0.0f);
			glVertex3f(-0.11f, -0.13f, 0.0f);
			glVertex3f(-0.18f, -0.09f, 0.0f);
			glVertex3f(-0.2f, -0.1f, 0.0f);
			glEnd();

			glPopMatrix();

			//p letter ///////////////////////////////
			glPushMatrix();
			glTranslatef(-0.2f, 0.8f, 0.0f);
			glScalef(0.4f, 0.5f, 1.0f);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.1f, 0.1f, 0.0f);
			glVertex3f(-0.15f, 0.1f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(-0.07f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.4f, 0.0f);
			glVertex3f(0.05f, -0.4f, 0.0f);
			glVertex3f(0.05f, 0.1f, 0.0f);
			glVertex3f(0.0f, 0.1f, 0.0f);
			glEnd();

			glPopMatrix();


			glPushMatrix();
			glTranslatef(-0.16f, 1.06f, 0.0f);
			glScalef(1.0f, 1.1f, 0.0f);

			//m
			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.18f, -0.19f, 0.0f);
			glVertex3f(0.18f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.15f, -0.18f, 0.0f);
			glVertex3f(0.16f, -0.21f, 0.0f);
			glVertex3f(0.62f, -0.21f, 0.0f);
			glVertex3f(0.61f, -0.18f, 0.0f);
			glEnd();

			glPopMatrix();

			//continue m
			glPushMatrix();
			glTranslatef(0.05f, 0.7f, 0.0f);
			glScalef(1.0f, 1.0f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.05f, 0.02f, 0.0f);
			glVertex3f(-0.07f, 0.02f, 0.0f);
			glVertex3f(-0.08f, 0.01f, 0.0f);
			glVertex3f(-0.08f, -0.01f, 0.0f);
			glVertex3f(-0.03f, -0.05f, 0.0f);
			glVertex3f(-0.02f, -0.05f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(0.03f, -0.01f, 0.0f);
			glVertex3f(0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.03f, 0.15f, 0.0f);
			glVertex3f(0.03f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.12f, 0.0f);
			glVertex3f(0.05f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();

			//vi

			glPushMatrix();
			glTranslatef(0.18f, 1.1f, 0.0f);
			glScalef(1.1f, 1.3f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.19f, 0.0f);
			glVertex3f(0.0f, -0.38f, 0.0f);
			glVertex3f(0.02f, -0.39f, 0.0f);
			glVertex3f(0.02f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.01f, -0.26f, 0.0f);
			glVertex3f(0.0f, -0.24f, 0.0f);
			glVertex3f(-0.02f, -0.23f, 0.0f);
			glVertex3f(-0.02f, -0.26f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.02f, -0.23f, 0.0f);
			glVertex3f(-0.02f, -0.26f, 0.0f);
			glVertex3f(-0.03f, -0.28f, 0.0f);
			glVertex3f(-0.05f, -0.28f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.02f, -0.24f, 0.0f);
			glVertex3f(-0.03f, -0.25f, 0.0f);
			glVertex3f(-0.01f, -0.31f, 0.0f);
			glVertex3f(0.0f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.03f, -0.28f, 0.0f);
			glVertex3f(-0.05f, -0.28f, 0.0f);
			glVertex3f(-0.05f, -0.31f, 0.0f);
			glVertex3f(-0.03f, -0.29f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.05f, -0.31f, 0.0f);
			glVertex3f(-0.03f, -0.29f, 0.0f);
			glVertex3f(-0.02f, -0.32f, 0.0f);
			glVertex3f(-0.02f, -0.34f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.02f, -0.32f, 0.0f);
			glVertex3f(-0.02f, -0.34f, 0.0f);
			glVertex3f(0.0f, -0.31f, 0.0f);
			glVertex3f(0.01f, -0.28f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.07f, 1.08f, 0.0f);
			glScalef(0.8f, 1.3f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.19f, 0.0f);
			glVertex3f(0.28f, -0.19f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.25f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.23f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.23f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.25f, -0.28f, 0.0f);
			glVertex3f(0.28f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.27f, 0.0f);
			glVertex3f(0.24f, -0.3f, 0.0f);
			glVertex3f(0.35f, -0.3f, 0.0f);
			glVertex3f(0.35f, -0.27f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.35f, -0.17f, 0.0f);
			glVertex3f(0.35f, -0.35f, 0.0f);
			glVertex3f(0.38f, -0.36f, 0.0f);
			glVertex3f(0.38f, -0.17f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, -0.09f, 0.0f);
			glVertex3f(-0.01f, -0.12f, 0.0f);
			glVertex3f(0.01f, -0.19f, 0.0f);
			glVertex3f(0.03f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.03f, -0.08f, 0.0f);
			glVertex3f(-0.03f, -0.115f, 0.0f);
			glVertex3f(-0.01f, -0.12f, 0.0f);
			glVertex3f(-0.01f, -0.09f, 0.0f);
			glEnd();

			glPointSize(9.0f);
			glBegin(GL_POINTS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.04f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.35f, -0.17f, 0.0f);
			glVertex3f(0.38f, -0.17f, 0.0f);
			glVertex3f(0.4f, -0.12f, 0.0f);
			glVertex3f(0.4f, -0.09f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.4f, -0.12f, 0.0f);
			glVertex3f(0.4f, -0.09f, 0.0f);
			glVertex3f(0.45f, -0.1f, 0.0f);
			glVertex3f(0.45f, -0.12f, 0.0f);
			glEnd();

			glPopMatrix();
	}
	glPopMatrix();

	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();

	glPushMatrix();
	glTranslatef(0.07f, 0.08f, 0.0f);
	glScalef(0.8f, 0.5f, 0.0f);
	{
		glLineWidth(5.0f);

		glBegin(GL_LINES);

		glColor3f(1.0f, 1.0f, 1.0f); // red line
		glVertex3f(-0.75f, 0.8f, -3.0f);
		glVertex3f(-0.68f, 0.7f, -3.0f);

		glVertex3f(-0.75f, 0.7f, -3.0f);
		glVertex3f(-0.65f, 0.7f, -3.0f);

		glVertex3f(-0.75f, 0.7f, -3.0f);
		glVertex3f(-0.7f, 0.6f, -3.0f);

		glVertex3f(-0.65f, 0.8f, -3.0f);
		glVertex3f(-0.65f, 0.6f, -3.0f);
		glEnd();

		// स ई द.... ///
		glLineWidth(5.0f);

		glBegin(GL_LINES);

		glVertex3f(-0.50f, 0.88f, -3.0f);
		glVertex3f(-0.55f, 0.88f, -3.0f);

		glVertex3f(-0.55f, 0.88f, -3.0f);
		glVertex3f(-0.55f, 0.80f, -3.0f);

		glVertex3f(-0.53f, 0.80f, -3.0f);
		glVertex3f(-0.53f, 0.78f, -3.0f);

		glVertex3f(-0.53f, 0.78f, -3.0f);
		glVertex3f(-0.60f, 0.78f, -3.0f);

		glVertex3f(-0.60f, 0.78f, -3.0f);
		glVertex3f(-0.60f, 0.70f, -3.0f);

		glVertex3f(-0.60f, 0.70f, -3.0f);
		glVertex3f(-0.52f, 0.70f, -3.0f);

		glVertex3f(-0.52f, 0.70f, -3.0f);
		glVertex3f(-0.52f, 0.62f, -3.0f);

		glVertex3f(-0.52f, 0.62f, -3.0f);
		glVertex3f(-0.59f, 0.62f, -3.0f);

		glVertex3f(-0.59f, 0.63f, -3.0f);
		glVertex3f(-0.55f, 0.58f, -3.0f);

		glVertex3f(-0.40f, 0.80f, -3.0f);
		glVertex3f(-0.40f, 0.78f, -3.0f);

		glVertex3f(-0.40f, 0.78f, -3.0f);
		glVertex3f(-0.47f, 0.78f, -3.0f);

		glVertex3f(-0.47f, 0.78f, -3.0f);
		glVertex3f(-0.47f, 0.65f, -3.0f);

		glVertex3f(-0.47f, 0.65f, -3.0f);
		glVertex3f(-0.40f, 0.65f, -3.0f);

		glVertex3f(-0.40f, 0.65f, -3.0f);
		glVertex3f(-0.38f, 0.60f, -3.0f);

		glVertex3f(-0.80f, 0.81f, -3.0f);
		glVertex3f(-0.35f, 0.81f, -3.0f);

		glEnd();

		// रोहन..... ////
		glLineWidth(5.0f);

		glBegin(GL_LINES);

		glVertex3f(-0.75f, 0.60f, -3.0f);
		glVertex3f(-0.65f, 0.50f, -3.0f);

		glVertex3f(-0.65f, 0.50f, -3.0f);
		glVertex3f(-0.65f, 0.30f, -3.0f);

		glVertex3f(-0.75f, 0.50f, -3.0f);
		glVertex3f(-0.68f, 0.40f, -3.0f);

		glVertex3f(-0.75f, 0.40f, -3.0f);
		glVertex3f(-0.68f, 0.40f, -3.0f);

		glVertex3f(-0.75f, 0.40f, -3.0f);
		glVertex3f(-0.70f, 0.30f, -3.0f);

		glVertex3f(-0.55f, 0.50f, -3.0f);
		glVertex3f(-0.55f, 0.47f, -3.0f);

		glVertex3f(-0.55f, 0.47f, -3.0f);
		glVertex3f(-0.60f, 0.47f, -3.0f);

		glVertex3f(-0.60f, 0.47f, -3.0f);
		glVertex3f(-0.57f, 0.41f, -3.0f);


		glVertex3f(-0.57f, 0.41f, -3.0f);
		glVertex3f(-0.51f, 0.39f, -3.0f);

		glVertex3f(-0.51f, 0.39f, -3.0f);
		glVertex3f(-0.55f, 0.35f, -3.0f);


		glVertex3f(-0.57f, 0.41f, -3.0f);
		glVertex3f(-0.62f, 0.36f, -3.0f);

		glVertex3f(-0.62f, 0.36f, -3.0f);
		glVertex3f(-0.55f, 0.30f, -3.0f);

		glVertex3f(-0.33f, 0.50f, -3.0f);
		glVertex3f(-0.33f, 0.30f, -3.0f);

		glVertex3f(-0.33f, 0.42f, -3.0f);
		glVertex3f(-0.47f, 0.42f, -3.0f);

		glVertex3f(-0.47f, 0.42f, -3.0f);
		glVertex3f(-0.47f, 0.35f, -3.0f);
		glVertex3f(-0.47f, 0.35f, -3.0f);
		glVertex3f(-0.40f, 0.35f, -3.0f);

		glVertex3f(-0.40f, 0.35f, -3.0f);
		glVertex3f(-0.40f, 0.42f, -3.0f);

		glVertex3f(-0.80f, 0.50f, -3.0f);
		glVertex3f(-0.28f, 0.50f, -3.0f);

		//  स्नेहा ....... ///

		glVertex3f(-0.75f, 0.20f, -3.0f);
		glVertex3f(-0.68f, 0.10f, -3.0f);
		glVertex3f(-0.65f, 0.10f, -3.0f);
		glVertex3f(-0.75f, 0.10f, -3.0f);

		glVertex3f(-0.75f, 0.10f, -3.0f);
		glVertex3f(-0.70f, 0.00f, -3.0f);
		glVertex3f(-0.60f, 0.30f, -3.0f);
		glVertex3f(-0.53f, 0.20f, -3.0f);

		glVertex3f(-0.53f, 0.20f, -3.0f);
		glVertex3f(-0.53f, 0.00f, -3.0f);
		glVertex3f(-0.53f, 0.12f, -3.0f);
		glVertex3f(-0.65f, 0.12f, -3.0f);

		glVertex3f(-0.65f, 0.12f, -3.0f);
		glVertex3f(-0.65f, 0.05f, -3.0f);
		glVertex3f(-0.65f, 0.05f, -3.0f);
		glVertex3f(-0.58f, 0.05f, -3.0f);

		glVertex3f(-0.58f, 0.05f, -3.0f);
		glVertex3f(-0.58f, 0.12f, -3.0f);
		glVertex3f(-0.41f, 0.20f, -3.0f);
		glVertex3f(-0.41f, 0.17f, -3.0f);

		glVertex3f(-0.41f, 0.17f, -3.0f);
		glVertex3f(-0.47f, 0.17f, -3.0f);
		glVertex3f(-0.47f, 0.17f, -3.0f);
		glVertex3f(-0.43f, 0.11f, -3.0f);

		glVertex3f(-0.43f, 0.11f, -3.0f);
		glVertex3f(-0.38f, 0.07f, -3.0f);
		glVertex3f(-0.38f, 0.07f, -3.0f);
		glVertex3f(-0.43f, 0.04f, -3.0f);

		glVertex3f(-0.43f, 0.11f, -3.0f);
		glVertex3f(-0.49f, 0.05f, -3.0f);

		glVertex3f(-0.49f, 0.05f, -3.0f);
		glVertex3f(-0.43f, 0.00f, -3.0f);

		glVertex3f(-0.35f, 0.00f, -3.0f);
		glVertex3f(-0.35f, 0.20f, -3.0f);

		glVertex3f(-0.80f, 0.20f, -3.0f);
		glVertex3f(-0.30f, 0.20f, -3.0f);

		//  सौरभ....  ///

		glVertex3f(0.10f, 0.80f, -3.0f);
		glVertex3f(0.17f, 0.70f, -3.0f);
		glVertex3f(0.10f, 0.70f, -3.0f);
		glVertex3f(0.20f, 0.70f, -3.0f);

		glVertex3f(0.20f, 0.80f, -3.0f);
		glVertex3f(0.20f, 0.60f, -3.0f);
		glVertex3f(0.10f, 0.70f, -3.0f);
		glVertex3f(0.15f, 0.60f, -3.0f);

		glVertex3f(0.23f, 0.80f, -3.0f);
		glVertex3f(0.23f, 0.60f, -3.0f);
		glVertex3f(0.13f, 0.90f, -3.0f);
		glVertex3f(0.23f, 0.80f, -3.0f);

		glVertex3f(0.18f, 0.90f, -3.0f);
		glVertex3f(0.23f, 0.80f, -3.0f);
		glVertex3f(0.28f, 0.80f, -3.0f);
		glVertex3f(0.35f, 0.70f, -3.0f);

		glVertex3f(0.28f, 0.70f, -3.0f);
		glVertex3f(0.35f, 0.70f, -3.0f);
		glVertex3f(0.28f, 0.70f, -3.0f);
		glVertex3f(0.35f, 0.60f, -3.0f);

		glVertex3f(0.50f, 0.80f, -3.0f);
		glVertex3f(0.50f, 0.60f, -3.0f);
		glVertex3f(0.50f, 0.70f, -3.0f);
		glVertex3f(0.39f, 0.70f, -3.0f);

		glVertex3f(0.39f, 0.70f, -3.0f);
		glVertex3f(0.39f, 0.65f, -3.0f);
		glVertex3f(0.39f, 0.65f, -3.0f);
		glVertex3f(0.44f, 0.65f, -3.0f);

		glVertex3f(0.44f, 0.65f, -3.0f);
		glVertex3f(0.44f, 0.80f, -3.0f);
		glVertex3f(0.44f, 0.80f, -3.0f);
		glVertex3f(0.39f, 0.80f, -3.0f);

		glVertex3f(0.39f, 0.80f, -3.0f);
		glVertex3f(0.39f, 0.75f, -3.0f);
		glVertex3f(0.39f, 0.75f, -3.0f);
		glVertex3f(0.44f, 0.75f, -3.0f);

		glVertex3f(0.05f, 0.80f, -3.0f);
		glVertex3f(0.36f, 0.80f, -3.0f);

		glVertex3f(0.46f, 0.80f, -3.0f);
		glVertex3f(0.55f, 0.80f, -3.0f);

		//  शीतल..... ///

		glVertex3f(0.10f, 0.45f, -3.0f);
		glVertex3f(0.17f, 0.45f, -3.0f);
		glVertex3f(0.17f, 0.45f, -3.0f);
		glVertex3f(0.17f, 0.50f, -3.0f);

		glVertex3f(0.17f, 0.50f, -3.0f);
		glVertex3f(0.10f, 0.50f, -3.0f);
		glVertex3f(0.10f, 0.50f, -3.0f);
		glVertex3f(0.10f, 0.45f, -3.0f);

		glVertex3f(0.17f, 0.45f, -3.0f);
		glVertex3f(0.10f, 0.37f, -3.0f);
		glVertex3f(0.10f, 0.38f, -3.0f);
		glVertex3f(0.17f, 0.30f, -3.0f);


		glVertex3f(0.21f, 0.50f, -3.0f);
		glVertex3f(0.21f, 0.30f, -3.0f);
		glVertex3f(0.21f, 0.50f, -3.0f);
		glVertex3f(0.20f, 0.58f, -3.0f);


		glVertex3f(0.20f, 0.58f, -3.0f);
		glVertex3f(0.26f, 0.58f, -3.0f);
		glVertex3f(0.26f, 0.58f, -3.0f);
		glVertex3f(0.25f, 0.50f, -3.0f);

		glVertex3f(0.25f, 0.50f, -3.0f);
		glVertex3f(0.25f, 0.30f, -3.0f);
		glVertex3f(0.29f, 0.30f, -3.0f);
		glVertex3f(0.29f, 0.42f, -3.0f);

		glVertex3f(0.29f, 0.42f, -3.0f);
		glVertex3f(0.37f, 0.42f, -3.0f);
		glVertex3f(0.37f, 0.50f, -3.0f);
		glVertex3f(0.37f, 0.30f, -3.0f);

		glVertex3f(0.40f, 0.43f, -3.0f);
		glVertex3f(0.40f, 0.32f, -3.0f);
		glVertex3f(0.40f, 0.43f, -3.0f);
		glVertex3f(0.45f, 0.38f, -3.0f);


		glVertex3f(0.45f, 0.38f, -3.0f);
		glVertex3f(0.52f, 0.44f, -3.0f);
		glVertex3f(0.52f, 0.50f, -3.0f);
		glVertex3f(0.52f, 0.30f, -3.0f);

		glVertex3f(0.05f, 0.50f, -3.0f);
		glVertex3f(0.57f, 0.50f, -3.0f);

		// प्रणव.... ///

		glVertex3f(0.11f, 0.20f, -3.0f);
		glVertex3f(0.11f, 0.11f, -3.0f);

		glVertex3f(0.11f, 0.11f, -3.0f);
		glVertex3f(0.20f, 0.11f, -3.0f);

		glVertex3f(0.10f, 0.00f, -3.0f);
		glVertex3f(0.20f, 0.11f, -3.0f);

		glVertex3f(0.20f, 0.20f, -3.0f);
		glVertex3f(0.20f, 0.00f, -3.0f);

		glVertex3f(0.23f, 0.20f, -3.0f);
		glVertex3f(0.23f, 0.11f, -3.0f);

		glVertex3f(0.23f, 0.11f, -3.0f);
		glVertex3f(0.32f, 0.11f, -3.0f);

		glVertex3f(0.32f, 0.11f, -3.0f);
		glVertex3f(0.32f, 0.20f, -3.0f);

		glVertex3f(0.46f, 0.15f, -3.0f);
		glVertex3f(0.39f, 0.15f, -3.0f);

		glVertex3f(0.39f, 0.15f, -3.0f);
		glVertex3f(0.39f, 0.05f, -3.0f);

		glVertex3f(0.39f, 0.05f, -3.0f);
		glVertex3f(0.46f, 0.05f, -3.0f);

		glVertex3f(0.46f, 0.20f, -3.0f);
		glVertex3f(0.46f, 0.00f, -3.0f);

		glVertex3f(0.35f, 0.20f, -3.0f);
		glVertex3f(0.35f, 0.00f, -3.0f);

		glVertex3f(0.05f, 0.20f, -3.0f);
		glVertex3f(0.50f, 0.20f, -3.0f);

		//   अनिकेत..... /////


		glVertex3f(0.10f, -0.11f, -3.0f);
		glVertex3f(0.20f, -0.11f, -3.0f);

		glVertex3f(0.20f, -0.11f, -3.0f);
		glVertex3f(0.15f, -0.20f, -3.0f);

		glVertex3f(0.15f, -0.20f, -3.0f);
		glVertex3f(0.20f, -0.29f, -3.0f);

		glVertex3f(0.20f, -0.29f, -3.0f);
		glVertex3f(0.10f, -0.29f, -3.0f);


		glVertex3f(0.15f, -0.20f, -3.0f);
		glVertex3f(0.23f, -0.20f, -3.0f);

		glVertex3f(0.23f, -0.10f, -3.0f);
		glVertex3f(0.23f, -0.30f, -3.0f);

		glVertex3f(0.27f, -0.01f, -3.0f);
		glVertex3f(0.27f, -0.30f, -3.0f);
		glVertex3f(0.27f, -0.01f, -3.0f);
		glVertex3f(0.35f, -0.01f, -3.0f);

		glVertex3f(0.35f, -0.01f, -3.0f);
		glVertex3f(0.44f, -0.10f, -3.0f);
		glVertex3f(0.44f, -0.10f, -3.0f);
		glVertex3f(0.44f, -0.30f, -3.0f);

		glVertex3f(0.30f, -0.17f, -3.0f);
		glVertex3f(0.44f, -0.17f, -3.0f);
		glVertex3f(0.30f, -0.17f, -3.0f);
		glVertex3f(0.30f, -0.25f, -3.0f);

		//7

		glVertex3f(0.30f, -0.25f, -3.0f);
		glVertex3f(0.37f, -0.25f, -3.0f);
		glVertex3f(0.37f, -0.25f, -3.0f);
		glVertex3f(0.37f, -0.17f, -3.0f);

		glVertex3f(0.48f, -0.00f, -3.0f);
		glVertex3f(0.56f, -0.10f, -3.0f);
		glVertex3f(0.56f, -0.10f, -3.0f);
		glVertex3f(0.56f, -0.30f, -3.0f);

		glVertex3f(0.56f, -0.14f, -3.0f);
		glVertex3f(0.50f, -0.14f, -3.0f);
		glVertex3f(0.50f, -0.14f, -3.0f);
		glVertex3f(0.50f, -0.23f, -3.0f);

		glVertex3f(0.50f, -0.23f, -3.0f);
		glVertex3f(0.56f, -0.23f, -3.0f);
		glVertex3f(0.56f, -0.17f, -3.0f);
		glVertex3f(0.62f, -0.17f, -3.0f);

		glVertex3f(0.62f, -0.17f, -3.0f);
		glVertex3f(0.62f, -0.25f, -3.0f);
		glVertex3f(0.62f, -0.25f, -3.0f);
		glVertex3f(0.58f, -0.25f, -3.0f);

		glVertex3f(0.65f, -0.30f, -3.0f);
		glVertex3f(0.65f, -0.17f, -3.0f);
		glVertex3f(0.65f, -0.17f, -3.0f);
		glVertex3f(0.75f, -0.17f, -3.0f);

		glVertex3f(0.75f, -0.10f, -3.0f);
		glVertex3f(0.75f, -0.30f, -3.0f);

		glVertex3f(0.05f, -0.10f, -3.0f);
		glVertex3f(0.80f, -0.10f, -3.0f);
		glEnd();

		// सर्वेश....... ////

		glLineWidth(5.0f);

		glBegin(GL_LINES);

		glVertex3f(-0.75f, -0.10f, -3.0f);
		glVertex3f(-0.68f, -0.20f, -3.0f);

		glVertex3f(-0.75f, -0.20f, -3.0f);
		glVertex3f(-0.65f, -0.20f, -3.0f);

		glVertex3f(-0.75f, -0.20f, -3.0f);
		glVertex3f(-0.70f, -0.30f, -3.0f);

		glVertex3f(-0.65f, -0.10f, -3.0f);
		glVertex3f(-0.65f, -0.30f, -3.0f);

		glVertex3f(-0.62f, -0.00f, -3.0f);
		glVertex3f(-0.53f, -0.10f, -3.0f);

		glVertex3f(-0.53f, -0.10f, -3.0f);
		glVertex3f(-0.53f, -0.05f, -3.0f);

		glVertex3f(-0.49f, -0.05f, -3.0f);
		glVertex3f(-0.53f, -0.05f, -3.0f);

		glVertex3f(-0.53f, -0.30f, -3.0f);
		glVertex3f(-0.53f, -0.10f, -3.0f);

		glVertex3f(-0.60f, -0.15f, -3.0f);
		glVertex3f(-0.60f, -0.25f, -3.0f);

		glVertex3f(-0.60f, -0.25f, -3.0f);
		glVertex3f(-0.53f, -0.25f, -3.0f);

		glVertex3f(-0.60f, -0.15f, -3.0f);
		glVertex3f(-0.53f, -0.15f, -3.0f);

		glVertex3f(-0.40f, -0.15f, -3.0f);
		glVertex3f(-0.47f, -0.15f, -3.0f);

		glVertex3f(-0.47f, -0.15f, -3.0f);
		glVertex3f(-0.47f, -0.11f, -3.0f);

		glVertex3f(-0.47f, -0.11f, -3.0f);
		glVertex3f(-0.40f, -0.11f, -3.0f);
		glVertex3f(-0.40f, -0.11f, -3.0f);
		glVertex3f(-0.40f, -0.15f, -3.0f);

		glVertex3f(-0.40f, -0.15f, -3.0f);
		glVertex3f(-0.48f, -0.23f, -3.0f);
		glVertex3f(-0.48f, -0.20f, -3.0f);
		glVertex3f(-0.38f, -0.30f, -3.0f);

		glVertex3f(-0.35f, -0.10f, -3.0f);
		glVertex3f(-0.35f, -0.30f, -3.0f);

		glVertex3f(-0.30f, -0.10f, -3.0f);
		glVertex3f(-0.80f, -0.10f, -3.0f);
		glEnd();


		//  अभिलाष..... ///

		glPushMatrix();
		glTranslatef(0.2f, -0.17f, 0.0f);
		glScalef(0.8f, 1.0f, 0.0f);

		glLineWidth(5.0f);

		glBegin(GL_LINES);

		glVertex3f(-0.78f, -0.41f, -3.0f);
		glVertex3f(-0.69f, -0.41f, -3.0f);

		glVertex3f(-0.69f, -0.41f, -3.0f);
		glVertex3f(-0.75f, -0.50f, -3.0f);

		glVertex3f(-0.75f, -0.50f, -3.0f);
		glVertex3f(-0.69f, -0.59f, -3.0f);

		glVertex3f(-0.78f, -0.59f, -3.0f);
		glVertex3f(-0.69f, -0.59f, -3.0f);

		glVertex3f(-0.74f, -0.50f, -3.0f);
		glVertex3f(-0.65f, -0.50f, -3.0f);

		glVertex3f(-0.65f, -0.40f, -3.0f);
		glVertex3f(-0.65f, -0.60f, -3.0f);

		glVertex3f(-0.62f, -0.32f, -3.0f);
		glVertex3f(-0.62f, -0.6f, -3.0f);

		glVertex3f(-0.62f, -0.32f, -3.0f);
		glVertex3f(-0.48f, -0.32f, -3.0f);

		glVertex3f(-0.48f, -0.32f, -3.0f);
		glVertex3f(-0.48f, -0.60f, -3.0f);

		glVertex3f(-0.60f, -0.50f, -3.0f);
		glVertex3f(-0.48f, -0.50f, -3.0f);

		glVertex3f(-0.60f, -0.50f, -3.0f);
		glVertex3f(-0.60f, -0.55f, -3.0f);

		glVertex3f(-0.55f, -0.40f, -3.0f);
		glVertex3f(-0.55f, -0.55f, -3.0f);

		glVertex3f(-0.55f, -0.55f, -3.0f);
		glVertex3f(-0.60f, -0.55f, -3.0f);

		glVertex3f(-0.55f, -0.40f, -3.0f);
		glVertex3f(-0.60f, -0.40f, -3.0f);

		glVertex3f(-0.60f, -0.40f, -3.0f);
		glVertex3f(-0.60f, -0.45f, -3.0f);

		glVertex3f(-0.60f, -0.45f, -3.0f);
		glVertex3f(-0.55f, -0.45f, -3.0f);

		glVertex3f(-0.45f, -0.48f, -3.0f);
		glVertex3f(-0.45f, -0.60f, -3.0f);

		glVertex3f(-0.45f, -0.48f, -3.0f);
		glVertex3f(-0.38f, -0.55f, -3.0f);

		glVertex3f(-0.38f, -0.55f, -3.0f);
		glVertex3f(-0.33f, -0.49f, -3.0f);
		glVertex3f(-0.33f, -0.40f, -3.0f);
		glVertex3f(-0.33f, -0.60f, -3.0f);

		glVertex3f(-0.29f, -0.40f, -3.0f);
		glVertex3f(-0.29f, -0.60f, -3.0f);
		glVertex3f(-0.25f, -0.40f, -3.0f);
		glVertex3f(-0.25f, -0.50f, -3.0f);

		glVertex3f(-0.25f, -0.50f, -3.0f);
		glVertex3f(-0.15f, -0.50f, -3.0f);
		glVertex3f(-0.15f, -0.50f, -3.0f);
		glVertex3f(-0.25f, -0.40f, -3.0f);

		glVertex3f(-0.15f, -0.40f, -3.0f);
		glVertex3f(-0.15f, -0.60f, -3.0f);

		glVertex3f(-0.80f, -0.40f, -3.0f);
		glVertex3f(-0.62f, -0.40f, -3.0f);

		glVertex3f(-0.52f, -0.40f, -3.0f);
		glVertex3f(-0.10f, -0.40f, -3.0f);

		glEnd();

		glPopMatrix();
	}
	glPopMatrix();

	//group leader
	glPushMatrix();
	glTranslatef(0.05f, -1.13f, 0.0f);
	glScalef(0.8f, 0.8f, 0.0f);
	{
		glPushMatrix();
		glTranslatef(-0.85f, 1.0f, 0.0f);
		glScalef(0.9f, 0.9f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.46f, -0.15f, 0.0f);
		glVertex3f(0.47f, -0.19f, 0.0f);
		glVertex3f(0.78f, -0.19f, 0.0f);
		glVertex3f(0.77f, -0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.53f, -0.19f, 0.0f);
		glVertex3f(0.56f, -0.19f, 0.0f);
		glVertex3f(0.57f, -0.28f, 0.0f);
		glVertex3f(0.54f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.57f, -0.28f, 0.0f);
		glVertex3f(0.54f, -0.28f, 0.0f);
		glVertex3f(0.51f, -0.285f, 0.0f);
		glVertex3f(0.55f, -0.33f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.6f, -0.19f, 0.0f);
		glVertex3f(0.6f, -0.39f, 0.0f);
		glVertex3f(0.62f, -0.39f, 0.0f);
		glVertex3f(0.62f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.6f, -0.32f, 0.0f);
		glVertex3f(0.6f, -0.35f, 0.0f);
		glVertex3f(0.55f, -0.38f, 0.0f);
		glVertex3f(0.53f, -0.36f, 0.0f);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.185f, 0.725f, 0.0f);
		glScalef(0.9f, 1.0f, 0.0f);

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.14f, -0.1f, 0.0f);
		glVertex3f(-0.15f, -0.08f, 0.0f);
		glVertex3f(-0.12f, -0.07f, 0.0f);
		glVertex3f(-0.1f, -0.09f, 0.0f);
		glVertex3f(-0.11f, -0.1f, 0.0f);
		glVertex3f(-0.12f, -0.11f, 0.0f);
		glVertex3f(-0.12f, -0.09f, 0.0f);
		glVertex3f(-0.14f, -0.1f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.1f, -0.09f, 0.0f);
		glVertex3f(-0.13f, -0.11f, 0.0f);
		glVertex3f(-0.14f, -0.13f, 0.0f);
		glVertex3f(-0.11f, -0.13f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.14f, -0.13f, 0.0f);
		glVertex3f(-0.11f, -0.13f, 0.0f);
		glVertex3f(-0.18f, -0.09f, 0.0f);
		glVertex3f(-0.2f, -0.1f, 0.0f);
		glEnd();

		glPopMatrix();

		//p letter ///////////////////////////////
		glPushMatrix();
		glTranslatef(-0.2f, 0.8f, 0.0f);
		glScalef(0.4f, 0.5f, 1.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.15f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(-0.15f, 0.1f, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.15f, -0.1f, 0.0f);
		glVertex3f(-0.15f, -0.15f, 0.0f);
		glVertex3f(-0.1f, -0.2f, 0.0f);
		glVertex3f(-0.07f, -0.15f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(-0.15f, -0.1f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.1f, -0.15f, 0.0f);
		glVertex3f(-0.1f, -0.2f, 0.0f);
		glVertex3f(0.0f, -0.2f, 0.0f);
		glVertex3f(0.0f, -0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.4f, 0.0f);
		glVertex3f(0.05f, -0.4f, 0.0f);
		glVertex3f(0.05f, 0.1f, 0.0f);
		glVertex3f(0.0f, 0.1f, 0.0f);
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();

	//leader

	glPushMatrix();
	glTranslatef(-0.05f, -0.07f, 0.0f);
	glScalef(0.9f, 0.8f, 1.0f);
	{
		glPushMatrix();
		glTranslatef(0.0f, -0.3f, 0.0f);
		glScalef(0.7f, 0.9f, 1.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.14f, -0.17f, 0.0f);
		glVertex3f(0.14f, -0.2f, 0.0f);
		glVertex3f(0.57f, -0.2f, 0.0f);
		glVertex3f(0.57f, -0.17f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.15f, -0.2f, 0.0f);
		glVertex3f(0.15f, -0.45f, 0.0f);
		glVertex3f(0.17f, -0.46f, 0.0f);
		glVertex3f(0.17f, -0.2f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.13f, -0.31f, 0.0f);
		glVertex3f(0.13f, -0.275f, 0.0f);
		glVertex3f(0.15f, -0.27f, 0.0f);
		glVertex3f(0.15f, -0.3f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.34f, 0.0f);
		glVertex3f(0.12f, -0.35f, 0.0f);
		glVertex3f(0.13f, -0.31f, 0.0f);
		glVertex3f(0.13f, -0.275f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.13f, -0.28f, 0.0f);
		glVertex3f(0.13f, -0.3f, 0.0f);
		glVertex3f(0.09f, -0.31f, 0.0f);
		glVertex3f(0.09f, -0.27f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.09f, -0.31f, 0.0f);
		glVertex3f(0.09f, -0.27f, 0.0f);
		glVertex3f(0.05f, -0.34f, 0.0f);
		glVertex3f(0.08f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.05f, -0.34f, 0.0f);
		glVertex3f(0.08f, -0.34f, 0.0f);
		glVertex3f(0.11f, -0.43f, 0.0f);
		glVertex3f(0.09f, -0.45f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.21f, -0.2f, 0.0f);
		glVertex3f(0.21f, -0.45f, 0.0f);
		glVertex3f(0.23f, -0.46f, 0.0f);
		glVertex3f(0.23f, -0.2f, 0.0f);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.14f, -0.32f, 0.0f);
		glScalef(0.7f, 0.8f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.35f, -0.17f, 0.0f);
		glVertex3f(0.37f, -0.17f, 0.0f);
		glVertex3f(0.38f, -0.11f, 0.0f);
		glVertex3f(0.38f, -0.08f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.38f, -0.11f, 0.0f);
		glVertex3f(0.38f, -0.08f, 0.0f);
		glVertex3f(0.43f, -0.09f, 0.0f);
		glVertex3f(0.43f, -0.11f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.42f, -0.08f, 0.0f);
		glVertex3f(0.42f, -0.17f, 0.0f);
		glVertex3f(0.43f, -0.17f, 0.0f);
		glVertex3f(0.43f, -0.09f, 0.0f);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.5f, -0.25f, 0.0f);
		glScalef(0.7f, 1.2f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.36f, -0.19f, 0.0f);
		glVertex3f(-0.34f, -0.19f, 0.0f);
		glVertex3f(-0.34f, -0.22f, 0.0f);
		glVertex3f(-0.36f, -0.22f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.34f, -0.22f, 0.0f);
		glVertex3f(-0.34f, -0.25f, 0.0f);
		glVertex3f(-0.39f, -0.25f, 0.0f);
		glVertex3f(-0.39f, -0.22f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.39f, -0.22f, 0.0f);
		glVertex3f(-0.39f, -0.25f, 0.0f);
		glVertex3f(-0.4f, -0.27f, 0.0f);
		glVertex3f(-0.42f, -0.27f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.4f, -0.27f, 0.0f);
		glVertex3f(-0.42f, -0.27f, 0.0f);
		glVertex3f(-0.39f, -0.31f, 0.0f);
		glVertex3f(-0.39f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.39f, -0.31f, 0.0f);
		glVertex3f(-0.39f, -0.29f, 0.0f);
		glVertex3f(-0.37f, -0.28f, 0.0f);
		glVertex3f(-0.37f, -0.31f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.37f, -0.28f, 0.0f);
		glVertex3f(-0.37f, -0.31f, 0.0f);
		glVertex3f(-0.34f, -0.305f, 0.0f);
		glVertex3f(-0.32f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.34f, -0.305f, 0.0f);
		glVertex3f(-0.32f, -0.29f, 0.0f);
		glVertex3f(-0.3f, -0.31f, 0.0f);
		glVertex3f(-0.34f, -0.31f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.3f, -0.31f, 0.0f);
		glVertex3f(-0.33f, -0.31f, 0.0f);
		glVertex3f(-0.35f, -0.34f, 0.0f);
		glVertex3f(-0.32f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.35f, -0.34f, 0.0f);
		glVertex3f(-0.32f, -0.34f, 0.0f);
		glVertex3f(-0.37f, -0.38f, 0.0f);
		glVertex3f(-0.37f, -0.35f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.37f, -0.38f, 0.0f);
		glVertex3f(-0.37f, -0.35f, 0.0f);
		glVertex3f(-0.4f, -0.355f, 0.0f);
		glVertex3f(-0.4f, -0.375f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.4f, -0.355f, 0.0f);
		glVertex3f(-0.4f, -0.375f, 0.0f);
		glVertex3f(-0.45f, -0.34f, 0.0f);
		glVertex3f(-0.43f, -0.33f, 0.0f);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.13f, -0.23f, 0.0f);
		glScalef(0.8f, 1.3f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.25f, -0.19f, 0.0f);
		glVertex3f(0.28f, -0.19f, 0.0f);
		glVertex3f(0.29f, -0.25f, 0.0f);
		glVertex3f(0.26f, -0.25f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.29f, -0.25f, 0.0f);
		glVertex3f(0.26f, -0.23f, 0.0f);
		glVertex3f(0.2f, -0.27f, 0.0f);
		glVertex3f(0.23f, -0.3f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.2f, -0.27f, 0.0f);
		glVertex3f(0.25f, -0.28f, 0.0f);
		glVertex3f(0.28f, -0.33f, 0.0f);
		glVertex3f(0.28f, -0.37f, 0.0f);
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();

	//   मयुरेश..... ///

	glPushMatrix();
	glTranslatef(-0.3f, -0.45f, 0.0f);
	glScalef(0.7f, 0.75f, 0.0f);

	glLineWidth(7.0f);

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(0.18f, -0.40f, -3.0f);
	glVertex3f(0.18f, -0.56f, -3.0f);

	glVertex3f(0.18f, -0.56f, -3.0f);
	glVertex3f(0.10f, -0.56f, -3.0f);

	glVertex3f(0.10f, -0.49f, -3.0f);
	glVertex3f(0.10f, -0.56f, -3.0f);

	glVertex3f(0.10f, -0.49f, -3.0f);
	glVertex3f(0.25f, -0.49f, -3.0f);

	glVertex3f(0.25f, -0.40f, -3.0f);
	glVertex3f(0.25f, -0.60f, -3.0f);

	glVertex3f(0.30f, -0.41f, -3.0f);
	glVertex3f(0.40f, -0.41f, -3.0f);

	glVertex3f(0.40f, -0.40f, -3.0f);
	glVertex3f(0.36f, -0.50f, -3.0f);
	glVertex3f(0.30f, -0.47f, -3.0f);
	glVertex3f(0.41f, -0.55f, -3.0f);

	glVertex3f(0.41f, -0.55f, -3.0f);
	glVertex3f(0.47f, -0.47f, -3.0f);
	glVertex3f(0.47f, -0.40f, -3.0f);
	glVertex3f(0.47f, -0.60f, -3.0f);

	glVertex3f(0.47f, -0.60f, -3.0f);
	glVertex3f(0.43f, -0.65f, -3.0f);
	glVertex3f(0.47f, -0.60f, -3.0f);
	glVertex3f(0.50f, -0.65f, -3.0f);

	glVertex3f(0.50f, -0.65f, -3.0f);
	glVertex3f(0.46f, -0.70f, -3.0f);
	glVertex3f(0.46f, -0.70f, -3.0f);
	glVertex3f(0.35f, -0.63f, -3.0f);

	glVertex3f(0.50f, -0.30f, -3.0f);
	glVertex3f(0.56f, -0.40f, -3.0f);
	glVertex3f(0.54f, -0.40f, -3.0f);
	glVertex3f(0.61f, -0.50f, -3.0f);

	glVertex3f(0.54f, -0.50f, -3.0f);
	glVertex3f(0.61f, -0.50f, -3.0f);
	glVertex3f(0.54f, -0.50f, -3.0f);
	glVertex3f(0.60f, -0.60f, -3.0f);

	glVertex3f(0.67f, -0.45f, -3.0f);
	glVertex3f(0.74f, -0.45f, -3.0f);

	glVertex3f(0.74f, -0.45f, -3.0f);
	glVertex3f(0.74f, -0.40f, -3.0f);

	glVertex3f(0.74f, -0.40f, -3.0f);
	glVertex3f(0.67f, -0.40f, -3.0f);

	glVertex3f(0.67f, -0.40f, -3.0f);
	glVertex3f(0.67f, -0.45f, -3.0f);

	glVertex3f(0.74f, -0.45f, -3.0f);
	glVertex3f(0.68f, -0.53f, -3.0f);

	glVertex3f(0.67f, -0.51f, -3.0f);
	glVertex3f(0.76f, -0.60f, -3.0f);

	glVertex3f(0.79f, -0.40f, -3.0f);
	glVertex3f(0.79f, -0.60f, -3.0f);

	glVertex3f(0.85f, -0.40f, -3.0f);
	glVertex3f(0.05f, -0.40f, -3.0f);

	glEnd();

	glPopMatrix();

	//do double buffering
	// SwapBuffers(ghdc);

}
/*

void update(void)
{
	//code
}

void uninitialize(void)
{
	//code
	// if exiting in full screen first restore and then proceed
	if (bFullscreen == TRUE)
	{
		toggleFullScreen();
		bFullscreen = FALSE;
	}

	//first check the current contex and if it is then unmake it
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
		
	}

	//Destroy the rendering contex
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//release the device contex
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//destroy window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;

	}

	//Close Log File
	if (gpFile)
	{
		fprintf(gpFile, "SHS : Program Terminated Successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
*/