#include "Mesh.h"

Mesh::Mesh(std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<unsigned int>* td,unsigned int SHADER)
{
    shader=SHADER;
  	data=*vd;
	indices=*id;
	if(td)
		textures=*td;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(vertexData),
	&data[0],GL_STATIC_DRAW);


	glGenBuffers(1,&IND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
	//attribute vec3 vertex
	int vertex=glGetAttribLocation(shader,"position"); //0
	int normal=glGetAttribLocation(shader,"normal"); //1
	int tangent=glGetAttribLocation(shader,"tangent"); //2
	int color=glGetAttribLocation(shader,"color"); //3
	int UV=glGetAttribLocation(shader,"texcoord"); //4

	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),0);

	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(3*sizeof(float)));

	glEnableVertexAttribArray(tangent);
	glVertexAttribPointer(tangent,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(6*sizeof(float)));

	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(9*sizeof(float)));

	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV,2,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(12*sizeof(float)));

    glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

Mesh::~Mesh()
{
    glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&IND);
	glDeleteVertexArrays(1,&vao);
}
void Mesh::draw()
{


	//texture0
	//texture1...
	std::string str="texture";
	for(int i=0;i<textures.size();i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D,textures[i]);
		glUniform1i(glGetUniformLocation(shader,"image"),i); //bruk er masse textures
	}
	glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

}
