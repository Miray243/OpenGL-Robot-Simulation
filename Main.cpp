#include <GL/glut.h>
#include "Scene.h"

Scene* scene;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->draw();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
    scene->update();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    scene->handleKeyboard(key, x, y);
}

void special(int key, int x, int y) {
    scene->handleSpecialKeys(key, x, y);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Virtual Exhibition Hall");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    scene = new Scene();
    scene->init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special); // Ok tuşları için
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
