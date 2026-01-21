#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include "Robot.h"

class Camera {
public:
    enum Mode { FREE, FOLLOW };

    Camera();
    void update(Robot* robot);
    void apply();
    void toggleMode();
    
    // Serbest kamera kontrolleri
    void moveForward(float amount);
    void moveRight(float amount);
    void rotateYaw(float angle);
    void rotatePitch(float angle);

private:
    Mode mode;
    float posX, posY, posZ;    // Kamera pozisyonu
    float yaw, pitch;          // Bakış açıları
    float distanceToRobot;     // Takip mesafesi
};

#endif
