// Header Files
#include <windows.h>
#include <stdio.h>          // Used for log file --> FILE macro --> file I/O
#include <stdlib.h>      // used for exit(0);

#define _USE_MATH_DEFINES
#include <math.h>

// OpenGL related header files
#include <gl/GL.h>  // includes GL.h inside gl directory
//#include <gl/GLU.h>

// link with openGL import library
#pragma comment(lib,"OpenGL32.lib")

// Animation State Variables
float y_pos_SM = 12.0f;           // Starts high in the air
float y_vel_SM = -0.2f;           // Initial downward speed
float gravity_SM = -0.1f;        // gravity_SM pull

float tilt_angle_SM = 45.0f;     // Starts with a steep lean
float precess_angle_SM = 0.0f;   // The wobble sweeping around the floor
float precess_speed_SM = 0.03f;  // Initial wobble speed

float spin_angle_SM = 0.0f;      // The face spinning
float spin_speed_SM = 0.1f;    // Initial spin speed

BOOL is_flat_SM = FALSE;         // Flag to stop animation

// Camera State Variables
float cam_rot_x_SM = 20.0f;
float cam_y_SM = -5.0f;
float cam_z_SM = -25.0f;

//#pragma comment(lib,"GLU32.lib")
// Macros
//#define WIN_WIDTH 800
//#define WIN_HEIGHT 600

// global variable declarations
//HWND ghwnd = NULL;
//HDC ghdc = NULL;
//HGLRC ghrc = NULL;          // graphical library chya rendering context baddal info aslela handle
//BOOL bFullscreen = FALSE;
//DWORD dWStyle;
//WINDOWPLACEMENT wpPrev;
//FILE *gpFile = NULL;
//BOOL bActiveWindow = FALSE;
//BOOL bEscapeKeyIsPressed = FALSE;


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
		TEXT("RTR7 - Saurabh Tanaji Mane"),
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

*/

// -------------------------------------------------- HELPER FUNCTIONS ------------------------------------------------------------------------

void drawCircleOutline(float cx, float cy,float cz, float r, int segments)
{
	glBegin(GL_LINE_LOOP);          // Connects vertices in a continuous path, draws one final line from the last dot back to the first dot( A to B, B to C, C to D, and D back to A).
	for (int i = 0; i < segments; i++)
	{
		float angle = 2.0f * M_PI * i / segments;
		float x = cx + r * cos(angle);
		float y = cy + r * sin(angle);
		glVertex3f(x, y, cz);
	}
	glEnd();
}

void drawCurvedStrip(float centerX, float centerY,float centerZ, float width, float thickness, float curveAmount) {

	glBegin(GL_QUAD_STRIP);

	float halfWidth = width / 2.0f;
	float halfThickness = thickness / 2.0f;

	// Step across the width of the shape
	float step = width / 50.0f;

	for (float xOffset = -halfWidth; xOffset <= halfWidth + (step * 0.1f); xOffset += step) {


		float x = centerX + xOffset;

		// Calculate the curve based on the distance from the center
		// We normalize xOffset by halfWidth so the curve behaves consistently regardless of width
		float normalizedX = xOffset / halfWidth;
		float curveOffset = -curveAmount * (normalizedX * normalizedX);

		// Bottom vertex
		float bottomY = centerY - halfThickness + curveOffset;
		glVertex2f(x, bottomY);

		// Top vertex
		float topY = centerY + halfThickness + curveOffset;
		glVertex2f(x, topY);
	}

	glEnd();
}

