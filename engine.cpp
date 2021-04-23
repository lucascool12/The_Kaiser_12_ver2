#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "header.h"


void Engine::Triangle::init(float v1[], float v2[], float v3[], GLenum use, GLuint shId){
    GLfloat vert[] = {
        v1[0], v1[1],
        v2[0], v2[1],
        v3[0], v3[1]
    };
    shaderId = shId;
    glGenBuffers(1,&id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vert),vert,use);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Engine::Triangle::draw(float oP, float zr, float sc){

}