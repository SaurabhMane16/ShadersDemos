// =============================================================================
// Scene 3: Royal Darbar Confrontation & Dialogue (Integrated Module)
// Author: Saurabh Tanaji Mane
// Synchronized dialogue with King Dhana Nanda, Chanakya, Standing Minister,
// full court audience, and cinematic camera cuts.
// =============================================================================

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mmsystem.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Scene3.h"
#include "side_character.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// Forward declarations
extern HWND ghwnd;

// =============================================================================
// CAMERA SHOT ENUM & LOCAL STATE VARIABLES (STATIC TO PREVENT COLLISION)
// =============================================================================
typedef enum {
	SHOT_WIDE = 0,         // Master Establishing Darbar View
	SHOT_STANDING_SAGE,   // Close-up on Minister / Standing Sage beside King
	SHOT_KING,            // Close-up on King Dhana Nanda on royal throne
	SHOT_CHANAKYA,        // Low-angle Over-The-Shoulder framing on Chanakya
	SHOT_SHISHYA          // Over-The-Shoulder framing on Chanakya's Disciple
} CameraShot;

static BOOL g_bAutoDirector = TRUE;
static CameraShot g_currentShot = SHOT_WIDE;

// Interpolated camera coordinates (Steadicam)
static float g_camEyeX = 0.0f;
static float g_camEyeY = 0.0f;
static float g_camEyeZ = 0.0f;

static float g_camTargetX = 0.0f;
static float g_camTargetY = 0.0f;
static float g_camTargetZ = -28.0f;

// Desired camera destination
static float g_targetEyeX = 0.0f;
static float g_targetEyeY = 0.0f;
static float g_targetEyeZ = 0.0f;

static float g_targetTargetX = 0.0f;
static float g_targetTargetY = 0.0f;
static float g_targetTargetZ = -28.0f;

// Camera Transition Mode: TRUE = Instant Hard Cut (TV Serial / Movie dialogue style)
//                         FALSE = Smooth Steadicam Zoom / Interpolation
static BOOL g_bInstantCameraCut = TRUE;

static void applyCameraCut(void)
{
	if (g_bInstantCameraCut)
	{
		g_camEyeX = g_targetEyeX;
		g_camEyeY = g_targetEyeY;
		g_camEyeZ = g_targetEyeZ;

		g_camTargetX = g_targetTargetX;
		g_camTargetY = g_targetTargetY;
		g_camTargetZ = g_targetTargetZ;
	}
}

// Character speech and gesture blend weights
static float g_standingSageMouthOpen = 0.0f;
static float g_standingSageGesture = 0.0f;
static float g_chanakyaSpeakingBlend = 0.0f;
static BOOL g_bStandingSageSpeaking = FALSE;
static BOOL g_bChanakyaSpeaking = FALSE;
static BOOL g_bKingSpeaking = FALSE;
static float g_kingMouthOpen = 0.0f;

// King Emotion State: 0 = Royal Idle, 1 = Arrogant Laugh, 2 = Royal Anger
static int rliKingMode = 0;
static float rliAnimTime = 0.0f;
static float rliLaughBlend = 0.0f;
static float rliAngerBlend = 0.0f;

// Audio Synchronization state
static BOOL g_bScene3AudioStarted = FALSE;
static DWORD g_darbarAudioStartTick = 0;

void stopScene3Audio(void)
{
	if (g_bScene3AudioStarted)
	{
		PlaySound(NULL, 0, 0);
		g_bScene3AudioStarted = FALSE;
	}
}

void startScene3Audio(void)
{
	PlaySoundA("Dialogs.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT);
	g_darbarAudioStartTick = timeGetTime();
	g_bScene3AudioStarted = TRUE;
}

// Forward declarations of local shot and drawing functions
static void drawDarbarScene(void);
static void shotWide(void);
static void shotStandingSage(BOOL bSpeaking);
static void shotKing(int kingEmotionMode);
static void shotChanakya(BOOL bSpeaking);
static void shotShishya(BOOL bSpeaking);
static void renderWideShot(void);
static void renderStandingSageQuestionShot(void);
static void renderChanakyaResponseShot(void);
static void renderKingLaughShot(void);
static void renderKingNormalShot(void);
static void renderKingAngryShot(void);

// =============================================================================
// CAMERA SHOT & SCENE GEOMETRY IMPLEMENTATIONS
// =============================================================================
// INDIVIDUAL DEDICATED CAMERA SHOT FUNCTIONS
// =============================================================================

// 1. Master Wide Establishing Shot (Entire Grand Royal Darbar)
static void shotWide(void)
{
	g_currentShot = SHOT_WIDE;
	g_targetEyeX = 0.0f;
	g_targetEyeY = 0.0f;
	g_targetEyeZ = 0.0f;
	g_targetTargetX = 0.0f;
	g_targetTargetY = 0.0f;
	g_targetTargetZ = -28.0f;

	rliKingMode = 0;
	g_bStandingSageSpeaking = FALSE;
	g_bChanakyaSpeaking = FALSE;
	g_bKingSpeaking = FALSE;

	applyCameraCut();
}

// 2. Standing Person Close-Up Shot (Beside King on the dais)
static void shotStandingSage(BOOL bSpeaking)
{
	g_currentShot = SHOT_STANDING_SAGE;
	g_targetEyeX = -2.70f;
	g_targetEyeY = 4.30f;
	g_targetEyeZ = -20.5f;
	g_targetTargetX = -2.70f;
	g_targetTargetY = 4.30f;
	g_targetTargetZ = -28.0f;

	rliKingMode = 0;
	g_bStandingSageSpeaking = bSpeaking;
	g_bChanakyaSpeaking = FALSE;
	g_bKingSpeaking = FALSE;

	applyCameraCut();
}

// 3. King Dhana Nanda Close-Up Shot (0: Normal speaking, 1: Arrogant laugh, 2: Royal rage)
static void shotKing(int kingEmotionMode)
{
	g_currentShot = SHOT_KING;
	g_targetEyeX = 0.0f;
	g_targetEyeY = 4.05f;
	g_targetEyeZ = -20.5f;
	g_targetTargetX = 0.0f;
	g_targetTargetY = 4.30f;
	g_targetTargetZ = -28.5f;

	rliKingMode = kingEmotionMode;
	g_bStandingSageSpeaking = FALSE;
	g_bChanakyaSpeaking = FALSE;
	g_bKingSpeaking = (kingEmotionMode == 0 || kingEmotionMode == 2);

	applyCameraCut();
}

// 4. Chanakya Low-Angle Over-The-Shoulder Shot Confronting Throne
static void shotChanakya(BOOL bSpeaking)
{
	g_currentShot = SHOT_CHANAKYA;
	g_targetEyeX = 3.20f;
	g_targetEyeY = 0.50f;
	g_targetEyeZ = -7.0f;
	g_targetTargetX = 1.20f;
	g_targetTargetY = 1.80f;
	g_targetTargetZ = -25.0f;

	rliKingMode = 0;
	g_bStandingSageSpeaking = FALSE;
	g_bChanakyaSpeaking = bSpeaking;
	g_bKingSpeaking = FALSE;

	applyCameraCut();
}

// 5. Shishya / Disciple Foreground Shot
static void shotShishya(BOOL bSpeaking)
{
	g_currentShot = SHOT_SHISHYA;
	g_targetEyeX = -0.50f;
	g_targetEyeY = 0.20f;
	g_targetEyeZ = -8.0f;
	g_targetTargetX = -1.20f;
	g_targetTargetY = 1.60f;
	g_targetTargetZ = -24.0f;

	rliKingMode = 0;
	g_bStandingSageSpeaking = FALSE;
	g_bChanakyaSpeaking = bSpeaking;
	g_bKingSpeaking = FALSE;

	applyCameraCut();
}

// Compatibility dispatcher
static void setCameraTarget(CameraShot shot)
{
	switch (shot)
	{
	case SHOT_STANDING_SAGE: 
		shotStandingSage(g_bStandingSageSpeaking); 
		break;
	case SHOT_KING:          
		shotKing(rliKingMode);                   
		break;
	case SHOT_CHANAKYA:      
		shotChanakya(g_bChanakyaSpeaking);        
		break;
	case SHOT_SHISHYA:       
		shotShishya(g_bChanakyaSpeaking);         
		break;
	case SHOT_WIDE:
	default:                
		shotWide();                              
		break;
	}
}


// -------------------------------------------------- INITIAL DARBAR SCENE 3 FUNCTIONS ----------------------------------------------------

static void drawCircleOutline(float cx, float cy, float cz, float r, int segments)
{
	glBegin(GL_LINE_LOOP);          // Connects vertices in a continuous path, draws one final line from the last dot back to the first dot
	for (int i = 0; i < segments; i++)
	{
		float angle = 2.0f * (float)M_PI * (float)i / (float)segments;
		float x = cx + r * cosf(angle);
		float y = cy + r * sinf(angle);
		glVertex3f(x, y, cz);
	}
	glEnd();
}

static void drawCurvedStrip(float centerX, float centerY, float centerZ, float width, float thickness, float curveAmount)
{
	glBegin(GL_QUAD_STRIP);

	float halfWidth = width / 2.0f;
	float halfThickness = thickness / 2.0f;

	// Step across the width of the shape
	float step = width / 50.0f;

	for (float xOffset = -halfWidth; xOffset <= halfWidth + (step * 0.1f); xOffset += step)
	{
		float x = centerX + xOffset;

		// Calculate the curve based on the distance from the center
		// We normalize xOffset by halfWidth so the curve behaves consistently regardless of width
		float normalizedX = xOffset / halfWidth;
		float curveOffset = -curveAmount * (normalizedX * normalizedX);

		// Bottom vertex
		float bottomY = centerY - halfThickness + curveOffset;
		glVertex3f(x, bottomY, centerZ);

		// Top vertex
		float topY = centerY + halfThickness + curveOffset;
		glVertex3f(x, topY, centerZ);
	}

	glEnd();
}

static void drawPillar(void)
{
	float topY = 2.8f;
	float bottomY = -2.2f;

	float topOuterLeft = -0.40f;
	float topOuterRight = 0.40f;
	float bottomOuterLeft = -0.50f;
	float bottomOuterRight = 0.50f;

	glPushMatrix();
	glScalef(0.7f, 0.7f, 0.7f);

	// 1. MAIN PILLAR BODY
	glBegin(GL_QUADS);

	// Left Edge 
	glColor3f(0.30f, 0.07f, 0.05f);
	glVertex3f(topOuterLeft, topY, 0.0f);
	glVertex3f(bottomOuterLeft, bottomY, 0.0f);

	// Right Edge
	glColor3f(0.48f, 0.16f, 0.10f);
	glVertex3f(bottomOuterRight, bottomY, 0.0f);
	glVertex3f(topOuterRight, topY, 0.0f);

	glEnd();

	// Golden Strip & Base
	// Enable Polygon Offset to mathematically draw these exactly on top of the pillar body without physical Z-fighting or gaps.
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-1.0f, -1.0f);

	// Strip over the pillar
	glColor3f(0.70f, 0.50f, 0.10f);
	drawCurvedStrip(0.0f, 0.3f, 0.0f, 0.96f, 0.30f, 0.08f);

	// Pillar base 
	glColor3f(0.15f, 0.05f, 0.03f);
	drawCurvedStrip(0.0f, -2.2f, 0.0f, 1.2f, 0.4f, 0.10f);

	// QUAD overlapping the bottom to make it flat
	glBegin(GL_QUADS);
	glVertex3f(-0.60f, -2.4f, 0.0f);
	glVertex3f( 0.60f, -2.4f, 0.0f);
	glVertex3f( 0.60f, -2.8f, 0.0f);
	glVertex3f(-0.60f, -2.8f, 0.0f);
	glEnd();

	glDisable(GL_POLYGON_OFFSET_FILL);

	glPopMatrix();
}

static void drawLeftCurtain(void)
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

	// MAIN CURTAIN FABRIC
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

	// Curtain Folds
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.20f, 0.02f, 0.10f);
	float foldZ = z + 0.01f;

	glLineWidth(2.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);
		float foldX = -2.0f + (2.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glLineWidth(1.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);
		float foldX = -1.0f + (1.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

	glPopMatrix();
}

static void drawRightCurtain(void)
{
	glPushMatrix();
	glScalef(0.7f, 0.7f, 0.7f); // Match pillar scale

	float z = -0.5f;
	float topY = 3.0f;
	float bottomY = -2.1f;
	float step = 0.2f;

	// The right edge of the pillar to tuck the fabric behind
	float pillarRightEdge = -0.1f;

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

	// Curtain fabric
	glColor3f(0.55f, 0.10f, 0.35f);
	glBegin(GL_QUAD_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);
		float gatherSweep = -3.0f * (t * t);

		float fabricRightX = 3.0f + gatherSweep - 0.2f;
		float fabricLeftX = pillarRightEdge;

		glVertex3f(fabricLeftX, y, z);
		glVertex3f(fabricRightX, y, z);
	}
	glEnd();

	// Curtain Folds
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0.20f, 0.02f, 0.10f);
	float foldZ = z + 0.01f;

	glLineWidth(2.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step)
	{
		float t = (topY - y) / (topY - bottomY);
		float foldX = 2.0f + (-2.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glLineWidth(1.5f);
	glBegin(GL_LINE_STRIP);
	for (float y = topY; y >= bottomY; y -= step) 
	{
		float t = (topY - y) / (topY - bottomY);
		float foldX = 1.0f + (-1.2f * (t * t));
		glVertex3f(foldX, y, foldZ);
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

	glPopMatrix();
}

static void drawPillarDesign(void)
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

		drawCircleOutline(xOffset, circleY, zOffset, 0.025f, 16);
	}

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

static void drawPillarAndCurtain(void)
{
	drawLeftCurtain();
	drawRightCurtain();
	drawPillar();
	drawPillarDesign();
}

static void drawThroneRoom(void)
{
	float floorY = -3.0f;
	float ceilY = 15.0f;

	float bgX = 35.0f;
	float hallDepth = -35.0f;

	// Floor
	glColor3f(0.35f, 0.70f, 0.65f);
	glBegin(GL_QUADS);
	glVertex3f(-bgX, floorY, 2.0f);    
	glVertex3f( bgX, floorY, 2.0f);
	glVertex3f( bgX, floorY, hallDepth); 
	glVertex3f(-bgX, floorY, hallDepth);
	glEnd();

	// Floor Grid Lines
	glColor3f(0.2f, 0.5f, 0.45f); // Darker teal for lines
	glLineWidth(2.0f);
	glBegin(GL_LINES);

	// Horizontal lines
	for (float z = 2.0f; z >= hallDepth; z -= 2.0f)
	{
		// Left side tile line (stops at left carpet edge)
		glVertex3f(-bgX, floorY + 0.01f, z);
		glVertex3f(-1.6f, floorY + 0.01f, z);

		// Right side tile line (starts at right carpet edge)
		glVertex3f(1.6f, floorY + 0.01f, z);
		glVertex3f(bgX, floorY + 0.01f, z);
	}

	// Depth lines
	for (float x = -bgX; x <= bgX; x += 2.0f)
	{
		// Only draw the depth line if it is outside the carpet boundaries
		if (x <= -1.6f || x >= 1.6f)
		{
			glVertex3f(x, floorY + 0.01f, 2.0f);
			glVertex3f(x, floorY + 0.01f, hallDepth);
		}
	}
	glEnd();

	// Ceiling
	glColor3f(0.35f, 0.20f, 0.15f);
	glBegin(GL_QUADS);
	glVertex3f(-bgX, ceilY, hallDepth);
	glVertex3f( bgX, ceilY, hallDepth);
	glVertex3f( bgX, ceilY, 2.0f);       
	glVertex3f(-bgX, ceilY, 2.0f);
	glEnd();

	// Flat Back Wall
	glColor3f(0.75f, 0.45f, 0.65f);
	glBegin(GL_QUADS);
	glVertex3f(-bgX, floorY + 1.5f, hallDepth); 
	glVertex3f( bgX, floorY + 1.5f, hallDepth);
	glVertex3f( bgX, ceilY, hallDepth);         
	glVertex3f(-bgX, ceilY, hallDepth);
	glEnd();

	// Back Wall trim part

	// Black Band
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-bgX, floorY + 1.2f, hallDepth); 
	glVertex3f( bgX, floorY + 1.2f, hallDepth);
	glVertex3f( bgX, floorY + 1.5f, hallDepth); 
	glVertex3f(-bgX, floorY + 1.5f, hallDepth);
	glEnd();

	// Lower Red Trim
	glColor3f(0.7f, 0.15f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-bgX, floorY, hallDepth);      
	glVertex3f( bgX, floorY, hallDepth);
	glVertex3f( bgX, floorY + 1.2f, hallDepth); 
	glVertex3f(-bgX, floorY + 1.2f, hallDepth);
	glEnd();

	// 5. THE GOLDEN BACKDROP ARCH
	float archZ = hallDepth + 0.1f; // Drawn slightly in front of the wall
	float archCenterY = 2.0f;

	// Outer Orange/Dark Gold Arch
	glColor3f(0.85f, 0.55f, 0.15f);
	float outerRadius = 5.2f;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, archCenterY, archZ); // Center vertex

	for (int i = 0; i <= 180; i += 5) 
	{
		float angle = (float)i * (float)M_PI / 180.0f;
		glVertex3f(cosf(angle) * outerRadius, archCenterY + sinf(angle) * outerRadius, archZ);
	}
	glEnd();

	// Inner Bright Yellow Arch
	glColor3f(0.95f, 0.85f, 0.25f);
	float innerRadius = 4.6f;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, archCenterY, archZ + 0.05f); // Shifted slightly forward again
	for (int i = 0; i <= 180; i += 5) 
	{
		float angle = (float)i * (float)M_PI / 180.0f;
		glVertex3f(cosf(angle) * innerRadius, archCenterY + sinf(angle) * innerRadius, archZ + 0.05f);
	}
	glEnd();
}

