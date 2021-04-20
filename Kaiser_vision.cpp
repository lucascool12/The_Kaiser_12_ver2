#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
#include <chrono>
#include "header.h"


GLuint vboid;
GLuint programID;
GLfloat verts[] = {
        -1.0,  1.0,
        1.0,  1.0,
        0,  -0.5
    };

void Init(){
    programID = CompileAllShaders();

    glGenBuffers(1, &vboid);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //clears buffer
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glUseProgram(0);
    glutSwapBuffers();
}

void MakeWindow(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("OpenGL Testing");
    glewInit();
}



void click(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);
        glBindBuffer(GL_ARRAY_BUFFER, vboid);
        GLfloat verts2[6];
        printf("\n");
        for(int i = 0;i<6;i++){
            if( i%2 == 0)verts2[i] = verts[i] + (x-WINDOW_WIDTH/2)/((float)WINDOW_WIDTH);
            else verts2[i] = verts[i] - (y-WINDOW_HEIGHT/2)/((float)WINDOW_HEIGHT);
            //printf("%f %d %d %d\n",verts2[i],x,y,state);
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts2), verts2, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glUseProgram(0);
        glutSwapBuffers();
    }
}

int global_button,global_state;

void mouseStateChanged(int button, int state, int x, int y){
    global_button = button;
    global_state = state;
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

        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vboid);

        GLfloat verts2[6];

        for(int i = 0; i<3;i++){
            verts2[i * 2] = verts[i * 2] + (x*2.0-WINDOW_WIDTH)/(WINDOW_WIDTH); 
            verts2[i * 2 + 1] = verts[i * 2 + 1] - (y*2.0-WINDOW_HEIGHT)/(WINDOW_HEIGHT);
        }
        

        glBufferData(GL_ARRAY_BUFFER, sizeof(verts2), verts2, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glUseProgram(0);
        glutSwapBuffers();
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