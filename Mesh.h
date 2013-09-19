#ifndef MESH_H
#define MESH_H
struct vector3d
{
    float x,y,z;
};
struct color3d
{
    float r,g,b;
};
struct vertexData{
	vector3d position;
	vector3d normal;
	vector3d tangent;
	color3d color;
	float U,V;
};
#include <vector>
#include <GL/glew.h>
#include <string>
#include <iostream>
class Mesh
{
    public:
        Mesh(std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<unsigned int>* td,unsigned int SHADER);
        void draw();
        virtual ~Mesh();
    protected:
    private:
    	std::vector<vertexData> data;
        std::vector<unsigned int> textures;
        std::vector<unsigned int> indices;
        unsigned int VBO;
        unsigned int IND;
        unsigned int vao;
        unsigned int shader;
};

#endif // MESH_H
