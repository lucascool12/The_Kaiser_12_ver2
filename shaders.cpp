#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "header.h"

GLuint MakeShader(std::string shader, GLenum type);
GLuint LinkProgram(GLuint vertex);
void cursed();

std::string vertexShader = R"(
    #version 430
    layout(location = 0) in vec2 pos;
    void main()
    {
        gl_Position = vec4(pos, 0, 1);
    }
)";


std::string fragmentShader = R"(
    #version 430
    out vec4 outputColor;
    void main() 
    {
        outputColor = vec4(1, 1, 1, 1); // white color
    }
)";

GLuint CompileAllShaders(){
    glClearColor(1, 0, 0, 0);
    GLuint vertexShaderID = MakeShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = MakeShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    //cursed();

    return programID;
}

void cursed(){
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
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

    return shaderId;
}
