#include "Window.h"

Window::Window()
{
    //ctor
}

Window::~Window()
{
    glfwTerminate();
}
void Window::init()
{
    glfwInit();
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
    glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );
    glfwOpenWindow( 800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
    glfwSetWindowTitle( "oGeek" );
}
void Window::swapB()
{
    glfwSwapBuffers();
}
void Window::setTitle(const char* title)
{
    glfwSetWindowTitle( title );
}
bool Window::quit()
{
    if(glfwGetKey(GLFW_KEY_ESC)==GLFW_PRESS)
        return true;
    if(!glfwGetWindowParam(GLFW_OPENED))
        return true;
    return false;
}
void Window::initGlew()
{
    glewExperimental = GL_TRUE;
    glewInit();
}
