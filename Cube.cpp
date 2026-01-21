// main.cpp
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Senin yüklediğin dosyaların başlıkları
#include "Robot.h"
#include "Room.h"
#include "Light.h"
#include "ObjModel.h"

// --- Global Değişkenler ---
Robot* robot;
Room* room;
Light* mainLight;
ObjModel* tableModel; // Örnek bir obje

// Kamera Değişkenleri
float camAngleX = 0.0f;
float camAngleY = 0.0f;
float camDist = 15.0f;
int lastMouseX, lastMouseY;
bool mouseDown = false;

// --- Pencere Boyutlandırma ---
void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// --- Çizim Fonksiyonu ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamerayı ayarla (Orbit camera)
    float camX = camDist * sin(camAngleX * 0.01f) * cos(camAngleY * 0.01f);
    float camY = camDist * sin(camAngleY * 0.01f);
    float camZ = camDist * cos(camAngleX * 0.01f) * cos(camAngleY * 0.01f);
    
    // Kameranın her zaman odanın merkezine bakmasını sağla
    gluLookAt(camX, camY + 2.0f, camZ, 
              0.0f, 1.0f, 0.0f, 
              0.0f, 1.0f, 0.0f);

    // Işığı uygula
    mainLight->apply();
    mainLight->drawFixture(); // Işığın kendisini (lambayı) çiz
    mainLight->drawBeamEffect(); // Işık huzmesini çiz

    // Odayı çiz
    room->draw();

    // Robotu çiz
    robot->draw();

    // Varsa 3D modeli çiz (Örn: masa)
    // glPushMatrix();
    // glTranslatef(2.0f, 0.0f, 2.0f); // Konum
    // tableModel->draw();
    // glPopMatrix();

    glutSwapBuffers();
}

// --- Animasyon ve Güncelleme ---
void timer(int v) {
    robot->update(); // Robotun tekerleklerini ve animasyonunu günceller
    glutPostRedisplay(); // Ekranı tekrar çiz
    glutTimerFunc(16, timer, 0); // 60 FPS
}

// --- Klavye Kontrolü ---
void keyboard(unsigned char key, int x, int y) {
    float speed = 0.2f;
    
    switch (key) {
        case 'w': case 'W': robot->move(-speed, 0); break; // İleri (X ekseninde)
        case 's': case 'S': robot->move(speed, 0); break;  // Geri
        case 'a': case 'A': robot->move(0, -speed); break; // Sol
        case 'd': case 'D': robot->move(0, speed); break;  // Sağ
        case ' ': robot->scan(!robot->scanning); break;    // Lazer aç/kapa
        case 'l': case 'L': mainLight->toggle(); break;    // Işık aç/kapa
        case 27: exit(0); break; // ESC ile çıkış
    }
}

// --- Mouse Kontrolü (Kamera için) ---
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            mouseDown = false;
        }
    }
}

void motion(int x, int y) {
    if (mouseDown) {
        camAngleX += (x - lastMouseX);
        camAngleY += (y - lastMouseY);
        
        // Kamera açısını sınırla (takla atmaması için)
        if (camAngleY > 89.0f) camAngleY = 89.0f;
        if (camAngleY < -89.0f) camAngleY = -89.0f;

        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

// --- Başlangıç Ayarları ---
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Nesneleri Oluştur
    robot = new Robot(0.0f, 0.0f, 1.0f); // Merkezde bir robot
    room = new Room();
    
    // Işık Oluştur (Tavana asılı spot ışık)
    // ID, x, y, z, amb, diff, spec...
    mainLight = new Light(GL_LIGHT0, 0.0f, 4.0f, 0.0f, 
                          0.2f, 0.2f, 0.2f,  // Ambient
                          0.8f, 0.8f, 0.8f,  // Diffuse
                          1.0f, 1.0f, 1.0f,  // Specular
                          true);             // Spot ışık mı? Evet.

    // .obj modeli yükleme denemesi (Dosya yoksa hata vermez, sadece çizmez)
    tableModel = new ObjModel();
    // tableModel->load("masa.obj"); // Dosya varsa burayı açabilirsin
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robot Simulation Room");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(0, timer, 0);

    std::cout << "Kontroller:\nW,A,S,D: Robotu Hareket Ettir\nSPACE: Tarama Modu (Lazer)\nL: Isigi Ac/Kapa\nMouse Sol Tik: Kamerayi Cevir" << std::endl;

    glutMainLoop();
    return 0;
}