static void drawThroneStage(void)
{
	float floorY = -3.0f;
	float stageTopY = -0.5f;     // Height of the throne stage

	// Coordinates matching room depth
	float backWallZ = -35.0f;    // Flush against the new back wall
	float stageFrontZ = -27.0f;  // Front edge of the raised flat stage
	float stairBaseZ = -21.0f;   // Where the stairs touch the teal floor

	float stageW = 10.0f;
	float stairW = 2.4f;         // Width of the stairs (slightly wider than carpet)

	glPushMatrix();

	// Main Floor carpet
	// Yellow Center
	glColor3f(0.95f, 0.85f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-1.2f, floorY + 0.015f, 2.0f);
	glVertex3f( 1.2f, floorY + 0.015f, 2.0f);
	glVertex3f( 1.2f, floorY + 0.015f, stairBaseZ);
	glVertex3f(-1.2f, floorY + 0.015f, stairBaseZ);
	glEnd();

	// Red Borders
	glColor3f(0.7f, 0.1f, 0.15f);
	glBegin(GL_QUADS);
	glVertex3f(-1.6f, floorY + 0.015f, 2.0f);
	glVertex3f(-1.2f, floorY + 0.015f, 2.0f);
	glVertex3f(-1.2f, floorY + 0.015f, stairBaseZ);
	glVertex3f(-1.6f, floorY + 0.015f, stairBaseZ);

	glVertex3f( 1.2f, floorY + 0.015f, 2.0f);
	glVertex3f( 1.6f, floorY + 0.015f, 2.0f);
	glVertex3f( 1.6f, floorY + 0.015f, stairBaseZ);
	glVertex3f( 1.2f, floorY + 0.015f, stairBaseZ);
	glEnd();

	// Cuboid shape stage
	glColor3f(0.8f, 0.6f, 0.2f); // Golden base
	glBegin(GL_QUADS);
	// Top Face
	glVertex3f(-stageW, stageTopY, backWallZ);
	glVertex3f( stageW, stageTopY, backWallZ);
	glVertex3f( stageW, stageTopY, stageFrontZ); 
	glVertex3f(-stageW, stageTopY, stageFrontZ);

	// Front Face (Left side of the stairs)
	glVertex3f(-stageW, floorY, stageFrontZ);
	glVertex3f(-stairW, floorY, stageFrontZ);
	glVertex3f(-stairW, stageTopY, stageFrontZ);
	glVertex3f(-stageW, stageTopY, stageFrontZ);

	// Front Face (Right side of the stairs)
	glVertex3f(stairW, floorY, stageFrontZ);
	glVertex3f(stageW, floorY, stageFrontZ);
	glVertex3f(stageW, stageTopY, stageFrontZ); 
	glVertex3f(stairW, stageTopY, stageFrontZ);
	glEnd();

	// Carpet on top of the stage
	glColor3f(0.95f, 0.85f, 0.2f); // Yellow
	glBegin(GL_QUADS);
	glVertex3f(-1.2f, stageTopY + 0.01f, backWallZ);
	glVertex3f( 1.2f, stageTopY + 0.01f, backWallZ);
	glVertex3f( 1.2f, stageTopY + 0.01f, stageFrontZ);
	glVertex3f(-1.2f, stageTopY + 0.01f, stageFrontZ);
	glEnd();

	glColor3f(0.7f, 0.1f, 0.15f); // Red
	glBegin(GL_QUADS);
	glVertex3f(-1.6f, stageTopY + 0.01f, backWallZ);
	glVertex3f(-1.2f, stageTopY + 0.01f, backWallZ);
	glVertex3f(-1.2f, stageTopY + 0.01f, stageFrontZ);
	glVertex3f(-1.6f, stageTopY + 0.01f, stageFrontZ);

	glVertex3f( 1.2f, stageTopY + 0.01f, backWallZ);
	glVertex3f( 1.6f, stageTopY + 0.01f, backWallZ);
	glVertex3f( 1.6f, stageTopY + 0.01f, stageFrontZ);
	glVertex3f( 1.2f, stageTopY + 0.01f, stageFrontZ);
	glEnd();

	// Stairs climbing up
	int numSteps = 5;
	float stepH = (stageTopY - floorY) / (float)numSteps;
	float stepD = (stairBaseZ - stageFrontZ) / (float)numSteps;

	for (int i = 0; i < numSteps; i++) 
	{
		// Calculate from the floor going UP towards the stage
		float curBotY = floorY + (i * stepH);
		float curTopY = curBotY + stepH;
		float curFrontZ = stairBaseZ - (i * stepD);
		float curBackZ = curFrontZ - stepD;

		// Riser (Vertical face pushing up)
		glColor3f(0.7f, 0.5f, 0.15f);
		glBegin(GL_QUADS);
		glVertex3f(-stairW, curBotY, curFrontZ); 
		glVertex3f( stairW, curBotY, curFrontZ);
		glVertex3f( stairW, curTopY, curFrontZ);
		glVertex3f(-stairW, curTopY, curFrontZ);
		glEnd();

		// Riser Carpet (Yellow)
		glColor3f(0.85f, 0.75f, 0.15f);
		glBegin(GL_QUADS);
		glVertex3f(-1.2f, curBotY, curFrontZ + 0.01f);
		glVertex3f( 1.2f, curBotY, curFrontZ + 0.01f);
		glVertex3f( 1.2f, curTopY, curFrontZ + 0.01f);
		glVertex3f(-1.2f, curTopY, curFrontZ + 0.01f);
		glEnd();

		// Riser Carpet (Red)
		glColor3f(0.6f, 0.08f, 0.12f);
		glBegin(GL_QUADS);
		glVertex3f(-1.6f, curBotY, curFrontZ + 0.01f);
		glVertex3f(-1.2f, curBotY, curFrontZ + 0.01f);
		glVertex3f(-1.2f, curTopY, curFrontZ + 0.01f); 
		glVertex3f(-1.6f, curTopY, curFrontZ + 0.01f);
		glVertex3f( 1.2f, curBotY, curFrontZ + 0.01f);
		glVertex3f( 1.6f, curBotY, curFrontZ + 0.01f);
		glVertex3f( 1.6f, curTopY, curFrontZ + 0.01f); 
		glVertex3f( 1.2f, curTopY, curFrontZ + 0.01f);
		glEnd();

		// Tread (Horizontal face pushing back)
		glColor3f(0.8f, 0.6f, 0.2f);
		glBegin(GL_QUADS);
		glVertex3f(-stairW, curTopY, curBackZ);
		glVertex3f( stairW, curTopY, curBackZ);
		glVertex3f( stairW, curTopY, curFrontZ);
		glVertex3f(-stairW, curTopY, curFrontZ);
		glEnd();

		// Tread Carpet (Yellow)
		glColor3f(0.95f, 0.85f, 0.2f);
		glBegin(GL_QUADS);
		glVertex3f(-1.2f, curTopY + 0.01f, curBackZ); 
		glVertex3f( 1.2f, curTopY + 0.01f, curBackZ);
		glVertex3f( 1.2f, curTopY + 0.01f, curFrontZ);
		glVertex3f(-1.2f, curTopY + 0.01f, curFrontZ);
		glEnd();

		// Tread Carpet (Red)
		glColor3f(0.7f, 0.1f, 0.15f);
		glBegin(GL_QUADS);
		glVertex3f(-1.6f, curTopY + 0.01f, curBackZ);
		glVertex3f(-1.2f, curTopY + 0.01f, curBackZ);
		glVertex3f(-1.2f, curTopY + 0.01f, curFrontZ); 
		glVertex3f(-1.6f, curTopY + 0.01f, curFrontZ);
		glVertex3f( 1.2f, curTopY + 0.01f, curBackZ);
		glVertex3f( 1.6f, curTopY + 0.01f, curBackZ);
		glVertex3f( 1.6f, curTopY + 0.01f, curFrontZ);
		glVertex3f( 1.2f, curTopY + 0.01f, curFrontZ);
		glEnd();

		// Step Crease lines for 3D clarity
		glColor3f(0.2f, 0.1f, 0.0f);
		glLineWidth(2.5f);
		glBegin(GL_LINES);
		glVertex3f(-stairW, curTopY + 0.015f, curFrontZ + 0.015f);
		glVertex3f( stairW, curTopY + 0.015f, curFrontZ + 0.015f);
		glEnd();
	}

	glPopMatrix();
}

// =============================================================================
// 2D / 2.5D CARTOON CEL-STYLE PRIMITIVES & HELPERS
// =============================================================================

static void drawFilledEllipse(float cx, float cy, float rx, float ry, float zVal, float r, float g, float b, int segments)
{
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(cx, cy, zVal);
	for (int i = 0; i <= segments; i++)
	{
		float theta = 2.0f * (float)M_PI * (float)i / (float)segments;
		glVertex3f(cx + rx * cosf(theta), cy + ry * sinf(theta), zVal);
	}
	glEnd();
}

static void drawEllipseOutline(float cx, float cy, float rx, float ry, float zVal, float lineWidth, float r, float g, float b, int segments)
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(lineWidth);
	glColor3f(r, g, b);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * (float)M_PI * (float)i / (float)segments;
		glVertex3f(cx + rx * cosf(theta), cy + ry * sinf(theta), zVal);
	}
	glEnd();

	glLineWidth(1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

static void drawArc(float cx, float cy, float rx, float ry, float zVal, float startAngle, float endAngle, float lineWidth, float r, float g, float b, int segments)
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(lineWidth);
	glColor3f(r, g, b);

	glBegin(GL_LINE_STRIP);
	float startRad = startAngle * (float)M_PI / 180.0f;
	float endRad = endAngle * (float)M_PI / 180.0f;
	for (int i = 0; i <= segments; i++)
	{
		float theta = startRad + (endRad - startRad) * ((float)i / (float)segments);
		glVertex3f(cx + rx * cosf(theta), cy + ry * sinf(theta), zVal);
	}
	glEnd();

	glLineWidth(1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

static void drawFilledQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float zVal, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(x1, y1, zVal);
	glVertex3f(x2, y2, zVal);
	glVertex3f(x3, y3, zVal);
	glVertex3f(x4, y4, zVal);
	glEnd();
}

static void drawQuadOutline(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float zVal, float lineWidth, float r, float g, float b)
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(lineWidth);
	glColor3f(r, g, b);

	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y1, zVal);
	glVertex3f(x2, y2, zVal);
	glVertex3f(x3, y3, zVal);
	glVertex3f(x4, y4, zVal);
	glEnd();

	glLineWidth(1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

static void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float zVal, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	glVertex3f(x1, y1, zVal);
	glVertex3f(x2, y2, zVal);
	glVertex3f(x3, y3, zVal);
	glEnd();
}

static void drawTriangleOutline(float x1, float y1, float x2, float y2, float x3, float y3, float zVal, float lineWidth, float r, float g, float b)
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(lineWidth);
	glColor3f(r, g, b);

	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y1, zVal);
	glVertex3f(x2, y2, zVal);
	glVertex3f(x3, y3, zVal);
	glEnd();

	glLineWidth(1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

static void drawLine(float x1, float y1, float x2, float y2, float zVal, float lineWidth, float r, float g, float b)
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(lineWidth);
	glColor3f(r, g, b);

	glBegin(GL_LINES);
	glVertex3f(x1, y1, zVal);
	glVertex3f(x2, y2, zVal);
	glEnd();

	glLineWidth(1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}

// ============================================================================
// KING DHANA NANDA & ROYAL THRONE (FROM dahanad.txt)
// Win32 + WGL + OpenGL fixed-function pipeline
// Keys: 'M' or 'm' cycle mode: royal idle -> arrogant laugh -> anger (grips talwar)
// ============================================================================

// Animation Mode & State Variables (defined as static at top of file)

// Mathematical Helper Functions from dahanad.txt
static void rliDrawPolygon(const float *rliXY, int rliCount, float zVal, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	for (int rliIndex = 0; rliIndex < rliCount; rliIndex++)
		glVertex3f(rliXY[2 * rliIndex], rliXY[2 * rliIndex + 1], zVal);
	glEnd();
}

static void rliDrawSegment(float x0, float y0, float x1, float y1, float w0, float w1, float zVal, float r, float g, float b)
{
	float rliDx = x1 - x0, rliDy = y1 - y0;
	float rliLen = sqrtf(rliDx * rliDx + rliDy * rliDy);
	float rliNx, rliNy;
	if (rliLen < 0.0001f)
		return;
	rliNx = -rliDy / rliLen;
	rliNy =  rliDx / rliLen;
	drawFilledQuad(x0 + rliNx * w0 * 0.5f, y0 + rliNy * w0 * 0.5f,
	               x1 + rliNx * w1 * 0.5f, y1 + rliNy * w1 * 0.5f,
	               x1 - rliNx * w1 * 0.5f, y1 - rliNy * w1 * 0.5f,
	               x0 - rliNx * w0 * 0.5f, y0 - rliNy * w0 * 0.5f, zVal, r, g, b);
	drawFilledEllipse(x0, y0, w0 * 0.5f, w0 * 0.5f, zVal, r, g, b, 18);
	drawFilledEllipse(x1, y1, w1 * 0.5f, w1 * 0.5f, zVal, r, g, b, 18);
}

static void rliDrawRibbon(const float *rliXY, int rliCount, float w0, float w1, float zVal, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLE_STRIP);
	for (int rliIndex = 0; rliIndex < rliCount; rliIndex++)
	{
		int rliA = rliIndex > 0 ? rliIndex - 1 : rliIndex;
		int rliB = rliIndex < rliCount - 1 ? rliIndex + 1 : rliIndex;
		float rliTx = rliXY[2 * rliB] - rliXY[2 * rliA];
		float rliTy = rliXY[2 * rliB + 1] - rliXY[2 * rliA + 1];
		float rliLen = sqrtf(rliTx * rliTx + rliTy * rliTy);
		float rliT = rliCount > 1 ? (float)rliIndex / (float)(rliCount - 1) : 0.0f;
		float rliHw = 0.5f * (w0 + (w1 - w0) * rliT);
		float rliNx = rliLen > 0.0f ? -rliTy / rliLen : 0.0f;
		float rliNy = rliLen > 0.0f ?  rliTx / rliLen : 1.0f;
		glVertex3f(rliXY[2 * rliIndex] + rliNx * rliHw, rliXY[2 * rliIndex + 1] + rliNy * rliHw, zVal);
		glVertex3f(rliXY[2 * rliIndex] - rliNx * rliHw, rliXY[2 * rliIndex + 1] - rliNy * rliHw, zVal);
	}
	glEnd();
}

