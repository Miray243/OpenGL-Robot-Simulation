#include "Room.h"
#include <GL/gl.h>

namespace {
    void setMaterial(GLfloat difX, GLfloat difY, GLfloat difZ,
                     GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 50.0f) {
        GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
        GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess[] = {shine};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
    }
}

Room::Room() : wallTextureID(0), floorTextureID(0) {
}

void Room::draw() {
    GLfloat left_x = -2.6f;
    GLfloat right_x = 8.0f;
    GLfloat floor_y = -1.0f;
    GLfloat ceil_y = 5.1f;
    GLfloat back_z = 0.5f;
    GLfloat front_z = 15.0f;
    GLfloat wall_thickness = 0.2f;

    GLfloat room_width = right_x - left_x;
    GLfloat room_height = ceil_y - floor_y;
    GLfloat room_depth = front_z - back_z;

    glPushMatrix();
    glTranslatef(left_x, floor_y, back_z);
    glScalef(room_width / 3.0f, room_height / 3.0f, wall_thickness / 3.0f);
    setMaterial(1, 0.8, 0.7, 0.5, 0.4, 0.35);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);
    cubeDrawer.draw();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(left_x - wall_thickness, floor_y, back_z);
    glScalef(wall_thickness / 3.0f, room_height / 3.0f, room_depth / 3.0f);
    setMaterial(1, 0.8, 0.7, 0.5, 0.4, 0.35);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);
    cubeDrawer.draw();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(right_x, floor_y, back_z);
    glScalef(wall_thickness / 3.0f, room_height / 3.0f, room_depth / 3.0f);
    setMaterial(1, 0.8, 0.7, 0.5, 0.4, 0.35);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);
    cubeDrawer.draw();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(left_x - wall_thickness, ceil_y, back_z);
    glScalef((room_width + wall_thickness * 2) / 3.0f, wall_thickness / 3.0f, room_depth / 3.0f);
    setMaterial(1.0, 0.9, 0.8, 0.5, 0.45, 0.4);
    cubeDrawer.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(left_x - wall_thickness, floor_y - wall_thickness, back_z);
    glScalef((room_width + wall_thickness * 2) / 3.0f, wall_thickness / 3.0f, room_depth / 3.0f);
    setMaterial(0.5, 0.1, 0.0, 0.25, 0.05, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTextureID);
    cubeDrawer.draw();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}