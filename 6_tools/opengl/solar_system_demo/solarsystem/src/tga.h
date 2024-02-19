#ifndef TGA_H
#define TGA_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

class TGA
{
private:
	GLuint textureHandle;
public:
	TGA(char* imagePath);

	GLuint getTextureHandle(void);
};

#endif
