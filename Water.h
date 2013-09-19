#ifndef WATER_H
#define WATER_H
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imageLoader.h"
#include "Geometry.h"
#include "BaseGL.h"
class Water:public BaseGL
{
    public:
        Water(GLuint SHADER);
        virtual ~Water();
        void draw();
    protected:
    private:
        GLuint shader;
        GLuint plane;
        glm::mat4 modelM;
        imageLoader imgl;
        GLuint waterT;
};

#endif // WATER_H
