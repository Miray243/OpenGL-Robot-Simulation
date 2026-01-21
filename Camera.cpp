#include "Camera.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

Camera::Camera() {
    mode = FOLLOW;
    posX = 0.0f; posY = 5.0f; posZ = 10.0f;
    yaw = -90.0f; pitch = -20.0f;
    distanceToRobot = 8.0f;
}

void Camera::toggleMode() {
    mode = (mode == FREE) ? FOLLOW : FREE;
}

void Camera::update(Robot* robot) {
    if (mode == FOLLOW && robot != nullptr) {
        // Robotun arkasında ve biraz yukarısında dur
        float angleRad = (robot->orientationY + 90.0f) * M_PI / 180.0f; // Arkasından bakması için +90
        
        float targetX = robot->x - distanceToRobot * cos(angleRad);
        float targetZ = robot->z - distanceToRobot * sin(angleRad);
        
        // Yumuşak geçiş (basit lineer interpolasyon)
        posX += (targetX - posX) * 0.1f;
        posZ += (targetZ - posZ) * 0.1f;
        posY = 4.0f; // Yükseklik sabit

        // Robotun olduğu yere bak
        yaw = -robot->orientationY - 90.0f; 
        pitch = -15.0f;
    }
}

void Camera::apply() {
    glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-yaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-posX, -posY, -posZ);
}

void Camera::moveForward(float amount) {
    if (mode == FREE) {
        float rad = yaw * M_PI / 180.0f;
        posX += cos(rad) * amount; // Sin/Cos yerleşimi OpenGL koordinatlarına göre
        posZ += sin(rad) * amount;
    }
}

void Camera::moveRight(float amount) {
    if (mode == FREE) {
        float rad = (yaw + 90.0f) * M_PI / 180.0f;
        posX += cos(rad) * amount;
        posZ += sin(rad) * amount;
    }
}

void Camera::rotateYaw(float angle) {
    if (mode == FREE) yaw += angle;
}

void Camera::rotatePitch(float angle) {
    if (mode == FREE) pitch += angle;
}
