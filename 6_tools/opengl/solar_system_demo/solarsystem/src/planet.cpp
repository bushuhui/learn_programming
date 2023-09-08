#include "planet.h"
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "globals.h"

float planetSizeScale = 0.000005f;

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

void Planet::calculatePosition(float time)
{
	float angle = time * 3.1419f / orbitTime;
	
	position[0] = sin(angle) * distanceFromSun;
	position[1] = cos(angle) * distanceFromSun;
	position[2] = 0;

	rotation = time * 360 / rotationTime;

	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].calculatePosition(time);
	}

}

void Planet::render(void)
{
	glPushMatrix();

	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].render();
	}

	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

    if(wireShape){
        if (distanceFromSun < 0.001f)
        {
            float radiusScaled = radius * planetSizeScale;
            if (radiusScaled > 0.5f) radiusScaled = 0.5f;

            glDisable(GL_LIGHTING);
            glutWireSphere(radiusScaled,30,30);
            glEnable(GL_LIGHTING);
        }
        else
        {
            glutWireSphere(radius * planetSizeScale,30,30);
        }
    }
    else{
        if (distanceFromSun < 0.001f)
        {
            float radiusScaled = radius * planetSizeScale;
            if (radiusScaled > 0.5f) radiusScaled = 0.5f;

            glDisable(GL_LIGHTING);
            gluSphere(quadric, radiusScaled, 30, 30);
            glEnable(GL_LIGHTING);
        }
        else
        {
            gluSphere(quadric, radius * planetSizeScale, 30, 30);
        }
    }


	glPopMatrix();
}

void Planet::renderOrbit(void)
{
	glBegin(GL_LINE_STRIP);
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f)
	{
		glVertex3f(sin(angle) * distanceFromSun * distanceScale, cos(angle) * distanceFromSun * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, distanceFromSun * distanceScale, 0.0f);
	
	glEnd();

	glPushMatrix();
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].renderOrbit();
	}
	glPopMatrix();

}


void Planet::getPosition(float* vec)
{
	vec[0] = position[0] * distanceScale;
	vec[1] = position[1] * distanceScale;
	vec[2] = position[2] * distanceScale;
}

float Planet::getRadius(void)
{
    return radius*planetSizeScale;
}

void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}
