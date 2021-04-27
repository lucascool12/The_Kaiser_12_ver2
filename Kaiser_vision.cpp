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
        -0.5,  -0.5,
        0.5,  -0.5,


        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,
        1.0,    1.0,    1.0,    1.0,

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
GLuint vaoId;

GLushort order2[] = {
        0,  1,  2,
        1,  2,  3
    };
short width;
short height;
GLfloat vertices[50*40*4][2];
GLfloat color[50*40*4][4];
GLushort order[50*40*4];
GLfloat master[50*40*4*2*40*40*4*4];
int verticesIndex = 0;
int orderIndex = 0;
int colorIndex = 0;

void import(){
    FILE* bmpfile;
    bmpfile = fopen("giraffe.bmp","r");
    //bmpfile = fopen("test2.bmp","r");
    fseek(bmpfile,0xA,SEEK_SET);
    short addres_offset;
    fread(&addres_offset,sizeof(addres_offset),1,bmpfile);
    fseek(bmpfile,0x12,SEEK_SET);
    fread(&width,sizeof(addres_offset),1,bmpfile);
    fseek(bmpfile,0x16,SEEK_SET);
    fread(&height,sizeof(addres_offset),1,bmpfile);
    printf("%d %d %d\n",addres_offset,width,height);
    //fseek(bmpfile,addres_offset+267,SEEK_SET);
    fseek(bmpfile,addres_offset,SEEK_SET);
    uint8_t test[width][height][4];
    fread(&test,4,width*height,bmpfile);
    fclose(bmpfile);
    FILE* output;
    output = fopen("test.bmpvectors","w");
    fwrite(&test,4,width*height,output);
    fclose(output);
    printf("fsd %d %d\n",width,height);
    // for(int i = width-1; i >= 0 ; i--){
    //     printf("\n \n row %2d %2d \n \n",4-i,i);
    //     for(int j = 0; j < height; j++){
    //         for(int u = 0 ; u < 4 ; u++){
    //             int tmp = 0x00000000000FF&( test[i][j][u] );
    //             printf("%3d ",tmp);
    //         }
    //         printf("   %2d \n",j);
    //     } 
    // }

    //int temp = 0x0000000FF&( test[19-1][7][1] );
    //printf("%d",temp);
    //float vertices[width*4*height*4][2];
    //int verticesIndex = 0;
    //int8_t color[width*4*height*4][4];
    //GLuint order[width*4*height*4];

    for(int i = width-1; i >= 0 ; i--){
        for(int j = 0; j < height; j++){
            int tmp = 0x00000000000FF&( test[i][j][3] );
            if(tmp != 0){
                //printf("%d\n",tmp);
                float y = -((width-1 - i) - width/2.0); //relative to center of img
                float x = j - height/2.0;
                for(int v = 0; v < 6 ; v++){
                    order[orderIndex] = v + ((v > 2 && v<4) ? -2 : 0) + ((v>3) ? -1 : 0) + ((v>4) ? -2 : 0)  + verticesIndex;
                    //printf("%d: ",printf("%u ",order[orderIndex]));
                    orderIndex++;
                }
                //printf(" order %d %d\n",orderIndex,verticesIndex);
                for(int v = 0; v < 4; v++){
                    int negy = (v < 2) ? 1 : -1;
                    vertices[verticesIndex][0] = (x - 0.5*pow(-1 , v))/(float)width;
                    vertices[verticesIndex][1] = (y + 0.5*negy)/(float)height;
                    //printf("dfgv %d %d %f %f %f %f\n",i,j,x,y,x - 0.5*pow(-1 , v),y + 0.5*negy);
                    //printf("%d  ",printf("%d: %f %f\n",verticesIndex,vertices[verticesIndex][0],vertices[verticesIndex][1]));
                    //printf("%d: %f %f\n",verticesIndex,vertices[verticesIndex][0],vertices[verticesIndex][1]);
                    //printf(": %f\n",vertices[verticesIndex][1]);
                    for(int m = 0 ; m < 4; m++){
                        color[colorIndex][m] = test[i][j][3-m]/255.0;
                    }
                    colorIndex++;
                    
                    verticesIndex++;
                }
                
            }
        } 
    }
    for(int i = 0; i < verticesIndex*2;i+=2){
        master[i] = vertices[i/2 + i%2][0];
        master[i + 1] = vertices[i/2 + i%2][1];
        //printf("%f %f\n",vertices[i/2 + i%2][0],vertices[i/2 + i%2][1]);
    }
    for(int i = 0; i < colorIndex*4;i += 4){
        master[i + verticesIndex*2 + 1] = color[i/4 + i%4][0];
        master[i + verticesIndex*2 + 2] = color[i/4 + i%4][1];
        master[i + verticesIndex*2 + 3] = color[i/4 + i%4][2];
        master[i + verticesIndex*2 + 4] = color[i/4 + i%4][3];
        //printf("%d %f %f %f %f\n",i,color[i/4 + i%4][0],color[i/4 + i%4][1],color[i/4 + i%4][2],color[i/4 + i%4][3]);
    }
    //printf("\n%f %f   %f %f %f %f\n",master[verticesIndex-1],master[verticesIndex],
    //master[verticesIndex + verticesIndex - 3],master[verticesIndex + verticesIndex - 2],master[verticesIndex + verticesIndex - 1],master[verticesIndex + verticesIndex]);
    // printf("%d \n",orderIndex);
    // for(int i = 0; i <orderIndex; i++){
    //     //int tmp = 0x00000000000FF&( order[i] );
    //     printf("%d %3u \n",i,order[i]);
    // }
    // for(int i = 0; i <verticesIndex; i++){
    //    //int tmp = 0x00000000000FF&( order[i] );
    //    printf("%d %f %f\n",i,vertices[i][0],vertices[i][1]);
    // }
    // printf("\n");
    // for(int i = 0; i <=verticesIndex*2; i+=2){
    //    //int tmp = 0x00000000000FF&( order[i] );
    //    printf("%d %f %f\n",i,master[i],master[i+1]);
    // }

    // for(int i = 0; i <=verticesIndex*2; i+=2){
    //    //int tmp = 0x00000000000FF&( order[i] );
    //    printf("%d %f %f\n",i,master[i],master[i+1]);
    // }

    // for(int i = 0; i <=colorIndex*4; i+=4){
    //    //int tmp = 0x00000000000FF&( order[i] );
    //    printf("%d %f %f %f %f\n",i,master[i + verticesIndex*2 + 1],master[i + verticesIndex*2 + 2],master[i + verticesIndex*2 + 3],master[i + verticesIndex*2 + 4]);
    // }
    //printf("%f \n",master[verticesIndex*2 + 28]);
    //printf("%x a %x b %x c %x \n",color[1][0],color[1][1],color[1][2],color[1][3]);
    //printf("ab %f %f\n",vertices[verticesIndex-1][0],vertices[verticesIndex-1][1]);
    //printf("\nfd %d %d %d\n",verticesIndex,orderIndex,colorIndex);

}


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
    import();

    // for(int i = 0; i <orderIndex; i++){
    //     //int tmp = 0x00000000000FF&( order[i] );
    //     printf("%d %3u ",i,order[i]);
    // }
    // printf("")
    // for(int i = 0; i <6; i++){
    //     //int tmp = 0x00000000000FF&( order[i] );
    //     printf("%d %3u ",i,order2[i]);
    // }


    GLuint temp_array[2];
    glGenBuffers(2, temp_array);
    vBufferObjID = temp_array[0];
    vBufferObjID2 = temp_array[1];
    

    //printf("a %d %d %d %d\n",(verticesIndex)*sizeof(float)*2,orderIndex*sizeof(GLuint),sizeof(GLuint),verticesIndex);
    glBindBuffer(GL_ARRAY_BUFFER,vBufferObjID);
    glBufferData(GL_ARRAY_BUFFER,(verticesIndex*2 + colorIndex*4 + 1)*sizeof(float),master,GL_STREAM_DRAW);
    //glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vBufferObjID2);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,orderIndex*sizeof(GLuint),order,GL_STREAM_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(order),order,GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);


    glGenVertexArrays(1,&vaoId);

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER,vBufferObjID);

    
    //printf("%d\n",sizeof(verts));
    
    //printf("%p\n",(void*)(verticesIndex*2 + 1));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)((verticesIndex*2 + 1)*sizeof(float)));
    //glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)(sizeof(float)*4*2));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vBufferObjID2);
    //printf("%d\n",sizeof(order));

    
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glClearColor(0.0,0.0,0.0,0.0);


    // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0); //clears buffer
}
void transform(GLfloat oPos1,GLfloat oPos2, GLfloat s, GLfloat rotate){
    glUniform2f(oPos,oPos1,oPos2);
    glUniform1f(scale,s);
    glUniform1f(rot,rotate*(M_PI)/180.0);
    glUniform2f(window,(float)glutGet(GLUT_WINDOW_WIDTH),(float)glutGet(GLUT_WINDOW_HEIGHT));
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //printf("%d %d %f %f\n",glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),(float)glutGet(GLUT_WINDOW_WIDTH)/600.0,
    //(float)glutGet(GLUT_WINDOW_HEIGHT)/600.0);


    glUseProgram(programID);



    glBindVertexArray(vaoId);
    
    // glBindBuffer(GL_ARRAY_BUFFER,vBufferObjID);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vBufferObjID2);
    // //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vBufferObjID2);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
    int time = glutGet(GLUT_ELAPSED_TIME);
    transform(sin(time*0.001)*0.7,0,1,(time%5000)/5000.0*360);
    //printf("test3 %d\n",sizeof( order ) / (sizeof( order[0] ) * (sizeof( order ) != sizeof(void*) || sizeof( order[0] ) <= sizeof(void*))));
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //printf("\n %d \n",orderIndex);
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,nullptr);

    glDrawElements(GL_TRIANGLES,orderIndex,GL_UNSIGNED_SHORT,nullptr);
    glBindVertexArray(0);



    // transform((glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,-0.2,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    // //transform(0.5,0,1,0);
    // //printf("%f  %f\n",(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    // glDrawArrays(GL_TRIANGLES, 0, 3);
    


    // //glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
    // transform((glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,-0.2,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    // //printf("%f  %f\n",(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // glDisableVertexAttribArray(0);

    
    // transform((-glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1+0.5,0.2,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1.25,(-glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    // //printf("%f  %f\n",(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*1-0.5,(glutGet(GLUT_ELAPSED_TIME)%5000)/5000.0*360);
    // glBindBuffer(GL_ARRAY_BUFFER, vBufferObjID2);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    // glDrawArrays(GL_TRIANGLES, 0, 3);




    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glUseProgram(0);
    glutSwapBuffers();
    //printf("draw\n");
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