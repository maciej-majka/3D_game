#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "glm/glm.h"

void draw_model(GLMmodel *model,struct vec pos, struct vec dir, struct vec n, struct vec o, GLfloat offset1,GLfloat delta_z)
{
     //glLoadIdentity();
     GLfloat fi,theta,eta,dn,dd;
     fi=atan2(dir.y,dir.x);
     dn=sqrt(n.y*n.y+n.x*n.x);
     dd=sqrt(dir.x*dir.x+dir.y*dir.y);
     theta=atan2(n.z,dn);
     eta=atan2(dir.z,dd);
     /*
     glLineWidth(3);
     glColor3f(1,0,0);
     
     glBegin(GL_LINES);
     glVertex3f(-pos.x,-pos.y,pos.z);
     glVertex3f(-n.x-pos.x,-n.y-pos.y,n.z+pos.z);
     glEnd();
     
     glBegin(GL_LINES);
     glColor3f(1,0,0);
     glVertex3f(-dir.x-pos.x,-dir.y-pos.y,dir.z+pos.z+0.05);
     glColor3f(1,0,0);
     glVertex3f(-pos.x,-pos.y,pos.z+0.05);
     glEnd();
     
     glBegin(GL_LINES);
     glColor3f(1,0,0);
     glVertex3f(-o.x-pos.x,-o.y-pos.y,o.z+pos.z);
     glColor3f(1,0,0);
     glVertex3f(-pos.x,-pos.y,pos.z);
     glEnd();
     */
     glPushMatrix();
     glTranslatef(-pos.x,-pos.y,pos.z+delta_z);
     
     //glRotatef(90-theta*360/6.28,dir.x,dir.y,dir.z);
     glRotatef(eta*360/6.28,o.x,o.y,o.z);
     glRotatef(offset1+fi/6.28*360,0,0,1);
     
     //printf("%f %f %f\n",dir.x,dir.y, fi);
     //glDisable(GL_TEXTURE_2D);
     glEnable(GL_COLOR_MATERIAL);
     glColor3f(1,1,1);
     glmDraw(model,GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
     glDisable(GL_COLOR_MATERIAL);
     //glEnable(GL_TEXTURE_2D);
     
     glPopMatrix();
}

void draw_triangle(struct vec pos, struct vec dir, struct vec *pos_bramki,GLint *rys,GLint N)
{
     GLint i;
     for(i=0;i<N;++i)
     if(rys[i]==2) break;
     
     printf("bramka: %i %i\n",i,rys[i]);
     
     struct vec tmp;
     tmp.x=pos_bramki[i].x-pos.x;
     tmp.y=pos_bramki[i].y-pos.y;
     tmp.z=pos_bramki[i].z-pos.z;
     
     GLfloat fi=atan2(tmp.y,tmp.x);
     glPushMatrix();
     glTranslatef(-pos.x,-pos.y,pos.z+1);
     glRotatef(90+fi/6.28*360,0,0,1);
     glScalef(0.25,0.25,0.25);
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_LIGHTING);
     glBegin(GL_TRIANGLES);
     glColor3f(1,0,0);
     glVertex3f(0,2,-0.5);
     glColor3f(0,0,1);
     glVertex3f(0.5,0,0);
     glVertex3f(-0.5,0,0);
     glEnd();
     glEnable(GL_LIGHTING);
     glEnable(GL_TEXTURE_2D);
     glPopMatrix();
}
