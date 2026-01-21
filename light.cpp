#include "Light.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

Light::Light(GLenum light_id,
             GLfloat pos_x, GLfloat pos_y, GLfloat pos_z,
             GLfloat amb_r, GLfloat amb_g, GLfloat amb_b,
             GLfloat diff_r, GLfloat diff_g, GLfloat diff_b,
             GLfloat spec_r, GLfloat spec_g, GLfloat spec_b,
             bool is_spot,
             GLfloat spot_dir_x, GLfloat spot_dir_y, GLfloat spot_dir_z,
             GLfloat cutoff, GLfloat exponent,
             bool fixed_no_bulb_param,
             GLfloat initial_visual_beam_radius_local)
{
    this->id = light_id;
    this->position[0] = pos_x; this->position[1] = pos_y; this->position[2] = pos_z; this->position[3] = 1.0f;
    this->ambient[0]  = amb_r; this->ambient[1]  = amb_g; this->ambient[2]  = amb_b; this->ambient[3]  = 1.0f;
    this->diffuse[0]  = diff_r; this->diffuse[1]  = diff_g; this->diffuse[2]  = diff_b; this->diffuse[3]  = 1.0f;
    this->specular[0] = spec_r; this->specular[1] = spec_g; this->specular[2] = spec_b; this->specular[3] = 1.0f;
    this->is_spotlight = is_spot;
    this->spot_direction[0] = spot_dir_x;
    this->spot_direction[1] = spot_dir_y;
    this->spot_direction[2] = spot_dir_z;
    this->spot_cutoff = cutoff;
    this->spot_exponent = exponent;
    this->is_fixed_no_bulb = fixed_no_bulb_param;
    this->visual_beam_radius_local = initial_visual_beam_radius_local;

    if (this->is_fixed_no_bulb) {
        this->is_on = true;
        this->ambient_on = true;
        this->diffuse_on = true;
        this->specular_on = true;
    } else {
        this->is_on = false;
        this->ambient_on = false;
        this->diffuse_on = false;
        this->specular_on = false;
    }

    this->no_light[0] = 0.0f; this->no_light[1] = 0.0f; this->no_light[2] = 0.0f; this->no_light[3] = 1.0f;
    this->bulb_diffuse[0] = 1.000f; this->bulb_diffuse[1] = 0.843f; this->bulb_diffuse[2] = 0.000f; this->bulb_diffuse[3] = 1.0f;
    this->bulb_emission[0] = 1.0f;  this->bulb_emission[1] = 1.0f;   this->bulb_emission[2] = 1.0f;   this->bulb_emission[3] = 1.0f;
}

void Light::apply()
{
    GLenum err;
    auto printErrorIfAny = [&](const std::string& step_name) {
    };

    if (!is_on) {
        while (glGetError() != GL_NO_ERROR) {}
        glDisable(id);
        if ((err = glGetError()) != GL_NO_ERROR) {
        }
        return;
    }

    while (glGetError() != GL_NO_ERROR) {}
    glEnable(id);
    if ((err = glGetError()) != GL_NO_ERROR) {
    }

    while (glGetError() != GL_NO_ERROR) {}
    glLightfv(id, GL_AMBIENT,  ambient_on  ? ambient  : no_light);
    if ((err = glGetError()) != GL_NO_ERROR) {
    }

    while (glGetError() != GL_NO_ERROR) {}
    glLightfv(id, GL_DIFFUSE,  diffuse_on  ? diffuse  : no_light);
    if ((err = glGetError()) != GL_NO_ERROR) {
    }

    while (glGetError() != GL_NO_ERROR) {}
    glLightfv(id, GL_SPECULAR, specular_on ? specular : no_light);
    if ((err = glGetError()) != GL_NO_ERROR) {
    }

    while (glGetError() != GL_NO_ERROR) {}
    glLightfv(id, GL_POSITION, position);
    if ((err = glGetError()) != GL_NO_ERROR) {
    }

    if (is_spotlight) {
        while (glGetError() != GL_NO_ERROR) {}
        glLightfv(id, GL_SPOT_DIRECTION, spot_direction);
        if ((err = glGetError()) != GL_NO_ERROR) {
        }

        while (glGetError() != GL_NO_ERROR) {}
        glLightf(id, GL_SPOT_CUTOFF, spot_cutoff);
        if ((err = glGetError()) != GL_NO_ERROR) {
        }

        while (glGetError() != GL_NO_ERROR) {}
        glLightf(id, GL_SPOT_EXPONENT, spot_exponent);
        if ((err = glGetError()) != GL_NO_ERROR) {
        }

    } else {
        while (glGetError() != GL_NO_ERROR) {}
        glLightf(id, GL_SPOT_CUTOFF, 180.0f);
        if ((err = glGetError()) != GL_NO_ERROR) {
        }
    }

    while ((err = glGetError()) != GL_NO_ERROR) {
    }
}

void Light::drawFixture()
{
    if (is_fixed_no_bulb) {
        return;
    }
    GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat high_shininess[] = { 100.0f };
    GLfloat fixture_body_ambient[]  = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat fixture_body_diffuse[]  = {0.25f, 0.25f, 0.3f, 1.0f};
    GLfloat fixture_body_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, fixture_body_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, fixture_body_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, fixture_body_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        GLUquadric* quadric = gluNewQuadric();
        gluCylinder(quadric, 0.8, 0.8, 2.5, 16, 8);
        gluDeleteQuadric(quadric);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.5f);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, bulb_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, high_shininess);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, is_on ? bulb_emission : no_mat);
        glutSolidSphere(0.75f, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

void Light::drawBeamEffect()
{
    if (is_fixed_no_bulb) {
        return;
    }
    if (!is_on) return;

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);

    glTranslatef(0.0f, 0.0f, 2.5f);

    glPushAttrib(GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glColor4f(1.0f, 1.0f, 0.8f, 0.10f);

    float cone_height = 20.0f;
    float cone_base_radius = this->visual_beam_radius_local;

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, cone_height);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(cone_base_radius, cone_height, 16, 8);
    glPopMatrix();

    glPopAttrib();
    glPopMatrix();
}

void Light::setVisualBeamRadiusLocal(GLfloat radius) {
    this->visual_beam_radius_local = radius;
}

void Light::toggle()
{
    if (is_fixed_no_bulb) {
        return;
    }
    is_on = !is_on;
    ambient_on = is_on;
    diffuse_on = is_on;
    specular_on = is_on;
    if (is_on) {
        glEnable(id);
    } else {
        glDisable(id);
    }
}

void Light::toggleAmbient()
{
    if (is_on) {
        ambient_on = !ambient_on;
    }
}

void Light::toggleDiffuse()
{
    if (is_on) {
        diffuse_on = !diffuse_on;
    }
}

void Light::toggleSpecular()
{
    if (is_on) {
        specular_on = !specular_on;
    }
}

void Light::turnOn() {
    if (!is_on) {
        is_on = true;
        ambient_on = true;
        diffuse_on = true;
        specular_on = true;
        glEnable(id);
    }
}

void Light::turnOff() {
    if (is_fixed_no_bulb) return;
    if (is_on) {
        is_on = false;
        glDisable(id);
    }
}

void Light::setSpotDirection(GLfloat dir_x, GLfloat dir_y, GLfloat dir_z) {
    spot_direction[0] = dir_x;
    spot_direction[1] = dir_y;
    spot_direction[2] = dir_z;
}