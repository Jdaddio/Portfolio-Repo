// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 05

#include "Bullet.h"

Bullet::Bullet(float posX, float posY, float direction)
{
    // initialize the bullet with the given position
    position[0] = posX;
    position[1] = posY;

    // set the color of the bullet
    color[0] = 1.0f;
    color[1] = 0.0f;
    color[2] = 0.0f;

    vertices = 20;

    radius = 0.1f;

    lifetime = 0.0f; // used to track how long the bullet has been alive
    maxLifetime = 2.0f; // max lifetime of the bullet
    angle = (direction + 90) * (M_PI/180); // set the angle of the bullet's forward movement
}
Bullet::~Bullet()
{

}

void Bullet::draw() // draws the bullet as a circular polygon
{
    glColor3fv(color);

    glBegin(GL_POLYGON);
    for (int i = 0; i < vertices; i++)
    {
        float t = (float)i / vertices * 2.0f * 3.14f;
        glVertex2f(position[0] + radius * cos(t), position[1] + radius * sin(t));
    }
    glEnd();
}

void Bullet::update(float deltaTime) // updates the bullet's X and Y position, and tracks how long the bullet has been alive
{
    position[0] = position[0] + cos(angle) * 3 * deltaTime;
    position[1] = position[1] + sin(angle) * 3 * deltaTime;
    lifetime += deltaTime;
}

bool Bullet::checkCollision(float x2, float y2, float r2) // check to see if the bullet has collided with the target circle
{
    // determine the distance between the two circles' centers
    float xDistance = powf(position[0] - x2, 2.0f);
    float yDistance = powf(position[1] - y2, 2.0f);

    // if the distance is smaller than the radii of the circles, return true
    if (sqrt(xDistance + yDistance) < (radius + r2))
    {
        return true;
    }
    else
    {
        return false;
    }
}