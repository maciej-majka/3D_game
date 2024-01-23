#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "move.h"
#include "model_fun.h"
#include<math.h>
#include"glm/glm.h"

void compare(GLfloat a1,GLfloat a2,GLfloat a3,GLint *cmp)
{
     if(a1>a2&&a2>a3) {cmp[0]=3; cmp[1]=2; cmp[2]=1;}
     if(a1>a2&&a3>a2) {cmp[0]=3; cmp[1]=1; cmp[2]=2;}
     if(a2>a1&&a1>a3) {cmp[0]=2; cmp[1]=3; cmp[2]=1;}
     if(a2>a3&&a3>a1) {cmp[0]=1; cmp[1]=3; cmp[2]=2;}
     if(a3>a2&&a2>a1) {cmp[0]=1; cmp[1]=2; cmp[2]=3;}
     if(a3>a1&&a1>a2) {cmp[0]=2; cmp[1]=1; cmp[2]=3;}
}

void draw_terrain(struct terrain *teren,struct terrain *normals, struct vec pos, GLint *tex,struct vec *car_pos)
{
     glEnable(GL_COLOR_MATERIAL);
     glBindTexture(GL_TEXTURE_2D,tex[1]);
     GLint i,max,check=0,cmp[3],uv_choice;
     max=(teren->SX-1)*(teren->SY-1)*18;
    
     //printf("fcja terenu, max=%i\n",max);
     //getchar(); 
     
     glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
     glColor3f(0.5,0.5,0.5);
     
     //GLfloat uv[2];
     struct vec poly;
     for(i=0;i<max;++i)
     {
                       //if(i<36) printf("%f,%f,%f\n",teren->map[i],teren->map[i+1],teren->map[i+2]);
                 if(i%18==0)
                 {
                           //if(i%18==i%9)
                           {
                                        if(teren->map[i+2]<=1.4) {glBindTexture(GL_TEXTURE_2D,tex[2]); check=0;}
                                        if((teren->map[i+2]>1.4)&&(teren->map[i+2]<1.5)) {glBindTexture(GL_TEXTURE_2D,tex[0]); check=1;}
                                        if(teren->map[i+2]>3) {glBindTexture(GL_TEXTURE_2D,tex[1]); check=0;}
                                        if(teren->map[i+2]<=2.7&&teren->map[i+2]>=1.5) {glBindTexture(GL_TEXTURE_2D,tex[3]); check=0;}
                           }
                           /*
                           else
                           {
                                        if(teren->map[i+8]<=1.7) {glBindTexture(GL_TEXTURE_2D,tex[2]); check=0;}
                                        if((teren->map[i+8]>1.7)&&(teren->map[i+8]<2)) {glBindTexture(GL_TEXTURE_2D,tex[0]); check=1;}
                                        if(teren->map[i+8]>3) {glBindTexture(GL_TEXTURE_2D,tex[1]); check=0;}
                                        if(teren->map[i+8]<=3&&teren->map[i+2]>=2) {glBindTexture(GL_TEXTURE_2D,tex[3]); check=0;}
                           }
                           */
                 }
                 
                 if(i%9==0) glBegin(GL_TRIANGLES);
                 
                 if(check==0)
                 {
                             if(i%9==0) glTexCoord2f(1,1);
                             if(i%9==3) glTexCoord2f(0,1);
                             if(i%9==6) glTexCoord2f(0,0);
                 }
                 
                 if(check==1)
                 {
                             if(i%9==0) compare(teren->map[i+2],teren->map[i+5],teren->map[i+8],cmp);
                             //printf("i:%i cmp: %i %i %i\n",i%9,cmp[0],cmp[1],cmp[2]);
                             if(i%9==0) uv_choice=cmp[0];// printf("i mod 2\n");}
                             if(i%9==3) uv_choice=cmp[1];
                             if(i%9==6) uv_choice=cmp[2];
                             
                             //printf("uv: %i\n", uv_choice);
                             
                             switch(uv_choice)
                             {
                                              case 3:
                                                   {glTexCoord2f(1,0); break;}//printf("0,0\n");}
                                              case 2:
                                                   {glTexCoord2f(1,1);break;}//printf("0,1\n");}
                                              case 1:
                                                   {glTexCoord2f(0,0);break;}//printf("1,1\n");}
                             }
                             
                 }
                 if(i%3==0)
                 {
                           poly.x=teren->map[i]-pos.x;
                           poly.y=teren->map[i+1]-pos.y;
                           poly.z=teren->map[i+2]-pos.z;
                 
                           glNormal3f(normals->map[i],normals->map[i+1],normals->map[i+2]);
                           glVertex3f(poly.x,poly.y,poly.z);
                 }
                 
                 if(i%9==8) glEnd();
     }
     glColor3f(0,1,0);
     glDisable(GL_COLOR_MATERIAL);
     
     //rysowanie normalnych
     /*
     struct vec tmp,n,zero={0,0,0};
     for(i=0;i<max;i+=3)
     {
                      tmp.x=-(teren->map[i]-pos.x);
                      tmp.y=-(teren->map[i+1]-pos.y);
                      tmp.z=-(teren->map[i+2]-pos.z);
                      n=normal_to_terrain(teren,pos,tmp,0.8);
                      //printf("%f %f %f, normalny: %f %f %f\n",tmp.x,tmp.y,tmp.z,n.x,n.y,n.z);
                      glLineWidth(3);
                      glColor3f(1,0,0);
                      glBegin(GL_LINES);
                      glVertex3f(-tmp.x,-tmp.y,-tmp.z);
                      glVertex3f(n.x-tmp.x,n.y-tmp.y,n.z-tmp.z);
                      glEnd();
     }
     //glDisable(GL_COLOR_MATERIAL);
     */   
}

