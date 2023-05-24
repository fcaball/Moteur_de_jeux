#ifndef OBJECT3D
#define OBJECT3D
#include "Object3D.hpp"
#endif
using namespace glm;

class Camera : public Object3D
{
private:
    vec3 Depposition;
    vec3 position;
    vec3 target;
    vec3 direction; // /!\pointe dans la direction inverse
    vec3 up;
    vec3 right;
    vec3 front;

public:
    ~Camera();
    Camera(vec3 position, vec3 target, vec3 up, vec3 front)
    {
        this->Depposition = position;
        this->position = position;
        this->target = target;
        this->direction = glm::normalize(this->position - this->target);

        this->front = front;
        this->up = up;
        this->right = glm::normalize(glm::cross(this->up, this->direction));
    }
    
    vec3 getDepPosition()
    {
        return Depposition;
    }

    vec3 getPosition()
    {
        return position;
    }

    void setPosition(glm::vec3 pos)
    {
        position = pos;
    }

    vec3 getTarget()
    {
        return target;
    }

    void setTarget(glm::vec3 tar)
    {
        target = tar;
    }

    vec3 getDirection()
    {
        return direction;
    }

    void setDirection(glm::vec3 dir)
    {
        direction = dir;
    }

    vec3 getFront()
    {
        return front;
    }

    void setFront(glm::vec3 fro)
    {
        front = fro;
    }

    vec3 getRight()
    {
        return right;
    }

    void setRight(glm::vec3 rig)
    {
        right = rig;
    }

    vec3 getUp()
    {
        return up;
    }

    void setRigth(glm::vec3 u)
    {
        up = u;
    }

    void draw(GLuint programID)
    {
        for (Object3D *child : children)
        {
            child->draw(programID);
        }
    }

    void updateMeAndChilds()
    {
        if (this->parent)
        {
            vec4 new_pos = this->parent->transform.modelMatrix * vec4(this->Depposition, 1.0);
            this->transform.modelMatrix= this->parent->transform.modelMatrix ;
            this->position.x = new_pos.x;
            this->position.y = new_pos.y;
            this->position.z = new_pos.z;
        }

        for (auto &&child : children)
        {
            child->updateMeAndChilds();
        }
    }
};
