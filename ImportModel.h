#ifndef IMPORTMODEL_H
#define IMPORTMODEL_H
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "imageLoader.h"
#include "Mesh.h"

class ImportModel
{
struct boneInfo
{
    unsigned int    boneId;
    float           weight;
};
    public:
        ImportModel(const char* filename,unsigned int SHADER);
        void draw();
        virtual ~ImportModel();
    protected:
    private:
        imageLoader imgl;
        void recursiveProcess(aiNode* node,const aiScene* scene);
        void processMesh(aiMesh* mesh,const aiScene* scene);
        std::vector <Mesh*> meshes;
        unsigned int shader;
};

#endif // IMPORTMODEL_H
