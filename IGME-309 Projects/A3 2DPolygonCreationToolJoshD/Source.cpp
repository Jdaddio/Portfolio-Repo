// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 03


// Left Click to add vertices to your polygon, Right Click to access the menu, and SPACE to complete a polygon

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include "polygon.h"
using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };

// structure for storing 3 2D vertices of a triangle
float color[3];

float mousePos[2];

vector <polygon*> polygons;
polygon* currentPoly;

void init(void)
{
    mousePos[0] = mousePos[1] = 0.0f;
    color[0] = 1.0f;
    color[1] = color[2] = 0.0f;
    currentPoly = new polygon();
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < polygons.size(); i++) // Draw all of the existing polygons in the vector
    {
        polygons[i]->draw();
    }
    currentPoly->draw(mousePos); // Draw the current polygon

    drawCursor();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

        currentPoly->addVertex(vec2(mousePos[0], mousePos[1])); // Add the vertex to the current polygon's list of vertices

        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 32: // Press SPACE to finish drawing the current polygon and begin a new polygon
        polygons.push_back(currentPoly); // Push the current polygon to the vector,
        currentPoly = new polygon(); // Then set currentPoly to a new polygon object
        break;
    }
}

void menu(int value)
{
    switch (value) {
    case 0: // clear
        delete currentPoly; // Delete the polygon object pointed to by currentPoly
        for (int i = 0; i < polygons.size(); i++) // Delete the polygon objects pointed to by the polygons vector
        {
            delete polygons[i];
        }
        polygons.clear(); // Clear polygons
        currentPoly = new polygon(); // Set currentPoly to a new polygon object
        glutPostRedisplay();
        break;
    case 1: //exit
        delete currentPoly; // Before closing, delete the polygon object pointed to by currentPoly
        for (int i = 0; i < polygons.size(); i++) // Delete the polygon objects pointed to by the polygons vector
        {
            delete polygons[i];
        }
        exit(0);
    case 2: // red
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 3: // green
        color[0] = 0.0f;
        color[1] = 1.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 4: // blue
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
        glutPostRedisplay();
        break;
    default:
        break;
    }
    currentPoly->setColor(color); // After changing the color in the menu, setColor sets the color in the polygon object
}
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Mouse Event - draw polygons");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    // Clear the memory used by currentPoly and polygons at the end of the program
    delete currentPoly; 
    for (int i = 0; i < polygons.size(); i++)
    {
        delete polygons[i];
    }
    return 0;


}
