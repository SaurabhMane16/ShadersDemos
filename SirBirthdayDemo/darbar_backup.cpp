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
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLU32.lib")

/*
// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;          // graphical library chya rendering context baddal info aslela handle
BOOL bFullscreen = FALSE;
DWORD dWStyle;
WINDOWPLACEMENT wpPrev;
FILE *gpFile = NULL;
BOOL bActiveWindow = FALSE;
BOOL bEscapeKeyIsPressed = FALSE;

*/
// --- Animation State Variables ---
float doorAngle = 0.0f; // 0 to 90 degrees
float chanakyaZ = -45.0f; 
int sceneState = 0; // 0: Closed door wait, 1: Opening door, 2: Chanakya walks in, 3: Chanakya stops
float sceneTimer = 0.0f;
DWORD rlLastFrameTime = 0;
// ---------------------------------

// Character Animation Mode 
int rlAnimMode = 0;             // 0 = Pointing Stance, 1 = Walking Cycle, 2 = Angry Speech
BOOL rlShowFloatingCloth = FALSE; // FALSE for clean front view

float rlAnimTime = 0.0f;
float rlLeftShoulderPitch = 0.0f;   // Pitch around X-axis (Matches legs!)
float rlRightShoulderPitch = 0.0f;  // Pitch around X-axis (Matches legs!)
float rlLeftShoulderRoll = 125.0f;   // Z-axis rotation (For Pointing pose)
float rlRightShoulderRoll = 0.0f;
float rlLeftElbowAngle = -15.0f;
float rlRightElbowAngle	 = 10.0f;

float rlLeftHipAngle = 0.0f;
float rlRightHipAngle = 0.0f;
float rlLeftKneeAngle = 0.0f;
float rlRightKneeAngle = 0.0f;

float rlEyebrowSlantY = 0.24f;
float rlMouthOpenHeight = 0.0f;
float rlHipBobY = 0.0f;

// Mathematical Helper Function Prototypes
void drawFilledEllipse(float cx, float cy, float rx, float ry, float zVal, float r, float g, float b, int segments);
void drawEllipseOutline(float cx, float cy, float rx, float ry, float zVal, float lineWidth, float r, float g, float b, int segments);
void drawArc(float cx, float cy, float rx, float ry, float zVal, float startAngle, float endAngle, float lineWidth, float r, float g, float b, int segments);
void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float zVal, float r, float g, float b);
void drawFilledQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float zVal, float r, float g, float b);
void drawRudrakshaMala(float cx, float cy, float rx, float ry, float zVal, int beadCount);

// Chanakya FFP Rendering Modules
void drawNeck(void);
void drawHeadAndFace(void);
void drawFlowingShikhaHair(float timeVal);
void drawTorsoAndChest(void);
void drawLeftArm(void);
void drawRightArm(void);
void drawDhotiAndLegs(void);
void drawFlowingAngavastram(float timeVal);
void drawChanakyaCharacter(void);

void rlDrawSoliderEx(float xPosition, float yPosition, float zPosition,
                     float scaleX, float scaleY, float scaleZ,
                     float rotationAngleYDegrees,
                     int bHoldSpearInRightHand);

void rlDreawDarbariEx(float xPosition, float yPosition, float zPosition,
                      float scaleX, float scaleY, float scaleZ,
                      float rotationAngleYDegrees,
                      int robeColorIndex);
					  
void drawCircleborder(float cx, float cy,float cz, float r, int segments);
void drawCurvedLine(float centerX, float centerY,float centerZ, float width, float thickness, float curveAmount);
void updateOfDarbar(void);

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
		TEXT("RTR7 - Saurabh Tanaji Mane : Scene 2"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		screenWidth / 2 - WIN_WIDTH / 2,
		screenheight / 2 - WIN_HEIGHT / 2,
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

				DWORD rlCurrentTime = GetTickCount();
				if ((rlCurrentTime - rlLastFrameTime) >= 16)
				{
					// render
					render();

					// update
					update();
					rlLastFrameTime = rlCurrentTime;
				}
			}
		}
	}

	// uninitialize
	uninitialize();

	return((int)msg.wParam);

}
/*
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
*/

// MATHEMATICAL PRIMITIVE HELPER FUNCTIONS (FFP

void drawFilledEllipse(float cx, float cy, float rx, float ry, float zVal, float r, float g, float b, int segments)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, cy, zVal);
    for (int rlIndex = 0; rlIndex <= segments; rlIndex++)
    {
        float rlTheta = 2.0f * (float)M_PI * (float)rlIndex / (float)segments;
        float rlX = cx + rx * cosf(rlTheta);
        float rlY = cy + ry * sinf(rlTheta);
        glVertex3f(rlX, rlY	, zVal);
    }
    glEnd();
}

void drawEllipseOutline(float cx, float cy, float rx, float ry, float zVal, float lineWidth, float r, float g, float b, int segments)
{
    glLineWidth(lineWidth);
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int rlIndex = 0; rlIndex < segments; rlIndex++)
    {
        float rlTheta = 2.0f * (float)M_PI * (float)rlIndex / (float)segments;
        float rlX = cx + rx * cosf(rlTheta);
        float rlY = cy + ry * sinf(rlTheta);
        glVertex3f(rlX, rlY, zVal);
    }
    glEnd();
    glLineWidth(1.0f);
}

void drawArc(float cx, float cy, float rx, float ry, float zVal, float startAngle, float endAngle, float lineWidth, float r, float g, float b, int segments)
{
    glLineWidth(lineWidth);
    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);
    float startRad = startAngle * (float)M_PI / 180.0f;
    float endRad = endAngle * (float)M_PI / 180.0f;
    for (int rlIndex = 0; rlIndex <= segments; rlIndex++)
    {
        float rlTheta = startRad + (endRad - startRad) * ((float)rlIndex / (float)segments);
        float rlX = cx + rx * cosf(rlTheta);
        float rlY = cy + ry * sinf(rlTheta);
        glVertex3f(rlX, rlY, zVal);
    }
    glEnd();
    glLineWidth(1.0f);
}

void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float zVal, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex3f(x1, y1, zVal);
    glVertex3f(x2, y2, zVal);
    glVertex3f(x3, y3, zVal);
    glEnd();
}

void drawFilledQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float zVal, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, zVal);
    glVertex3f(x2, y2, zVal);
    glVertex3f(x3, y3, zVal);
    glVertex3f(x4, y4, zVal);
    glEnd();
}

