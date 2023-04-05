#include "Transform.hpp"
#include <vector>
#include <common/texture.hpp>

using namespace std;

class Object3D
{
protected:
    Object3D *parent = nullptr;
    vector<Object3D *> children;
    vector<vec3> vertices;
    vector<unsigned short> indices;
    vector<vec2> UVs;
    GLuint vertexbuffer;
    GLuint elementbuffer;
    GLuint texture;
    int width;
    int height;
    int nrChannels;
    GLuint uv;
    int mode = 0;

public:
    Transform transform;
    Object3D();
    ~Object3D();
    void addChild(Object3D *child);
    void updateMeAndChilds();
    void loadTexture(std::string pathtexture);
    vector<vec3> getVertices();
    vector<vec2> getUVs();
    vector<unsigned short> getIndices();
    virtual void draw(GLuint programID);
    vector<Object3D *> getChilds();
    void removeChild(int pos);
};

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
    glDeleteBuffers(1, &uv);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
}
void Object3D::addChild(Object3D *child)
{
    child->parent = this;
    this->children.push_back(child);
}

void Object3D::removeChild(int pos)
{
    if (pos >= 0 && pos < children.size())
    {
        children[pos]->parent = nullptr;
        children.erase(children.begin() + pos);
    }
}

void Object3D::updateMeAndChilds()
{
    if (this->parent)
        this->transform.modelMatrix = this->parent->transform.modelMatrix * this->transform.getLocalModelMatrix();
    else
        this->transform.modelMatrix = this->transform.getLocalModelMatrix();

    for (auto &&child : children)
    {
        child->updateMeAndChilds();
    }
}

vector<vec3> Object3D::getVertices()
{
    return vertices;
}
vector<vec2> Object3D::getUVs()
{
    return UVs;
}

vector<Object3D *> Object3D::getChilds()
{
    return children;
}

vector<unsigned short> Object3D::getIndices()
{
    return indices;
}

 void Object3D::draw(GLuint programID)
{
    if (texture != -1)
    {
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(programID, "text"), 0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glUniformMatrix4fv(glGetUniformLocation(programID, "modelM"), 1, GL_FALSE, &(this->transform.modelMatrix)[0][0]);
    glUniform1i(glGetUniformLocation(programID, "mode"), mode);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv);
    glVertexAttribPointer(
        1,        // attribute
        2,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, (void *)0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    for (Object3D *child : children)
    {
        child->draw(programID);
    }
}

void Object3D::loadTexture(std::string pathtexture)
{
    texture = loadTexture2DFromFilePath(pathtexture, this->width, this->height, this->nrChannels);
}