static float rliLerp(float a, float b, float t) 
{ 
	return(a + (b - a) * t); 
}

// Palette from dahanad.txt
#define RLI_SKIN         0.86f, 0.64f, 0.46f
#define RLI_SKIN_SHADE   0.74f, 0.53f, 0.36f
#define RLI_HAIR         0.12f, 0.08f, 0.05f
#define RLI_GOLD         0.95f, 0.78f, 0.22f
#define RLI_GOLD_DARK    0.76f, 0.56f, 0.12f
#define RLI_RUBY         0.85f, 0.08f, 0.12f
#define RLI_VEST         0.13f, 0.28f, 0.62f
#define RLI_VEST_SHADE   0.09f, 0.20f, 0.48f
#define RLI_DHOTI        0.98f, 0.82f, 0.25f
#define RLI_DHOTI_SHADE  0.86f, 0.66f, 0.12f
#define RLI_VELVET       0.72f, 0.09f, 0.10f
#define RLI_VELVET_DARK  0.52f, 0.05f, 0.07f

#define RLI_SEAT_TOP_Y  -1.42f
#define RLI_DAIS_TOP_Y  -3.05f

// Royal Throne Front from dahanad.txt
static void rliDrawThroneFront(void)
{
	// gold frame (drawn bigger, behind the velvet)
	drawFilledEllipse(0.0f, 1.05f, 1.42f, 1.02f, -0.32f, RLI_GOLD_DARK, 50);
	drawFilledQuad(-1.42f, 1.05f, 1.42f, 1.05f, 1.42f, -1.5f, -1.42f, -1.5f, -0.32f, RLI_GOLD_DARK);
	drawFilledEllipse(0.0f, 1.05f, 1.34f, 0.95f, -0.31f, RLI_GOLD, 50);
	drawFilledQuad(-1.34f, 1.05f, 1.34f, 1.05f, 1.34f, -1.5f, -1.34f, -1.5f, -0.31f, RLI_GOLD);

	// red velvet back with tufting buttons
	drawFilledEllipse(0.0f, 1.05f, 1.16f, 0.80f, -0.30f, RLI_VELVET, 50);
	drawFilledQuad(-1.16f, 1.05f, 1.16f, 1.05f, 1.16f, -1.5f, -1.16f, -1.5f, -0.30f, RLI_VELVET);
	for (int rliRow = 0; rliRow < 5; rliRow++)
	{
		for (int rliCol = -3; rliCol <= 3; rliCol++)
		{
			float rliX = 0.30f * (float)rliCol + ((rliRow % 2) ? 0.15f : 0.0f);
			float rliY = 1.45f - 0.55f * (float)rliRow;
			if (fabsf(rliX) < 1.05f)
				drawFilledEllipse(rliX, rliY, 0.035f, 0.035f, -0.29f, RLI_VELVET_DARK, 10);
		}
	}

	// crest on top: gold kalash finial with a ruby
	drawFilledQuad(-0.05f, 2.02f, 0.05f, 2.02f, 0.05f, 2.42f, -0.05f, 2.42f, -0.30f, RLI_GOLD_DARK);
	drawFilledEllipse(0.0f, 2.48f, 0.20f, 0.13f, -0.30f, RLI_GOLD, 24);
	drawFilledTriangle(-0.10f, 2.56f, 0.10f, 2.56f, 0.0f, 2.84f, -0.30f, RLI_GOLD);
	drawFilledEllipse(0.0f, 2.48f, 0.07f, 0.07f, -0.29f, RLI_RUBY, 16);

	// side posts with round gold knobs
	for (int rliSide = -1; rliSide <= 1; rliSide += 2)
	{
		float rliS = (float)rliSide;
		drawFilledQuad(rliS * 1.30f, 0.30f, rliS * 1.48f, 0.30f, rliS * 1.48f, -1.5f, rliS * 1.30f, -1.5f, -0.28f, RLI_GOLD_DARK);
		drawFilledEllipse(rliS * 1.39f, 0.38f, 0.13f, 0.13f, -0.27f, RLI_GOLD, 24);

		// armrest: red padded top on a gold scrolled bar, curl at the front
		drawFilledQuad(rliS * 0.95f, -0.80f, rliS * 1.55f, -0.80f, rliS * 1.55f, -1.00f, rliS * 0.95f, -1.00f, -0.20f, RLI_GOLD);
		drawFilledQuad(rliS * 0.98f, -0.70f, rliS * 1.52f, -0.70f, rliS * 1.52f, -0.82f, rliS * 0.98f, -0.82f, -0.19f, RLI_VELVET);
		drawFilledEllipse(rliS * 1.55f, -0.90f, 0.14f, 0.14f, -0.19f, RLI_GOLD, 24);
		drawArc(rliS * 1.55f, -0.90f, 0.08f, 0.08f, -0.18f, 0.0f, 300.0f, 3.0f, RLI_GOLD_DARK, 16);
		drawFilledQuad(rliS * 1.18f, -1.00f, rliS * 1.40f, -1.00f, rliS * 1.36f, -1.50f, rliS * 1.22f, -1.50f, -0.20f, RLI_GOLD_DARK);
	}

	// seat cushion with gold piping and the front skirt
	drawFilledQuad(-1.45f, -1.42f, 1.45f, -1.42f, 1.50f, -1.80f, -1.50f, -1.80f, -0.18f, RLI_VELVET);
	drawFilledQuad(-1.45f, -1.40f, 1.45f, -1.40f, 1.45f, -1.46f, -1.45f, -1.46f, -0.17f, RLI_GOLD);
	drawFilledQuad(-1.52f, -1.80f, 1.52f, -1.80f, 1.45f, -2.70f, -1.45f, -2.70f, -0.18f, RLI_GOLD);
	drawFilledQuad(-1.44f, -1.86f, 1.44f, -1.86f, 1.38f, -2.62f, -1.38f, -2.62f, -0.175f, RLI_VELVET_DARK);

	for (int rliPanel = -2; rliPanel <= 2; rliPanel++)
	{
		float rliX = 0.55f * (float)rliPanel;
		drawFilledQuad(rliX - 0.22f, -1.94f, rliX + 0.22f, -1.94f, rliX + 0.21f, -2.55f, rliX - 0.21f, -2.55f, -0.17f, RLI_GOLD);
		drawFilledQuad(rliX - 0.18f, -1.98f, rliX + 0.18f, -1.98f, rliX + 0.17f, -2.51f, rliX - 0.17f, -2.51f, -0.165f, RLI_VELVET);
		drawFilledEllipse(rliX, -2.25f, 0.06f, 0.08f, -0.16f, RLI_GOLD, 14);
		drawFilledEllipse(rliX, -2.25f, 0.035f, 0.05f, -0.155f, RLI_RUBY, 12);
	}

	// lion-paw legs and the stepped dais
	for (int rliSide = -1; rliSide <= 1; rliSide += 2)
	{
		float rliS = (float)rliSide;
		drawFilledQuad(rliS * 1.20f, -2.70f, rliS * 1.45f, -2.70f, rliS * 1.48f, -3.00f, rliS * 1.17f, -3.00f, -0.17f, RLI_GOLD_DARK);
		drawFilledEllipse(rliS * 1.33f, -3.02f, 0.20f, 0.09f, -0.16f, RLI_GOLD, 20);
		for (int rliToe = -1; rliToe <= 1; rliToe++)
			drawArc(rliS * 1.33f + 0.07f * (float)rliToe, -3.02f, 0.035f, 0.05f, -0.15f, 180.0f, 360.0f, 2.0f, RLI_GOLD_DARK, 8);
	}
	drawFilledQuad(-2.0f, -3.05f, 2.0f, -3.05f, 2.15f, -3.22f, -2.15f, -3.22f, -0.16f, RLI_VELVET_DARK);
	drawFilledQuad(-2.15f, -3.22f, 2.15f, -3.22f, 2.30f, -3.40f, -2.30f, -3.40f, -0.16f, RLI_GOLD_DARK);
}

// Half-width of the cone crown at height y
static float rliCrownHalfWidth(float rliY)
{
	static const float rliYs[5] = { 0.40f, 0.70f, 0.95f, 1.25f, 1.45f };
	static const float rliWs[5] = { 0.47f, 0.40f, 0.30f, 0.15f, 0.0f };
	if (rliY <= rliYs[0]) return(rliWs[0]);
	for (int rliI = 0; rliI < 4; rliI++)
	{
		if (rliY <= rliYs[rliI + 1])
			return(rliLerp(rliWs[rliI], rliWs[rliI + 1], (rliY - rliYs[rliI]) / (rliYs[rliI + 1] - rliYs[rliI])));
	}
	return(0.0f);
}

// King's Head with Cone Mukut and Expressions from dahanad.txt
static void rliDrawKingHead(float rliTimeVal)
{
	float rliBlink = (fmodf(rliTimeVal, 3.8f) < 0.12f) ? 1.0f : 0.0f;
	float rliEyeOpen = (1.0f - rliBlink) * (1.0f - 0.55f * rliLaughBlend);
	float rliBrowIn = 0.20f - 0.07f * rliAngerBlend + 0.04f * rliLaughBlend;
	float rliMouthOpen = 0.06f * rliLaughBlend + 0.025f * rliAngerBlend + 0.045f * g_kingMouthOpen;

	// long dark hair falling behind the shoulders
	drawFilledEllipse(0.0f, -0.05f, 0.56f, 0.70f, -0.04f, RLI_HAIR, 40);
	drawFilledEllipse(-0.48f, -0.55f, 0.20f, 0.42f, -0.04f, RLI_HAIR, 24);
	drawFilledEllipse( 0.48f, -0.55f, 0.20f, 0.42f, -0.04f, RLI_HAIR, 24);

	// ears with heavy gold kundal hoops
	for (int rliSide = -1; rliSide <= 1; rliSide += 2)
	{
		float rliS = (float)rliSide;
		drawFilledEllipse(rliS * 0.45f, 0.02f, 0.09f, 0.16f, 0.01f, RLI_SKIN_SHADE, 24);
		drawArc(rliS * 0.45f, 0.02f, 0.05f, 0.10f, 0.015f, 40.0f, 320.0f, 1.5f, 0.62f, 0.42f, 0.28f, 14);
		drawEllipseOutline(rliS * 0.46f, -0.22f, 0.07f, 0.09f, 0.03f, 5.0f, RLI_GOLD, 24);
		drawFilledEllipse(rliS * 0.46f, -0.32f, 0.03f, 0.04f, 0.035f, RLI_RUBY, 12);
	}

	// face and strong jaw
	drawFilledEllipse(0.0f, 0.08f, 0.44f, 0.56f, 0.02f, RLI_SKIN, 60);
	drawFilledEllipse(0.0f, -0.18f, 0.37f, 0.36f, 0.02f, RLI_SKIN, 50);
	drawArc(0.0f, -0.40f, 0.10f, 0.04f, 0.03f, 200.0f, 340.0f, 1.8f, RLI_SKIN_SHADE, 15);

	// red tilak
	drawFilledQuad(-0.025f, 0.42f, 0.025f, 0.42f, 0.018f, 0.24f, -0.018f, 0.24f, 0.05f, 0.85f, 0.12f, 0.06f);
	drawFilledEllipse(0.0f, 0.22f, 0.022f, 0.026f, 0.055f, 0.98f, 0.80f, 0.20f, 12);

	// fierce eyes with kohl
	for (int rliSide = -1; rliSide <= 1; rliSide += 2)
	{
		float rliX = 0.17f * (float)rliSide;
		drawFilledEllipse(rliX, 0.10f, 0.090f, 0.050f * rliEyeOpen + 0.004f, 0.05f, 0.98f, 0.98f, 0.95f, 25);
		if (rliEyeOpen > 0.2f)
		{
			drawFilledEllipse(rliX - 0.01f * (float)rliSide, 0.10f, 0.040f, 0.040f * rliEyeOpen, 0.07f, 0.24f, 0.13f, 0.07f, 20);
			drawFilledEllipse(rliX - 0.01f * (float)rliSide, 0.10f, 0.020f, 0.020f * rliEyeOpen, 0.08f, 0.02f, 0.02f, 0.02f, 15);
			drawFilledEllipse(rliX + 0.005f, 0.112f, 0.007f, 0.007f, 0.09f, 1.0f, 1.0f, 1.0f, 8);
		}
		drawArc(rliX, 0.10f, 0.092f, 0.052f * rliEyeOpen + 0.004f, 0.09f, 0.0f, 180.0f, 2.5f, 0.06f, 0.04f, 0.03f, 20);

		// heavy brow
		glLineWidth(6.0f);
		glColor3f(0.10f, 0.06f, 0.04f);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.33f * (float)rliSide, 0.20f, 0.09f);
		glVertex3f(0.19f * (float)rliSide, 0.25f, 0.09f);
		glVertex3f(0.05f * (float)rliSide, rliBrowIn, 0.09f);
		glEnd();
		glLineWidth(1.0f);
	}

	// nose
	drawFilledTriangle(0.0f, 0.16f, -0.05f, -0.08f, 0.05f, -0.08f, 0.05f, 0.80f, 0.58f, 0.40f);
	drawFilledEllipse(0.0f, -0.08f, 0.065f, 0.040f, 0.06f, 0.84f, 0.62f, 0.44f, 20);
	drawFilledEllipse(-0.04f, -0.095f, 0.018f, 0.010f, 0.065f, 0.45f, 0.28f, 0.18f, 8);
	drawFilledEllipse( 0.04f, -0.095f, 0.018f, 0.010f, 0.065f, 0.45f, 0.28f, 0.18f, 8);

	// mouth
	if (rliMouthOpen > 0.01f)
	{
		drawFilledEllipse(0.0f, -0.25f, 0.11f, rliMouthOpen + 0.01f, 0.06f, 0.30f, 0.06f, 0.06f, 24);
		drawFilledQuad(-0.08f, -0.235f, 0.08f, -0.235f, 0.08f, -0.25f, -0.08f, -0.25f, 0.065f, 0.98f, 0.97f, 0.92f);
	}
	else
	{
		drawFilledEllipse(0.0f, -0.25f, 0.10f, 0.022f, 0.06f, 0.70f, 0.34f, 0.30f, 25);
	}
	drawFilledEllipse(0.0f, -0.29f - rliMouthOpen * 0.6f, 0.08f, 0.020f, 0.06f, 0.74f, 0.38f, 0.32f, 20);

	// thick royal moustache curling upwards at both ends
	for (int rliSide = -1; rliSide <= 1; rliSide += 2)
	{
		float rliS = (float)rliSide;
		float rliMoustache[] = {
			0.0f * rliS, -0.15f,
			0.10f * rliS, -0.18f,
			0.22f * rliS, -0.17f,
			0.31f * rliS, -0.10f,
			0.32f * rliS, -0.02f,
			0.27f * rliS,  0.01f,
		};
		rliDrawRibbon(rliMoustache, 6, 0.075f, 0.018f, 0.075f, 0.10f, 0.06f, 0.04f);
	}

	// MUKUT: tall cone-shaped golden crown
	{
		static const float rliOutline[] = {
			0.47f, 0.40f, 0.40f, 0.70f, 0.30f, 0.95f, 0.15f, 1.25f, 0.0f, 1.45f
		};
		float rliLeft[12], rliRight[12];
		rliLeft[0] = 0.0f; rliLeft[1] = 0.40f;
		rliRight[0] = 0.0f; rliRight[1] = 0.40f;
		for (int rliP = 0; rliP < 5; rliP++)
		{
			rliRight[2 + 2 * rliP] =  rliOutline[2 * rliP];
			rliRight[3 + 2 * rliP] =  rliOutline[2 * rliP + 1];
			rliLeft[2 + 2 * rliP]  = -rliOutline[2 * (4 - rliP)];
			rliLeft[3 + 2 * rliP]  =  rliOutline[2 * (4 - rliP) + 1];
		}
		rliDrawPolygon(rliLeft, 6, 0.10f, RLI_GOLD);
		rliDrawPolygon(rliRight, 6, 0.10f, 0.84f, 0.62f, 0.14f);
		drawFilledQuad(-0.22f, 0.42f, -0.12f, 0.42f, -0.05f, 1.20f, -0.09f, 1.20f, 0.101f, 1.0f, 0.90f, 0.55f);
	}

	// jewelled bands
	for (int rliBand = 0; rliBand < 3; rliBand++)
	{
		float rliY = 0.62f + 0.28f * (float)rliBand;
		float rliHw = rliCrownHalfWidth(rliY);
		drawArc(0.0f, rliY + 0.05f, rliHw, 0.06f, 0.11f, 180.0f, 360.0f, 6.0f, RLI_GOLD_DARK, 24);
		for (int rliGem = -2; rliGem <= 2; rliGem++)
		{
			float rliGx = rliHw * 0.38f * (float)rliGem;
			float rliGy = rliY + 0.05f - 0.06f * sqrtf(fmaxf(0.0f, 1.0f - (rliGx / rliHw) * (rliGx / rliHw)));
			if ((rliGem + rliBand) % 2 == 0)
				drawFilledEllipse(rliGx, rliGy, 0.030f, 0.030f, 0.12f, 0.10f, 0.62f, 0.30f, 12);
			else
				drawFilledEllipse(rliGx, rliGy, 0.030f, 0.030f, 0.12f, RLI_RUBY, 12);
		}
	}

	// base rim
	drawFilledQuad(-0.50f, 0.50f, 0.50f, 0.50f, 0.48f, 0.37f, -0.48f, 0.37f, 0.115f, RLI_GOLD_DARK);
	drawArc(0.0f, 0.47f, 0.47f, 0.06f, 0.12f, 180.0f, 360.0f, 4.0f, RLI_GOLD, 24);
	for (int rliPearl = 0; rliPearl < 11; rliPearl++)
	{
		float rliT = (float)rliPearl / 10.0f;
		float rliX = -0.44f + 0.88f * rliT;
		float rliY = 0.43f - 0.05f * sinf(rliT * (float)M_PI);
		drawFilledEllipse(rliX, rliY, 0.021f, 0.021f, 0.125f, 0.98f, 0.96f, 0.90f, 10);
	}
	drawFilledTriangle(-0.50f, 0.50f, -0.62f, 0.62f, -0.48f, 0.37f, 0.11f, RLI_GOLD);
	drawFilledTriangle( 0.50f, 0.50f,  0.62f, 0.62f,  0.48f, 0.37f, 0.11f, 0.84f, 0.62f, 0.14f);

	// centre jewel
	drawFilledEllipse(0.0f, 0.70f, 0.10f, 0.13f, 0.13f, RLI_GOLD, 24);
	drawFilledEllipse(0.0f, 0.70f, 0.060f, 0.085f, 0.135f, RLI_RUBY, 20);
	drawFilledEllipse(0.015f, 0.73f, 0.016f, 0.022f, 0.14f, 1.0f, 0.70f, 0.70f, 8);
	for (int rliDrop = -1; rliDrop <= 1; rliDrop++)
		drawFilledEllipse(0.05f * (float)rliDrop, 0.55f, 0.016f, 0.020f, 0.135f, 0.98f, 0.96f, 0.90f, 8);

	// finial
	drawFilledEllipse(0.0f, 1.47f, 0.07f, 0.06f, 0.12f, RLI_GOLD, 20);
	drawFilledEllipse(0.0f, 1.47f, 0.030f, 0.030f, 0.125f, RLI_RUBY, 12);
	drawFilledTriangle(-0.035f, 1.51f, 0.035f, 1.51f, 0.0f, 1.66f, 0.12f, RLI_GOLD);
}