void drawRudrakshaMala(float cx, float cy, float rx, float ry, float zVal, int beadCount)
{
    float rlStartAngle = 200.0f;
    float rlEndAngle = 340.0f;
    float rlStartRad = rlStartAngle * (float)M_PI / 180.0f;
    float rlEndRad = rlEndAngle * (float)M_PI / 180.0f;

    // Golden Silk Thread Line connecting beads
    glLineWidth(2.0f);
    glColor3f(0.85f, 0.65f, 0.15f);
    glBegin(GL_LINE_STRIP);
    for (int rlIndex = 0; rlIndex <= 30; rlIndex++)
    {
        float rlTheta = rlStartRad + (rlEndRad - rlStartRad) * ((float)rlIndex / 30.0f);
        float rlX = cx + rx * cosf(rlTheta);
        float rlY = cy + ry * sinf(rlTheta);
        glVertex3f(rlX, rlY, zVal - 0.002f);
    }
    glEnd();
    glLineWidth(1.0f);

    // Individual Rudraksha Beads along U-arc
    for (int rlIndex = 0; rlIndex < beadCount; rlIndex++)
    {
        float rlT = (float)rlIndex / (float)(beadCount - 1);
        float rlTheta = rlStartRad + (rlEndRad - rlStartRad) * rlT;
        float rlBeadX = cx + rx * cosf(rlTheta);
        float rlBeadY = cy + ry * sinf(rlTheta);

        // Rudraksha main bead (Warm textured brown sphere)
        drawFilledEllipse(rlBeadX, rlBeadY, 0.038f, 0.038f, zVal, 0.48f, 0.18f, 0.08f, 12);
        // Saffron/Gold highlight dot
        drawFilledEllipse(rlBeadX - 0.008f, rlBeadY + 0.008f, 0.012f, 0.012f, zVal + 0.003f, 0.78f, 0.42f, 0.18f, 8);
    }

    // Central Guru Bead (Sumeru Mani) at lowest point
    float rlGuruX = cx;
    float rlGuruY = cy - ry;
    drawFilledEllipse(rlGuruX, rlGuruY, 0.055f, 0.055f, zVal + 0.005f, 0.55f, 0.22f, 0.08f, 16);
    drawFilledEllipse(rlGuruX - 0.01f, rlGuruY + 0.01f, 0.018f, 0.018f, zVal + 0.008f, 0.85f, 0.50f, 0.20f, 10);

    // Red Tassel Threads dangling from Guru Bead
    glLineWidth(2.5f);
    glColor3f(0.88f, 0.12f, 0.05f);
    glBegin(GL_LINES);
    glVertex3f(rlGuruX, rlGuruY - 0.055f, zVal + 0.006f);
    glVertex3f(rlGuruX - 0.02f, rlGuruY - 0.12f, zVal + 0.006f);

    glVertex3f(rlGuruX, rlGuruY - 0.055f, zVal + 0.006f);
    glVertex3f(rlGuruX, rlGuruY - 0.13f, zVal + 0.006f);
    glVertex3f(rlGuruX, rlGuruY - 0.055f, zVal + 0.006f);
    glVertex3f(rlGuruX + 0.02f, rlGuruY - 0.12f, zVal + 0.006f);
    glEnd();
    glLineWidth(1.0f);
}

// 1. PROPORTIONAL NECK MODULE (Skin Tone with Muscle Lines & Adam's Apple)
void drawNeck(void)
{
    // Muscular Neck Column (Jaw base Y=0.42f down to shoulder notch Y=-0.05f)
    drawFilledQuad(-0.16f, 0.42f,  0.16f, 0.42f,  0.24f, -0.05f, -0.24f, -0.05f, 0.01f, 0.86f, 0.66f, 0.48f);
    
    // Throat Center Contour Shadow
    drawFilledQuad(-0.04f, 0.40f, 0.04f, 0.40f, 0.06f, -0.05f, -0.06f, -0.05f, 0.012f, 0.82f, 0.62f, 0.44f);

    // Adam's Apple (Laryngeal Prominence)
    drawFilledEllipse(0.0f, 0.22f, 0.045f, 0.065f, 0.015f, 0.88f, 0.68f, 0.50f, 16);
    drawArc(0.0f, 0.20f, 0.045f, 0.03f, 0.016f, 190.0f, 350.0f, 1.8f, 0.74f, 0.54f, 0.36f, 12);

    // Sternocleidomastoid Tendon Muscle Lines (Neck to Clavicle Notch)
    glLineWidth(2.0f);
    glColor3f(0.74f, 0.54f, 0.36f);
    glBegin(GL_LINES);
    glVertex3f(-0.14f, 0.38f, 0.015f);
    glVertex3f(-0.03f, -0.05f, 0.015f);

    glVertex3f(0.14f, 0.38f, 0.015f);
    glVertex3f(0.03f, -0.05f, 0.015f);
    glEnd();
    glLineWidth(1.0f);
}

