// Implementation of Royal Court Side Characters:
// 1. rlDrawSolider()   : Guard with Spear (Sainik)
// 2. rlDreawDarbari()  : Courtier or Minister (Darbari)


#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// #include "side_character.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

void rlDrawSoliderEx(float xPosition, float yPosition, float zPosition,
                     float scaleX, float scaleY, float scaleZ,
                     float rotationAngleYDegrees,
                     int bHoldSpearInRightHand);

void rlDreawDarbariEx(float xPosition, float yPosition, float zPosition,
                      float scaleX, float scaleY, float scaleZ,
                      float rotationAngleYDegrees,
                      int robeColorIndex);

// GEOMETRIC HELPER FUNCTION

static void sc_drawFilledEllipse(float cx, float cy, float rx, float ry, float zVal, float r, float g, float b, int segments)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, cy, zVal);
    for (int i = 0; i <= segments; i++)
    {
        float theta = 2.0f * (float)M_PI * (float)i / (float)segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex3f(x, y, zVal);
    }
    glEnd();
}

static void sc_drawEllipseOutline(float cx, float cy, float rx, float ry, float zVal, float lineWidth, float r, float g, float b, int segments)
{
    glLineWidth(lineWidth);
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * (float)M_PI * (float)i / (float)segments;
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex3f(x, y, zVal);
    }
    glEnd();
    glLineWidth(1.0f);
}

static void sc_drawArc(float cx, float cy, float rx, float ry, float zVal, float startAngle, float endAngle, float lineWidth, float r, float g, float b, int segments)
{
    glLineWidth(lineWidth);
    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);
    float startRad = startAngle * (float)M_PI / 180.0f;
    float endRad = endAngle * (float)M_PI / 180.0f;
    for (int i = 0; i <= segments; i++)
    {
        float theta = startRad + (endRad - startRad) * ((float)i / (float)segments);
        float x = cx + rx * cosf(theta);
        float y = cy + ry * sinf(theta);
        glVertex3f(x, y, zVal);
    }
    glEnd();
    glLineWidth(1.0f);
}

static void sc_drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float zVal, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex3f(x1, y1, zVal);
    glVertex3f(x2, y2, zVal);
    glVertex3f(x3, y3, zVal);
    glEnd();
}

static void sc_drawFilledQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float zVal, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, zVal);
    glVertex3f(x2, y2, zVal);
    glVertex3f(x3, y3, zVal);
    glVertex3f(x4, y4, zVal);
    glEnd();
}

static void sc_drawQuadOutline(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float zVal, float lineWidth, float r, float g, float b)
{
    glLineWidth(lineWidth);
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x1, y1, zVal);
    glVertex3f(x2, y2, zVal);
    glVertex3f(x3, y3, zVal);
    glVertex3f(x4, y4, zVal);
    glEnd();
    glLineWidth(1.0f);
}


// SOLDIER (SAINIK) MODULES
// Reference: Magadha royal guard with pointed helmet, spear, warrior kilt & belt

static void sc_drawSoldierFeet(void)
{
    // Tan warrior skin tone
    float skinR = 0.84f, skinG = 0.64f, skinB = 0.46f;
    float strapR = 0.45f, strapG = 0.28f, strapB = 0.15f;

    // Left Foot (x around -0.16)
    sc_drawFilledEllipse(-0.16f, 0.05f, 0.08f, 0.05f, 0.02f, skinR, skinG, skinB, 16);
    // Sandal sole
    sc_drawFilledQuad(-0.25f, 0.0f, -0.07f, 0.0f, -0.07f, 0.03f, -0.25f, 0.03f, 0.025f, 0.25f, 0.16f, 0.08f);
    // Sandal leather straps
    glLineWidth(2.0f);
    glColor3f(strapR, strapG, strapB);
    glBegin(GL_LINES);
    glVertex3f(-0.22f, 0.03f, 0.03f); glVertex3f(-0.16f, 0.09f, 0.03f);
    glVertex3f(-0.10f, 0.03f, 0.03f); glVertex3f(-0.16f, 0.09f, 0.03f);
    glEnd();
    glLineWidth(1.0f);

    // Right Foot (x around +0.16)
    sc_drawFilledEllipse(0.16f, 0.05f, 0.08f, 0.05f, 0.02f, skinR, skinG, skinB, 16);
    // Sandal sole
    sc_drawFilledQuad(0.07f, 0.0f, 0.25f, 0.0f, 0.25f, 0.03f, 0.07f, 0.03f, 0.025f, 0.25f, 0.16f, 0.08f);
    // Sandal leather straps
    glLineWidth(2.0f);
    glColor3f(strapR, strapG, strapB);
    glBegin(GL_LINES);
    glVertex3f(0.10f, 0.03f, 0.03f); glVertex3f(0.16f, 0.09f, 0.03f);
    glVertex3f(0.22f, 0.03f, 0.03f); glVertex3f(0.16f, 0.09f, 0.03f);
    glEnd();
    glLineWidth(1.0f);
}

static void sc_drawSoldierLegs(void)
{
    float skinR = 0.84f, skinG = 0.64f, skinB = 0.46f;
    float shadeR = 0.74f, shadeG = 0.54f, shadeB = 0.38f;

    // Left Shin & Calf (y = 0.05 to 0.70)
    sc_drawFilledQuad(-0.21f, 0.70f, -0.11f, 0.70f, -0.12f, 0.08f, -0.20f, 0.08f, 0.015f, skinR, skinG, skinB);
    // Left Knee cap highlight
    sc_drawFilledEllipse(-0.16f, 0.72f, 0.045f, 0.05f, 0.02f, skinR * 1.05f, skinG * 1.05f, skinB * 1.05f, 12);
    // Knee contour arc
    sc_drawArc(-0.16f, 0.70f, 0.045f, 0.03f, 0.022f, 200.0f, 340.0f, 1.5f, shadeR, shadeG, shadeB, 10);

    // Right Shin & Calf
    sc_drawFilledQuad(0.11f, 0.70f, 0.21f, 0.70f, 0.20f, 0.08f, 0.12f, 0.08f, 0.015f, skinR, skinG, skinB);
    // Right Knee cap highlight
    sc_drawFilledEllipse(0.16f, 0.72f, 0.045f, 0.05f, 0.02f, skinR * 1.05f, skinG * 1.05f, skinB * 1.05f, 12);
    // Knee contour arc
    sc_drawArc(0.16f, 0.70f, 0.045f, 0.03f, 0.022f, 200.0f, 340.0f, 1.5f, shadeR, shadeG, shadeB, 10);
}

