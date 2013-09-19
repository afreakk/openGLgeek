#include "Car.h"

Car::Car()
{
    physx = Phys::getInstance();
}

Car::~Car()
{
    //dtor
}
void Car::keys()
{
  /*  float force=1;
    if(glfwGetKey( 'W' )==GLFW_PRESS)
        physx->addForce(0,sin(kk)*force,0,cos(kk)*force , translationV);
    if(glfwGetKey( 'S' )==GLFW_PRESS)
        physx->addForce(0,-sin(kk)*force,0,-cos(kk)*force ,translationV);
    if(glfwGetKey( 'A' )==GLFW_PRESS)
    {
        rotation(1.0,glm::vec3(0,1,0));
        kk+=(3.14*2.0)/360;
        physx->setRotation(0,orientationV.x,orientationV.y,orientationV.z,orientationV.w);
    }
    if(glfwGetKey( 'D' )==GLFW_PRESS)
    {
        rotation(-1.0,glm::vec3(0,1,0));
        kk-=(3.14*2.0)/360;
        physx->setRotation(0,orientationV.x,orientationV.y,orientationV.z,orientationV.w);
    }

*/
}
