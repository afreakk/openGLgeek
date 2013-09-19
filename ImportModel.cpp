#include "ImportModel.h"

ImportModel::ImportModel(const char* filename, unsigned int SHADER)
{
    shader=SHADER;
    Assimp::Importer importer;
	const aiScene* scene=importer.ReadFile(filename, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if(scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode || !scene)
	{
		std::cout   << "error: " << filename << "\n"
                    << "output: "<< importer.GetErrorString()<< std::endl;
		return;
	}
	std::cout << filename<< " was successfuly opened atleast.." << std::endl;
	recursiveProcess(scene->mRootNode,scene);


}
void ImportModel::recursiveProcess(aiNode* node,const aiScene* scene)
{
	//process
	for(int i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh,scene);
	}



	//recursion
	for(int i=0;i<node->mNumChildren;i++)
	{
		recursiveProcess(node->mChildren[i],scene);
	}
}
void ImportModel::processMesh(aiMesh* mesh,const aiScene* scene)
{
	std::vector<vertexData> data;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> textures;
	aiColor4D col;
	aiMaterial* mat=scene->mMaterials[mesh->mMaterialIndex];
	aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&col);
	color3d defaultColor;
	defaultColor.r= col.r,defaultColor.g=col.g,defaultColor.b=col.b;

    if(mesh->HasBones())
    {
        std :: cout<<"numberofBones: "<< mesh->mNumBones<<std::endl;
        boneInfo bArr[mesh->mNumVertices];
        for(int i=0;i<mesh->mNumBones;i++)
        {
            for(int j=0;j<mesh->mBones[i]->mNumWeights;j++)
            {
                bArr[mesh->mBones[i]->mWeights[j].mVertexId].boneId = i;
                bArr[mesh->mBones[i]->mWeights[j].mVertexId].weight = mesh->mBones[i]->mWeights[j].mWeight;

            }
        }
    }

	for(int i=0;i<mesh->mNumVertices;i++)
	{
			vertexData tmp;
			vector3d tmpVec;
			//position
			tmpVec.x=mesh->mVertices[i].x;
			tmpVec.y=mesh->mVertices[i].y;
			tmpVec.z=mesh->mVertices[i].z;
			tmp.position=tmpVec;

			//normals
			tmpVec.x=mesh->mNormals[i].x;
			tmpVec.y=mesh->mNormals[i].y;
			tmpVec.z=mesh->mNormals[i].z;
			tmp.normal=tmpVec;


			//tangent
			if(mesh->mTangents)
			{
				tmpVec.x=mesh->mTangents[i].x;
				tmpVec.y=mesh->mTangents[i].y;
				tmpVec.z=mesh->mTangents[i].z;
			}else{
				tmpVec.x=1.0;
				tmpVec.y=tmpVec.z=0;
			}
			tmp.tangent=tmpVec;

            color3d clr;
			//colors
			if(mesh->mColors[0])
			{
				//!= material color
				clr.r=mesh->mColors[0][i].r;
				clr.g=mesh->mColors[0][i].g;
				clr.b=mesh->mColors[0][i].b;
			}else{
				clr=defaultColor;
			}
			tmp.color=clr;

			//color
			if(mesh->mTextureCoords[0])
			{
				tmpVec.x=mesh->mTextureCoords[0][i].x;
				tmpVec.y=mesh->mTextureCoords[0][i].y;
			}else{
				tmpVec.x=tmpVec.y=tmpVec.z=0.0;
			}
			tmp.U=tmpVec.x;
			tmp.V=tmpVec.y;
			data.push_back(tmp);
	}

	for(int i=0;i<mesh->mNumFaces;i++)
	{
		aiFace face=mesh->mFaces[i];
		for(int j=0;j<face.mNumIndices;j++) //0..2
		{
			indices.push_back(face.mIndices[j]);
		}
	}

    std::cout<<"textures: " <<mat->GetTextureCount(aiTextureType_DIFFUSE) <<std::endl;
	for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++)
	{
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE,i,&str);
		unsigned int tmp;
		tmp=imgl.sdlLoad(str.C_Str());
		textures.push_back(tmp);
	}
	meshes.push_back(new Mesh(&data,&indices,&textures,shader));
}

ImportModel::~ImportModel()
{
    //dtor
}
void ImportModel::draw()
{
	for(int i=0;i<meshes.size();i++)
		meshes[i]->draw();
}