static void sc_drawSoldierDhotiAndBelt(void)
{
    // Dark Navy / Slate warrior kilt (y = 0.70 to 1.15)
    float kiltR = 0.22f, kiltG = 0.30f, kiltB = 0.42f;
    float kiltDarkR = 0.14f, kiltDarkG = 0.20f, kiltDarkB = 0.30f;
    float kiltLightR = 0.30f, kiltLightG = 0.40f, kiltLightB = 0.54f;

    // Main flared pleated warrior wrap
    sc_drawFilledQuad(-0.30f, 1.15f, 0.30f, 1.15f, 0.36f, 0.70f, -0.36f, 0.70f, 0.025f, kiltR, kiltG, kiltB);
    sc_drawQuadOutline(-0.30f, 1.15f, 0.30f, 1.15f, 0.36f, 0.70f, -0.36f, 0.70f, 0.026f, 1.5f, 0.08f, 0.12f, 0.18f);

    // Pleat shadow folds
    sc_drawFilledTriangle(-0.25f, 1.15f, -0.15f, 1.15f, -0.22f, 0.70f, 0.027f, kiltDarkR, kiltDarkG, kiltDarkB);
    sc_drawFilledTriangle(0.15f, 1.15f, 0.25f, 1.15f, 0.22f, 0.70f, 0.027f, kiltDarkR, kiltDarkG, kiltDarkB);

    // Vertical pleat lines
    glLineWidth(1.8f);
    glColor3f(kiltLightR, kiltLightG, kiltLightB);
    glBegin(GL_LINES);
    glVertex3f(-0.18f, 1.12f, 0.028f); glVertex3f(-0.26f, 0.72f, 0.028f);
    glVertex3f(-0.08f, 1.12f, 0.028f); glVertex3f(-0.12f, 0.72f, 0.028f);
    glVertex3f(0.08f, 1.12f, 0.028f);  glVertex3f(0.12f, 0.72f, 0.028f);
    glVertex3f(0.18f, 1.12f, 0.028f);  glVertex3f(0.26f, 0.72f, 0.028f);
    glEnd();
    glLineWidth(1.0f);

    // Waistband / Sash (Kamarband) - Reddish-Brown / Terracotta
    float beltR = 0.62f, beltG = 0.32f, beltB = 0.18f;
    sc_drawFilledQuad(-0.31f, 1.25f, 0.31f, 1.25f, 0.31f, 1.13f, -0.31f, 1.13f, 0.035f, beltR, beltG, beltB);
    sc_drawQuadOutline(-0.31f, 1.25f, 0.31f, 1.25f, 0.31f, 1.13f, -0.31f, 1.13f, 0.036f, 1.5f, 0.25f, 0.10f, 0.05f);

    // Center hanging sash flap (patka)
    sc_drawFilledQuad(-0.07f, 1.22f, 0.07f, 1.22f, 0.09f, 0.62f, -0.09f, 0.62f, 0.04f, beltR, beltG, beltB);
    sc_drawQuadOutline(-0.07f, 1.22f, 0.07f, 1.22f, 0.09f, 0.62f, -0.09f, 0.62f, 0.041f, 1.2f, 0.35f, 0.15f, 0.08f);

    // Gold trim on bottom of patka
    sc_drawFilledQuad(-0.09f, 0.66f, 0.09f, 0.66f, 0.09f, 0.62f, -0.09f, 0.62f, 0.042f, 0.90f, 0.75f, 0.20f);

    // Golden waist buckle / clasp
    sc_drawFilledEllipse(0.0f, 1.19f, 0.05f, 0.045f, 0.045f, 0.92f, 0.78f, 0.22f, 16);
    sc_drawFilledEllipse(0.0f, 1.19f, 0.025f, 0.022f, 0.046f, 0.75f, 0.15f, 0.15f, 12);
}

static void sc_drawSoldierTorsoAndChest(void)
{
    float skinR = 0.84f, skinG = 0.64f, skinB = 0.46f;
    float shadeR = 0.72f, shadeG = 0.52f, shadeB = 0.36f;

    // Muscular Torso: Broad warrior shoulders (y = 1.95, width = 0.76) tapering to waist (y = 1.25, width = 0.60)
    sc_drawFilledQuad(-0.38f, 1.95f, 0.38f, 1.95f, 0.30f, 1.25f, -0.30f, 1.25f, 0.02f, skinR, skinG, skinB);
    sc_drawQuadOutline(-0.38f, 1.95f, 0.38f, 1.95f, 0.30f, 1.25f, -0.30f, 1.25f, 0.021f, 1.5f, shadeR, shadeG, shadeB);

    // Shoulder deltoid caps
    sc_drawFilledEllipse(-0.37f, 1.88f, 0.10f, 0.12f, 0.022f, skinR * 0.98f, skinG * 0.98f, skinB * 0.98f, 16);
    sc_drawFilledEllipse(0.37f, 1.88f, 0.10f, 0.12f, 0.022f, skinR * 0.98f, skinG * 0.98f, skinB * 0.98f, 16);

    // Collarbone (Clavicle lines)
    glLineWidth(2.0f);
    glColor3f(shadeR, shadeG, shadeB);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.32f, 1.90f, 0.025f);
    glVertex3f(-0.12f, 1.84f, 0.025f);
    glVertex3f(0.0f, 1.82f, 0.025f);
    glVertex3f(0.12f, 1.84f, 0.025f);
    glVertex3f(0.32f, 1.90f, 0.025f);
    glEnd();
    glLineWidth(1.0f);

    // Pectoral Muscle Contours
    sc_drawArc(-0.14f, 1.68f, 0.15f, 0.10f, 0.025f, 195.0f, 345.0f, 2.0f, shadeR, shadeG, shadeB, 16);
    sc_drawArc(0.14f, 1.68f, 0.15f, 0.10f, 0.025f, 195.0f, 345.0f, 2.0f, shadeR, shadeG, shadeB, 16);

    // Abdominal Division lines (Six-pack definition)
    glLineWidth(1.8f);
    glColor3f(shadeR, shadeG, shadeB);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 1.70f, 0.025f); glVertex3f(0.0f, 1.28f, 0.025f); // Linea alba
    glEnd();
    glLineWidth(1.0f);

    sc_drawArc(0.0f, 1.48f, 0.09f, 0.05f, 0.025f, 190.0f, 350.0f, 1.5f, shadeR, shadeG, shadeB, 12);
    sc_drawArc(0.0f, 1.36f, 0.08f, 0.045f, 0.025f, 190.0f, 350.0f, 1.5f, shadeR, shadeG, shadeB, 12);

    // Golden Armbands (Bazuband / Vanki) on upper arms
    sc_drawFilledQuad(-0.44f, 1.78f, -0.32f, 1.78f, -0.32f, 1.71f, -0.44f, 1.71f, 0.035f, 0.90f, 0.74f, 0.20f);
    sc_drawFilledQuad(0.32f, 1.78f, 0.44f, 1.78f, 0.44f, 1.71f, 0.32f, 1.71f, 0.035f, 0.90f, 0.74f, 0.20f);
    // Center gem on armbands
    sc_drawFilledEllipse(-0.38f, 1.745f, 0.015f, 0.015f, 0.038f, 0.85f, 0.15f, 0.15f, 8);
    sc_drawFilledEllipse(0.38f, 1.745f, 0.015f, 0.015f, 0.038f, 0.85f, 0.15f, 0.15f, 8);
}

