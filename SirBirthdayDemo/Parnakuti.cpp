#include <windows.h>
#include <math.h>

#include <gl/GL.h>

#pragma comment(lib, "opengl32.lib")

#include "Parnakuti.h"

#define TWO_PI 6.2831855f

static void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
		glVertex3f(x4, y4, 0.0f);
	glEnd();
}

static void drawRect(float x, float y, float w, float h)
{
	drawQuad(x, y, x + w, y, x + w, y + h, x, y + h);
}

static void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
	glEnd();
}

static void drawOval(float cx, float cy, float rx, float ry)
{
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(cx, cy, 0.0f);
		for (int i = 0; i <= 36; i++)
		{
			float angle = TWO_PI * i / 36.0f;
			glVertex3f(cx + rx * cosf(angle), cy + ry * sinf(angle), 0.0f);
		}
	glEnd();
}

static void drawLimb(float x1, float y1, float x2, float y2, float w1, float w2)
{
	float dx = x2 - x1, dy = y2 - y1;
	float len = sqrtf(dx * dx + dy * dy);
	float nx = -dy / len * 0.5f, ny = dx / len * 0.5f;

	drawQuad(x1 + nx * w1, y1 + ny * w1, x1 - nx * w1, y1 - ny * w1,
	         x2 - nx * w2, y2 - ny * w2, x2 + nx * w2, y2 + ny * w2);
	drawOval(x1, y1, w1 / 2.0f, w1 / 2.0f);
	drawOval(x2, y2, w2 / 2.0f, w2 / 2.0f);
}

static void drawGradient(float x, float y, float w, float h,
                         float r1, float g1, float b1, float r2, float g2, float b2)
{
	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1); glVertex3f(x,     y,     0.0f);
		glColor3f(r1, g1, b1); glVertex3f(x + w, y,     0.0f);
		glColor3f(r2, g2, b2); glVertex3f(x + w, y + h, 0.0f);
		glColor3f(r2, g2, b2); glVertex3f(x,     y + h, 0.0f);
	glEnd();
}

static void drawShadow(float x, float y, float rx, float ry, float alpha)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.0f, alpha);
	drawOval(x, y, rx, ry);
	glDisable(GL_BLEND);
}

static void drawGlow(float x, float y, float rx, float ry, float r, float g, float b, float alpha)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 1; i <= 8; i++)
	{
		glColor4f(r, g, b, alpha / 8.0f);
		drawOval(x, y, rx * i / 8.0f, ry * i / 8.0f);
	}
	glDisable(GL_BLEND);
}

static void rotateAbout(float px, float py, float angle)
{
	glTranslatef(px, py, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-px, -py, 0.0f);
}

static void drawSky(void)
{
	drawGradient(-300.0f, -300.0f, 2200.0f, 1600.0f, 0.20f, 0.16f, 0.28f, 0.03f, 0.04f, 0.15f);

	glColor3f(0.9f, 0.92f, 1.0f);
	for (int i = 0; i < 40; i++)
		drawRect(-200.0f + fmodf(i * 193.0f, 1900.0f), 480.0f + fmodf(i * 137.0f, 640.0f), 3.0f, 3.0f);

	drawGlow(1040.0f, 810.0f, 110.0f, 110.0f, 1.0f, 0.95f, 0.8f, 0.30f);
	glColor3f(0.98f, 0.95f, 0.82f);
	drawOval(1040.0f, 810.0f, 52.0f, 52.0f);
}

static void drawHills(void)
{
	glColor3f(0.10f, 0.14f, 0.30f); drawOval(300.0f, 420.0f, 520.0f, 160.0f);
	glColor3f(0.09f, 0.12f, 0.27f); drawOval(1250.0f, 420.0f, 600.0f, 200.0f);
	glColor3f(0.07f, 0.20f, 0.22f); drawOval(800.0f, 415.0f, 460.0f, 95.0f);
}

static void drawGround(void)
{

	drawGradient(-300.0f, -300.0f, 2200.0f, 715.0f, 0.04f, 0.13f, 0.11f, 0.11f, 0.28f, 0.22f);

	glBegin(GL_QUADS);
		glColor3f(0.17f, 0.17f, 0.23f); glVertex3f(171.0f,  -300.0f, 0.0f);
		glColor3f(0.17f, 0.17f, 0.23f); glVertex3f(1429.0f, -300.0f, 0.0f);
		glColor3f(0.43f, 0.41f, 0.50f); glVertex3f(835.0f,   415.0f, 0.0f);
		glColor3f(0.43f, 0.41f, 0.50f); glVertex3f(765.0f,   415.0f, 0.0f);
	glEnd();

	glColor3f(0.13f, 0.13f, 0.19f);
	drawLimb(171.0f, -300.0f, 765.0f, 415.0f, 6.0f, 3.0f);
	drawLimb(1429.0f, -300.0f, 835.0f, 415.0f, 6.0f, 3.0f);
}