// King Dhana Nanda Full Character from dahanad.txt
static void rliDrawDhanaNandaCharacter(void)
{
	float rliBreathe = 0.0f; // Firm, regal seated posture (no dancing/bobbing)
	float rliLean = rliLerp(-5.0f, 0.0f, rliAngerBlend);
	float rliHeadTilt = 4.0f * rliLaughBlend - 3.0f * rliAngerBlend; // Static regal posture
	float rliLaughBob = 0.0f; // No vertical bouncing or dancing on throne

	float rliHandX = rliLerp(-0.72f, -0.76f, rliAngerBlend);
	float rliHandY = rliLerp(-1.05f, -0.75f, rliAngerBlend);

	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0f);
	glScalef(0.82f, 0.82f, 0.82f);

	// LEGS & DHOTI
	{
		float rliLap[] = { -0.62f, -1.28f, 0.62f, -1.28f, 0.72f, -1.62f, 0.55f, -1.85f, -0.55f, -1.85f, -0.72f, -1.62f };
		rliDrawPolygon(rliLap, 6, -0.05f, RLI_DHOTI);
	}
	drawArc(0.0f, -1.50f, 0.70f, 0.36f, -0.045f, 200.0f, 340.0f, 3.0f, RLI_DHOTI_SHADE, 24);

	// left leg
	rliDrawSegment(0.32f, -1.62f, 0.36f, -2.55f, 0.52f, 0.42f, -0.042f, RLI_DHOTI_SHADE);
	rliDrawSegment(0.32f, -1.62f, 0.36f, -2.55f, 0.46f, 0.36f, -0.04f, RLI_DHOTI);
	drawArc(0.30f, -2.05f, 0.18f, 0.40f, -0.03f, 250.0f, 300.0f, 2.0f, RLI_DHOTI_SHADE, 10);
	drawFilledQuad(0.17f, -2.50f, 0.55f, -2.50f, 0.54f, -2.60f, 0.18f, -2.60f, -0.03f, RLI_GOLD);
	rliDrawSegment(0.36f, -2.58f, 0.38f, -2.92f, 0.15f, 0.12f, -0.045f, RLI_SKIN);
	drawFilledQuad(0.30f, -2.84f, 0.46f, -2.84f, 0.46f, -2.89f, 0.30f, -2.89f, -0.03f, RLI_GOLD);
	drawFilledEllipse(0.39f, RLI_DAIS_TOP_Y + 0.06f, 0.12f, 0.06f, -0.03f, RLI_SKIN, 20);
	for (int rliToe = 0; rliToe < 5; rliToe++)
		drawFilledEllipse(0.31f + 0.04f * (float)rliToe, RLI_DAIS_TOP_Y + 0.03f, 0.018f, 0.018f, -0.025f, RLI_SKIN_SHADE, 8);

	// right leg
	rliDrawSegment(-0.32f, -1.62f, -0.36f, -2.55f, 0.52f, 0.42f, -0.042f, RLI_DHOTI_SHADE);
	rliDrawSegment(-0.32f, -1.62f, -0.36f, -2.55f, 0.46f, 0.36f, -0.04f, RLI_DHOTI);
	drawArc(-0.30f, -2.05f, 0.18f, 0.40f, -0.03f, 240.0f, 290.0f, 2.0f, RLI_DHOTI_SHADE, 10);
	drawFilledQuad(-0.55f, -2.50f, -0.17f, -2.50f, -0.18f, -2.60f, -0.54f, -2.60f, -0.03f, RLI_GOLD);
	rliDrawSegment(-0.36f, -2.58f, -0.38f, -2.92f, 0.15f, 0.12f, -0.045f, RLI_SKIN);
	drawFilledQuad(-0.46f, -2.84f, -0.30f, -2.84f, -0.30f, -2.89f, -0.46f, -2.89f, -0.03f, RLI_GOLD);
	drawFilledEllipse(-0.39f, RLI_DAIS_TOP_Y + 0.06f, 0.12f, 0.06f, -0.03f, RLI_SKIN, 20);
	for (int rliToe = 0; rliToe < 5; rliToe++)
		drawFilledEllipse(-0.47f + 0.04f * (float)rliToe, RLI_DAIS_TOP_Y + 0.03f, 0.018f, 0.018f, -0.025f, RLI_SKIN_SHADE, 8);

	// UPPER BODY (Firm, steady regal seated posture - no dancing on throne)
	glPushMatrix();
	glTranslatef(0.0f, -1.35f, 0.0f);
	glRotatef(rliLean, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 1.35f, 0.0f);

	// torso
	drawFilledQuad(-0.54f, 0.0f, 0.54f, 0.0f, 0.44f, -1.35f, -0.44f, -1.35f, 0.0f, RLI_SKIN);
	drawArc(-0.18f, -0.34f, 0.20f, 0.13f, 0.01f, 190.0f, 350.0f, 2.0f, RLI_SKIN_SHADE, 20);
	drawArc( 0.18f, -0.34f, 0.20f, 0.13f, 0.01f, 190.0f, 350.0f, 2.0f, RLI_SKIN_SHADE, 20);
	drawArc(0.0f, -0.70f, 0.08f, 0.06f, 0.015f, 180.0f, 360.0f, 1.5f, RLI_SKIN_SHADE, 12);
	drawArc(0.0f, -0.92f, 0.07f, 0.05f, 0.015f, 180.0f, 360.0f, 1.5f, RLI_SKIN_SHADE, 12);

	// shoulder deltoids
	drawFilledEllipse(-0.55f, -0.06f, 0.20f, 0.22f, 0.005f, RLI_SKIN, 25);
	drawFilledEllipse( 0.55f, -0.06f, 0.20f, 0.22f, 0.005f, RLI_SKIN, 25);

	// blue sleeveless vest
	{
		float rliLeftPanel[]  = { -0.58f, 0.02f, -0.24f, 0.04f, -0.05f, -0.80f, -0.08f, -1.33f, -0.47f, -1.33f, -0.52f, -0.40f };
		float rliRightPanel[] = {  0.24f, 0.04f,  0.58f, 0.02f,  0.52f, -0.40f,  0.47f, -1.33f,  0.08f, -1.33f,  0.05f, -0.80f };
		rliDrawPolygon(rliLeftPanel, 6, 0.02f, RLI_VEST);
		rliDrawPolygon(rliRightPanel, 6, 0.02f, RLI_VEST);
		drawFilledQuad(-0.10f, -0.80f, 0.10f, -0.80f, 0.10f, -1.33f, -0.10f, -1.33f, 0.021f, RLI_VEST_SHADE);
		drawArc(-0.34f, -0.78f, 0.10f, 0.40f, 0.022f, 100.0f, 260.0f, 2.0f, RLI_VEST_SHADE, 12);
		drawArc( 0.34f, -0.78f, 0.10f, 0.40f, 0.022f, -80.0f,  80.0f, 2.0f, RLI_VEST_SHADE, 12);
	}
	glLineWidth(7.0f);
	glColor3f(RLI_GOLD);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.24f, 0.04f, 0.03f); glVertex3f(-0.05f, -0.80f, 0.03f); glVertex3f(-0.05f, -1.30f, 0.03f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.24f, 0.04f, 0.03f); glVertex3f(0.05f, -0.80f, 0.03f); glVertex3f(0.05f, -1.30f, 0.03f);
	glEnd();
	glLineWidth(1.0f);
	drawArc(-0.56f, -0.22f, 0.10f, 0.26f, 0.03f, 280.0f, 440.0f, 6.0f, RLI_GOLD, 14);
	drawArc( 0.56f, -0.22f, 0.10f, 0.26f, 0.03f, 100.0f, 260.0f, 6.0f, RLI_GOLD, 14);

	// belt and sash
	drawFilledQuad(-0.48f, -1.20f, 0.48f, -1.20f, 0.46f, -1.36f, -0.46f, -1.36f, 0.04f, RLI_GOLD);
	drawFilledEllipse(0.0f, -1.28f, 0.09f, 0.08f, 0.05f, RLI_RUBY, 18);
	drawEllipseOutline(0.0f, -1.28f, 0.09f, 0.08f, 0.055f, 3.0f, RLI_GOLD_DARK, 18);
	{
		float rliSash[] = { 0.05f, -1.36f, 0.08f, -1.55f, 0.04f, -1.78f, 0.07f, -2.00f };
		rliDrawRibbon(rliSash, 4, 0.22f, 0.26f, 0.045f, RLI_DHOTI);
		drawFilledQuad(-0.06f, -1.96f, 0.20f, -1.96f, 0.20f, -2.03f, -0.06f, -2.03f, 0.05f, RLI_RUBY);
	}

	// neck
	drawFilledQuad(-0.17f, 0.42f, 0.17f, 0.42f, 0.24f, -0.05f, -0.24f, -0.05f, 0.01f, RLI_SKIN);
	drawFilledQuad(-0.04f, 0.40f, 0.04f, 0.40f, 0.06f, -0.05f, -0.06f, -0.05f, 0.012f, 0.82f, 0.60f, 0.42f);

	// layered necklaces
	drawArc(0.0f, 0.02f, 0.25f, 0.18f, 0.035f, 200.0f, 340.0f, 6.0f, RLI_GOLD, 24);
	drawArc(0.0f, -0.02f, 0.32f, 0.30f, 0.035f, 205.0f, 335.0f, 5.0f, RLI_GOLD_DARK, 24);
	for (int rliPearl = 0; rliPearl < 15; rliPearl++)
	{
		float rliA = (200.0f + 140.0f * (float)rliPearl / 14.0f) * (float)M_PI / 180.0f;
		drawFilledEllipse(0.38f * cosf(rliA), -0.05f + 0.50f * sinf(rliA), 0.022f, 0.022f, 0.036f, 0.98f, 0.96f, 0.90f, 10);
	}
	drawFilledEllipse(0.0f, -0.33f, 0.06f, 0.08f, 0.04f, RLI_GOLD, 18);
	drawFilledEllipse(0.0f, -0.33f, 0.035f, 0.05f, 0.045f, RLI_RUBY, 14);

	// head
	glPushMatrix();
	glTranslatef(0.0f, 0.60f, 0.0f);
	glRotatef(rliHeadTilt, 0.0f, 0.0f, 1.0f);
	rliDrawKingHead(rliAnimTime);
	glPopMatrix();

	// left arm resting on armrest
	rliDrawSegment(0.55f, -0.08f, 0.90f, -0.58f, 0.30f, 0.22f, 0.20f, RLI_SKIN);
	rliDrawSegment(0.90f, -0.58f, 1.30f, -0.70f, 0.22f, 0.16f, 0.20f, RLI_SKIN);
	rliDrawSegment(0.63f, -0.27f, 0.82f, -0.33f, 0.07f, 0.07f, 0.21f, RLI_GOLD);
	drawFilledEllipse(0.71f, -0.30f, 0.035f, 0.035f, 0.22f, RLI_RUBY, 10);
	rliDrawSegment(1.19f, -0.61f, 1.17f, -0.73f, 0.05f, 0.05f, 0.21f, RLI_GOLD);
	drawFilledEllipse(1.36f, -0.72f, 0.10f, 0.085f, 0.21f, RLI_SKIN, 20);
	for (int rliF = 0; rliF < 4; rliF++)
		drawFilledEllipse(1.42f + 0.02f * (float)rliF, -0.66f - 0.035f * (float)rliF, 0.03f, 0.022f, 0.215f, RLI_SKIN_SHADE, 10);
	drawFilledEllipse(1.40f, -0.70f, 0.018f, 0.018f, 0.22f, RLI_GOLD, 8);

	// right arm gripping talwar
	rliDrawSegment(-0.55f, -0.08f, -0.82f, -0.60f, 0.30f, 0.22f, 0.20f, RLI_SKIN);
	rliDrawSegment(-0.82f, -0.60f, rliHandX, rliHandY, 0.22f, 0.16f, 0.20f, RLI_SKIN);
	rliDrawSegment(-0.54f, -0.30f, -0.73f, -0.26f, 0.07f, 0.07f, 0.21f, RLI_GOLD);
	drawFilledEllipse(-0.635f, -0.30f, 0.035f, 0.035f, 0.22f, RLI_RUBY, 10);
	rliDrawSegment(rliLerp(-0.82f, rliHandX, 0.78f) - 0.07f, rliLerp(-0.60f, rliHandY, 0.78f),
	               rliLerp(-0.82f, rliHandX, 0.78f) + 0.07f, rliLerp(-0.60f, rliHandY, 0.78f) - 0.01f, 0.05f, 0.05f, 0.21f, RLI_GOLD);

	// TALWAR in scabbard
	{
		float rliTipX = rliHandX - 0.45f, rliTipY = RLI_DAIS_TOP_Y + 0.08f + 0.20f * rliAngerBlend;
		float rliScabbard[] = {
			rliHandX - 0.02f, rliHandY - 0.14f,
			rliHandX - 0.12f, rliHandY - 0.60f,
			rliHandX - 0.26f, rliHandY - 1.10f,
			rliHandX - 0.42f, rliHandY - 1.55f,
			rliTipX, rliTipY,
		};
		rliDrawRibbon(rliScabbard, 5, 0.13f, 0.09f, 0.18f, 0.45f, 0.10f, 0.12f);
		drawFilledEllipse(rliTipX, rliTipY, 0.06f, 0.07f, 0.185f, RLI_GOLD, 14);
		for (int rliBand = 1; rliBand <= 3; rliBand++)
		{
			float rliT = (float)rliBand * 0.25f;
			float rliX = rliLerp(rliHandX - 0.02f, rliTipX, rliT) - 0.05f * rliT;
			float rliY = rliLerp(rliHandY - 0.14f, rliTipY, rliT);
			drawFilledEllipse(rliX, rliY, 0.08f, 0.03f, 0.185f, RLI_GOLD, 14);
		}
		drawFilledQuad(rliHandX - 0.14f, rliHandY - 0.08f, rliHandX + 0.12f, rliHandY - 0.08f,
		               rliHandX + 0.12f, rliHandY - 0.14f, rliHandX - 0.14f, rliHandY - 0.14f, 0.19f, RLI_GOLD);
		drawArc(rliHandX + 0.06f, rliHandY + 0.02f, 0.09f, 0.14f, 0.19f, -90.0f, 90.0f, 4.0f, RLI_GOLD, 12);
		rliDrawSegment(rliHandX, rliHandY - 0.08f, rliHandX + 0.02f, rliHandY + 0.14f, 0.06f, 0.06f, 0.19f, RLI_GOLD_DARK);
		drawFilledEllipse(rliHandX + 0.02f, rliHandY + 0.17f, 0.09f, 0.035f, 0.195f, RLI_GOLD, 16);
	}
	drawFilledEllipse(rliHandX, rliHandY, 0.10f, 0.09f, 0.21f, RLI_SKIN, 20);
	for (int rliF = 0; rliF < 4; rliF++)
		drawFilledEllipse(rliHandX + 0.06f, rliHandY + 0.05f - 0.035f * (float)rliF, 0.028f, 0.02f, 0.215f, RLI_SKIN_SHADE, 10);
	drawFilledEllipse(rliHandX + 0.07f, rliHandY - 0.02f, 0.016f, 0.016f, 0.22f, RLI_GOLD, 8);

	glPopMatrix(); // upper body
	glPopMatrix(); // character scale
}

