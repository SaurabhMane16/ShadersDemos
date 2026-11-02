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

GLuint texture_mahajaiapadas = 0;

/*
BOOL loadGLTexture(GLuint* tex, TCHAR imageResourceID[])
{
	//Variable Declarations
	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	//code
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		printf("Load image == failed");
		return FALSE;
	}

	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glGenTextures(1, tex);

	glBindTexture(GL_TEXTURE_2D, *tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	DeleteObject(hBitmap);
	return TRUE;
}


*/

void firstMap(void)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_mahajaiapadas);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.8f, 1.2f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.8f, 1.2f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.8f, -1.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.8f, -1.2f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}

