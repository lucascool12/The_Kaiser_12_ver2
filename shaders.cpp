#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include "header.h"

GLuint MakeShader(std::string shader, GLenum type);
GLuint LinkProgram(GLuint vertex);

GLuint CompileAllShaders(){
    glClearColor(1, 0, 0, 0);

    std::ifstream vertex_file;
    std::ifstream frag_file;

    vertex_file.open("vertexShader.vert");
    frag_file.open("fragShader.frag");

    std::string vertexShader((std::istreambuf_iterator<char>(vertex_file)),std::istreambuf_iterator<char>());
    std::string fragmentShader((std::istreambuf_iterator<char>(frag_file)),std::istreambuf_iterator<char>());

    vertex_file.close();
    frag_file.close();

    GLuint vertexShaderID = MakeShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = MakeShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    GLint linkStatus;

    
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        printf("Error Linking program");
        glDetachShader(programID, vertexShaderID);
        glDetachShader(programID, fragmentShaderID);
        glDeleteProgram(programID);

        return 0;
    }

    //cursed();

    return programID;
}

GLuint LinkProgram(GLuint vertex){
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glLinkProgram(programID);

    return programID;
}

GLuint MakeShader(std::string shader, GLenum type) {

    const char *shaderCode = shader.c_str();
    GLuint shaderId = glCreateShader(type);

    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    GLint compileStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

    if (!compileStatus) {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        char *cMessage = new char[length];

        // Get additional information
        glGetShaderInfoLog(shaderId, length, &length, cMessage);
        printf("Cannot Compile Shader: %s", cMessage);
        delete[] cMessage;
        glDeleteShader(shaderId);
        return 0;
    }
    
    return shaderId;
}