void set_norm_terr(struct terrain *teren, struct terrain *normals,struct vec terr_pos)
{
     GLint max,i;
     max=(teren->SX-1)*(teren->SY-1)*18;
     normals->map=(GLfloat*)malloc(max*sizeof(GLfloat));
     struct vec tmp,n;
     
     for(i=0;i<max;i+=3)
     {
                      tmp.x=-(teren->map[i]-terr_pos.x);
                      tmp.y=-(teren->map[i+1]-terr_pos.y);
                      tmp.z=-(teren->map[i+2]-terr_pos.z);
                      n=normal_to_terrain(teren,terr_pos,tmp,0.8);
                      normals->map[i]=n.x;
                      normals->map[i+1]=n.y;
                      normals->map[i+2]=n.z;
     }
}
GLfloat *gen_grass(GLfloat R,GLfloat H,GLint N,GLfloat *tab)
{
     GLfloat x,y,z,r,fi;
     GLint i;
     if(tab==NULL)
     {
                  printf("trawa\n");
                  tab=(GLfloat*)malloc(6*N*sizeof(GLfloat));
                  for(i=0;i<6*N;i+=6)
                  {
                                   r=R*(rand()%1000)/1000.0;
                                   fi=6.28*(rand()%360)/360.0;
                                   tab[i]=r*cos(fi);
                                   tab[i+1]=r*sin(fi);
                                   tab[i+2]=0;
                                   r=0.1*(rand()%10)/10.0;
                                   fi=6.28*(rand()%360)/360.0;
                                   tab[i+3]=tab[i]+r*cos(fi);
                                   tab[i+4]=tab[i+1]+r*sin(fi);
                                   tab[i+5]=0.5*H*(1+(rand()%100)/100.0);
                  }
     }
     /*
     GLint j;
     for(i=0;i<6*N;i+=6)
     {for(j=0;j<6;++j)
     printf("%f, ",tab[i+j]);
     printf("\n");
     }
     */
     return tab;
}

void draw_grass(struct vec pos, struct vec dir,GLint N,GLfloat *tab,GLfloat fi, GLfloat eta)
{
     if(tab==NULL) {printf("nie ma trawy\n");return;}
     GLint i;
     
     glPushMatrix();
     glTranslatef(-pos.x,-pos.y,-pos.z);
     glRotatef(fi,0,0,1);
     glRotatef(eta,dir.x,dir.y,0);
          
     glEnable(GL_COLOR_MATERIAL);
     
     glLineWidth(3);
     for(i=0;i<6*N;i+=6)
     {
                      glBegin(GL_LINES); 
                      glColor3f(0.1,0.1,0);
                      glVertex3f(tab[i],tab[i+1],tab[i+2]);
                      glColor3f(0.3,0.5,0);
                      glVertex3f(tab[i+3],tab[i+4],tab[i+5]);
                      glEnd();
     }
     glDisable(GL_COLOR_MATERIAL);
     glPopMatrix();
}

void gen_grass2(struct vec *pos, struct vec *dir,GLint *Fi,GLint *eta, GLint N, struct terrain *teren, struct vec terr_pos)
{
     GLint i;
     GLfloat fi;
     struct vec n;
     for(i=0;i<N;++i)
     {
                     fi=rand()%360/360.0*6.28;
                     pos[i].x=-25+(rand()%20)*cos(fi);
                     pos[i].y=-25+(rand()%20)*sin(fi);
                     pos[i].z=-height_control(teren, terr_pos,pos+i,dir+i,0.8)+0.06;
                     dir[i].x=1;
                     dir[i].y=0;
                     dir[i].z=0;
                     n=normal_to_terrain(teren,terr_pos,pos[i],0.8);
                     Fi[i]=90+360*atan2(n.y,n.x)/6.28;
                     eta[i]=360*atan2(sqrt(n.x*n.x+n.y*n.y),n.z)/6.28;
     }
}     

void trees_generator(struct vec *grupa, struct vec *kierunki,GLint N,struct vec pos, GLfloat R,struct terrain *teren,struct vec terr_pos)
{
     GLint i;
     GLfloat r, fi;
     for(i=0;i<N;++i)
     {
              fi=6.28*(rand()%360)/360.0;
              kierunki[i].x=sin(fi);
              kierunki[i].y=cos(fi);
              kierunki[i].z=0;
     }
     for(i=0;i<N;++i)
     {
              fi=6.28*(rand()%360)/360.0;
              r=R*(rand()%30)/30.0;
              grupa[i].x=pos.x+r*cos(fi);
              grupa[i].y=pos.y+r*sin(fi);
              grupa[i].z=height_control(teren, terr_pos,grupa+i,kierunki+i,0.8);
     }
}

