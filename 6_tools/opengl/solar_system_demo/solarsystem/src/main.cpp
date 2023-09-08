#include <cmath>
#include <cstdlib>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "tga.h"
#include "solarsystem.h"
#include "camera.h"
#include "globals.h"
using namespace std;
int screenWidth, screenHeight;
int view = -1;
TGA *stars, * moon;
int planetSelected = 1;

SolarSystem solarSystem;

Camera camera;

double _time;
double timeSpeed;

struct ControlStates
{
	bool forward, backward, left, right, yawLeft, yawRight, pitchUp,
		pitchDown, rollLeft, rollRight;
} controls;


void timer(int)
{
	glutPostRedisplay(); // post for display func
	glutTimerFunc(10, timer, 0); // limit frame drawing to 100fps
}

float random(float max)
{
	return (float)(std::rand() % 1000) * max * 0.001;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	
	// set up lighting
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat matShininess[] = { 20.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// Load all image data
    stars = new TGA("../images/stars.tga");
    moon = new TGA("../images/moon.tga");
    TGA* flag = new TGA("../images/flag.tga");

    TGA* sun = new TGA("../images/sun.tga");
    TGA* mercury = new TGA("../images/mercury.tga");
    TGA* venus = new TGA("../images/venus.tga");
    TGA* earth = new TGA("../images/earth.tga");
    TGA* mars = new TGA("../images/mars.tga");
    TGA* jupiter = new TGA("../images/jupiter.tga");
    TGA* saturn = new TGA("../images/saturn.tga");
    TGA* uranus = new TGA("../images/uranus.tga");
    TGA* neptune = new TGA("../images/neptune.tga");
    TGA* pluto = new TGA("../images/pluto.tga");

	// Add all the planets with accurate data. Distance measured in km, time measured in earth days.
	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureHandle()); // sun
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureHandle()); // mercury
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureHandle()); // venus
	solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureHandle()); // earth
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureHandle()); // mars
	solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureHandle()); // jupiter
	solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureHandle()); // saturn
	solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureHandle()); // uranus
	solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureHandle()); // neptune
	solarSystem.addPlanet(5906380000, 90616, 6.39, 1137, pluto->getTextureHandle()); // pluto

    solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureHandle());
    _time = 2.552f;
	timeSpeed = 0.1f;

	// reset controls
	controls.forward = false;
	controls.backward = false;
	controls.left = false;
	controls.right = false;
	controls.rollRight = false;
	controls.rollLeft = false;
	controls.pitchDown = false;
	controls.pitchUp = false;
	controls.yawLeft = false;
	controls.yawRight = false;

	timer(0);
}

void drawCube(void);

void isWireShape(int value){
    switch (value) {
    case 0:
        solarSystem.setWireShape(false);
        break;
    case 1:
        solarSystem.setWireShape(true);
        break;
    default:
        solarSystem.setWireShape(false);
        break;
    }
}

void setView(int value){
    view = value;
    if(view == -1){
        camera = Camera();
    }
    else{
        float lookatposition[3]={0.0f,0.0f,0.0f};
        solarSystem.getPlanetPosition(view,lookatposition);
        float r;
        solarSystem.getRadius(view,&r);
        float position[3]={lookatposition[0]+0.00001f,lookatposition[1],lookatposition[2]+10*r};
        camera.setPosition(position);
        camera.pointAt(lookatposition);
    }
}

void nothingToDo(int value){}

void display(void)
{
    _time += timeSpeed;
    solarSystem.calculatePositions(_time);

	if (controls.forward) camera.forward();		if (controls.backward) camera.backward();
	if (controls.left) camera.left();			if (controls.right) camera.right();
	if (controls.yawLeft) camera.yawLeft();		if (controls.yawRight) camera.yawRight();
	if (controls.rollLeft) camera.rollLeft();	if (controls.rollRight) camera.rollRight();
	if (controls.pitchUp) camera.pitchUp();		if (controls.pitchDown) camera.pitchDown();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    if(view != -1 && false){
        float lookatposition[3]={0.0f,0.0f,0.0f};
        solarSystem.getPlanetPosition(view,lookatposition);
        float position[3]={lookatposition[0],lookatposition[1],lookatposition[2]};
        camera.setPosition(position);
        camera.pointAt(lookatposition);
    }
    else{
        camera.transformOrientation();

        glBindTexture(GL_TEXTURE_2D, stars->getTextureHandle());
        drawCube();

        camera.transformTranslation();
    }
	GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	solarSystem.render();
	glDisable(GL_LIGHTING);

    solarSystem.renderOrbits();

    glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) screenWidth, (GLdouble) screenHeight, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glFlush();
	glutSwapBuffers();
}
void keyDown(unsigned char key, int x, int y)
{
	if (key > '0' && key <= '9')
	{
		float vec[3];
		solarSystem.getPlanetPosition(key - '0', vec);
		camera.pointAt(vec);
		planetSelected = key - '0';
	}
	switch (key)
	{
	case '-':
        timeSpeed /= 2.0f;
		break;
	case '=':
        timeSpeed *= 2.0f;
        break;

    case 'w':
		controls.forward = true;
		break;
	case 's':
		controls.backward = true;
		break;
	case 'a':
		controls.left = true;
		break;
	case 'd':
		controls.right = true;
		break;
	case 'l':
		controls.rollRight = true;
		break;
	case 'j':
		controls.rollLeft = true;
		break;
	case 'i':
		controls.pitchDown = true;
		break;
	case 'k':
		controls.pitchUp = true;
		break;
	case 'q':
		controls.yawLeft = true;
		break;
	case 'e':
		controls.yawRight = true;
		break;
	}

}

void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		controls.forward = false;
		break;
	case 's':
		controls.backward = false;
		break;
	case 'a':
		controls.left = false;
		break;
	case 'd':
		controls.right = false;
		break;
	case 'l':
		controls.rollRight = false;
		break;
	case 'j':
		controls.rollLeft = false;
		break;
	case 'i':
		controls.pitchDown = false;
		break;
	case 'k':
		controls.pitchUp = false;
		break;
	case 'q':
		controls.yawLeft = false;
		break;
	case 'e':
		controls.yawRight = false;
		break;
	}
}

void reshape(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

    int nWireMenu;
    int nPlanetMenu;
    int nMainMenu;
    // Create the Menu
    nWireMenu = glutCreateMenu(isWireShape);
    glutAddMenuEntry("True",1);
    glutAddMenuEntry("False",0);

    nPlanetMenu = glutCreateMenu(setView);
    glutAddMenuEntry("All",-1);
    glutAddMenuEntry("Sun",0);
    glutAddMenuEntry("Mercury",1);
    glutAddMenuEntry("Venus",2);
    glutAddMenuEntry("Earth",3);
    glutAddMenuEntry("Mars",4);
    glutAddMenuEntry("Jupiter",5);
    glutAddMenuEntry("Saturn",6);
    glutAddMenuEntry("Uranus",7);
    glutAddMenuEntry("Neptune",8);
    glutAddMenuEntry("Pluto",9);

    nMainMenu = glutCreateMenu(nothingToDo);
    glutAddSubMenu("Wire", nWireMenu);
    glutAddSubMenu("View", nPlanetMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}

void drawCube(void)
{
	glBegin(GL_QUADS);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}
