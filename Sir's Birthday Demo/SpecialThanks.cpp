// Header Files 
#include <windows.h>
#include <stdio.h> //for file I/O
#include <stdlib.h> // for exit

//OpenGl Related Header files
#include <gl\GL.h>
#include <gl/glu.h>

//Link with OpenGl import library
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLU32.lib")

extern GLuint texture_background;

void SpecialThanks(void)
{

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

	//Special

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(2.0f, 1.2f, 0.0f);
	{
		glPushMatrix();
		glTranslatef(-0.17f, 0.1f, 0.0f);
		glScalef(0.7f, 1.2f, 0.0f);
		{

			glPushMatrix();
			glTranslatef(-0.5f, 0.7f, 0.0f);
			glScalef(0.7f, 1.4f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.18f, 0.0f);
			glVertex3f(0.21f, -0.2f, 0.0f);
			glVertex3f(0.91f, -0.2f, 0.0f);
			glVertex3f(0.9f, -0.18f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.19f, 0.0f);
			glVertex3f(0.28f, -0.19f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.25f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.23f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.23f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.25f, -0.28f, 0.0f);
			glVertex3f(0.28f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.26f, 0.0f);
			glVertex3f(0.24f, -0.29f, 0.0f);
			glVertex3f(0.35f, -0.29f, 0.0f);
			glVertex3f(0.35f, -0.26f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.2f, 0.38f, 0.0f);
			glScalef(0.45f, 0.45f, 1.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.1f, 0.1f, 0.0f);
			glVertex3f(-0.15f, 0.1f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(-0.07f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.4f, 0.0f);
			glVertex3f(0.05f, -0.4f, 0.0f);
			glVertex3f(0.05f, 0.1f, 0.0f);
			glVertex3f(0.0f, 0.1f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.325f, 0.56f, 0.0f);
			glScalef(0.9f, 0.7f, 1.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.12f, -0.03f, 0.0f);
			glVertex3f(0.12f, -0.06f, 0.0f);
			glVertex3f(0.14f, -0.19f, 0.0f);
			glVertex3f(0.16f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.1f, -0.02f, 0.0f);
			glVertex3f(0.1f, -0.055f, 0.0f);
			glVertex3f(0.12f, -0.06f, 0.0f);
			glVertex3f(0.12f, -0.03f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.11f, 0.28f, 0.0f);
			glScalef(0.9f, 1.0f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.2f, 0.06f, 0.0f);
			glVertex3f(-0.19f, 0.08f, 0.0f);
			glVertex3f(-0.23f, 0.1f, 0.0f);
			glVertex3f(-0.26f, 0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.23f, 0.1f, 0.0f);
			glVertex3f(-0.26f, 0.1f, 0.0f);
			glVertex3f(-0.25f, 0.15f, 0.0f);
			glVertex3f(-0.22f, 0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.21f, 0.15f, 0.0f);
			glVertex3f(-0.18f, 0.15f, 0.0f);
			glVertex3f(-0.17f, 0.11f, 0.0f);
			glVertex3f(-0.2f, 0.11f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.17f, 0.11f, 0.0f);
			glVertex3f(-0.2f, 0.11f, 0.0f);
			glVertex3f(-0.27f, 0.0f, 0.0f);
			glVertex3f(-0.27f, -0.05f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.24f, 0.02f, 0.0f);
			glVertex3f(-0.26f, 0.0f, 0.0f);
			glVertex3f(-0.28f, 0.0f, 0.0f);
			glVertex3f(-0.28f, 0.04f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.28f, 0.01f, 0.0f);
			glVertex3f(-0.28f, 0.04f, 0.0f);
			glVertex3f(-0.29f, 0.0f, 0.0f);
			glVertex3f(-0.28f, -0.05f, 0.0f);
			glVertex3f(-0.27f, -0.05f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.26f, 0.03f, 0.0f);
			glVertex3f(-0.28f, -0.01f, 0.0f);
			glVertex3f(-0.26f, -0.09f, 0.0f);
			glVertex3f(-0.23f, -0.07f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.14f, 0.15f, 0.0f);
			glVertex3f(-0.14f, -0.08f, 0.0f);
			glVertex3f(-0.12f, -0.09f, 0.0f);
			glVertex3f(-0.12f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0f, 0.6f, 0.0f);
			glScalef(0.7f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.15f, -0.2f, 0.0f);
			glVertex3f(0.15f, -0.45f, 0.0f);
			glVertex3f(0.17f, -0.46f, 0.0f);
			glVertex3f(0.17f, -0.2f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.13f, -0.31f, 0.0f);
			glVertex3f(0.13f, -0.275f, 0.0f);
			glVertex3f(0.15f, -0.27f, 0.0f);
			glVertex3f(0.15f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.1f, -0.34f, 0.0f);
			glVertex3f(0.12f, -0.35f, 0.0f);
			glVertex3f(0.13f, -0.31f, 0.0f);
			glVertex3f(0.13f, -0.275f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.13f, -0.28f, 0.0f);
			glVertex3f(0.13f, -0.3f, 0.0f);
			glVertex3f(0.09f, -0.31f, 0.0f);
			glVertex3f(0.09f, -0.27f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.09f, -0.31f, 0.0f);
			glVertex3f(0.09f, -0.27f, 0.0f);
			glVertex3f(0.05f, -0.34f, 0.0f);
			glVertex3f(0.08f, -0.34f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.05f, -0.34f, 0.0f);
			glVertex3f(0.08f, -0.34f, 0.0f);
			glVertex3f(0.11f, -0.43f, 0.0f);
			glVertex3f(0.09f, -0.45f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();

		//Thanks

		glPushMatrix();
		glTranslatef(0.06f, -0.03f, 0.0f);
		glScalef(0.7f, 1.04f, 0.0f);
		{
			glPushMatrix();
			glTranslatef(-0.25f, 0.77f, 0.0f);
			glScalef(0.9f, 1.0f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.15f, 0.0f);
			glVertex3f(0.28f, -0.15f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.25f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.23f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.23f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.25f, -0.28f, 0.0f);
			glVertex3f(0.28f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.27f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glVertex3f(0.33f, -0.36f, 0.0f);
			glVertex3f(0.33f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.33f, -0.15f, 0.0f);
			glVertex3f(0.33f, -0.4f, 0.0f);
			glVertex3f(0.35f, -0.42f, 0.0f);
			glVertex3f(0.35f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.16f, -0.12f, 0.0f);
			glVertex3f(0.18f, -0.15f, 0.0f);
			glVertex3f(0.69f, -0.15f, 0.0f);
			glVertex3f(0.67f, -0.12f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.16f, 0.49f, 0.0f);
			glScalef(0.9f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.2f, 0.06f, 0.0f);
			glVertex3f(-0.19f, 0.08f, 0.0f);
			glVertex3f(-0.23f, 0.1f, 0.0f);
			glVertex3f(-0.26f, 0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.23f, 0.1f, 0.0f);
			glVertex3f(-0.26f, 0.1f, 0.0f);
			glVertex3f(-0.25f, 0.15f, 0.0f);
			glVertex3f(-0.22f, 0.15f, 0.0f);
			glEnd();

			glPointSize(9.0f);
			glBegin(GL_POINTS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.09f, 0.2f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.095f, 0.78f, 0.0f);
			glScalef(0.9f, 0.7f, 1.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.12f, -0.03f, 0.0f);
			glVertex3f(0.12f, -0.06f, 0.0f);
			glVertex3f(0.14f, -0.19f, 0.0f);
			glVertex3f(0.16f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.1f, -0.02f, 0.0f);
			glVertex3f(0.1f, -0.055f, 0.0f);
			glVertex3f(0.12f, -0.06f, 0.0f);
			glVertex3f(0.12f, -0.03f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.075f, 0.78f, 0.0f);
			glScalef(0.9f, 0.7f, 1.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.12f, -0.03f, 0.0f);
			glVertex3f(0.12f, -0.06f, 0.0f);
			glVertex3f(0.14f, -0.19f, 0.0f);
			glVertex3f(0.16f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.1f, -0.02f, 0.0f);
			glVertex3f(0.1f, -0.055f, 0.0f);
			glVertex3f(0.12f, -0.06f, 0.0f);
			glVertex3f(0.12f, -0.03f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.15f, 0.88f, 0.0f);
			glScalef(0.9f, 1.35f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.19f, 0.0f);
			glVertex3f(0.0f, -0.38f, 0.0f);
			glVertex3f(0.02f, -0.39f, 0.0f);
			glVertex3f(0.02f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.01f, -0.26f, 0.0f);
			glVertex3f(0.0f, -0.24f, 0.0f);
			glVertex3f(-0.02f, -0.23f, 0.0f);
			glVertex3f(-0.02f, -0.26f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.02f, -0.23f, 0.0f);
			glVertex3f(-0.02f, -0.26f, 0.0f);
			glVertex3f(-0.03f, -0.28f, 0.0f);
			glVertex3f(-0.05f, -0.28f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.03f, -0.28f, 0.0f);
			glVertex3f(-0.05f, -0.28f, 0.0f);
			glVertex3f(-0.05f, -0.31f, 0.0f);
			glVertex3f(-0.03f, -0.29f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.05f, -0.31f, 0.0f);
			glVertex3f(-0.03f, -0.29f, 0.0f);
			glVertex3f(-0.02f, -0.32f, 0.0f);
			glVertex3f(-0.02f, -0.34f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.02f, -0.32f, 0.0f);
			glVertex3f(-0.02f, -0.34f, 0.0f);
			glVertex3f(0.0f, -0.31f, 0.0f);
			glVertex3f(0.01f, -0.28f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.02f, -0.24f, 0.0f);
			glVertex3f(0.02f, -0.27f, 0.0f);
			glVertex3f(0.05f, -0.25f, 0.0f);
			glVertex3f(0.05f, -0.23f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.05f, -0.25f, 0.0f);
			glVertex3f(0.05f, -0.23f, 0.0f);
			glVertex3f(0.08f, -0.28f, 0.0f);
			glVertex3f(0.06f, -0.28f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.06f, 0.85f, 0.0f);
			glScalef(0.7f, 1.3f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.17f, 0.0f);
			glVertex3f(0.28f, -0.17f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.25f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.23f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.23f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.25f, -0.28f, 0.0f);
			glVertex3f(0.28f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.27f, 0.0f);
			glVertex3f(0.24f, -0.3f, 0.0f);
			glVertex3f(0.35f, -0.3f, 0.0f);
			glVertex3f(0.35f, -0.27f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(0.35f, -0.17f, 0.0f);
			glVertex3f(0.35f, -0.35f, 0.0f);
			glVertex3f(0.38f, -0.36f, 0.0f);
			glVertex3f(0.38f, -0.17f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();


		glPushMatrix();
		glTranslatef(0.21f, -0.02f, 0.0f);
		glScalef(0.65f, 1.0f, 0.0f);
		{
			glPushMatrix();
			glTranslatef(0.7f, 0.19f, 0.0f);
			glScalef(0.65f, 1.2f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.7f, 0.395f, 0.0f);
			glVertex3f(-0.68f, 0.37f, 0.0f);
			glVertex3f(-0.54f, 0.37f, 0.0f);
			glVertex3f(-0.56f, 0.395f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.62f, 0.30f, 0.0f);
			glVertex3f(-0.62f, 0.37f, 0.0f);
			glVertex3f(-0.6f, 0.37f, 0.0f);
			glVertex3f(-0.6f, 0.30f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.70f, 0.33f, 0.0f);
			glVertex3f(-0.70f, 0.30f, 0.0f);
			glVertex3f(-0.62f, 0.30f, 0.0f);
			glVertex3f(-0.62f, 0.33f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.70f, 0.30f, 0.0f);
			glVertex3f(-0.70f, 0.16f, 0.0f);
			glVertex3f(-0.67f, 0.16f, 0.0f);
			glVertex3f(-0.67f, 0.30f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.70f, 0.20f, 0.0f);
			glVertex3f(-0.70f, 0.16f, 0.0f);
			glVertex3f(-0.60f, 0.16f, 0.0f);
			glVertex3f(-0.60f, 0.20f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.60f, 0.16f, 0.0f);
			glVertex3f(-0.60f, 0.22f, 0.0f);
			glVertex3f(-0.57f, 0.22f, 0.0f);
			glVertex3f(-0.57f, 0.16f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.4f, 0.27f, 0.0f);
			glScalef(1.0f, 1.0f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.1f, 0.05f, 0.0f);
			glVertex3f(-0.13f, 0.07f, 0.0f);
			glVertex3f(-0.13f, 0.1f, 0.0f);
			glVertex3f(-0.12f, 0.13f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.50f, 0.0f, 0.0f);
			glVertex3f(-0.13f, 0.1f, 0.0f);
			glVertex3f(-0.12f, 0.13f, 0.0f);
			glVertex3f(-0.05f, 0.05f, 0.0f);
			glVertex3f(-0.07f, 0.03f, 0.0f);
			glEnd();

			glPopMatrix();

		}
		glPopMatrix();
	}
	glPopMatrix();


	//Rama mam

	glPushMatrix();
	glTranslatef(-0.15f, 0.0f, 0.0f);
	glScalef(2.0f, 1.4f, 0.0f);
	{

		glPushMatrix();
		glTranslatef(0.0f, -0.1f, 0.0f);
		glScalef(0.8f, 1.3f, 0.0f);
		{

			glPushMatrix();
			glTranslatef(-0.37f, 0.35f, 0.0f);
			glScalef(0.7f, 1.07f, 0.0f);


			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.25f, -0.19f, 0.0f);
			glVertex3f(0.28f, -0.19f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.25f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.23f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.23f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.25f, -0.28f, 0.0f);
			glVertex3f(0.28f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glEnd();

			glPopMatrix();


			glPushMatrix();
			glTranslatef(-0.26f, 0.31f, 0.0f);
			glScalef(0.8f, 0.8f, 0.0f);

			//m
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.18f, -0.19f, 0.0f);
			glVertex3f(0.18f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.02f, -0.18f, 0.0f);
			glVertex3f(0.03f, -0.21f, 0.0f);
			glVertex3f(0.34f, -0.21f, 0.0f);
			glVertex3f(0.35f, -0.18f, 0.0f);
			glEnd();

			glPopMatrix();

			//continue m
			glPushMatrix();
			glTranslatef(-0.09f, 0.05f, 0.0f);
			glScalef(0.7f, 0.7f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
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
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(0.03f, -0.01f, 0.0f);
			glVertex3f(0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.03f, 0.15f, 0.0f);
			glVertex3f(0.03f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.12f, 0.0f);
			glVertex3f(0.05f, 0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.08f, 0.15f, 0.0f);
			glVertex3f(0.08f, -0.1f, 0.0f);
			glVertex3f(0.1f, -0.12f, 0.0f);
			glVertex3f(0.1f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();

		//Mam

		glPushMatrix();
		glTranslatef(0.0f, -0.015f, 0.0f);
		glScalef(0.9f, 1.15f, 0.0f);
		{
			glPushMatrix();
			glTranslatef(0.0f, 0.26f, 0.0f);
			glScalef(0.8f, 0.8f, 0.0f);

			//m
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.18f, -0.19f, 0.0f);
			glVertex3f(0.18f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.13f, -0.18f, 0.0f);
			glVertex3f(0.14f, -0.21f, 0.0f);
			glVertex3f(0.44f, -0.21f, 0.0f);
			glVertex3f(0.45f, -0.18f, 0.0f);
			glEnd();

			glPopMatrix();

			//continue m
			glPushMatrix();
			glTranslatef(0.17f, -0.0f, 0.0f);
			glScalef(0.7f, 0.7f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
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
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(0.03f, -0.01f, 0.0f);
			glVertex3f(0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.03f, 0.15f, 0.0f);
			glVertex3f(0.03f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.12f, 0.0f);
			glVertex3f(0.05f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();


			glPushMatrix();
			glTranslatef(0.11f, 0.26f, 0.0f);
			glScalef(0.8f, 0.8f, 0.0f);

			//m
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.18f, -0.19f, 0.0f);
			glVertex3f(0.18f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.19f, 0.0f);
			glEnd();

			glPopMatrix();

			//continue m
			glPushMatrix();
			glTranslatef(0.28f, -0.0f, 0.0f);
			glScalef(0.7f, 0.7f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
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
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(0.03f, -0.01f, 0.0f);
			glVertex3f(0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.03f, 0.15f, 0.0f);
			glVertex3f(0.03f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.12f, 0.0f);
			glVertex3f(0.05f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();


			glPushMatrix();
			glTranslatef(0.39f, 0.21f, 0.0f);
			glScalef(0.6f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.38f, -0.05f, 0.0f);
			glVertex3f(-0.34f, -0.04f, 0.0f);
			glVertex3f(-0.32f, -0.07f, 0.0f);
			glVertex3f(-0.32f, -0.09f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.32f, -0.09f, 0.0f);
			glVertex3f(-0.33f, -0.06f, 0.0f);
			glVertex3f(-0.31f, -0.04f, 0.0f);
			glVertex3f(-0.26f, -0.05f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	//Pradnya

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.8f, 1.2f, 0.0f);
	{

		glPushMatrix();
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glScalef(1.1f, 1.1f, 0.0f);
		{

			glPushMatrix();
			glTranslatef(-0.13f, -0.45f, 0.0f);
			glScalef(0.3f, 0.6f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.2f, 0.05f, 0.0f);
			glVertex3f(-0.24f, 0.1f, 0.0f);
			glVertex3f(0.7f, 0.1f, 0.0f);
			glVertex3f(0.73f, 0.05f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.1f, 0.1f, 0.0f);
			glVertex3f(-0.15f, 0.1f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(-0.07f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.4f, 0.0f);
			glVertex3f(0.05f, -0.4f, 0.0f);
			glVertex3f(0.05f, 0.1f, 0.0f);
			glVertex3f(0.0f, 0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(-0.03f, -0.18f, 0.0f);
			glVertex3f(-0.12f, -0.4f, 0.0f);
			glVertex3f(-0.07f, -0.4f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, -0.4f, 0.0f);
			glVertex3f(0.5f, 0.1f, 0.0f);
			glVertex3f(0.54f, 0.1f, 0.0f);
			glVertex3f(0.54f, -0.42f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.6f, -0.4f, 0.0f);
			glVertex3f(0.6f, 0.1f, 0.0f);
			glVertex3f(0.64f, 0.1f, 0.0f);
			glVertex3f(0.64f, -0.42f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.28f, -0.05f, 0.0f);
			glVertex3f(0.28f, -0.02f, 0.0f);
			glVertex3f(0.5f, -0.02f, 0.0f);
			glVertex3f(0.5f, -0.05f, 0.0f);
			glEnd();

			glPopMatrix();

			//U letter ///////////////////////////////
			glPushMatrix();
			glTranslatef(-0.04f, -0.52f, 0.0f);
			glScalef(0.2f, 0.5f, 1.0f);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(-0.07f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(-0.15f, -0.1f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.15f, 0.0f);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(0.0f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.03f, -0.15f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(0.05f, -0.15f, 0.0f);
			glVertex3f(0.05f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, 0.0f);
			glVertex3f(-0.03f, -0.15f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.1f, 0.0f);
			glVertex3f(0.05f, 0.1f, 0.0f);
			glVertex3f(0.0f, 0.1f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.06f, -0.46f, 0.0f);
			glScalef(0.2f, 0.7f, 1.0f);

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -0.2f, 0.0f);
			glVertex3f(-0.03f, -0.18f, 0.0f);
			glVertex3f(-0.12f, -0.3f, 0.0f);
			glVertex3f(-0.07f, -0.3f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.61f, 0.0f);
		glScalef(0.9f, 1.6f, 0.0f);
		{
			glPushMatrix();
			glTranslatef(0.0f, 0.26f, 0.0f);
			glScalef(0.8f, 0.8f, 0.0f);

			//m
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.18f, -0.19f, 0.0f);
			glVertex3f(0.18f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.19f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.13f, -0.18f, 0.0f);
			glVertex3f(0.14f, -0.21f, 0.0f);
			glVertex3f(0.44f, -0.21f, 0.0f);
			glVertex3f(0.45f, -0.18f, 0.0f);
			glEnd();

			glPopMatrix();

			//continue m
			glPushMatrix();
			glTranslatef(0.17f, -0.0f, 0.0f);
			glScalef(0.7f, 0.7f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
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
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(0.03f, -0.01f, 0.0f);
			glVertex3f(0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.03f, 0.15f, 0.0f);
			glVertex3f(0.03f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.12f, 0.0f);
			glVertex3f(0.05f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();


			glPushMatrix();
			glTranslatef(0.11f, 0.26f, 0.0f);
			glScalef(0.8f, 0.8f, 0.0f);

			//m
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.18f, -0.19f, 0.0f);
			glVertex3f(0.18f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.33f, 0.0f);
			glVertex3f(0.2f, -0.19f, 0.0f);
			glEnd();

			glPopMatrix();

			//continue m
			glPushMatrix();
			glTranslatef(0.28f, -0.0f, 0.0f);
			glScalef(0.7f, 0.7f, 0.0f);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
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
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.01f, 0.02f, 0.0f);
			glVertex3f(-0.01f, -0.01f, 0.0f);
			glVertex3f(0.03f, -0.01f, 0.0f);
			glVertex3f(0.03f, 0.02f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.03f, 0.15f, 0.0f);
			glVertex3f(0.03f, -0.1f, 0.0f);
			glVertex3f(0.05f, -0.12f, 0.0f);
			glVertex3f(0.05f, 0.15f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.39f, 0.21f, 0.0f);
			glScalef(0.6f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.38f, -0.05f, 0.0f);
			glVertex3f(-0.34f, -0.04f, 0.0f);
			glVertex3f(-0.32f, -0.07f, 0.0f);
			glVertex3f(-0.32f, -0.09f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.32f, -0.09f, 0.0f);
			glVertex3f(-0.33f, -0.06f, 0.0f);
			glVertex3f(-0.31f, -0.04f, 0.0f);
			glVertex3f(-0.26f, -0.05f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();

	}
	glPopMatrix();
}

