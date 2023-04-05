
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

class Transform
{
private:
    mat4 localMatrix = mat4(1.0f);

public:
    // Global space information concatenate in matrix
    mat4 modelMatrix = mat4(1.0f);

    void Translate(vec3 translatation)
    {
        localMatrix = translate(localMatrix, translatation);
    }

    void Rotation(const vec3 axis, float angle)
    {
        localMatrix = rotate(localMatrix, angle, axis);
    }

    void Scale(vec3 scaling)
    {
        localMatrix = scale(localMatrix, scaling);
    }

    Transform(/* args */)
    {
        modelMatrix = mat4(1.0f);
    }

    ~Transform()
    {
    }

    mat4 getLocalModelMatrix()
    {
        return localMatrix;
    }
};
