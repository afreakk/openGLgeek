#ifndef SHADERCOMPILE_H
#define SHADERCOMPILE_H
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class shaderCompile
{
    public:
        shaderCompile();
        virtual ~shaderCompile();
        GLuint loadShader(const char * vertexPath, const char * fragmentPath);
    protected:
    private:
        void compileShader(const char * path, GLuint& shader, int shaderType);
        std::vector<GLuint> shaderPrograms;
        std::vector<GLuint> fragmentShaders;
        std::vector<GLuint> vertexShaders;
};

#endif // SHADERCOMPILE_H
