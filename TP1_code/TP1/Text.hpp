#ifndef OBJECT3D
#define OBJECT3D
#include "Object3D.hpp"
#endif
#include <common/text2D.hpp>

class Text : public Object3D
{
private:
    std::string text;

public:
    void makeText(std::string text);
    ~Text();
    void draw(GLuint programID);
};

void Text::makeText(std::string text)
{
    this->text = text;

}

Text::~Text()
{
}

void Text::draw(GLuint programID)
{
    const char *s = text.c_str();
    initText2D("../textures/sun.jpg");

    glUniformMatrix4fv(glGetUniformLocation(programID, "modelM"), 1, GL_FALSE, &(this->transform.modelMatrix)[0][0]);
    printText2D(s, 0, 0, 1);
}
