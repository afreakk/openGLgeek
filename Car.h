#ifndef CAR_H
#define CAR_H
#include "Object3D.h"
#include <GL/glfw.h>
#include "Phys.h"
class Car:public Object3D
{
    public:
        Car();
        virtual ~Car();
        void keys();
    protected:
    private:
        Phys * physx;
        float kk=0;
};

#endif // CAR_H
