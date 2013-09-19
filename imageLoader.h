#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
class imageLoader
{
    public:
        imageLoader();
        virtual ~imageLoader();
        GLuint loadBMP(const char* imagepath);
        GLuint sdlLoad(const char *file);
        void initTransparency();
    protected:
    private:
        std::vector<GLuint> forDeleting;
        void filtering();
};

#endif // IMAGELOADER_H
