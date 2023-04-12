#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



class Shader
{
public:
    
    unsigned int ID;
    Shader() { }
    Shader& Use();
    void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 
    void    SetMatrix4(const std::string& name,const glm::mat4& matrix);
private:
    
    void    checkCompileErrors(unsigned int object, std::string type);
};

#endif