static void sc_drawSoldierArms(int inRightHand)
{
    float skinR = 0.84f, skinG = 0.64f, skinB = 0.46f;
    float shadeR = 0.72f, shadeG = 0.52f, shadeB = 0.36f;
    float bracerR = 0.55f, bracerG = 0.35f, bracerB = 0.18f;

    // LEFT ARM:
    if (inRightHand)
    {
        // Left arm rests straight at attention along body
        sc_drawFilledQuad(-0.44f, 1.88f, -0.34f, 1.88f, -0.30f, 1.45f, -0.39f, 1.45f, 0.02f, skinR, skinG, skinB); // Bicep
        sc_drawFilledQuad(-0.39f, 1.45f, -0.30f, 1.45f, -0.28f, 1.05f, -0.36f, 1.05f, 0.02f, skinR, skinG, skinB); // Forearm
        // Leather Wrist Bracer
        sc_drawFilledQuad(-0.37f, 1.12f, -0.27f, 1.12f, -0.27f, 1.04f, -0.37f, 1.04f, 0.03f, bracerR, bracerG, bracerB);
        // Left fist
        sc_drawFilledEllipse(-0.32f, 0.98f, 0.055f, 0.06f, 0.03f, skinR, skinG, skinB, 14);
    }
    else
    {
        // Left arm bent holding the spear
        sc_drawFilledQuad(-0.44f, 1.88f, -0.34f, 1.88f, -0.42f, 1.45f, -0.50f, 1.45f, 0.02f, skinR, skinG, skinB);
        sc_drawFilledQuad(-0.50f, 1.45f, -0.42f, 1.45f, -0.47f, 1.25f, -0.54f, 1.25f, 0.02f, skinR, skinG, skinB);
        // Wrist bracer
        sc_drawFilledQuad(-0.55f, 1.30f, -0.46f, 1.30f, -0.46f, 1.24f, -0.55f, 1.24f, 0.03f, bracerR, bracerG, bracerB);
        // Left hand grasping spear
        sc_drawFilledEllipse(-0.52f, 1.22f, 0.055f, 0.055f, 0.05f, skinR, skinG, skinB, 16);
    }

    // RIGHT ARM:
    if (inRightHand)
    {
        // Right arm bent holding the spear
        sc_drawFilledQuad(0.34f, 1.88f, 0.44f, 1.88f, 0.50f, 1.45f, 0.42f, 1.45f, 0.02f, skinR, skinG, skinB);
        sc_drawFilledQuad(0.42f, 1.45f, 0.50f, 1.45f, 0.54f, 1.25f, 0.47f, 1.25f, 0.02f, skinR, skinG, skinB);
        // Wrist bracer
        sc_drawFilledQuad(0.46f, 1.30f, 0.55f, 1.30f, 0.55f, 1.24f, 0.46f, 1.24f, 0.03f, bracerR, bracerG, bracerB);
        // Right hand grasping spear
        sc_drawFilledEllipse(0.52f, 1.22f, 0.055f, 0.055f, 0.05f, skinR, skinG, skinB, 16);
    }
    else
    {
        // Right arm rests at attention along body
        sc_drawFilledQuad(0.34f, 1.88f, 0.44f, 1.88f, 0.39f, 1.45f, 0.30f, 1.45f, 0.02f, skinR, skinG, skinB);
        sc_drawFilledQuad(0.30f, 1.45f, 0.39f, 1.45f, 0.36f, 1.05f, 0.28f, 1.05f, 0.02f, skinR, skinG, skinB);
        // Wrist Bracer
        sc_drawFilledQuad(0.27f, 1.12f, 0.37f, 1.12f, 0.37f, 1.04f, 0.27f, 1.04f, 0.03f, bracerR, bracerG, bracerB);
        // Right fist
        sc_drawFilledEllipse(0.32f, 0.98f, 0.055f, 0.06f, 0.03f, skinR, skinG, skinB, 14);
    }
}

static void sc_drawSoldierHeadAndFace(void)
{
    float skinR = 0.84f, skinG = 0.64f, skinB = 0.46f;
    float shadeR = 0.72f, shadeG = 0.52f, shadeB = 0.36f;

    // Muscular Neck (y = 1.92 to 2.15)
    sc_drawFilledQuad(-0.13f, 2.15f, 0.13f, 2.15f, 0.16f, 1.92f, -0.16f, 1.92f, 0.022f, skinR, skinG, skinB);
    // Adam's apple
    sc_drawFilledEllipse(0.0f, 2.02f, 0.035f, 0.045f, 0.025f, skinR * 1.05f, skinG * 1.05f, skinB * 1.05f, 12);

    // Dark Hair behind ears / neck
    sc_drawFilledEllipse(0.0f, 2.22f, 0.24f, 0.26f, 0.015f, 0.12f, 0.08f, 0.05f, 24);

    // Warrior Face Oval (y center = 2.22)
    sc_drawFilledEllipse(0.0f, 2.22f, 0.20f, 0.25f, 0.03f, skinR, skinG, skinB, 32);
    // Jaw taper
    sc_drawFilledQuad(-0.17f, 2.24f, 0.17f, 2.24f, 0.08f, 2.05f, -0.08f, 2.05f, 0.032f, skinR, skinG, skinB);

    // Ears
    sc_drawFilledEllipse(-0.20f, 2.22f, 0.035f, 0.06f, 0.028f, skinR, skinG, skinB, 12);
    sc_drawFilledEllipse(0.20f, 2.22f, 0.035f, 0.06f, 0.028f, skinR, skinG, skinB, 12);

    // Eyes: Focused warrior gaze
    // Sclera (Whites of eyes)
    sc_drawFilledEllipse(-0.08f, 2.25f, 0.045f, 0.022f, 0.04f, 0.95f, 0.95f, 0.95f, 12);
    sc_drawFilledEllipse(0.08f, 2.25f, 0.045f, 0.022f, 0.04f, 0.95f, 0.95f, 0.95f, 12);
    // Black Pupils
    sc_drawFilledEllipse(-0.075f, 2.25f, 0.020f, 0.020f, 0.042f, 0.05f, 0.05f, 0.05f, 10);
    sc_drawFilledEllipse(0.085f, 2.25f, 0.020f, 0.020f, 0.042f, 0.05f, 0.05f, 0.05f, 10);
    // Eye catchlights (tiny white sparkles)
    sc_drawFilledEllipse(-0.08f, 2.26f, 0.007f, 0.007f, 0.045f, 1.0f, 1.0f, 1.0f, 6);
    sc_drawFilledEllipse(0.08f, 2.26f, 0.007f, 0.007f, 0.045f, 1.0f, 1.0f, 1.0f, 6);

    // Strong Warrior Eyebrows (Dark, thick, angled)
    glLineWidth(2.5f);
    glColor3f(0.12f, 0.08f, 0.05f);
    glBegin(GL_LINES);
    glVertex3f(-0.14f, 2.28f, 0.045f); glVertex3f(-0.03f, 2.31f, 0.045f);
    glVertex3f(0.14f, 2.28f, 0.045f);  glVertex3f(0.03f, 2.31f, 0.045f);
    glEnd();
    glLineWidth(1.0f);

    // Straight Warrior Nose
    glLineWidth(1.8f);
    glColor3f(shadeR, shadeG, shadeB);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, 2.30f, 0.045f);
    glVertex3f(-0.015f, 2.18f, 0.045f);
    glVertex3f(0.025f, 2.16f, 0.045f);
    glEnd();
    glLineWidth(1.0f);

    // Dark Curled Warrior Mustache
    sc_drawFilledEllipse(-0.05f, 2.12f, 0.06f, 0.025f, 0.042f, 0.12f, 0.08f, 0.05f, 12);
    sc_drawFilledEllipse(0.05f, 2.12f, 0.06f, 0.025f, 0.042f, 0.12f, 0.08f, 0.05f, 12);

    // Neatly trimmed chin beard
    sc_drawFilledTriangle(-0.06f, 2.08f, 0.06f, 2.08f, 0.0f, 2.01f, 0.04f, 0.14f, 0.09f, 0.06f);
}

