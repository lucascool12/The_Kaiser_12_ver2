#include <cstdio>
#include <string>

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
    int8_t test[20][20][4];
    fread(&test,2,800,bmpfile);
    fclose(bmpfile);
    // FILE* output;
    // output = fopen("test.bmpvectors","w");
    // fwrite(&test,2,800,output);
    // fclose(output);
    float test[400][4];
    int curindex = 0;
    
}