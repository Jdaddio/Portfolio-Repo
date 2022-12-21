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

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen to white, which is the background color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // specify the color for drawing
    glColor3f(1.0, 0.0, 0.0);

    // Draw the circle using a for loop
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices; i++)
    {
        float t = (float)i / vertices * 2.0f * 3.14f;
        glVertex2f(xPos + radius * cos(t), yPos + radius * sin(t));
    }
    glEnd();

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