static void sc_drawSoldierHelmet(void)
{
    // Steel / Silver conical helmet (y = 2.32 to 2.85)
    float steelR = 0.72f, steelG = 0.75f, steelB = 0.78f;
    float steelLightR = 0.88f, steelLightG = 0.90f, steelLightB = 0.94f;
    float steelDarkR = 0.52f, steelDarkG = 0.55f, steelDarkB = 0.60f;

    // Helmet Ear/Cheek Guards (curving down beside face)
    sc_drawFilledQuad(-0.23f, 2.36f, -0.17f, 2.36f, -0.18f, 2.15f, -0.23f, 2.15f, 0.048f, steelDarkR, steelDarkG, steelDarkB);
    sc_drawFilledQuad(0.17f, 2.36f, 0.23f, 2.36f, 0.23f, 2.15f, 0.18f, 2.15f, 0.048f, steelDarkR, steelDarkG, steelDarkB);

    // Helmet Brow Rim Band
    sc_drawFilledQuad(-0.24f, 2.38f, 0.24f, 2.38f, 0.22f, 2.30f, -0.22f, 2.30f, 0.05f, steelR, steelG, steelB);
    sc_drawQuadOutline(-0.24f, 2.38f, 0.24f, 2.38f, 0.22f, 2.30f, -0.22f, 2.30f, 0.051f, 1.5f, 0.15f, 0.15f, 0.18f);

    // Golden Rivets on helmet rim
    for (int i = -3; i <= 3; i++)
    {
        float rx = (float)i * 0.065f;
        sc_drawFilledEllipse(rx, 2.34f, 0.012f, 0.012f, 0.055f, 0.92f, 0.78f, 0.22f, 8);
    }

    // Main Arched Conical Helmet Dome (tapering to pointed crest)
    // Left side (Shaded)
    sc_drawFilledTriangle(-0.22f, 2.38f, 0.0f, 2.38f, 0.0f, 2.76f, 0.049f, steelDarkR, steelDarkG, steelDarkB);
    // Right side (Highlight)
    sc_drawFilledTriangle(0.0f, 2.38f, 0.22f, 2.38f, 0.0f, 2.76f, 0.049f, steelLightR, steelLightG, steelLightB);

    // Helmet Outline
    glLineWidth(2.0f);
    glColor3f(0.15f, 0.15f, 0.18f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.22f, 2.38f, 0.052f);
    glVertex3f(0.0f, 2.76f, 0.052f);
    glVertex3f(0.22f, 2.38f, 0.052f);
    glEnd();
    glLineWidth(1.0f);

    // Central Ridge Line
    glLineWidth(2.2f);
    glColor3f(steelLightR, steelLightG, steelLightB);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 2.38f, 0.053f);
    glVertex3f(0.0f, 2.76f, 0.053f);
    glEnd();
    glLineWidth(1.0f);

    // Sharp Pointed Top Finial / Spike (y = 2.76 to 2.92)
    sc_drawFilledTriangle(-0.035f, 2.76f, 0.035f, 2.76f, 0.0f, 2.92f, 0.055f, 0.95f, 0.82f, 0.25f);
    // Spike outline
    glLineWidth(1.5f);
    glColor3f(0.2f, 0.18f, 0.08f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.035f, 2.76f, 0.056f);
    glVertex3f(0.035f, 2.76f, 0.056f);
    glVertex3f(0.0f, 2.92f, 0.056f);
    glEnd();
    glLineWidth(1.0f);
}

