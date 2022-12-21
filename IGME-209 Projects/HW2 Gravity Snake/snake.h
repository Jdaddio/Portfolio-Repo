#pragma once

void update(b2World& world);
void display(b2Body* snake, float targetX, float targetY);
void applyForces(b2Body* snake, int key);
void moveTarget(float& xPos, float& yPos);