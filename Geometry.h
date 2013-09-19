#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <iostream>
#include "math.h"
#include <vector>
class Geometry
{
    public:
        Geometry();
        void init(GLint POSITION, GLint TEXCOORD,GLuint SHADER);
        virtual ~Geometry();
        GLuint getCube();
        GLuint getPyramide();
        GLuint getPlane();
        unsigned getElements();
        GLuint getVBO();
        GLuint getEBO();
        GLuint getUVBO();
    protected:
    private:
        unsigned vertElements;
        GLint position;
        GLint texcoord;
        GLuint xVBO;
        GLuint eBO;
        GLuint uvBO;
        GLuint shader;

};

#endif // GEOMETRY_H