static void drawHut(void)
{

	glColor3f(0.42f, 0.28f, 0.18f); drawRect(650.0f, 410.0f, 300.0f, 115.0f);
	glColor3f(0.32f, 0.21f, 0.13f); drawRect(650.0f, 410.0f, 300.0f, 16.0f);

	glColor3f(0.56f, 0.41f, 0.17f); drawTriangle(612.0f, 520.0f, 988.0f, 520.0f, 800.0f, 735.0f);
	glColor3f(0.42f, 0.30f, 0.11f);
	for (int i = 1; i < 6; i++)
	{
		float y = 520.0f + i * 42.0f;
		float half = 188.0f * (1.0f - (y - 520.0f) / 215.0f);
		drawRect(800.0f - half, y, 2.0f * half, 7.0f);
	}
	glColor3f(0.30f, 0.21f, 0.09f); drawRect(606.0f, 512.0f, 388.0f, 14.0f);

	glColor3f(0.12f, 0.07f, 0.05f); drawRect(762.0f, 410.0f, 76.0f, 102.0f);
	glColor3f(0.91f, 0.62f, 0.23f); drawRect(771.0f, 410.0f, 58.0f, 92.0f);
	glColor3f(0.91f, 0.77f, 0.45f); drawOval(800.0f, 440.0f, 16.0f, 26.0f);

	drawGlow(800.0f, 455.0f, 230.0f, 170.0f, 1.0f, 0.65f, 0.25f, 0.30f);
	drawGlow(800.0f, 372.0f, 300.0f,  70.0f, 1.0f, 0.70f, 0.30f, 0.28f);
}

static void drawTree(float x, float y, float s)
{
	static const float lobes[7][3] = {
		{ -150.0f, 470.0f, 150.0f }, { 150.0f, 480.0f, 155.0f }, { 0.0f, 560.0f, 170.0f },
		{  -70.0f, 410.0f, 120.0f }, {  80.0f, 420.0f, 125.0f }, { -190.0f, 560.0f, 110.0f },
		{  190.0f, 570.0f, 115.0f }
	};
	static const float tones[3][7] = {
		{   0.0f,  0.0f, 1.00f, 0.88f, 0.04f, 0.17f, 0.12f },
		{ -14.0f, 16.0f, 0.78f, 0.68f, 0.07f, 0.26f, 0.18f },
		{  26.0f, 44.0f, 0.45f, 0.34f, 0.11f, 0.35f, 0.24f }
	};

	drawShadow(x + 30.0f * s, y - 6.0f * s, 190.0f * s, 26.0f * s, 0.30f);

	glColor3f(0.20f, 0.12f, 0.07f);
	drawQuad(x - 62.0f * s, y, x + 62.0f * s, y, x + 46.0f * s, y + 340.0f * s, x - 46.0f * s, y + 340.0f * s);
	drawTriangle(x - 95.0f * s, y - 6.0f * s, x - 30.0f * s, y + 10.0f * s, x - 45.0f * s, y + 120.0f * s);
	drawTriangle(x + 95.0f * s, y - 6.0f * s, x + 30.0f * s, y + 10.0f * s, x + 45.0f * s, y + 120.0f * s);
	glColor3f(0.30f, 0.19f, 0.11f);
	drawQuad(x + 14.0f * s, y, x + 62.0f * s, y, x + 46.0f * s, y + 340.0f * s, x + 10.0f * s, y + 340.0f * s);

	glColor3f(0.22f, 0.14f, 0.08f);
	drawLimb(x - 20.0f * s, y + 300.0f * s, x - 150.0f * s, y + 400.0f * s, 46.0f * s, 22.0f * s);
	drawLimb(x + 20.0f * s, y + 300.0f * s, x + 150.0f * s, y + 410.0f * s, 46.0f * s, 22.0f * s);

	for (int tone = 0; tone < 3; tone++)
	{
		glColor3f(tones[tone][4], tones[tone][5], tones[tone][6]);
		for (int i = 0; i < 7; i++)
			drawOval(x + (lobes[i][0] + tones[tone][0]) * s, y + (lobes[i][1] + tones[tone][1]) * s,
			         lobes[i][2] * tones[tone][2] * s, lobes[i][2] * tones[tone][3] * s);
	}
}

