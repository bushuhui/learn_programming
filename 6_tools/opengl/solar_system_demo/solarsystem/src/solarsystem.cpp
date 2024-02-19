#include "solarsystem.h"

SolarSystem::SolarSystem()
{
	
}

void SolarSystem::calculatePositions(float time)
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].calculatePosition(time);
	}
}

void SolarSystem::addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

void SolarSystem::addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets[planetIndex].addMoon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}


void SolarSystem::render()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].render();
	}
}


void SolarSystem::renderOrbits()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].renderOrbit();
	}
}

void SolarSystem::getPlanetPosition(int index, float* vec)
{
	planets[index].getPosition(vec);
}

void SolarSystem::setWireShape(bool b){
    for(auto& p:planets){
        p.wireShape = b;
    }
}
