// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 05

#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class Bullet {
private:
    float position[2];
    float angle;
    float color[3];
    int vertices;
    float radius;
public:
    float lifetime;
    float maxLifetime;

    Bullet(float posX, float posY, float direction);
    ~Bullet();
    void draw();
    void update(float deltaTime);
    bool checkCollision(float x2, float y2, float r2);
};