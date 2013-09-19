#include <iostream>
#include "ImportModel.h"
#include "Window.h"
#include "shaderCompile.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Cruiser.h"
#include "Water.h"
#include "Camera.h"
#include "Object3D.h"
#include "Car.h"
#include "Phys.h"
#include "PhysObject.h"
#include "Player.h"
/*char* fps(const double & globalTime)
{
     std::stringstream caption;

    //Calculate the frames per second and create the string
    caption << "Average Frames Per Second: " << 1 / ( globalTime );
    return caption.c_
}*/
int main()
{
    Phys *physx;
    physx = Phys::getInstance();
    physx->init();
    float resX = 800;
    float resY = 600;
    Window window;
    window.init();
    window.initGlew();
    shaderCompile shaderBuilder;
    GLuint waterShader = shaderBuilder.loadShader("shaders/vert","shaders/fragWater");
    GLuint nShader = shaderBuilder.loadShader("shaders/vert","shaders/frag");
    Camera camera(resX,resY,1000000.0f);
    camera.addShader(waterShader);
    camera.addShader(nShader);
    BaseGL master;
    Object3D sun;
    sun.init("sphere.obj",nShader);
    int xCrates = 14;
    int yCrates = 8;
    PhysObject crate[xCrates][yCrates];
    PhysObject ground;
    PhysObject hookCrate;
    Player player;
    player.init("silotest.obj",nShader);
    player.position(glm::vec3(10,40.0,-30));
    player.enablePhysicsCapsule(10000,1.8,0.5,glm::vec3(0,-1.6*1.8,0));
    ground.init("Crate1.obj",nShader);
    hookCrate.init(ground.getModel(),nShader);
    hookCrate.position(glm::vec3(2,25,-30));
    hookCrate.enablePhysicsBox(0,1,1,1);
    ground.position(glm::vec3(0.0,0.0,-30.0));
    ground.scale(glm::vec3(30.0, 1.0, 10.0));
    ground.enablePhysicsBox(0,1,1,1);
    bool first=true;
    for(int x=0; x<xCrates; x++)
    {
        for(int y=0; y<yCrates; y++)
        {

            crate[x][y].init(ground.getModel(),nShader);
            crate[x][y].position(glm::vec3(-xCrates*2+(x+1)*4.0,1.0+(yCrates*4)-(y+1)*4.0,-30.0));
            if(first)
                crate[x][y].enablePhysicsBox(100,1,1,1);
            else
                crate[x][y].enablePhysicsBox(100,1,1,1,crate[0][0].getBoxShape());
            first=false;
        }
    }
    player.hingeTo(hookCrate.getRigidBody(),10);
    sun.scale(glm::vec3(1.0));
    glEnable(GL_DEPTH_TEST);
    glm::vec3 sunPos;
    double time = glfwGetTime();
    double globalTime = time;

    while(!window.quit())
    {
        globalTime = glfwGetTime()-time;
        time = glfwGetTime();
        camera.lookAtFrom(player.getTranslation(),glm::vec3(0,10,10));
        camera.updateLightPosition(sunPos);
        camera.updateFloat("speed",time);

        glClearColor(0.01, 0.0, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        sunPos.x = sin(time/1.0)*100;
        sunPos.z = cos(time/1.0)*100-30;
        sunPos.y = 200;
        sun.position(sunPos);
        master.drawAll();
        window.swapB();
        physx->update(globalTime);
    }
    return 0;
}
