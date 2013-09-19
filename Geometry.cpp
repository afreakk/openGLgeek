#include "Geometry.h"

Geometry::Geometry():position(0),vertElements(0),xVBO(0),eBO(0),texcoord(0),uvBO(0)
{
    //ctor
}

Geometry::~Geometry()
{
    //dtor
}

void Geometry::init(GLint POSITION, GLint TEXCOORD,GLuint SHADER)
{
    position = POSITION,texcoord = TEXCOORD,shader = SHADER;
}
unsigned Geometry::getElements()
{
    return vertElements;
}
GLuint Geometry::getPyramide()
{
    float vertices[] =
    {
        0.0,1.0,0.0, //top                      0
        -1.0,-1.0,1.0, //bot Left   front       1
        1.0,-1.0,1.0, // bot right  front       2
        0.0,-1.0,-1.0   //bot mid back          3
    };
    GLuint elements[]=
    {
            0,1,2, //front
            0,2,3, //side
            0,1,3
    };
    float uiBO[] =
    {
        0.0,0.0,
        0.0,1.0,
        1.0,1.0,
        0.5,1.0
    };
    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(position);
    glEnableVertexAttribArray(texcoord);
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,0,0);
    GLuint vbou;
    glGenBuffers(1,&vbou);
    glBindBuffer(GL_ARRAY_BUFFER, vbou);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uiBO),uiBO,GL_STATIC_DRAW);
    glVertexAttribPointer(texcoord,2,GL_FLOAT,GL_FALSE,0,0);
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    vertElements = sizeof(elements)/sizeof(float);
    eBO = ebo;
    xVBO = vbo;
    glBindVertexArray(0);
    return vao;
}
GLuint Geometry::getVBO()
{
    return xVBO;
}
GLuint Geometry::getEBO()
{
    return eBO;
}
GLuint Geometry::getUVBO()
{
    return uvBO;
}
GLuint Geometry::getPlane()
{
    float plane[] =
    {
        -1.0,0.0,-1.0,
        -1.0,0.0,1.0,
        1.0,0.0,1.0,

        1.0,0.0,-1.0,
        -1.0,0.0,-1.0,
        1.0,0.0,1.0,
    };
    float uvP[] =
    {
        0.0,0.0,
        0.0,1.0,
        1.0,1.0,

        1.0,0.0,
        0.0,0.0,
        1.0,1.0
    };
    float pNorms[6*3];
    for(int i=0; i<6*3; i+=3)
    {
        pNorms[i]=0.0;
        pNorms[i+1]=2.0;
        pNorms[i+2]=0.0;
    }
    GLint normals = glGetAttribLocation(shader,"normal");
    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane,GL_STATIC_DRAW);
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,0,0);
    GLuint vboNorms;
    glGenBuffers(1,&vboNorms);
    glBindBuffer(GL_ARRAY_BUFFER,vboNorms);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pNorms),pNorms,GL_STATIC_DRAW);
    glEnableVertexAttribArray(normals);
    glVertexAttribPointer(normals,3,GL_FLOAT,GL_FALSE,0,0);

    GLuint uvbf;
    glGenBuffers(1,&uvbf);
    glBindBuffer(GL_ARRAY_BUFFER, uvbf);
    glBufferData(GL_ARRAY_BUFFER,sizeof(uvP),uvP,GL_STATIC_DRAW);
    glEnableVertexAttribArray(texcoord);
    glVertexAttribPointer(texcoord,2,GL_FLOAT,GL_FALSE,0,0);


    glBindVertexArray(0);
    return vao;
}

GLuint Geometry::getCube()
{
    int smoothness=1;
    float halvsirkler = 1;
	std::vector <float> uiBO;
	//high
	int amnt=8;
    float tiling=1000000000000000000000000;
    float size=tiling;
    float spread = 1000000.00000001;
    float helsirkler=1;
	for(int y=0; y<amnt; y++)
	{
        for(int x=0; x<amnt; x++)
        {
            for(int z=0; z<amnt; z++)
            {
                for(int i=0; i<smoothness; i++)
                {
                    float tempSize = sin(float(i)/float(smoothness)*(3.14/halvsirkler))*size;
                    uiBO.push_back(sin( ( float(x+0.1)/float(amnt) )*(3.14*helsirkler) )*spread);
                    uiBO.push_back(cos(( float(y+0.1)/float(amnt) )*(3.14*helsirkler))*spread);


                    uiBO.push_back(sin(( float(x+0.1)/float(amnt) )*(3.14*helsirkler))*spread);
                    uiBO.push_back(cos(( float(y+0.1)/float(amnt) )*(3.14*helsirkler))*spread-tempSize);


                    uiBO.push_back(sin(( float(x+0.1)/float(amnt) )*(3.14*helsirkler))*spread-tempSize);
                    uiBO.push_back(cos(( float(y+0.1)/float(amnt) )*(3.14*helsirkler))*spread-tempSize);

                }
            }
        }
	}
	std::vector <float> vertices;
	//high
    size=5;
    spread = 5.0;
    float ind=1;
    float total = amnt*amnt*amnt*smoothness;
	for(int y=0; y<amnt; y++)
	{
        for(int x=0; x<amnt; x++)
        {
            for(int z=0; z<amnt; z++)
            {
                for(int i=0; i<smoothness; i++)
                {
                    float tempSize = sin((ind/total)*(3.14/halvsirkler))*size;
                    vertices.push_back(sin((ind/total )*(3.14*helsirkler) )*spread);
                    vertices.push_back(cos((ind/total )*(3.14*helsirkler))*spread);
                    vertices.push_back(sin((ind/total )*(3.14*helsirkler))*spread*-tempSize*200);

                    vertices.push_back(sin(( ind/total )*(3.14*helsirkler))*spread);
                    vertices.push_back(cos(( ind/total )*(3.14*helsirkler))*spread*-tempSize);
                    vertices.push_back(sin(( ind/total )*(3.14*helsirkler))*spread*-tempSize*200);

                    vertices.push_back(sin(( ind/total )*(3.14*helsirkler))*spread*-tempSize);
                    vertices.push_back(cos(( ind/total )*(3.14*helsirkler))*spread*-tempSize);
                    vertices.push_back(sin(( ind/total )*(3.14*helsirkler))*spread);
                    ind++;
                }


            }
        }
	}








    vertElements = ( vertices.size()/3.0);
   GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(position);
    glEnableVertexAttribArray(texcoord);
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vertices.size()*sizeof( float ), &vertices[0], GL_STATIC_DRAW );
    glVertexAttribPointer(position,3,GL_FLOAT,GL_TRUE,0,0);
    GLuint vbou;
    glGenBuffers(1,&vbou);
    glBindBuffer(GL_ARRAY_BUFFER, vbou);
    glBufferData(GL_ARRAY_BUFFER, uiBO.size()*sizeof(float),&uiBO[0],GL_STATIC_DRAW);
    glVertexAttribPointer(texcoord,2,GL_FLOAT,GL_FALSE,0,0);

    std::cout << "texcoord = "<<texcoord<<std::endl;
    std::cout << "position = "<<position<<std::endl;
    xVBO = vbo;
    glBindVertexArray(0);
    return vao;
}