static void sc_drawSoldierSpear(int inRightHand)
{
    float spearX = inRightHand ? 0.52f : -0.52f;
    float woodR = 0.42f, woodG = 0.26f, woodB = 0.14f;
    float steelR = 0.85f, steelG = 0.88f, steelB = 0.92f;
    float steelHighlightR = 0.98f, steelHighlightG = 0.98f, steelHighlightB = 1.0f;
    float steelShadowR = 0.62f, steelShadowG = 0.65f, steelShadowB = 0.70f;

    // 1. Long Wooden Pole / Shaft (y = 0.0 to 2.85)
    sc_drawFilledQuad(spearX - 0.022f, 2.85f, spearX + 0.022f, 2.85f,
                      spearX + 0.022f, 0.0f,  spearX - 0.022f, 0.0f,
                      0.045f, woodR, woodG, woodB);
    sc_drawQuadOutline(spearX - 0.022f, 2.85f, spearX + 0.022f, 2.85f,
                       spearX + 0.022f, 0.0f,  spearX - 0.022f, 0.0f,
                       0.046f, 1.2f, 0.18f, 0.10f, 0.05f);

    // Decorative Brass Rings / Ferrules along shaft
    sc_drawFilledQuad(spearX - 0.026f, 2.85f, spearX + 0.026f, 2.85f,
                      spearX + 0.026f, 2.78f, spearX - 0.026f, 2.78f,
                      0.048f, 0.92f, 0.78f, 0.22f);

    sc_drawFilledQuad(spearX - 0.026f, 1.35f, spearX + 0.026f, 1.35f,
                      spearX + 0.026f, 1.30f, spearX - 0.026f, 1.30f,
                      0.048f, 0.92f, 0.78f, 0.22f);

    // 2. Spear Socket (Connecting blade to wood, y = 2.85 to 2.95)
    sc_drawFilledQuad(spearX - 0.035f, 2.95f, spearX + 0.035f, 2.95f,
                      spearX + 0.026f, 2.85f, spearX - 0.026f, 2.85f,
                      0.050f, steelShadowR, steelShadowG, steelShadowB);

    // 3. Spearhead Blade (Sharp leaf / diamond blade, y = 2.95 to 3.55)
    // Left side of blade (Metallic highlight)
    sc_drawFilledTriangle(spearX - 0.08f, 3.20f, spearX, 3.20f, spearX, 3.55f, 0.052f, steelHighlightR, steelHighlightG, steelHighlightB);
    sc_drawFilledTriangle(spearX - 0.08f, 3.20f, spearX, 2.95f, spearX, 3.20f, 0.052f, steelHighlightR, steelHighlightG, steelHighlightB);

    // Right side of blade (Metallic shadow)
    sc_drawFilledTriangle(spearX, 3.20f, spearX + 0.08f, 3.20f, spearX, 3.55f, 0.052f, steelShadowR, steelShadowG, steelShadowB);
    sc_drawFilledTriangle(spearX, 3.20f, spearX + 0.08f, 3.20f, spearX, 2.95f, 0.052f, steelShadowR, steelShadowG, steelShadowB);

    // Sharp Blade Black Outline
    glLineWidth(2.0f);
    glColor3f(0.12f, 0.15f, 0.20f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(spearX, 3.55f, 0.055f);
    glVertex3f(spearX - 0.08f, 3.20f, 0.055f);
    glVertex3f(spearX, 2.95f, 0.055f);
    glVertex3f(spearX + 0.08f, 3.20f, 0.055f);
    glEnd();

    // Center Blade Ridge Line
    glBegin(GL_LINES);
    glVertex3f(spearX, 2.95f, 0.056f);
    glVertex3f(spearX, 3.55f, 0.056f);
    glEnd();
    glLineWidth(1.0f);
}

// Complete Soldier Model Assembly
static void sc_drawSoldierModel(int inRightHand)
{
    glPushMatrix();
    sc_drawSoldierFeet();
    sc_drawSoldierLegs();
    sc_drawSoldierDhotiAndBelt();
    sc_drawSoldierTorsoAndChest();
    sc_drawSoldierArms(inRightHand);
    sc_drawSoldierHeadAndFace();
    sc_drawSoldierHelmet();
    sc_drawSoldierSpear(inRightHand);
    glPopMatrix();
}

// DARBARI (COURTIER / MINISTER) MODULES
// Reference: Courtier in royal robes and turban seated on royal durbar chair

// Darbari Color Palette Generator
static void sc_getDarbariColors(int colorIndex, float *rRobe, float *gRobe, float *bRobe,
                                                float *rTurb, float *gTurb, float *bTurb,
                                                float *rTrim, float *gTrim, float *bTrim)
{
    // Golden zari trim default
    *rTrim = 0.95f; *gTrim = 0.82f; *bTrim = 0.22f;

    switch (colorIndex % 7)
    {
    case 0: // Saffron Gold (Classic Front-Right Darbari)
        *rRobe = 0.95f; *gRobe = 0.78f; *bRobe = 0.18f;
        *rTurb = 0.98f; *gTurb = 0.82f; *bTurb = 0.22f;
        break;
    case 1: // Pure Silk White / Cream (Mid-Right / Left Darbari)
        *rRobe = 0.93f; *gRobe = 0.93f; *bRobe = 0.90f;
        *rTurb = 0.95f; *gTurb = 0.85f; *bTurb = 0.35f;
        break;
    case 2: // Turquoise / Sky Blue (Right Gallery Darbari)
        *rRobe = 0.20f; *gRobe = 0.65f; *bRobe = 0.85f;
        *rTurb = 0.25f; *gTurb = 0.75f; *bTurb = 0.90f;
        break;
    case 3: // Royal Deep Blue with Crimson Turban
        *rRobe = 0.18f; *gRobe = 0.35f; *bRobe = 0.75f;
        *rTurb = 0.88f; *gTurb = 0.20f; *bTurb = 0.20f;
        break;
    case 4: // Emerald Green (Right Gallery Darbari)
        *rRobe = 0.18f; *gRobe = 0.62f; *bRobe = 0.28f;
        *rTurb = 0.25f; *gTurb = 0.72f; *bTurb = 0.35f;
        break;
    case 5: // Crimson Red / Orange (Left Gallery Darbari)
        *rRobe = 0.88f; *gRobe = 0.26f; *bRobe = 0.18f;
        *rTurb = 0.95f; *gTurb = 0.80f; *bTurb = 0.20f;
        break;
    case 6: // Imperial Purple / Violet (Left Gallery Darbari)
        *rRobe = 0.55f; *gRobe = 0.22f; *bRobe = 0.65f;
        *rTurb = 0.65f; *gTurb = 0.28f; *bTurb = 0.75f;
        break;
    default:
        *rRobe = 0.95f; *gRobe = 0.78f; *bRobe = 0.18f;
        *rTurb = 0.98f; *gTurb = 0.82f; *bTurb = 0.22f;
        break;
    }
}



static void sc_drawDarbariStandingFeetAndJutti(void)
{
    float juttiR = 0.80f, juttiG = 0.18f, juttiB = 0.22f; // Royal crimson velvet
    float goldR = 0.95f, goldG = 0.82f, goldB = 0.22f;

    // Left Foot / Jutti (x = -0.15f)
    // Shoe base
    sc_drawFilledEllipse(-0.15f, 0.05f, 0.075f, 0.045f, 0.02f, juttiR, juttiG, juttiB, 16);
    // Pointed upturned curled toe
    sc_drawFilledTriangle(-0.23f, 0.05f, -0.15f, 0.05f, -0.21f, 0.11f, 0.022f, goldR, goldG, goldB);
    // Shoe opening / gold collar
    sc_drawFilledEllipse(-0.13f, 0.06f, 0.035f, 0.025f, 0.023f, goldR, goldG, goldB, 10);

    // Right Foot / Jutti (x = +0.15f)
    // Shoe base
    sc_drawFilledEllipse(0.15f, 0.05f, 0.075f, 0.045f, 0.02f, juttiR, juttiG, juttiB, 16);
    // Pointed upturned curled toe
    sc_drawFilledTriangle(0.15f, 0.05f, 0.23f, 0.05f, 0.21f, 0.11f, 0.022f, goldR, goldG, goldB);
    // Shoe opening / gold collar
    sc_drawFilledEllipse(0.13f, 0.06f, 0.035f, 0.025f, 0.023f, goldR, goldG, goldB, 10);

    // Churidar leg gathers at ankles (peeking out beneath robe hemline at y = 0.08 to 0.20)
    // Left ankle churidar
    sc_drawFilledQuad(-0.18f, 0.20f, -0.11f, 0.20f, -0.12f, 0.07f, -0.17f, 0.07f, 0.015f, 0.90f, 0.88f, 0.82f);
    // Right ankle churidar
    sc_drawFilledQuad(0.11f, 0.20f, 0.18f, 0.20f, 0.17f, 0.07f, 0.12f, 0.07f, 0.015f, 0.90f, 0.88f, 0.82f);

    // Churidar cloth gather rings
    glLineWidth(1.5f);
    glColor3f(0.70f, 0.68f, 0.62f);
    glBegin(GL_LINES);
    glVertex3f(-0.18f, 0.11f, 0.018f); glVertex3f(-0.11f, 0.11f, 0.018f);
    glVertex3f(-0.18f, 0.15f, 0.018f); glVertex3f(-0.11f, 0.15f, 0.018f);
    glVertex3f(0.11f, 0.11f, 0.018f);  glVertex3f(0.18f, 0.11f, 0.018f);
    glVertex3f(0.11f, 0.15f, 0.018f);  glVertex3f(0.18f, 0.15f, 0.018f);
    glEnd();
    glLineWidth(1.0f);
}

static void sc_drawDarbariStandingLegsAndRobe(float rRobe, float gRobe, float bRobe, float rTrim, float gTrim, float bTrim)
{
    float darkR = rRobe * 0.72f, darkG = gRobe * 0.72f, darkB = bRobe * 0.72f;
    float lightR = (rRobe * 1.15f > 1.0f) ? 1.0f : rRobe * 1.15f;
    float lightG = (gRobe * 1.15f > 1.0f) ? 1.0f : gRobe * 1.15f;
    float lightB = (bRobe * 1.15f > 1.0f) ? 1.0f : bRobe * 1.15f;

    // 1. Main Flared Robe Skirt (from waist y=1.25 down to hemline y=0.18)
    // Trapezoid: waist width = 0.62f (x: -0.31 to +0.31), hem width = 0.82f (x: -0.41 to +0.41)
    sc_drawFilledQuad(-0.31f, 1.25f, 0.31f, 1.25f, 0.41f, 0.18f, -0.41f, 0.18f, 0.02f, rRobe, gRobe, bRobe);
    sc_drawQuadOutline(-0.31f, 1.25f, 0.31f, 1.25f, 0.41f, 0.18f, -0.41f, 0.18f, 0.021f, 1.5f, darkR, darkG, darkB);

    // 2. Lateral Draping Shading on left and right borders
    sc_drawFilledTriangle(-0.31f, 1.25f, -0.22f, 1.25f, -0.41f, 0.18f, 0.022f, darkR, darkG, darkB);
    sc_drawFilledTriangle(0.22f, 1.25f, 0.31f, 1.25f, 0.41f, 0.18f, 0.022f, darkR, darkG, darkB);

    // 3. Flowing Vertical Pleat Folds (giving rich Indian royal fabric volume)
    sc_drawFilledTriangle(-0.16f, 1.25f, -0.09f, 1.25f, -0.18f, 0.25f, 0.023f, darkR, darkG, darkB);
    sc_drawFilledTriangle(0.09f, 1.25f, 0.16f, 1.25f, 0.18f, 0.25f, 0.023f, darkR, darkG, darkB);

    // Pleat highlight ridges
    glLineWidth(2.0f);
    glColor3f(lightR, lightG, lightB);
    glBegin(GL_LINES);
    glVertex3f(-0.20f, 1.23f, 0.025f); glVertex3f(-0.28f, 0.25f, 0.025f);
    glVertex3f(-0.10f, 1.23f, 0.025f); glVertex3f(-0.12f, 0.25f, 0.025f);
    glVertex3f(0.10f, 1.23f, 0.025f);  glVertex3f(0.12f, 0.25f, 0.025f);
    glVertex3f(0.20f, 1.23f, 0.025f);  glVertex3f(0.28f, 0.25f, 0.025f);
    glEnd();
    glLineWidth(1.0f);

    // 4. Broad Golden Zari Hemline Border (Gota Patti) at bottom (y = 0.18 to 0.25)
    sc_drawFilledQuad(-0.41f, 0.25f, 0.41f, 0.25f, 0.41f, 0.18f, -0.41f, 0.18f, 0.026f, rTrim, gTrim, bTrim);
    sc_drawQuadOutline(-0.41f, 0.25f, 0.41f, 0.25f, 0.41f, 0.18f, -0.41f, 0.18f, 0.027f, 1.2f, 0.35f, 0.22f, 0.05f);

    // Golden hemline decorative motifs (little diamonds across border)
    for (int i = -4; i <= 4; i++)
    {
        float mx = (float)i * 0.085f;
        sc_drawFilledTriangle(mx - 0.02f, 0.215f, mx + 0.02f, 0.215f, mx, 0.245f, 0.028f, 0.85f, 0.20f, 0.20f);
        sc_drawFilledTriangle(mx - 0.02f, 0.215f, mx + 0.02f, 0.215f, mx, 0.185f, 0.028f, 0.85f, 0.20f, 0.20f);
    }

    // 5. Central Vertical Hanging Sash (Patka)
    // Rich embroidered stole hanging down the front from belt (y = 1.25 down to 0.42)
    float patkaR = (rRobe * 0.85f < 0.15f) ? 0.85f : (rRobe * 0.85f);
    float patkaG = (gRobe * 0.85f < 0.15f) ? 0.25f : (gRobe * 0.85f);
    float patkaB = (bRobe * 0.85f < 0.15f) ? 0.25f : (bRobe * 0.85f);

    // Patka body
    sc_drawFilledQuad(-0.09f, 1.25f, 0.09f, 1.25f, 0.10f, 0.42f, -0.10f, 0.42f, 0.030f, patkaR, patkaG, patkaB);
    sc_drawQuadOutline(-0.09f, 1.25f, 0.09f, 1.25f, 0.10f, 0.42f, -0.10f, 0.42f, 0.031f, 1.5f, rTrim, gTrim, bTrim);

    // Golden side borders on Patka
    sc_drawFilledQuad(-0.09f, 1.25f, -0.07f, 1.25f, -0.08f, 0.42f, -0.10f, 0.42f, 0.032f, rTrim, gTrim, bTrim);
    sc_drawFilledQuad(0.07f, 1.25f, 0.09f, 1.25f, 0.10f, 0.42f, 0.08f, 0.42f, 0.032f, rTrim, gTrim, bTrim);

    // Ornate bottom embroidered panel on Patka (y = 0.42 to 0.50)
    sc_drawFilledQuad(-0.10f, 0.50f, 0.10f, 0.50f, 0.10f, 0.42f, -0.10f, 0.42f, 0.033f, rTrim, gTrim, bTrim);
    // Center gem motif on bottom panel
    sc_drawFilledEllipse(0.0f, 0.46f, 0.025f, 0.022f, 0.035f, 0.85f, 0.15f, 0.18f, 10);

    // Golden tassels / fringes (Latkan) dangling from bottom of Patka
    glLineWidth(2.0f);
    glColor3f(rTrim, gTrim, bTrim);
    glBegin(GL_LINES);
    for (int t = -3; t <= 3; t++)
    {
        float tx = (float)t * 0.025f;
        glVertex3f(tx, 0.42f, 0.033f);
        glVertex3f(tx, 0.37f, 0.033f);
    }
    glEnd();
    glLineWidth(1.0f);

    // 6. Waistband / Sash (Kamarbandh) (y = 1.23 to 1.35)
    float beltR = 0.85f, beltG = 0.18f, beltB = 0.18f; // Royal silk waistband
    sc_drawFilledQuad(-0.32f, 1.35f, 0.32f, 1.35f, 0.32f, 1.23f, -0.32f, 1.23f, 0.035f, beltR, beltG, beltB);
    sc_drawQuadOutline(-0.32f, 1.35f, 0.32f, 1.35f, 0.32f, 1.23f, -0.32f, 1.23f, 0.036f, 1.5f, 0.25f, 0.05f, 0.05f);

    // Gold borders along top and bottom of waistband
    sc_drawFilledQuad(-0.32f, 1.35f, 0.32f, 1.35f, 0.32f, 1.325f, -0.32f, 1.325f, 0.037f, rTrim, gTrim, bTrim);
    sc_drawFilledQuad(-0.32f, 1.255f, 0.32f, 1.255f, 0.32f, 1.23f, -0.32f, 1.23f, 0.037f, rTrim, gTrim, bTrim);

    // Large Center Jeweled Buckle / Medallion
    sc_drawFilledEllipse(0.0f, 1.29f, 0.050f, 0.045f, 0.038f, rTrim, gTrim, bTrim, 16);
    sc_drawFilledEllipse(0.0f, 1.29f, 0.028f, 0.025f, 0.039f, 0.15f, 0.68f, 0.28f, 12); // Emerald center gem
    sc_drawEllipseOutline(0.0f, 1.29f, 0.050f, 0.045f, 0.040f, 1.2f, 0.30f, 0.20f, 0.05f, 16);
}

static void sc_drawDarbariTorso(float rRobe, float gRobe, float bRobe, float rTrim, float gTrim, float bTrim)
{
    float darkR = rRobe * 0.72f, darkG = gRobe * 0.72f, darkB = bRobe * 0.72f;

    // Main Upper Body Robe (Angarkha / Jama, y = 1.33 to 1.95)
    sc_drawFilledQuad(-0.36f, 1.95f, 0.36f, 1.95f, 0.33f, 1.33f, -0.33f, 1.33f, 0.030f, rRobe, gRobe, bRobe);
    sc_drawQuadOutline(-0.36f, 1.95f, 0.36f, 1.95f, 0.33f, 1.33f, -0.33f, 1.33f, 0.031f, 1.5f, darkR, darkG, darkB);

    // Angarkha Diagonal Cross-Over Lapel Fold (Classic Indian court tunic)
    sc_drawFilledTriangle(-0.25f, 1.95f, 0.15f, 1.95f, -0.05f, 1.33f, 0.032f, rRobe * 1.05f, gRobe * 1.05f, bRobe * 1.05f);

    // Diagonal Gold Zari Embroidered Lapel Border
    glLineWidth(3.0f);
    glColor3f(rTrim, gTrim, bTrim);
    glBegin(GL_LINES);
    glVertex3f(-0.15f, 1.95f, 0.033f);
    glVertex3f(0.12f, 1.33f, 0.033f);
    glEnd();
    glLineWidth(1.0f);

    // Royal Pearl & Emerald Necklace (Kanthi / Haar)
    for (int i = -4; i <= 4; i++)
    {
        float t = (float)i / 4.0f;
        float bx = t * 0.18f;
        float by = 1.82f - 0.12f * (1.0f - t * t);
        sc_drawFilledEllipse(bx, by, 0.018f, 0.018f, 0.034f, 0.96f, 0.96f, 0.92f, 10); // Pearl bead
    }
    // Central Emerald / Ruby Pendant
    sc_drawFilledEllipse(0.0f, 1.68f, 0.035f, 0.045f, 0.035f, 0.15f, 0.70f, 0.30f, 14);
    sc_drawEllipseOutline(0.0f, 1.68f, 0.035f, 0.045f, 0.036f, 1.5f, rTrim, gTrim, bTrim, 14);
}

static void sc_drawDarbariStandingArmsAndHands(float rRobe, float gRobe, float bRobe, float rTrim, float gTrim, float bTrim)
{
    float skinR = 0.86f, skinG = 0.67f, skinB = 0.49f;
    float darkR = rRobe * 0.72f, darkG = gRobe * 0.72f, darkB = bRobe * 0.72f;

    // LEFT ARM (In Court Attendance Posture: Bicep downward, forearm angling in to clasp hands at waist)
    // Upper Arm / Bicep Sleeve (shoulder y=1.92, elbow y=1.45)
    sc_drawFilledQuad(-0.36f, 1.92f, -0.27f, 1.92f, -0.32f, 1.45f, -0.42f, 1.45f, 0.032f, rRobe, gRobe, bRobe);
    sc_drawQuadOutline(-0.36f, 1.92f, -0.27f, 1.92f, -0.32f, 1.45f, -0.42f, 1.45f, 0.033f, 1.2f, darkR, darkG, darkB);

    // Left Forearm Sleeve (elbow y=1.45 to wrist y=1.30, angled inward towards navel)
    sc_drawFilledQuad(-0.42f, 1.45f, -0.32f, 1.45f, -0.08f, 1.34f, -0.12f, 1.26f, 0.036f, rRobe, gRobe, bRobe);
    sc_drawQuadOutline(-0.42f, 1.45f, -0.32f, 1.45f, -0.08f, 1.34f, -0.12f, 1.26f, 0.037f, 1.2f, darkR, darkG, darkB);

    // Left Wrist Brocade Cuff (Gota)
    sc_drawFilledQuad(-0.13f, 1.35f, -0.07f, 1.35f, -0.07f, 1.25f, -0.13f, 1.25f, 0.038f, rTrim, gTrim, bTrim);

    // RIGHT ARM (Symmetric Court Attendance Posture)
    // Upper Arm / Bicep Sleeve
    sc_drawFilledQuad(0.27f, 1.92f, 0.36f, 1.92f, 0.42f, 1.45f, 0.32f, 1.45f, 0.032f, rRobe, gRobe, bRobe);
    sc_drawQuadOutline(0.27f, 1.92f, 0.36f, 1.92f, 0.42f, 1.45f, 0.32f, 1.45f, 0.033f, 1.2f, darkR, darkG, darkB);

    // Right Forearm Sleeve
    sc_drawFilledQuad(0.32f, 1.45f, 0.42f, 1.45f, 0.12f, 1.26f, 0.08f, 1.34f, 0.036f, rRobe, gRobe, bRobe);
    sc_drawQuadOutline(0.32f, 1.45f, 0.42f, 1.45f, 0.12f, 1.26f, 0.08f, 1.34f, 0.037f, 1.2f, darkR, darkG, darkB);

    // Right Wrist Brocade Cuff (Gota)
    sc_drawFilledQuad(0.07f, 1.35f, 0.13f, 1.35f, 0.13f, 1.25f, 0.07f, 1.25f, 0.038f, rTrim, gTrim, bTrim);

    // CLASPED HANDS IN CENTER (Dast-Basta: Dignified respect in the Royal Durbar)
    // Left hand palm/fingers beneath
    sc_drawFilledEllipse(-0.03f, 1.29f, 0.055f, 0.040f, 0.040f, skinR, skinG, skinB, 16);
    // Right hand cupping over left hand
    sc_drawFilledEllipse(0.03f, 1.30f, 0.055f, 0.042f, 0.042f, skinR, skinG, skinB, 16);

    // Fingers detail
    glLineWidth(1.5f);
    glColor3f(skinR * 0.85f, skinG * 0.85f, skinB * 0.85f);
    glBegin(GL_LINES);
    glVertex3f(-0.04f, 1.31f, 0.043f); glVertex3f(0.02f, 1.31f, 0.043f);
    glVertex3f(-0.04f, 1.28f, 0.043f); glVertex3f(0.02f, 1.28f, 0.043f);
    glEnd();
    glLineWidth(1.0f);

    // Royal Gold Signet Rings on fingers
    sc_drawFilledEllipse(-0.02f, 1.31f, 0.012f, 0.012f, 0.045f, rTrim, gTrim, bTrim, 8);
    sc_drawFilledEllipse(0.04f, 1.29f, 0.012f, 0.012f, 0.045f, rTrim, gTrim, bTrim, 8);
}

static void sc_drawDarbariHeadAndFace(void)
{
    float skinR = 0.86f, skinG = 0.67f, skinB = 0.49f;
    float shadeR = 0.74f, shadeG = 0.55f, shadeB = 0.38f;

    // Neck (y = 1.92 to 2.12)
    sc_drawFilledQuad(-0.11f, 2.12f, 0.11f, 2.12f, 0.14f, 1.92f, -0.14f, 1.92f, 0.025f, skinR, skinG, skinB);

    // Dignified Courtier Face Oval (y center = 2.18)
    sc_drawFilledEllipse(0.0f, 2.18f, 0.19f, 0.23f, 0.030f, skinR, skinG, skinB, 32);
    // Jaw taper
    sc_drawFilledQuad(-0.16f, 2.20f, 0.16f, 2.20f, 0.07f, 2.02f, -0.07f, 2.02f, 0.031f, skinR, skinG, skinB);

    // Ears with Gold Ear Studs (Kundal)
    sc_drawFilledEllipse(-0.19f, 2.18f, 0.035f, 0.055f, 0.028f, skinR, skinG, skinB, 12);
    sc_drawFilledEllipse(0.19f, 2.18f, 0.035f, 0.055f, 0.028f, skinR, skinG, skinB, 12);
    // Kundal (Gold earrings)
    sc_drawFilledEllipse(-0.20f, 2.14f, 0.018f, 0.025f, 0.032f, 0.95f, 0.82f, 0.22f, 10);
    sc_drawFilledEllipse(0.20f, 2.14f, 0.018f, 0.025f, 0.032f, 0.95f, 0.82f, 0.22f, 10);

    // Intelligent, Noble Eyes
    sc_drawFilledEllipse(-0.075f, 2.22f, 0.040f, 0.020f, 0.034f, 0.95f, 0.95f, 0.95f, 12);
    sc_drawFilledEllipse(0.075f, 2.22f, 0.040f, 0.020f, 0.034f, 0.95f, 0.95f, 0.95f, 12);
    // Pupils
    sc_drawFilledEllipse(-0.07f, 2.22f, 0.018f, 0.018f, 0.035f, 0.05f, 0.05f, 0.05f, 10);
    sc_drawFilledEllipse(0.08f, 2.22f, 0.018f, 0.018f, 0.035f, 0.05f, 0.05f, 0.05f, 10);

    // Dignified Arched Eyebrows
    glLineWidth(2.2f);
    glColor3f(0.12f, 0.08f, 0.05f);
    glBegin(GL_LINES);
    glVertex3f(-0.13f, 2.26f, 0.036f); glVertex3f(-0.02f, 2.27f, 0.036f);
    glVertex3f(0.13f, 2.26f, 0.036f);  glVertex3f(0.02f, 2.27f, 0.036f);
    glEnd();
    glLineWidth(1.0f);

    // Forehead Chandana / Tilak Mark
    sc_drawFilledEllipse(0.0f, 2.29f, 0.012f, 0.022f, 0.036f, 0.88f, 0.18f, 0.15f, 10);

    // Refined Nose
    glLineWidth(1.6f);
    glColor3f(shadeR, shadeG, shadeB);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, 2.27f, 0.036f);
    glVertex3f(-0.012f, 2.15f, 0.036f);
    glVertex3f(0.020f, 2.13f, 0.036f);
    glEnd();
    glLineWidth(1.0f);

    // Curled Royal Mustache
    sc_drawFilledEllipse(-0.045f, 2.10f, 0.055f, 0.022f, 0.036f, 0.12f, 0.08f, 0.05f, 12);
    sc_drawFilledEllipse(0.045f, 2.10f, 0.055f, 0.022f, 0.036f, 0.12f, 0.08f, 0.05f, 12);
    // Upturned tips
    sc_drawArc(-0.09f, 2.12f, 0.03f, 0.02f, 0.037f, 40.0f, 160.0f, 1.8f, 0.12f, 0.08f, 0.05f, 8);
    sc_drawArc(0.09f, 2.12f, 0.03f, 0.02f, 0.037f, 20.0f, 140.0f, 1.8f, 0.12f, 0.08f, 0.05f, 8);

    // Neatly Groomed Beard framing jaw
    sc_drawFilledTriangle(-0.06f, 2.06f, 0.06f, 2.06f, 0.0f, 1.98f, 0.035f, 0.14f, 0.09f, 0.06f);
}

