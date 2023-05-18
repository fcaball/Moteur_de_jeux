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
    vector<vec3> cube;

public:
    Transform transform;
    Object3D();
    ~Object3D();
    void addChild(Object3D *child);
    virtual void updateMeAndChilds();
    void loadTexture(std::string pathtexture);
    vector<vec3> getVertices();
    vector<vec2> getUVs();
    vector<unsigned short> getIndices();
    virtual void draw(GLuint programID);
    vector<Object3D *> getChilds();
    void removeChild(int pos);
    vector<vec3> boiteEnglobante();
    vector<vec3> getBE();
    void addBE(vector<vec3> BEenCours, vector<vec3> BE);
    vec3 modifTranslation(vec3 translationEnCours, vec3 t);
    vec3 modifTranslationBis(vec3 translationEnCours, vec3 scale);

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
        (void *)0);
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

vector<vec3> Object3D::boiteEnglobante()
{
    /*  // float Xmin = FLT_MAX; // initialisation de valeurs arbitraires
     // float Ymin = FLT_MAX;
     // float Zmin = FLT_MAX;
     // float Xmax = FLT_MIN;
     // float Ymax = FLT_MIN;
     // float Zmax = FLT_MIN;
     // if (vertices.size() != 0)
     // {
     //     double taille = this->vertices.size();

     //     for (long unsigned int i = 0; i < taille; i++)
     //     {
     //         if (this->vertices[i][0] < Xmin)
     //         {
     //             Xmin = this->vertices[i][0];
     //         }
     //         if (this->vertices[i][1] < Ymin)
     //         {
     //             Ymin = this->vertices[i][1];
     //         }
     //         if (this->vertices[i][2] < Zmin)
     //         {
     //             Zmin = this->vertices[i][2];
     //         }
     //         if (this->vertices[i][0] > Xmax)
     //         {
     //             Xmax = this->vertices[i][0];
     //         }
     //         if (this->vertices[i][1] > Ymax)
     //         {
     //             Ymax = this->vertices[i][1];
     //         }
     //         if (this->vertices[i][2] > Zmax)
     //         {
     //             Zmax = this->vertices[i][2];
     //         }
     //     }
     // }
     // else
     // {
     //     vector<vec3> BestBE;
     //     BestBE.push_back(vec3(Xmin, Ymin, Zmin));
     //     BestBE.push_back(vec3(Xmax, Ymax, Zmax));
     //     for (int i = 0; i < this->getChilds().size(); i++)
     //     {
     //         cout<<"Je vais checker le "<<i<< "eme fdp de gosse de merde"<<endl;
     //         vector<vec3> BECurrentChild = this->getChilds()[i]->boiteEnglobante();
     //         if (BECurrentChild.size() == 2)
     //         {
     //             if (BECurrentChild[1].x > BestBE[1].x || BECurrentChild[1].y > BestBE[1].y || BECurrentChild[1].z > BestBE[1].z)
     //             {
     //                 BestBE = BECurrentChild;
     //             }
     //             if (BECurrentChild[0].x < BestBE[0].x || BECurrentChild[0].y < BestBE[0].y || BECurrentChild[0].z < BestBE[0].z)
     //             {
     //                 BestBE = BECurrentChild;
     //             }
     //         }
     //     }
     // }
     // cube.push_back(vec3(Xmin, Ymin, Zmin));
     // cube.push_back(vec3(Xmax, Ymax, Zmax));

     // Initialise la boîte englobante avec les coordonnées du premier sommet de l'objet
     minPoint = vertices[0] + this->transform.t;
     maxPoint = vertices[0] + this->transform.t;

     // Calcule la boîte englobante pour chaque sommet de l'objet
     for (const auto &vertex : vertices)
     {
         glm::vec3 absoluteVertex = vertex + this->transform.t;
         minPoint = glm::min(minPoint, absoluteVertex);
         maxPoint = glm::max(maxPoint, absoluteVertex);
     }

     // Calcule la boîte englobante pour chaque enfant de l'objet
     for (const auto &child : children)
     {
         glm::vec3 childMinPoint, childMaxPoint;
         child->boiteEnglobante(childMinPoint, childMaxPoint);

         // Étend la boîte englobante de l'objet en y incluant la boîte englobante de l'enfant
         minPoint = glm::min(minPoint, childMinPoint);
         maxPoint = glm::max(maxPoint, childMaxPoint);
     }
     cube.push_back(minPoint);
     cube.push_back(maxPoint); */

    /* vec3 minPoint;
    vec3 maxPoint;
    if (this->vertices.size() != 0)
    {
        for (size_t i = 0; i < this->vertices.size(); i++)
        {
            minPoint = min(this->vertices[i], minPoint);
            maxPoint = max(this->vertices[i], maxPoint);
        }
    }
    minPoint = minPoint + this->transform.t;
    maxPoint = maxPoint + this->transform.t;
    for (size_t i = 0; i < this->children.size(); i++)
    {
        vector<vec3> childBE = this->children[i]->boiteEnglobante();

        minPoint = min(childBE[0], minPoint);
        maxPoint = max(childBE[1], maxPoint);
    }
    cube.push_back(minPoint);
    cube.push_back(maxPoint);

    return cube; */
        float Xmin = 100; //initialisation de valeurs arbitraires
        float Ymin = 100;
        float Zmin = 100;
        float Xmax = -100;
        float Ymax = -100;
        float Zmax = -100;
        for(long unsigned int i=0; i<vertices.size() ; i++){ 
            if(vertices[i][0]<Xmin){
                Xmin = vertices[i][0];
            }
            if(vertices[i][1]<Ymin){
                Ymin = vertices[i][1];
            }
            if(vertices[i][2]<Zmin){
                Zmin = vertices[i][2];
            }
            if(vertices[i][0]>Xmax){
                Xmax = vertices[i][0];
            }
            if(vertices[i][1]>Ymax){
                Ymax= vertices[i][1];
            }
            if(vertices[i][2]>Zmax){
                Zmax = vertices[i][2];
            }
        }
        cube.push_back(vec3(Xmin,Ymin,Zmin));
        cube.push_back(vec3(Xmax,Ymax,Zmax));
        /*for(unsigned int i = 0 ;i<cube.size() ; i++){
            std::cout<<"Point "<<i<<" : ("<<cube[i][0]<<" ; "<<cube[i][1]<<" ; "<<cube[i][2]<<")"<<std::endl;
        }*/
        return cube;
    }


vector<vec3> Object3D::getBE()
{
    return cube;
}

void Object3D::addBE(vector<vec3> BEenCours, vector<vec3> BE)
{
    cube[0][0] = std::min(BEenCours[0][0], BE[0][0]);
    cube[0][1] = std::min(BEenCours[0][1], BE[0][1]);
    cube[0][2] = std::min(BEenCours[0][2], BE[0][2]);
    cube[1][0] = std::max(BEenCours[1][0], BE[1][0]);
    cube[1][1] = std::max(BEenCours[1][1], BE[1][1]);
    cube[1][2] = std::max(BEenCours[1][2], BE[1][2]);
}

vec3 Object3D::modifTranslation(vec3 translationEnCours, vec3 t){
    return vec3(translationEnCours[0] + t[0], translationEnCours[1] + t[1], translationEnCours[2] + t[2]) ;
}

vec3 Object3D::modifTranslationBis(vec3 translationEnCours, vec3 scale){
    return vec3(translationEnCours[0] * scale[0], translationEnCours[1] * scale[1], translationEnCours[2] * scale[2]);
}
