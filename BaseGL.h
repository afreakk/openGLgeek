#ifndef BASEGL_H
#define BASEGL_H
#include <vector>

class BaseGL
{
    public:
        void drawAll();
        virtual void draw();
    protected:
        void addObj(BaseGL* object);
    private:
        static std::vector<BaseGL*> objects;

};

#endif // BASEGL_H