// Scene update function for King Dhana Nanda
static void rliUpdateScene(void)
{
	rliAnimTime += 0.018f;
	rliLaughBlend += ((rliKingMode == 1 ? 1.0f : 0.0f) - rliLaughBlend) * 0.08f;
	rliAngerBlend += ((rliKingMode == 2 ? 1.0f : 0.0f) - rliAngerBlend) * 0.08f;
}

// Unified call for Dhana Nanda and Royal Throne from dahanad.txt
static void drawDhanaNandaAndThrone(float cx, float cy, float cz, float scale)
{
	glPushMatrix();
	glTranslatef(cx, cy, cz);
	glScalef(scale, scale, 1.0f);

	// 1. Royal Throne (Simhasana)
	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0f);
	glScalef(0.82f, 0.82f, 0.82f);
	rliDrawThroneFront();
	glPopMatrix();

	// 2. King Dhana Nanda Character
	rliDrawDhanaNandaCharacter();

	glPopMatrix();
}

// =============================================================================
// STANDING SAGE MODULE (EXTRACTED FROM OGL_backup.c)
// Standing beside King Dhana Nanda on the royal throne stage
// =============================================================================

static void rlCol(int r, int g, int b)
{
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

static void rlRect(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

static void rlQuad(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

static void rlTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

static void rlEllipse(float cx, float cy, float rx, float ry)
{
	const int segments = 32;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (int i = 0; i <= segments; i++)
	{
		float a = 2.0f * (float)M_PI * (float)i / (float)segments;
		glVertex2f(cx + cosf(a) * rx, cy + sinf(a) * ry);
	}
	glEnd();
}

// Extracted character rendering code from OGL_backup.c (originally drawChanakya)
// =============================================================================
// STANDING ROYAL MINISTER / COURTIER MODULE
// Standing beside King Dhana Nanda on the royal throne stage
// Distinct noble courtier: NO tilak, NO shikha, beautifully sculpted hands,
// draped royal saffron silk uttariya with gold/crimson borders, fine pleated dhoti
// =============================================================================

// =============================================================================
// STANDING ROYAL MINISTER MODULE
// Standing beside King Dhana Nanda on the royal throne stage
// Distinct noble royal court official:
//   - NO Tilak on forehead (distinct person from Chanakya)
//   - NO Shikha (clean, smooth bald cranium)
//   - Anatomically sculpted muscular arms and realistic hands (completely stationary)
//   - Elegant, beautifully draped Saffron-Gold Silk Uttariya with gold/crimson borders
//   - Contoured pleated ivory Dhoti with embroidered border hem
//   - Royal Golden Kamarbandh (waist sash) with ruby brooch and hanging patka
//   - Double-strand royal gold & pearl necklace (Kantha) with central emerald
// =============================================================================

static void drawStandingSage(void)
{
	int i;

	// 1. Dhoti with Pleats (matching cartoon style)
	rlCol(235, 225, 200);
	rlQuad(-0.75f, 0.0f, 0.75f, 0.0f, 0.85f, 3.3f, -0.85f, 3.3f);
	rlCol(200, 190, 165);
	for (i = -2; i <= 2; i++)
		rlRect(i * 0.28f - 0.02f, 0.0f, 0.04f, 3.3f);

	// Feet
	rlCol(225, 160, 120);
	rlEllipse(-0.35f, 0.10f, 0.28f, 0.12f);
	rlEllipse(0.35f, 0.10f, 0.28f, 0.12f);

	// Yellow Waist Sash + Knot
	rlCol(225, 175, 50);
	rlRect(-0.9f, 3.0f, 1.8f, 0.6f);
	rlEllipse(0.85f, 3.35f, 0.3f, 0.3f);

	// Bare Torso
	rlCol(225, 160, 120);
	rlRect(-0.8f, 3.6f, 1.6f, 2.0f);
	rlCol(190, 125, 90);
	rlRect(-0.02f, 3.65f, 0.04f, 1.4f); // Centre chest line

	// Right Arm Hanging (Stationary)
	rlCol(225, 160, 120);
	rlQuad(0.8f, 5.5f, 1.1f, 5.4f, 1.15f, 3.7f, 0.85f, 3.7f);
	rlEllipse(1.0f, 3.55f, 0.17f, 0.20f);

	// left arm raised, open hand (speaking gesture)
	rlCol(225, 160, 120);
	rlQuad(-0.8f, 5.45f, -0.8f, 5.05f, -1.55f, 4.2f, -1.75f, 4.55f);
	rlEllipse(-1.7f, 4.4f, 0.2f, 0.2f);

	// Yellow Shawl (Position shifted toward +X onto the shoulder and chest, no overhang in air)
	rlCol(225, 175, 50);
	rlQuad(-0.75f, 5.75f, -0.15f, 5.75f, -0.10f, 2.4f, -0.80f, 2.2f);

	// 1. Neck
	rlCol(225, 160, 120);
	rlRect(-0.17f, 5.55f, 0.34f, 0.30f);
	rlCol(190, 125, 90);
	rlRect(-0.17f, 5.55f, 0.34f, 0.05f);

	// 2. Cranium & Bald Head Contour
	rlCol(225, 160, 120);
	rlEllipse(0.0f, 6.35f, 0.50f, 0.65f); // Upper cranium
	rlCol(215, 150, 110);
	rlEllipse(0.0f, 6.05f, 0.40f, 0.40f); // Jaw taper
	drawArc(0.0f, 5.82f, 0.12f, 0.05f, 0.0f, 200.0f, 340.0f, 2.0f, 0.72f, 0.48f, 0.34f, 15);

	// 3. Smooth Bald Crown (NO Shikha)

	// 4. Ears with Inner Cartilage Folds
	// Left Ear
	rlCol(225, 160, 120);
	rlEllipse(-0.52f, 6.30f, 0.10f, 0.18f);
	rlCol(185, 120, 85);
	rlEllipse(-0.52f, 6.30f, 0.05f, 0.11f);
	drawArc(-0.52f, 6.30f, 0.06f, 0.12f, 0.0f, 40.0f, 320.0f, 1.5f, 0.70f, 0.46f, 0.32f, 15);

	// Right Ear
	rlCol(225, 160, 120);
	rlEllipse(0.52f, 6.30f, 0.10f, 0.18f);
	rlCol(185, 120, 85);
	rlEllipse(0.52f, 6.30f, 0.05f, 0.11f);
	drawArc(0.52f, 6.30f, 0.06f, 0.12f, 0.0f, 220.0f, 140.0f, 1.5f, 0.70f, 0.46f, 0.32f, 15);

	// 5. Forehead Chandan Tilak / Tripundra
	rlCol(245, 245, 235);
	rlQuad(-0.10f, 6.78f, 0.10f, 6.78f, 0.07f, 6.52f, -0.07f, 6.52f);
	rlCol(220, 35, 25);
	rlQuad(-0.038f, 6.75f, 0.038f, 6.75f, 0.024f, 6.53f, -0.024f, 6.53f);
	rlCol(225, 30, 20);
	rlEllipse(0.0f, 6.50f, 0.035f, 0.045f);

	// 6. Arched Resolute Eyebrows (Steady, strong expression)
	glLineWidth(3.2f);
	glColor3f(0.12f, 0.08f, 0.05f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.35f, 6.46f);
	glVertex2f(-0.20f, 6.54f);
	glVertex2f(-0.05f, 6.48f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0.05f, 6.48f);
	glVertex2f(0.20f, 6.54f);
	glVertex2f(0.35f, 6.46f);
	glEnd();
	glLineWidth(1.0f);

	// 7. Refined Eyes (Whites, Iris, Pupils, Catchlights, Eyelids)
	// Left Eye
	rlCol(250, 250, 248);
	rlEllipse(-0.19f, 6.38f, 0.095f, 0.060f);
	rlCol(65, 38, 22);
	rlEllipse(-0.18f, 6.38f, 0.052f, 0.052f);
	rlCol(12, 10, 10);
	rlEllipse(-0.18f, 6.38f, 0.026f, 0.026f);
	rlCol(255, 255, 255);
	rlEllipse(-0.165f, 6.398f, 0.010f, 0.010f);
	drawArc(-0.19f, 6.38f, 0.095f, 0.060f, 0.0f, 10.0f, 170.0f, 2.2f, 0.18f, 0.10f, 0.07f, 16);

	// Right Eye
	rlCol(250, 250, 248);
	rlEllipse(0.19f, 6.38f, 0.095f, 0.060f);
	rlCol(65, 38, 22);
	rlEllipse(0.18f, 6.38f, 0.052f, 0.052f);
	rlCol(12, 10, 10);
	rlEllipse(0.18f, 6.38f, 0.026f, 0.026f);
	rlCol(255, 255, 255);
	rlEllipse(0.195f, 6.398f, 0.010f, 0.010f);
	drawArc(0.19f, 6.38f, 0.095f, 0.060f, 0.0f, 10.0f, 170.0f, 2.2f, 0.18f, 0.10f, 0.07f, 16);

	// 8. Sculpted Nose (Bridge, tip, nostrils)
	rlCol(195, 130, 95);
	rlTri(0.0f, 6.42f, -0.05f, 6.18f, 0.05f, 6.18f);
	rlCol(210, 145, 105);
	rlEllipse(0.0f, 6.18f, 0.065f, 0.040f);
	rlCol(155, 95, 68);
	rlEllipse(-0.045f, 6.16f, 0.020f, 0.018f);
	rlEllipse( 0.045f, 6.16f, 0.020f, 0.018f);

	// 9. Animated Lip-Sync Mouth & Lips (Only mouth moves when speaking)
	if (g_standingSageMouthOpen > 0.02f)
	{
		// Open mouth cavity
		rlCol(50, 16, 16);
		rlEllipse(0.0f, 5.98f - g_standingSageMouthOpen * 0.025f, 0.095f, 0.022f + g_standingSageMouthOpen * 0.045f);

		// Upper teeth
		rlCol(245, 245, 240);
		rlRect(-0.06f, 5.98f, 0.12f, 0.016f * g_standingSageMouthOpen);

		// Upper lip
		rlCol(180, 95, 80);
		rlTri(0.0f, 6.06f, -0.13f, 5.99f, 0.13f, 5.99f);

		// Moving lower lip
		rlCol(195, 110, 95);
		rlEllipse(0.0f, 5.95f - g_standingSageMouthOpen * 0.060f, 0.11f, 0.038f);

		// Lip corner crease lines
		glLineWidth(1.6f);
		glColor3f(0.35f, 0.16f, 0.12f);
		glBegin(GL_LINES);
		glVertex2f(-0.13f, 5.99f);
		glVertex2f(-0.08f, 5.97f - g_standingSageMouthOpen * 0.03f);
		glVertex2f( 0.13f, 5.99f);
		glVertex2f( 0.08f, 5.97f - g_standingSageMouthOpen * 0.03f);
		glEnd();
		glLineWidth(1.0f);
	}
	else
	{
		// Closed dignified mouth
		rlCol(180, 95, 80);
		rlTri(0.0f, 6.06f, -0.13f, 5.99f, 0.13f, 5.99f);
		rlCol(195, 110, 95);
		rlEllipse(0.0f, 5.96f, 0.11f, 0.04f);
		glLineWidth(1.8f);
		glColor3f(0.35f, 0.16f, 0.12f);
		glBegin(GL_LINES);
		glVertex2f(-0.14f, 5.99f);
		glVertex2f( 0.14f, 5.99f);
		glEnd();
		glLineWidth(1.0f);
	}

	// 10. Rudraksha Mala (U shaped chain of beads)
	rlCol(120, 70, 35);
	for (i = 0; i < 15; i++)
	{
		float a = (float)M_PI + (float)M_PI * (float)i / 14.0f;
		rlEllipse(cosf(a) * 0.7f, 5.65f + sinf(a) * 1.0f, 0.10f, 0.10f);
	}
}

static void drawStandingSageByKing(float cx, float cy, float cz, float scale)
{
	glPushMatrix();
	glTranslatef(cx, cy, cz);
	glScalef(scale, scale, 1.0f);

	// Painter's algorithm within 2D planar character
	glDisable(GL_DEPTH_TEST);
	drawStandingSage();
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
}


// =============================================================================
// 3. CHANAKYA BACK VIEW MODULE (DERIVED FROM Character_Chanakya_Front_View)
// Win32 + WGL + OpenGL fixed-function pipeline
// Faithful translation of Chanakya to rear perspective:
// - Completely static, resolute stance (no animation)
// - Grounded: feet rest firmly on the court floor tiles (zero clipping/sinking)
// - Full-length traditional pleated ochre Dhoti extending to the ankles with red border trim
// - Bald cranium with scalp hair tie and iconic 'S'-curved flowing shikha hair lock
// - Muscular bare back with spine groove and anatomical scapulae definition
// - White Janeu (sacred thread) across back with sacred granthi knot
// - Terracotta/saffron Angavastram draped naturally over left shoulder with red border trim
// - Both arms with Rudraksha armlets (Keyura) and wrist bracelets (Kankana)
// - Lower legs, heels, and bare feet planted firmly on the floor
// =============================================================================

#ifndef PI
#define PI 3.14159265358979323846f
#endif

// Rudraksha Mala (Sacred bead strand with golden silk thread & Guru Mani)
static void drawRudrakshaMala(float cx, float cy, float rx, float ry, float zVal, int beadCount)
{
	float rliStartAngle = 200.0f;
	float rliEndAngle = 340.0f;
	float rliStartRad = rliStartAngle * (float)M_PI / 180.0f;
	float rliEndRad = rliEndAngle * (float)M_PI / 180.0f;

	// Golden Silk Thread Line connecting beads
	glLineWidth(2.0f);
	glColor3f(0.85f, 0.65f, 0.15f);
	glBegin(GL_LINE_STRIP);
	for (int rliIndex = 0; rliIndex <= 30; rliIndex++)
	{
		float rliTheta = rliStartRad + (rliEndRad - rliStartRad) * ((float)rliIndex / 30.0f);
		float rliX = cx + rx * cosf(rliTheta);
		float rliY = cy + ry * sinf(rliTheta);
		glVertex3f(rliX, rliY, zVal - 0.002f);
	}
	glEnd();
	glLineWidth(1.0f);

	// Individual Rudraksha Beads along U-arc
	for (int rliIndex = 0; rliIndex < beadCount; rliIndex++)
	{
		float rliT = (float)rliIndex / (float)(beadCount - 1);
		float rliTheta = rliStartRad + (rliEndRad - rliStartRad) * rliT;
		float rliBeadX = cx + rx * cosf(rliTheta);
		float rliBeadY = cy + ry * sinf(rliTheta);

		// Rudraksha main bead (Warm textured brown sphere)
		drawFilledEllipse(rliBeadX, rliBeadY, 0.038f, 0.038f, zVal, 0.48f, 0.18f, 0.08f, 12);
		// Saffron/Gold highlight dot
		drawFilledEllipse(rliBeadX - 0.008f, rliBeadY + 0.008f, 0.012f, 0.012f, zVal + 0.003f, 0.78f, 0.42f, 0.18f, 8);
	}

	// Central Guru Bead (Sumeru Mani) at lowest point
	float rliGuruX = cx;
	float rliGuruY = cy - ry;
	drawFilledEllipse(rliGuruX, rliGuruY, 0.055f, 0.055f, zVal + 0.005f, 0.55f, 0.22f, 0.08f, 16);
	drawFilledEllipse(rliGuruX - 0.01f, rliGuruY + 0.01f, 0.018f, 0.018f, zVal + 0.008f, 0.85f, 0.50f, 0.20f, 10);

	// Red Tassel Threads dangling from Guru Bead
	glLineWidth(2.5f);
	glColor3f(0.88f, 0.12f, 0.05f);
	glBegin(GL_LINES);
	glVertex3f(rliGuruX, rliGuruY - 0.055f, zVal + 0.006f);
	glVertex3f(rliGuruX - 0.02f, rliGuruY - 0.12f, zVal + 0.006f);

	glVertex3f(rliGuruX, rliGuruY - 0.055f, zVal + 0.006f);
	glVertex3f(rliGuruX, rliGuruY - 0.13f, zVal + 0.006f);

	glVertex3f(rliGuruX, rliGuruY - 0.055f, zVal + 0.006f);
	glVertex3f(rliGuruX + 0.02f, rliGuruY - 0.12f, zVal + 0.006f);
	glEnd();
	glLineWidth(1.0f);
}

// 1. Chanakya Back Neck Module
static void drawChanakyaBackNeck(void)
{
	// Muscular Neck Column seen from behind (Jaw base Y=0.42f down to shoulder line Y=-0.05f)
	drawFilledQuad(-0.16f, 0.42f,  0.16f, 0.42f,  0.24f, -0.05f, -0.24f, -0.05f, 0.01f, 0.86f, 0.66f, 0.48f);
	drawQuadOutline(-0.16f, 0.42f,  0.16f, 0.42f,  0.24f, -0.05f, -0.24f, -0.05f, 0.015f, 2.2f, 0.15f, 0.10f, 0.08f);

	// Central cervical furrow shadow
	drawFilledQuad(-0.035f, 0.40f, 0.035f, 0.40f, 0.05f, -0.05f, -0.05f, -0.05f, 0.012f, 0.82f, 0.62f, 0.44f);

	// Trapezius neckline ridges
	glLineWidth(2.2f);
	glColor3f(0.68f, 0.48f, 0.32f);
	glBegin(GL_LINES);
	glVertex3f(-0.14f, 0.38f, 0.015f);
	glVertex3f(-0.22f, -0.05f, 0.015f);

	glVertex3f(0.14f, 0.38f, 0.015f);
	glVertex3f(0.22f, -0.05f, 0.015f);
	glEnd();
	glLineWidth(1.0f);
}

// 2. Chanakya Back Head & Iconic 'S'-Curved Shikha Hair Module (Static)
static void drawChanakyaBackHead(void)
{
	// Smooth shaven cranium viewed from behind
	drawFilledEllipse(0.0f, 0.08f, 0.44f, 0.54f, 0.02f, 0.90f, 0.70f, 0.52f, 60);
	drawEllipseOutline(0.0f, 0.08f, 0.44f, 0.54f, 0.025f, 2.6f, 0.15f, 0.10f, 0.08f, 60);

	// Lower skull / nape junction taper
	drawFilledEllipse(0.0f, -0.16f, 0.35f, 0.30f, 0.02f, 0.86f, 0.66f, 0.48f, 40);

	// Left and Right Ears seen from behind (cartilage rim)
	drawFilledEllipse(-0.46f, 0.06f, 0.09f, 0.16f, 0.01f, 0.84f, 0.63f, 0.45f, 30);
	drawEllipseOutline(-0.46f, 0.06f, 0.09f, 0.16f, 0.015f, 1.8f, 0.15f, 0.10f, 0.08f, 30);
	drawArc(-0.45f, 0.06f, 0.05f, 0.10f, 0.018f, 140.0f, 380.0f, 1.5f, 0.72f, 0.52f, 0.36f, 15);

	drawFilledEllipse(0.46f, 0.06f, 0.09f, 0.16f, 0.01f, 0.84f, 0.63f, 0.45f, 30);
	drawEllipseOutline(0.46f, 0.06f, 0.09f, 0.16f, 0.015f, 1.8f, 0.15f, 0.10f, 0.08f, 30);
	drawArc(0.45f, 0.06f, 0.05f, 0.10f, 0.018f, -20.0f, 220.0f, 1.5f, 0.72f, 0.52f, 0.36f, 15);

	// Scalp Hair Knot (Shikha) at the crown
	// Red / Saffron Hair Tie Ring at Base of Shikha
	drawFilledEllipse(0.0f, 0.46f, 0.07f, 0.06f, 0.045f, 0.85f, 0.15f, 0.08f, 18);
	drawEllipseOutline(0.0f, 0.46f, 0.07f, 0.06f, 0.048f, 1.8f, 0.15f, 0.10f, 0.08f, 18);

	// Shikha Knot Bun atop the crown
	drawFilledEllipse(0.0f, 0.52f, 0.12f, 0.10f, 0.04f, 0.15f, 0.08f, 0.05f, 25);
	drawEllipseOutline(0.0f, 0.52f, 0.12f, 0.10f, 0.042f, 1.8f, 0.08f, 0.05f, 0.03f, 25);
	drawFilledEllipse(-0.03f, 0.55f, 0.06f, 0.05f, 0.044f, 0.24f, 0.14f, 0.09f, 15);

	// Iconic Curved 'S'-Lock Shikha flowing down the back to mid-back
	float pts[9][2] = {
		{  0.00f,  0.46f },
		{ -0.08f,  0.25f },
		{ -0.16f,  0.05f },
		{ -0.20f, -0.18f },
		{ -0.16f, -0.42f },
		{ -0.06f, -0.65f },
		{  0.02f, -0.85f },
		{  0.00f, -1.02f },
		{ -0.06f, -1.18f }
	};
	float halfW[9] = {
		0.12f, 0.11f, 0.10f, 0.09f, 0.075f, 0.06f, 0.045f, 0.028f, 0.008f
	};

	// Filled hair lock strip
	glColor3f(0.12f, 0.08f, 0.05f);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 9; i++)
	{
		float dx = (i < 8) ? (pts[i + 1][0] - pts[i][0]) : (pts[i][0] - pts[i - 1][0]);
		float dy = (i < 8) ? (pts[i + 1][1] - pts[i][1]) : (pts[i][1] - pts[i - 1][1]);
		float len = sqrtf(dx * dx + dy * dy);
		if (len < 0.0001f) len = 1.0f;
		float nx = -dy / len;
		float ny =  dx / len;

		glVertex3f(pts[i][0] - nx * halfW[i], pts[i][1] - ny * halfW[i], 0.05f);
		glVertex3f(pts[i][0] + nx * halfW[i], pts[i][1] + ny * halfW[i], 0.05f);
	}
	glEnd();

	// Dark cel-shaded outlines for the flowing hair
	glLineWidth(2.2f);
	glColor3f(0.08f, 0.05f, 0.03f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 9; i++)
	{
		float dx = (i < 8) ? (pts[i + 1][0] - pts[i][0]) : (pts[i][0] - pts[i - 1][0]);
		float dy = (i < 8) ? (pts[i + 1][1] - pts[i][1]) : (pts[i][1] - pts[i - 1][1]);
		float len = sqrtf(dx * dx + dy * dy);
		if (len < 0.0001f) len = 1.0f;
		float nx = -dy / len;
		float ny =  dx / len;
		glVertex3f(pts[i][0] - nx * halfW[i], pts[i][1] - ny * halfW[i], 0.055f);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 9; i++)
	{
		float dx = (i < 8) ? (pts[i + 1][0] - pts[i][0]) : (pts[i][0] - pts[i - 1][0]);
		float dy = (i < 8) ? (pts[i + 1][1] - pts[i][1]) : (pts[i][1] - pts[i - 1][1]);
		float len = sqrtf(dx * dx + dy * dy);
		if (len < 0.0001f) len = 1.0f;
		float nx = -dy / len;
		float ny =  dx / len;
		glVertex3f(pts[i][0] + nx * halfW[i], pts[i][1] + ny * halfW[i], 0.055f);
	}
	glEnd();
	glLineWidth(1.0f);
}

// 3. Chanakya Back Torso & Muscular Back Module
static void drawChanakyaBackTorso(void)
{
	// Muscular Back Contour (Broad heroic shoulders tapering down to waist)
	drawFilledQuad(-0.58f, 0.02f,  0.58f, 0.02f,  0.44f, -1.35f, -0.44f, -1.35f, 0.0f, 0.86f, 0.66f, 0.48f);
	drawQuadOutline(-0.58f, 0.02f, 0.58f, 0.02f, 0.44f, -1.35f, -0.44f, -1.35f, 0.005f, 2.6f, 0.15f, 0.10f, 0.08f);

	// Shoulder Deltoid Caps (viewed from back)
	drawFilledEllipse(-0.56f, -0.06f, 0.16f, 0.20f, 0.005f, 0.84f, 0.64f, 0.46f, 25);
	drawEllipseOutline(-0.56f, -0.06f, 0.16f, 0.20f, 0.008f, 2.2f, 0.15f, 0.10f, 0.08f, 25);
	drawFilledEllipse( 0.56f, -0.06f, 0.16f, 0.20f, 0.005f, 0.84f, 0.64f, 0.46f, 25);
	drawEllipseOutline( 0.56f, -0.06f, 0.16f, 0.20f, 0.008f, 2.2f, 0.15f, 0.10f, 0.08f, 25);

	// Spine Line (Vertebral groove down the back)
	drawLine(0.0f, -0.05f, 0.0f, -1.25f, 0.015f, 2.4f, 0.68f, 0.48f, 0.32f);

	// Scapulae (Shoulder Blade ridges & muscle plane shading)
	// Left Scapula
	drawLine(-0.46f, -0.16f, -0.16f, -0.24f, 0.015f, 2.2f, 0.68f, 0.48f, 0.32f);
	drawLine(-0.16f, -0.24f, -0.18f, -0.65f, 0.015f, 2.2f, 0.68f, 0.48f, 0.32f);
	drawArc(-0.25f, -0.42f, 0.18f, 0.20f, 0.012f, 200.0f, 330.0f, 2.0f, 0.68f, 0.48f, 0.32f, 15);

	// Right Scapula
	drawLine(0.46f, -0.16f, 0.16f, -0.24f, 0.015f, 2.2f, 0.68f, 0.48f, 0.32f);
	drawLine(0.16f, -0.24f, 0.18f, -0.65f, 0.015f, 2.2f, 0.68f, 0.48f, 0.32f);
	drawArc(0.25f, -0.42f, 0.18f, 0.20f, 0.012f, 210.0f, 340.0f, 2.0f, 0.68f, 0.48f, 0.32f, 15);

	// Latissimus dorsi side contours
	drawLine(-0.48f, -0.70f, -0.40f, -1.25f, 0.015f, 2.0f, 0.68f, 0.48f, 0.32f);
	drawLine( 0.48f, -0.70f,  0.40f, -1.25f, 0.015f, 2.0f, 0.68f, 0.48f, 0.32f);

	// White Janeu Sacred Thread with Knot (Across back from left shoulder to right hip)
	glLineWidth(2.8f);
	glColor3f(0.96f, 0.96f, 0.92f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.30f, 0.02f, 0.04f);
	glVertex3f(0.01f, -0.65f, 0.04f);
	glVertex3f(0.34f, -1.30f, 0.04f);
	glEnd();

	glLineWidth(1.6f);
	glColor3f(0.74f, 0.54f, 0.36f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.29f, 0.0f, 0.038f);
	glVertex3f(0.02f, -0.67f, 0.038f);
	glVertex3f(0.35f, -1.32f, 0.038f);
	glEnd();
	glLineWidth(1.0f);

	drawFilledEllipse(0.01f, -0.65f, 0.025f, 0.025f, 0.045f, 1.0f, 1.0f, 0.95f, 12); // Janeu Knot

	// Dhoti Waistband Sash (Kamarbandh) matching Front View
	drawFilledQuad(-0.48f, -1.25f,  0.48f, -1.25f,  0.46f, -1.35f, -0.46f, -1.35f, 0.03f, 0.88f, 0.12f, 0.05f);
	drawQuadOutline(-0.48f, -1.25f,  0.48f, -1.25f,  0.46f, -1.35f, -0.46f, -1.35f, 0.035f, 2.0f, 0.15f, 0.10f, 0.08f);
}

// 4. Chanakya Back Angavastram Module (Natural Shoulder Wrap - Static)
static void drawChanakyaBackAngavastram(float r, float g, float b)
{
	float shadeR = r * 0.86f;
	float shadeG = g * 0.86f;
	float shadeB = b * 0.86f;

	// Draped Shawl wrapping naturally over left shoulder and down the back
	drawFilledQuad(-0.58f, 0.06f, -0.20f, 0.10f, -0.16f, -1.35f, -0.52f, -1.35f, 0.05f, r, g, b);
	drawQuadOutline(-0.58f, 0.06f, -0.20f, 0.10f, -0.16f, -1.35f, -0.52f, -1.35f, 0.055f, 2.2f, 0.15f, 0.10f, 0.08f);

	// Fabric fold shading
	drawFilledQuad(-0.42f, 0.07f, -0.28f, 0.09f, -0.24f, -1.35f, -0.36f, -1.35f, 0.052f, shadeR, shadeG, shadeB);

	// Red Accent Border Trim along the drape edges
	glLineWidth(2.8f);
	glColor3f(0.85f, 0.10f, 0.08f);
	glBegin(GL_LINES);
	glVertex3f(-0.20f, 0.10f, 0.06f);
	glVertex3f(-0.16f, -1.35f, 0.06f);

	glVertex3f(-0.58f, 0.06f, 0.06f);
	glVertex3f(-0.52f, -1.35f, 0.06f);
	glEnd();
	glLineWidth(1.0f);
}

// 5. Chanakya Back Arms Module (with Rudraksha Armlets & Wristlets)
static void drawChanakyaBackLeftArm(void)
{
	glPushMatrix();
		glTranslatef(-0.54f, -0.05f, 0.0f);

		// Upper Arm
		drawFilledQuad(-0.10f, 0.05f,  0.10f, 0.05f,  0.08f, -0.55f, -0.08f, -0.55f, 0.01f, 0.84f, 0.64f, 0.46f);
		drawQuadOutline(-0.10f, 0.05f,  0.10f, 0.05f,  0.08f, -0.55f, -0.08f, -0.55f, 0.015f, 2.2f, 0.15f, 0.10f, 0.08f);
		drawRudrakshaMala(0.0f, -0.30f, 0.09f, 0.04f, 0.03f, 6);

		// Forearm
		glPushMatrix();
			glTranslatef(0.0f, -0.55f, 0.0f);
			
			drawFilledQuad(-0.085f, 0.0f,  0.085f, 0.0f,  0.075f, -0.50f, -0.075f, -0.50f, 0.01f, 0.84f, 0.64f, 0.46f);
			drawQuadOutline(-0.085f, 0.0f,  0.085f, 0.0f,  0.075f, -0.50f, -0.075f, -0.50f, 0.015f, 2.2f, 0.15f, 0.10f, 0.08f);
			
			// Wrist Rudraksha Bracelet
			drawRudrakshaMala(0.0f, -0.48f, 0.08f, 0.035f, 0.03f, 6);

			// Left Hand (clenched fist / resolve seen from back)
			drawFilledEllipse(0.0f, -0.56f, 0.085f, 0.075f, 0.02f, 0.82f, 0.60f, 0.42f, 20);
			drawEllipseOutline(0.0f, -0.56f, 0.085f, 0.075f, 0.025f, 1.8f, 0.15f, 0.10f, 0.08f, 20);
			drawArc(0.0f, -0.58f, 0.05f, 0.03f, 0.026f, 180.0f, 360.0f, 1.6f, 0.74f, 0.54f, 0.36f, 10);
		glPopMatrix();
	glPopMatrix();
}

static void drawChanakyaBackRightArm(void)
{
	glPushMatrix();
		glTranslatef(0.54f, -0.05f, 0.0f);

		// Upper Arm
		drawFilledQuad(-0.10f, 0.05f,  0.10f, 0.05f,  0.08f, -0.55f, -0.08f, -0.55f, 0.01f, 0.86f, 0.66f, 0.48f);
		drawQuadOutline(-0.10f, 0.05f,  0.10f, 0.05f,  0.08f, -0.55f, -0.08f, -0.55f, 0.015f, 2.2f, 0.15f, 0.10f, 0.08f);
		drawRudrakshaMala(0.0f, -0.30f, 0.09f, 0.04f, 0.03f, 6);

		// Forearm (angled slightly inward towards the royal throne in confrontation)
		glPushMatrix();
			glTranslatef(0.0f, -0.55f, 0.0f);
			glRotatef(8.0f, 0.0f, 0.0f, 1.0f);
			
			drawFilledQuad(-0.085f, 0.0f,  0.085f, 0.0f,  0.075f, -0.50f, -0.075f, -0.50f, 0.01f, 0.86f, 0.66f, 0.48f);
			drawQuadOutline(-0.085f, 0.0f,  0.085f, 0.0f,  0.075f, -0.50f, -0.075f, -0.50f, 0.015f, 2.2f, 0.15f, 0.10f, 0.08f);
			
			// Wrist Rudraksha Bracelet
			drawRudrakshaMala(0.0f, -0.48f, 0.08f, 0.035f, 0.03f, 6);

			// Right Hand (resolute posture)
			drawFilledEllipse(0.0f, -0.56f, 0.085f, 0.075f, 0.02f, 0.84f, 0.63f, 0.45f, 20);
			drawEllipseOutline(0.0f, -0.56f, 0.085f, 0.075f, 0.025f, 1.8f, 0.15f, 0.10f, 0.08f, 20);
		glPopMatrix();
	glPopMatrix();
}

// 6. Chanakya Back Dhoti & Legs Module (Full Length to Ankles)
static void drawChanakyaBackDhotiAndLegs(float r, float g, float b)
{
	float shadeR = r * 0.85f;
	float shadeG = g * 0.85f;
	float shadeB = b * 0.85f;

	float pleatR = r * 0.75f;
	float pleatG = g * 0.75f;
	float pleatB = b * 0.75f;

	// Full-length Tapered Dhoti draping down to the ankles
	drawFilledQuad(-0.50f, -1.30f,  0.50f, -1.30f,  0.44f, -3.15f, -0.44f, -3.15f, 0.02f, r, g, b);
	drawQuadOutline(-0.50f, -1.30f,  0.50f, -1.30f,  0.44f, -3.15f, -0.44f, -3.15f, 0.025f, 2.4f, 0.15f, 0.10f, 0.08f);

	// Center Drapery Pleat Fold Shading
	drawFilledQuad(-0.12f, -1.30f,  0.12f, -1.30f,  0.08f, -3.15f, -0.08f, -3.15f, 0.03f, shadeR, shadeG, shadeB);

	// Dhoti Pleat Fold Curves across the length
	drawArc(-0.20f, -1.85f, 0.24f, 0.40f, 0.035f, 280.0f, 350.0f, 2.0f, pleatR, pleatG, pleatB, 15);
	drawArc( 0.20f, -1.85f, 0.24f, 0.40f, 0.035f, 190.0f, 260.0f, 2.0f, pleatR, pleatG, pleatB, 15);

	drawArc(-0.18f, -2.50f, 0.22f, 0.35f, 0.035f, 280.0f, 350.0f, 1.8f, pleatR, pleatG, pleatB, 15);
	drawArc( 0.18f, -2.50f, 0.22f, 0.35f, 0.035f, 190.0f, 260.0f, 1.8f, pleatR, pleatG, pleatB, 15);

	// Vertical fabric pleat lines
	glLineWidth(2.0f);
	glColor3f(pleatR, pleatG, pleatB);
	glBegin(GL_LINES);
	glVertex3f(-0.28f, -1.35f, 0.032f);
	glVertex3f(-0.24f, -3.10f, 0.032f);

	glVertex3f(0.28f, -1.35f, 0.032f);
	glVertex3f(0.24f, -3.10f, 0.032f);

	glVertex3f(0.0f, -1.35f, 0.035f);
	glVertex3f(0.0f, -3.12f, 0.035f);
	glEnd();
	glLineWidth(1.0f);

	// Bottom Dhoti Red Border Trim
	drawFilledQuad(-0.44f, -3.15f,  0.44f, -3.15f,  0.43f, -3.26f, -0.43f, -3.26f, 0.04f, 0.85f, 0.10f, 0.08f);
	drawQuadOutline(-0.44f, -3.15f,  0.44f, -3.15f,  0.43f, -3.26f, -0.43f, -3.26f, 0.045f, 2.2f, 0.15f, 0.10f, 0.08f);

	// Left Bare Heel & Ankle emerging beneath dhoti hem
	glPushMatrix();
		glTranslatef(-0.18f, -3.24f, 0.0f);
		drawFilledQuad(-0.075f, 0.0f,  0.075f, 0.0f,  0.06f, -0.12f, -0.06f, -0.12f, 0.01f, 0.86f, 0.66f, 0.48f);
		drawQuadOutline(-0.075f, 0.0f,  0.075f, 0.0f,  0.06f, -0.12f, -0.06f, -0.12f, 0.015f, 1.8f, 0.15f, 0.10f, 0.08f);
		
		// Bare Heel & Achilles tendon line
		drawLine(0.0f, 0.0f, 0.0f, -0.12f, 0.018f, 1.8f, 0.74f, 0.54f, 0.36f);
		drawFilledEllipse(0.0f, -0.14f, 0.075f, 0.05f, 0.02f, 0.84f, 0.63f, 0.45f, 16);
		drawEllipseOutline(0.0f, -0.14f, 0.075f, 0.05f, 0.025f, 1.8f, 0.15f, 0.10f, 0.08f, 16);
	glPopMatrix();

	// Right Bare Heel & Ankle emerging beneath dhoti hem
	glPushMatrix();
		glTranslatef(0.18f, -3.24f, 0.0f);
		drawFilledQuad(-0.075f, 0.0f,  0.075f, 0.0f,  0.06f, -0.12f, -0.06f, -0.12f, 0.01f, 0.86f, 0.66f, 0.48f);
		drawQuadOutline(-0.075f, 0.0f,  0.075f, 0.0f,  0.06f, -0.12f, -0.06f, -0.12f, 0.015f, 1.8f, 0.15f, 0.10f, 0.08f);
		
		// Bare Heel & Achilles tendon line
		drawLine(0.0f, 0.0f, 0.0f, -0.12f, 0.018f, 1.8f, 0.74f, 0.54f, 0.36f);
		drawFilledEllipse(0.0f, -0.14f, 0.075f, 0.05f, 0.02f, 0.84f, 0.63f, 0.45f, 16);
		drawEllipseOutline(0.0f, -0.14f, 0.075f, 0.05f, 0.025f, 1.8f, 0.15f, 0.10f, 0.08f, 16);
	glPopMatrix();
}

// 7. Back View Sage / Chanakya / Student Character Pipeline
// Accepts position, scale, and custom cloth colors:
//   cx, cy, cz          : World coordinates (cy = -3.00f touches court floor)
//   scale               : Uniform size factor (e.g. 1.15f for Master Chanakya, 1.05f for Student)
//   dhotiR, dhotiG, dhotiB : RGB color of lower dhoti garment
//   angaR, angaG, angaB    : RGB color of upper shoulder shawl (Angavastram / Uttariya)
static void drawChanakyaBackView(float cx, float cy, float cz, float scale,
                          float dhotiR, float dhotiG, float dhotiB,
                          float angaR, float angaG, float angaB)
{
	glPushMatrix();
		glTranslatef(cx, cy, cz);
		glScalef(scale, scale, 1.0f);

		// Ground offset: exactly offsets character so feet soles rest at Y=0
		glTranslatef(0.0f, 2.37f, 0.0f);

		// Proportional character hierarchy matching Front View
		glPushMatrix();
			glTranslatef(0.0f, 0.45f, 0.0f);
			glScalef(0.82f, 0.82f, 0.82f);

			drawChanakyaBackTorso();
			drawChanakyaBackNeck();
			drawChanakyaBackDhotiAndLegs(dhotiR, dhotiG, dhotiB);
			drawChanakyaBackRightArm();
			drawChanakyaBackLeftArm();

			glPushMatrix();
				glTranslatef(0.0f, 0.60f, 0.0f);
				drawChanakyaBackHead(); // Static pose: no animation
			glPopMatrix();

			drawChanakyaBackAngavastram(angaR, angaG, angaB); // Static drape: no animation

		glPopMatrix();

	glPopMatrix();
}


// =============================================================================
// SCREENSHOT UTILITY
// =============================================================================

static void saveScreenshot(const char *filename, int width, int height)
{
	BYTE *pixels = (BYTE *)malloc(width * height * 3);
	if (!pixels) return;

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&bih, 0, sizeof(BITMAPINFOHEADER));

	bfh.bfType = 0x4D42;
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width * height * 3;
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;

	FILE *fp = fopen(filename, "wb");
	if (fp)
	{
		fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fp);
		fwrite(pixels, width * height * 3, 1, fp);
		fclose(fp);
	}
	free(pixels);
}

