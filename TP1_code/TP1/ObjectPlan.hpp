#ifndef OBJECT3D
#define OBJECT3D
#include "Object3D.hpp"
#include <vector>
#endif
class ObjectPlan : public Object3D
{
protected:
    GLuint hmap;
    int nX;
    int nY;
    int sizeX;
    int sizeY;
    float offsetX;
    float offsetZ;
    float offsetY;
    bool HeightMap;
    string path;

public:
    float offSetZ;
    ObjectPlan(/* args */);
    ObjectPlan(int nX, int nY, int sizeX, int sizeY, float offsetX, float offsetZ, bool HeightMap, string path = "", float offsetY = 0);

    ~ObjectPlan();
    void makePlan(int nX, int nY, int sizeX, int sizeY, float offsetX, float offsetZ, float offsetY, bool HeightMap, string path = "");
    void changeResolution(int newResX, int newResY);
    void draw(GLuint programID);
};

ObjectPlan::ObjectPlan(/* args */)
{
}

ObjectPlan::ObjectPlan(int nX, int nY, int sizeX, int sizeY, float offsetX, float offsetZ, bool HeightMap, string path, float offsetY)
{
    this->nX = nX;
    this->nY = nY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->offsetZ = offsetZ;
    this->HeightMap = HeightMap;
    this->path = path;

    makePlan(nX, nY, sizeX, sizeY, offsetX, offsetZ, offsetY, HeightMap, path);
}

ObjectPlan::~ObjectPlan()
{
}

void ObjectPlan::makePlan(int nX, int nY, int sizeX, int sizeY, float offsetX, float offsetZ, float offsetY, bool HeightMap, string path)
{
    this->offSetZ = offsetZ;
    this->vertices.clear();
    this->indices.clear();

    vector<vec2> texCoords;

    for (size_t i = 0; i <= nX; i++)
    {
        for (size_t j = 0; j <= nY; j++)
        {
            this->vertices.push_back(vec3((((float)sizeX / (float)nX) * i) - offsetX, -offsetY, (((float)sizeY / (float)nY) * j) - offsetZ));
            texCoords.push_back(vec2((float)i / (float)nX, (float)j / (float)nY));
        }
    }

    for (size_t i = 0; i < nX; i++)
    {
        for (size_t j = 0; j < nY; j++)
        {
            this->indices.push_back((i + 1) * (nX + 1) + j);
            this->indices.push_back((i + 1) * (nX + 1) + j + 1);
            this->indices.push_back(i * (nX + 1) + j + 1);
            /* ___
               \  |
                \ |
                 \| */

            this->indices.push_back(i * (nX + 1) + j);
            this->indices.push_back((i + 1) * (nX + 1) + j);
            this->indices.push_back(i * (nX + 1) + j + 1);
            /*
              |\
              | \
              |__\  */

            texCoords.push_back(vec2((float)(i + 1) / (float)nX, (float)j / (float)nY));

            texCoords.push_back(vec2((float)(i + 1) / (float)nX, (float)(j + 1) / (float)nY));

            texCoords.push_back(vec2((float)(i) / (float)nX, (float)(j + 1) / (float)nY));

            texCoords.push_back(vec2((float)(i) / (float)nX, (float)j / (float)nY));

            texCoords.push_back(vec2((float)(i + 1) / (float)nX, (float)(j) / (float)nY));

            texCoords.push_back(vec2((float)(i) / (float)nX, (float)(j + 1) / (float)nY));
        }
    }
    this->UVs = texCoords;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uv);
    glBindBuffer(GL_ARRAY_BUFFER, uv);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(vec2), &texCoords[0], GL_STATIC_DRAW);

    if (HeightMap)
    {
        this->mode = 1;
        this->hmap = loadTexture2DFromFilePath(this->path);
    }

    // Generate a buffer for the this->indices as well
}

void ObjectPlan::changeResolution(int newResX, int newResY)
{
    this->nX = newResX;
    this->nY = newResY;
    makePlan(this->nX, this->nY, this->sizeX, this->sizeY, this->offsetX, this->offSetZ, this->offsetY, this->HeightMap, this->path);
}

void ObjectPlan::draw(GLuint programID)
{
    if (this->hmap != -1)
    {
        glActiveTexture(GL_TEXTURE0 + 1);
        glUniform1i(glGetUniformLocation(programID, "HMPlan"), 1);
        glBindTexture(GL_TEXTURE_2D, this->hmap);
    }
    Object3D::draw(programID);
}
