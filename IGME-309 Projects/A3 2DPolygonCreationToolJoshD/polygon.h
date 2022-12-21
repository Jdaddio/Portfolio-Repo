// Course: IGME 309-02
// Student Name: Joshua D'Addio
// Assignment Number: 03

#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace glm;
using namespace std;

class polygon {
private:
    vector <vec2> vertices;
    float color[3];
public:
    polygon();
    ~polygon();
    void addVertex(vec2 p_vert);
    void setColor(float color[3]);
    unsigned int getVertNum();
    void draw();
    void draw(float mousePos[2]);
};