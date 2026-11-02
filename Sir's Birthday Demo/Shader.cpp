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


void Shader(void)
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
	glTranslatef(0.30f, -0.65f, 0.0f);
	glScalef(2.2f, 2.2f, 1.0f);

	glBegin(GL_QUADS);

	// 1)

	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f(-0.80f, 0.30f, 0.0f);
	glVertex3f(-0.80f, 0.40f, 0.0f);
	glVertex3f(-0.77f, 0.40f, 0.0f);
	glVertex3f(-0.77f, 0.30f, 0.0f);

	// 2)

	glVertex3f(-0.80f, 0.40f, 0.0f);
	glVertex3f(-0.80f, 0.37f, 0.0f);
	glVertex3f(-0.70f, 0.37f, 0.0f);
	glVertex3f(-0.70f, 0.40f, 0.0f);

	// 3)

	glVertex3f(-0.70f, 0.40f, 0.0f);
	glVertex3f(-0.70f, 0.20f, 0.0f);
	glVertex3f(-0.67f, 0.20f, 0.0f);
	glVertex3f(-0.67f, 0.40f, 0.0f);

	// 4)

	glVertex3f(-0.80f, 0.33f, 0.0f);
	glVertex3f(-0.80f, 0.30f, 0.0f);
	glVertex3f(-0.70f, 0.30f, 0.0f);
	glVertex3f(-0.70f, 0.33f, 0.0f);

	// 5)

	glVertex3f(-0.80f, 0.25f, 0.0f);
	glVertex3f(-0.80f, 0.20f, 0.0f);
	glVertex3f(-0.75f, 0.20f, 0.0f);
	glVertex3f(-0.75f, 0.25f, 0.0f);

	// 6)

	glVertex3f(-0.80f, 0.23f, 0.0f);
	glVertex3f(-0.80f, 0.20f, 0.0f);
	glVertex3f(-0.70f, 0.20f, 0.0f);
	glVertex3f(-0.70f, 0.23f, 0.0f);

	// 7)

	glVertex3f(-0.78f, 0.20f, 0.0f);
	glVertex3f(-0.75f, 0.20f, 0.0f);
	glVertex3f(-0.70f, 0.10f, 0.0f);
	glVertex3f(-0.73f, 0.10f, 0.0f);

	// 8)

	glVertex3f(-0.63f, 0.40f, 0.0f);
	glVertex3f(-0.63f, 0.10f, 0.0f);
	glVertex3f(-0.60f, 0.10f, 0.0f);
	glVertex3f(-0.60f, 0.40f, 0.0f);

	// 9)

	glVertex3f(-0.40f, 0.40f, 0.0f);
	glVertex3f(-0.40f, 0.34f, 0.0f);
	glVertex3f(-0.37f, 0.34f, 0.0f);
	glVertex3f(-0.37f, 0.40f, 0.0f);

	// 10)

	glVertex3f(-0.53f, 0.34f, 0.0f);
	glVertex3f(-0.53f, 0.24f, 0.0f);
	glVertex3f(-0.50f, 0.24f, 0.0f);
	glVertex3f(-0.50f, 0.34f, 0.0f);

	// 11)

	glVertex3f(-0.53f, 0.37f, 0.0f);
	glVertex3f(-0.53f, 0.34f, 0.0f);
	glVertex3f(-0.40f, 0.34f, 0.0f);
	glVertex3f(-0.40f, 0.37f, 0.0f);

	// 12 )

	glVertex3f(-0.53f, 0.24f, 0.0f);
	glVertex3f(-0.53f, 0.21f, 0.0f);
	glVertex3f(-0.35f, 0.21f, 0.0f);
	glVertex3f(-0.35f, 0.24f, 0.0f);

	// 13)

	glVertex3f(-0.38f, 0.21f, 0.0f);
	glVertex3f(-0.38f, 0.10f, 0.0f);
	glVertex3f(-0.35f, 0.10f, 0.0f);
	glVertex3f(-0.35f, 0.21f, 0.0f);

	// 14)

	glVertex3f(-0.53f, 0.13f, 0.0f);
	glVertex3f(-0.53f, 0.10f, 0.0f);
	glVertex3f(-0.35f, 0.10f, 0.0f);
	glVertex3f(-0.35f, 0.13f, 0.0f);

	// 15)

	glVertex3f(-0.28f, 0.40f, 0.0f);
	glVertex3f(-0.24f, 0.40f, 0.0f);
	glVertex3f(-0.16f, 0.33f, 0.0f);
	glVertex3f(-0.20f, 0.33f, 0.0f);

	// 16)

	glVertex3f(-0.20f, 0.33f, 0.0f);
	glVertex3f(-0.20f, 0.25f, 0.0f);
	glVertex3f(-0.17f, 0.25f, 0.0f);
	glVertex3f(-0.17f, 0.33f, 0.0f);

	// 17)

	glVertex3f(-0.28f, 0.25f, 0.0f);
	glVertex3f(-0.27f, 0.28f, 0.0f);
	glVertex3f(-0.16f, 0.10f, 0.0f);
	glVertex3f(-0.19f, 0.10f, 0.0f);

	// 18)

	glVertex3f(-0.28f, 0.28f, 0.0f);
	glVertex3f(-0.28f, 0.25f, 0.0f);
	glVertex3f(-0.20f, 0.25f, 0.0f);
	glVertex3f(-0.20f, 0.28f, 0.0f);

	// 19)

	glVertex3f(-0.73f, 0.60f, 0.0f);
	glVertex3f(-0.70f, 0.60f, 0.0f);
	glVertex3f(-0.60f, 0.43f, 0.0f);
	glVertex3f(-0.63f, 0.43f, 0.0f);

	// 20)

	glVertex3f(-0.75f, 0.60f, 0.0f);
	glVertex3f(-0.75f, 0.57f, 0.0f);
	glVertex3f(-0.70f, 0.57f, 0.0f);
	glVertex3f(-0.70f, 0.60f, 0.0f);

	// 21)

	glVertex3f(-0.90f, 0.43f, 0.0f);
	glVertex3f(-0.90f, 0.40f, 0.0f);
	glVertex3f(-0.10f, 0.40f, 0.0f);
	glVertex3f(-0.10f, 0.43f, 0.0f);




	glEnd();

	glPopMatrix();

	glColor3f(0.5f, 0.0f, 0.0f); // golden brown line

	glLineWidth(15.0f);

	glPushMatrix();
	glTranslatef(0.25f, -0.75f, 0.0f);
	glScalef(2.5f, 2.5f, 0.5f);

	glBegin(GL_LINES);

	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.2f, 0.3f, 0.0f);


	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.3f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.4f, 0.0f);

	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.33f, 0.34f, 0.0f);

	glVertex3f(0.33f, 0.34f, 0.0f);
	glVertex3f(0.33f, 0.3f, 0.0f);

	glVertex3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.25f, 0.3f, 0.0f);

	glVertex3f(0.25f, 0.3f, 0.0f);
	glVertex3f(0.34f, 0.2f, 0.0f);
	glVertex3f(0.4f, 0.2f, 0.0f);
	glVertex3f(0.4f, 0.31f, 0.0f);

	glVertex3f(0.4f, 0.31f, 0.0f);
	glVertex3f(0.5f, 0.31f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.15f, 0.0f);

	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.15f, 0.0f);

	glVertex3f(0.45f, 0.15f, 0.0f);
	glVertex3f(0.5f, 0.15f, 0.0f);
	glVertex3f(0.5f, 0.15f, 0.0f);
	glVertex3f(0.42f, 0.1f, 0.0f);

	glVertex3f(0.42f, 0.1f, 0.0f);
	glVertex3f(0.37f, 0.15f, 0.0f);
	glVertex3f(0.55f, 0.2f, 0.0f);
	glVertex3f(0.55f, 0.31f, 0.0f);

	glVertex3f(0.55f, 0.31f, 0.0f);
	glVertex3f(0.65f, 0.31f, 0.0f);
	glVertex3f(0.65f, 0.4f, 0.0f);
	glVertex3f(0.65f, 0.2f, 0.0f);

	glVertex3f(0.05f, 0.4f, 0.0f);
	glVertex3f(0.7f, 0.4f, 0.0f);


	glEnd();

	glPopMatrix();
}

/*

void update(void)
{
	//code
}

void uninitialize(void)
{
	//code
	// if exiting in full screen first restore and then proceed
	if (bFullscreen == TRUE)
	{
		toggleFullScreen();
		bFullscreen = FALSE;
	}

	//first check the current contex and if it is then unmake it
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
		
	}

	//Destroy the rendering contex
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//release the device contex
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//destroy window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;

	}

	//Close Log File
	if (gpFile)
	{
		fprintf(gpFile, "SHS : Program Terminated Successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
*/