void DrawCoin(float radius, float thickness, int slices)
{
	float halfThickness = thickness / 2.0f;

	glColor3f(0.35f, 0.16f, 0.03f);
	//  Top Face rim
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, halfThickness, 0.0f); // Center point
	for (int i = 0; i <= slices; i++) {
		float angle = i * 2.0f * M_PI / slices;
		glVertex3f(radius * cos(angle), halfThickness, radius * sin(angle));
	}
	glEnd();

	glColor3f(0.72f, 0.42f, 0.08f);
	// Top Face  - Flat circle pointing up
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, halfThickness+0.002f, 0.0f); // Center point
	for (int i = 0; i <= slices; i++) {
		float angle = i * 2.0f * M_PI / slices;
		glVertex3f(radius *0.9f* cos(angle), halfThickness+0.002f, radius*0.9f * sin(angle));
	}
	glEnd();

	glColor3f(0.35f, 0.16f, 0.03f);
	// Bottom Face - Flat circle pointing down
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, -halfThickness, 0.0f); // Center point
	// Drawn in reverse order so the face is visible if backface culling is turned on
	for (int i = slices; i >= 0; i--) {
		float angle = i * 2.0f * M_PI / slices;
		glVertex3f(radius * cos(angle), -halfThickness, radius * sin(angle));
	}
	glEnd();

	glColor3f(0.72f, 0.42f, 0.08f);
	// Bottom Face - Flat circle pointing down
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, -halfThickness-0.002f, 0.0f); // Center point
	// Drawn in reverse order so the face is visible if backface culling is turned on
	for (int i = slices; i >= 0; i--) {
		float angle = i * 2.0f * M_PI / slices;
		glVertex3f(radius *0.9f* cos(angle), -halfThickness-0.002f, radius*0.9f* sin(angle));
	}
	glEnd();

	glColor3f(0.7f, 0.5f, 0.0f);
	// 3. The Rim - Connecting the top and bottom circles
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= slices; i++) 
	{
		float angle = i * 2.0f * M_PI / slices;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		// Top vertex of the rim
		glVertex3f(x, halfThickness, z);
		// Bottom vertex of the rim
		glVertex3f(x, -halfThickness, z);
	}
	glEnd();
}

