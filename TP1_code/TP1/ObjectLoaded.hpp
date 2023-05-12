#ifndef OBJECT3D
#define OBJECT3D
#include "Object3D.hpp"
#endif
#include <common/objloader.hpp>

class ObjectLoaded : public Object3D
{
private:
    /* data */

public:
    ObjectLoaded(/* args */);
    ~ObjectLoaded();
    void loadObject(const std::string &filename, int typeObject);
};

ObjectLoaded::ObjectLoaded(/* args */)
{
}

ObjectLoaded::~ObjectLoaded()
{
}

void ObjectLoaded::loadObject(const std::string &filename, int typeObject)
{
    std::vector<std::vector<unsigned short>> triangles;
    if (typeObject == 0)
    { // off
        loadOFF(filename, this->vertices, this->indices, triangles);
        vector<vec2> uvs;

        long int taille = vertices.size();
        float theta, phi, u, v;
        for (int i = 0; i < taille; i++)
        {
            theta = acos(vertices[i][1]);
            phi = atan(vertices[i][2], vertices[i][0]);
            u = (phi / (2 * M_PI) + 0.5);
            v = (theta / M_PI);
            uvs.push_back(vec2(u, v));
        }
        this->UVs = uvs;
    }
    else if (typeObject == 1) // obj ...
    {
        std::vector<vec3> normals;
        loadModel(filename.c_str(), this->indices, this->vertices,  normals,this->UVs);
    }

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uv);
    glBindBuffer(GL_ARRAY_BUFFER, uv);
    glBufferData(GL_ARRAY_BUFFER, this->UVs.size() * sizeof(vec2), &UVs[0], GL_STATIC_DRAW);
}