static int g_frameCount = 0;

static void drawFilledCourtAudience(void)
{
	// =========================================================================
	// RIGHT SIDE GALLERY (Courtiers & Guards filling the right court hall)
	// =========================================================================
	// Row 1 - Near foreground (Z ~ -12.0f to -13.5f)
	rlDrawSoliderEx(2.30f, -3.00f, -12.0f, 1.38f, 1.38f, 1.38f, 185.0f, 0);
	rlDreawDarbariEx(4.30f, -3.00f, -12.8f, 1.38f, 1.38f, 1.38f, 192.0f, DARBARI_COLOR_SAFFRON_GOLD);
	rlDreawDarbariEx(6.30f, -3.00f, -13.5f, 1.38f, 1.38f, 1.38f, 196.0f, DARBARI_COLOR_ROYAL_NAVY);

	// Row 2 - Midground (Z ~ -16.5f to -17.5f)
	rlDrawSoliderEx(2.60f, -3.00f, -16.8f, 1.38f, 1.38f, 1.38f, 186.0f, 0);
	rlDreawDarbariEx(4.60f, -3.00f, -16.5f, 1.38f, 1.38f, 1.38f, 190.0f, DARBARI_COLOR_EMERALD_GREEN);
	rlDreawDarbariEx(6.60f, -3.00f, -17.2f, 1.38f, 1.38f, 1.38f, 194.0f, DARBARI_COLOR_PEARL_WHITE);

	// Row 3 - Near stairs (Z ~ -21.0f to -22.0f)
	rlDrawSoliderEx(2.50f, -3.00f, -21.5f, 1.38f, 1.38f, 1.38f, 185.0f, 0);
	rlDreawDarbariEx(4.40f, -3.00f, -21.0f, 1.38f, 1.38f, 1.38f, 188.0f, DARBARI_COLOR_CRIMSON_RED);
	rlDreawDarbariEx(6.30f, -3.00f, -21.8f, 1.38f, 1.38f, 1.38f, 192.0f, DARBARI_COLOR_VIOLET_PURPLE);

	// =========================================================================
	// LEFT SIDE GALLERY (Courtiers & Guards filling the left court hall)
	// =========================================================================
	// Row 1 - Flanking left of Chanakya & Student
	rlDreawDarbariEx(-4.80f, -3.00f, -12.8f, 1.38f, 1.38f, 1.38f, 172.0f, DARBARI_COLOR_SKY_BLUE);
	rlDreawDarbariEx(-6.80f, -3.00f, -13.5f, 1.38f, 1.38f, 1.38f, 168.0f, DARBARI_COLOR_PEARL_WHITE);

	// Row 2 - Left midground (Z ~ -16.5f to -17.5f)
	rlDrawSoliderEx(-2.60f, -3.00f, -16.8f, 1.38f, 1.38f, 1.38f, 176.0f, 1);
	rlDreawDarbariEx(-4.60f, -3.00f, -16.5f, 1.38f, 1.38f, 1.38f, 171.0f, DARBARI_COLOR_VIOLET_PURPLE);
	rlDreawDarbariEx(-6.60f, -3.00f, -17.2f, 1.38f, 1.38f, 1.38f, 166.0f, DARBARI_COLOR_SAFFRON_GOLD);

	// Row 3 - Left near stairs (Z ~ -21.0f to -22.0f)
	rlDrawSoliderEx(-2.50f, -3.00f, -21.5f, 1.38f, 1.38f, 1.38f, 175.0f, 1);
	rlDreawDarbariEx(-4.40f, -3.00f, -21.0f, 1.38f, 1.38f, 1.38f, 172.0f, DARBARI_COLOR_EMERALD_GREEN);
	rlDreawDarbariEx(-6.30f, -3.00f, -21.8f, 1.38f, 1.38f, 1.38f, 168.0f, DARBARI_COLOR_CRIMSON_RED);

	// =========================================================================
	// STAGE ROYAL GUARDS (Elevated on the stage floor Y = -0.50f flanking throne)
	// =========================================================================
	//rlDrawSoliderEx(-4.20f, -0.50f, -28.0f, 1.38f, 1.38f, 1.38f, 160.0f, 1);
	//rlDrawSoliderEx( 4.20f, -0.50f, -28.0f, 1.38f, 1.38f, 1.38f, 200.0f, 0);
}

