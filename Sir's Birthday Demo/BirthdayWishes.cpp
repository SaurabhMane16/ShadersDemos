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

void BirthdayWishes(void)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_background);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -1.5f, -0.1f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -1.5f, -0.1f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, 1.5f, -0.1f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, 1.5f, -0.1f);

glEnd();

glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 0);

	//Janamdinyasa//////////////////////////////

	glPushMatrix();
	glTranslatef(0.1f, -0.2f, 0.0f);
	glScalef(1.5f, 1.6f, 0.0f);

	glPushMatrix();
	glTranslatef(0.1f, 0.31f, 0.0f);
	glScalef(0.6f, 1.3f, 0.0f);

	glBegin(GL_QUADS);

	// 1)
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.45f, 0.25f, 0.0f);
	glVertex3f(-1.45f, 0.16f, 0.0f);
	glVertex3f(-1.42f, 0.16f, 0.0f);
	glVertex3f(-1.42f, 0.25f, 0.0f);

	// 2)

	glVertex3f(-1.42f, 0.20f, 0.0f);
	glVertex3f(-1.42f, 0.16f, 0.0f);
	glVertex3f(-1.34f, 0.16f, 0.0f);
	glVertex3f(-1.34f, 0.20f, 0.0f);

	// 3)

	glVertex3f(-1.36f, 0.23f, 0.0f);
	glVertex3f(-1.36f, 0.20f, 0.0f);
	glVertex3f(-1.28f, 0.20f, 0.0f);
	glVertex3f(-1.28f, 0.23f, 0.0f);

	// 4)

	glVertex3f(-1.28f, 0.30f, 0.0f);
	glVertex3f(-1.28f, 0.10f, 0.0f);
	glVertex3f(-1.25f, 0.10f, 0.0f);
	glVertex3f(-1.25f, 0.30f, 0.0f);

	// 5)

	glVertex3f(-1.23f, 0.24f, 0.0f);
	glVertex3f(-1.20f, 0.18f, 0.0f);
	glVertex3f(-1.18f, 0.18f, 0.0f);
	glVertex3f(-1.18f, 0.24f, 0.0f);

	// 6)

	glVertex3f(-1.18f, 0.24f, 0.0f);
	glVertex3f(-1.18f, 0.22f, 0.0f);
	glVertex3f(-1.14f, 0.22f, 0.0f);
	glVertex3f(-1.14f, 0.24f, 0.0f);

	// 7)

	glVertex3f(-1.15f, 0.22f, 0.0f);
	glVertex3f(-1.15f, 0.14f, 0.0f);
	glVertex3f(-1.08f, 0.14f, 0.0f);
	glVertex3f(-1.08f, 0.22f, 0.0f);

	// 8)

	glVertex3f(-1.11f, 0.30f, 0.0f);
	glVertex3f(-1.11f, 0.22f, 0.0f);
	glVertex3f(-1.08f, 0.22f, 0.0f);
	glVertex3f(-1.08f, 0.30f, 0.0f);

	// 9)

	glVertex3f(-1.08f, 0.22f, 0.0f);
	glVertex3f(-1.08f, 0.19f, 0.0f);
	glVertex3f(-1.01f, 0.19f, 0.0f);
	glVertex3f(-1.01f, 0.22f, 0.0f);

	// 10)

	glVertex3f(-1.01f, 0.30f, 0.0f);
	glVertex3f(-1.01f, 0.10f, 0.0f);
	glVertex3f(-0.98f, 0.10f, 0.0f);
	glVertex3f(-0.98f, 0.30f, 0.0f);

	// 11)

	glVertex3f(-0.95f, 0.45f, 0.0f);
	glVertex3f(-0.95f, 0.10f, 0.0f);
	glVertex3f(-0.92f, 0.10f, 0.0f);
	glVertex3f(-0.92f, 0.45f, 0.0f);

	// 12)

	glVertex3f(-0.95f, 0.42f, 0.0f);
	glVertex3f(-0.95f, 0.45f, 0.0f);
	glVertex3f(-0.80f, 0.45f, 0.0f);
	glVertex3f(-0.80f, 0.42f, 0.0f);

	//  13)

	glVertex3f(-0.80f, 0.45f, 0.0f);
	glVertex3f(-0.80f, 0.33f, 0.0f);
	glVertex3f(-0.77f, 0.33f, 0.0f);
	glVertex3f(-0.77f, 0.45f, 0.0f);

	// 14)

	glVertex3f(-0.82f, 0.30f, 0.0f);
	glVertex3f(-0.82f, 0.25f, 0.0f);
	glVertex3f(-0.79f, 0.25f, 0.0f);
	glVertex3f(-0.79f, 0.30f, 0.0f);

	// 15)

	glVertex3f(-0.82f, 0.28f, 0.0f);
	glVertex3f(-0.82f, 0.25f, 0.0f);
	glVertex3f(-0.89f, 0.25f, 0.0f);
	glVertex3f(-0.89f, 0.28f, 0.0f);

	// 16)

	glVertex3f(-0.86f, 0.28f, 0.0f);
	glVertex3f(-0.86f, 0.15f, 0.0f);
	glVertex3f(-0.89f, 0.15f, 0.0f);
	glVertex3f(-0.89f, 0.28f, 0.0f);

	// 17)

	glVertex3f(-0.89f, 0.18f, 0.0f);
	glVertex3f(-0.89f, 0.15f, 0.0f);
	glVertex3f(-0.78f, 0.15f, 0.0f);
	glVertex3f(-0.78f, 0.18f, 0.0f);

	// 18)

	glVertex3f(-0.83f, 0.20f, 0.0f);
	glVertex3f(-0.80f, 0.10f, 0.0f);
	glVertex3f(-0.77f, 0.10f, 0.0f);
	glVertex3f(-0.80f, 0.20f, 0.0f);

	// 19)

	glVertex3f(-0.74f, 0.23f, 0.0f);
	glVertex3f(-0.74f, 0.15f, 0.0f);
	glVertex3f(-0.68f, 0.15f, 0.0f);
	glVertex3f(-0.68f, 0.23f, 0.0f);

	// 20)

	glVertex3f(-0.68f, 0.23f, 0.0f);
	glVertex3f(-0.68f, 0.20f, 0.0f);
	glVertex3f(-0.58f, 0.20f, 0.0f);
	glVertex3f(-0.58f, 0.23f, 0.0f);

	// 21) 

	glVertex3f(-0.58f, 0.30f, 0.0f);
	glVertex3f(-0.58f, 0.10f, 0.0f);
	glVertex3f(-0.55f, 0.10f, 0.0f);
	glVertex3f(-0.55f, 0.30f, 0.0f);

	// 22) 

	glVertex3f(-0.50f, 0.24f, 0.0f);
	glVertex3f(-0.50f, 0.20f, 0.0f);
	glVertex3f(-0.38f, 0.20f, 0.0f);
	glVertex3f(-0.38f, 0.24f, 0.0f);

	// 23) 

	glVertex3f(-0.50f, 0.30f, 0.0f);
	glVertex3f(-0.45f, 0.24f, 0.0f);
	glVertex3f(-0.42f, 0.24f, 0.0f);
	glVertex3f(-0.47f, 0.30f, 0.0f);

	// 24) 

	glVertex3f(-0.50f, 0.20f, 0.0f);
	glVertex3f(-0.41f, 0.10f, 0.0f);
	glVertex3f(-0.38f, 0.10f, 0.0f);
	glVertex3f(-0.47f, 0.20f, 0.0f);

	// 25) 

	glVertex3f(-0.37f, 0.25f, 0.0f);
	glVertex3f(-0.37f, 0.17f, 0.0f);
	glVertex3f(-0.34f, 0.17f, 0.0f);
	glVertex3f(-0.34f, 0.25f, 0.0f);

	// 26) 

	glVertex3f(-0.37f, 0.24f, 0.0f);
	glVertex3f(-0.37f, 0.21f, 0.0f);
	glVertex3f(-0.26f, 0.21f, 0.0f);
	glVertex3f(-0.26f, 0.24f, 0.0f);

	// 27) 

	glVertex3f(-0.33f, 0.30f, 0.0f);
	glVertex3f(-0.29f, 0.24f, 0.0f);
	glVertex3f(-0.26f, 0.24f, 0.0f);
	glVertex3f(-0.30f, 0.30f, 0.0f);

	// 28) 

	glVertex3f(-0.37f, 0.17f, 0.0f);
	glVertex3f(-0.30f, 0.10f, 0.0f);
	glVertex3f(-0.30f, 0.13f, 0.0f);
	glVertex3f(-0.24f, 0.17f, 0.0f);

	// 29) 

	glVertex3f(-0.30f, 0.13f, 0.0f);
	glVertex3f(-0.30f, 0.10f, 0.0f);
	glVertex3f(-0.20f, 0.17f, 0.0f);
	glVertex3f(-0.20f, 0.20f, 0.0f);

	// 30) 

	glVertex3f(-0.20f, 0.30f, 0.0f);
	glVertex3f(-0.20f, 0.10f, 0.0f);
	glVertex3f(-0.17f, 0.10f, 0.0f);
	glVertex3f(-0.17f, 0.30f, 0.0f);

	// 31) line

	glVertex3f(-1.47f, 0.33f, 0.0f);
	glVertex3f(-1.47f, 0.30f, 0.0f);
	glVertex3f(-0.15f, 0.30f, 0.0f);
	glVertex3f(-0.15f, 0.33f, 0.0f);

	glEnd();

	glPopMatrix();

	//hardik//////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.95f, 0.35f, 0.0f);
	glScalef(0.9f, 1.0f, 0.0f);

	glBegin(GL_QUADS);

	// 1)
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.90f, 0.36f, 0.0f);
	glVertex3f(-0.90f, 0.29f, 0.0f);
	glVertex3f(-0.88f, 0.29f, 0.0f);
	glVertex3f(-0.88f, 0.36f, 0.0f);

	// 2) 

	glVertex3f(-0.98f, 0.32f, 0.0f);
	glVertex3f(-0.98f, 0.29f, 0.0f);
	glVertex3f(-0.90f, 0.29f, 0.0f);
	glVertex3f(-0.90f, 0.32f, 0.0f);

	// 3) 

	glVertex3f(-0.98f, 0.29f, 0.0f);
	glVertex3f(-0.94f, 0.23f, 0.0f);
	glVertex3f(-0.91f, 0.23f, 0.0f);
	glVertex3f(-0.95f, 0.29f, 0.0f);

	// 4) 

	glVertex3f(-0.98f, 0.18f, 0.0f);
	glVertex3f(-0.95f, 0.18f, 0.0f);
	glVertex3f(-0.90f, 0.24f, 0.0f);
	glVertex3f(-0.90f, 0.27f, 0.0f);

	// 5) 

	glVertex3f(-0.90f, 0.27f, 0.0f);
	glVertex3f(-0.90f, 0.24f, 0.0f);
	glVertex3f(-0.87f, 0.21f, 0.0f);
	glVertex3f(-0.84f, 0.21f, 0.0f);

	// 6) 

	glVertex3f(-0.87f, 0.21f, 0.0f);
	glVertex3f(-0.84f, 0.21f, 0.0f);
	glVertex3f(-0.88f, 0.15f, 0.0f);
	glVertex3f(-0.91f, 0.15f, 0.0f);

	// 7) 

	glVertex3f(-0.98f, 0.18f, 0.0f);
	glVertex3f(-0.95f, 0.18f, 0.0f);
	glVertex3f(-0.92f, 0.12f, 0.0f);
	glVertex3f(-0.95f, 0.12f, 0.0f);

	// 8) 

	glVertex3f(-0.95f, 0.12f, 0.0f);
	glVertex3f(-0.95f, 0.10f, 0.0f);
	glVertex3f(-0.88f, 0.10f, 0.0f);
	glVertex3f(-0.88f, 0.12f, 0.0f);

	// 9) 

	glVertex3f(-0.83f, 0.36f, 0.0f);
	glVertex3f(-0.83f, 0.10f, 0.0f);
	glVertex3f(-0.80f, 0.10f, 0.0f);
	glVertex3f(-0.80f, 0.36f, 0.0f);

	// 10) 

	glVertex3f(-0.78f, 0.50f, 0.0f);
	glVertex3f(-0.78f, 0.10f, 0.0f);
	glVertex3f(-0.75f, 0.10f, 0.0f);
	glVertex3f(-0.75f, 0.50f, 0.0f);

	// 11)

	glVertex3f(-0.78f, 0.50f, 0.0f);
	glVertex3f(-0.78f, 0.47f, 0.0f);
	glVertex3f(-0.60f, 0.47f, 0.0f);
	glVertex3f(-0.60f, 0.50f, 0.0f);

	// 12) 

	glVertex3f(-0.62f, 0.50f, 0.0f);
	glVertex3f(-0.62f, 0.30f, 0.0f);
	glVertex3f(-0.59f, 0.30f, 0.0f);
	glVertex3f(-0.59f, 0.50f, 0.0f);

	// 13) 

	glVertex3f(-0.60f, 0.39f, 0.0f);
	glVertex3f(-0.57f, 0.39f, 0.0f);
	glVertex3f(-0.54f, 0.47f, 0.0f);
	glVertex3f(-0.55f, 0.50f, 0.0f);

	// 14) 

	glVertex3f(-0.54f, 0.47f, 0.0f);
	glVertex3f(-0.55f, 0.50f, 0.0f);
	glVertex3f(-0.50f, 0.50f, 0.0f);
	glVertex3f(-0.50f, 0.47f, 0.0f);

	// 15) 

	glVertex3f(-0.70f, 0.33f, 0.0f);
	glVertex3f(-0.70f, 0.30f, 0.0f);
	glVertex3f(-0.62f, 0.30f, 0.0f);
	glVertex3f(-0.62f, 0.33f, 0.0f);

	// 16) 

	glVertex3f(-0.70f, 0.30f, 0.0f);
	glVertex3f(-0.70f, 0.16f, 0.0f);
	glVertex3f(-0.67f, 0.16f, 0.0f);
	glVertex3f(-0.67f, 0.30f, 0.0f);

	// 17) 

	glVertex3f(-0.70f, 0.20f, 0.0f);
	glVertex3f(-0.70f, 0.16f, 0.0f);
	glVertex3f(-0.60f, 0.16f, 0.0f);
	glVertex3f(-0.60f, 0.20f, 0.0f);

	// 18) 

	glVertex3f(-0.60f, 0.16f, 0.0f);
	glVertex3f(-0.60f, 0.22f, 0.0f);
	glVertex3f(-0.57f, 0.22f, 0.0f);
	glVertex3f(-0.57f, 0.16f, 0.0f);

	// 19) 

	glVertex3f(-0.62f, 0.16f, 0.0f);
	glVertex3f(-0.59f, 0.10f, 0.0f);
	glVertex3f(-0.56f, 0.10f, 0.0f);
	glVertex3f(-0.59f, 0.16f, 0.0f);

	// 20) 

	glVertex3f(-0.50f, 0.31f, 0.0f);
	glVertex3f(-0.50f, 0.18f, 0.0f);
	glVertex3f(-0.47f, 0.18f, 0.0f);
	glVertex3f(-0.47f, 0.31f, 0.0f);

	// 21) 

	glVertex3f(-0.50f, 0.31f, 0.0f);
	glVertex3f(-0.50f, 0.28f, 0.0f);
	glVertex3f(-0.39f, 0.28f, 0.0f);
	glVertex3f(-0.39f, 0.31f, 0.0f);

	// 22) 

	glVertex3f(-0.39f, 0.36f, 0.0f);
	glVertex3f(-0.39f, 0.10f, 0.0f);
	glVertex3f(-0.36f, 0.10f, 0.0f);
	glVertex3f(-0.36f, 0.36f, 0.0f);

	// 23) 

	glVertex3f(-0.50f, 0.21f, 0.0f);
	glVertex3f(-0.50f, 0.18f, 0.0f);
	glVertex3f(-0.39f, 0.18f, 0.0f);
	glVertex3f(-0.39f, 0.21f, 0.0f);

	// 24) 

	glVertex3f(-0.36f, 0.31f, 0.0f);
	glVertex3f(-0.36f, 0.28f, 0.0f);
	glVertex3f(-0.25f, 0.28f, 0.0f);
	glVertex3f(-0.25f, 0.32f, 0.0f);

	// 25) 

	glVertex3f(-0.28f, 0.31f, 0.0f);
	glVertex3f(-0.28f, 0.14f, 0.0f);
	glVertex3f(-0.25f, 0.14f, 0.0f);
	glVertex3f(-0.25f, 0.31f, 0.0f);

	// 26) 

	glVertex3f(-0.33f, 0.17f, 0.0f);
	glVertex3f(-0.33f, 0.14f, 0.0f);
	glVertex3f(-0.25f, 0.14f, 0.0f);
	glVertex3f(-0.25f, 0.17f, 0.0f);

	// 27) 

	glVertex3f(-0.22f, 0.36f, 0.0f);
	glVertex3f(-0.22f, 0.10f, 0.0f);
	glVertex3f(-0.19f, 0.10f, 0.0f);
	glVertex3f(-0.19f, 0.36f, 0.0f);

	// 28) 

	glVertex3f(-1.0f, 0.36f, 0.0f);
	glVertex3f(-1.0f, 0.39f, 0.0f);
	glVertex3f(-0.11f, 0.39f, 0.0f);
	glVertex3f(-0.11f, 0.36f, 0.0f);

	glEnd();

	glPopMatrix();

	glPopMatrix();

	//shubkamna//////////////////////////////////

	

	glPushMatrix();
	glTranslatef(-0.1f, -0.1f, 0.0f);
	glScalef(1.5f, 1.6f, 0.0f);
	{
		//shu
		glPushMatrix();
		glTranslatef(-0.1f, 0.01f, 0.0f);
		glScalef(1.0f, 1.1f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.29f, 0.18f, 0.0f);
		glVertex3f(-0.27f, 0.15f, 0.0f);
		glVertex3f(-0.08f, 0.15f, 0.0f);
		glVertex3f(-0.1f, 0.18f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.2f, 0.06f, 0.0f);
		glVertex3f(-0.19f, 0.08f, 0.0f);
		glVertex3f(-0.23f, 0.1f, 0.0f);
		glVertex3f(-0.26f, 0.1f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.23f, 0.1f, 0.0f);
		glVertex3f(-0.26f, 0.1f, 0.0f);
		glVertex3f(-0.25f, 0.15f, 0.0f);
		glVertex3f(-0.22f, 0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.21f, 0.15f, 0.0f);
		glVertex3f(-0.18f, 0.15f, 0.0f);
		glVertex3f(-0.17f, 0.11f, 0.0f);
		glVertex3f(-0.2f, 0.11f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.17f, 0.11f, 0.0f);
		glVertex3f(-0.2f, 0.11f, 0.0f);
		glVertex3f(-0.27f, 0.0f, 0.0f);
		glVertex3f(-0.27f, -0.05f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.24f, 0.02f, 0.0f);
		glVertex3f(-0.26f, 0.0f, 0.0f);
		glVertex3f(-0.28f, 0.0f, 0.0f);
		glVertex3f(-0.28f, 0.04f, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.28f, 0.01f, 0.0f);
		glVertex3f(-0.28f, 0.04f, 0.0f);
		glVertex3f(-0.29f, 0.0f, 0.0f);
		glVertex3f(-0.28f, -0.05f, 0.0f);
		glVertex3f(-0.27f, -0.05f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.26f, 0.03f, 0.0f);
		glVertex3f(-0.28f, -0.01f, 0.0f);
		glVertex3f(-0.26f, -0.09f, 0.0f);
		glVertex3f(-0.23f, -0.07f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.14f, 0.15f, 0.0f);
		glVertex3f(-0.14f, -0.08f, 0.0f);
		glVertex3f(-0.12f, -0.08f, 0.0f);
		glVertex3f(-0.12f, 0.15f, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
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
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.1f, -0.09f, 0.0f);
		glVertex3f(-0.13f, -0.11f, 0.0f);
		glVertex3f(-0.14f, -0.13f, 0.0f);
		glVertex3f(-0.11f, -0.13f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.14f, -0.13f, 0.0f);
		glVertex3f(-0.11f, -0.13f, 0.0f);
		glVertex3f(-0.18f, -0.09f, 0.0f);
		glVertex3f(-0.2f, -0.1f, 0.0f);
		glEnd();

		glPopMatrix();

		//bha
		glPushMatrix();
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glScalef(1.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, 0.15f, 0.0f);
		glVertex3f(-0.03f, -0.05f, 0.0f);
		glVertex3f(-0.01f, -0.05f, 0.0f);
		glVertex3f(-0.01f, 0.15f, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, 0.19f, 0.0f);
		glVertex3f(-0.03f, 0.15f, 0.0f);
		glVertex3f(-0.01f, 0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.06f, 0.19f, 0.0f);
		glVertex3f(-0.06f, 0.15f, 0.0f);
		glVertex3f(-0.03f, 0.15f, 0.0f);
		glVertex3f(-0.03f, 0.19f, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.06f, 0.19f, 0.0f);
		glVertex3f(-0.06f, 0.15f, 0.0f);
		glVertex3f(-0.08f, 0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.06f, 0.15f, 0.0f);
		glVertex3f(-0.08f, 0.15f, 0.0f);
		glVertex3f(-0.07f, 0.11f, 0.0f);
		glVertex3f(-0.06f, 0.11f, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.06f, 0.11f, 0.0f);
		glVertex3f(-0.07f, 0.11f, 0.0f);
		glVertex3f(-0.06f, 0.09f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.06f, 0.12f, 0.0f);
		glVertex3f(-0.06f, 0.09f, 0.0f);
		glVertex3f(-0.03f, 0.09f, 0.0f);
		glVertex3f(-0.03f, 0.12f, 0.0f);
		glEnd();

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
		glVertex3f(0.03f, 0.19f, 0.0f);
		glVertex3f(0.03f, -0.07f, 0.0f);
		glVertex3f(0.05f, -0.09f, 0.0f);
		glVertex3f(0.05f, 0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.22f, 0.0f);
		glVertex3f(0.02f, 0.19f, 0.0f);
		glVertex3f(0.7f, 0.19f, 0.0f);
		glVertex3f(0.68f, 0.22f, 0.0f);
		glEnd();

		glPopMatrix();

		//kaa
		glPushMatrix();
		glTranslatef(0.05f, 0.5f, 0.0f);
		glScalef(1.2f, 1.5f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.19f, 0.0f);
		glVertex3f(0.0f, -0.38f, 0.0f);
		glVertex3f(0.02f, -0.39f, 0.0f);
		glVertex3f(0.02f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.01f, -0.26f, 0.0f);
		glVertex3f(0.0f, -0.24f, 0.0f);
		glVertex3f(-0.02f, -0.23f, 0.0f);
		glVertex3f(-0.02f, -0.26f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, -0.23f, 0.0f);
		glVertex3f(-0.02f, -0.26f, 0.0f);
		glVertex3f(-0.03f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.31f, 0.0f);
		glVertex3f(-0.03f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.05f, -0.31f, 0.0f);
		glVertex3f(-0.03f, -0.29f, 0.0f);
		glVertex3f(-0.02f, -0.32f, 0.0f);
		glVertex3f(-0.02f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, -0.32f, 0.0f);
		glVertex3f(-0.02f, -0.34f, 0.0f);
		glVertex3f(0.0f, -0.31f, 0.0f);
		glVertex3f(0.01f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.02f, -0.24f, 0.0f);
		glVertex3f(0.02f, -0.27f, 0.0f);
		glVertex3f(0.05f, -0.25f, 0.0f);
		glVertex3f(0.05f, -0.23f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.05f, -0.25f, 0.0f);
		glVertex3f(0.05f, -0.23f, 0.0f);
		glVertex3f(0.08f, -0.28f, 0.0f);
		glVertex3f(0.06f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.08f, -0.28f, 0.0f);
		glVertex3f(0.06f, -0.28f, 0.0f);
		glVertex3f(0.04f, -0.32f, 0.0f);
		glVertex3f(0.06f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.19f, 0.0f);
		glVertex3f(0.1f, -0.37f, 0.0f);
		glVertex3f(0.12f, -0.38f, 0.0f);
		glVertex3f(0.12f, -0.19f, 0.0f);
		glEnd();

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
		glTranslatef(0.3f, 0.06f, 0.0f);
		glScalef(1.0f, 1.0f, 0.0f);

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


		//na
		glPushMatrix();
		glTranslatef(0.47f, 0.1f, 0.0f);
		glScalef(1.0f, 1.0f, 0.0f);

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.05f, 0.02f, 0.0f);
		glVertex3f(-0.07f, 0.02f, 0.0f);
		glVertex3f(-0.08f, 0.01f, 0.0f);
		glVertex3f(-0.08f, -0.01f, 0.0f);
		glVertex3f(-0.03f, -0.05f, 0.0f);
		glVertex3f(-0.02f, -0.05f, 0.0f);
		glVertex3f(-0.02f, 0.02f, 0.0f);
		glVertex3f(-0.03f, 0.02f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, 0.02f, 0.0f);
		glVertex3f(-0.03f, -0.01f, 0.0f);
		glVertex3f(0.01f, -0.01f, 0.0f);
		glVertex3f(0.01f, 0.02f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.01f, 0.11f, 0.0f);
		glVertex3f(0.01f, -0.13f, 0.0f);
		glVertex3f(0.03f, -0.15f, 0.0f);
		glVertex3f(0.03f, 0.11f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.06f, 0.11f, 0.0f);
		glVertex3f(0.06f, -0.13f, 0.0f);
		glVertex3f(0.08f, -0.15f, 0.0f);
		glVertex3f(0.08f, 0.11f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.14f, 0.06f, 0.0f);
		glVertex3f(0.12f, 0.04f, 0.0f);
		glVertex3f(0.14f, 0.02f, 0.0f);
		glVertex3f(0.16f, 0.04f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.14f, -0.04f, 0.0f);
		glVertex3f(0.12f, -0.06f, 0.0f);
		glVertex3f(0.14f, -0.08f, 0.0f);
		glVertex3f(0.16f, -0.06f, 0.0f);
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();

	//Name////////////////////////////

	glPushMatrix();
	glTranslatef(-0.1f, 0.12f, 0.0f);
	glScalef(1.4f, 1.5f, 0.0f);

	glPushMatrix();
	glTranslatef(-0.25f, 0.0f, 0.0f);
	glScalef(1.0f, 1.2f, 0.0f);
	{
		//dr letter
		glPushMatrix();
		glTranslatef(-0.2f, -0.3f, 0.0f);
		glScalef(1.0f, 1.0f, 0.0f);

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

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.43f, -0.15f, 0.0f);
		glVertex3f(-0.4f, -0.19f, 0.0f);
		glVertex3f(-0.25f, -0.19f, 0.0f);
		glVertex3f(-0.28f, -0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.36f, -0.19f, 0.0f);
		glVertex3f(-0.34f, -0.19f, 0.0f);
		glVertex3f(-0.34f, -0.22f, 0.0f);
		glVertex3f(-0.36f, -0.22f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.34f, -0.22f, 0.0f);
		glVertex3f(-0.34f, -0.25f, 0.0f);
		glVertex3f(-0.39f, -0.25f, 0.0f);
		glVertex3f(-0.39f, -0.22f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.39f, -0.22f, 0.0f);
		glVertex3f(-0.39f, -0.25f, 0.0f);
		glVertex3f(-0.4f, -0.27f, 0.0f);
		glVertex3f(-0.42f, -0.27f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.4f, -0.27f, 0.0f);
		glVertex3f(-0.42f, -0.27f, 0.0f);
		glVertex3f(-0.39f, -0.31f, 0.0f);
		glVertex3f(-0.39f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.39f, -0.31f, 0.0f);
		glVertex3f(-0.39f, -0.29f, 0.0f);
		glVertex3f(-0.37f, -0.28f, 0.0f);
		glVertex3f(-0.37f, -0.31f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.37f, -0.28f, 0.0f);
		glVertex3f(-0.37f, -0.31f, 0.0f);
		glVertex3f(-0.34f, -0.305f, 0.0f);
		glVertex3f(-0.32f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.34f, -0.305f, 0.0f);
		glVertex3f(-0.32f, -0.29f, 0.0f);
		glVertex3f(-0.3f, -0.31f, 0.0f);
		glVertex3f(-0.34f, -0.31f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.3f, -0.31f, 0.0f);
		glVertex3f(-0.33f, -0.31f, 0.0f);
		glVertex3f(-0.35f, -0.34f, 0.0f);
		glVertex3f(-0.32f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.35f, -0.34f, 0.0f);
		glVertex3f(-0.32f, -0.34f, 0.0f);
		glVertex3f(-0.37f, -0.38f, 0.0f);
		glVertex3f(-0.37f, -0.35f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.37f, -0.38f, 0.0f);
		glVertex3f(-0.37f, -0.35f, 0.0f);
		glVertex3f(-0.4f, -0.355f, 0.0f);
		glVertex3f(-0.4f, -0.375f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.4f, -0.355f, 0.0f);
		glVertex3f(-0.4f, -0.375f, 0.0f);
		glVertex3f(-0.45f, -0.34f, 0.0f);
		glVertex3f(-0.43f, -0.33f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.29f, -0.19f, 0.0f);
		glVertex3f(-0.29f, -0.38f, 0.0f);
		glVertex3f(-0.27f, -0.39f, 0.0f);
		glVertex3f(-0.27f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.2f, -0.35f, 0.0f);
		glVertex3f(-0.22f, -0.37f, 0.0f);
		glVertex3f(-0.2f, -0.39f, 0.0f);
		glVertex3f(-0.18f, -0.37f, 0.0f);
		glEnd();

		//Vijay letter

		//vi
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.1f, -0.19f, 0.0f);
		glVertex3f(-0.1f, -0.38f, 0.0f);
		glVertex3f(-0.08f, -0.39f, 0.0f);
		glVertex3f(-0.08f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.19f, 0.0f);
		glVertex3f(0.0f, -0.38f, 0.0f);
		glVertex3f(0.02f, -0.39f, 0.0f);
		glVertex3f(0.02f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.01f, -0.26f, 0.0f);
		glVertex3f(0.0f, -0.24f, 0.0f);
		glVertex3f(-0.02f, -0.23f, 0.0f);
		glVertex3f(-0.02f, -0.26f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, -0.23f, 0.0f);
		glVertex3f(-0.02f, -0.26f, 0.0f);
		glVertex3f(-0.03f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.31f, 0.0f);
		glVertex3f(-0.03f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.05f, -0.31f, 0.0f);
		glVertex3f(-0.03f, -0.29f, 0.0f);
		glVertex3f(-0.02f, -0.32f, 0.0f);
		glVertex3f(-0.02f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, -0.32f, 0.0f);
		glVertex3f(-0.02f, -0.34f, 0.0f);
		glVertex3f(0.0f, -0.31f, 0.0f);
		glVertex3f(0.01f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.15f, -0.15f, 0.0f);
		glVertex3f(-0.12f, -0.19f, 0.0f);
		glVertex3f(0.39f, -0.19f, 0.0f);
		glVertex3f(0.37f, -0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.11f, -0.15f, 0.0f);
		glVertex3f(-0.08f, -0.15f, 0.0f);
		glVertex3f(-0.09f, -0.11f, 0.0f);
		glVertex3f(-0.12f, -0.11f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.09f, -0.11f, 0.0f);
		glVertex3f(-0.12f, -0.11f, 0.0f);
		glVertex3f(-0.08f, -0.04f, 0.0f);
		glVertex3f(-0.08f, -0.08f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.08f, -0.04f, 0.0f);
		glVertex3f(-0.08f, -0.08f, 0.0f);
		glVertex3f(-0.03f, -0.1f, 0.0f);
		glVertex3f(-0.03f, -0.06f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, -0.1f, 0.0f);
		glVertex3f(-0.03f, -0.06f, 0.0f);
		glVertex3f(0.01f, -0.13f, 0.0f);
		glVertex3f(0.02f, -0.18f, 0.0f);
		glEnd();

		//ja

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.05f, -0.26f, 0.0f);
		glVertex3f(0.08f, -0.25f, 0.0f);
		glVertex3f(0.1f, -0.31f, 0.0f);
		glVertex3f(0.07f, -0.31f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.31f, 0.0f);
		glVertex3f(0.07f, -0.31f, 0.0f);
		glVertex3f(0.12f, -0.38f, 0.0f);
		glVertex3f(0.12f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.12f, -0.38f, 0.0f);
		glVertex3f(0.11f, -0.34f, 0.0f);
		glVertex3f(0.12f, -0.25f, 0.0f);
		glVertex3f(0.14f, -0.25f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.22f, 0.0f);
		glVertex3f(0.1f, -0.25f, 0.0f);
		glVertex3f(0.16f, -0.25f, 0.0f);
		glVertex3f(0.16f, -0.22f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.16f, -0.15f, 0.0f);
		glVertex3f(0.16f, -0.37f, 0.0f);
		glVertex3f(0.18f, -0.39f, 0.0f);
		glVertex3f(0.18f, -0.15f, 0.0f);
		glEnd();

		//y
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

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.27f, -0.33f, 0.0f);
		glVertex3f(0.28f, -0.37f, 0.0f);
		glVertex3f(0.33f, -0.36f, 0.0f);
		glVertex3f(0.33f, -0.3f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.33f, -0.15f, 0.0f);
		glVertex3f(0.33f, -0.4f, 0.0f);
		glVertex3f(0.35f, -0.42f, 0.0f);
		glVertex3f(0.35f, -0.15f, 0.0f);
		glEnd();

		//gokhale letter
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.46f, -0.15f, 0.0f);
		glVertex3f(0.47f, -0.19f, 0.0f);
		glVertex3f(1.05f, -0.19f, 0.0f);
		glVertex3f(1.04f, -0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.53f, -0.19f, 0.0f);
		glVertex3f(0.56f, -0.19f, 0.0f);
		glVertex3f(0.57f, -0.28f, 0.0f);
		glVertex3f(0.54f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.57f, -0.28f, 0.0f);
		glVertex3f(0.54f, -0.28f, 0.0f);
		glVertex3f(0.51f, -0.285f, 0.0f);
		glVertex3f(0.55f, -0.33f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.6f, -0.19f, 0.0f);
		glVertex3f(0.6f, -0.38f, 0.0f);
		glVertex3f(0.62f, -0.4f, 0.0f);
		glVertex3f(0.62f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.65f, -0.19f, 0.0f);
		glVertex3f(0.65f, -0.38f, 0.0f);
		glVertex3f(0.67f, -0.4f, 0.0f);
		glVertex3f(0.67f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.62f, -0.03f, 0.0f);
		glVertex3f(0.62f, -0.06f, 0.0f);
		glVertex3f(0.64f, -0.15f, 0.0f);
		glVertex3f(0.66f, -0.15f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.6f, -0.02f, 0.0f);
		glVertex3f(0.6f, -0.055f, 0.0f);
		glVertex3f(0.62f, -0.06f, 0.0f);
		glVertex3f(0.62f, -0.03f, 0.0f);
		glEnd();

		glPopMatrix();

		//kha
		glPushMatrix();
		glTranslatef(0.3f, -0.3f, 0.0f);
		glScalef(1.0f, 1.0f, 0.0f);

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

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.27f, -0.33f, 0.0f);
		glVertex3f(0.28f, -0.37f, 0.0f);
		glVertex3f(0.36f, -0.36f, 0.0f);
		glVertex3f(0.36f, -0.3f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.35f, -0.15f, 0.0f);
		glVertex3f(0.35f, -0.4f, 0.0f);
		glVertex3f(0.37f, -0.42f, 0.0f);
		glVertex3f(0.37f, -0.15f, 0.0f);
		glEnd();


		glPopMatrix();

		//Continue kha
		glPushMatrix();
		glTranslatef(0.65f, -0.27f, 0.0f);
		glScalef(1.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.01f, -0.26f, 0.0f);
		glVertex3f(0.0f, -0.24f, 0.0f);
		glVertex3f(-0.02f, -0.23f, 0.0f);
		glVertex3f(-0.02f, -0.26f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, -0.23f, 0.0f);
		glVertex3f(-0.02f, -0.26f, 0.0f);
		glVertex3f(-0.03f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.28f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.03f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.28f, 0.0f);
		glVertex3f(-0.05f, -0.31f, 0.0f);
		glVertex3f(-0.03f, -0.29f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.05f, -0.31f, 0.0f);
		glVertex3f(-0.03f, -0.29f, 0.0f);
		glVertex3f(-0.02f, -0.32f, 0.0f);
		glVertex3f(-0.02f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, -0.32f, 0.0f);
		glVertex3f(-0.02f, -0.34f, 0.0f);
		glVertex3f(0.0f, -0.31f, 0.0f);
		glVertex3f(0.01f, -0.28f, 0.0f);
		glEnd();

		//le

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.15f, -0.2f, 0.0f);
		glVertex3f(0.15f, -0.45f, 0.0f);
		glVertex3f(0.17f, -0.46f, 0.0f);
		glVertex3f(0.17f, -0.2f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.13f, -0.31f, 0.0f);
		glVertex3f(0.13f, -0.275f, 0.0f);
		glVertex3f(0.15f, -0.27f, 0.0f);
		glVertex3f(0.15f, -0.3f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.34f, 0.0f);
		glVertex3f(0.12f, -0.35f, 0.0f);
		glVertex3f(0.13f, -0.31f, 0.0f);
		glVertex3f(0.13f, -0.275f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.13f, -0.28f, 0.0f);
		glVertex3f(0.13f, -0.3f, 0.0f);
		glVertex3f(0.09f, -0.31f, 0.0f);
		glVertex3f(0.09f, -0.27f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.09f, -0.31f, 0.0f);
		glVertex3f(0.09f, -0.27f, 0.0f);
		glVertex3f(0.05f, -0.34f, 0.0f);
		glVertex3f(0.08f, -0.34f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.05f, -0.34f, 0.0f);
		glVertex3f(0.08f, -0.34f, 0.0f);
		glVertex3f(0.11f, -0.43f, 0.0f);
		glVertex3f(0.09f, -0.45f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.12f, -0.03f, 0.0f);
		glVertex3f(0.12f, -0.06f, 0.0f);
		glVertex3f(0.14f, -0.19f, 0.0f);
		glVertex3f(0.16f, -0.19f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.02f, 0.0f);
		glVertex3f(0.1f, -0.055f, 0.0f);
		glVertex3f(0.12f, -0.06f, 0.0f);
		glVertex3f(0.12f, -0.03f, 0.0f);
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.45f, -0.27f, 0.0f);
	glScalef(1.0f, 1.6f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.2f, -0.17f, 0.0f);
	glVertex3f(0.21f, -0.2f, 0.0f);
	glVertex3f(0.51f, -0.2f, 0.0f);
	glVertex3f(0.5f, -0.17f, 0.0f);
	glEnd();

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

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.25f, -0.27f, 0.0f);
	glVertex3f(0.24f, -0.3f, 0.0f);
	glVertex3f(0.35f, -0.3f, 0.0f);
	glVertex3f(0.35f, -0.27f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.35f, -0.17f, 0.0f);
	glVertex3f(0.35f, -0.35f, 0.0f);
	glVertex3f(0.38f, -0.36f, 0.0f);
	glVertex3f(0.38f, -0.17f, 0.0f);
	glEnd();

	glPopMatrix();

	//Continue of sir
	glPushMatrix();
	glTranslatef(0.65f, -0.27f, 0.0f);
	glScalef(1.0f, 1.6f, 0.0f);

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

	glPopMatrix();
}
