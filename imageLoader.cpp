#include "imageLoader.h"

imageLoader::imageLoader()
{
    SDL_Init(SDL_INIT_EVERYTHING);
}

imageLoader::~imageLoader()
{
    for(std::vector<GLuint>::iterator i = forDeleting.begin(); i!= forDeleting.end(); i++)
    {
        glDeleteBuffers(1, &(*i));
    }
}
GLuint imageLoader::loadBMP(const char * imagepath)
{

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file)							    {printf("%s could not be opened.\n", imagepath); return 0;}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	delete [] data;
    filtering();
	return textureID;
}
GLuint imageLoader::sdlLoad(const char *file)
{
    SDL_Surface *tex=0;
    tex = IMG_Load(file);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if(!tex)
    {
        std::cout << "couldnt open texture file: "<<file<<std::endl;
        return 0;
    }
    if(tex->format->BytesPerPixel == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h,  0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
    else if (tex->format->BytesPerPixel == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h,  0, GL_RGB, GL_UNSIGNED_BYTE, tex->pixels);
    else
        fprintf(stderr,"image not supported.");
    filtering();
   // initTransparency();//gjør ikke noe spess forskjell som jeg ser
    SDL_FreeSurface(tex);
    forDeleting.push_back(texture);
    std::cout << "texture: "<<file<<" loaded."<<std::endl;
    return texture;
}
void imageLoader::initTransparency()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void imageLoader::filtering()
{
    // Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //glEnable(GL_BLEND);              //activate blending mode
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// set the blend mode
	// ... nice trilinear filtering.
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}
