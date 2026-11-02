// header files

#include <windows.h>
#include <stdio.h>
#include <stdlib.h> // FOR EXIT()

// OpenGL Related Files
#include <gl/GL.h>
#include <gl/glu.h>

// Link With OpenGL Import Library
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "GLU32.lib")

extern GLuint texture_background;

void IgnitedBy(void)
{
	// Background textured quad
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_background);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -1.5f, -0.3f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -1.5f, -0.3f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, 1.5f, -0.3f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, 1.5f, -0.3f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	// First Line: "Ignited By" (इग्नाइटेड बाय)
	glLineWidth(7.0f);

	glPushMatrix();
	glTranslatef(0.55f, 0.2f, 0.0f);
	glScalef(1.7f, 2.2f, 1.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.12f, 0.0f);
	glScalef(1.2f, 1.2f, 1.0f);

	glBegin(GL_LINES);
	glColor3f(0.50f, 0.0f, 0.0f);

	// Ignited (इग्नाइटेड)
	//1
	glVertex3f(-0.55f, 0.20f, 0.0f);
	glVertex3f(-0.55f, 0.18f, 0.0f);
	glVertex3f(-0.55f, 0.18f, 0.0f);
	glVertex3f(-0.60f, 0.18f, 0.0f);

	// 2
	glVertex3f(-0.60f, 0.18f, 0.0f);
	glVertex3f(-0.60f, 0.14f, 0.0f);
	glVertex3f(-0.60f, 0.14f, 0.0f);
	glVertex3f(-0.55f, 0.14f, 0.0f);

	//3
	glVertex3f(-0.55f, 0.14f, 0.0f);
	glVertex3f(-0.55f, 0.10f, 0.0f);
	glVertex3f(-0.55f, 0.10f, 0.0f);
	glVertex3f(-0.60f, 0.10f, 0.0f);

	//4
	glVertex3f(-0.60f, 0.11f, 0.0f);
	glVertex3f(-0.58f, 0.08f, 0.0f);
	glVertex3f(-0.50f, 0.20f, 0.0f);
	glVertex3f(-0.50f, 0.13f, 0.0f);

	//5
	glVertex3f(-0.50f, 0.13f, 0.0f);
	glVertex3f(-0.53f, 0.13f, 0.0f);
	glVertex3f(-0.53f, 0.13f, 0.0f);
	glVertex3f(-0.53f, 0.16f, 0.0f);

	// 6
	glVertex3f(-0.53f, 0.16f, 0.0f);
	glVertex3f(-0.50f, 0.16f, 0.0f);
	glVertex3f(-0.43f, 0.10f, 0.0f);
	glVertex3f(-0.43f, 0.20f, 0.0f);

	//7
	glVertex3f(-0.43f, 0.16f, 0.0f);
	glVertex3f(-0.49f, 0.16f, 0.0f);
	glVertex3f(-0.49f, 0.16f, 0.0f);
	glVertex3f(-0.49f, 0.14f, 0.0f);

	//8
	glVertex3f(-0.49f, 0.14f, 0.0f);
	glVertex3f(-0.47f, 0.14f, 0.0f);
	glVertex3f(-0.47f, 0.14f, 0.0f);
	glVertex3f(-0.47f, 0.16f, 0.0f);

	//9
	glVertex3f(-0.41f, 0.10f, 0.0f);
	glVertex3f(-0.41f, 0.20f, 0.0f);
	glVertex3f(-0.33f, 0.20f, 0.0f);
	glVertex3f(-0.33f, 0.18f, 0.0f);

	// 10
	glVertex3f(-0.33f, 0.18f, 0.0f);
	glVertex3f(-0.38f, 0.18f, 0.0f);
	glVertex3f(-0.38f, 0.18f, 0.0f);
	glVertex3f(-0.38f, 0.14f, 0.0f);

	//11
	glVertex3f(-0.38f, 0.14f, 0.0f);
	glVertex3f(-0.33f, 0.14f, 0.0f);
	glVertex3f(-0.33f, 0.14f, 0.0f);
	glVertex3f(-0.33f, 0.10f, 0.0f);

	//12
	glVertex3f(-0.33f, 0.10f, 0.0f);
	glVertex3f(-0.38f, 0.10f, 0.0f);
	glVertex3f(-0.38f, 0.11f, 0.0f);
	glVertex3f(-0.36f, 0.08f, 0.0f);

	//13
	glVertex3f(-0.32f, 0.25f, 0.0f);
	glVertex3f(-0.27f, 0.20f, 0.0f);
	glVertex3f(-0.27f, 0.20f, 0.0f);
	glVertex3f(-0.27f, 0.18f, 0.0f);

	// 14
	glVertex3f(-0.27f, 0.18f, 0.0f);
	glVertex3f(-0.31f, 0.18f, 0.0f);
	glVertex3f(-0.31f, 0.18f, 0.0f);
	glVertex3f(-0.31f, 0.11f, 0.0f);

	//15
	glVertex3f(-0.31f, 0.11f, 0.0f);
	glVertex3f(-0.27f, 0.11f, 0.0f);
	glVertex3f(-0.19f, 0.20f, 0.0f);
	glVertex3f(-0.19f, 0.18f, 0.0f);

	//16
	glVertex3f(-0.19f, 0.18f, 0.0f);
	glVertex3f(-0.24f, 0.18f, 0.0f);
	glVertex3f(-0.24f, 0.18f, 0.0f);
	glVertex3f(-0.24f, 0.14f, 0.0f);

	//17
	glVertex3f(-0.24f, 0.14f, 0.0f);
	glVertex3f(-0.19f, 0.14f, 0.0f);
	glVertex3f(-0.19f, 0.14f, 0.0f);
	glVertex3f(-0.19f, 0.10f, 0.0f);

	// 18
	glVertex3f(-0.0f, 0.0f, 0.0f);
	glVertex3f(-0.0f, 0.0f, 0.0f);
	glVertex3f(-0.0f, 0.0f, 0.0f);
	glVertex3f(-0.0f, 0.0f, 0.0f);

	//19
	glVertex3f(-0.19f, 0.10f, 0.0f);
	glVertex3f(-0.24f, 0.10f, 0.0f);

	glVertex3f(-0.65f, 0.2f, 0.0f);
	glVertex3f(-0.15f, 0.2f, 0.0f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3f, 0.24f, 0.0f);
	glScalef(1.2f, 1.2f, 1.0f);

	glBegin(GL_LINES);

	// By (बाय)
	glVertex3f(-0.3f, -0.1f, 0.0f);
	glVertex3f(-0.3f, -0.2f, 0.0f);
	glVertex3f(-0.3f, -0.12f, 0.0f);
	glVertex3f(-0.35f, -0.12f, 0.0f);

	glVertex3f(-0.35f, -0.12f, 0.0f);
	glVertex3f(-0.35f, -0.18f, 0.0f);
	glVertex3f(-0.35f, -0.18f, 0.0f);
	glVertex3f(-0.3f, -0.18f, 0.0f);

	glVertex3f(-0.35f, -0.12f, 0.0f);
	glVertex3f(-0.3f, -0.18f, 0.0f);
	glVertex3f(-0.28f, -0.1f, 0.0f);
	glVertex3f(-0.28f, -0.2f, 0.0f);

	glVertex3f(-0.26f, -0.1f, 0.0f);
	glVertex3f(-0.21f, -0.15f, 0.0f);

	glVertex3f(-0.21f, -0.15f, 0.0f);
	glVertex3f(-0.25f, -0.15f, 0.0f);
	glVertex3f(-0.25f, -0.15f, 0.0f);
	glVertex3f(-0.21f, -0.20f, 0.0f);

	glVertex3f(-0.21f, -0.20f, 0.0f);
	glVertex3f(-0.17f, -0.15f, 0.0f);
	glVertex3f(-0.17f, -0.1f, 0.0f);
	glVertex3f(-0.17f, -0.20f, 0.0f);

	glVertex3f(-0.37f, -0.1f, 0.0f);
	glVertex3f(-0.14f, -0.1f, 0.0f);

	glEnd();
	glPopMatrix();

	glPopMatrix(); // End First Line


	// Second Line: "Dr. Vijay Gokhale Sir" (डॉ. विजय गोखले सर)
	glPushMatrix();
	glTranslatef(-0.21f, 0.15f, 0.0f);
	glScalef(1.5f, 1.9f, 1.0f);

	// Dr. (डॉ.)
	glPushMatrix();
	glTranslatef(-0.78f, -0.03f, 0.0f);
	glScalef(1.2f, 1.2f, 1.0f);

	glLineWidth(7.0f);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(0.2f, -0.1f, 0.0f);
	glVertex3f(0.3f, -0.1f, 0.0f);

	glVertex3f(0.25f, -0.1f, 0.0f);
	glVertex3f(0.25f, -0.12f, 0.0f);

	glVertex3f(0.25f, -0.12f, 0.0f);
	glVertex3f(0.2f, -0.12f, 0.0f);
	glVertex3f(0.2f, -0.12f, 0.0f);
	glVertex3f(0.2f, -0.16f, 0.0f);

	glVertex3f(0.2f, -0.16f, 0.0f);
	glVertex3f(0.25f, -0.16f, 0.0f);
	glVertex3f(0.25f, -0.16f, 0.0f);
	glVertex3f(0.25f, -0.2f, 0.0f);

	glVertex3f(0.25f, -0.2f, 0.0f);
	glVertex3f(0.2f, -0.2f, 0.0f);
	glVertex3f(0.27f, -0.1f, 0.0f);
	glVertex3f(0.27f, -0.2f, 0.0f);

	glVertex3f(0.22f, -0.06f, 0.0f);
	glVertex3f(0.22f, -0.08f, 0.0f);
	glVertex3f(0.22f, -0.08f, 0.0f);
	glVertex3f(0.27f, -0.08f, 0.0f);

	glVertex3f(0.27f, -0.08f, 0.0f);
	glVertex3f(0.27f, -0.06f, 0.0f);

	glEnd();
	glPopMatrix();

	// Vijay (विजय)
	glPushMatrix();
	glTranslatef(-0.4f, -0.39f, 0.0f);
	glScalef(1.2f, 1.2f, 1.0f);

	glLineWidth(7.0f);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(0.05f, 0.10f, 0.0f);
	glVertex3f(0.05f, 0.25f, 0.0f);
	glVertex3f(0.05f, 0.25f, 0.0f);
	glVertex3f(0.10f, 0.25f, 0.0f);

	// 2
	glVertex3f(0.10f, 0.25f, 0.0f);
	glVertex3f(0.12f, 0.20f, 0.0f);
	glVertex3f(0.12f, 0.20f, 0.0f);
	glVertex3f(0.12f, 0.10f, 0.0f);

	//3
	glVertex3f(0.12f, 0.18f, 0.0f);
	glVertex3f(0.08f, 0.18f, 0.0f);
	glVertex3f(0.08f, 0.18f, 0.0f);
	glVertex3f(0.08f, 0.12f, 0.0f);

	// 4
	glVertex3f(0.08f, 0.12f, 0.0f);
	glVertex3f(0.12f, 0.12f, 0.0f);
	glVertex3f(0.15f, 0.17f, 0.0f);
	glVertex3f(0.15f, 0.12f, 0.0f);

	// 5
	glVertex3f(0.15f, 0.12f, 0.0f);
	glVertex3f(0.20f, 0.12f, 0.0f);
	glVertex3f(0.20f, 0.12f, 0.0f);
	glVertex3f(0.20f, 0.16f, 0.0f);

	// 6
	glVertex3f(0.20f, 0.16f, 0.0f);
	glVertex3f(0.24f, 0.16f, 0.0f);
	glVertex3f(0.24f, 0.10f, 0.0f);
	glVertex3f(0.24f, 0.20f, 0.0f);

	//7
	glVertex3f(0.27f, 0.20f, 0.0f);
	glVertex3f(0.31f, 0.15f, 0.0f);
	glVertex3f(0.27f, 0.15f, 0.0f);
	glVertex3f(0.31f, 0.15f, 0.0f);

	// 8
	glVertex3f(0.27f, 0.15f, 0.0f);
	glVertex3f(0.30f, 0.10f, 0.0f);
	glVertex3f(0.30f, 0.10f, 0.0f);
	glVertex3f(0.35f, 0.15f, 0.0f);

	//9
	glVertex3f(0.35f, 0.20f, 0.0f);
	glVertex3f(0.35f, 0.10f, 0.0f);

	glVertex3f(0.02f, 0.20f, 0.0f);
	glVertex3f(0.38f, 0.20f, 0.0f);

	glEnd();
	glPopMatrix();

	// Gokhale (गोखले)
	glPushMatrix();
	glTranslatef(-0.38f, -0.41f, 0.0f);
	glScalef(1.2f, 1.3f, 1.0f);

	glLineWidth(7.0f);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	//5
	glVertex3f(0.45f, 0.20f, 0.0f);
	glVertex3f(0.73f, 0.20f, 0.0f);

	glVertex3f(0.47f, 0.20f, 0.0f);
	glVertex3f(0.47f, 0.13f, 0.0f);

	// 10
	glVertex3f(0.47f, 0.16f, 0.0f);
	glVertex3f(0.44f, 0.16f, 0.0f);
	glVertex3f(0.44f, 0.16f, 0.0f);
	glVertex3f(0.44f, 0.13f, 0.0f);

	// 11
	glVertex3f(0.44f, 0.13f, 0.0f);
	glVertex3f(0.47f, 0.13f, 0.0f);
	glVertex3f(0.49f, 0.20f, 0.0f);
	glVertex3f(0.49f, 0.10f, 0.0f);

	//12
	glVertex3f(0.51f, 0.10f, 0.0f);
	glVertex3f(0.51f, 0.20f, 0.0f);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.51f, 0.20f, 0.0f);

	// 13
	glVertex3f(0.55f, 0.20f, 0.0f);
	glVertex3f(0.59f, 0.15f, 0.0f);
	glVertex3f(0.59f, 0.15f, 0.0f);
	glVertex3f(0.54f, 0.15f, 0.0f);

	//14
	glVertex3f(0.54f, 0.15f, 0.0f);
	glVertex3f(0.59f, 0.10f, 0.0f);
	glVertex3f(0.59f, 0.10f, 0.0f);
	glVertex3f(0.62f, 0.15f, 0.0f);

	// 15
	glVertex3f(0.62f, 0.20f, 0.0f);
	glVertex3f(0.62f, 0.10f, 0.0f);
	glVertex3f(0.60f, 0.18f, 0.0f);
	glVertex3f(0.62f, 0.18f, 0.0f);

	//7
	glVertex3f(0.60f, 0.18f, 0.0f);
	glVertex3f(0.60f, 0.12f, 0.0f);
	glVertex3f(0.65f, 0.11f, 0.0f);
	glVertex3f(0.65f, 0.17f, 0.0f);

	//8
	glVertex3f(0.65f, 0.17f, 0.0f);
	glVertex3f(0.68f, 0.13f, 0.0f);
	glVertex3f(0.68f, 0.13f, 0.0f);
	glVertex3f(0.70f, 0.16f, 0.0f);

	//9
	glVertex3f(0.70f, 0.10f, 0.0f);
	glVertex3f(0.70f, 0.20f, 0.0f);
	glVertex3f(0.65f, 0.25f, 0.0f);
	glVertex3f(0.70f, 0.20f, 0.0f);

	glEnd();
	glPopMatrix();

	// Sir (सर)
	glPushMatrix();
	glTranslatef(-0.3f, -0.39f, 0.0f);
	glScalef(1.2f, 1.2f, 1.0f);

	glLineWidth(7.0f);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(0.72f, 0.20f, 0.0f);
	glVertex3f(0.93f, 0.20f, 0.0f);

	//1
	glVertex3f(0.77f, 0.20f, 0.0f);
	glVertex3f(0.81f, 0.15f, 0.0f);
	glVertex3f(0.77f, 0.15f, 0.0f);
	glVertex3f(0.83f, 0.15f, 0.0f);

	//2
	glVertex3f(0.77f, 0.15f, 0.0f);
	glVertex3f(0.80f, 0.10f, 0.0f);
	glVertex3f(0.83f, 0.10f, 0.0f);
	glVertex3f(0.83f, 0.20f, 0.0f);

	//3
	glVertex3f(0.87f, 0.20f, 0.0f);
	glVertex3f(0.91f, 0.15f, 0.0f);
	glVertex3f(0.87f, 0.15f, 0.0f);
	glVertex3f(0.91f, 0.15f, 0.0f);

	//4
	glVertex3f(0.87f, 0.15f, 0.0f);
	glVertex3f(0.91f, 0.10f, 0.0f);

	glEnd();
	glPopMatrix();

	glPopMatrix(); // End Second Line
}

void Ignited(void)
{
	IgnitedBy();
}
