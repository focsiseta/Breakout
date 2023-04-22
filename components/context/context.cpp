#include "context.h"

GLFWwindow* createWindow(const char* windowName, int height,int width) {
    if (windowName == nullptr) windowName = "Default name";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_HINT);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_HINT);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(height, width, windowName, nullptr, nullptr);
    if (window == nullptr) {

        std::cout << "Couldn't create window" << std::endl;
        glfwTerminate();
        return nullptr;


    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return nullptr;
    }
	return window;

}
int checkErrors(){
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "Error occured" << std::endl;
        return -1;
    }
    return 0;

}