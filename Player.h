#ifndef PLAYER_H
#define PLAYER_H
#include "Object3D.h"
#include <GL/glfw.h>
#include "Phys.h"
#include <btBulletDynamicsCommon.h>
#include "hMotionState.h"
#include "DistanceConstraint.h"
class Player:public Object3D, btActionInterface
{
    public:
        Player();
        void enablePhysicsCapsule(float MASS,float radius, float height, glm::vec3 compensation);
        virtual ~Player();
        void hingeTo(btRigidBody* body,float distance);
    protected:
    private:
        void debugDraw(btIDebugDraw* debugDrawer);
        void updateAction( btCollisionWorld* collisionWorld, btScalar deltaTimeStep);
        glm::vec3 movement;
        btRigidBody* rigidBody;
        bool physics;
};

#endif // PLAYER_H
