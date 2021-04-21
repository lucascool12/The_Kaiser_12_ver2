#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
#include <chrono>
#include "header.h"


GLuint vBufferObjID;
GLuint programID;

GLfloat verts[] = {
        -1.0,  1.0,
        1.0,  1.0,
        0,  -0.5
    };

GLuint elapsedTimeUniform;
GLuint moveSelf;
GLuint mousePosition;
GLuint windowDimension;
GLuint timeDif;

int global_button,global_state;
int timeSnapshot;

void Init() {
    programID = CompileAllShaders();

    elapsedTimeUniform = glGetUniformLocation(programID,"time");
    moveSelf = glGetUniformLocation(programID,"mouseDown");
    mousePosition = glGetUniformLocation(programID, "mousePos");
    windowDimension = glGetUniformLocation(programID, "window");
    timeDif = glGetUniformLocation(programID, "timeDif");

    glGenBuffers(1, &vBufferObjID);
    glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //clears buffer
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);
    glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

    glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glUseProgram(0);
    glutSwapBuffers();
    glutPostRedisplay();
}

void MakeWindow(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("OpenGL Testing");
    glewInit();
}


void mouseStateChanged(int button, int state, int x, int y){
    global_button = button;
    global_state = state;

    glUseProgram(programID);
    
    if(global_button == GLUT_LEFT_BUTTON && state == 1){ //press
        glUniform1i(moveSelf, false);

        // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
        // GLfloat oldvec[6];
        // glGetBufferSubData(GL_ARRAY_BUFFER,0,sizeof(verts),&oldvec);
        // GLfloat newvec[sizeof(verts)/4];
        // for(int i = 0; i < 3; i++)
        //     printf("A%f B%f ", oldvec[2*i], oldvec[2*i+1]);

        // printf("\n"); 

        // for(int i = 0; i< 3; i++){
        //     newvec[2*i] = oldvec[2*i];
        //     newvec[2*i + 1] = oldvec[2*i + 1];
        // }
        // printf("%d\n",sizeof(newvec)/4);
        
        // for(int i = 0; i < sizeof(newvec)/(4*2);i++)
        // printf("Z%f X%f ",newvec[2*i],newvec[2*i+1]);
        // printf("X %d Y %d xl %d yl %d",x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
        // printf("\n\n");
        // //glBufferData(GL_ARRAY_BUFFER,sizeof(newvec),newvec,GL_STREAM_DRAW);
        // glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(newvec),&newvec[0]);
        // glBindBuffer(GL_ARRAY_BUFFER,0);

    } else if(global_button == GLUT_LEFT_BUTTON){ //release 
        glUniform1i(moveSelf, true);
        glUniform2f(mousePosition, (GLfloat)x, (GLfloat)y);
        glUniform2f(windowDimension,(GLfloat)glutGet(GLUT_WINDOW_WIDTH), (GLfloat)glutGet(GLUT_WINDOW_HEIGHT));
    }
    

    glUseProgram(0);
}

#if defined FPS
    int frames = 0;
    std::chrono::_V2::steady_clock::time_point start;

    void FPS(){
        frames++;
        if(frames<2){
            start = std::chrono::steady_clock::now();
        }else{
            auto end = std::chrono::steady_clock::now();
            int64_t tiime= std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            printf("%f\n",1000000000.0/((float)tiime));
            frames = 0;
        }
    }
#endif
 
void mouseMove(int x, int y){
    if(global_button == GLUT_LEFT_BUTTON || global_state == 0){
        #if defined FPS
            FPS();
        #endif
        glUseProgram(programID);

        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);

        glUniform2f(mousePosition, (GLfloat)x, (GLfloat)y);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

}

int main(int argc, char **argv){
    MakeWindow(argc,argv);
    Init();

    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseStateChanged);
    glutDisplayFunc(Display);

    glutMainLoop();
    return 0;
}