void drawAstroMediCompText(void)
{

	glPushMatrix();
	glTranslatef(0.05f, -0.10f, 0.002f);
	glScalef(0.8f, 1.0f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.35f, 0.19f, 0.04f);
	glVertex3f(0.43f, 0.4f, 0.0f);
	glVertex3f(0.38f, 0.35f, 0.0f);
	glVertex3f(0.41f, 0.33f, 0.0f);
	glVertex3f(0.42f, 0.3f, 0.0f);
	glVertex3f(0.44f, 0.28f, 0.0f);
	glVertex3f(0.42f, 0.23f, 0.0f);
	glVertex3f(0.43f, 0.4f, 0.0f);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.07f, 0.05f, 0.002f);
	glScalef(0.6f, 0.2f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.35f, 0.19f, 0.04f);
	glVertex2f(-0.62f, 0.48f);
	glVertex2f(-0.52f, 0.62f);
	glVertex2f(-0.40f, 0.65f);
	glVertex2f(-0.32f, 0.55f);
	glVertex2f(-0.43f, 0.45f);
	glVertex2f(-0.55f, 0.42f);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25f, -0.35f, 0.002f);
	glScalef(0.6f, 0.2f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.35f, 0.19f, 0.04f);
	glVertex2f(0.30f, -0.42f);
	glVertex2f(0.48f, -0.55f);
	glVertex2f(0.65f, -0.40f);
	glVertex2f(0.58f, -0.22f);
	glVertex2f(0.40f, -0.28f);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3f, 0.50f, 0.002f);
	glScalef(0.6f, 0.2f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.35f, 0.19f, 0.04f);
	glVertex2f(0.30f, -0.42f);
	glVertex2f(0.48f, -0.55f);
	glVertex2f(0.65f, -0.40f);
	glVertex2f(0.58f, -0.22f);
	glVertex2f(0.40f, -0.28f);
	glEnd();

	glPopMatrix();

	//Shadow of A letter /////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.28f, -0.41f, 0.002f);
	glScalef(0.4f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.45f, 0.6f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.4f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.25f, 0.6f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.41f, 0.75f, 0.0f);
	glVertex3f(-0.42f, 0.7f, 0.0f);
	glVertex3f(-0.28f, 0.7f, 0.0f);
	glVertex3f(-0.29f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	//A letter /////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.27f, -0.4f, 0.004f);
	glScalef(0.4f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.45f, 0.6f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.4f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.25f, 0.6f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.41f, 0.75f, 0.0f);
	glVertex3f(-0.42f, 0.7f, 0.0f);
	glVertex3f(-0.28f, 0.7f, 0.0f);
	glVertex3f(-0.29f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	//Shadow of S Letter /////////////////////////
	glPushMatrix();
	glTranslatef(-0.11f, -0.11f, 0.002f);
	glScalef(0.4f, 0.4f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.55f, 0.35f, 0.0f);
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.65f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.65f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.65f, 0.1f, 0.0f);
	glVertex3f(-0.6f, 0.1f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.65f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.56f, 0.4f, 0.0f);
	glVertex3f(-0.5f, 0.35f, 0.0f);
	glVertex3f(-0.56f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.65f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//S Letter /////////////////////////
	glPushMatrix();
	glTranslatef(-0.1f, -0.1f, 0.004f);
	glScalef(0.4f, 0.4f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.55f, 0.35f, 0.0f);
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.65f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.65f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.65f, 0.1f, 0.0f);
	glVertex3f(-0.6f, 0.1f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.65f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.56f, 0.4f, 0.0f);
	glVertex3f(-0.5f, 0.35f, 0.0f);
	glVertex3f(-0.56f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.65f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//Show of T Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.72f, 0.12f, 0.002f);
	glScalef(0.5f, 0.74f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.88f, -0.15f, 0.0f);
	glVertex3f(0.92f, -0.15f, 0.0f);
	glVertex3f(0.92f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.85f, -0.15f, 0.0f);
	glVertex3f(0.85f, -0.1f, 0.0f);
	glVertex3f(0.95f, -0.1f, 0.0f);
	glVertex3f(0.95f, -0.15f, 0.0f);
	glEnd();
	glPopMatrix();

	//T Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.71f, 0.13f, 0.004f);
	glScalef(0.5f, 0.74f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.88f, -0.15f, 0.0f);
	glVertex3f(0.92f, -0.15f, 0.0f);
	glVertex3f(0.92f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.85f, -0.15f, 0.0f);
	glVertex3f(0.85f, -0.1f, 0.0f);
	glVertex3f(0.95f, -0.1f, 0.0f);
	glVertex3f(0.95f, -0.15f, 0.0f);
	glEnd();
	glPopMatrix();

	//Shadow of R Letter //////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.37f, -0.1f, 0.002f);
	glScalef(0.35f, 0.37f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.55f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//R Letter //////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.36f, -0.09f, 0.004f);
	glScalef(0.35f, 0.37f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.55f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//Shadow of O Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.6f, 0.13f, 0.002f);
	glScalef(0.5f, 0.77f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.13f, 0.0f);
	glVertex3f(0.88f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.95f, -0.13f, 0.0f);
	glVertex3f(0.95f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.11f, 0.0f);
	glVertex3f(0.88f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.27f, 0.0f);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.27f, 0.0f);
	glEnd();

	glPopMatrix();

	//O Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.59f, 0.14f, 0.004f);
	glScalef(0.5f, 0.77f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.13f, 0.0f);
	glVertex3f(0.88f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.95f, -0.13f, 0.0f);
	glVertex3f(0.95f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.11f, 0.0f);
	glVertex3f(0.88f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.27f, 0.0f);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.27f, 0.0f);
	glEnd();

	glPopMatrix();

	//Shadow of M Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(0.22f, 0.0f, 0.002f);
	glScalef(0.35f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.9f, -0.2f, 0.0f);
	glVertex3f(-0.9f, 0.1f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.85f, -0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.85f, 0.02f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.75f, 0.02f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.7f, -0.2f, 0.0f);
	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.75f, -0.2f, 0.0f);
	glEnd();

	glPopMatrix();

	//M Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(0.23f, 0.01f, 0.004f);
	glScalef(0.35f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.002f);
	glVertex3f(-0.9f, -0.2f, 0.0f);
	glVertex3f(-0.9f, 0.1f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.85f, -0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.85f, 0.02f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.75f, 0.02f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.7f, -0.2f, 0.0f);
	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.75f, -0.2f, 0.0f);
	glEnd();

	glPopMatrix();

	//Shadow of E Letter /////////////////////////////
	glPushMatrix();
	glTranslatef(-0.07f, -0.1f, 0.002f);
	glScalef(0.3f, 0.38f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.2f, 0.4f, 0.0f);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.35f, 0.4f, 0.0f);
	glVertex3f(0.35f, 0.35f, 0.0f);
	glVertex3f(0.25f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.25f, 0.22f, 0.0f);
	glVertex3f(0.35f, 0.22f, 0.0f);
	glVertex3f(0.35f, 0.18f, 0.0f);
	glVertex3f(0.25f, 0.18f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.25f, 0.06f, 0.0f);
	glVertex3f(0.35f, 0.06f, 0.0f);
	glVertex3f(0.35f, 0.0f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//E Letter /////////////////////////////
	glPushMatrix();
	glTranslatef(-0.06f, -0.09f, 0.004f);
	glScalef(0.3f, 0.38f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.2f, 0.4f, 0.0f);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.35f, 0.4f, 0.0f);
	glVertex3f(0.35f, 0.35f, 0.0f);
	glVertex3f(0.25f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.25f, 0.22f, 0.0f);
	glVertex3f(0.35f, 0.22f, 0.0f);
	glVertex3f(0.35f, 0.18f, 0.0f);
	glVertex3f(0.25f, 0.18f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.25f, 0.06f, 0.0f);
	glVertex3f(0.35f, 0.06f, 0.0f);
	glVertex3f(0.35f, 0.0f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Shadow of D Letter //////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.05f, -0.1f, 0.002f);
	glScalef(0.4f, 0.39f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.0, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.04f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.04f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.09f, 0.0f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.04f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(0.04f, 0.4f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glVertex3f(0.0f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.13f, 0.35f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.03f, 0.35f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glVertex3f(0.13f, 0.35f, 0.0f);
	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glVertex3f(0.05f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.15f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glVertex3f(0.15f, 0.09f, 0.0f);
	glVertex3f(0.15f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//D Letter //////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.06f, -0.09f, 0.004f);
	glScalef(0.4f, 0.39f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.0, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.04f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.04f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.09f, 0.0f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.04f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(0.04f, 0.4f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glVertex3f(0.0f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.13f, 0.35f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.03f, 0.35f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glVertex3f(0.13f, 0.35f, 0.0f);
	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glVertex3f(0.05f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.15f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glVertex3f(0.15f, 0.09f, 0.0f);
	glVertex3f(0.15f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//Shadow of I letter ////////////////////////////
	glPushMatrix();
	glTranslatef(0.32f, -0.2f, 0.002f);
	glScalef(0.4f, 0.51f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.25f, 0.0f);
	glVertex3f(-0.35f, 0.25f, 0.0f);
	glVertex3f(-0.35f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.5f, 0.45f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.35f, 0.5f, 0.0f);
	glVertex3f(-0.35f, 0.45f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.45f, 0.25f, 0.0f);
	glVertex3f(-0.45f, 0.45f, 0.0f);
	glVertex3f(-0.4f, 0.45f, 0.0f);
	glVertex3f(-0.4f, 0.25f, 0.0f);
	glEnd();
	glPopMatrix();

	//I letter ////////////////////////////
	glPushMatrix();
	glTranslatef(0.33f, -0.19f, 0.004f);
	glScalef(0.4f, 0.51f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.25f, 0.0f);
	glVertex3f(-0.35f, 0.25f, 0.0f);
	glVertex3f(-0.35f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.5f, 0.45f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.35f, 0.5f, 0.0f);
	glVertex3f(-0.35f, 0.45f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.45f, 0.25f, 0.0f);
	glVertex3f(-0.45f, 0.45f, 0.0f);
	glVertex3f(-0.4f, 0.45f, 0.0f);
	glVertex3f(-0.4f, 0.25f, 0.0f);
	glEnd();
	glPopMatrix();

	//Shadow of c letter ////////////////////////////
	glPushMatrix();
	glTranslatef(0.33f, -0.07f, 0.002f);
	glScalef(0.35f, 0.51f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.38f, 0.2f, 0.0f);
	glVertex3f(-0.38f, 0.25f, 0.0f);
	glVertex3f(-0.25f, 0.25f, 0.0f);
	glVertex3f(-0.25f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.38f, 0.2f, 0.0f);
	glVertex3f(-0.38f, 0.0f, 0.0f);
	glVertex3f(-0.34f, 0.0f, 0.0f);
	glVertex3f(-0.34f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.38f, 0.0f, 0.0f);
	glVertex3f(-0.38f, -0.05f, 0.0f);
	glVertex3f(-0.25f, -0.05f, 0.0f);
	glVertex3f(-0.25f, 0.0f, 0.0f);
	glEnd();

	glPopMatrix();

	//c letter ////////////////////////////
	glPushMatrix();
	glTranslatef(0.34f, -0.06f, 0.004f);
	glScalef(0.35f, 0.51f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.38f, 0.2f, 0.0f);
	glVertex3f(-0.38f, 0.25f, 0.0f);
	glVertex3f(-0.25f, 0.25f, 0.0f);
	glVertex3f(-0.25f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.38f, 0.2f, 0.0f);
	glVertex3f(-0.38f, 0.0f, 0.0f);
	glVertex3f(-0.34f, 0.0f, 0.0f);
	glVertex3f(-0.34f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.38f, 0.0f, 0.0f);
	glVertex3f(-0.38f, -0.05f, 0.0f);
	glVertex3f(-0.25f, -0.05f, 0.0f);
	glVertex3f(-0.25f, 0.0f, 0.0f);
	glEnd();

	glPopMatrix();

	//Shadow of O Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.18f, 0.14f, 0.002f);
	glScalef(0.5f, 0.77f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.13f, 0.0f);
	glVertex3f(0.88f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.95f, -0.13f, 0.0f);
	glVertex3f(0.95f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.11f, 0.0f);
	glVertex3f(0.88f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.88f, -0.27f, 0.0f);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.27f, 0.0f);
	glEnd();

	glPopMatrix();

	//O Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.17f, 0.15f, 0.004f);
	glScalef(0.5f, 0.77f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.13f, 0.0f);
	glVertex3f(0.88f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.28f, 0.0f);
	glVertex3f(0.91f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.95f, -0.13f, 0.0f);
	glVertex3f(0.95f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.28f, 0.0f);
	glVertex3f(0.98f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.11f, 0.0f);
	glVertex3f(0.88f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.14f, 0.0f);
	glVertex3f(0.98f, -0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.88f, -0.27f, 0.0f);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.3f, 0.0f);
	glVertex3f(0.98f, -0.27f, 0.0f);
	glEnd();

	glPopMatrix();

	//Shadow of M Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(0.64f, 0.01f, 0.002f);
	glScalef(0.35f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.9f, -0.2f, 0.0f);
	glVertex3f(-0.9f, 0.1f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.85f, -0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.85f, 0.02f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.75f, 0.02f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(-0.7f, -0.2f, 0.0f);
	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.75f, -0.2f, 0.0f);
	glEnd();

	glPopMatrix();

	//M Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(0.65f, 0.02f, 0.004f);
	glScalef(0.35f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.9f, -0.2f, 0.0f);
	glVertex3f(-0.9f, 0.1f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.85f, -0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.85f, 0.02f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.75f, 0.02f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(-0.7f, -0.2f, 0.0f);
	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.75f, -0.2f, 0.0f);
	glEnd();

	glPopMatrix();

	//Shadow of P letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(0.25f, -0.09f, 0.002f);
	glScalef(0.4f, 0.39f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.08f, 0.04f, 0.01f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//P letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(0.26f, -0.08f, 0.004f);
	glScalef(0.4f, 0.39f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.65f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();

	glPopMatrix();

}

/*
int initialize(void)
{
	// function declarations
	void resize(int, int);

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	// code
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));       // ZeroMemory() also can be used
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);       // nSize is short int
	pfd.nVersion = 1;       // conventional
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;   // Red, Green, Blue, Alpha(transparency)
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
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);    // iPixelFormatIndex is 1-based 
	if (iPixelFormatIndex == 0)
		return(-2);

	if (SetPixelFormat(ghdc,iPixelFormatIndex,&pfd)==FALSE)
		return(-3);

	ghrc = wglCreateContext(ghdc);    // windows bridging API --> wgl
	if (ghrc == NULL)
		return(-4);

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)   // give charge of ghdc to ghrc and make it current context
		return(-5);

	// Enable depth
	glShadeModel(GL_SMOOTH);    
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	// choose screen clearing color as blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// warmup resize
	resize(WIN_WIDTH, WIN_HEIGHT);      // traditionally called

	return 0;
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;         // in future to avoid undefined/infinite issue
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);    // (GLsizei) --> openGL ne tharavlelya integer chya size la typecast kar width and height la

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective projection
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

*/

void coinFlip(void)
{

	glTranslatef(0.0f, cam_y_SM, cam_z_SM);
	glRotatef(cam_rot_x_SM, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glScalef(1.75f, 1.75f, 1.75f);
	// Move coin to its height
	glTranslatef(0.0f, y_pos_SM, 0.0f);

	// The sweeping wobble around the world Y axis
	glRotatef(precess_angle_SM, 0.0f, 1.0f, 0.0f);

	// The lean toward the floor 
	glRotatef(tilt_angle_SM, 1.0f, 0.0f, 0.0f);

	// The spin of the coin face itself 
	glRotatef(spin_angle_SM, 0.0f, 1.0f, 0.0f);

	DrawCoin(3.0f, 0.45f, 64);

	// --- AstroMediComp Text ---
	glPushMatrix();

	glTranslatef(0.0f, 0.227f, 0.0f);          // 0.227f added to slightly elevate text over coin

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	glScalef(5.0f, 5.0f, 5.0f);

	drawAstroMediCompText();

	glPopMatrix();


	glPopMatrix();
}

void UpdateCoinAnimation(float deltaTime)
{
	if (is_flat_SM)
	{
		// 1. Smoothly pan the camera to look straight down and zoom in
		cam_rot_x_SM += (90.0f - cam_rot_x_SM) * 0.05f * deltaTime;
		cam_y_SM += (0.0f - cam_y_SM) * 0.05f * deltaTime;
		cam_z_SM += (-14.0f - cam_z_SM) * 0.05f * deltaTime;

		// 2. Smoothly rotate the coin to face perfectly forward (0 or 360 degrees)

		// Align Spin Angle
		if (spin_angle_SM <= 180.0f) {
			spin_angle_SM -= spin_angle_SM * 0.06f * deltaTime;
		}
		else {
			spin_angle_SM += (360.0f - spin_angle_SM) * 0.06f * deltaTime;
		}

		// Align Precess Angle
		if (precess_angle_SM <= 180.0f) {
			precess_angle_SM -= precess_angle_SM * 0.06f * deltaTime;
		}
		else {
			precess_angle_SM += (360.0f - precess_angle_SM) * 0.06f * deltaTime;
		}

		return;
	}

	if (y_pos_SM > 0.0f || y_vel_SM > 0.0f)
	{
		y_vel_SM += gravity_SM * deltaTime;
		y_pos_SM += y_vel_SM * deltaTime;

		if (y_pos_SM <= 0.0f) {
			y_pos_SM = 0.0f;
			y_vel_SM = -y_vel_SM * 0.75f;

			if (y_vel_SM < 0.05f) y_vel_SM = 0.0f;
		}
	}
	else {
		if (tilt_angle_SM > 0.5f) {
			// Decays half as fast (takes longer to fall flat)
			tilt_angle_SM -= 0.42f * deltaTime;

			// Speeds up half as fast
			precess_speed_SM += 0.25f * deltaTime;

			// Slows down half as fast
			spin_speed_SM -= 0.002f * deltaTime;
			if (spin_speed_SM < 0.0f) spin_speed_SM = 0.0f;
		}
		else {
			tilt_angle_SM = 0.0f;
			is_flat_SM = TRUE;
		}
	}

	precess_angle_SM += precess_speed_SM * deltaTime;
	if (precess_angle_SM > 360.0f)
		precess_angle_SM -= 360.0f;

	spin_angle_SM += spin_speed_SM * deltaTime;
	if (spin_angle_SM > 360.0f)
		spin_angle_SM -= 360.0f;
}

//void render(void)
//{
//	//code
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // the actual screen clear task is done by this bit by bit
//
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//
//
//	// Do double buffering
//	SwapBuffers(ghdc);
//
//}

//void update(void)
//{
//	// code
//	float deltaTime = 0.010f;
//
//	// 3. Call the coin animation logic
//	UpdateCoinAnimation(deltaTime);
//}

/*
void uninitialize(void)
{
	// code
	// If exitting in fullscreen first restore to original and then proceed
	if (bFullscreen == TRUE)
	{
		toggleFullscreen();
		bFullscreen = FALSE;
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

