// Header Files 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// Link with OpenGL and Windows libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "GDI32.lib")

#define PI 3.14159265358979323846


// ============================================================================
// GEOMETRIC PRIMITIVES
// ============================================================================
void drawCircleXY(float cx, float cy, float cz, float r, int segments)
{
	int i;
	float angle;
	glBegin(GL_POLYGON);
	for (i = 0; i < segments; i++)
	{
		angle = 2.0f * PI * ((float)i / (float)segments);
		glVertex3f(cx + cosf(angle) * r, cy + sinf(angle) * r, cz);
	}
	glEnd();
}

void drawDiscXZ(float cx, float cy, float cz, float r, int segments)
{
	int i;
	float angle;
	glBegin(GL_POLYGON);
	for (i = 0; i < segments; i++)
	{
		angle = 2.0f * PI * ((float)i / (float)segments);
		glVertex3f(cx + cosf(angle) * r, cy, cz + sinf(angle) * r);
	}
	glEnd();
}

void drawCylinderY(float cx, float cy, float cz, float r, float h, int segments)
{
	int i;
	float halfH = h * 0.5f;
	float angle;
	float x, z;
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= segments; i++)
	{
		angle = 2.0f * PI * ((float)i / (float)segments);
		x = cosf(angle) * r;
		z = sinf(angle) * r;
		glVertex3f(cx + x, cy - halfH, cz + z);
		glVertex3f(cx + x, cy + halfH, cz + z);
	}
	glEnd();
}

void drawBox3D(float cx, float cy, float cz, float w, float h, float d)
{
	float hw = w * 0.5f;
	float hh = h * 0.5f;
	float hd = d * 0.5f;

	glBegin(GL_QUADS);
	// Front Face
	glVertex3f(cx - hw, cy - hh, cz + hd);
	glVertex3f(cx + hw, cy - hh, cz + hd);
	glVertex3f(cx + hw, cy + hh, cz + hd);
	glVertex3f(cx - hw, cy + hh, cz + hd);

	// Back Face
	glVertex3f(cx - hw, cy - hh, cz - hd);
	glVertex3f(cx - hw, cy + hh, cz - hd);
	glVertex3f(cx + hw, cy + hh, cz - hd);
	glVertex3f(cx + hw, cy - hh, cz - hd);

	// Top Face
	glVertex3f(cx - hw, cy + hh, cz - hd);
	glVertex3f(cx - hw, cy + hh, cz + hd);
	glVertex3f(cx + hw, cy + hh, cz + hd);
	glVertex3f(cx + hw, cy + hh, cz - hd);

	// Bottom Face
	glVertex3f(cx - hw, cy - hh, cz - hd);
	glVertex3f(cx + hw, cy - hh, cz - hd);
	glVertex3f(cx + hw, cy - hh, cz + hd);
	glVertex3f(cx - hw, cy - hh, cz + hd);

	// Right Face
	glVertex3f(cx + hw, cy - hh, cz - hd);
	glVertex3f(cx + hw, cy + hh, cz - hd);
	glVertex3f(cx + hw, cy + hh, cz + hd);
	glVertex3f(cx + hw, cy - hh, cz + hd);

	// Left Face
	glVertex3f(cx - hw, cy - hh, cz - hd);
	glVertex3f(cx - hw, cy - hh, cz + hd);
	glVertex3f(cx - hw, cy + hh, cz + hd);
	glVertex3f(cx - hw, cy + hh, cz - hd);
	glEnd();
}

void drawTrapezoidXY(float cx, float cy, float cz, float topW, float bottomW, float h)
{
	float htop = topW * 0.5f;
	float hbot = bottomW * 0.5f;
	float hh = h * 0.5f;

	glBegin(GL_QUADS);
	glVertex3f(cx - hbot, cy - hh, cz);
	glVertex3f(cx + hbot, cy - hh, cz);
	glVertex3f(cx + htop, cy + hh, cz);
	glVertex3f(cx - htop, cy + hh, cz);
	glEnd();
}

