#include "Object3D.h"

Object3D::Object3D()
{
    //ctor
}

Object3D::~Object3D()
{
    //dtor
}
void Object3D::init(const char* filename,unsigned int SHADER)
{
    object = new ImportModel(filename,SHADER);
    shader = SHADER;
    translationV = glm::vec3(0.0,0.0,0.0);
    orientationV = glm::quat_cast(rotationM);
    scaleV = glm::vec3(1.0);
    BaseGL::addObj(this);
}
glm::vec3 Object3D::getScale()
{
    return scaleV;
}
void Object3D::init(ImportModel* model,unsigned int SHADER)
{
    object = model;
    shader = SHADER;
    translationV = glm::vec3(0.0,0.0,0.0);
    orientationV = glm::quat_cast(rotationM);
    scaleV = glm::vec3(1.0);
    BaseGL::addObj(this);
}
void Object3D::setOrientation(glm::quat orient)
{
    orientationV = orient;
    rotationM = glm::mat4_cast(orientationV);
}
void Object3D::rotation(float angle, glm::vec3 axis)
{
    rotationM = glm::rotate(rotationM,angle,axis);
    orientationV = glm::quat_cast(rotationM);

}
glm::quat Object3D::getOrientation()
{
    return orientationV;
}
void Object3D::translate(glm::vec3 with)
{
    translationV += with;
    translationM = glm::translate(translationM,with);

}
void Object3D::scale(glm::vec3 scaleVec )
{
    scaleV *= scaleVec;
    scaleM = glm::scale(scaleM, scaleVec);
}
glm::vec3 Object3D::getTranslation()
{
    return translationV;
}
void Object3D::position(glm::vec3 pos)
{
    glm::mat4 id;
    translationM = id;
    translationM = glm::translate(translationM,pos);
    translationV = pos;
}
void Object3D::draw()
{
    glUseProgram(shader);
    modelM = translationM*rotationM*scaleM;
    GLint modelGLSL = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(modelGLSL,1,GL_FALSE,glm::value_ptr( modelM ) );
    object->draw();
    glUseProgram(0);
}
ImportModel* Object3D::getModel()
{
    return object;
}
