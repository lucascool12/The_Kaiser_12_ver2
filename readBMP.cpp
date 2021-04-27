#include <cstdio>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <cmath>

using std::pow;
// struct verticesfile{
//     unsigned int verticesAmount;
//     float * vertices;
//     int8_t * colors;
// };


int main(){
    FILE* bmpfile;
    bmpfile = fopen("test.bmp","r");
    fseek(bmpfile,0xA,SEEK_SET);
    short addres_offset;
    short width;
    short height;
    fread(&addres_offset,sizeof(addres_offset),1,bmpfile);
    fseek(bmpfile,0x12,SEEK_SET);
    fread(&width,sizeof(addres_offset),1,bmpfile);
    fseek(bmpfile,0x16,SEEK_SET);
    fread(&height,sizeof(addres_offset),1,bmpfile);
    printf("%d %d %d\n",addres_offset,width,height);
    //fseek(bmpfile,addres_offset+267,SEEK_SET);
    fseek(bmpfile,addres_offset,SEEK_SET);
    int8_t test[width][height][4];
    fread(&test,2,800,bmpfile);
    fclose(bmpfile);
    FILE* output;
    output = fopen("test.bmpvectors","w");
    fwrite(&test,2,800,output);
    fclose(output);
    //20x20
    //      0   1   2   3   4   5   6   ...
    //  19  p   p   p   p   p   p   p
    //  18  p   p   p   p   p   p   p
    //  17
    //  16
    //  15
    //  14
    //  ..
    //  color pos
    //  0   1   2   3
    //  B   G   R   A
    for(int i = width-1; i >= 0 ; i--){
        printf("\n \n row %2d %2d \n \n",19-i,i);
        for(int j = 0; j < height; j++){
            for(int u = 0 ; u < 4 ; u++){
                int tmp = 0x00000000000FF&( test[i][j][u] );
                printf("%3d ",tmp);
            }
            printf("   %2d \n",j);
        } 
    }

    int temp = 0x0000000FF&( test[19-1][7][1] );
    printf("%d",temp);
    float vertices[width*height*4][2];
    int verticesIndex = 0;
    int8_t color[width*height*4][4];
    int colorIndex = 0;
    GLuint order[width*height*4];

    for(int i = width-1; i >= 0 ; i--){
        for(int j = 0; j < height; j++){
            int tmp = 0x00000000000FF&( test[i][j][3] );
            if(tmp != 0){
                float x = (19 - i) - width/2.0; //relative to center of img
                float y = height/2.0 - j;
                // vertices[verticesIndex][0] = x - 0.5;
                // vertices[verticesIndex][1] = y + 0.5;
                // verticesIndex++;
                // vertices[verticesIndex][0] = x + 0.5;
                // vertices[verticesIndex][1] = y + 0.5;
                // verticesIndex++;
                // vertices[verticesIndex][0] = x - 0.5;
                // vertices[verticesIndex][1] = y - 0.5;
                // verticesIndex++;
                // vertices[verticesIndex][0] = x + 0.5;
                // vertices[verticesIndex][1] = y - 0.5;
                // verticesIndex++;
                for(int v = 0; v < 6 ; v++){
                    order[verticesIndex + v] = v - (v > 2) ? -2 : 0;
                }
                for(int v = 0; v < 4; v++){
                    // int posx = (v == 0) ? -1 : 1;
                    int negy = (v < 2) ? 1 : -1;
                    vertices[verticesIndex][0] = x - 0.5*pow(-1 , v);
                    vertices[verticesIndex][1] = y + 0.5*negy;
                    for(int m = 0 ; m < 4 ; m++){
                        color[verticesIndex][m] = test[i][j][3-m];
                    }
                    verticesIndex++;
                }

            }
        } 
    }   
}