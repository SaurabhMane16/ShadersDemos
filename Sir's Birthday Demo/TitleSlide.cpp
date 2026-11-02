// Header Files 
#include <windows.h>
#include <stdio.h> //for file I/O
#include <stdlib.h> // for exit

// OpenGL related header files
#include <gl/GL.h>  // includes GL.h inside gl directory
#include <gl/GLU.h>

// link with openGL import library
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLU32.lib")

extern GLuint texture_background;

/*
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

*/

void Title(void)
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

	glPushMatrix();
	glTranslatef(0.1f, -0.35f, 0.0f);
	glScalef(2.5f, 2.0f, 0.0f);
	{

		glPushMatrix();
		glTranslatef(0.1f, -0.12f, 0.0f);
		glScalef(1.1f, 1.6f, 0.0f);
		{

			glPushMatrix();
			glTranslatef(0.0f, -0.75f, 0.0f);
			glScalef(1.1f, 1.3f, 0.0f);
			{

				glPushMatrix();
				glColor3f(0.7f, 0.0f, 0.2f);

				glTranslatef(-0.85f, 1.0f, 0.0f);
				glScalef(0.9f, 0.9f, 0.0f);

				glBegin(GL_QUADS);
				glVertex3f(0.46f, -0.16f, 0.0f);
				glVertex3f(0.47f, -0.19f, 0.0f);
				glVertex3f(0.8f, -0.19f, 0.0f);
				glVertex3f(0.79f, -0.16f, 0.0f);
				glEnd();

				glBegin(GL_QUADS);
				glVertex3f(0.53f, -0.19f, 0.0f);
				glVertex3f(0.56f, -0.19f, 0.0f);
				glVertex3f(0.57f, -0.28f, 0.0f);
				glVertex3f(0.54f, -0.28f, 0.0f);
				glEnd();

				glBegin(GL_QUADS);
				glVertex3f(0.57f, -0.28f, 0.0f);
				glVertex3f(0.54f, -0.28f, 0.0f);
				glVertex3f(0.51f, -0.285f, 0.0f);
				glVertex3f(0.55f, -0.33f, 0.0f);
				glEnd();

				glBegin(GL_QUADS);
				glVertex3f(0.6f, -0.19f, 0.0f);
				glVertex3f(0.6f, -0.39f, 0.0f);
				glVertex3f(0.62f, -0.39f, 0.0f);
				glVertex3f(0.62f, -0.19f, 0.0f);
				glEnd();

				glPopMatrix();

				glPushMatrix();
				glTranslatef(-0.17f, 0.74f, 0.0f);
				glScalef(1.0f, 1.0f, 0.0f);

				glBegin(GL_POLYGON);
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
				glVertex3f(-0.1f, -0.09f, 0.0f);
				glVertex3f(-0.13f, -0.11f, 0.0f);
				glVertex3f(-0.14f, -0.13f, 0.0f);
				glVertex3f(-0.11f, -0.13f, 0.0f);
				glEnd();

				glBegin(GL_QUADS);
				glVertex3f(-0.14f, -0.13f, 0.0f);
				glVertex3f(-0.11f, -0.13f, 0.0f);
				glVertex3f(-0.18f, -0.09f, 0.0f);
				glVertex3f(-0.2f, -0.1f, 0.0f);
				glEnd();

				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.43f, 0.6f, 0.0f);
			glScalef(0.8f, 1.4f, 0.0f);

			glBegin(GL_QUADS);
			glVertex3f(0.25f, -0.19f, 0.0f);
			glVertex3f(0.28f, -0.19f, 0.0f);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.25f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0.29f, -0.25f, 0.0f);
			glVertex3f(0.26f, -0.23f, 0.0f);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.23f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0.2f, -0.27f, 0.0f);
			glVertex3f(0.25f, -0.28f, 0.0f);
			glVertex3f(0.28f, -0.33f, 0.0f);
			glVertex3f(0.28f, -0.37f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.215f, 0.51f, 0.0f);
			glScalef(0.7f, 1.0f, 0.0f);

			glBegin(GL_QUADS);
			glVertex3f(0.02f, -0.24f, 0.0f);
			glVertex3f(0.02f, -0.27f, 0.0f);
			glVertex3f(0.05f, -0.25f, 0.0f);
			glVertex3f(0.05f, -0.23f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0.05f, -0.25f, 0.0f);
			glVertex3f(0.05f, -0.23f, 0.0f);
			glVertex3f(0.08f, -0.28f, 0.0f);
			glVertex3f(0.06f, -0.28f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0.08f, -0.28f, 0.0f);
			glVertex3f(0.06f, -0.28f, 0.0f);
			glVertex3f(0.04f, -0.32f, 0.0f);
			glVertex3f(0.06f, -0.34f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.08f, 0.08f, 0.0f);
		glScalef(1.2f, 1.35f, 0.0f);
		{

			glPushMatrix();
			glTranslatef(-0.08f, 0.08f, 0.0f);
			glScalef(1.2f, 1.75f, 0.0f);
			{
				glPushMatrix();
				glTranslatef(0.0f, 0.26f, 0.0f);
				glScalef(0.8f, 0.8f, 0.0f);

				//m
				glBegin(GL_QUADS);
				glVertex3f(0.18f, -0.19f, 0.0f);
				glVertex3f(0.18f, -0.33f, 0.0f);
				glVertex3f(0.2f, -0.33f, 0.0f);
				glVertex3f(0.2f, -0.19f, 0.0f);
				glEnd();

				glBegin(GL_QUADS);
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
				glVertex3f(-0.01f, 0.02f, 0.0f);
				glVertex3f(-0.01f, -0.01f, 0.0f);
				glVertex3f(0.03f, -0.01f, 0.0f);
				glVertex3f(0.03f, 0.02f, 0.0f);
				glEnd();

				glBegin(GL_QUADS);
				glVertex3f(0.03f, 0.15f, 0.0f);
				glVertex3f(0.03f, -0.1f, 0.0f);
				glVertex3f(0.05f, -0.12f, 0.0f);
				glVertex3f(0.05f, 0.15f, 0.0f);
				glEnd();

				glPopMatrix();

			}
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.3f, 0.65f, 0.0f);
			glScalef(0.7f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glVertex3f(-0.2f, -0.35f, 0.0f);
			glVertex3f(-0.22f, -0.37f, 0.0f);
			glVertex3f(-0.2f, -0.39f, 0.0f);
			glVertex3f(-0.18f, -0.37f, 0.0f);
			glEnd();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.13f, 0.05f, 0.0f);
			glScalef(0.9f, 0.9f, 0.0f);

			glBegin(GL_QUADS);
			glVertex3f(0.2f, 0.24f, 0.0f);
			glVertex3f(0.2f, -0.11f, 0.0f);
			glVertex3f(0.22f, -0.13f, 0.0f);
			glVertex3f(0.22f, 0.24f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0.1f, 0.16f, 0.0f);
			glVertex3f(0.2f, 0.08f, 0.0f);
			glVertex3f(0.2f, 0.04f, 0.0f);
			glVertex3f(0.1f, 0.12f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0.2f, 0.08f, 0.0f);
			glVertex3f(0.2f, 0.04f, 0.0f);
			glVertex3f(0.1f, -0.08f, 0.0f);
			glVertex3f(0.1f, -0.03f, 0.0f);
			glEnd();

			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
