
#include "game.h"
#include "ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
Game::Game(unsigned int width, unsigned int height)
    :   Width(width), Height(height)
{
    p1 = glm::vec3(1.8f, -0.5f, 0.0f);
    p2 = glm::vec3(1.9f, -0.5f, 0.0f);
    p3= glm::vec3(1.8f, -1.0f, 0.0f);
    p4= glm::vec3(1.9f, -1.0f, 0.0f);
    p5= glm::vec3(-1.8f, 0.5f, 0.0f);
    p6= glm::vec3(-1.9f, 0.5f, 0.0f);
    p7= glm::vec3(-1.8f, 1.0f, 0.0f);
    p8= glm::vec3(-1.9f, 1.0f, 0.0f);
    p9 = glm::vec3(0.0f,0.0f,0.0f);
    p10 = glm::vec3(-0.1f,0.0f,0.0f);
    p11 = glm::vec3(0.0f, -0.1f, 0.0f);
    p12 = glm::vec3(-0.1f, -0.1f, 0.0f);

}

Game::~Game()
{

}

void Game::Init()
{
    
   Shader shader= ResourceManager::LoadShader("PlayerShader.vert"
        , "PlayerShader.frag", NULL, "test");
   shader.Use();
   glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.0f, -1.0f);
   shader.SetMatrix4("u_MVP",proj);

   
}

void Game::Update()
{
    MoveTheBall();
    float vertices[] = {
   p1.x,p1.y,p1.z, 1.0f,1.0f,0.0f, 
    p2.x,p2.y,p2.z, 1.0f,1.0f,0.0f,
   p3.x,p3.y,p3.z,  1.0f,1.0f,0.0f,
    p4.x,p4.y,p4.z, 1.0f,1.0f,0.0f,
    p5.x,p5.y,p5.z, 1.0f,0.0f,0.0f,
    p6.x,p6.y,p6.z, 1.0f,0.0f,0.0f,
   p7.x,p7.y,p7.z,  1.0f,0.0f,0.0f,
    p8.x,p8.y,p8.z, 1.0f,0.0f,0.0f,
    p9.x,p9.y,p9.z, 1.0f, 0.5f, 0.2f,
    p10.x,p10.y,p10.z,1.0f, 0.5f, 0.2f,
    p11.x,p11.y,p11.z,1.0f, 0.5f, 0.2f,
    p12.x,p12.y,p12.z,1.0f, 0.5f, 0.2f,
    };

    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    
}
void Game::MoveTheBall() {
    auto hight = std::abs(p7.y - p5.y);
    auto width = std::abs(p6.x - p5.x);
    
    //Moving the ball
    if (recenterBall == true)
    {
        p9 = glm::vec3(0.0f, 0.0f, 0.0f);
        p10 = glm::vec3(-0.1f, 0.0f, 0.0f);
        p11 = glm::vec3(0.0f, -0.1f, 0.0f);
        p12 = glm::vec3(-0.1f, -0.1f, 0.0f);
        velocity = glm::vec3(0.02f, 0.02f, 0.0f);
        recenterBall = false;
    }
    if (p9.y >= 1.5f)
    {
        velocity.y *= -1;
    }
    if (p12.y <= -1.5f)
    {
        velocity.y *= -1;
    }
    if ((p9.x > p1.x && p9.x < p1.x+width)&&(p9.y>p4.y&&p9.y<p4.y+ hight)&&iscolided==false )
    {
        velocity.x *= -1;
        iscolided = true;
        
    }
     if ((p9.x > p5.x && p9.x < p5.x+ width)&&(p9.y>p5.y&&p9.y<p5.y+ hight)&&iscolided==true)
    {
        velocity.x *= -1;
        iscolided = false;
    }
    

    if (p9.x >= 2.0f)
    {
        scoreLeft++;
       
        std::cout << std::to_string(scoreLeft)+":"+std::to_string(scoreRight) << std::endl;
        recenterBall = true;
        iscolided = false;
    }
    if (p9.x <= -2.0f)
    {
        scoreRight++;
        std::cout << std::to_string(scoreLeft) + ":" + std::to_string(scoreRight) << std::endl;
        recenterBall = true;
        iscolided = false;
        
    }
    p9 += velocity;
    p10 += velocity;
    p11 += velocity ;
    p12 += velocity ;
    
}
void Game::ProcessInput(GLFWwindow* window,bool singlePlayer)
{
    
    if (!(singlePlayer==true))
    {
        if (glfwGetKey(window, GLFW_KEY_UP))
        {
            if (p1.y < 1.40f)
            {
                p1.y += 0.1;
                p2.y += 0.1;
                p3.y += 0.1;
                p4.y += 0.1;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_W))
        {
            if (p8.y < 1.40f)
            {
                p5.y += 0.1;
                p6.y += 0.1;
                p7.y += 0.1;
                p8.y += 0.1;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_S))
        {


            if (p8.y > -0.9f)
            {
                p5.y -= 0.1;
                p6.y -= 0.1;
                p7.y -= 0.1;
                p8.y -= 0.1;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_DOWN))
        {

            if (p1.y > -0.9f)
            {
                p1.y -= 0.1;
                p2.y -= 0.1;
                p3.y -= 0.1;
                p4.y -= 0.1;
            }

        }
       
   
    }
    else
    {
        p1.y = p9.y + 0.2;
        p2.y = p10.y + 0.2;
        p3.y = p11.y - 0.2;
        p4.y = p12.y - 0.2;
        if (glfwGetKey(window, GLFW_KEY_W))
        {
            if (p8.y < 1.40f)
            {
                p5.y += 0.1;
                p6.y += 0.1;
                p7.y += 0.1;
                p8.y += 0.1;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_S))
        {


            if (p8.y > -0.9f)
            {
                p5.y -= 0.1;
                p6.y -= 0.1;
                p7.y -= 0.1;
                p8.y -= 0.1;
            }

        }
        
    }
       

       
  
}

void Game::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
}