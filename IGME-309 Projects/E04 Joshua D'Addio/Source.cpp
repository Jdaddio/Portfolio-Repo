#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif


// the window's width and height
int width, height;

float eyePos[3] = {20.0f, 20.0f, -20.0f};
float lookAtPos[3] = { 0.0f, 0.0f, 0.0f };
float nearPlane = 0.1f;
float farPlane = 1000.0f;
float FOV = 45.0f;
float aspectOfProjection = 2.0f;

void init(void)
{
    // initialize the size of the window
    width = 600 * aspectOfProjection;
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
    // glLoadIdentity();

    // Procedurally create the lines in the grid
    glBegin(GL_LINES);
    for (int i = 0; i <= 25; i++)
    {
        glVertex3f(-12.5f, 0.0f, i -12.5f);
        glVertex3f(12.5f, 0.0f, i -12.5f);

        glVertex3f(i -12.5f, 0.0f, -12.5f);
        glVertex3f(i -12.5f, 0.0f, 12.5f);
        if (i == 12)
        {
            glColor3f(0.0, 0.0, 0.0);
        }
        else
        {
            glColor3f(0.7, 0.7, 0.7);
        }
    }
    glEnd();
    glLineWidth(1.0f);

    glPopMatrix();

    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyePos[0], eyePos[1], eyePos[2], lookAtPos[0], lookAtPos[1], lookAtPos[2], 0, 1, 0);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(FOV, w/h, nearPlane, farPlane);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

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

    //start the glut main loop
    glutMainLoop();

    return 0;
}
