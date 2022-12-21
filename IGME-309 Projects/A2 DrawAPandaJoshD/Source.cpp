// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 02

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <math.h>
#include <iostream>

// the window's width and height
int width, height;

// The values that define the circle
float xPos = 5.0f;
float yPos = 5.0f;
int vertices = 50; // The number of vertices in the circle
float radius = 2.5f; // Radius of the circle


void init(void)
{
    // initialize the size of the window
    width = 600;
    height = 600;
}

void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius)
{
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < vertices; i++)
    {
        float t = (float)i / vertices * 2.0f * 3.14f;
        glVertex2f(center_x + radius * cos(t), center_y + radius * sin(t));
    }
    glEnd();
}

void drawWireframeCircle(float red, float green, float blue, float center_x, float center_y, float radius, float lineWidth)
{
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices; i++)
    {
        float t = (float)i / vertices * 2.0f * 3.14f;
        glVertex2f(center_x + radius * cos(t), center_y + radius * sin(t));
    }
    glEnd();
    glLineWidth(lineWidth);
}

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen to white, which is the background color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // PANDA ROBOT CREATION

    // Legs
    drawFilledCircle(0.5f, 0.5f, 0.55f, 5.4f, 5.3f, 0.65f);
    drawFilledCircle(0.5f, 0.5f, 0.55f, 5.55f, 4.5f, 0.6f);
    drawFilledCircle(0.5f, 0.5f, 0.55f, 5.45f, 3.9f, 0.6f);
    // Left wheel
    drawFilledCircle(0.15f, 0.15f, 0.3f, 4.65f, 2.55f, 0.6f);
    drawWireframeCircle(0.1f, 0.1f, 0.1f, 4.65f, 2.55f, 0.6f, 3.0f);
    // Right wheel
    drawFilledCircle(0.15f, 0.15f, 0.3f, 6.0f, 2.55f, 0.6f);
    drawWireframeCircle(0.1f, 0.1f, 0.1f, 6.0f, 2.55f, 0.6f, 3.0f);
    // Base
    drawFilledCircle(0.9f, 0.9f, 0.9f, 5.25f, 3.0f, 1.0f);
    // Front wheel
    drawFilledCircle(0.15f, 0.15f, 0.3f, 4.85f, 2.25f, 0.6f);
    drawWireframeCircle(0.1f, 0.1f, 0.1f, 4.85f, 2.25f, 0.6f, 3.0f);

    // Left arm
    drawFilledCircle(0.5f, 0.5f, 0.55f, 3.5f, 6.5f, 0.75f);
    drawFilledCircle(0.5f, 0.5f, 0.55f, 3.5f, 5.7f, 0.44f);
    drawFilledCircle(0.5f, 0.5f, 0.55f, 3.3f, 5.2f, 0.35f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 3.1f, 4.9f, 0.45f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 2.85f, 4.65f, 0.55f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 2.58f, 4.37f, 0.73f);

    // Ears
    drawFilledCircle(0.1f, 0.1f, 0.1f, 4.4f, 8.25f, 0.6f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 5.9f, 8.1f, 0.63f);
    // Body
    drawFilledCircle(0.9f, 0.9f, 0.9f, 5.0f, 7.0f, 1.7f);
    // Nose
    drawFilledCircle(0.1f, 0.1f, 0.1f, 4.4f, 6.1f, 0.13f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 4.5f, 6.08f, 0.13f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 4.6f, 6.1f, 0.13f);
    // Right eye
    drawFilledCircle(0.2f, 0.75f, 1.0f, 5.33f, 6.7f, 0.42f);
    drawWireframeCircle(0.1f, 0.1f, 0.1f, 5.33f, 6.7f, 0.42f, 4.0f);
    // Left eye
    drawFilledCircle(0.2f, 0.75f, 1.0f, 3.8f, 6.75f, 0.36f);
    drawWireframeCircle(0.1f, 0.1f, 0.1f, 3.8f, 6.75f, 0.36f, 5.0f);

    // Right arm
    drawFilledCircle(0.5f, 0.5f, 0.55f, 6.7f, 6.5f, 0.85f);
    drawFilledCircle(0.5f, 0.5f, 0.55f, 7.2f, 5.8f, 0.5f);
    drawFilledCircle(0.5f, 0.5f, 0.55f, 7.4f, 5.2f, 0.4f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 7.2f, 4.8f, 0.53f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 6.7f, 4.45f, 0.63f);
    drawFilledCircle(0.1f, 0.1f, 0.1f, 6.1f, 4.1f, 0.83f);

    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {
        exit(0);
    }
    
    // If the user enters the '-' key, and vertices is greater than 3, vertices will be decreased by 1
    if (key == '-') {
        if (vertices > 3)
        {
            vertices -= 1;
        }
    }

    // If the user enters the '+' or '=' key, and vertices is less than 100, vertices will be increased by 1
    if (key == '=' || key == '+') {
        if (vertices < 100)
        {
            vertices += 1;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // before create a glut window,
    // initialize stuff not opengl/glut dependent
    init();

    //initialize GLUT, let it extract command-line GLUT options that you may provide
    //NOTE that the '&' before argc
    glutInit(&argc, argv);

    // specify as double bufferred can make the display faster
    // Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //set the initial window size */
    glutInitWindowSize((int)width, (int)height);

    // create the window with a title
    glutCreateWindow("First OpenGL Program");

    /* --- register callbacks with GLUT --- */

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function that draws in the window
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    //start the glut main loop
    glutMainLoop();

    return 0;
}
