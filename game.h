#pragma once

#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Game
{
public:
 
    unsigned int Width, Height;
   
    Game(unsigned int width, unsigned int height);
    ~Game();
   
    void Init();
    
    void ProcessInput(GLFWwindow* window, bool singlePlayer);
    void MoveTheBall();
    void Update();
    void Render();
private:
   bool recenterBall = false;
   glm::vec3 velocity= glm::vec3(0.02f, 0.02f, 0.0f);
    bool iscolided=false;
    unsigned int scoreLeft = 0;
    unsigned int scoreRight = 0;
    //Player1
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 p4;
    //Plear2 
    glm::vec3 p5;
    glm::vec3 p6;
    glm::vec3 p7;
    glm::vec3 p8;
    //Ball
    glm::vec3 p9;
    glm::vec3 p10;
    glm::vec3 p11;
    glm::vec3 p12;
};

#endif