static void sc_drawDarbariTurban(float rTurb, float gTurb, float bTurb, float rTrim, float gTrim, float bTrim)
{
    float darkTurbR = rTurb * 0.72f, darkTurbG = gTurb * 0.72f, darkTurbB = bTurb * 0.72f;

    // Wrapped Court Turban Base Dome (y = 2.28 to 2.65)
    sc_drawFilledEllipse(0.0f, 2.45f, 0.25f, 0.22f, 0.035f, rTurb, gTurb, bTurb, 36);
    sc_drawEllipseOutline(0.0f, 2.45f, 0.25f, 0.22f, 0.036f, 1.8f, darkTurbR, darkTurbG, darkTurbB, 36);

    // Overlapping Wrapped Silk Cloth Bands across brow
    sc_drawFilledQuad(-0.24f, 2.42f, 0.22f, 2.34f, 0.20f, 2.26f, -0.22f, 2.32f, 0.037f, rTurb * 1.05f, gTurb * 1.05f, bTurb * 1.05f);
    sc_drawFilledQuad(-0.22f, 2.34f, 0.24f, 2.42f, 0.22f, 2.34f, -0.20f, 2.26f, 0.038f, rTurb * 0.95f, gTurb * 0.95f, bTurb * 0.95f);

    // Gold Brocade Band (Patti) across base of turban
    sc_drawFilledQuad(-0.24f, 2.36f, 0.24f, 2.36f, 0.22f, 2.31f, -0.22f, 2.31f, 0.039f, rTrim, gTrim, bTrim);
    sc_drawQuadOutline(-0.24f, 2.36f, 0.24f, 2.36f, 0.22f, 2.31f, -0.22f, 2.31f, 0.040f, 1.2f, 0.2f, 0.15f, 0.05f);

    // Top Pleated Fan Crest (Turra / Kalgi, y = 2.60 to 2.85)
    sc_drawFilledTriangle(-0.12f, 2.60f, 0.12f, 2.60f, 0.0f, 2.85f, 0.038f, rTurb * 1.10f, gTurb * 1.10f, bTurb * 1.10f);
    sc_drawArc(0.0f, 2.60f, 0.12f, 0.25f, 0.039f, 60.0f, 120.0f, 2.0f, rTrim, gTrim, bTrim, 12);

    // Royal Jeweled Brooch (Sarpech) in center front
    sc_drawFilledEllipse(0.0f, 2.46f, 0.035f, 0.05f, 0.041f, rTrim, gTrim, bTrim, 16);
    // Center Ruby / Emerald jewel
    sc_drawFilledEllipse(0.0f, 2.46f, 0.018f, 0.026f, 0.042f, 0.85f, 0.12f, 0.12f, 12);

    // Feather / Pearl Plume rising from brooch
    glLineWidth(2.2f);
    glColor3f(0.98f, 0.98f, 0.98f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 2.51f, 0.043f);
    glVertex3f(-0.02f, 2.68f, 0.043f);
    glEnd();
    glLineWidth(1.0f);
}

