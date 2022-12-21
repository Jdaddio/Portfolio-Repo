// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 04

//Usage:
// Use W and S to select the parts of the robot
// Use A and D to rotate the selected robot part

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

#define MAX_NUM_CIRCLE 16
#define CIRCLE_RADIUM 2.0

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;

bool keyStates[256];
int buttonState;
float vertex[2]; // Used to plug into glVertex2fv to draw the polygons
float color[3] = {0, 0, 0}; // Keeps track of the colors of the polygons
float rotations[MAX_NUM_CIRCLE];

int selected = 0; // Used to keep track of what polygon is selected

void init(void)
{
    for (int i = 0; i < MAX_NUM_CIRCLE; i++) {

        rotations[i] = 0.0f;
    }
    rotations[4] = -90;
    rotations[7] = 90;

    buttonState = -1;
}

void drawPoly(float width, float height, float color[3]) // Draws a 4 sided polygon with specified width, height and color from local origin
{
    glColor3fv(color);
    glBegin(GL_POLYGON);
        
    // First vertex
    vertex[0] = width / 2;
    vertex[1] = 0;
    glVertex2fv(vertex);
    // Second vertex
    vertex[0] = -width / 2;
    glVertex2fv(vertex);
    // Third vertex
    vertex[1] = height;
    glVertex2fv(vertex);
    //Fourth vertex
    vertex[0] = width / 2;
    glVertex2fv(vertex);

    glEnd();
}
void setColor(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    int id = -1; // the index of current circle

    // Waist (main body)
    id = 0;
    glPushMatrix(); // Push the main body
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 0) { setColor(1.0f, 0.0f, 0.0f); } 
    else { setColor(0.0f, 0.4f, 0.6f); }
    drawPoly(2.0f, -2.0f, color);

    // Chest
    id = 1;
    glPushMatrix(); // Push the chest
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 1) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 1.0f); }
    drawPoly(3.0f, 2.0f, color);

    // Neck
    id = 2;
    glPushMatrix(); // Push the neck
    glTranslatef(0.0f, 2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 2) { setColor(1.0f, 0.0f, 0.0f); }
    else{ setColor(0.0f, 1.0f, 0.0f); }
    drawPoly(0.5f, 0.5f, color);

    // Head
    id = 3;
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 3) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 0.0f); }
    drawPoly(2.0f, 2.0f, color);

    glPopMatrix(); // Pop back to the chest

    // Right Shoulder
    id = 4;
    glPushMatrix(); // Push the right shoulder
    glTranslatef(-1.5f, 1.5f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 4) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 0.0f); }
    drawPoly(1.0f, -2.0f, color);

    // Right Forearm
    id = 5;
    glPushMatrix(); // Push the right forearm
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 5) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 0.8f, 0.2f); }
    drawPoly(1.0f, -2.0f, color);

    // Right Hand
    id = 6;
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 6) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 0.0f); }
    drawPoly(1.5f, -1.5f, color);

    glPopMatrix(); // Pop back to the right shoulder
    glPopMatrix(); // Pop back to the chest

    // Left Shoulder
    id = 7;
    glPushMatrix(); // Push the left shoulder
    glTranslatef(1.5f, 1.5f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 7) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 0.0f); }
    drawPoly(1.0f, -2.0f, color);

    // Left Forearm
    id = 8;
    glPushMatrix(); // Push the left forearm
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 8) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 0.8f, 0.2f); }
    drawPoly(1.0f, -2.0f, color);

    // Left Hand
    id = 9;
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 9) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 0.0f); }
    drawPoly(1.5f, -1.5f, color);

    glPopMatrix(); // Pop back to the left shoulder
    glPopMatrix(); // Pop back to the chest
    glPopMatrix(); // Pop back to the waist

    // Right Leg
    id = 10;
    glPushMatrix(); // Push the right leg
    glTranslatef(-0.6f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 10) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 0.2f, 0.8f); }
    drawPoly(0.8f, -2.0f, color);

    // Right Knee
    id = 11;
    glPushMatrix(); // Push the right knee
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 11) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 0.3f, 0.9f); }
    drawPoly(0.8f, -2.0f, color);

    // Right Foot
    id = 12;
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 12) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 1.0f); }
    drawPoly(1.1f, -1.5f, color);

    glPopMatrix(); // Pop back to the right knee
    glPopMatrix(); // Pop back to the waist

    // Left Leg
    id = 13;
    glPushMatrix(); // Push the left leg
    glTranslatef(0.6f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 13) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 0.2f, 0.8f); }
    drawPoly(0.8f, -2.0f, color);

    // Left Knee
    id = 14;
    glPushMatrix(); // Push the left knee
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 14) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 0.3f, 0.9f); }
    drawPoly(0.8f, -2.0f, color);

    // Left Foot
    id = 15;
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotations[id], 0.0f, 0.0f, 1.0f);
    if (selected == 15) { setColor(1.0f, 0.0f, 0.0f); }
    else { setColor(0.0f, 1.0f, 1.0f); }
    drawPoly(1.1f, -1.5f, color);

    glPopMatrix(); // Pop back to the left knee
    glPopMatrix(); // Pop back to the waist
    glPopMatrix(); // Pop off the waist (done)
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) // WASD are used to select and control the robot's parts
{
    if (key == 27) // 'esc' key
        exit(0);

    if (key == 'w') // 'W' key - changes selection +
    {
        if (selected < 15) { selected = selected + 1; }
        else  {  selected = 0;  }
    }
    if (key == 's') // 'S' key - changes selection -
    {
        if (selected > 0) { selected--; }
        else { selected = 15; }
    }
    if (key == 'a') // 'A' key - rotates + 5
    {
        rotations[selected] = rotations[selected] + 5.0f;
    }
    if (key == 'd') // 'D' key - rotates - 5
    {
        rotations[selected] = rotations[selected] - 5.0f;
    }
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) // WASD are used to select and control the robot's parts
{
    if (key == 87) // 'W' key - changes selection +
    {
        if (selected < 15) { selected = selected + 1; }
        else { selected = 0; }
    }
    if (key == 83) // 'S' key - changes selection -
    {
        if (selected > 0) { selected--; }
        else { selected = 15; }
    }
    if (key == 65) // 'A' key - rotates + 5
    {
        rotations[selected] = rotations[selected] + 5.0f;
    }
    if (key == 68) // 'D' key - rotates - 5
    {
        rotations[selected] = rotations[selected] - 5.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}
