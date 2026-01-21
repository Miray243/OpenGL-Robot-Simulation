#include "Scene.h"
#include <GL/glut.h>
#include <iostream>

Scene::Scene() {
    robot = new Robot(0.0f, 0.0f, 1.0f);
    room = new Room();
    camera = new Camera();
    
    // Spot ışık (Tavanda)
    mainLight = new Light(GL_LIGHT0, 0.0f, 4.5f, 0.0f, 
                          0.3f, 0.3f, 0.3f, 
                          0.9f, 0.9f, 0.9f, 
                          1.0f, 1.0f, 1.0f, 
                          true); 
}

Scene::~Scene() {
    delete robot;
    delete room;
    delete mainLight;
    delete camera;
    for(auto m : models) delete m;
}

void Scene::init() {
    // Varsa modelleri burada yükle
    // ObjModel* table = new ObjModel();
    // if(table->load("table.obj")) models.push_back(table);
}

void Scene::update() {
    robot->update();
    camera->update(robot); // Kamera robotu takip etsin
}

void Scene::draw() {
    // Önce kamerayı ayarla
    glLoadIdentity();
    camera->apply();

    // Işığı güncelle
    mainLight->apply();
    mainLight->drawFixture();
    mainLight->drawBeamEffect();

    // Odayı çiz
    room->draw();

    // Robotu çiz
    robot->draw();

    // Diğer modelleri çiz
    for(auto m : models) {
        m->draw();
    }
}

void Scene::handleKeyboard(unsigned char key, int x, int y) {
    float speed = 0.2f;
    switch (key) {
        case 'w': case 'W': 
            if(camera->Mode::FREE) camera->moveForward(speed);
            else robot->move(speed, 0); 
            break;
        case 's': case 'S': 
            if(camera->Mode::FREE) camera->moveForward(-speed);
            else robot->move(-speed, 0); 
            break;
        case 'a': case 'A': 
            if(camera->Mode::FREE) camera->moveRight(-speed);
            else robot->move(0, -speed); 
            break;
        case 'd': case 'D': 
            if(camera->Mode::FREE) camera->moveRight(speed);
            else robot->move(0, speed); 
            break;
        case ' ': robot->scan(!robot->scanning); break;
        case 'l': case 'L': mainLight->toggle(); break;
        case 'f': case 'F': camera->toggleMode(); break; // Kamera modu değiştir
        case 27: exit(0); break; // ESC
    }
}

void Scene::handleSpecialKeys(int key, int x, int y) {
    // Ok tuşları ile kamerayı döndür (Sadece Free modda)
    switch(key) {
        case GLUT_KEY_LEFT: camera->rotateYaw(-2.0f); break;
        case GLUT_KEY_RIGHT: camera->rotateYaw(2.0f); break;
        case GLUT_KEY_UP: camera->rotatePitch(-2.0f); break;
        case GLUT_KEY_DOWN: camera->rotatePitch(2.0f); break;
    }
}