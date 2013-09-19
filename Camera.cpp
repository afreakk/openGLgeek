#include "Camera.h"

Camera::Camera(float resolutionX, float resolutionY, float drawDistance)
{
    view = glm::lookAt(
    glm::vec3( 0.0f, 0.0f, 0.0f ),
    glm::vec3( 0.0f, 0.0f, -1.0f ),
    glm::vec3( 0.0f, 1.0f, 0.0f ) );
    projection = glm::perspective( 45.0f, resolutionX / resolutionY, 1.0f, drawDistance );
}
void Camera::updateLightPosition(glm::vec3 lightPos)
{
    updateShaders("LightPosition_worldspace",lightPos);
}
void Camera::lookAtFrom(glm::vec3 lookAt, glm::vec3 from)
{
    view = glm::lookAt(from,lookAt,glm::vec3( 0.0f, 1.0f, 0.0f ));
    updateShaders("view", view);

}
void Camera::updateFloat(const char* loc, float value)
{
    updateShaders(loc,value);
}
void Camera::updateShaders(const char* locName, const float& value)
{
    for(int i=0; i<shaders.size(); i++)
    {
        glUseProgram(shaders[i]);
        glUniform1f(glGetUniformLocation( shaders[i], locName ),value );
    }
    glUseProgram(0);
}
void Camera::updateShaders(const char* locName, const glm::mat4& matrise)
{
    for(int i=0; i<shaders.size(); i++)
    {
        glUseProgram(shaders[i]);
        glUniformMatrix4fv(glGetUniformLocation( shaders[i], locName ), 1,GL_FALSE,glm::value_ptr(matrise) );
    }
    glUseProgram(0);
}
void Camera::updateShaders(const char* locName, const glm::vec3& vektor)
{
    for(int i=0; i<shaders.size(); i++)
    {
        glUseProgram(shaders[i]);
        glUniform3fv(glGetUniformLocation( shaders[i], locName ), 1,glm::value_ptr(vektor) );
    }
    glUseProgram(0);
}
Camera::~Camera()
{
    //dtor
}
void Camera::addShader(GLuint shader)
{
    glUseProgram(shader);
    shaders.push_back(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"),1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "proj"),1,GL_FALSE,glm::value_ptr(projection));
    glUseProgram(0);
}
