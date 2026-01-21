#ifndef SCENE_H
#define SCENE_H

#include "Robot.h"
#include "Room.h"
#include "Light.h"
#include "ObjModel.h"
#include "Camera.h"
#include <vector>

class Scene {
public:
    Scene();
    ~Scene();

    void init();
    void draw();
    void update();
    void handleKeyboard(unsigned char key, int x, int y);
    void handleSpecialKeys(int key, int x, int y);

private:
    Robot* robot;
    Room* room;
    Light* mainLight;
    Camera* camera;
    
    // Modeller için vector (list) kullanıyoruz
    std::vector<ObjModel*> models;
};

#endif