void draw_trees(struct vec *grupa, struct vec *kierunki, GLint N, struct vec pos,GLMmodel *model)
{
     GLint i;
     struct vec normalny={0,0,1}, orto={0,1,0};
     
     for(i=0;i<N;++i)
     {
                     draw_model(model,grupa[i],kierunki[i],normalny,orto,0,0.4);
     }
}

void gen_barrels(struct vec *obj_pos, struct vec *obj_dir, GLint *rys, GLint N, struct terrain *teren, struct vec terr_pos)
{
     GLint i;
     GLfloat fi;
     for(i=0;i<N;++i)
     {
                     rys[i]=1;
                     switch (i)
                     {
                            case 0:
                                 {
                                           obj_pos[i].x=-3.5;
                                           obj_pos[i].y=-15;
                                           break;
                                 }
                            case 1:
                                 {
                                           obj_pos[i].x=-3;
                                           obj_pos[i].y=-36;
                                           break;
                                 }
                            case 2:
                                 {
                                           obj_pos[i].x=-23;
                                           obj_pos[i].y=-44;
                                           break;
                                 }
                            case 3:
                                 {
                                           obj_pos[i].x=-39;
                                           obj_pos[i].y=-35;
                                           break;
                                 }
                            case  4:
                                 {
                                           obj_pos[i].x=-38;
                                           obj_pos[i].y=-10;
                                           break;
                                 }
                            case 5:
                                 {
                                           obj_pos[i].x=-23;
                                           obj_pos[i].y=-15;
                                           break;
                                 }
                     }
                     
                     fi=rand()%360/360.0*6.28;
                     obj_dir[i].x=cos(fi);
                     obj_dir[i].y=sin(fi);
                     obj_pos[i].z=height_control(teren, terr_pos,obj_pos+i,obj_dir+i,0.8);
     }
}

void draw_barrels(struct vec *obj_pos, struct vec *obj_dir, GLint *rys,GLint N, GLMmodel *model)
{
     struct vec normalny={0,0,1}, orto={0,1,0};
     GLint i;
     for(i=0;i<N;++i)
     {
                     if(rys[i]==0) continue;
                     draw_model(model,obj_pos[i],obj_dir[i],normalny,orto,0,0.05);
     }
}

void gen_gates(struct vec *obj_pos, struct vec *obj_dir, GLint *rys, GLint N, struct terrain *teren, struct vec terr_pos)
{
     GLint i;
     GLfloat fi;
     for(i=0;i<N;++i)
     {
                     if(i==0) rys[i]=2;
                     else rys[i]=1;
                     switch (i)
                     {
                            case 0:
                                 {
                                           obj_pos[i].x=-4;
                                           obj_pos[i].y=-3.5;
                                           break;
                                 }
                            case 1:
                                 {
                                           obj_pos[i].x=-5;
                                           obj_pos[i].y=-39;
                                           break;
                                 }
                            case 2:
                                 {
                                           obj_pos[i].x=-30;
                                           obj_pos[i].y=-44;
                                           break;
                                 }
                            case 3:
                                 {
                                           obj_pos[i].x=-42.5;
                                           obj_pos[i].y=-20;
                                           break;
                                 }
                            case  4:
                                 {
                                           obj_pos[i].x=-28;
                                           obj_pos[i].y=-6;
                                           break;
                                 }
                            case 5:
                                 {
                                           obj_pos[i].x=-20;
                                           obj_pos[i].y=-25;
                                           break;
                                 }
                     }
                     switch (i)
                     {
                            case 0:
                                 {
                                           obj_dir[i].x=0.7;
                                           obj_dir[i].y=0.3;
                                           break;
                                 }
                            case 1:
                                 {
                                           obj_dir[i].x=0.4;
                                           obj_dir[i].y=-0.6;
                                           break;
                                 }
                            case 2:
                                 {
                                           obj_dir[i].x=-2;
                                           obj_dir[i].y=-3;
                                           break;
                                 }
                            case 3:
                                 {
                                           obj_dir[i].x=1;
                                           obj_dir[i].y=0;
                                           break;
                                 }
                            case  4:
                                 {
                                           obj_dir[i].x=-1;
                                           obj_dir[i].y=-1;
                                           break;
                                 }
                            case 5:
                                 {
                                           obj_dir[i].x=-40;
                                           obj_dir[i].y=-20;
                                           break;
                                 }
                     }
                     obj_pos[i].z=height_control(teren, terr_pos,obj_pos+i,obj_dir+i,0.8);
     }
}

void draw_gates(struct vec *obj_pos, struct vec *obj_dir, GLint N, GLMmodel *model)
{
     struct vec normalny={0,0,1}, orto={0,1,0};
     GLint i;
     for(i=0;i<N;++i)
     {
                     //if(rys[i]==0) continue;
                     draw_model(model,obj_pos[i],obj_dir[i],normalny,orto,0,0.4);
     }
}