// ============================================================================
// ELEPHANT PILLAR
// ============================================================================
void drawElephantPillar(float x, float y, float z, float scale, float rotY)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	// Base Pedestal
	glColor3f(0.78f, 0.36f, 0.14f);
	drawBox3D(0.0f, 0.15f, 0.0f, 1.80f, 0.30f, 1.80f);
	glColor3f(0.86f, 0.42f, 0.17f);
	drawBox3D(0.0f, 0.35f, 0.0f, 1.60f, 0.20f, 1.60f);
	glColor3f(0.88f, 0.44f, 0.18f);
	drawBox3D(0.0f, 0.70f, 0.0f, 1.45f, 0.50f, 1.45f);
	glColor3f(0.92f, 0.48f, 0.20f);
	drawBox3D(0.0f, 1.00f, 0.0f, 1.60f, 0.15f, 1.60f);
	glColor3f(0.72f, 0.28f, 0.10f);
	drawBox3D(0.0f, 1.10f, 0.0f, 1.50f, 0.08f, 1.50f);

	// Central Pillar Shaft
	glColor3f(0.88f, 0.44f, 0.18f);
	drawCylinderY(0.0f, 3.45f, 0.0f, 0.38f, 4.62f, 24);
	glColor3f(0.78f, 0.34f, 0.14f);
	drawDiscXZ(0.0f, 1.14f, 0.0f, 0.38f, 24);
	drawDiscXZ(0.0f, 5.76f, 0.0f, 0.38f, 24);

	// Elephant Legs
	glColor3f(0.80f, 0.62f, 0.32f);
	drawBox3D(-0.32f, 1.45f,  0.35f, 0.22f, 0.62f, 0.22f);
	drawBox3D( 0.32f, 1.45f,  0.35f, 0.22f, 0.62f, 0.22f);
	drawBox3D(-0.32f, 1.45f, -0.35f, 0.22f, 0.62f, 0.22f);
	drawBox3D( 0.32f, 1.45f, -0.35f, 0.22f, 0.62f, 0.22f);

	// Feet rings
	glColor3f(0.74f, 0.56f, 0.30f);
	drawBox3D(-0.32f, 1.18f,  0.35f, 0.24f, 0.10f, 0.24f);
	drawBox3D( 0.32f, 1.18f,  0.35f, 0.24f, 0.10f, 0.24f);
	drawBox3D(-0.32f, 1.18f, -0.35f, 0.24f, 0.10f, 0.24f);
	drawBox3D( 0.32f, 1.18f, -0.35f, 0.24f, 0.10f, 0.24f);

	// Nails
	glColor3f(0.96f, 0.95f, 0.90f);
	drawBox3D(-0.38f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D(-0.32f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D(-0.26f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D( 0.26f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D( 0.32f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D( 0.38f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);

	// Elephant Body
	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 1.95f, 0.0f, 0.90f, 0.85f, 1.25f);
	drawBox3D(0.0f, 1.92f, -0.58f, 0.82f, 0.78f, 0.20f);
	drawCircleXY(-0.45f, 1.95f, 0.0f, 0.38f, 16);
	drawCircleXY( 0.45f, 1.95f, 0.0f, 0.38f, 16);

	// Tail
	glColor3f(0.75f, 0.58f, 0.28f);
	drawBox3D(0.0f, 1.62f, -0.68f, 0.04f, 0.50f, 0.04f);
	drawTrapezoidXY(0.0f, 1.34f, -0.68f, 0.08f, 0.02f, 0.10f);

	// Saddle / Blanket
	glColor3f(0.76f, 0.14f, 0.18f);
	drawBox3D(0.0f, 2.15f, 0.0f, 0.96f, 0.52f, 0.78f);
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D(0.0f, 1.90f, 0.0f, 0.98f, 0.08f, 0.80f);
	drawBox3D(-0.49f, 1.82f,  0.35f, 0.06f, 0.10f, 0.06f);
	drawBox3D( 0.49f, 1.82f,  0.35f, 0.06f, 0.10f, 0.06f);
	drawBox3D(-0.49f, 1.82f, -0.35f, 0.06f, 0.10f, 0.06f);
	drawBox3D( 0.49f, 1.82f, -0.35f, 0.06f, 0.10f, 0.06f);

	// Neck and Head
	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 1.95f, 0.55f, 0.82f, 0.75f, 0.25f);
	glColor3f(0.95f, 0.80f, 0.20f);
	drawTrapezoidXY(0.0f, 1.78f, 0.69f, 0.60f, 0.35f, 0.14f);
	drawCircleXY(0.0f, 1.66f, 0.70f, 0.08f, 12);

	// Forehead
	glColor3f(0.86f, 0.69f, 0.35f);
	drawBox3D(0.0f, 2.22f, 0.78f, 0.68f, 0.62f, 0.48f);
	drawCircleXY(-0.18f, 2.50f, 0.88f, 0.22f, 18);
	drawCircleXY( 0.18f, 2.50f, 0.88f, 0.22f, 18);

	// Headcloth Diadem
	glColor3f(0.96f, 0.84f, 0.22f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.18f, 2.54f, 0.96f);
	glVertex3f( 0.18f, 2.54f, 0.96f);
	glVertex3f( 0.14f, 2.30f, 0.98f);
	glVertex3f( 0.00f, 2.15f, 1.00f);
	glVertex3f(-0.14f, 2.30f, 0.98f);
	glEnd();
	glColor3f(0.85f, 0.12f, 0.18f);
	drawCircleXY(0.0f, 2.36f, 1.01f, 0.06f, 12);

	// Eyes
	glColor3f(0.20f, 0.15f, 0.10f);
	drawCircleXY(-0.35f, 2.28f, 0.88f, 0.05f, 10);
	drawCircleXY( 0.35f, 2.28f, 0.88f, 0.05f, 10);

	// Left Ear
	glColor3f(0.84f, 0.66f, 0.32f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.32f, 2.45f, 0.70f);
	glVertex3f(-0.62f, 2.40f, 0.65f);
	glVertex3f(-0.68f, 2.05f, 0.60f);
	glVertex3f(-0.50f, 1.75f, 0.65f);
	glVertex3f(-0.32f, 1.95f, 0.72f);
	glEnd();
	glColor3f(0.76f, 0.52f, 0.30f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.36f, 2.35f, 0.71f);
	glVertex3f(-0.56f, 2.30f, 0.66f);
	glVertex3f(-0.60f, 2.08f, 0.62f);
	glVertex3f(-0.46f, 1.88f, 0.66f);
	glVertex3f(-0.36f, 2.02f, 0.73f);
	glEnd();

	// Right Ear
	glColor3f(0.84f, 0.66f, 0.32f);
	glBegin(GL_POLYGON);
	glVertex3f(0.32f, 2.45f, 0.70f);
	glVertex3f(0.62f, 2.40f, 0.65f);
	glVertex3f(0.68f, 2.05f, 0.60f);
	glVertex3f(0.50f, 1.75f, 0.65f);
	glVertex3f(0.32f, 1.95f, 0.72f);
	glEnd();
	glColor3f(0.76f, 0.52f, 0.30f);
	glBegin(GL_POLYGON);
	glVertex3f(0.36f, 2.35f, 0.71f);
	glVertex3f(0.56f, 2.30f, 0.66f);
	glVertex3f(0.60f, 2.08f, 0.62f);
	glVertex3f(0.46f, 1.88f, 0.66f);
	glVertex3f(0.36f, 2.02f, 0.73f);
	glEnd();

	// Tusks
	glColor3f(0.96f, 0.95f, 0.88f);
	drawBox3D(-0.18f, 1.95f, 0.96f, 0.08f, 0.10f, 0.15f);
	drawBox3D(-0.20f, 1.90f, 1.10f, 0.07f, 0.08f, 0.18f);
	drawBox3D(-0.21f, 1.98f, 1.25f, 0.05f, 0.07f, 0.15f);
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D(-0.18f, 1.95f, 0.98f, 0.09f, 0.11f, 0.04f);

	glColor3f(0.96f, 0.95f, 0.88f);
	drawBox3D( 0.18f, 1.95f, 0.96f, 0.08f, 0.10f, 0.15f);
	drawBox3D( 0.20f, 1.90f, 1.10f, 0.07f, 0.08f, 0.18f);
	drawBox3D( 0.21f, 1.98f, 1.25f, 0.05f, 0.07f, 0.15f);
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D( 0.18f, 1.95f, 0.98f, 0.09f, 0.11f, 0.04f);

	// Trunk
	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 1.98f, 0.95f, 0.26f, 0.25f, 0.22f);
	drawBox3D(0.0f, 1.75f, 1.00f, 0.22f, 0.26f, 0.20f);
	drawBox3D(0.0f, 1.50f, 1.05f, 0.19f, 0.26f, 0.18f);
	drawBox3D(0.0f, 1.28f, 1.12f, 0.16f, 0.22f, 0.16f);
	drawBox3D(0.0f, 1.18f, 1.24f, 0.14f, 0.14f, 0.18f);
	drawBox3D(0.0f, 1.30f, 1.30f, 0.12f, 0.14f, 0.12f);

	// Trunk Gold Bands
	glColor3f(0.78f, 0.60f, 0.28f);
	drawBox3D(0.0f, 1.86f, 1.00f, 0.24f, 0.03f, 0.21f);
	drawBox3D(0.0f, 1.62f, 1.05f, 0.21f, 0.03f, 0.19f);
	drawBox3D(0.0f, 1.38f, 1.10f, 0.18f, 0.03f, 0.17f);

	// Rider Platform
	glColor3f(0.82f, 0.38f, 0.16f);
	drawCylinderY(0.0f, 2.50f, 0.0f, 0.44f, 0.20f, 24);
	drawDiscXZ(0.0f, 2.40f, 0.0f, 0.44f, 24);
	drawDiscXZ(0.0f, 2.60f, 0.0f, 0.44f, 24);

	glColor3f(0.88f, 0.44f, 0.18f);
	drawBox3D(0.0f, 3.05f, 0.35f, 0.38f, 0.60f, 0.45f);
	glColor3f(0.92f, 0.48f, 0.20f);
	drawCircleXY(0.0f, 3.45f, 0.48f, 0.18f, 16);
	glColor3f(0.72f, 0.28f, 0.10f);
	drawCircleXY(0.0f, 3.45f, 0.44f, 0.26f, 16);

	// Flags
	glColor3f(0.92f, 0.78f, 0.26f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.16f, 3.10f, 0.35f);
	glVertex3f(-0.55f, 3.65f, 0.30f);
	glVertex3f(-0.48f, 3.85f, 0.28f);
	glVertex3f(-0.16f, 3.40f, 0.32f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( 0.16f, 3.10f, 0.35f);
	glVertex3f( 0.55f, 3.65f, 0.30f);
	glVertex3f( 0.48f, 3.85f, 0.28f);
	glVertex3f( 0.16f, 3.40f, 0.32f);
	glEnd();

	// Pillar Capital Rings
	glColor3f(0.95f, 0.82f, 0.22f);
	drawCylinderY(0.0f, 3.90f, 0.0f, 0.43f, 0.14f, 24);
	drawDiscXZ(0.0f, 3.83f, 0.0f, 0.43f, 24);
	drawDiscXZ(0.0f, 3.97f, 0.0f, 0.43f, 24);

	drawCylinderY(0.0f, 4.80f, 0.0f, 0.43f, 0.14f, 24);
	drawDiscXZ(0.0f, 4.73f, 0.0f, 0.43f, 24);
	drawDiscXZ(0.0f, 4.87f, 0.0f, 0.43f, 24);

	// Pillar Top Tiered Capital
	glColor3f(0.88f, 0.44f, 0.18f);
	drawBox3D(0.0f, 5.85f, 0.0f, 1.10f, 0.20f, 1.10f);
	glColor3f(0.82f, 0.38f, 0.16f);
	drawBox3D(0.0f, 6.05f, 0.0f, 1.35f, 0.20f, 1.35f);
	glColor3f(0.72f, 0.28f, 0.10f);
	drawBox3D(0.0f, 6.25f, 0.0f, 1.60f, 0.20f, 1.60f);

	// Capital Abacus and Connector joining with upper beam
	glColor3f(0.86f, 0.42f, 0.17f);
	drawBox3D(0.0f, 6.45f, 0.0f, 1.45f, 0.20f, 1.45f);
	glColor3f(0.92f, 0.48f, 0.20f);
	drawBox3D(0.0f, 6.62f, 0.0f, 1.70f, 0.16f, 1.70f);
	glColor3f(0.62f, 0.22f, 0.08f);
	drawBox3D(0.0f, 6.76f, 0.0f, 1.85f, 0.14f, 1.85f);

	glPopMatrix();
}

// ============================================================================
// ELEPHANT CART
// ============================================================================
void drawElephantCart(float x, float y, float z, float scale, float rotY)
{
	int i;
	int k;
	float angle;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	// 1. ELEPHANT
	// Legs
	glColor3f(0.52f, 0.54f, 0.56f);
	drawBox3D( 0.38f, 0.25f,  0.24f, 0.22f, 0.50f, 0.20f);
	drawBox3D( 0.38f, 0.25f, -0.24f, 0.22f, 0.50f, 0.20f);
	drawBox3D(-0.38f, 0.25f,  0.24f, 0.22f, 0.50f, 0.20f);
	drawBox3D(-0.38f, 0.25f, -0.24f, 0.22f, 0.50f, 0.20f);

	// Foot Pads
	glColor3f(0.44f, 0.46f, 0.48f);
	drawBox3D( 0.38f, 0.04f,  0.24f, 0.24f, 0.08f, 0.22f);
	drawBox3D( 0.38f, 0.04f, -0.24f, 0.24f, 0.08f, 0.22f);
	drawBox3D(-0.38f, 0.04f,  0.24f, 0.24f, 0.08f, 0.22f);
	drawBox3D(-0.38f, 0.04f, -0.24f, 0.24f, 0.08f, 0.22f);

	// Toenails (White Ivory on feet)
	glColor3f(0.96f, 0.95f, 0.90f);
	// Front Left Foot
	drawBox3D( 0.49f, 0.04f,  0.19f, 0.04f, 0.06f, 0.04f);
	drawBox3D( 0.50f, 0.04f,  0.24f, 0.04f, 0.06f, 0.04f);
	drawBox3D( 0.49f, 0.04f,  0.29f, 0.04f, 0.06f, 0.04f);
	// Front Right Foot
	drawBox3D( 0.49f, 0.04f, -0.19f, 0.04f, 0.06f, 0.04f);
	drawBox3D( 0.50f, 0.04f, -0.24f, 0.04f, 0.06f, 0.04f);
	drawBox3D( 0.49f, 0.04f, -0.29f, 0.04f, 0.06f, 0.04f);
	// Rear Left Foot
	drawBox3D(-0.49f, 0.04f,  0.19f, 0.04f, 0.06f, 0.04f);
	drawBox3D(-0.50f, 0.04f,  0.24f, 0.04f, 0.06f, 0.04f);
	drawBox3D(-0.49f, 0.04f,  0.29f, 0.04f, 0.06f, 0.04f);
	// Rear Right Foot
	drawBox3D(-0.49f, 0.04f, -0.19f, 0.04f, 0.06f, 0.04f);
	drawBox3D(-0.50f, 0.04f, -0.24f, 0.04f, 0.06f, 0.04f);
	drawBox3D(-0.49f, 0.04f, -0.29f, 0.04f, 0.06f, 0.04f);

	// Body Torso
	glColor3f(0.58f, 0.60f, 0.62f);
	drawBox3D(0.0f, 0.72f, 0.0f, 1.05f, 0.52f, 0.70f);
	drawBox3D(0.0f, 0.95f, 0.0f, 0.90f, 0.16f, 0.64f);

	// Side curves
	glColor3f(0.54f, 0.56f, 0.58f);
	drawCircleXY(-0.20f, 0.75f,  0.35f, 0.26f, 14);
	drawCircleXY( 0.20f, 0.75f,  0.35f, 0.26f, 14);
	drawCircleXY(-0.20f, 0.75f, -0.35f, 0.26f, 14);
	drawCircleXY( 0.20f, 0.75f, -0.35f, 0.26f, 14);

	// Saddle Blanket (Terracotta orange with gold border)
	glColor3f(0.86f, 0.44f, 0.24f);
	drawBox3D(-0.02f, 0.90f, 0.0f, 0.62f, 0.30f, 0.74f);
	// Gold Border Hem
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D(-0.02f, 0.74f,  0.37f, 0.64f, 0.04f, 0.03f);
	drawBox3D(-0.02f, 0.74f, -0.37f, 0.64f, 0.04f, 0.03f);
	drawBox3D( 0.29f, 0.88f,  0.37f, 0.04f, 0.26f, 0.03f);
	drawBox3D(-0.33f, 0.88f,  0.37f, 0.04f, 0.26f, 0.03f);
	drawBox3D( 0.29f, 0.88f, -0.37f, 0.04f, 0.26f, 0.03f);
	drawBox3D(-0.33f, 0.88f, -0.37f, 0.04f, 0.26f, 0.03f);

	// Under-belly girth strap
	glColor3f(0.38f, 0.24f, 0.14f);
	drawBox3D(-0.02f, 0.47f, 0.0f, 0.08f, 0.04f, 0.72f);

	// Breast collar harness strap
	glColor3f(0.42f, 0.26f, 0.14f);
	drawBox3D(0.48f, 0.62f, 0.0f, 0.22f, 0.06f, 0.72f);

	// Head & Forehead
	glColor3f(0.58f, 0.60f, 0.62f);
	drawBox3D(0.65f, 0.80f, 0.0f, 0.40f, 0.46f, 0.50f);
	// Dual temporal lobes on forehead
	glColor3f(0.55f, 0.57f, 0.59f);
	drawCircleXY(0.68f, 1.04f,  0.13f, 0.15f, 12);
	drawCircleXY(0.68f, 1.04f, -0.13f, 0.15f, 12);

	// Eyes
	glColor3f(0.15f, 0.12f, 0.08f);
	drawCircleXY(0.70f, 0.88f,  0.26f, 0.032f, 8);
	drawCircleXY(0.70f, 0.88f, -0.26f, 0.032f, 8);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircleXY(0.71f, 0.89f,  0.265f, 0.012f, 6);
	drawCircleXY(0.71f, 0.89f, -0.265f, 0.012f, 6);

	// Ears with inner ear shading
	glColor3f(0.50f, 0.52f, 0.54f);
	glBegin(GL_POLYGON);
	glVertex3f(0.50f, 0.95f,  0.26f);
	glVertex3f(0.35f, 0.95f,  0.38f);
	glVertex3f(0.32f, 0.68f,  0.42f);
	glVertex3f(0.48f, 0.62f,  0.30f);
	glEnd();

	glColor3f(0.62f, 0.50f, 0.50f);
	glBegin(GL_POLYGON);
	glVertex3f(0.48f, 0.92f,  0.28f);
	glVertex3f(0.38f, 0.92f,  0.37f);
	glVertex3f(0.35f, 0.72f,  0.40f);
	glVertex3f(0.46f, 0.66f,  0.31f);
	glEnd();

	glColor3f(0.50f, 0.52f, 0.54f);
	glBegin(GL_POLYGON);
	glVertex3f(0.50f, 0.95f, -0.26f);
	glVertex3f(0.35f, 0.95f, -0.38f);
	glVertex3f(0.32f, 0.68f, -0.42f);
	glVertex3f(0.48f, 0.62f, -0.30f);
	glEnd();

	glColor3f(0.62f, 0.50f, 0.50f);
	glBegin(GL_POLYGON);
	glVertex3f(0.48f, 0.92f, -0.28f);
	glVertex3f(0.38f, 0.92f, -0.37f);
	glVertex3f(0.35f, 0.72f, -0.40f);
	glVertex3f(0.46f, 0.66f, -0.31f);
	glEnd();

	// Trunk (Curved with creases)
	glColor3f(0.56f, 0.58f, 0.60f);
	drawBox3D(0.85f, 0.70f, 0.0f, 0.16f, 0.26f, 0.18f);
	drawBox3D(0.93f, 0.48f, 0.0f, 0.14f, 0.24f, 0.15f);
	drawBox3D(0.91f, 0.30f, 0.0f, 0.12f, 0.18f, 0.13f);
	drawBox3D(0.85f, 0.22f, 0.0f, 0.10f, 0.10f, 0.11f);

	// Trunk crease lines
	glColor3f(0.46f, 0.48f, 0.50f);
	drawBox3D(0.86f, 0.62f, 0.0f, 0.17f, 0.02f, 0.19f);
	drawBox3D(0.94f, 0.42f, 0.0f, 0.15f, 0.02f, 0.16f);

	// Tusks with Gold Base Rings
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D(0.78f, 0.60f,  0.14f, 0.04f, 0.08f, 0.08f);
	drawBox3D(0.78f, 0.60f, -0.14f, 0.04f, 0.08f, 0.08f);

	glColor3f(0.96f, 0.95f, 0.88f);
	drawBox3D(0.88f, 0.60f,  0.14f, 0.18f, 0.05f, 0.05f);
	drawBox3D(0.88f, 0.60f, -0.14f, 0.18f, 0.05f, 0.05f);

	// Tail with hair tuft
	glColor3f(0.48f, 0.50f, 0.52f);
	drawBox3D(-0.54f, 0.64f, 0.0f, 0.03f, 0.30f, 0.03f);
	glColor3f(0.20f, 0.20f, 0.20f);
	drawTrapezoidXY(-0.55f, 0.46f, 0.0f, 0.04f, 0.08f, 0.08f);

	// 2. TOW BARS
	glColor3f(0.50f, 0.32f, 0.16f);
	drawBox3D(-0.75f, 0.38f,  0.30f, 0.65f, 0.06f, 0.06f);
	drawBox3D(-0.75f, 0.38f, -0.30f, 0.65f, 0.06f, 0.06f);
	drawBox3D(-0.45f, 0.38f,  0.0f,  0.06f, 0.06f, 0.64f);

	// 3. WOODEN CART
	// Floor
	glColor3f(0.62f, 0.40f, 0.22f);
	drawBox3D(-1.45f, 0.38f, 0.0f, 0.95f, 0.05f, 0.72f);

	// Walls
	glColor3f(0.68f, 0.44f, 0.24f);
	drawBox3D(-1.45f, 0.54f,  0.35f, 0.95f, 0.26f, 0.04f);
	drawBox3D(-1.45f, 0.54f, -0.35f, 0.95f, 0.26f, 0.04f);
	drawBox3D(-0.99f, 0.54f,  0.0f,  0.04f, 0.26f, 0.70f);

	// Slanted Tailgate
	glBegin(GL_QUADS);
	glColor3f(0.64f, 0.40f, 0.20f);
	glVertex3f(-1.92f, 0.38f, -0.35f);
	glVertex3f(-1.92f, 0.38f,  0.35f);
	glVertex3f(-2.02f, 0.58f,  0.35f);
	glVertex3f(-2.02f, 0.58f, -0.35f);
	glEnd();

	// Cargo Block
	glColor3f(0.82f, 0.42f, 0.22f);
	drawBox3D(-1.45f, 0.50f, 0.0f, 0.42f, 0.20f, 0.40f);

	// Axle
	glColor3f(0.44f, 0.26f, 0.12f);
	drawBox3D(-1.45f, 0.28f, 0.0f, 0.08f, 0.08f, 0.88f);

	// Wheels
	for (i = 0; i < 2; i++)
	{
		float wz = (i == 0) ? 0.42f : -0.42f;

		glColor3f(0.40f, 0.24f, 0.12f);
		drawCircleXY(-1.45f, 0.28f, wz, 0.08f, 12);

		glColor3f(0.55f, 0.34f, 0.18f);
		glLineWidth(3.0f);
		glBegin(GL_LINE_LOOP);
		for (k = 0; k < 18; k++)
		{
			angle = 2.0f * PI * ((float)k / 18.0f);
			glVertex3f(-1.45f + cosf(angle) * 0.28f, 0.28f + sinf(angle) * 0.28f, wz);
		}
		glEnd();

		glLineWidth(2.0f);
		glBegin(GL_LINES);
		for (k = 0; k < 8; k++)
		{
			angle = 2.0f * PI * ((float)k / 8.0f);
			glVertex3f(-1.45f, 0.28f, wz);
			glVertex3f(-1.45f + cosf(angle) * 0.28f, 0.28f + sinf(angle) * 0.28f, wz);
		}
		glEnd();
		glLineWidth(1.0f);
	}

	glPopMatrix();
}

// ============================================================================
// SOLDIER / GUARD
// ============================================================================
void drawSoldier(float x, float y, float z, float scale, float rBody, float gBody, float bBody, float rTurban, float gTurban, float bTurban, int hasSpear, float rotY)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	// Head
	glColor3f(0.85f, 0.62f, 0.45f);
	drawCircleXY(0.0f, 1.55f, 0.0f, 0.20f, 24);

	// Turban
	glColor3f(rTurban, gTurban, bTurban);
	glBegin(GL_POLYGON);
	glVertex3f(-0.22f, 1.58f, 0.01f);
	glVertex3f( 0.22f, 1.58f, 0.01f);
	glVertex3f( 0.20f, 1.76f, 0.01f);
	glVertex3f( 0.00f, 1.84f, 0.01f);
	glVertex3f(-0.20f, 1.76f, 0.01f);
	glEnd();

	// Turban Jewel
	glColor3f(0.95f, 0.82f, 0.20f);
	drawCircleXY(0.0f, 1.73f, 0.02f, 0.05f, 12);

	// Turban Plume
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f( 0.00f, 1.95f, 0.02f);
	glVertex3f(-0.04f, 1.75f, 0.02f);
	glVertex3f( 0.04f, 1.75f, 0.02f);
	glEnd();

	// Neck
	glColor3f(0.80f, 0.58f, 0.40f);
	drawTrapezoidXY(0.0f, 1.33f, 0.0f, 0.12f, 0.14f, 0.10f);

	// Torso
	glColor3f(rBody, gBody, bBody);
	drawTrapezoidXY(0.0f, 1.05f, 0.0f, 0.55f, 0.40f, 0.46f);

	// Shoulder Epaulets
	glColor3f(0.92f, 0.78f, 0.22f);
	drawCircleXY(-0.26f, 1.24f, 0.01f, 0.08f, 12);
	drawCircleXY( 0.26f, 1.24f, 0.01f, 0.08f, 12);

	// Waistband
	glColor3f(0.95f, 0.80f, 0.20f);
	drawTrapezoidXY(0.0f, 0.78f, 0.0f, 0.41f, 0.38f, 0.08f);

	// Sash
	glColor3f(rTurban, gTurban, bTurban);
	drawTrapezoidXY(0.0f, 0.66f, 0.01f, 0.12f, 0.18f, 0.18f);

	// Dhoti
	glColor3f(0.90f, 0.85f, 0.75f);
	drawTrapezoidXY(0.0f, 0.42f, 0.0f, 0.38f, 0.28f, 0.60f);

	// Feet
	glColor3f(0.80f, 0.58f, 0.40f);
	drawTrapezoidXY(-0.08f, 0.06f, 0.0f, 0.07f, 0.06f, 0.14f);
	drawTrapezoidXY( 0.08f, 0.06f, 0.0f, 0.07f, 0.06f, 0.14f);

	// Weapon
	if (hasSpear != 0)
	{
		glColor3f(0.48f, 0.30f, 0.15f);
		drawBox3D(0.32f, 1.10f, 0.05f, 0.04f, 2.10f, 0.04f);

		glColor3f(0.88f, 0.92f, 0.98f);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.32f, 2.38f, 0.06f);
		glVertex3f(0.26f, 2.14f, 0.06f);
		glVertex3f(0.38f, 2.14f, 0.06f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(0.24f, 2.26f, 0.06f);
		glVertex3f(0.22f, 2.14f, 0.06f);
		glVertex3f(0.26f, 2.14f, 0.06f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(0.40f, 2.26f, 0.06f);
		glVertex3f(0.38f, 2.14f, 0.06f);
		glVertex3f(0.42f, 2.14f, 0.06f);
		glEnd();

		glColor3f(0.95f, 0.80f, 0.20f);
		drawBox3D(0.32f, 2.13f, 0.05f, 0.08f, 0.04f, 0.06f);
	}
	else
	{
		glColor3f(0.95f, 0.82f, 0.20f);
		drawCircleXY(0.0f, 0.92f, 0.12f, 0.14f, 16);
		glColor3f(0.20f, 0.75f, 0.30f);
		drawCircleXY(0.0f, 0.96f, 0.13f, 0.08f, 12);
	}

	glPopMatrix();
}

// ============================================================================
// STYLIZED TREES
// ============================================================================
void drawTree(float x, float y, float z, float scale)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);

	// Trunk
	glColor3f(0.50f, 0.35f, 0.20f);
	drawCylinderY(0.0f, 0.45f, 0.0f, 0.08f, 0.90f, 12);

	// Foliage
	glColor3f(0.24f, 0.56f, 0.28f);
	drawCircleXY(0.0f, 1.05f, 0.0f, 0.38f, 16);
	drawCircleXY(-0.16f, 0.95f, 0.05f, 0.28f, 14);
	drawCircleXY( 0.16f, 0.95f, 0.05f, 0.28f, 14);
	drawCircleXY( 0.0f, 1.25f, 0.05f, 0.26f, 14);

	glColor3f(0.30f, 0.65f, 0.32f);
	drawCircleXY(0.05f, 1.10f, 0.08f, 0.24f, 12);

	glPopMatrix();
}