// 2. REFINED HEAD & FACIAL ANATOMY MODULE (Heroic Proportions)
void drawHeadAndFace(void)
{
    // Scaled head for heroic body proportions
    drawFilledEllipse(0.0f, 0.08f, 0.44f, 0.56f, 0.02f, 0.90f, 0.70f, 0.52f, 60);
    drawFilledEllipse(0.0f, -0.18f, 0.35f, 0.35f, 0.02f, 0.88f, 0.68f, 0.50f, 50); // Jaw taper

    // Left & Right Ears with Inner Folds
    drawFilledEllipse(-0.46f, 0.06f, 0.09f, 0.16f, 0.01f, 0.84f, 0.63f, 0.45f, 30);
    drawArc(-0.46f, 0.06f, 0.05f, 0.10f, 0.015f, 40.0f, 320.0f, 1.5f, 0.72f, 0.52f, 0.36f, 15);

    drawFilledEllipse(0.46f, 0.06f, 0.09f, 0.16f, 0.01f, 0.84f, 0.63f, 0.45f, 30);
    drawArc(0.46f, 0.06f, 0.05f, 0.10f, 0.015f, 220.0f, 140.0f, 1.5f, 0.72f, 0.52f, 0.36f, 15);

    // Chin Cleft & Jaw Shadow Contour
    drawArc(0.0f, -0.36f, 0.08f, 0.04f, 0.03f, 200.0f, 340.0f, 1.8f, 0.74f, 0.54f, 0.36f, 15);

    // Forehead Tilak (Chandan U-Shape + Saffron Red Strip + Central Red Bindu)
    drawFilledQuad(-0.09f, 0.44f, 0.09f, 0.44f, 0.06f, 0.22f, -0.06f, 0.22f, 0.04f, 0.95f, 0.95f, 0.90f);
    drawFilledQuad(-0.035f, 0.42f, 0.035f, 0.42f, 0.02f, 0.23f, -0.02f, 0.23f, 0.05f, 0.88f, 0.12f, 0.05f);
    drawFilledEllipse(0.0f, 0.21f, 0.03f, 0.04f, 0.06f, 0.90f, 0.10f, 0.05f, 20);

    // Eyebrows
    glLineWidth(3.5f);
    glColor3f(0.12f, 0.08f, 0.05f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.32f, 0.20f, 0.06f);
    glVertex3f(-0.18f, 0.26f, 0.06f);
    glVertex3f(-0.04f, rlEyebrowSlantY - 0.04f, 0.06f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(0.04f, rlEyebrowSlantY - 0.04f, 0.06f);
    glVertex3f(0.18f, 0.26f, 0.06f);
    glVertex3f(0.32f, 0.20f, 0.06f);
    glEnd();
    glLineWidth(1.0f);

    // Eyes with Pupil Glint
    drawFilledEllipse(-0.17f, 0.12f, 0.085f, 0.055f, 0.05f, 0.98f, 0.98f, 0.96f, 25);
    drawFilledEllipse(-0.16f, 0.12f, 0.045f, 0.045f, 0.07f, 0.22f, 0.12f, 0.08f, 20);
    drawFilledEllipse(-0.16f, 0.12f, 0.022f, 0.022f, 0.08f, 0.02f, 0.02f, 0.02f, 15);
    drawFilledEllipse(-0.145f, 0.135f, 0.008f, 0.008f, 0.09f, 1.0f, 1.0f, 1.0f, 10); // Pupil reflection
    drawArc(-0.17f, 0.12f, 0.085f, 0.055f, 0.09f, 10.0f, 170.0f, 2.0f, 0.20f, 0.12f, 0.08f, 20);

    drawFilledEllipse(0.17f, 0.12f, 0.085f, 0.055f, 0.05f, 0.98f, 0.98f, 0.96f, 25);
    drawFilledEllipse(0.16f, 0.12f, 0.045f, 0.045f, 0.07f, 0.22f, 0.12f, 0.08f, 20);
    drawFilledEllipse(0.16f, 0.12f, 0.022f, 0.022f, 0.08f, 0.02f, 0.02f, 0.02f, 15);
    drawFilledEllipse(0.175f, 0.135f, 0.008f, 0.008f, 0.09f, 1.0f, 1.0f, 1.0f, 10); // Pupil reflection
    drawArc(0.17f, 0.12f, 0.085f, 0.055f, 0.09f, 10.0f, 170.0f, 2.0f, 0.20f, 0.12f, 0.08f, 20);

    // Nose
    drawFilledTriangle(0.0f, 0.15f, -0.045f, -0.07f, 0.045f, -0.07f, 0.05f, 0.82f, 0.60f, 0.42f);
    drawFilledEllipse(0.0f, -0.07f, 0.055f, 0.035f, 0.06f, 0.86f, 0.64f, 0.46f, 20);

    // Lips
    drawFilledTriangle(0.0f, -0.18f, -0.12f, -0.23f, 0.12f, -0.23f, 0.06f, 0.72f, 0.35f, 0.30f);
    drawFilledEllipse(0.0f, -0.25f - rlMouthOpenHeight, 0.10f, 0.035f + rlMouthOpenHeight, 0.06f, 0.76f, 0.38f, 0.32f, 25);
}

// 3. SHIKHA HAIR MODULE (With scalp knot tie)
void drawFlowingShikhaHair(float timeVal)
{
    // Hair Tie Ring at Base of Shikha
    drawFilledEllipse(-0.30f, 0.48f, 0.05f, 0.05f, 0.05f, 0.85f, 0.15f, 0.08f, 16);

    drawFilledEllipse(-0.30f, 0.50f, 0.09f, 0.08f, 0.03f, 0.15f, 0.08f, 0.05f, 25);
    drawFilledEllipse(-0.40f, 0.60f, 0.11f, 0.12f, 0.04f, 0.10f, 0.06f, 0.04f, 30);

    glLineWidth(3.5f);
    glColor3f(0.12f, 0.08f, 0.05f);
    glBegin(GL_LINE_STRIP);
    for (int rlIndex = 0; rlIndex < 8; rlIndex++)
    {
        float rlXPos = -0.46f - (float)rlIndex * 0.12f;
        float rlWaveY = 0.64f + 0.05f * sinf(timeVal * 2.0f + (float)rlIndex * 0.5f);
        glVertex3f(rlXPos, rlWaveY, 0.04f);
    }
    glEnd();
    glLineWidth(1.0f);
}

// 4. IMPROVISED BARE TORSO & MUSCULAR CHEST MODULE
void drawTorsoAndChest(void)
{
    // Torso Contour (Broad shoulder taper to waist)
    drawFilledQuad(-0.54f, 0.0f,  0.54f, 0.0f,  0.42f, -1.35f, -0.42f, -1.35f, 0.0f, 0.86f, 0.66f, 0.48f);

    // Shoulder Deltoid Caps
    drawFilledEllipse(-0.52f, -0.08f, 0.14f, 0.18f, 0.005f, 0.84f, 0.64f, 0.46f, 25);
    drawFilledEllipse(0.52f, -0.08f, 0.14f, 0.18f, 0.005f, 0.84f, 0.64f, 0.46f, 25);

    // Collarbone Lines (Clavicle)
    glLineWidth(2.0f);
    glColor3f(0.72f, 0.52f, 0.36f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.45f, -0.05f, 0.01f);
    glVertex3f(-0.15f, -0.12f, 0.01f);
    glVertex3f(0.0f, -0.14f, 0.01f);
    glVertex3f(0.15f, -0.12f, 0.01f);
    glVertex3f(0.45f, -0.05f, 0.01f);
    glEnd();
    glLineWidth(1.0f);

    // Pectoral Muscle Outline & Shading
    drawArc(-0.20f, -0.32f, 0.22f, 0.14f, 0.01f, 190.0f, 350.0f, 2.0f, 0.72f, 0.52f, 0.36f, 20);
    drawArc(0.20f, -0.32f, 0.22f, 0.14f, 0.01f, 190.0f, 350.0f, 2.0f, 0.72f, 0.52f, 0.36f, 20);

    // Abdominal Division Line Shading
    drawArc(0.0f, -0.65f, 0.12f, 0.08f, 0.015f, 180.0f, 360.0f, 1.5f, 0.74f, 0.54f, 0.36f, 15);
    drawArc(0.0f, -0.90f, 0.10f, 0.06f, 0.015f, 180.0f, 360.0f, 1.5f, 0.74f, 0.54f, 0.36f, 15);

    // Rudraksha Necklace
    drawRudrakshaMala(0.0f, -0.15f, 0.32f, 0.24f, 0.03f, 14);

    // White Janeu Sacred Thread with Sacred Knot (Granthi)
    glLineWidth(2.5f);
    glColor3f(0.96f, 0.96f, 0.92f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.30f, 0.0f, 0.04f);
    glVertex3f(-0.04f, -0.55f, 0.04f);
    glVertex3f(0.32f, -1.30f, 0.04f);
    glEnd();
    glLineWidth(1.0f);
    drawFilledEllipse(-0.04f, -0.55f, 0.025f, 0.025f, 0.045f, 1.0f, 1.0f, 0.95f, 12); // Janeu Knot

    // Dhoti Waistband Sash (Kamarbandh)
    drawFilledQuad(-0.46f, -1.25f,  0.46f, -1.25f,  0.44f, -1.35f, -0.44f, -1.35f, 0.03f, 0.88f, 0.12f, 0.05f);
}

// 5. LEFT ARM MODULE (With Pointing Finger Gesture & Wrist Bracelet)
void drawLeftArm(void)
{
    glPushMatrix();
        glTranslatef(0.50f, -0.05f, 0.0f);
        glRotatef(rlLeftShoulderPitch, 1.0f, 0.0f, 0.0f);
        glRotatef(rlLeftShoulderRoll, 0.0f, 0.0f, 1.0f);

        drawFilledQuad(-0.09f, 0.0f,  0.09f, 0.0f,  0.07f, -0.55f, -0.07f, -0.55f, 0.01f, 0.86f, 0.66f, 0.48f);
        drawRudrakshaMala(0.0f, -0.30f, 0.085f, 0.04f, 0.03f, 6);

        glPushMatrix();
            glTranslatef(0.0f, -0.55f, 0.0f);
            glRotatef(rlLeftElbowAngle, 1.0f, 0.0f, 0.0f);
            
            drawFilledQuad(-0.075f, 0.0f,  0.075f, 0.0f,  0.065f, -0.50f, -0.065f, -0.50f, 0.01f, 0.86f, 0.66f, 0.48f);
            
            // Wrist Rudraksha Bracelet
            drawRudrakshaMala(0.0f, -0.48f, 0.075f, 0.035f, 0.03f, 6);

            // Palm Base
            drawFilledEllipse(0.0f, -0.56f, 0.08f, 0.07f, 0.02f, 0.84f, 0.63f, 0.45f, 20);

            // Pointing Index Finger
            drawFilledQuad(-0.02f, -0.56f,  0.025f, -0.56f,  0.025f, -0.80f, -0.02f, -0.80f, 0.025f, 0.84f, 0.63f, 0.45f);
            drawFilledEllipse(0.0025f, -0.80f, 0.022f, 0.025f, 0.026f, 0.84f, 0.63f, 0.45f, 12);
            drawFilledEllipse(0.0025f, -0.81f, 0.012f, 0.010f, 0.027f, 0.94f, 0.80f, 0.70f, 10); // Fingernail

            // Curled Fingers (Middle, Ring, Pinky)
            drawFilledEllipse(-0.04f, -0.60f, 0.025f, 0.035f, 0.022f, 0.78f, 0.58f, 0.40f, 12);
            drawFilledEllipse(-0.06f, -0.58f, 0.022f, 0.030f, 0.022f, 0.76f, 0.56f, 0.38f, 12);

            // Thumb
            drawFilledEllipse(0.05f, -0.56f, 0.03f, 0.025f, 0.022f, 0.80f, 0.60f, 0.42f, 12);
        glPopMatrix();
    glPopMatrix();
}

// 6. RIGHT ARM MODULE (With Wrist Bracelet)
void drawRightArm(void)
{
    glPushMatrix();
        glTranslatef(-0.50f, -0.05f, 0.0f);
        glRotatef(rlRightShoulderPitch, 1.0f, 0.0f, 0.0f);
        glRotatef(rlRightShoulderRoll, 0.0f, 0.0f, 1.0f);

        drawFilledQuad(-0.09f, 0.0f,  0.09f, 0.0f,  0.07f, -0.55f, -0.07f, -0.55f, 0.01f, 0.84f, 0.64f, 0.46f);
        drawRudrakshaMala(0.0f, -0.30f, 0.085f, 0.04f, 0.03f, 6);

        glPushMatrix();
            glTranslatef(0.0f, -0.55f, 0.0f);
            glRotatef(rlRightElbowAngle, 1.0f, 0.0f, 0.0f);
            
            drawFilledQuad(-0.075f, 0.0f,  0.075f, 0.0f,  0.065f, -0.50f, -0.065f, -0.50f, 0.01f, 0.84f, 0.64f, 0.46f);
            
            // Wrist Rudraksha Bracelet
            drawRudrakshaMala(0.0f, -0.48f, 0.075f, 0.035f, 0.03f, 6);

            // Right Hand Palm & Relaxed Fingers
            drawFilledEllipse(0.0f, -0.56f, 0.08f, 0.08f, 0.02f, 0.82f, 0.60f, 0.42f, 20);
            drawFilledEllipse(-0.03f, -0.63f, 0.022f, 0.030f, 0.022f, 0.78f, 0.58f, 0.40f, 10);
            drawFilledEllipse(0.0f, -0.65f, 0.022f, 0.035f, 0.022f, 0.78f, 0.58f, 0.40f, 10);
            drawFilledEllipse(0.03f, -0.63f, 0.020f, 0.030f, 0.022f, 0.78f, 0.58f, 0.40f, 10);
        glPopMatrix();
    glPopMatrix();
}

// 7. IMPROVISED CONTOURED DHOTI & TAILORED LEGS MODULE (With Anatomical Toes & Ankle Joint)
void drawDhotiAndLegs(void)
{
    // Tapered Yellow/Ochre Dhoti Main Draping Fold (Organic waist-to-knee taper)
    drawFilledQuad(-0.48f, -1.30f,  0.48f, -1.30f,  0.38f, -2.60f, -0.38f, -2.60f, 0.02f, 0.92f, 0.72f, 0.15f);
    
    // Center Drapery Pleat Fold Shading
    drawFilledQuad(-0.10f, -1.30f,  0.10f, -1.30f,  0.05f, -2.60f, -0.05f, -2.60f, 0.03f, 0.82f, 0.60f, 0.10f);
    
    // Dhoti Pleat Fold Curves (Organic fabric lines)
    drawArc(-0.18f, -1.85f, 0.24f, 0.40f, 0.035f, 280.0f, 350.0f, 1.8f, 0.78f, 0.56f, 0.10f, 15);
    drawArc(0.18f, -1.85f, 0.24f, 0.40f, 0.035f, 190.0f, 260.0f, 1.8f, 0.78f, 0.56f, 0.10f, 15);

    // Bottom Dhoti Red Border Trim
    drawFilledQuad(-0.38f, -2.60f,  0.38f, -2.60f,  0.36f, -2.72f, -0.36f, -2.72f, 0.04f, 0.85f, 0.10f, 0.08f);

    // Left Leg & Calf Taper with Foot Toes & Ankle Bone
    glPushMatrix();
        glTranslatef(-0.18f, -2.70f, 0.0f);
        glRotatef(rlLeftHipAngle, 1.0f, 0.0f, 0.0f);
        drawFilledQuad(-0.075f, 0.0f,  0.075f, 0.0f,  0.06f, -0.65f, -0.06f, -0.65f, 0.01f, 0.86f, 0.66f, 0.48f);
        
        // Ankle Bone Highlight (Malleolus)
        drawFilledEllipse(-0.07f, -0.62f, 0.025f, 0.025f, 0.015f, 0.90f, 0.72f, 0.54f, 12);

        // Bare Foot Base
        drawFilledEllipse(-0.01f, -0.70f, 0.10f, 0.055f, 0.02f, 0.84f, 0.63f, 0.45f, 20);

        // 5 Individual Toes on Left Foot
        drawFilledEllipse(0.06f, -0.73f, 0.025f, 0.025f, 0.025f, 0.84f, 0.63f, 0.45f, 10);  // Big Toe
        drawFilledEllipse(0.02f, -0.74f, 0.020f, 0.020f, 0.025f, 0.84f, 0.63f, 0.45f, 10);  // 2nd Toe
        drawFilledEllipse(-0.02f, -0.74f, 0.018f, 0.018f, 0.025f, 0.84f, 0.63f, 0.45f, 10); // 3rd Toe
        drawFilledEllipse(-0.05f, -0.73f, 0.016f, 0.016f, 0.025f, 0.84f, 0.63f, 0.45f, 10); // 4th Toe
        drawFilledEllipse(-0.08f, -0.72f, 0.014f, 0.014f, 0.025f, 0.84f, 0.63f, 0.45f, 10); // Pinky Toe
    glPopMatrix();

    // Right Leg & Calf Taper with Foot Toes & Ankle Bone
    glPushMatrix();
        glTranslatef(0.18f, -2.70f, 0.0f);
        glRotatef(rlRightHipAngle, 1.0f, 0.0f, 0.0f);
        drawFilledQuad(-0.075f, 0.0f,  0.075f, 0.0f,  0.06f, -0.65f, -0.06f, -0.65f, 0.01f, 0.86f, 0.66f, 0.48f);
        
        // Ankle Bone Highlight (Malleolus)
        drawFilledEllipse(0.07f, -0.62f, 0.025f, 0.025f, 0.015f, 0.90f, 0.72f, 0.54f, 12);

        // Bare Foot Base
        drawFilledEllipse(0.01f, -0.70f, 0.10f, 0.055f, 0.02f, 0.84f, 0.63f, 0.45f, 20);

        // 5 Individual Toes on Right Foot
        drawFilledEllipse(-0.06f, -0.73f, 0.025f, 0.025f, 0.025f, 0.84f, 0.63f, 0.45f, 10); // Big Toe
        drawFilledEllipse(-0.02f, -0.74f, 0.020f, 0.020f, 0.025f, 0.84f, 0.63f, 0.45f, 10); // 2nd Toe
        drawFilledEllipse(0.02f, -0.74f, 0.018f, 0.018f, 0.025f, 0.84f, 0.63f, 0.45f, 10);  // 3rd Toe
        drawFilledEllipse(0.05f, -0.73f, 0.016f, 0.016f, 0.025f, 0.84f, 0.63f, 0.45f, 10);  // 4th Toe
        drawFilledEllipse(0.08f, -0.72f, 0.014f, 0.014f, 0.025f, 0.84f, 0.63f, 0.45f, 10);  // Pinky Toe
    glPopMatrix();
}

// 8. CONTOURED ANGAVASTRAM (SHOULDER CLOTH) MODULE
void drawFlowingAngavastram(float timeVal)
{
    // Diagonal Shoulder Draped Portion (Slightly curved chest wrap)
    drawFilledQuad(-0.52f, 0.02f, -0.22f, 0.06f,  0.42f, -1.32f,  0.22f, -1.36f, 0.05f, 0.65f, 0.42f, 0.18f);

    // Decorative Red Accent Border Trim along shoulder drape edge
    glLineWidth(2.5f);
    glColor3f(0.85f, 0.10f, 0.08f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.52f, 0.02f, 0.06f);
    glVertex3f(-0.22f, 0.06f, 0.06f);
    glVertex3f(0.42f, -1.32f, 0.06f);
    glEnd();
    glLineWidth(1.0f);

    if (rlShowFloatingCloth == TRUE)
    {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.68f, 0.45f, 0.20f);
        for (int rlIndex = 0; rlIndex <= 8; rlIndex++)
        {
            float rlXPos = -0.52f - (float)rlIndex * 0.13f;
            float rlWaveY = -0.15f + 0.07f * sinf(timeVal * 2.5f + (float)rlIndex * 0.4f);
            float rlWidth = 0.26f - (float)rlIndex * 0.012f;

            glVertex3f(rlXPos, rlWaveY + rlWidth, 0.06f);
            glVertex3f(rlXPos, rlWaveY - rlWidth, 0.06f);
        }
        glEnd();

        glLineWidth(3.0f);
        glColor3f(0.85f, 0.10f, 0.08f);
        glBegin(GL_LINE_STRIP);
        for (int rlIndex = 0; rlIndex <= 8; rlIndex++)
        {
            float rlXPos = -0.52f - (float)rlIndex * 0.13f;
            float rlWaveY = -0.15f + 0.07f * sinf(timeVal * 2.5f + (float)rlIndex * 0.4f);
            glVertex3f(rlXPos, rlWaveY - (0.26f - (float)rlIndex * 0.012f), 0.07f);
        }
        glEnd();
        glLineWidth(1.0f);
    }
}