// =============================================================================
// RENDER FUNCTION (INITIAL LOGIC + CHARACTERS & THRONE)
// =============================================================================

// =============================================================================
// CENTRAL DARBAR SCENE DRAWING FUNCTION
// Draws room, stage, pillars, curtains, throne, King, Standing Sage, Chanakya, Disciple, Audience
// =============================================================================
static void drawDarbarScene(void)
{
	// 1. Initial Darbar Room (Teal floor, grid lines, ceiling, back wall & trims, golden arch)
	drawThroneRoom();

	// 2. Initial Darbar Stage (Raised cuboid stage, yellow/red carpet, 5 stairs climbing up)
	drawThroneStage();

	// 3. Initial Left Pillars and Curtains
	glPushMatrix();
	glTranslatef(-9.5f, 5.0f, -32.0f);
	glScalef(4.2f, 4.2f, 4.2f);
	drawPillarAndCurtain();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-21.0f, 5.0f, -31.5f);
	glScalef(4.2f, 4.2f, 4.2f);
	drawPillarAndCurtain();
	glPopMatrix();

	// 4. Initial Right Pillars and Curtains
	glPushMatrix();
	glTranslatef(9.5f, 5.0f, -32.0f);
	glScalef(4.2f, 4.2f, 4.2f);
	drawPillarAndCurtain();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(21.0f, 5.0f, -31.5f);
	glScalef(4.2f, 4.2f, 4.2f);
	drawPillarAndCurtain();
	glPopMatrix();

	// 5. King Dhana Nanda & Royal Throne at the center of the stage (from dahanad.txt)
	drawDhanaNandaAndThrone(0.0f, 2.90f, -28.5f, 1.30f);

	// 6. Standing Sage from OGL_backup.c standing beside King Dhana Nanda on the stage
	drawStandingSageByKing(-2.70f, -0.50f, -28.0f, 0.82f);

	// 7. Master Chanakya (confronting King Dhana Nanda) - Golden Yellow Dhoti & Saffron Angavastram
	drawChanakyaBackView(4.20f, -3.00f, -12.0f, 1.15f,
	                     0.92f, 0.72f, 0.15f,   // Dhoti: Golden Ochre / Yellow
	                     0.65f, 0.42f, 0.18f);  // Angavastram: Terracotta Saffron

	// 8. Chanakya's Disciple / Student - Pure White / Cream Cotton Attire (slightly smaller scale)
	drawChanakyaBackView(-0.00f, -3.00f, -13.0f, 1.02f,
	                     0.94f, 0.94f, 0.90f,   // Dhoti: Pure Cotton White
	                     0.86f, 0.84f, 0.78f);  // Angavastram: Off-white / Cream

	// 9. Multiple Side Characters filling the Darbar hall with back side facing camera
	drawFilledCourtAudience();
}

