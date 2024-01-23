#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<gd.h>
#include"structs.h"

void load_texture(char string[100], struct texture *tekstura)
{
       gdImagePtr img;
       FILE *in;
       in=fopen(string,"rb");
       printf("otwarto plik tekstur %s\n",string);
       img=gdImageCreateFromPng(in);
       tekstura->SX=gdImageSX(img);
       tekstura->SY=gdImageSY(img);
       
       int i,j;
       tekstura->img=(GLubyte*)malloc(tekstura->SX*tekstura->SY*3*sizeof(GLubyte));
       
       int color,k=0;
       for(i=tekstura->SX-1;i>=0;--i)
       for(j=0;j<tekstura->SY;++j)
       {
                 color=gdImageGetPixel(img,j,i);
                 tekstura->img[k]=gdImageRed(img,color);
                 tekstura->img[++k]=gdImageGreen(img,color);
                 tekstura->img[++k]=gdImageBlue(img,color);
                 ++k;
       }
       fclose(in);
       gdImageDestroy(img);
}

void texture_free(struct texture *tekstura)
{
     free(tekstura->img);
}

void texture_test(struct texture *tekstura)
{
     FILE *out;
       gdImagePtr img;
       img=gdImageCreateTrueColor(tekstura->SX,tekstura->SY);
       out=fopen("test.png","wb");
       
       printf("test\n");
       int i,j,k=0, color;
       for(i=0;i<tekstura->SX;++i)
       for(j=0;j<tekstura->SY;++j)
       {
                                  color=gdImageColorAllocate(img,tekstura->img[k],tekstura->img[++k],tekstura->img[++k]);
                                  gdImageSetPixel(img,i,j,color);
                                  ++k;
       }
       gdImagePng(img,out);
       fclose(out);
}

void tekstura_auto()
{
     FILE *out;
     gdImagePtr img;
     GLint color,i,j;
     
     img=gdImageCreateTrueColor(128,64);
     color=gdImageColorAllocate(img, 100,255,100);
     gdImageFilledRectangle(img,0,12,16,52,color); //bokL
     gdImageFilledRectangle(img,112,12,128,52,color); //bokR
     color=gdImageColorAllocate(img, 150,150,150); 
     gdImageFilledRectangle(img,32,0,96,12,color); //przod
     gdImageFilledRectangle(img,32,52,96,64,color); //tyl
     color=gdImageColorAllocate(img, 255,0,0); 
     gdImageFilledRectangle(img,32,12,96,35,color); //maska
     gdImageFilledRectangle(img,32,41,96,47,color); //dach
     color=gdImageColorAllocate(img, 0,0,255);
     gdImageFilledRectangle(img,32,35,96,41,color); //szyba przod
     gdImageFilledRectangle(img,32,47,96,52,color); //szyba tyl
     gdImageFilledRectangle(img,16,41,32,47,color); //szyba L
     gdImageFilledRectangle(img,96,41,112,47,color); //szyba R
     
     out=fopen("textura_auto.png","wb");
     gdImagePng(img,out);
     fclose(out);
     gdImageDestroy(img);
}

GLfloat average(gdImagePtr img,int i, int j)
{
        int color;
        GLfloat R,G,B;
        color=gdImageGetPixel(img,i,j);
        R=gdImageRed(img,color);
        G=gdImageGreen(img,color);
        B=gdImageBlue(img,color);
        
        return (R+G+B)/3;
}

GLfloat *terrain_generation(GLfloat scale, GLfloat scale_h,GLint *globSX,GLint *globSY)
{
        printf("skala: %f\n",scale_h);
     FILE *in;
     gdImagePtr img;
     in=fopen("terrain_map.png","rb");
     img=gdImageCreateFromPng(in);
     
     int SX,SY,i,j,curr=0,k,l;
     GLfloat *map;
     SX=gdImageSX(img);
     SY=gdImageSY(img);
     *globSX=SX;
     *globSY=SY;
     
     map=(GLfloat*)malloc((SX-1)*(SY-1)*2*3*3*sizeof(GLfloat));
     for(i=0;i<SX-1;++i)
     for(j=0;j<SY-1;++j)
     {
                       curr=18*(i*(SX-1)+j);
                       //printf("curr: %i\n",curr);
                       k=0; l=0;
                       map[curr++]=scale*(i+k);
                       map[curr++]=scale*(j+l);
                       map[curr++]=scale_h*average(img,i+k,j+l);
                       //printf("curr: %i\n",curr);
                       k=1; l=0;
                       map[curr++]=scale*(i+k);
                       map[curr++]=scale*(j+l);
                       map[curr++]=scale_h*average(img,i+k,j+l);
                       //printf("curr: %i\n",curr);
                       k=1; l=1;
                       map[curr++]=scale*(i+k);
                       map[curr++]=scale*(j+l);
                       map[curr++]=scale_h*average(img,i+k,j+l);
                       //printf("curr: %i\n",curr);
                       k=1; l=1;
                       map[curr++]=scale*(i+k);
                       map[curr++]=scale*(j+l);
                       map[curr++]=scale_h*average(img,i+k,j+l);
                       //printf("curr: %i\n",curr);
                       k=0; l=1;
                       map[curr++]=scale*(i+k);
                       map[curr++]=scale*(j+l);
                       map[curr++]=scale_h*average(img,i+k,j+l);
                       //printf("curr: %i\n",curr);
                       k=0; l=0;
                       map[curr++]=scale*(i+k);
                       map[curr++]=scale*(j+l);
                       map[curr++]=scale_h*average(img,i+k,j+l);
                       //printf("curr: %i\n\n",curr);
                       //getchar();
     }
     gdImageDestroy(img);
     fclose(in);
     return map;
}
     
     
