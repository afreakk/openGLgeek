#include "PhysObject.h"

PhysObject::PhysObject():rigidBody(0),physics(false),cubeShape(0)
{
    //ctor
}
void PhysObject::enablePhysicsBox(float MASS,float scaleX, float scaleY, float scaleZ, btBoxShape* box)
{
    hMotionState* motionState = new hMotionState(this,btTransform(btQuaternion(orientationV.x,orientationV.y,orientationV.z,orientationV.w),btVector3(translationV.x,translationV.y,translationV.z)));
    btScalar mass = MASS;
    btVector3 cubeInertia(0.0, 0.0, 0.0);
    if(!box)
        cubeShape= new btBoxShape(btVector3(scaleV.x*scaleX, scaleV.y*scaleY,scaleV.z*scaleZ)); //testx2
    else
        cubeShape = box;
    cubeShape->calculateLocalInertia(mass,cubeInertia);
    btRigidBody::btRigidBodyConstructionInfo cubeRigidCI(mass,motionState,cubeShape,cubeInertia);
    rigidBody = new btRigidBody(cubeRigidCI);
    Phys::getInstance()->addRigid(rigidBody);
    physics=true;
}
btRigidBody* PhysObject::getRigidBody()
{
    return rigidBody;
}
btBoxShape* PhysObject::getBoxShape()
{
    return cubeShape;
}

PhysObject::~PhysObject()
{
    if(rigidBody)
        delete rigidBody;
}
