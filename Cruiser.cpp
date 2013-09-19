#include "Cruiser.h"

Cruiser::Cruiser()
{
    //ctor
}
void Cruiser::init(const char* filename,unsigned int SHADER)
{
    boat = new ImportModel(filename,SHADER);
    shader = SHADER;

    translationV = glm::vec3(-0.0,-20.0,-60.0f);
    translate(translationV);
    rotation(-90.0f,glm::vec3(0.0,1.0,0.0));
    BaseGL::addObj(this);
}
void Cruiser::draw()
{
    glUseProgram(shader);
    GLint modelGLSL = glGetUniformLocation(shader, "model");
    //modelM = scaleM*rotationM*translationM;
    modelM = translationM*rotationM*scaleM;
    glUniformMatrix4fv(modelGLSL,1,GL_FALSE,glm::value_ptr( modelM ) );
    boat->draw();
    glUseProgram(0);
}
Cruiser::~Cruiser()
{
    //dtor
}
void Cruiser::rotation(float angle, glm::vec3 axis)
{
    rotationM = glm::rotate(rotationM,angle,axis);
}
void Cruiser::translate(glm::vec3 with)
{
    translationV += with;
    translationM = glm::translate(translationM,with);
}
void Cruiser::scale(glm::vec3 scaleVec )
{
    scaleM = glm::scale(scaleM, scaleVec);
}
glm::vec3 Cruiser::getTranslation()
{
    return translationV;
}
void Cruiser::position(glm::vec3 pos)
{
    glm::mat4 id;
    translationM = id;
    translationM = glm::translate(translationM,pos);
    translationV = pos;
}
