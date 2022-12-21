// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 03

#include "polygon.h"

polygon::polygon()
{
    color[0] = 1.0f;
    color[1] = 0.0f;
    color[2] = 0.0f;
}
polygon::~polygon()
{

}

void polygon::addVertex(vec2 p_vert)
{
    vertices.push_back(p_vert);
}

void polygon::setColor(float p_color[3])
{
    color[0] = p_color[0];
    color[1] = p_color[1];
    color[2] = p_color[2];
}

unsigned int polygon::getVertNum()
{
    return vertices.size();
}

void polygon::draw()
{
    glColor3fv(color);

    glBegin(GL_POLYGON);
    for (int i = 0; i < vertices.size(); i++)
    {
        glVertex2fv(new float[2]{ vertices[i].x, vertices[i].y });
    }
    glEnd();
}

void polygon::draw(float mousePos[2])
{
    glColor3fv(color);

    if (vertices.size() == 1) // If the polygon has only one vertex, draw the line between that vertex and the mouse position
    {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < vertices.size(); i++)
        {
            glVertex2fv(new float[2]{ vertices[i].x, vertices[i].y });
        }
        glVertex2fv(mousePos);
        glEnd();
    }
    if (vertices.size() > 1) // If the polygon has more than one vertex, draw the polygon formed
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++)
        {
            glVertex2fv(new float[2]{ vertices[i].x, vertices[i].y });
        }
        glVertex2fv(mousePos);
        glEnd();
    }

}