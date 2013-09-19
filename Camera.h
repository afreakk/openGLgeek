#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Camera
{
    public:
        Camera(float resolutionX, float resolutionY, float drawDistance);
        void addShader(GLuint shader);
        void updateLightPosition(glm::vec3 lightPos);
        void lookAtFrom(glm::vec3 lookAt, glm::vec3 from);
        void updateFloat(const char* loc, float value);
        virtual ~Camera();
    protected:
    private:
        std::vector<GLuint> shaders;
        glm::mat4 projection;
        glm::mat4 view;
        void updateShaders(const char* locName,const glm::mat4& matrise);
        void updateShaders(const char* locName, const glm::vec3& vektor);
        void updateShaders(const char* locName, const float& value);
};

#endif // CAMERA_H
