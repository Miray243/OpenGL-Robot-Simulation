#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "ObjModel.h"
#include <iostream>
#include <limits>

ObjModel::ObjModel() :
    modelMinX(0.0f), modelMinY(0.0f), modelMinZ(0.0f),
    modelMaxX(0.0f), modelMaxY(0.0f), modelMaxZ(0.0f) {
}

bool ObjModel::load(const std::string& filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> loaded_materials;
    std::string warn;
    std::string err;

    std::string base_dir;
    size_t last_slash = filename.find_last_of("/\\");
    if (last_slash != std::string::npos) {
        base_dir = filename.substr(0, last_slash + 1);
    }

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &loaded_materials, &warn, &err, filename.c_str(), base_dir.c_str(), true);

    if (!warn.empty()) {
        std::cout << "TinyObjLoader UYARI: " << filename << ": " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "TinyObjLoader HATA: " << filename << ": " << err << std::endl;
        return false;
    }
    if (!ret) {
        std::cerr << "TinyObjLoader: .obj dosyasi yuklenemedi: " << filename << std::endl;
        return false;
    }

    vertices.clear();
    normals.clear();
    this->modelMaterials.clear();

    for (size_t m = 0; m < loaded_materials.size(); ++m) {
        const tinyobj::material_t& mat_from_loader = loaded_materials[m];
        MaterialInfo current_material;

        current_material.ambient[0] = mat_from_loader.ambient[0];
        current_material.ambient[1] = mat_from_loader.ambient[1];
        current_material.ambient[2] = mat_from_loader.ambient[2];
        current_material.ambient[3] = 1.0f;

        current_material.diffuse[0] = mat_from_loader.diffuse[0];
        current_material.diffuse[1] = mat_from_loader.diffuse[1];
        current_material.diffuse[2] = mat_from_loader.diffuse[2];
        current_material.diffuse[3] = 1.0f;

        current_material.specular[0] = mat_from_loader.specular[0];
        current_material.specular[1] = mat_from_loader.specular[1];
        current_material.specular[2] = mat_from_loader.specular[2];
        current_material.specular[3] = 1.0f;

        current_material.shininess[0] = mat_from_loader.shininess;

        this->modelMaterials.push_back(current_material);
    }
    if (!loaded_materials.empty()) {
        std::cout << "TinyObjLoader BİLGİ: " << filename << " icin " << loaded_materials.size() << " adet malzeme yuklendi." << std::endl;
    }

    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = shapes[s].mesh.num_face_vertices[f];

            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                Vertex vert;
                vert.x = attrib.vertices[3 * idx.vertex_index + 0];
                vert.y = attrib.vertices[3 * idx.vertex_index + 1];
                vert.z = attrib.vertices[3 * idx.vertex_index + 2];
                vertices.push_back(vert);

                if (idx.normal_index >= 0 && !attrib.normals.empty()) {
                    Normal norm;
                    norm.nx = attrib.normals[3 * idx.normal_index + 0];
                    norm.ny = attrib.normals[3 * idx.normal_index + 1];
                    norm.nz = attrib.normals[3 * idx.normal_index + 2];
                    normals.push_back(norm);
                } else {
                    Normal default_norm = {0.0f, 1.0f, 0.0f};
                    normals.push_back(default_norm);
                }
            }
            index_offset += fv;
        }
    }

    calculateDimensions();
    return true;
}

void ObjModel::calculateDimensions() {
    if (vertices.empty()) {
        modelMinX = modelMinY = modelMinZ = 0.0f;
        modelMaxX = modelMaxY = modelMaxZ = 0.0f;
        return;
    }

    modelMinX = modelMaxX = vertices[0].x;
    modelMinY = modelMaxY = vertices[0].y;
    modelMinZ = modelMaxZ = vertices[0].z;

    for (size_t i = 1; i < vertices.size(); ++i) {
        const Vertex& v = vertices[i];
        if (v.x < modelMinX) modelMinX = v.x;
        if (v.x > modelMaxX) modelMaxX = v.x;
        if (v.y < modelMinY) modelMinY = v.y;
        if (v.y > modelMaxY) modelMaxY = v.y;
        if (v.z < modelMinZ) modelMinZ = v.z;
        if (v.z > modelMaxZ) modelMaxZ = v.z;
    }
}

void ObjModel::getModelDimensions(float& minX, float& minY, float& minZ, float& maxX, float& maxY, float& maxZ) {
    minX = modelMinX;
    minY = modelMinY;
    minZ = modelMinZ;
    maxX = modelMaxX;
    maxY = modelMaxY;
    maxZ = modelMaxZ;
}

void ObjModel::draw() {
    if (vertices.empty()) {
        return;
    }
    if (!this->modelMaterials.empty()) {
        const MaterialInfo& first_material = this->modelMaterials[0];

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, first_material.ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, first_material.diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, first_material.specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, first_material.shininess);
    }

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (i < normals.size()) {
            glNormal3f(normals[i].nx, normals[i].ny, normals[i].nz);
        }
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
}