// =============================================================================
// DEDICATED SHOT RENDERING FUNCTIONS
// Each function sets its camera position, character emotions, and renders the scene
// =============================================================================

// 1. Wide Darbar Shot
static void renderWideShot(void)
{
	shotWide();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_camEyeX, g_camEyeY, g_camEyeZ,
	          g_camTargetX, g_camTargetY, g_camTargetZ,
	          0.0f, 1.0f, 0.0f);

	drawDarbarScene();
}

// 2. Standing Person Questioning / Speaking Close-Up Shot
static void renderStandingSageQuestionShot(void)
{
	shotStandingSage(TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_camEyeX, g_camEyeY, g_camEyeZ,
	          g_camTargetX, g_camTargetY, g_camTargetZ,
	          0.0f, 1.0f, 0.0f);

	drawDarbarScene();
}

// 3. Chanakya & Disciple Over-The-Shoulder Response Shot
static void renderChanakyaResponseShot(void)
{
	shotChanakya(TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_camEyeX, g_camEyeY, g_camEyeZ,
	          g_camTargetX, g_camTargetY, g_camTargetZ,
	          0.0f, 1.0f, 0.0f);

	drawDarbarScene();
}

// 4. King Dhana Nanda Laughing Shot
static void renderKingLaughShot(void)
{
	shotKing(1); // 1 = Laughing mode

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_camEyeX, g_camEyeY, g_camEyeZ,
	          g_camTargetX, g_camTargetY, g_camTargetZ,
	          0.0f, 1.0f, 0.0f);

	drawDarbarScene();
}

// 5. King Dhana Nanda Normal Speaking Shot
static void renderKingNormalShot(void)
{
	shotKing(0); // 0 = Normal speaking mode

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_camEyeX, g_camEyeY, g_camEyeZ,
	          g_camTargetX, g_camTargetY, g_camTargetZ,
	          0.0f, 1.0f, 0.0f);

	drawDarbarScene();
}

// 6. King Dhana Nanda Royal Rage / Climax Shot
static void renderKingAngryShot(void)
{
	shotKing(2); // 2 = Anger mode (gripping sword)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_camEyeX, g_camEyeY, g_camEyeZ,
	          g_camTargetX, g_camTargetY, g_camTargetZ,
	          0.0f, 1.0f, 0.0f);

	drawDarbarScene();
}

// =============================================================================
// MAIN RENDER FUNCTION (CALLED EVERY FRAME)
// Dispatches to the specific shot rendering function based on elapsed audio time
// (Structured exactly like showSirsBirthdayGift in the reference demo)
// =============================================================================


// =============================================================================
// SCENE UPDATE FUNCTION
// Called every frame by main update() loop during Darbar timeline window
// =============================================================================
void updateScene3(void)
{
	rliAnimTime += 0.016f;

	// Update King emotion blend weights
	float targetLaugh = (rliKingMode == 1) ? 1.0f : 0.0f;
	float targetAnger = (rliKingMode == 2) ? 1.0f : 0.0f;
	rliLaughBlend += (targetLaugh - rliLaughBlend) * 0.1f;
	rliAngerBlend += (targetAnger - rliAngerBlend) * 0.1f;

	// Update Standing Person mouth animation if speaking
	float targetSageMouth = 0.0f;
	if (g_bStandingSageSpeaking)
	{
		float speechWave = (0.5f + 0.5f * sinf(rliAnimTime * 2.8f)) *
		                   (0.6f + 0.4f * sinf(rliAnimTime * 1.2f));
		targetSageMouth = speechWave;
	}
	g_standingSageMouthOpen += (targetSageMouth - g_standingSageMouthOpen) * 0.05f;

	// Update King mouth animation if speaking (like renderStandingSageQuestionShot)
	float targetKingMouth = 0.0f;
	if (g_bKingSpeaking)
	{
		float speechWave = (0.5f + 0.5f * sinf(rliAnimTime * 2.8f)) *
		                   (0.6f + 0.4f * sinf(rliAnimTime * 1.2f));
		targetKingMouth = speechWave;
	}
	g_kingMouthOpen += (targetKingMouth - g_kingMouthOpen) * 0.08f;

	// Camera Positioning: Instant Hard Cut (Movie / TV Serial) vs Smooth Steadicam
	if (g_bInstantCameraCut)
	{
		g_camEyeX = g_targetEyeX;
		g_camEyeY = g_targetEyeY;
		g_camEyeZ = g_targetEyeZ;

		g_camTargetX = g_targetTargetX;
		g_camTargetY = g_targetTargetY;
		g_camTargetZ = g_targetTargetZ;
	}
	else
	{
		float camSpeed = 0.06f;
		g_camEyeX += (g_targetEyeX - g_camEyeX) * camSpeed;
		g_camEyeY += (g_targetEyeY - g_camEyeY) * camSpeed;
		g_camEyeZ += (g_targetEyeZ - g_camEyeZ) * camSpeed;

		g_camTargetX += (g_targetTargetX - g_camTargetX) * camSpeed;
		g_camTargetY += (g_targetTargetY - g_camTargetY) * camSpeed;
		g_camTargetZ += (g_targetTargetZ - g_camTargetZ) * camSpeed;
	}
}

// =============================================================================
// SCENE INITIALIZATION
// =============================================================================
void initScene3(void)
{
	g_bScene3AudioStarted = FALSE;
	g_darbarAudioStartTick = 0;
	rliAnimTime = 0.0f;
	rliKingMode = 0;
	g_bKingSpeaking = FALSE;
	g_kingMouthOpen = 0.0f;
	g_currentShot = SHOT_WIDE;
	shotWide();
}

// =============================================================================
// MAIN DARBAR RENDER FUNCTION
// Called by showSirsBirthdayGift() when timeline reaches Darbar Scene
// =============================================================================
void renderScene3(void)
{
	// 1. Auto-start audio on first entry
	if (!g_bScene3AudioStarted)
	{
		startScene3Audio();
	}

	DWORD currentTick = timeGetTime();
	float elapsedTime = (float)(currentTick - g_darbarAudioStartTick) / 1000.0f;

	// 2. Timeline Dispatcher (Calls dedicated shot rendering functions)
	if (elapsedTime < 4.0f)
	{
		// 0.0s to 4.0s: Grand Master Establishing Shot of the entire Darbar
		renderWideShot();
	}
	else if (elapsedTime < 5.5f)
	{
		// 4.0s to 5.0s (on 0.4): Standing Sage first question
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 6.5f)
	{
		// 5.0s to 6.0s (on 0.5): Shishya answers the question
		renderWideShot();
	}
	else if (elapsedTime < 7.5f)
	{
		// 6.0s to 7.0s (0.6 - 0.7): Standing Sage second question
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 8.7f)
	{
		// 7.0s to 8.7s (0.7 - 0.8): Shishya answers the question
		renderWideShot();
	}
	else if (elapsedTime < 11.0f)
	{
		// 8.7s to 11.0s (0.9 - 10.0): Standing Sage question
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 14.0f)
	{
		// 11.0s to 14.0s: Grand Court Wide View
		renderWideShot();
	}
	else if (elapsedTime < 21.0f)
	{
		// 14.0s to 21.0s: Chanakya response shot
		renderChanakyaResponseShot();
	}
	else if (elapsedTime < 22.5f)
	{
		// 0:21 - 0:22 (21.0s to 22.0s): Standing Sage question
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 24.5f)
	{
		// 22 - 23 (22.0s to 24.0s): Shishya answer (Wide Shot)
		renderWideShot();
	}
	else if (elapsedTime < 25.5f)
	{
		// 24 - 25 (24.0s to 25.0s): Standing Sage question
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 27.0f)
	{
		// 25 - 26 (25.0s to 26.5s): Shishya answer (Wide Shot)
		renderWideShot();
	}
	else if (elapsedTime < 28.5f)
	{
		// 25 - 26 (25.0s to 26.5s): Shishya answer (Wide Shot)
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 40.0f)
	{
		// 25 - 26 (25.0s to 26.5s): Shishya answer (Wide Shot)
		renderWideShot();
	}
	else if (elapsedTime < 47.5f)
	{
		// 39 - 47 (39.0s to 47.0s): King Dhana Nanda normal speaking from throne
		renderKingNormalShot();
	}
	else if (elapsedTime < 50.0f)
	{
		// 47 - 49 (47.0s to 49.0s): Standing Sage speaking
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 79.0f)
	{
		// 46.0s to 54.0s: Darbar Hall Wide Shot (Tension mounts across court)
		renderWideShot();
	}	
	else if (elapsedTime < 84.5f)
	{
		// 39 - 47 (39.0s to 47.0s): King Dhana Nanda normal speaking from throne
		renderKingNormalShot();
	}
	else if (elapsedTime < 85.0f)
	{
		// 73.0s to 86.0s: King Dhana Nanda arrogant mocking laughter
		renderKingLaughShot();
	}
	else if (elapsedTime < 94.0f)
	{
		// 86.0s to 92.5s: Darbar Wide silence reaction
		renderWideShot();
	}
	else if (elapsedTime < 98.0f)
	{
		// 86.0s to 92.5s: Darbar Wide silence reaction
		renderKingAngryShot();
	}
	else if (elapsedTime < 101.0f)
	{
		// 86.0s to 92.5s: Darbar Wide silence reaction
		renderWideShot();
	}
	else if (elapsedTime < 107.0f)
	{
		// 86.0s to 92.5s: Darbar Wide silence reaction
		renderKingAngryShot();
	}
	else if (elapsedTime < 121.0f)
	{
		// 106.0s to 121.0s: Chanakya warning of dharma and duty
		renderChanakyaResponseShot();
	}
	else if (elapsedTime < 138.0f)
	{
		// 121.0s to 138.0s: King Dhana Nanda speaks dismissively from throne
		renderKingNormalShot();
	}
	else if (elapsedTime < 161.0f)
	{
		// 138.0s to 161.0s: Standing Person delivering court decree
		renderStandingSageQuestionShot();
	}
	else if (elapsedTime < 180.0f)
	{
		// 161.0s to 180.0s: Chanakya Historic Vow to unseat tyrant
		renderChanakyaResponseShot();
	}
	else if (elapsedTime < 198.5f)
	{
		// 180.0s to 198.5s: King Dhana Nanda boiling royal rage, gripping sword
		renderKingAngryShot();
	}
	else
	{
		// 198.5s+: Grand Finale Wide View
		renderWideShot();
	}
}
