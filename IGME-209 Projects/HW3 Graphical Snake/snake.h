#pragma once

void update(b2World& world);
void display(b2Body* snake, float targetX, float targetY);
void applyForces(b2Body* snake, int key);
void moveTarget(float& xPos, float& yPos);

//hw3 Graphical Snake functions
void processInput(b2Body& player);
void ApplyForceUp(b2Body& player);
void ApplyForceDown(b2Body& player);
void ApplyForceLeft(b2Body& player);
void ApplyForceRight(b2Body& player);
void StopMoving(b2Body& player);
void ReverseGravity(b2World& world);
void setupTargets(int cnt);
bool selectNextTarget();
