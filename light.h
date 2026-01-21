#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

class Light {
private:
    GLenum id;
    GLfloat position[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat no_light[4];
    GLfloat spot_direction[3];
    GLfloat spot_cutoff;
    GLfloat spot_exponent;
    bool is_spotlight;
    bool is_fixed_no_bulb;
    GLfloat bulb_diffuse[4];
    GLfloat bulb_emission[4];
    bool is_on;
    bool ambient_on;
    bool diffuse_on;
    bool specular_on;
    GLfloat visual_beam_radius_local;

public:
    Light(GLenum light_id,
          GLfloat pos_x, GLfloat pos_y, GLfloat pos_z,
          GLfloat amb_r, GLfloat amb_g, GLfloat amb_b,
          GLfloat diff_r, GLfloat diff_g, GLfloat diff_b,
          GLfloat spec_r, GLfloat spec_g, GLfloat spec_b,
          bool is_spot = false,
          GLfloat spot_dir_x = 0.0f,
          GLfloat spot_dir_y = -1.0f,
          GLfloat spot_dir_z = 0.0f,
          GLfloat cutoff = 45.0f,
          GLfloat exponent = 0.0f,
          bool fixed_no_bulb = false,
          GLfloat initial_visual_beam_radius_local = 3.0f);

    void apply();
    void drawFixture();
    void drawBeamEffect();
    void setVisualBeamRadiusLocal(GLfloat radius);
    void toggle();
    void toggleAmbient();
    void toggleDiffuse();
    void toggleSpecular();
    bool isOn() const { return is_on; }
    GLenum getID() const { return id; }
    void setSpotDirection(GLfloat dir_x, GLfloat dir_y, GLfloat dir_z);
    void turnOn();
    void turnOff();
};

#endif // LIGHT_H