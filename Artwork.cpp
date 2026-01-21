platform_size[0] = platformX;
platform_size[1] = platformY;
platform_size[2] = platformZ;

platform_ambient[0] = 0.3f; platform_ambient[1] = 0.3f; platform_ambient[2] = 0.3f; platform_ambient[3] = 1.0f;
platform_diffuse[0] = 0.6f; platform_diffuse[1] = 0.6f; platform_diffuse[2] = 0.6f; platform_diffuse[3] = 1.0f;
platform_specular[0] = 1.0f; platform_specular[1] = 1.0f; platform_specular[2] = 1.0f; platform_specular[3] = 1.0f;
platform_shininess[0] = 20.0f;


glPushMatrix();
glTranslatef(x - platform_size[0] / 2.0f, y, z - platform_size[2] / 2.0f);
glScalef(platform_size[0] / 3.0f, platform_size[1] / 3.0f, platform_size[2] / 3.0f);
glMaterialfv(GL_FRONT, GL_AMBIENT, platform_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, platform_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, platform_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, platform_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
platformCube.draw();
glPopMatrix();