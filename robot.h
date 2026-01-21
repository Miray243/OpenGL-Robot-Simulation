#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    float x, z;
    float size;
    float orientationY;

    float wheelAngle;
    float armLiftAngle;
    float scanAngle;

    bool scanning;

    Robot(float x = 0.0f, float z = 0.0f, float size = 1.0f);

    void update();
    void scan(bool enable);

    void draw();
    void move(float dx, float dz);

private:
    void drawBase();
    void drawWheels();
    void drawArm();
    void drawScannerHead();
    void drawLaser();
    void drawGlow(float intensity);

    float laserTimer;
};

#endif