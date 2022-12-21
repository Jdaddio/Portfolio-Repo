// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 05

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <math.h>
#include <iostream>
#include "Bullet.h"

using namespace std;

// Window's width and height
int width, height;

// global parameters defining the target circle
float targetColor[3]; // color of the target circle
int targetVertNum = 20; // total number of vertices for the target circle
float targetX = 0.0f, targetY = 1.5f; // center postion of the target circle
float targetR = 0.2f; // target circle's radius
int targetHits = 30; // target circle's health

// global parameters defining the cannon
float cannonColor[3]; // color of the cannon
int bodyVertNum = 20; // total number of vertices for the body
float bodyX = 0.0f, bodyY = -3.0f; // center postion of the body
float bodyR = 0.4f; // body's radius
float moveSpeed = 0.0f; // movement speed of the body
float angle = 0.0f; // angle of the cannon launcher
float rotSpeed = 0.0f; // speed of the cannon's rotation

// define the y value of the floor
float floor_y = -3.0f;

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;

// vector containing pointers to the created bullet objects
vector<Bullet*> bullets;

void init(void)
{
	// initialize the size of the window
	width = 600;
	height = 600;

	// set the target's color
	targetColor[0] = 0.2f;
	targetColor[1] = 0.0f;
	targetColor[2] = 0.0f;

	// set the cannon color
	cannonColor[0] = 0.5f;
	cannonColor[1] = 0.5f;
	cannonColor[2] = 0.0f;

	// create a random seed for target location
	srand(time(0));
	targetX = rand() % 7 - 3.5;
	targetY = rand() % 4;
}

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw the bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw();
	}

	// draw the target circle
	glColor3f(targetColor[0], targetColor[1], targetColor[2]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < targetVertNum; ++i) {
		float t = (float)i / targetVertNum * 2.0f * 3.14f;
		glVertex2f(targetX + targetR * cos(t), targetY + targetR * sin(t));
	}
	glEnd();

	// draw the cannon 
	glPushMatrix(); // push the matrix so that the translation and rotation are applied to both the body and the launcher
	glTranslatef(bodyX, bodyY, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	// draw the cannon body
	glColor3f(cannonColor[0], cannonColor[1], cannonColor[2]);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < bodyVertNum; ++i) {
		float t = (float)i / bodyVertNum * 2.0f * 3.14f;
		glVertex2f(0.0f + bodyR * cos(t), 0.0f+ bodyR * sin(t));
	}
	glEnd();

	// draw the cannon launcher
	glLineWidth(3);
	glColor3f(cannonColor[0], cannonColor[1], cannonColor[2]);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
	glLineWidth(1);

	glPopMatrix(); // pop the matrix when the cannon is finished

	// use GL_LINES to draw the floor 
	glLineWidth(3);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-2.0f, floor_y);
	glVertex2f(2.0f, floor_y);
	glEnd();
	glLineWidth(1);

	glutSwapBuffers();
}

// when a target is hit by a bullet, increase the target's radius, change its color, and decrease its health
void hitTarget() 
{
	targetR = targetR + 0.025f;
	targetColor[0] += 0.026f;
	targetHits -= 1;
	// when a target's health is fully depleted, recreate it in a new random location with its base radius, color and health values
	if (targetHits <= 0) 
	{
		targetR = 0.2f;
		targetColor[0] = 0.2f;
		targetHits = 30;
		targetX = rand() % 7 - 3.5;
		targetY = rand() % 4;
	}
}
void update()
{
	curTime = glutGet(GLUT_ELAPSED_TIME); // returns the number of milliseconds since glutInit() was called.
	float deltaTime = (float)(curTime - preTime) / 1000.0f; // frame-different time in seconds 

	// if the cannon's position is in range, or if it is moving back into range, then change the body's X position
	if (bodyX > -2 && bodyX < 2) { bodyX += moveSpeed * deltaTime; }
	else if (bodyX <= -2 && moveSpeed > 0) { bodyX += moveSpeed * deltaTime; }
	else if (bodyX >= 2 && moveSpeed < 0) { bodyX += moveSpeed * deltaTime; }

	// if the cannon's rotation is in range, or if it is moving back into range, then change the launcher's rotation
	if (angle > -90 && angle < 90) { angle += rotSpeed * deltaTime; }
	else if (angle <= -90 && rotSpeed > 0) { angle += rotSpeed * deltaTime; }
	else if (angle >= 90 && rotSpeed < 0) { angle += rotSpeed * deltaTime; }

	// update each of the bullets in the vector
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update(deltaTime);
	}
	// check the bullets to see if they have collided with the target or expired, and delete and erase the bullets that have
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->checkCollision(targetX, targetY, targetR))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			hitTarget();
			break;
		}
		if (bullets[i]->lifetime >= bullets[i]->maxLifetime)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			break;
		}
	}

	preTime = curTime; // make the curTime become the preTime for the next frame
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	width = w;
	height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // exit the program
	{
		// delete the full vector of bullets to prevent leaks
		for (int i = 0; i < bullets.size(); i++)
		{
			delete bullets[i];
		}
		exit(0);
	}
	if (key == 'a') { moveSpeed = -5.0f; } // move left
	if (key == 'd') { moveSpeed = 5.0f; } // move right
	if (key == 'k') { rotSpeed = 90.0f; } // rotate counterclockwise
	if (key == 'l') { rotSpeed = -90.0f; } // rotate clockwise
	// create a new bullet object at the tip of the cannon's launcher
	if (key == ' ') { bullets.push_back(new Bullet(bodyX + cos((angle + 90) * M_PI/180), bodyY + sin((angle + 90) * M_PI / 180), angle)); }
}
void keyboardUp(unsigned char key, int x, int y)
{
	// when a key is not being pressed, set the rotation and movement speeds to 0
	moveSpeed = 0.0f;
	rotSpeed = 0.0f;
}

int main(int argc, char* argv[])
{
	init();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize((int)width, (int)height);

	// create the window with a title
	glutCreateWindow("Ball Bounces at Constant Speed");

	/* --- register callbacks with GLUT --- */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(update);

	//start the glut main loop
	glutMainLoop();

	// delete the full vector of bullets to prevent leaks
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	return 0;
}
