#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H
#include "Object3D.h"
#include "Phys.h"
#include <btBulletDynamicsCommon.h>
#include "hMotionState.h"
class PhysObject:public Object3D
{
    public:
        PhysObject();
        virtual ~PhysObject();
        void enablePhysicsBox(float MASS,float scaleX, float scaleY, float scaleZ, btBoxShape* box=0);
        btBoxShape* getBoxShape();
        btRigidBody* getRigidBody();
    protected:
    private:
        btRigidBody* rigidBody;
        btBoxShape *cubeShape;
        bool physics;

};

#endif // PHYSOBJECT_H
