#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <string>
#include <vector>
#include <GL/gl.h>

struct Vertex {
    float x, y, z;
};

struct Normal {
    float nx, ny, nz;
};

struct MaterialInfo {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess[1];

    MaterialInfo() {
        ambient[0] = 0.2f; ambient[1] = 0.2f; ambient[2] = 0.2f; ambient[3] = 1.0f;
        diffuse[0] = 0.8f; diffuse[1] = 0.8f; diffuse[2] = 0.8f; diffuse[3] = 1.0f;
        specular[0] = 0.0f; specular[1] = 0.0f; specular[2] = 0.0f; specular[3] = 1.0f;
        shininess[0] = 0.0f;
    }
};

class ObjModel {
public:
    ObjModel();
    bool load(const std::string& filename);
    void draw();
    void getModelDimensions(float& minX, float& minY, float& minZ, float& maxX, float& maxY, float& maxZ);

private:
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;
    std::vector<unsigned int> indices;
    std::vector<MaterialInfo> modelMaterials;

    float modelMinX, modelMinY, modelMinZ;
    float modelMaxX, modelMaxY, modelMaxZ;

    void calculateDimensions();
};

#endif // OBJMODEL_H