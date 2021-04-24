#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
#include <chrono>
#include <cmath>
#include "header.h"


GLuint vBufferObjID;
GLuint vBufferObjID2;
GLuint programID;

GLfloat verts[] = {
        -0.5,  0.5,
        0.5,  0.5,
        0,  -0.5
    };

// GLuint elapsedTimeUniform;
// GLuint moveSelf;
// GLuint mousePosition;
// GLuint windowDimension;
// GLuint timeDif;

int global_button,global_state;
int timeSnapshot;

GLuint rot;
GLuint oPos;
GLuint scale;
GLuint window;

void Init() {
    programID = CompileAllShaders();// trans vert

    // elapsedTimeUniform = glGetUniformLocation(programID,"time");
    // moveSelf = glGetUniformLocation(programID,"mouseDown");
    // mousePosition = glGetUniformLocation(programID, "mousePos");
    // windowDimension = glGetUniformLocation(programID, "window");
    // timeDif = glGetUniformLocation(programID, "timeDif");

    rot = glGetUniformLocation(programID,"rotAngle");
    oPos = glGetUniformLocation(programID,"oPos");
    scale = glGetUniformLocation(programID,"scale");
    window = glGetUniformLocation(programID,"w");

    GLuint temp_array[2];
    glGenBuffers(2, temp_array);
    vBufferObjID = temp_array[0];
    vBufferObjID2 = temp_array[1];
    glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //clears buffer
}
void transform(GLfloat oPos1,GLfloat oPos2, GLfloat s, GLfloat rotate){
    glUniform2f(oPos,oPos1,oPos2);
    glUniform1f(scale,s);
    glUniform1f(rot,rotate*(M_PI)/180.0);
    glUniform2f(window,(float)glutGet(GLUT_WINDOW_WIDTH),(float)glutGet(GLUT_WINDOW_HEIGHT));
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    printf("%d %d %f %f\n",glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),(float)glutGet(GLUT_WINDOW_WIDTH)/600.0,
    (float)glutGet(GLUT_WINDOW_HEIGHT)/600.0);
    glUseProgram(programID);
    //glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
    transform((glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,-0.2,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    //transform(0.5,0,1,0);
    //printf("%f  %f\n",(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    
    transform((-glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1+0.5,0.2,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1.25,(-glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    //transform(-0.5,0,1,0);
    //printf("%f  %f\n",(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID2);
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
    glutInitWindowPosition(0, 0);
    glutCreateWindow("my dick is bigger than yours ayami");
    glewInit();
}


// void mouseStateChanged(int button, int state, int x, int y){
//     global_button = button;
//     global_state = state;

//     glUseProgram(programID);
    
//     if(global_button == GLUT_LEFT_BUTTON && state == 1){ //press
//         glUniform1i(moveSelf, false);

//         // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
//         // GLfloat oldvec[6];
//         // glGetBufferSubData(GL_ARRAY_BUFFER,0,sizeof(verts),&oldvec);
//         // GLfloat newvec[sizeof(verts)/4];
//         // for(int i = 0; i < 3; i++)
//         //     printf("A%f B%f ", oldvec[2*i], oldvec[2*i+1]);

//         // printf("\n"); 

//         // for(int i = 0; i< 3; i++){
//         //     newvec[2*i] = oldvec[2*i];
//         //     newvec[2*i + 1] = oldvec[2*i + 1];
//         // }
//         // printf("%d\n",sizeof(newvec)/4);
        
//         // for(int i = 0; i < sizeof(newvec)/(4*2);i++)
//         // printf("Z%f X%f ",newvec[2*i],newvec[2*i+1]);
//         // printf("X %d Y %d xl %d yl %d",x,y,glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
//         // printf("\n\n");
//         // //glBufferData(GL_ARRAY_BUFFER,sizeof(newvec),newvec,GL_STREAM_DRAW);
//         // glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(newvec),&newvec[0]);
//         // glBindBuffer(GL_ARRAY_BUFFER,0);

//     } else if(global_button == GLUT_LEFT_BUTTON){ //release 
//         glUniform1i(moveSelf, true);
//         glUniform2f(mousePosition, (GLfloat)x, (GLfloat)y);
//         glUniform2f(windowDimension,(GLfloat)glutGet(GLUT_WINDOW_WIDTH), (GLfloat)glutGet(GLUT_WINDOW_HEIGHT));
//     }
    

//     glUseProgram(0);
// }

// #if defined FPS
//     int frames = 0;
//     std::chrono::_V2::steady_clock::time_point start;

//     void FPS(){
//         frames++;
//         if(frames<2){
//             start = std::chrono::steady_clock::now();
//         }else{
//             auto end = std::chrono::steady_clock::now();
//             int64_t tiime= std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//             printf("%f\n",1000000000.0/((float)tiime));
//             frames = 0;
//         }
//     }
// #endif
 
// void mouseMove(int x, int y){
//     if(global_button == GLUT_LEFT_BUTTON || global_state == 0){
//         #if defined FPS
//             FPS();
//         #endif
//         glUseProgram(programID);

//         glClear(GL_COLOR_BUFFER_BIT);

//         glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);

//         glUniform2f(mousePosition, (GLfloat)x, (GLfloat)y);

//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         glUseProgram(0);
//         glBindBuffer(GL_ARRAY_BUFFER,0);
//     }

// }

int main(int argc, char **argv){
    MakeWindow(argc,argv);
    Init();

    //glutMotionFunc(mouseMove);
    //glutMouseFunc(mouseStateChanged);
    glutDisplayFunc(Display);

    glutMainLoop();
    return 0;
}