// Header Files
#include <windows.h>
#include <stdio.h>          // Used for log file --> FILE macro --> file I/O
#include <stdlib.h>      // used for exit(0);
// #include "OGL.h"
#define _USE_MATH_DEFINES
#include <math.h>

// OpenGL related header files
#include <gl/GL.h>  // includes GL.h inside gl directory
#include <gl/GLU.h>

// link with openGL import library
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLU32.lib")

/*
// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;      
BOOL bFullscreen = FALSE;
DWORD dWStyle;
WINDOWPLACEMENT wpPrev;
FILE *gpFile = NULL;
BOOL bActiveWindow = FALSE;
BOOL bEscapeKeyIsPressed = FALSE;
*/
 GLuint texture_Quote_SM = 0;
 extern FILE* gpFile;
/*
// Global Function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// function declarations
	int initialize(void);
	void render(void);         // display, draw
	void update(void);
	void uninitialize(void);

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd = NULL;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR7_STM");
	BOOL bDone = FALSE;

	// code
	// Create Log File
	gpFile = fopen("log.txt", "w");
	if (gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log File Creation Failed !!"), TEXT("Error !!"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log File By : Saurabh Tanaji Mane !!\n");
		fprintf(gpFile, "Program Started Successfully !!\n");
	}

	// WNDCLASSEX structure initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register above WNDCLASS
	RegisterClassEx(&wndclass);

	// Centering
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenheight = GetSystemMetrics(SM_CYSCREEN);

	// create the extended window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("RTR7 - Saurabh Tanaji Mane : Sanskrit Quote"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		screenWidth / 2 - WIN_WIDTH / 2,
		screenheight/2-WIN_HEIGHT/2,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);


	// Set global window handle
	ghwnd = hwnd;

	int iResult = initialize();
	if (iResult != 0)
	{
		fprintf(gpFile, "STM : WinMain() : Initialize() Failed !!\n");
		DestroyWindow(hwnd);
		hwnd = NULL;
	}
	else
	{
		fprintf(gpFile, "STM : WinMain() : Initialize() Succeded !!\n");
	}
	// show window
	ShowWindow(hwnd, iCmdShow);

	// update the window to point its background
	UpdateWindow(hwnd);
	
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Game loop
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
				// render
				render();

				// update
				update();
			}
		}
	}

	// uninitialize
	uninitialize();

	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	// function declarations
	void resize(int, int);
	void toggleFullscreen(void);
	void uninitialize(void);

	// code
	switch (imsg)
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
				toggleFullscreen();
				bFullscreen = TRUE;
			}
			else
			{
				toggleFullscreen();
				bFullscreen = FALSE;
			}
			break;
		}
		break;

	case WM_CLOSE:
		uninitialize();
		break;

	case WM_DESTROY:
		PostQuitMessage(340);     // if not handled task will remain active in task manager and won't open again --> Error : fatal error LNK1104: cannot open file 'Window.exe'
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, imsg, wParam, lParam));
}

void toggleFullscreen(void)
{
	// variable declarations
	MONITORINFO mi;

	// code
	if (bFullscreen == FALSE)
	{
		dWStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dWStyle & WS_OVERLAPPEDWINDOW)
		{
			memset(&mi, 0, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd,MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dWStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top,SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dWStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	// function declarations
	void resize(int, int);
	void printGLInfo(void);
	BOOL loadGLTexture(GLuint*, TCHAR[]);

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	// code
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));       // ZeroMemory() also can be used
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;       // conventional
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;         // 2 raised to 32 depth

	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		return(-1);
	}
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
		return(-2);

	if (SetPixelFormat(ghdc,iPixelFormatIndex,&pfd)==FALSE)
		return(-3);

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
		return(-4);

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
		return(-5);

	// print OpenGL Info
	printGLInfo();

	// Enable depth
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// choose screen clearing color as black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Load Textures
	BOOL bResult = FALSE;
	bResult = loadGLTexture(&texture_Quote_SM, MAKEINTRESOURCE(IDBITMAP_QUOTE));
	if (bResult == FALSE)
		return(-6);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	resize(WIN_WIDTH, WIN_HEIGHT);
	toggleFullscreen();


	return 0;
}
*/

BOOL loadGLTexture(GLuint* tex, TCHAR imageResourceID[])
{
	// variable declarations
	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	// code
	//  Load the image resource and get its handle
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		fprintf(gpFile, "LoadImage() failed !!\n");
		return(FALSE);
	}

	// Use this handle to get the windows struct BITMAP object
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	// Decide how openGL should store and align bits of the image in memory
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	// Create the openGL texture object
	glGenTextures(1, tex);

	// Bind with that newly created openGL texture object
	glBindTexture(GL_TEXTURE_2D, *tex);

	// Set the texture object's parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Accordingly build openGL texture objects and its mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, (void*)bmp.bmBits);

	//Unbind with the openGL texture object
	glBindTexture(GL_TEXTURE_2D, 0);

	// Delete windows Texture objects
	DeleteObject((HGDIOBJ)hBitmap);

	return(TRUE);

}

/*
void printGLInfo(void)
{
	fprintf(gpFile, "OpenGL VENDOR : %s \n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL RENDEROR : %s \n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL VERSION : %s \n", glGetString(GL_VERSION));

}


void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;         // in future to avoid undefined/infinite
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective projection
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

*/
void drawSanskritQuote(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);   // 2D dimensions

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Disable depth write so the background quad does not block 3D geometry
	glDepthMask(GL_FALSE);

	glColor3f(1.0f, 1.0f, 1.0f); // Ensure texture isn't tinted
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_Quote_SM);

	glBegin(GL_QUADS);
	// Bottom-Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	// Bottom-Right
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);

	// Top-Right
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);

	// Top-Left
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);

	// Re-enable depth 
	glDepthMask(GL_TRUE);
	// Restore original matrices 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void sanskrit_lettering(void)
{
	//code
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawSanskritQuote();

	// Do double buffering
	// SwapBuffers(ghdc);

}
/*
void update(void)
{
	// code
	
}

void uninitialize(void)
{
	// code
	// If exitting in fullscreen first restore and then proceed
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

	// Now destroy the rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// Release the device context
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// Destroy window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	// close Log File
	if (gpFile)
	{
		fprintf(gpFile, "Program Terminated Successfully !!\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

*/