static void drawTrees(void)
{
	drawTree(1140.0f, 385.0f, 0.50f);
	drawTree(235.0f,  235.0f, 1.00f);
	drawTree(1385.0f, 215.0f, 1.05f);
}

static void drawChanakya(void)
{

	glColor3f(0.20f, 0.13f, 0.09f);
	drawOval(-40.0f, 22.0f, 30.0f, 12.0f);
	drawOval( 38.0f,  4.0f, 30.0f, 12.0f);
	glColor3f(0.80f, 0.46f, 0.10f); drawQuad(-72.0f, 26.0f, 72.0f, 10.0f, 58.0f, 262.0f, -58.0f, 262.0f);
	glColor3f(0.62f, 0.34f, 0.07f);
	drawTriangle(-14.0f, 24.0f, 4.0f, 20.0f, -6.0f, 236.0f);
	drawTriangle( 26.0f, 14.0f, 44.0f, 12.0f, 34.0f, 206.0f);

	glPushMatrix();
	rotateAbout(0.0f, 250.0f, -4.0f);

		glColor3f(0.78f, 0.52f, 0.36f);
		drawQuad(-58.0f, 250.0f, 58.0f, 250.0f, 72.0f, 372.0f, -72.0f, 372.0f);
		drawOval(-72.0f, 362.0f, 24.0f, 22.0f);
		drawOval( 72.0f, 362.0f, 24.0f, 22.0f);
		drawRect(-17.0f, 368.0f, 34.0f, 30.0f);

		drawLimb(-100.0f, 336.0f, -134.0f, 314.0f, 26.0f, 19.0f);

		glPushMatrix();
		rotateAbout(0.0f, 398.0f, -7.0f);
			drawOval(-43.0f, 428.0f, 11.0f, 15.0f);
			drawOval( 41.0f, 428.0f,  5.0f, 11.0f);
			drawOval(0.0f, 428.0f, 43.0f, 47.0f);
		glPopMatrix();

		glColor3f(0.05f, 0.03f, 0.03f);
		drawQuad(-10.0f, 466.0f, 10.0f, 466.0f, 4.0f, 322.0f, -16.0f, 322.0f);
		drawTriangle(-16.0f, 322.0f, 4.0f, 322.0f, -8.0f, 290.0f);
		drawOval(0.0f, 470.0f, 13.0f, 12.0f);

		glColor3f(0.93f, 0.56f, 0.12f);
		drawQuad(-100.0f, 376.0f, 18.0f, 376.0f, 30.0f, 230.0f, -96.0f, 240.0f);
		drawQuad(-96.0f, 240.0f, 30.0f, 230.0f, 12.0f, 112.0f, -84.0f, 104.0f);
		drawOval(-76.0f, 366.0f, 34.0f, 28.0f);
		glColor3f(0.74f, 0.40f, 0.07f);
		drawQuad(-72.0f, 372.0f, -62.0f, 372.0f, -58.0f, 108.0f, -68.0f, 106.0f);
		drawQuad(-42.0f, 374.0f, -33.0f, 374.0f, -31.0f, 108.0f, -40.0f, 108.0f);
		drawQuad(-10.0f, 372.0f,  -2.0f, 372.0f,   0.0f, 110.0f,  -8.0f, 110.0f);
		glColor3f(0.45f, 0.22f, 0.05f);
		drawQuad(-86.0f, 104.0f, 12.0f, 112.0f, 12.0f, 128.0f, -88.0f, 120.0f);

	glPopMatrix();

	glColor3f(0.78f, 0.52f, 0.36f);
	drawLimb(77.0f, 347.0f, 96.0f, 282.0f, 30.0f, 26.0f);
	drawLimb(96.0f, 282.0f, 106.0f, 198.0f, 28.0f, 22.0f);
	drawOval(106.0f, 196.0f, 15.0f, 15.0f);
	glColor3f(0.12f, 0.08f, 0.05f);
	drawLimb(72.0f, 314.0f, 96.0f, 321.0f, 7.0f, 7.0f);

	glColor3f(0.28f, 0.17f, 0.09f); drawLimb(-152.0f, -30.0f, -140.0f, 440.0f, 14.0f, 11.0f);
	glColor3f(0.42f, 0.27f, 0.14f); drawLimb(-148.0f, -30.0f, -136.0f, 440.0f,  4.0f,  3.0f);
	glColor3f(0.78f, 0.52f, 0.36f); drawOval(-140.0f, 318.0f, 14.0f, 17.0f);
}

