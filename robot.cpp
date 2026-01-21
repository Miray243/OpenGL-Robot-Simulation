#include "Robot.h"
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Robot::Robot(float x, float z, float size)
    : x(x), z(z), size(size), orientationY(0.0f), wheelAngle(0.0f),
      armLiftAngle(0.0f), scanAngle(0.0f), scanning(false), laserTimer(0.0f) {}

void Robot::update() {
    wheelAngle += 5.0f;
    if (wheelAngle > 360.0f) wheelAngle -= 360.0f;

    scanAngle = sin(glutGet(GLUT_ELAPSED_TIME) / 400.0f) * 20.0f;

    if (scanning) {
        laserTimer += 0.05f;
        armLiftAngle = sin(glutGet(GLUT_ELAPSED_TIME) / 300.0f) * 12.0f;
    }
    else {
        armLiftAngle = 0.0f;
    }
}

void Robot::move(float dx_dt, float dz_dt)
{
    if (dx_dt != 0.0f || dz_dt != 0.0f) {
        orientationY = atan2(dx_dt, dz_dt) * 180.0f / M_PI;
    }
    x += dx_dt;
    z += dz_dt;
}

void Robot::scan(bool enable) {
    scanning = enable;
    if (enable) laserTimer = 0.0f;
}

void Robot::draw() {
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -0.0f * size);

    float vibX = scanning ? sin(glutGet(GLUT_ELAPSED_TIME) / 80.0f) * 0.005f : 0.0f;
    float vibrationY = scanning ? sin(glutGet(GLUT_ELAPSED_TIME) / 50.0f) * 0.01f : 0.0f;

    glTranslatef(x + vibX, -1.0f + (size * 0.3f) + vibrationY, z);

    glRotatef(orientationY, 0.0f, 1.0f, 0.0f);

    GLfloat robot_ambient[]  = { 0.4f, 0.2f, 0.0f, 1.0f };
    GLfloat robot_diffuse[]  = { 1.0f, 0.5f, 0.0f, 1.0f };
    GLfloat robot_specular[] = { 0.7f, 0.7f, 0.5f, 1.0f };
    GLfloat robot_shininess[] = { 32.0f };
    GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, robot_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, robot_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, robot_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, robot_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

    drawBase();
    drawWheels();
    drawArm();

    glPopMatrix();
}

void Robot::drawBase() {
    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
    glScalef(size * 0.4f, size * 0.4f, size * 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Robot::drawWheels() {
    glColor3f(0.2f, 0.2f, 0.2f);
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * size * 0.25f, -size * 0.2f, j * size * 0.25f);
            glRotatef(wheelAngle, 1, 0, 0);
            glutSolidSphere(size * 0.1f, 20, 20);
            glPopMatrix();
        }
    }
}

void Robot::drawArm() {
    glPushMatrix();
    glTranslatef(0.0f, size * 0.2f, 0.0f);
    glRotatef(armLiftAngle, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glColor3f(0.8f, 0.2f, 0.2f);
    glScalef(size * 0.05f, size * 0.5f, size * 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glTranslatef(0.0f, size * 0.25f, 0.0f);
    drawScannerHead();
    glPopMatrix();
}

void Robot::drawScannerHead() {
    glPushMatrix();
    glRotatef(scanAngle, 1.0f, 0.0f, 0.0f);
    glColor3f(0.9f, 0.9f, 0.2f);
    glutSolidSphere(size * 0.05f, 20, 20);
    if (scanning) drawLaser();
    glPopMatrix();
}

void Robot::drawLaser() {
    float angleRad = 20.0f * 3.14159f / 180.0f;
    float reach = 1.0f * size;
    float alpha = 0.3f + 0.2f * sinf(laserTimer * 5.0f);
    float r = 1.0f - laserTimer;
    float g = laserTimer;

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(r, g, 0.0f, alpha);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
        glVertex3f(0, 0, 0);
        glVertex3f(reach * cosf(angleRad), 0, reach * sinf(angleRad));
        glVertex3f(reach * cosf(-angleRad), 0, reach * sinf(-angleRad));
    glEnd();

    drawGlow(alpha);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Robot::drawGlow(float intensity) {
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 0.0f, intensity);
    glutSolidSphere(size * 0.06f, 10, 10);
    glPopMatrix();
}
