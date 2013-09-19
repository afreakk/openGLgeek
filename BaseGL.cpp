#include "BaseGL.h"
std::vector<BaseGL*> BaseGL::objects;
void BaseGL::addObj(BaseGL* object)
{
    objects.push_back(object);
}
void BaseGL::drawAll()
{
    for(unsigned int i=0; i < objects.size(); i++)
        objects[i]->draw();
}
void BaseGL::draw()
{
}
