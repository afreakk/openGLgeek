#include "Player.h"

Player::Player():rigidBody(0),physics(false)
{
    //ctor
}

Player::~Player()
{
    //dtor
}
void Player::enablePhysicsCapsule(float MASS,float radius, float height, glm::vec3 compensation)
{
    hMotionState* motionState = new hMotionState(this,btTransform(btQuaternion(orientationV.x,orientationV.y,orientationV.z,orientationV.w)
    ,btVector3(translationV.x,translationV.y,translationV.z)),compensation);
    btScalar mass = MASS;
    btVector3 cubeInertia(0.0, 0.0, 0.0);
    btCapsuleShape * capShape= new btCapsuleShape(radius,height); //testx
    capShape->calculateLocalInertia(mass,cubeInertia);
    btRigidBody::btRigidBodyConstructionInfo cubeRigidCI(mass,motionState,capShape,cubeInertia);
    rigidBody = new btRigidBody(cubeRigidCI);
    rigidBody->setSleepingThresholds(0,0);
    rigidBody->setAngularFactor(0.0);
    Phys::getInstance()->addRigid(rigidBody);
    Phys::getInstance()->addAction(this);
    physics=true;
}
void Player::hingeTo(btRigidBody* body,float distance)
{
    DistanceConstraint* hinge = new DistanceConstraint(*rigidBody,*body, btVector3(0.0, 0.0, 0.0),btVector3(0.0, 0.0, 0.0),distance);
    Phys::getInstance()->addConstrain(hinge);
}

void Player::debugDraw(btIDebugDraw* debugDrawer)
{
}
void Player::updateAction( btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
    float speed = 10.0*deltaTimeStep;
    float jump = 100;
    btVector3 velocity = rigidBody->getLinearVelocity();
    movement = glm::vec3(velocity.getX(),velocity.getY(),velocity.getZ());
    if(glfwGetKey( 'D' )==GLFW_PRESS)
        movement.x += speed;
    if(glfwGetKey( 'A' )==GLFW_PRESS)
        movement.x -= speed;
    if(glfwGetKey( 'W' )==GLFW_PRESS)
        movement.z -= speed;
    if(glfwGetKey( 'S' )==GLFW_PRESS)
        movement.z += speed;
    rigidBody->setLinearVelocity(btVector3(movement.x,movement.y,movement.z));
    if(glfwGetKey( GLFW_KEY_SPACE )==GLFW_PRESS)
        rigidBody->applyImpulse(btVector3(0.0,jump,0.0),btVector3(0.0,jump,0.0));
}
