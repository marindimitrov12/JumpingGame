
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include"IndexBuffer.h"
#include <iostream>
#include "ResourceManager.h"
#include "glm/gtc/matrix_transform.hpp"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool singlePlayer=true;

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game JumpingGame(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, true);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2DPong", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


    
    JumpingGame.Init();

    
    

    unsigned int indices[] = { 
        0, 1, 3,   
        0, 3, 2,   
        4, 5, 7,
        4, 7, 6,
        8,9,11,
        8,11,10
    
    };
   
    VertexArray va;
    VertexBuffer vb(nullptr,sizeof(glm::vec3)*1000);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    va.AddBuffer(vb,layout);

    IndexBuffer ib(indices, sizeof(indices));

   


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
       
        JumpingGame.ProcessInput(window,singlePlayer);
        JumpingGame.Update();
        va.Bind();
        JumpingGame.Render();
        glfwSwapBuffers(window);

        
    }

   
    ResourceManager::Clear();
    va.~VertexArray();
    vb.~VertexBuffer();
    ib.~IndexBuffer();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
   // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        singlePlayer = false;
    if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT)
        singlePlayer = true;
   
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}