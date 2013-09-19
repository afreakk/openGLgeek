#include "shaderCompile.h"

shaderCompile::shaderCompile()
{
    //ctor
}

shaderCompile::~shaderCompile()
{
    for(int i=0; i<shaderPrograms.size(); i++)
        glDeleteProgram( shaderPrograms[i] );
    for(int i=0; i<fragmentShaders.size(); i++)
        glDeleteShader( fragmentShaders[i] );
	for(int i=0; i<vertexShaders.size(); i++)
        glDeleteShader( vertexShaders[i] );
}
GLuint shaderCompile::loadShader(const char * vertexPath, const char * fragmentPath)
{
    GLuint vertexShader, fragmentShader;
    compileShader(vertexPath,vertexShader,GL_VERTEX_SHADER);
    compileShader(fragmentPath,fragmentShader,GL_FRAGMENT_SHADER);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glBindFragDataLocation(shaderProgram,0,"outColor");
    glLinkProgram(shaderProgram);
    vertexShaders.push_back(vertexShader);
    fragmentShaders.push_back(fragmentShader);
    shaderPrograms.push_back(shaderProgram);
    return shaderPrograms.back();
}
void shaderCompile::compileShader(const char * path, GLuint& shader, int shaderType)
{
    std::string srcLine;
    std::string sourceCode;
    std::ifstream shaderFile (path, std::ios::in);
    if(shaderFile.is_open())
    {
        while(shaderFile.good())
        {
            getline(shaderFile,srcLine);
            sourceCode += srcLine+"\n";
        }
    }
    else
    {
        std::cout << "Cannot open "<<path<<std::endl;
    }
    shader = glCreateShader(shaderType);
    const GLchar* cStyleSourceCode= sourceCode.c_str();
    glShaderSource(shader,1,&cStyleSourceCode,NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
    std::string shaderName;
    switch(shaderType)
    {
        case GL_VERTEX_SHADER: shaderName = " Vertex Shader ";shaderName += path;break;
        case GL_FRAGMENT_SHADER: shaderName = " Fragment Shader ";shaderName+=path;break;
    }
    if(status != GL_TRUE)
    {
        std::cout << "Cannot compile"<< shaderName+"\n";
    }
    char buffer[512];
    glGetShaderInfoLog(shader,512,NULL,buffer);
    std::cout << "Debug log for"<<shaderName<<":\n";
    std::cout <<buffer<<std::endl;
}