// MASTER PIPELINE: FULL-BODY ANIMATABLE CHANAKYA CHARACTER
void drawChanakyaCharacter(void)
{
    glPushMatrix();
        glTranslatef(0.0f, 0.45f + rlHipBobY, 0.0f);
        glScalef(0.82f, 0.82f, 0.82f);

        drawTorsoAndChest();
        drawNeck();
        drawDhotiAndLegs();
        drawRightArm();
        drawLeftArm();

        glPushMatrix();
            glTranslatef(0.0f, 0.60f, 0.0f); // Proportional head placement atop neck
            drawHeadAndFace();
            //drawFlowingShikhaHair(rlAnimTime);
        glPopMatrix();

        drawFlowingAngavastram(rlAnimTime);

    glPopMatrix();
}


/*
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

void drawCircleborder(float cx, float cy,float cz, float r, int segments)
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

void drawCurvedLine(float centerX, float centerY,float centerZ, float width, float thickness, float curveAmount) {

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

void drawPillar(void)
{
	float topY = 2.8f;
	float bottomY = -2.2f;

	float topOuterLeft = -0.40f;
	float topOuterRight = 0.40f;
	float bottomOuterLeft = -0.50f;
	float bottomOuterRight = 0.50f;

	glPushMatrix();
	glScalef(0.7f, 0.7f, 0.7f);

	// 1. MAIN PILLAR BODY (No GL_LINE_LOOP outline)
	glBegin(GL_QUADS);

	// Left Edge (Darker for shadow)
	glColor3f(0.30f, 0.07f, 0.05f);
	glVertex3f(topOuterLeft, topY, 0.0f);
	glVertex3f(bottomOuterLeft, bottomY, 0.0f);

	// Right Edge (Lighter for highlight)
	glColor3f(0.48f, 0.16f, 0.10f);
	glVertex3f(bottomOuterRight, bottomY, 0.0f);
	glVertex3f(topOuterRight, topY, 0.0f);

	glEnd();

	// 2. THE DETAILS (Golden Strip & Base)
	
	// Enable Polygon Offset to mathematically draw these exactly on top 
	// of the pillar body without physical Z-fighting or gaps.
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-1.0f, -1.0f);

	// Strip over the pillar
	glColor3f(0.70f, 0.50f, 0.10f);
	drawCurvedLine(0.0f, 0.3f, 0.0f, 0.96f, 0.30f, 0.08f);

	// Pillar base 
	glColor3f(0.15f, 0.05f, 0.03f);
	drawCurvedLine(0.0f, -2.2f, 0.0f, 1.2f, 0.4f, 0.10f);

	// Add a QUAD overlapping the bottom to make it perfectly flat
	glBegin(GL_QUADS);
	glVertex3f(-0.60f, -2.4f, 0.0f);
	glVertex3f(0.60f, -2.4f, 0.0f);
	glVertex3f(0.60f, -2.8f, 0.0f);
	glVertex3f(-0.60f, -2.8f, 0.0f);
	glEnd();

	// Disable Polygon Offset so it doesn't affect the rest of your scene
	glDisable(GL_POLYGON_OFFSET_FILL);

	glPopMatrix();


}

void drawLeftCurtain(void)
{

	glPushMatrix();
	glScalef(0.7f, 0.7f, 0.7f); // Matching pillar scale

	float z = -0.5f;
	float topY = 3.0f;
	float bottomY = -2.1f;
	float step = 0.2f;

	float pillarLeftEdge = -0.1f;

	// GOLDEN BORDER 
	glColor3f(0.85f, 0.65f, 0.20f);
	glBegin(GL_QUAD_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);

		float gatherSweep = (3.0f + pillarLeftEdge) * (t * t);

		float outerX = -3.0f + gatherSweep;

		glVertex3f(outerX, y, z);
		glVertex3f(outerX + 0.2f, y, z);
	}
	glEnd();

	//  MAIN CURTAIN FABRIC
	glColor3f(0.55f, 0.10f, 0.35f);
	glBegin(GL_QUAD_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);
		float gatherSweep = (3.0f + pillarLeftEdge) * (t * t);

		float fabricLeftX = -3.0f + gatherSweep + 0.2f;

		float fabricRightX = pillarLeftEdge;

		glVertex3f(fabricLeftX, y, z);
		glVertex3f(fabricRightX, y, z);
	}
	glEnd();

	//  FOLDS (Disappearing behind the pillar)
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.20f, 0.02f, 0.10f);
	float foldZ = z + 0.01f;

	glLineWidth(2.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step) {
		float t = (topY - y) / (topY - bottomY);
		float foldX = -2.0f + (2.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glLineWidth(1.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step) {
		float t = (topY - y) / (topY - bottomY);
		float foldX = -1.0f + (1.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

	glPopMatrix();

}

void drawRightCurtain(void)
{
	glPushMatrix();
	glScalef(0.7f, 0.7f, 0.7f); // Match pillar scale

	float z = -0.5f;
	float topY = 3.0f;
	float bottomY = -2.1f;
	float step = 0.2f;

	// The right edge of the pillar to tuck the fabric behind
	float pillarRightEdge = -0.1f;

	// GOLDEN BORDER (Now on the Far RIGHT edge)
	glColor3f(0.85f, 0.65f, 0.20f);
	glBegin(GL_QUAD_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);

		float gatherSweep = -3.0f * (t * t);

		float outerX = 3.0f + gatherSweep;

		glVertex3f(outerX - 0.2f, y, z);
		glVertex3f(outerX, y, z);
	}
	glEnd();

	//  MAIN CURTAIN FABRIC
	glColor3f(0.55f, 0.10f, 0.35f);
	glBegin(GL_QUAD_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);
		float gatherSweep = -3.0f * (t * t);

		float fabricRightX = 3.0f + gatherSweep - 0.2f;

		// Fabric ends safely behind the pillar's right edge
		float fabricLeftX = pillarRightEdge;

		glVertex3f(fabricLeftX, y, z);
		glVertex3f(fabricRightX, y, z);
	}
	glEnd();

	// FOLDS (Disappearing behind the pillar)
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.20f, 0.02f, 0.10f);
	float foldZ = z + 0.01f;

	glLineWidth(2.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step) {
		float t = (topY - y) / (topY - bottomY);
		float foldX = 2.0f + (-2.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glLineWidth(1.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step) {
		float t = (topY - y) / (topY - bottomY);
		float foldX = 1.0f + (-1.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

	glPopMatrix();


}

void drawPillarDesign(void)
{
	// Circle design on golden band
	glColor3f(0.95f, 0.80f, 0.25f);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.0f);

	float bandCenterY = 0.2f;
	float bandWidth = 0.92f;
	float halfWidth = bandWidth / 2.0f;
	float bandCurveAmount = 0.08f;

	float zOffset = 0.01f;

	int numCircles = 5;
	float spacing = bandWidth / (numCircles + 1);

	for (int i = 1; i <= numCircles; i++)
	{
		float xOffset = -halfWidth + (i * spacing);

		float normalizedX = xOffset / halfWidth;
		float curveOffset = -bandCurveAmount * (normalizedX * normalizedX);
		float circleY = bandCenterY + curveOffset;

		drawCircleborder(xOffset, circleY, zOffset, 0.025f, 16);
	}

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

void drawPillarAndCurtain(void)
{
	drawLeftCurtain();
	drawRightCurtain();
	drawPillar();
	drawPillarDesign();

}

void drawRoom(void)
{
	float hallDepth = -45.0f; // How deep the room goes
	float floorY = -3.0f;
	float ceilY = 5.0f;
	float wallX = 8.0f;       // Room width

	glPushMatrix();

	// TEAL TILED FLOOR
	glColor3f(0.3f, 0.65f, 0.6f); // Teal color
	glBegin(GL_QUADS);
	glVertex3f(-wallX, floorY, 2.0f);
	glVertex3f(wallX, floorY, 2.0f);
	glVertex3f(wallX, floorY, hallDepth);
	glVertex3f(-wallX, floorY, hallDepth);
	glEnd();

	// grid lines on tile
	glColor3f(0.2f, 0.5f, 0.45f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for (float z = 2.0f; z >= hallDepth; z -= 2.0f) {
		// Left tile lines stop at -1.6f
		glVertex3f(-wallX, floorY + 0.01f, z);
		glVertex3f(-1.6f, floorY + 0.01f, z);
		// Right tile lines start at 1.6f
		glVertex3f(1.6f, floorY + 0.01f, z);
		glVertex3f(wallX, floorY + 0.01f, z);
	}
	for (float x = -wallX; x <= wallX; x += 2.0f) {
		// Only draw depth lines outside the narrower 1.6f boundary
		if (x <= -1.6f || x >= 1.6f) {
			glVertex3f(x, floorY + 0.01f, 2.0f);
			glVertex3f(x, floorY + 0.01f, hallDepth);
		}
	}
	glEnd();

	// PINK WALLS WITH LOWER TRIM
	// Main Pink Wall (Left & Right)
	glColor3f(0.75f, 0.45f, 0.65f);
	glBegin(GL_QUADS);
	// Left Wall
	glVertex3f(-wallX, floorY + 1.5f, 2.0f);
	glVertex3f(-wallX, floorY + 1.5f, hallDepth);
	glVertex3f(-wallX, ceilY, hallDepth);
	glVertex3f(-wallX, ceilY, 2.0f);
	// Right Wall
	glVertex3f(wallX, floorY + 1.5f, 2.0f);
	glVertex3f(wallX, floorY + 1.5f, hallDepth);
	glVertex3f(wallX, ceilY, hallDepth);
	glVertex3f(wallX, ceilY, 2.0f);
	glEnd();

	// Lower Red Wall Trim
	glColor3f(0.7f, 0.15f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-wallX, floorY, 2.0f); glVertex3f(-wallX, floorY, hallDepth);
	glVertex3f(-wallX, floorY + 1.2f, hallDepth); glVertex3f(-wallX, floorY + 1.2f, 2.0f);

	glVertex3f(wallX, floorY, 2.0f); glVertex3f(wallX, floorY, hallDepth);
	glVertex3f(wallX, floorY + 1.2f, hallDepth); glVertex3f(wallX, floorY + 1.2f, 2.0f);
	glEnd();

	// 3. CUBICAL / BOXY BROWN CEILING
	float recessY = 6.5f;         // How high the center ceiling goes
	float recessX = wallX - 2.0f; // Where the vertical drop happens

	// A. Lower flat ceiling margins (Left & Right)
	glColor3f(0.35f, 0.2f, 0.15f);
	glBegin(GL_QUADS);
	glVertex3f(-wallX, ceilY, 2.0f); glVertex3f(-wallX, ceilY, hallDepth);
	glVertex3f(-recessX, ceilY, hallDepth); glVertex3f(-recessX, ceilY, 2.0f);

	glVertex3f(recessX, ceilY, 2.0f); glVertex3f(recessX, ceilY, hallDepth);
	glVertex3f(wallX, ceilY, hallDepth); glVertex3f(wallX, ceilY, 2.0f);
	glEnd();

	// B. Vertical step/rise 
	glColor3f(0.25f, 0.12f, 0.08f); 
	glBegin(GL_QUADS);
	glVertex3f(-recessX, ceilY, 2.0f); glVertex3f(-recessX, ceilY, hallDepth);
	glVertex3f(-recessX, recessY, hallDepth); glVertex3f(-recessX, recessY, 2.0f);

	glVertex3f(recessX, ceilY, 2.0f); glVertex3f(recessX, ceilY, hallDepth);
	glVertex3f(recessX, recessY, hallDepth); glVertex3f(recessX, recessY, 2.0f);
	glEnd();

	// C. High flat center ceiling
	glColor3f(0.45f, 0.25f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-recessX, recessY, 2.0f); glVertex3f(recessX, recessY, 2.0f);
	glVertex3f(recessX, recessY, hallDepth); glVertex3f(-recessX, recessY, hallDepth);
	glEnd();

	// D. Front Vertical Face
	glColor3f(0.25f, 0.12f, 0.08f); // Matches the dark inner shadow depth
	glBegin(GL_QUADS);
	glVertex3f(-recessX, ceilY, hallDepth);
	glVertex3f(recessX, ceilY, hallDepth);
	glVertex3f(recessX, recessY, hallDepth);
	glVertex3f(-recessX, recessY, hallDepth);
	glEnd();

	//  THE BACK WALL
	float doorZ = hallDepth;

	// Main Pink Back Wall
	glColor3f(0.75f, 0.45f, 0.65f);
	glBegin(GL_QUADS);
	// Left side of door
	glVertex3f(-wallX, floorY + 1.5f, doorZ); glVertex3f(-3.0f, floorY + 1.5f, doorZ);
	glVertex3f(-3.0f, ceilY, doorZ);          glVertex3f(-wallX, ceilY, doorZ);
	// Right side of door
	glVertex3f(3.0f, floorY + 1.5f, doorZ);   glVertex3f(wallX, floorY + 1.5f, doorZ);
	glVertex3f(wallX, ceilY, doorZ);          glVertex3f(3.0f, ceilY, doorZ);
	// Top of door
	glVertex3f(-3.0f, 4.0f, doorZ);           glVertex3f(3.0f, 4.0f, doorZ);
	glVertex3f(3.0f, ceilY, doorZ);           glVertex3f(-3.0f, ceilY, doorZ);
	glEnd();

	// Lower Red Wall Trim (Back Wall)
	glColor3f(0.7f, 0.15f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-wallX, floorY, doorZ);        glVertex3f(-3.0f, floorY, doorZ);
	glVertex3f(-3.0f, floorY + 1.2f, doorZ);  glVertex3f(-wallX, floorY + 1.2f, doorZ);

	glVertex3f(3.0f, floorY, doorZ);          glVertex3f(wallX, floorY, doorZ);
	glVertex3f(wallX, floorY + 1.2f, doorZ);  glVertex3f(3.0f, floorY + 1.2f, doorZ);
	glEnd();

	// CORNER CREASE LINES (Separating side and back walls)
	glColor3f(0.0f, 0.0f, 0.0f); // Solid black
	glLineWidth(2.0f);

	glBegin(GL_LINES);

	float cornerZ = hallDepth + 0.02f;

	// Left Corner Line 
	glVertex3f(-wallX + 0.02f, floorY, cornerZ);
	glVertex3f(-wallX + 0.02f, ceilY, cornerZ);

	// Right Corner Line
	glVertex3f(wallX - 0.02f, floorY, cornerZ);
	glVertex3f(wallX - 0.02f, ceilY, cornerZ);

	glEnd();

	glPopMatrix();
}


void drawCarpetAndDoors(void)
{
	float hallDepth = -44.9f; 
	float floorY = -2.99f;    

	// CARPET (Yellow center, Red borders)
	// Yellow Center 
	glColor3f(0.95f, 0.85f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-1.2f, floorY, 2.0f); glVertex3f(1.2f, floorY, 2.0f);
	glVertex3f(1.2f, floorY, hallDepth); glVertex3f(-1.2f, floorY, hallDepth);
	glEnd();

	// Red Borders 
	glColor3f(0.7f, 0.1f, 0.15f);
	glBegin(GL_QUADS);
	// Left border
	glVertex3f(-1.6f, floorY, 2.0f); glVertex3f(-1.2f, floorY, 2.0f);
	glVertex3f(-1.2f, floorY, hallDepth); glVertex3f(-1.6f, floorY, hallDepth);
	// Right border
	glVertex3f(1.2f, floorY, 2.0f); glVertex3f(1.6f, floorY, 2.0f);
	glVertex3f(1.6f, floorY, hallDepth); glVertex3f(1.2f, floorY, hallDepth);
	glEnd();

	//  BACK WALL & OPEN DOORS
	float doorZ = -45.0f;

	// The Outside (Sky and ground visible through the door)
	glColor3f(0.4f, 0.7f, 0.9f); // Sky
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, floorY, doorZ - 1.0f); glVertex3f(3.0f, floorY, doorZ - 1.0f);
	glVertex3f(3.0f, 4.0f, doorZ - 1.0f); glVertex3f(-3.0f, 4.0f, doorZ - 1.0f);
	glEnd();

	glColor3f(0.3f, 0.6f, 0.2f); // Green Ground
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, floorY, doorZ - 0.9f); glVertex3f(3.0f, floorY, doorZ - 0.9f);
	glVertex3f(3.0f, -1.0f, doorZ - 0.9f); glVertex3f(-3.0f, -1.0f, doorZ - 0.9f);
	glEnd();

	// Wooden Doors 
	float doorH = 4.0f;

    // LEFT DOOR
    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, doorZ);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f); // Positive angle swings into -Z
    
    glColor3f(0.35f, 0.20f, 0.10f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, floorY, 0.0f);
    glVertex3f(3.0f, floorY, 0.0f);
    glVertex3f(3.0f, doorH, 0.0f);
    glVertex3f(0.0f, doorH, 0.0f);
    glEnd();

    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
    glVertex3f(0.15f, floorY + 0.2f, -0.01f);
    glVertex3f(2.85f, floorY + 0.2f, -0.01f);
    glVertex3f(2.85f, doorH - 0.2f, -0.01f);
    glVertex3f(0.15f, doorH - 0.2f, -0.01f);
    glEnd();
    glPopMatrix();

    // RIGHT DOOR
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, doorZ);
    glRotatef(-doorAngle, 0.0f, 1.0f, 0.0f); // Negative angle swings into -Z
    
    glColor3f(0.35f, 0.20f, 0.10f);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, floorY, 0.0f);
    glVertex3f(0.0f, floorY, 0.0f);
    glVertex3f(0.0f, doorH, 0.0f);
    glVertex3f(-3.0f, doorH, 0.0f);
    glEnd();

    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
    glVertex3f(-2.85f, floorY + 0.2f, -0.01f);
    glVertex3f(-0.15f, floorY + 0.2f, -0.01f);
    glVertex3f(-0.15f, doorH - 0.2f, -0.01f);
    glVertex3f(-2.85f, doorH - 0.2f, -0.01f);
    glEnd();
    glPopMatrix();
}

void drawForegroundStage(void)
{
	float floorY = -2.98f;
	float stageTopY = -2.2f; // Lowered so it doesn't block the view of the hall

	// Positioned slightly in front of the camera and extending backwards
	float startZ = -5.0f;
	float stairZ = -7.5f;    // Where the stairs begin to drop
	float stageW = 4.0f;     // Width of the main flat stage

	glPushMatrix();
	// MAIN FLAT STAGE 
	glColor3f(0.75f, 0.55f, 0.35f);
	glBegin(GL_QUADS);
	glVertex3f(-stageW, stageTopY, stairZ);
	glVertex3f(stageW, stageTopY, stairZ);
	glVertex3f(stageW, stageTopY, startZ); 
	glVertex3f(-stageW, stageTopY, startZ);
	glEnd();

	// Yellow Carpet on stage
	glColor3f(0.95f, 0.85f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-1.2f, stageTopY + 0.01f, stairZ);
	glVertex3f(1.2f, stageTopY + 0.01f, stairZ);
	glVertex3f(1.2f, stageTopY + 0.01f, startZ);
	glVertex3f(-1.2f, stageTopY + 0.01f, startZ);
	glEnd();

	// Red Carpet Borders on stage
	glColor3f(0.7f, 0.1f, 0.15f);
	glBegin(GL_QUADS);
	glVertex3f(-1.6f, stageTopY + 0.01f, stairZ);
	glVertex3f(-1.2f, stageTopY + 0.01f, stairZ);
	glVertex3f(-1.2f, stageTopY + 0.01f, startZ);
	glVertex3f(-1.6f, stageTopY + 0.01f, startZ);

	glVertex3f(1.2f, stageTopY + 0.01f, stairZ);
	glVertex3f(1.6f, stageTopY + 0.01f, stairZ);
	glVertex3f(1.6f, stageTopY + 0.01f, startZ);
	glVertex3f(1.2f, stageTopY + 0.01f, startZ);
	glEnd();

	// Three stairs attached to stage
	int numSteps = 3;
	float stepH = (stageTopY - floorY) / (float)numSteps;
	float stepD = 1.2f;  // Depth of each step
	float stairW = 2.4f; 

	for (int i = 0; i < numSteps; i++)
	{
		float curTopY = stageTopY - (i * stepH);
		float curBotY = curTopY - stepH;
		float curFrontZ = stairZ - (i * stepD);
		float curBackZ = curFrontZ - stepD;

		// Riser (Draw the vertical face dropping down FIRST)
		glColor3f(0.6f, 0.15f, 0.15f);
		glBegin(GL_QUADS);
		glVertex3f(-stairW, curBotY, curFrontZ); glVertex3f(stairW, curBotY, curFrontZ);
		glVertex3f(stairW, curTopY, curFrontZ); glVertex3f(-stairW, curTopY, curFrontZ);
		glEnd();

		// Black Outlines around the vertical face
		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(2.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-stairW, curBotY, curFrontZ + 0.01f);
		glVertex3f(stairW, curBotY, curFrontZ + 0.01f);
		glVertex3f(stairW, curTopY, curFrontZ + 0.01f);
		glVertex3f(-stairW, curTopY, curFrontZ + 0.01f);
		glEnd();

		float treadY = curBotY;

		glColor3f(0.65f, 0.45f, 0.25f); // Wood margins
		glBegin(GL_QUADS);
		glVertex3f(-stairW, treadY, curBackZ); glVertex3f(stairW, treadY, curBackZ);
		glVertex3f(stairW, treadY, curFrontZ); glVertex3f(-stairW, treadY, curFrontZ);
		glEnd();

		// Carpet (Yellow)
		glColor3f(0.95f, 0.85f, 0.2f);
		glBegin(GL_QUADS);
		glVertex3f(-1.2f, treadY + 0.01f, curBackZ); glVertex3f(1.2f, treadY + 0.01f, curBackZ);
		glVertex3f(1.2f, treadY + 0.01f, curFrontZ); glVertex3f(-1.2f, treadY + 0.01f, curFrontZ);
		glEnd();

		//  Carpet (Red)
		glColor3f(0.7f, 0.1f, 0.15f);
		glBegin(GL_QUADS);
		glVertex3f(-1.6f, treadY + 0.01f, curBackZ); glVertex3f(-1.2f, treadY + 0.01f, curBackZ);
		glVertex3f(-1.2f, treadY + 0.01f, curFrontZ); glVertex3f(-1.6f, treadY + 0.01f, curFrontZ);
		glVertex3f(1.2f, treadY + 0.01f, curBackZ); glVertex3f(1.6f, treadY + 0.01f, curBackZ);
		glVertex3f(1.6f, treadY + 0.01f, curFrontZ); glVertex3f(1.2f, treadY + 0.01f, curFrontZ);
		glEnd();
	}

	glPopMatrix();
}

void drawSideCharacters(void)
{
	float floorY = -2.98f;

	
	// 1. ROYAL GUARDS (Sainik)
	// Rendered using  rlDrawSoliderEx
	
	// Foreground Right Soldier (standing near royal staircase railing)
	rlDrawSoliderEx(3.4f, floorY, -9.2f, 1.15f, 1.15f, 1.15f, -30.0f, 0);

	// Midground Right Soldier (standing alert beside pillars)
	rlDrawSoliderEx(3.8f, floorY, -17.5f, 1.15f, 1.15f, 1.15f, -40.0f, 0);

	// Background Right Soldier (standing guard at open palace doorway)
	rlDrawSoliderEx(2.6f, floorY, -35.0f, 1.15f, 1.15f, 1.15f, -20.0f, 0);

	// Midground Left Soldier (standing alert beside left colonnade)
	rlDrawSoliderEx(-3.8f, floorY, -17.5f, 1.15f, 1.15f, 1.15f, 40.0f, 1);

	// Background Left Soldier (standing guard at open palace doorway)
	rlDrawSoliderEx(-2.6f, floorY, -35.0f, 1.15f, 1.15f, 1.15f, 20.0f, 1);

	
	// 2. COURTIERS / MINISTERS (Darbari)
	// Rendered standing in dignified royal court attendance (no chairs)
	// Using rlDreawDarbari / rlDreawDarbariEx
	// Colors and positions faithfully reproduce the scene artwork
	

	// --- Right Gallery Standing Courtiers (Facing inward towards central aisle) ---
	// Courtier 1: Royal Saffron / Gold Robe
	rlDreawDarbariEx(4.0f, floorY, -8.5f, 0.95f, 0.95f, 0.95f, -65.0f, 0);

	// Courtier 2: Dignified Pure Silk White Robe
	rlDreawDarbariEx(4.7f, floorY, -18.0f, 0.95f, 0.95f, 0.95f, -65.0f, 1);

	// Courtier 3: Turquoise / Sky Blue Robe
	rlDreawDarbariEx(4.8f, floorY, -20.5f, 0.95f, 0.95f, 0.95f, -65.0f, 2);

	// Courtier 4: Royal Deep Blue Robe with Red Turban
	rlDreawDarbariEx(4.9f, floorY, -23.0f, 0.95f, 0.95f, 0.95f, -65.0f, 3);

	// Courtier 5: Emerald Green Robe
	rlDreawDarbariEx(5.0f, floorY, -25.5f, 0.95f, 0.95f, 0.95f, -65.0f, 4);

	// Courtier 6: Crimson / Red Robe
	rlDreawDarbariEx(5.1f, floorY, -28.0f, 0.95f, 0.95f, 0.95f, -65.0f, 5);

	// Right Gallery Second Row Standing Attendants
	rlDreawDarbariEx(5.3f, floorY, -19.5f, 0.92f, 0.92f, 0.92f, -60.0f, 0);
	rlDreawDarbariEx(5.4f, floorY, -22.0f, 0.92f, 0.92f, 0.92f, -60.0f, 1);

	// --- Left Gallery Standing Courtiers (Facing inward towards central aisle) ---
	// Courtier 1: Crimson Red Robe with Gold Turban
	rlDreawDarbariEx(-4.6f, floorY, -16.0f, 0.95f, 0.95f, 0.95f, 65.0f, 5);

	// Courtier 2: Pure White Silk Robe
	rlDreawDarbariEx(-4.7f, floorY, -18.8f, 0.95f, 0.95f, 0.95f, 65.0f, 1);

	// Courtier 3: Imperial Violet / Purple Robe
	rlDreawDarbariEx(-4.8f, floorY, -21.6f, 0.95f, 0.95f, 0.95f, 65.0f, 6);

	// Left Gallery Second Row Standing Attendants
	rlDreawDarbariEx(-5.3f, floorY, -17.5f, 0.92f, 0.92f, 0.92f, 60.0f, 4);
	rlDreawDarbariEx(-5.4f, floorY, -20.2f, 0.92f, 0.92f, 0.92f, 60.0f, 0);
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
*/
/*
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
void darbar(void)
{
	//code
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // the actual screen clear task is done by this bit by bit


	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();

	drawRoom();
	drawCarpetAndDoors();

	for (float zOffset = -2.0f; zOffset >= -40.0f; zOffset -= 8.4f)
	{
		//------------- LEFT WALL---------------------------
		glPushMatrix();

		// X = -6.0f (Pushed against the left wall)
		glTranslatef(-6.0f, 1.7f, zOffset);

		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		glScalef(2.0f, 2.5f, 2.0f);

		drawPillarAndCurtain();
		glPopMatrix();

		// ---------------- RIGHT WALL --------------------------
		glPushMatrix();

		// X = 6.0f (Pushed against the right wall)
		glTranslatef(6.0f, 1.7f, zOffset);

		glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

		glScalef(2.0f, 2.5f, 2.0f);

		drawPillarAndCurtain();
		glPopMatrix();
	}

	drawForegroundStage();

	// Draw Royal Guards and Courtiers (Side Characters)
	drawSideCharacters();



    // Draw Chanakya if doors are opening or open
    if (sceneState >= 1)
    {
        glPushMatrix();
        glTranslatef(0.0f, -0.35f, chanakyaZ); // Adjust Y to stand on floor
        glScalef(0.82f, 0.82f, 0.82f);
        drawChanakyaCharacter();
        glPopMatrix();
    }

	// // Do double buffering
	// SwapBuffers(ghdc);

}

/*
void updateOfDarbar(void)
{
    // Update Chanakya animation time
    rlAnimTime += 0.018f;

    // Scene flow
    if (sceneState == 0) // Doors closed, waiting
    {
        sceneTimer += 0.01f;
        if (sceneTimer > 1.0f)
        {
            sceneState = 1;
        }
    }
    else if (sceneState == 1) // Opening doors
    {
        doorAngle += 1.0f;
        if (doorAngle >= 90.0f)
        {
            doorAngle = 90.0f;
            sceneState = 2; // Start walking
            rlAnimMode = 1; // Walking cycle
        }
    }
    else if (sceneState == 2) // Walking inside
    {
        chanakyaZ += 0.05f; // Walk forward (towards camera, which is at +Z)
        if (chanakyaZ >= -10.0f) // Stop point
        {
            chanakyaZ = -10.0f;
            sceneState = 3;
            rlAnimMode = 0; // Pointing Stance
        }
    }

    // Chanakya joint updates based on rliAnimMode
    if (rlAnimMode == 0)
    {
        rlLeftShoulderRoll = 125.0f + 2.0f * sinf(rlAnimTime * 1.5f);
        rlLeftShoulderPitch = 0.0f;
        rlLeftElbowAngle = -15.0f;

        rlRightShoulderRoll = -10.0f;
        rlRightShoulderPitch = 0.0f;
        rlRightElbowAngle = 10.0f;
        rlLeftHipAngle = 0.0f;
        rlRightHipAngle = 0.0f;
        rlLeftKneeAngle = 0.0f;
        rlRightKneeAngle = 0.0f;
        rlHipBobY = 0.0f;
        rlEyebrowSlantY = 0.24f;
        rlMouthOpenHeight = 0.0f;
    }
    else if (rlAnimMode == 1)
    {
        float rlWalkCycleVal = sinf(rlAnimTime * 3.5f);

        rlLeftHipAngle = 24.0f * rlWalkCycleVal;
        rlRightHipAngle = -24.0f * rlWalkCycleVal;
        rlLeftKneeAngle = (rlWalkCycleVal > 0.0f) ? (18.0f * rlWalkCycleVal) : 0.0f;
        rlRightKneeAngle = (rlWalkCycleVal < 0.0f) ? (-18.0f * rlWalkCycleVal) : 0.0f;

        rlHipBobY = -0.03f * fabsf(sinf(rlAnimTime * 7.0f));

        rlLeftShoulderPitch = -24.0f * rlWalkCycleVal;
        rlRightShoulderPitch = 24.0f * rlWalkCycleVal;
        rlLeftShoulderRoll = 0.0f;
        rlRightShoulderRoll = 0.0f;

        rlLeftElbowAngle = (rlWalkCycleVal < 0.0f) ? (-22.0f * fabsf(rlWalkCycleVal)) : -5.0f;
        rlRightElbowAngle = (rlWalkCycleVal > 0.0f) ? (22.0f * fabsf(rlWalkCycleVal)) : 5.0f;

        rlEyebrowSlantY = 0.28f;
        rlMouthOpenHeight = 0.0f;
    }
}

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
