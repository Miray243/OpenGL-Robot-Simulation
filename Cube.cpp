// Cube.cpp
#include "Cube.h"
#include <GL/glut.h>

void Cube::draw() {
    // 1 birimlik standart bir küp çizer.
    // Room.cpp içinde glScalef ile boyutlandırıldığı için bu yeterlidir.
    glutSolidCube(1.0f); 
}
