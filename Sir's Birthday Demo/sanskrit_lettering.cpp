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
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLU32.lib")

 GLuint texture_Quote_SM = 0;

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


void drawSanskritQuote(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);   // 2D dimensions

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Disable depth write so the background quad does not block 3D geometry
	glDepthMask(GL_FALSE);

	glColor3f(1.0f, 1.0f, 1.0f); // Ensure texture isn't tinted
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_Quote_SM);

	glBegin(GL_QUADS);
	// Bottom-Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	// Bottom-Right
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);

	// Top-Right
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);

	// Top-Left
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);

	// Re-enable depth 
	glDepthMask(GL_TRUE);
	// Restore original matrices 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