void drawRedKilla(void)
{
	// MAIN WALL - full width orange base
	glBegin(GL_QUADS);
	glColor3f(0.88f, 0.44f, 0.18f);
	glVertex3f(-1.00f, -0.85f, 0.0f);
	glVertex3f(1.00f, -0.85f, 0.0f);
	glVertex3f(1.00f, -0.10f, 0.0f);
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
	glVertex3f(0.42f, -0.85f, 0.0f);
	glVertex3f(0.42f, -0.10f, 0.0f);
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
	glVertex3f(0.46f, -0.10f, 0.0f);
	glVertex3f(0.46f, -0.07f, 0.0f);
	glVertex3f(-0.46f, -0.07f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.50f, 0.18f, 0.07f);
	glVertex3f(-0.46f, -0.74f, 0.0f);
	glVertex3f(0.46f, -0.74f, 0.0f);
	glVertex3f(0.46f, -0.68f, 0.0f);
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
	glVertex3f(0.86f, -0.48f, 0.0f);
	glVertex3f(0.96f, -0.48f, 0.0f);
	glVertex3f(0.96f, -0.35f, 0.0f);
	glVertex3f(0.86f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.86f, -0.35f, 0.0f);
	glVertex3f(0.96f, -0.35f, 0.0f);
	glVertex3f(0.91f, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.68f, -0.48f, 0.0f);
	glVertex3f(0.78f, -0.48f, 0.0f);
	glVertex3f(0.78f, -0.35f, 0.0f);
	glVertex3f(0.68f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.68f, -0.35f, 0.0f);
	glVertex3f(0.78f, -0.35f, 0.0f);
	glVertex3f(0.73f, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.50f, -0.48f, 0.0f);
	glVertex3f(0.60f, -0.48f, 0.0f);
	glVertex3f(0.60f, -0.35f, 0.0f);
	glVertex3f(0.50f, -0.35f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.50f, -0.35f, 0.0f);
	glVertex3f(0.60f, -0.35f, 0.0f);
	glVertex3f(0.55f, -0.25f, 0.0f);
	glEnd();

	// LARGE ARCHES - centre block
	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(-0.40f, -0.85f, 0.0f);
	glVertex3f(-0.22f, -0.85f, 0.0f);
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
	glVertex3f(-0.10f, -0.85f, 0.0f);
	glVertex3f(0.10f, -0.85f, 0.0f);
	glVertex3f(0.10f, -0.30f, 0.0f);
	glVertex3f(-0.10f, -0.30f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(-0.10f, -0.30f, 0.0f);
	glVertex3f(0.10f, -0.30f, 0.0f);
	glVertex3f(0.00f, -0.13f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.22f, -0.85f, 0.0f);
	glVertex3f(0.40f, -0.85f, 0.0f);
	glVertex3f(0.40f, -0.30f, 0.0f);
	glVertex3f(0.22f, -0.30f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.22f, -0.30f, 0.0f);
	glVertex3f(0.40f, -0.30f, 0.0f);
	glVertex3f(0.31f, -0.13f, 0.0f);
	glEnd();

	// INNER DOOR 1
	glBegin(GL_QUADS);
	glColor3f(0.25f, 0.08f, 0.03f);// Dark brown door
	glVertex3f(-0.38f, -0.83f, 0.01f);
	glVertex3f(-0.24f, -0.83f, 0.01f);
	glVertex3f(-0.24f, -0.32f, 0.01f);
	glVertex3f(-0.38f, -0.32f, 0.01f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.25f, 0.08f, 0.03f);
	glVertex3f(-0.38f, -0.32f, 0.01f);
	glVertex3f(-0.24f, -0.32f, 0.01f);
	glVertex3f(-0.31f, -0.17f, 0.01f);
	glEnd();

	glLineWidth(6.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.62f, 0.22f, 0.08f); // Door Line
	glVertex3f(-0.32f, -0.19f, 0.01f);
	glVertex3f(-0.32f, -0.83f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.62f, 0.22f, 0.08f); // Door Line
	glVertex3f(-0.3f, -0.19f, 0.01f);
	glVertex3f(-0.3f, -0.83f, 0.01f);
	glEnd();


	//Middle door inner part
	glBegin(GL_QUADS);
	glColor3f(0.25f, 0.08f, 0.03f); // Dark brown
	glVertex3f(-0.065f, -0.85f, 0.0f);
	glVertex3f(0.065f, -0.85f, 0.0f);
	glVertex3f(0.065f, -0.34f, 0.0f);
	glVertex3f(-0.065f, -0.34f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.25f, 0.08f, 0.03f);
	glVertex3f(-0.065f, -0.34f, 0.0f);
	glVertex3f(0.065f, -0.34f, 0.0f);
	glVertex3f(0.00f, -0.23f, 0.0f);
	glEnd();

	glLineWidth(6.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.62f, 0.22f, 0.08f); // Door Line
	glVertex3f(-0.01f, -0.25f, 0.01f);
	glVertex3f(-0.01f, -0.85f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.62f, 0.22f, 0.08f); // Door Line
	glVertex3f(0.01f, -0.25f, 0.01f);
	glVertex3f(0.01f, -0.85f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.83f, 0.60f, 0.20f); // 1st Door Handle
	glVertex3f(-0.34f, -0.47f, 0.01f);
	glVertex3f(-0.34f, -0.57f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.83f, 0.60f, 0.20f); // 1st Door Handle
	glVertex3f(-0.28f, -0.47f, 0.01f);
	glVertex3f(-0.28f, -0.57f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.83f, 0.60f, 0.20f); // 2nd Door Handle
	glVertex3f(-0.03f, -0.47f, 0.01f);
	glVertex3f(-0.03f, -0.57f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.83f, 0.60f, 0.20f); // 2nd Door Handle
	glVertex3f(0.03f, -0.47f, 0.01f);
	glVertex3f(0.03f, -0.57f, 0.01f);
	glEnd();

	

	//3rd door 
	glBegin(GL_QUADS);
	glColor3f(0.25f, 0.08f, 0.03f);

	glVertex3f(0.24f, -0.85f, 0.0f);
	glVertex3f(0.38f, -0.85f, 0.0f);
	glVertex3f(0.38f, -0.32f, 0.0f);
	glVertex3f(0.24f, -0.32f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.25f, 0.08f, 0.03f);
	glVertex3f(0.237f, -0.32f, 0.01f);
	glVertex3f(0.383f, -0.32f, 0.01f);
	glVertex3f(0.31f, -0.17f, 0.01f);
	glEnd();

	glLineWidth(6.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.62f, 0.22f, 0.08f); // Door Line
	glVertex3f(0.3f, -0.19f, 0.01f);
	glVertex3f(0.3f, -0.85f, 0.01f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.62f, 0.22f, 0.08f); // Door Line
	glVertex3f(0.32f, -0.19f, 0.01f);
	glVertex3f(0.32f, -0.85f, 0.01f);
	glEnd();

	glColor3f(0.83f, 0.60f, 0.20f);
	glLineWidth(6.0f);

	glBegin(GL_LINES);

	glVertex3f(0.28f, -0.47f, 0.02f);
	glVertex3f(0.28f, -0.57f, 0.02f);
	glVertex3f(0.34f, -0.47f, 0.02f);
	glVertex3f(0.34f, -0.57f, 0.02f);

	glEnd();


	// CENTRAL PAVILION BACK WALL
	glBegin(GL_QUADS);
	glColor3f(0.98f, 0.66f, 0.42f);
	glVertex3f(-0.36f, -0.07f, 0.0f);
	glVertex3f(0.36f, -0.07f, 0.0f);
	glVertex3f(0.36f, 0.22f, 0.0f);
	glVertex3f(-0.36f, 0.22f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(-0.36f, 0.20f, 0.0f);
	glVertex3f(0.36f, 0.20f, 0.0f);
	glVertex3f(0.36f, 0.22f, 0.0f);
	glVertex3f(-0.36f, 0.22f, 0.0f);
	glEnd();

	// CENTRAL PAVILION - 7 white arches
	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.33f, -0.07f, 0.0f);
	glVertex3f(-0.24f, -0.07f, 0.0f);
	glVertex3f(-0.24f, 0.12f, 0.0f);
	glVertex3f(-0.33f, 0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.33f, 0.12f, 0.0f);
	glVertex3f(-0.24f, 0.12f, 0.0f);
	glVertex3f(-0.285f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.22f, -0.07f, 0.0f);
	glVertex3f(-0.13f, -0.07f, 0.0f);
	glVertex3f(-0.13f, 0.12f, 0.0f);
	glVertex3f(-0.22f, 0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.22f, 0.12f, 0.0f);
	glVertex3f(-0.13f, 0.12f, 0.0f);
	glVertex3f(-0.180f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.11f, -0.07f, 0.0f);
	glVertex3f(-0.02f, -0.07f, 0.0f);
	glVertex3f(-0.02f, 0.12f, 0.0f);
	glVertex3f(-0.11f, 0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.11f, 0.12f, 0.0f);
	glVertex3f(-0.02f, 0.12f, 0.0f);
	glVertex3f(-0.070f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.02f, -0.07f, 0.0f);
	glVertex3f(0.11f, -0.07f, 0.0f);
	glVertex3f(0.11f, 0.12f, 0.0f);
	glVertex3f(0.02f, 0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.02f, 0.12f, 0.0f);
	glVertex3f(0.11f, 0.12f, 0.0f);
	glVertex3f(0.065f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.13f, -0.07f, 0.0f);
	glVertex3f(0.22f, -0.07f, 0.0f);
	glVertex3f(0.22f, 0.12f, 0.0f);
	glVertex3f(0.13f, 0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.13f, 0.12f, 0.0f);
	glVertex3f(0.22f, 0.12f, 0.0f);
	glVertex3f(0.175f, 0.20f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.24f, -0.07f, 0.0f);
	glVertex3f(0.33f, -0.07f, 0.0f);
	glVertex3f(0.33f, 0.12f, 0.0f);
	glVertex3f(0.24f, 0.12f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.24f, 0.12f, 0.0f);
	glVertex3f(0.33f, 0.12f, 0.0f);
	glVertex3f(0.285f, 0.20f, 0.0f);
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
			glVertex3f(cx[i], 0.42f, 0.0f);
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
	glVertex3f(-0.38f, 0.72f, 0.0f);
	glVertex3f(-0.44f, 0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.88f, 0.44f, 0.18f);
	glVertex3f(-0.42f, -0.10f, 0.0f);
	glVertex3f(-0.40f, -0.10f, 0.0f);
	glVertex3f(-0.40f, 0.72f, 0.0f);
	glVertex3f(-0.42f, 0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.95f, 0.55f, 0.28f);
	glVertex3f(0.38f, -0.10f, 0.0f);
	glVertex3f(0.44f, -0.10f, 0.0f);
	glVertex3f(0.44f, 0.72f, 0.0f);
	glVertex3f(0.38f, 0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.88f, 0.44f, 0.18f);
	glVertex3f(0.40f, -0.10f, 0.0f);
	glVertex3f(0.42f, -0.10f, 0.0f);
	glVertex3f(0.42f, 0.72f, 0.0f);
	glVertex3f(0.40f, 0.72f, 0.0f);
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
	glVertex3f(0.35f, 0.72f, 0.0f);
	glVertex3f(0.47f, 0.72f, 0.0f);
	glVertex3f(0.47f, 0.82f, 0.0f);
	glVertex3f(0.35f, 0.82f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.98f, 0.78f, 0.58f);
	glVertex3f(0.32f, 0.82f, 0.0f);
	glVertex3f(0.50f, 0.82f, 0.0f);
	glVertex3f(0.41f, 0.98f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.32f, 0.80f, 0.0f);
	glVertex3f(0.50f, 0.80f, 0.0f);
	glVertex3f(0.50f, 0.82f, 0.0f);
	glVertex3f(0.32f, 0.82f, 0.0f);
	glEnd();

	// LEFT CORNER PAVILION
	glBegin(GL_QUADS);
	glColor3f(0.98f, 0.66f, 0.42f);
	glVertex3f(-0.98f, 0.03f, 0.0f);
	glVertex3f(-0.48f, 0.03f, 0.0f);
	glVertex3f(-0.48f, 0.42f, 0.0f);
	glVertex3f(-0.98f, 0.42f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.95f, 0.05f, 0.0f);
	glVertex3f(-0.82f, 0.05f, 0.0f);
	glVertex3f(-0.82f, 0.27f, 0.0f);
	glVertex3f(-0.95f, 0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.95f, 0.27f, 0.0f);
	glVertex3f(-0.82f, 0.27f, 0.0f);
	glVertex3f(-0.885f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.80f, 0.05f, 0.0f);
	glVertex3f(-0.67f, 0.05f, 0.0f);
	glVertex3f(-0.67f, 0.27f, 0.0f);
	glVertex3f(-0.80f, 0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.80f, 0.27f, 0.0f);
	glVertex3f(-0.67f, 0.27f, 0.0f);
	glVertex3f(-0.735f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glVertex3f(-0.52f, 0.05f, 0.0f);
	glVertex3f(-0.52f, 0.27f, 0.0f);
	glVertex3f(-0.65f, 0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(-0.65f, 0.27f, 0.0f);
	glVertex3f(-0.52f, 0.27f, 0.0f);
	glVertex3f(-0.585f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(-0.98f, 0.40f, 0.0f);
	glVertex3f(-0.48f, 0.40f, 0.0f);
	glVertex3f(-0.48f, 0.42f, 0.0f);
	glVertex3f(-0.98f, 0.42f, 0.0f);
	glEnd();

	// RIGHT CORNER PAVILION
	glBegin(GL_QUADS);
	glColor3f(0.98f, 0.66f, 0.42f);
	glVertex3f(0.48f, 0.03f, 0.0f);
	glVertex3f(0.98f, 0.03f, 0.0f);
	glVertex3f(0.98f, 0.42f, 0.0f);
	glVertex3f(0.48f, 0.42f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.52f, 0.05f, 0.0f);
	glVertex3f(0.65f, 0.05f, 0.0f);
	glVertex3f(0.65f, 0.27f, 0.0f);
	glVertex3f(0.52f, 0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.52f, 0.27f, 0.0f);
	glVertex3f(0.65f, 0.27f, 0.0f);
	glVertex3f(0.585f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.67f, 0.05f, 0.0f);
	glVertex3f(0.80f, 0.05f, 0.0f);
	glVertex3f(0.80f, 0.27f, 0.0f);
	glVertex3f(0.67f, 0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.67f, 0.27f, 0.0f);
	glVertex3f(0.80f, 0.27f, 0.0f);
	glVertex3f(0.735f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.82f, 0.05f, 0.0f);
	glVertex3f(0.95f, 0.05f, 0.0f);
	glVertex3f(0.95f, 0.27f, 0.0f);
	glVertex3f(0.82f, 0.27f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.99f, 0.97f, 0.95f);
	glVertex3f(0.82f, 0.27f, 0.0f);
	glVertex3f(0.95f, 0.27f, 0.0f);
	glVertex3f(0.885f, 0.40f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.62f, 0.22f, 0.08f);
	glVertex3f(0.48f, 0.40f, 0.0f);
	glVertex3f(0.98f, 0.40f, 0.0f);
	glVertex3f(0.98f, 0.42f, 0.0f);
	glVertex3f(0.48f, 0.42f, 0.0f);
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
	glVertex3f(1.60f, -1.40f, 0.0f);
	glVertex3f(1.60f, -0.85f, 0.0f);
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
	glVertex3f(-1.18f, 0.25f, 0.0f);
	glVertex3f(-1.60f, 0.25f, 0.0f);
	glEnd();

	// Left wall - light accent strip (front face)
	glBegin(GL_QUADS);
	glColor3f(0.98f, 0.66f, 0.42f);
	glVertex3f(-1.60f, -0.85f, 0.0f);
	glVertex3f(-1.52f, -0.85f, 0.0f);
	glVertex3f(-1.52f, 0.25f, 0.0f);
	glVertex3f(-1.60f, 0.25f, 0.0f);
	glEnd();

	// Left wall - dark accent strip (inner face)
	glBegin(GL_QUADS);
	glColor3f(0.80f, 0.38f, 0.12f);
	glVertex3f(-1.18f, -0.85f, 0.0f);
	glVertex3f(-1.26f, -0.85f, 0.0f);
	glVertex3f(-1.26f, 0.25f, 0.0f);
	glVertex3f(-1.18f, 0.25f, 0.0f);
	glEnd();

	// Left wall - battlements top (5 merlons)
	{
		int m;
		for (m = 0; m < 5; m++)
		{
			float mx = -1.60f + (m * 0.085f);
			glBegin(GL_QUADS);
			glColor3f(0.88f, 0.44f, 0.18f);
			glVertex3f(mx, 0.25f, 0.0f);
			glVertex3f(mx + 0.06f, 0.25f, 0.0f);
			glVertex3f(mx + 0.06f, 0.35f, 0.0f);
			glVertex3f(mx, 0.35f, 0.0f);
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
	glVertex3f(1.18f, -0.85f, 0.0f);
	glVertex3f(1.60f, -0.85f, 0.0f);
	glVertex3f(1.60f, 0.25f, 0.0f);
	glVertex3f(1.18f, 0.25f, 0.0f);
	glEnd();

	// Right wall - light accent strip (front face)
	glBegin(GL_QUADS);
	glColor3f(0.98f, 0.66f, 0.42f);
	glVertex3f(1.52f, -0.85f, 0.0f);
	glVertex3f(1.60f, -0.85f, 0.0f);
	glVertex3f(1.60f, 0.25f, 0.0f);
	glVertex3f(1.52f, 0.25f, 0.0f);
	glEnd();

	// Right wall - dark accent strip (inner face)
	glBegin(GL_QUADS);
	glColor3f(0.80f, 0.38f, 0.12f);
	glVertex3f(1.18f, -0.85f, 0.0f);
	glVertex3f(1.26f, -0.85f, 0.0f);
	glVertex3f(1.26f, 0.25f, 0.0f);
	glVertex3f(1.18f, 0.25f, 0.0f);
	glEnd();

	// Right wall - battlements top (5 merlons)
	{
		int m;
		for (m = 0; m < 5; m++)
		{
			float mx = 1.18f + (m * 0.085f);
			glBegin(GL_QUADS);
			glColor3f(0.88f, 0.44f, 0.18f);
			glVertex3f(mx, 0.25f, 0.0f);
			glVertex3f(mx + 0.06f, 0.25f, 0.0f);
			glVertex3f(mx + 0.06f, 0.35f, 0.0f);
			glVertex3f(mx, 0.35f, 0.0f);
			glEnd();
		}
	}

	// Right wall - 2 arched windows
	// window 1
	glBegin(GL_POLYGON);
	glColor3f(0.65f, 0.28f, 0.08f);
	glVertex3f(1.38f, -0.60f, 0.0f);
	glVertex3f(1.56f, -0.60f, 0.0f);
	glVertex3f(1.56f, -0.30f, 0.0f);
	glVertex3f(1.47f, -0.18f, 0.0f);
	glVertex3f(1.38f, -0.30f, 0.0f);
	glEnd();

	// window 2
	glBegin(GL_POLYGON);
	glColor3f(0.65f, 0.28f, 0.08f);
	glVertex3f(1.38f, -0.80f, 0.0f);
	glVertex3f(1.56f, -0.80f, 0.0f);
	glVertex3f(1.56f, -0.68f, 0.0f);
	glVertex3f(1.47f, -0.62f, 0.0f);
	glVertex3f(1.38f, -0.68f, 0.0f);
	glEnd();

	// =========================================================
	// SANDY PLAIN GAP - right (between fort and right wall)
	// =========================================================
	glBegin(GL_QUADS);
	glColor3f(0.95f, 0.75f, 0.35f);
	glVertex3f(1.00f, -1.40f, 0.0f);
	glVertex3f(1.18f, -1.40f, 0.0f);
	glVertex3f(1.18f, -0.85f, 0.0f);
	glVertex3f(1.00f, -0.85f, 0.0f);
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
	glVertex3f(0.48f, -1.22f, 0.0f);
	glVertex3f(1.00f, -1.22f, 0.0f);
	glVertex3f(1.00f, -0.85f, 0.0f);
	glVertex3f(0.48f, -0.85f, 0.0f);
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
	glVertex3f(0.48f, -1.22f, 0.0f);
	glVertex3f(0.40f, -1.22f, 0.0f);
	glVertex3f(0.34f, -1.10f, 0.0f);
	glVertex3f(0.28f, -1.00f, 0.0f);
	glVertex3f(0.24f, -0.92f, 0.0f);
	glVertex3f(0.18f, -0.85f, 0.0f);
	glVertex3f(0.22f, -0.85f, 0.0f);
	glVertex3f(0.30f, -0.92f, 0.0f);
	glVertex3f(0.36f, -1.00f, 0.0f);
	glVertex3f(0.42f, -1.10f, 0.0f);
	glEnd();

	// =========================================================
	// TOP LANDING
	// =========================================================
	glBegin(GL_QUADS);
	glColor3f(0.80f, 0.66f, 0.48f);
	glVertex3f(-0.22f, -0.85f, 0.0f);
	glVertex3f(0.22f, -0.85f, 0.0f);
	glVertex3f(0.20f, -0.90f, 0.0f);
	glVertex3f(-0.20f, -0.90f, 0.0f);
	glEnd();

	// =========================================================
	// CENTER STAIRCASE - 10 thin widening steps
	// =========================================================
	{
		float topY = -0.90f;
		float stepH = 0.035f;
		float leftX = -0.18f;
		float rightX = 0.18f;
		float expand = 0.014f;
		int i;

		for (i = 0; i < 10; i++)
		{
			float y1 = topY - (i * stepH);
			float y2 = y1 - stepH + 0.003f;
			float lx1 = leftX - (i * expand);
			float rx1 = rightX + (i * expand);
			float lx2 = leftX - ((i + 1) * expand);
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
}


// ============================================================================
// SKY AND CLOUDS
// ============================================================================
void drawSkyAndClouds(void)
{
	glDisable(GL_DEPTH_TEST);

	// Sky Backdrop Quad
	glBegin(GL_QUADS);
	glColor3f(0.35f, 0.65f, 0.94f);
	glVertex3f(-35.0f,  20.0f, -6.0f);
	glVertex3f( 35.0f,  20.0f, -6.0f);
	glColor3f(0.72f, 0.86f, 0.98f);
	glVertex3f( 35.0f,  -1.0f, -6.0f);
	glVertex3f(-35.0f,  -1.0f, -6.0f);
	glEnd();

	// Clouds
	glColor3f(0.98f, 0.98f, 1.0f);
	drawCircleXY(-6.5f, 5.2f, -5.5f, 0.95f, 20);
	drawCircleXY(-5.6f, 5.5f, -5.5f, 1.15f, 20);
	drawCircleXY(-4.6f, 5.25f, -5.5f, 0.85f, 20);
	drawCircleXY(-5.4f, 4.7f, -5.5f, 0.90f, 20);

	drawCircleXY(-2.0f, 5.8f, -5.5f, 0.50f, 16);
	drawCircleXY(-1.5f, 5.9f, -5.5f, 0.60f, 16);
	drawCircleXY(-1.0f, 5.75f, -5.5f, 0.45f, 16);

	drawCircleXY(4.8f, 5.3f, -5.5f, 0.90f, 20);
	drawCircleXY(5.8f, 5.6f, -5.5f, 1.10f, 20);
	drawCircleXY(6.7f, 5.35f, -5.5f, 0.85f, 20);
	drawCircleXY(5.6f, 4.8f, -5.5f, 0.85f, 20);

	drawCircleXY(8.8f, 5.1f, -5.5f, 0.60f, 16);
	drawCircleXY(9.5f, 5.3f, -5.5f, 0.70f, 16);

	glEnable(GL_DEPTH_TEST);
}

// ============================================================================
// GROUND
// ============================================================================
void drawGround(void)
{
	glBegin(GL_QUADS);
	glColor3f(0.93f, 0.73f, 0.44f);
	glVertex3f(-30.0f, -0.70f, -3.0f);
	glVertex3f( 30.0f, -0.70f, -3.0f);
	glVertex3f( 30.0f, -0.70f,  14.0f);
	glVertex3f(-30.0f, -0.70f,  14.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.90f, 0.69f, 0.40f);
	glVertex3f(-30.0f, -0.699f, 6.0f);
	glVertex3f( 30.0f, -0.699f, 6.0f);
	glColor3f(0.94f, 0.75f, 0.46f);
	glVertex3f( 30.0f, -0.699f, 14.0f);
	glVertex3f(-30.0f, -0.699f, 14.0f);
	glEnd();
}

// ============================================================================
// ELEVATED PLINTH & GRAND 3D STAIRCASE
// ============================================================================
void drawPlinthAndGrandStairs(void)
{
	int t;
	float tierW = 16.5f;
	float tierH = 0.20f;
	float tierZ = -0.30f;

	// 5 Stepped tiers from Y = -0.70f up to Y = 0.30f
	for (t = 0; t < 5; t++)
	{
		float yBot = -0.70f + (t * tierH);
		float yTop = yBot + tierH;
		float curW = tierW - (t * 0.20f);
		float curZ = tierZ + (t * 0.06f);

		// Front Face
		glBegin(GL_QUADS);
		if (t % 2 == 0)
			glColor3f(0.70f, 0.58f, 0.44f);
		else
			glColor3f(0.64f, 0.52f, 0.38f);

		glVertex3f(-curW * 0.5f, yBot, curZ);
		glVertex3f( curW * 0.5f, yBot, curZ);
		glVertex3f( curW * 0.5f, yTop, curZ);
		glVertex3f(-curW * 0.5f, yTop, curZ);
		glEnd();

		// Divider line
		glBegin(GL_LINES);
		glColor3f(0.48f, 0.38f, 0.26f);
		glVertex3f(-curW * 0.5f, yTop, curZ + 0.005f);
		glVertex3f( curW * 0.5f, yTop, curZ + 0.005f);
		glEnd();

		// Top tread
		glBegin(GL_QUADS);
		glColor3f(0.76f, 0.64f, 0.48f);
		glVertex3f(-curW * 0.5f, yTop, curZ);
		glVertex3f( curW * 0.5f, yTop, curZ);
		glVertex3f( curW * 0.5f, yTop, curZ - 0.40f);
		glVertex3f(-curW * 0.5f, yTop, curZ - 0.40f);
		glEnd();
	}

	// Entrance Terrace Landing supporting the gate and pillars
	glBegin(GL_QUADS);
	glColor3f(0.76f, 0.64f, 0.48f);
	glVertex3f(-4.0f, 0.30f,  0.25f);
	glVertex3f( 4.0f, 0.30f,  0.25f);
	glVertex3f( 4.0f, 0.30f, -0.40f);
	glVertex3f(-4.0f, 0.30f, -0.40f);
	glEnd();

	// Grand Central Staircase descending from Y=0.30f down to Y=-0.70f
	{
		int s;
		int numSteps = 16;
		float startY = 0.30f;
		float endY = -0.70f;
		float startZ = 0.25f;
		float endZ = 1.95f;
		float stairWidthTop = 1.40f;
		float stairWidthBot = 2.40f;

		for (s = 0; s < numSteps; s++)
		{
			float frac1 = (float)s / (float)numSteps;
			float frac2 = (float)(s + 1) / (float)numSteps;

			float y1 = startY - frac1 * (startY - endY);
			float y2 = startY - frac2 * (startY - endY);

			float z1 = startZ + frac1 * (endZ - startZ);
			float z2 = startZ + frac2 * (endZ - startZ);

			float w1 = stairWidthTop + frac1 * (stairWidthBot - stairWidthTop);
			float w2 = stairWidthTop + frac2 * (stairWidthBot - stairWidthTop);

			float hw1 = w1 * 0.5f;
			float hw2 = w2 * 0.5f;

			// Step Top Tread
			glBegin(GL_QUADS);
			if (s % 2 == 0)
				glColor3f(0.82f, 0.70f, 0.52f);
			else
				glColor3f(0.76f, 0.64f, 0.46f);

			glVertex3f(-hw1, y1, z1);
			glVertex3f( hw1, y1, z1);
			glVertex3f( hw2, y1, z2);
			glVertex3f(-hw2, y1, z2);
			glEnd();

			// Step Riser
			glBegin(GL_QUADS);
			glColor3f(0.60f, 0.48f, 0.34f);
			glVertex3f(-hw2, y2, z2);
			glVertex3f( hw2, y2, z2);
			glVertex3f( hw2, y1, z2);
			glVertex3f(-hw2, y1, z2);
			glEnd();

			// Edge line
			glBegin(GL_LINES);
			glColor3f(0.44f, 0.32f, 0.20f);
			glVertex3f(-hw2, y1, z2);
			glVertex3f( hw2, y1, z2);
			glEnd();
		}

		// Left & Right Cheek Walls
		glBegin(GL_QUADS);
		glColor3f(0.68f, 0.55f, 0.40f);
		glVertex3f(-stairWidthBot * 0.5f - 0.16f, -0.70f, endZ + 0.05f);
		glVertex3f(-stairWidthTop * 0.5f - 0.16f,  0.30f, startZ);
		glVertex3f(-stairWidthTop * 0.5f - 0.16f,  0.46f, startZ);
		glVertex3f(-stairWidthBot * 0.5f - 0.16f, -0.48f, endZ + 0.05f);

		glColor3f(0.80f, 0.68f, 0.50f);
		glVertex3f(-stairWidthBot * 0.5f - 0.16f, -0.48f, endZ + 0.05f);
		glVertex3f(-stairWidthTop * 0.5f - 0.16f,  0.46f, startZ);
		glVertex3f(-stairWidthTop * 0.5f,          0.46f, startZ);
		glVertex3f(-stairWidthBot * 0.5f,         -0.48f, endZ + 0.05f);

		glColor3f(0.68f, 0.55f, 0.40f);
		glVertex3f( stairWidthBot * 0.5f + 0.16f, -0.70f, endZ + 0.05f);
		glVertex3f( stairWidthTop * 0.5f + 0.16f,  0.30f, startZ);
		glVertex3f( stairWidthTop * 0.5f + 0.16f,  0.46f, startZ);
		glVertex3f( stairWidthBot * 0.5f + 0.16f, -0.48f, endZ + 0.05f);

		glColor3f(0.80f, 0.68f, 0.50f);
		glVertex3f( stairWidthBot * 0.5f + 0.16f, -0.48f, endZ + 0.05f);
		glVertex3f( stairWidthTop * 0.5f + 0.16f,  0.46f, startZ);
		glVertex3f( stairWidthTop * 0.5f,          0.46f, startZ);
		glVertex3f( stairWidthBot * 0.5f,         -0.48f, endZ + 0.05f);
		glEnd();
	}
}

void drawFortAndDetails(float elapsedTime)
{
	float eyeX = 0.0f;
	float eyeY = 1.65f;
	float eyeZ = 6.50f;
	float centerX = 0.0f;
	float centerY = 1.25f;
	float centerZ = 0.0f;

	// First 2 seconds (28.0f to 30.0f): static wide view
	// Next 3 seconds (30.0f to 33.0f): smooth zoom into center door
	if (elapsedTime > 30.0f)
	{
		float t = (elapsedTime - 30.0f) / 3.0f; 
		if (t > 1.0f)
			t = 1.0f;

		// Smoothstep easing for cinematic ease-in/ease-out
		float smoothT = t * t * (3.0f - 2.0f * t);

		eyeZ    = 6.50f + (0.5f - 6.50f) * smoothT;
		eyeY    = 1.65f + (1.10f - 1.65f) * smoothT;
		centerY = 1.25f + (1.05f - 1.25f) * smoothT;
	}

	gluLookAt(eyeX, eyeY, eyeZ,centerX, centerY, centerZ,0.0f, 1.0f, 0.0f);

	// 1. Sky and Clouds
	drawSkyAndClouds();

	// 2. Ground
	drawGround();

	// 3. Red Fort
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.0f, 2.34f, -0.20f);
	glScalef(4.10f, 2.40f, 1.0f);
	drawRedKilla();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	// 4. Stepped Stone Plinth and Grand 3D Central Staircase
	drawPlinthAndGrandStairs();

	// 5. Flanking Trees
	drawTree(-6.2f, -0.70f, 0.2f, 1.3f);
	drawTree(-5.4f, -0.70f, -0.4f, 1.1f);
	drawTree(6.2f, -0.70f, 0.2f, 1.3f);
	drawTree(5.4f, -0.70f, -0.4f, 1.1f);

	// 6. Elephant Cart on sand ground
	drawElephantCart(-3.20f, -0.70f, 2.60f, 0.70f, 175.0f);

	// 7. Elephant Pillars at the Central Entrance Gate Porch
	drawElephantPillar(-0.78f, 0.30f, -0.05f, 0.28f, 20.0f);
	drawElephantPillar(0.78f, 0.30f, -0.05f, 0.28f, -20.0f);

	// Connecting Entablature Beam across pillars into fort architrave
	glColor3f(0.62f, 0.22f, 0.08f);
	drawBox3D(0.0f, 2.16f, -0.05f, 2.05f, 0.12f, 0.40f);
	glColor3f(0.88f, 0.44f, 0.18f);
	drawBox3D(0.0f, 2.08f, -0.05f, 1.90f, 0.06f, 0.36f);

	// 8. Guards
	// Guards at foot of the Grand Staircase
	drawSoldier(-1.45f, -0.70f, 1.95f, 0.28f, 0.88f, 0.20f, 0.18f, 0.95f, 0.75f, 0.20f, 1, 25.0f);
	drawSoldier(1.45f, -0.70f, 1.95f, 0.28f, 0.88f, 0.20f, 0.18f, 0.95f, 0.75f, 0.20f, 1, -25.0f);

	// Guards on middle steps
	drawSoldier(-1.08f, -0.20f, 1.05f, 0.25f, 0.20f, 0.35f, 0.82f, 0.90f, 0.45f, 0.15f, 1, 20.0f);
	drawSoldier(1.08f, -0.20f, 1.05f, 0.25f, 0.20f, 0.35f, 0.82f, 0.90f, 0.45f, 0.15f, 1, -20.0f);

	// Guards on entrance landing next to elephant pillars
	drawSoldier(-1.18f, 0.30f, -0.05f, 0.24f, 0.85f, 0.50f, 0.15f, 0.85f, 0.15f, 0.20f, 1, 15.0f);
	drawSoldier(1.18f, 0.30f, -0.05f, 0.24f, 0.85f, 0.50f, 0.15f, 0.85f, 0.15f, 0.20f, 1, -15.0f);

	// Guards on side terrace wings
	drawSoldier(-3.20f, 0.30f, -0.10f, 0.23f, 0.80f, 0.15f, 0.20f, 0.20f, 0.60f, 0.30f, 1, 10.0f);
	drawSoldier(3.20f, 0.30f, -0.10f, 0.23f, 0.80f, 0.15f, 0.20f, 0.20f, 0.60f, 0.30f, 1, -10.0f);

	drawSoldier(-5.20f, 0.30f, -0.10f, 0.22f, 0.90f, 0.45f, 0.15f, 0.18f, 0.60f, 0.25f, 1, 10.0f);
	drawSoldier(5.20f, 0.30f, -0.10f, 0.22f, 0.90f, 0.45f, 0.15f, 0.18f, 0.60f, 0.25f, 1, -10.0f);

	// Courtyard sentries
	drawSoldier(-2.60f, -0.70f, 3.20f, 0.32f, 0.20f, 0.55f, 0.25f, 0.90f, 0.75f, 0.20f, 0, 40.0f);
	drawSoldier(2.60f, -0.70f, 3.20f, 0.32f, 0.20f, 0.55f, 0.25f, 0.90f, 0.75f, 0.20f, 0, -40.0f);

	drawSoldier(0.00f, -0.70f, 3.60f, 0.34f, 0.88f, 0.60f, 0.15f, 0.75f, 0.15f, 0.20f, 0, 180.0f);
}

