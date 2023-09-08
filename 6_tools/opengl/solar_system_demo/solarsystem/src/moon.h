#ifndef MOON_H
#define MOON_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

class Moon
{
private:
	float distanceFromPlanet;

	float orbitTime;

	float rotationTime;

	float radius;

	GLuint textureHandle;

	float position[3];
	float rotation;

public:
	Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	void calculatePosition(float time);

	void render(void);

	void renderOrbit(void);
};
#endif
