#include "Water.h"

Water::Water(GLuint SHADER)
{
    shader = SHADER;
    glUseProgram(shader);
    GLint pos = glGetAttribLocation(shader, "position");
    GLint texC = glGetAttribLocation(shader, "texcoord");
    Geometry mesh;
    mesh.init(pos,texC,SHADER);
    plane = mesh.getPlane();
    modelM = glm::translate(modelM,glm::vec3(0,-18,-2000));
    modelM = glm::scale(modelM,glm::vec3(4000.0f));
    waterT = imgl.sdlLoad("water.jpg");
    glUseProgram(0);
    BaseGL::addObj(this);
}
void Water::draw()
{
    glUseProgram(shader);
    glBindTexture(GL_TEXTURE_2D,waterT);
    GLint modelGLSL = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(modelGLSL,1,GL_FALSE,glm::value_ptr( modelM ) );
    glBindVertexArray(plane);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
    glUseProgram(0);
}
Water::~Water()
{
    //dtor
}
