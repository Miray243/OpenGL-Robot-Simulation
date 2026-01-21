#ifndef ROOM_H
#define ROOM_H

#include <GL/glut.h>
#include "Cube.h"
#include <string>

class Room {
public:
    Room();
    void draw();

    void setWallTextureID(GLuint id) { wallTextureID = id; }
    void setFloorTextureID(GLuint id) { floorTextureID = id; }

private:
    Cube cubeDrawer;

    GLuint wallTextureID;
    GLuint floorTextureID;
};

#endif // ROOM_H