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
#include <vector>
#include "header.h"

GLuint MakeShader(std::string shader, GLenum type);
GLuint LinkProgram(GLuint vertex);

void Engine::shaderProgram::init(std::vector<std::string> Shaders,std::vector<GLenum> identifier){
    std::vector<GLenum> Ids;
    for(int i = 0 ; i < Shaders.size(); i++){
        Ids.push_back(MakeShader(Shaders[i],identifier[i]));
    }
    id = glCreateProgram();
    for(int i = 0; i < Ids.size(); i++){
        glAttachShader(id,Ids[i]);
    }


    GLint linkStatus;

    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        printf("Error Linking program");
        for(int i = 0; i < Ids.size(); i++){
            glDetachShader(id,Ids[i]);
        }
        glDeleteProgram(id);
        id = 0;
    }
}

int Engine::shaderProgram::getAndSaveUniform(string var){
    if(vars.find(var) == vars.end()){
        GLuint uniId;
        uniId = glGetUniformLocation(id,var.c_str());
        if(uniId == -1) return 1;
        vars[var] = uniId;
        return 0;
    }
    return 0;
}

int Engine::shaderProgram::Uniform1f(string var, GLfloat v0){
    //hash map to find already used variables?
    if(getAndSaveUniform(var)) return 1;
    glUniform1f(vars[var],v0);
    return 0;
}

int Engine::shaderProgram::Uniform2f(string var, GLfloat v0, GLfloat v1){
    if(getAndSaveUniform(var)) return 1;
    glUniform2f(vars[var],v0,v1);
    return 0;
}

int Engine::shaderProgram::Uniform3f(string var, GLfloat v0, GLfloat v1, GLfloat v2){
    if(getAndSaveUniform(var)) return 1;
    glUniform3f(vars[var],v0,v1,v2);
    return 0;
}

int Engine::shaderProgram::Uniform4f(string var, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    if(getAndSaveUniform(var)) return 1;
    glUniform4f(vars[var],v0,v1,v2,v3);
    return 0;
}

int Engine::shaderProgram::Uniform1i(string var, GLint v0){
    if(getAndSaveUniform(var)) return 1;
    glUniform1i(vars[var],v0);
    return 0;
}

int Engine::shaderProgram::Uniform2i(string var, GLint v0, GLint v1){
    if(getAndSaveUniform(var)) return 1;
    glUniform2i(vars[var],v0,v1);
    return 0;
}

int Engine::shaderProgram::Uniform3i(string var,GLint v0, GLint v1, GLint v2){
    if(getAndSaveUniform(var)) return 1;
    glUniform3i(vars[var],v0,v1,v2);
    return 0;
}

int Engine::shaderProgram::Uniform4i(string var, GLint v0, GLint v1, GLint v2, GLint v3){
    if(getAndSaveUniform(var)) return 1;
    glUniform4i(vars[var],v0,v1,v2,v3);
    return 0;
}

int Engine::shaderProgram::Uniform1ui(string var, GLuint v0){
    if(getAndSaveUniform(var)) return 1;
    glUniform1ui(vars[var],v0);
    return 0;
}

int Engine::shaderProgram::Uniform2ui(string var, GLuint v0, GLuint v1){
    if(getAndSaveUniform(var)) return 1;
    glUniform2ui(vars[var],v0,v1);
    return 0;
}

int Engine::shaderProgram::Uniform3ui(string var, GLuint v0, GLuint v1, GLuint v2){
    if(getAndSaveUniform(var)) return 1;
    glUniform3ui(vars[var],v0,v1,v2);
    return 0;
}

int Engine::shaderProgram::Uniform4ui(string var, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
    if(getAndSaveUniform(var)) return 1;
    glUniform4ui(vars[var],v0,v1,v2,v3);
    return 0;
}




GLuint CompileAllShaders(){
    glClearColor(1, 0, 0, 0);

    std::ifstream vertex_file;
    std::ifstream frag_file;

    vertex_file.open("transformationShader.vert"); //!!!!
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