static void drawChandragupta(void)
{

	glColor3f(0.42f, 0.28f, 0.18f);
	drawOval(-26.0f, 12.0f, 20.0f, 9.0f);
	drawOval( 26.0f, -2.0f, 20.0f, 9.0f);
	glColor3f(0.93f, 0.90f, 0.80f); drawQuad(-50.0f, 20.0f, 50.0f, 6.0f, 42.0f, 150.0f, -42.0f, 150.0f);
	glColor3f(0.80f, 0.76f, 0.66f); drawTriangle(-6.0f, 16.0f, 10.0f, 12.0f, 2.0f, 132.0f);

	glPushMatrix();
	rotateAbout(0.0f, 142.0f, 5.0f);

		glColor3f(0.74f, 0.50f, 0.35f);
		drawQuad(-42.0f, 142.0f, 42.0f, 142.0f, 50.0f, 222.0f, -50.0f, 222.0f);
		drawOval(-50.0f, 214.0f, 16.0f, 14.0f);
		drawOval( 50.0f, 214.0f, 16.0f, 14.0f);
		drawRect(-11.0f, 220.0f, 22.0f, 22.0f);

		glColor3f(0.96f, 0.93f, 0.84f);
		drawQuad(-52.0f, 226.0f, -14.0f, 226.0f, 52.0f, 128.0f, 18.0f, 112.0f);
		glColor3f(0.55f, 0.35f, 0.15f);
		drawLimb(-33.0f, 226.0f, 35.0f, 120.0f, 5.0f, 5.0f);

		glColor3f(0.74f, 0.50f, 0.35f);
		drawLimb(50.0f, 212.0f, 62.0f, 160.0f, 20.0f, 16.0f);
		drawLimb(62.0f, 160.0f, 72.0f, 116.0f, 16.0f, 13.0f);
		drawOval(73.0f, 108.0f, 11.0f, 11.0f);

		glPushMatrix();
		rotateAbout(0.0f, 242.0f, 10.0f);
			glColor3f(0.74f, 0.50f, 0.35f);
			drawOval(-31.0f, 262.0f, 8.0f, 12.0f);
			drawOval(-26.0f, 248.0f, 10.0f, 8.0f);
			drawOval( 30.0f, 262.0f, 5.0f, 9.0f);
			glColor3f(0.07f, 0.05f, 0.04f);
			drawOval(0.0f, 266.0f, 31.0f, 33.0f);
			drawOval(0.0f, 303.0f, 13.0f, 13.0f);
		glPopMatrix();

	glPopMatrix();
}

static void drawFigures(void)
{
	glPushMatrix();
	glTranslatef(623.19f, 155.29f, 0.0f);
	glScalef(0.9218f, 0.9218f, 1.0f);

		drawShadow(0.0f,   4.0f, 100.0f, 16.0f, 0.35f);
		drawShadow(245.0f, 4.0f,  72.0f, 12.0f, 0.35f);

		drawChanakya();

		glPushMatrix();
		glTranslatef(245.0f, 4.0f, 0.0f);
		drawChandragupta();
		glPopMatrix();

		glColor3f(0.74f, 0.50f, 0.35f);
		drawLimb(189.0f, 213.0f, 106.0f, 196.0f, 26.0f, 20.0f);
		glColor3f(0.78f, 0.52f, 0.36f);
		drawOval(106.0f, 196.0f, 13.0f, 13.0f);

	glPopMatrix();
}

static void drawLayer(float z, void (*layer)(void))
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, z);
	layer();
	glPopMatrix();
}

void displayParnakuti(void)
{
	glPushMatrix();

	glScalef(0.002f, 0.002f, 1.0f);
	glTranslatef(-800.0f, -450.0f, 0.0f);

	drawLayer(-0.10f, drawSky);
	drawLayer(-0.08f, drawHills);
	drawLayer(-0.06f, drawGround);
	drawLayer(-0.04f, drawHut);
	drawLayer(-0.02f, drawTrees);
	drawLayer( 0.00f, drawFigures);

	glPopMatrix();
}