// Complete Darbari Model Assembly (Standing courtier in royal attendance)
static void sc_drawDarbariModel(int colorIndex)
{
    float rRobe, gRobe, bRobe;
    float rTurb, gTurb, bTurb;
    float rTrim, gTrim, bTrim;

    sc_getDarbariColors(colorIndex, &rRobe, &gRobe, &bRobe, &rTurb, &gTurb, &bTurb, &rTrim, &gTrim, &bTrim);

    glPushMatrix();
    
    sc_drawDarbariStandingFeetAndJutti();
    sc_drawDarbariStandingLegsAndRobe(rRobe, gRobe, bRobe, rTrim, gTrim, bTrim);
    sc_drawDarbariTorso(rRobe, gRobe, bRobe, rTrim, gTrim, bTrim);
    sc_drawDarbariStandingArmsAndHands(rRobe, gRobe, bRobe, rTrim, gTrim, bTrim);
    sc_drawDarbariHeadAndFace();
    sc_drawDarbariTurban(rTurb, gTurb, bTurb, rTrim, gTrim, bTrim);
    glPopMatrix();
}

void rlDrawSoliderEx(float xPosition, float yPosition, float zPosition,
                     float scaleX, float scaleY, float scaleZ,
                     float rotationAngleYDegrees,
                     int bHoldSpearInRightHand)
{
    glPushMatrix();
    glTranslatef(xPosition, yPosition, zPosition);
    if (rotationAngleYDegrees != 0.0f)
        glRotatef(rotationAngleYDegrees, 0.0f, 1.0f, 0.0f);
    glScalef(scaleX, scaleY, scaleZ);
    sc_drawSoldierModel(bHoldSpearInRightHand);
    glPopMatrix();
}

void rlDreawDarbariEx(float xPosition, float yPosition, float zPosition,
                      float scaleX, float scaleY, float scaleZ,
                      float rotationAngleYDegrees,
                      int robeColorIndex)
{
    glPushMatrix();
    glTranslatef(xPosition, yPosition, zPosition);
    if (rotationAngleYDegrees != 0.0f)
        glRotatef(rotationAngleYDegrees, 0.0f, 1.0f, 0.0f);
    glScalef(scaleX, scaleY, scaleZ);
    sc_drawDarbariModel(robeColorIndex);
    glPopMatrix();
}


