#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include<math.h>

void forward(struct vec *vel, struct vec dir, GLfloat delta)
{
     GLfloat v_r,d,fi;
     d=sqrt(dir.x*dir.x+dir.y*dir.y);
     fi=atan2(dir.z,d);
     //printf("fi: %f\n",fi);
     if(fi>0.18) return;
     v_r=sqrt(vel->x*vel->x+vel->y*vel->y+vel->z*vel->z);
     v_r+=delta;
     vel->x=v_r*dir.x/d;
     vel->y=v_r*dir.y/d;
}

void turn(struct vec *vel, struct vec *dir, GLfloat delta)
{
     if(vel->x==0&&vel->y==0) return;
     GLfloat v_r,d_r;
     v_r=sqrt(vel->x*vel->x+vel->y*vel->y+vel->z*vel->z);
     d_r=sqrt(dir->x*dir->x+dir->y*dir->y+dir->z*dir->z);
     
     GLfloat fi=atan2(vel->y,vel->x);
     fi+=delta;
     vel->x=v_r*cos(fi);
     vel->y=v_r*sin(fi);
     dir->x=d_r*cos(fi);
     dir->y=d_r*sin(fi);
}

void backward(struct vec *vel, struct vec dir, GLfloat delta)
{
     GLfloat v_r;
     v_r=sqrt(vel->x*vel->x+vel->y*vel->y+vel->z*vel->z);
     v_r-=delta;
     
     GLfloat fi;
     /*
     if(vel->x==0&&vel->y==0) 
     {
                              fi=atan2(dir.y,dir.x);
                              vel->x+=-delta*cos(fi);
                              vel->y+=-delta*sin(fi);
                              
                              return;
     }*/
     fi=atan2(vel->y,vel->x);
     vel->x=v_r*cos(fi);
     vel->y=v_r*sin(fi);
}
/*
GLfloat change_height(GLfloat dr, struct vec poly, struct vec *pos)
{
        GLfloat r;
        r=sqrt((pos->x-poly.x)*(pos->x-poly.x)+(pos->y-poly.y)*(pos->y-poly.y));
        if(r<dr)
        {
                /*
                //printf("sprawdzenie wysokosci %f, %f \n",pos->z,poly.z);
                 if(pos->z>poly.z)  return (poly.z-pos->z);
                 else return 0;
                 
        }
        else return 0;
}
*/

GLfloat height_control(struct terrain *teren, struct vec terr_pos,struct vec *car_pos,struct vec *car_dir, GLfloat skala)
{
        GLint i, j, index, max=(teren->SX-1)*(teren->SY-1)*18, check=0,i1,j1,i2,j2,index1,index2;
        GLfloat a=skala/4.0,norma=sqrt(car_dir->x*car_dir->x+car_dir->y*car_dir->y);
        struct vec pos1,pos2;
        pos1.x=car_pos->x+a*car_dir->x/norma;
        pos2.x=car_pos->x-a*car_dir->x/norma;
        pos1.y=car_pos->y+a*car_dir->y/norma;
        pos2.y=car_pos->y-a*car_dir->y/norma;
        
        i=-(car_pos->x-terr_pos.x)/skala;
        j=-(car_pos->y-terr_pos.y)/skala;
        
        i1=-(pos1.x-terr_pos.x)/skala;
        j1=-(pos1.y-terr_pos.y)/skala;
        i2=-(pos2.x-terr_pos.x)/skala;
        j2=-(pos2.y-terr_pos.y)/skala;
        
        index1=((teren->SX-1)*i1+j1)*18;
        index2=((teren->SX-1)*i2+j2)*18;
        
        //1->0,0; 2->0,s; 3->s,s; 4->s,s; 5->0,s; 6->0,0
        GLfloat licznik=0,mianownik=0;
        pos1.x+=skala*i1-terr_pos.x;
        pos1.y+=skala*j1-terr_pos.y;
        pos2.x+=skala*i2-terr_pos.x;
        pos2.y+=skala*j2-terr_pos.y;
        if((-(pos1.y-terr_pos.y)/skala-j1)<(-(pos1.x-terr_pos.x)/skala-i1))
        {
                                                                           check=1;
                                                                           licznik+=((pos1.y+skala)*(pos1.x+skala)-(pos1.x+skala)*pos1.y)*teren->map[index1+2];
                                                                           licznik+=(-pos1.x*(pos1.y+skala)+(pos1.x+skala)*pos1.y)*teren->map[index1+5];
                                                                           licznik+=(pos1.x*pos1.y-(pos1.x+skala)*pos1.y)*teren->map[index1+8];
                                                                           mianownik=-pos1.x*(pos1.y+skala)-pos1.y*(pos1.x+skala)+(pos1.x+skala)*(pos1.y+skala)+pos1.x*pos1.y;
                                                                           pos1.z=licznik/mianownik;
        }
        else
        {
            check=2;
            licznik+=(-pos1.x*(pos1.y+skala)+pos1.x*pos1.y)*teren->map[index1+11];
            licznik+=(pos1.x*(pos1.y+skala)-pos1.y*(pos1.x+skala))*teren->map[index1+14];
            licznik+=((pos1.x+skala)*(pos1.y+skala)-pos1.x*(pos1.y+skala))*teren->map[index1+17];
            mianownik=-pos1.x*(pos1.y+skala)-pos1.y*(pos1.x+skala)+(pos1.x+skala)*(pos1.y+skala)+pos1.x*pos1.y;
            pos1.z=licznik/mianownik;
        
        }
        //printf("check: %i, licznik: %f, mianownik: %f\n",check,licznik, mianownik);
        licznik=0;
        mianownik=0;
        if((-(pos2.y-terr_pos.y)/skala-j2)<(-(pos2.x-terr_pos.x)/skala-i2))
        {
                                                                           licznik+=((pos2.x+skala)*(pos2.y+skala)-(pos2.x+skala)*pos2.y)*teren->map[index2+2];
                                                                           licznik+=(pos2.y*(pos2.x+skala)-pos2.x*(pos2.y+skala))*teren->map[index2+5];
                                                                           licznik+=(pos2.x*pos2.y-(pos2.x+skala)*pos2.y)*teren->map[index2+8];
                                                                           mianownik=-pos2.x*(pos2.y+skala)-pos2.y*(pos2.x+skala)+(pos2.x+skala)*(pos2.y+skala)+pos2.x*pos2.y;
                                                                           pos2.z=licznik/mianownik;
        }
        else
        {
            licznik+=(-pos2.x*(pos2.y+skala)+pos2.x*pos2.y)*teren->map[index2+11];
            licznik+=(pos2.x*(pos2.y+skala)-(pos2.x+skala)*pos2.y)*teren->map[index2+14];
            licznik+=(-pos2.x*(pos2.y+skala)+(pos2.x+skala)*(pos2.y+skala))*teren->map[index2+17];
            mianownik=-pos2.x*(pos2.y-skala)-pos2.y*(pos2.x-skala)+(pos2.x-skala)*(pos2.y-skala)+pos2.x*pos2.y;
            pos2.z=licznik/mianownik;
        }
        /*
        printf("polozenia %f,%f; dir+: %f %f; dir-: %f, %f\n",car_pos->x,car_pos->y,pos1.x,pos1.y,pos2.x,pos2.y);
        int l;
        for(l=0;l<18;++l)
        {
                         if (l%3==0) printf("%i: ",l/3+1);
                         printf("%f ",teren->map[index1+l]);
        }
        printf("\n");
        */
        car_dir->z=pos1.z-pos2.z;
        norma=sqrt(car_dir->x*car_dir->x+car_dir->y*car_dir->y+car_dir->z*car_dir->z);
        car_dir->x/=norma;
        car_dir->y/=norma;
        car_dir->z/=norma;
        return pos1.z/2.0+pos2.z/2.0-terr_pos.z;
        
        /*
        if ((-(car_pos->x-terr_pos.x)/skala-i)>=0.5) ++i;
        if ((-(car_pos->y-terr_pos.y)/skala-j)>=0.5) ++j;
        //printf("polozenia ij: %i,%i\n",i,j);
        
        index=((teren->SX-1)*i+j)*18;
        if(index>=max||index<0) return 0;
        GLfloat x=0,y=0,z1=0,z2=0,z3=0;
        
        x=teren->map[index];
        y=teren->map[index+1];
        if(index+2<max) z1=teren->map[index+2];
        if(index+5<max) z2=teren->map[index+5];
        if(index+8<max) z3=teren->map[index+8];
        return (teren->map[index+2]-terr_pos.z);
        */
}

void collision(struct vec *dir, struct vec *vel,struct vec *car_pos,struct vec *obj_pos,GLfloat *dmg,GLfloat Vmax)
{
     struct vec r,r2;
     r.x=car_pos->x-obj_pos->x;
     r.y=car_pos->y-obj_pos->y;
     r2.x=car_pos->x+0.01*dir->x-obj_pos->x;
     r2.y=car_pos->y+0.01*dir->y-obj_pos->y;
     GLfloat delta;
     delta=r2.x*r2.x+r2.y*r2.y-r.x*r.x-r.y*r.y;
     if(delta>0) return;
     GLfloat cosine,tmp_x,tmp_y;
     cosine=-(r.x*dir->x+r.y*dir->y)/sqrt((r.x*r.x+r.y*r.y)*(dir->x*dir->x+dir->y*dir->y));
     GLfloat fi=acos(cosine+1E-10);
     tmp_x=cos(3.14-2*fi)*dir->x-sin(3.14-2*fi)*dir->y;
     tmp_y=cos(3.14-2*fi)*dir->y+sin(3.14-2*fi)*dir->x;
     dir->x=tmp_x;
     dir->y=tmp_y;
     tmp_x=0.5*(cos(3.14-2*fi)*vel->x-sin(3.14-2*fi)*vel->y);
     tmp_y=0.5*(cos(3.14-2*fi)*vel->y+sin(3.14-2*fi)*vel->x);
     vel->x=tmp_x;
     vel->y=tmp_y;
     *dmg-=50*sqrt(tmp_x*tmp_x+tmp_y*tmp_y)/Vmax;
     if(*dmg<0) *dmg=0;
}


void collision_detection(struct vec *obj_pos,GLint N, struct vec *pos,struct vec *dir,struct vec *vel,GLfloat *dmg,GLfloat Vmax)
{
     GLfloat r;
     GLint i;
     for(i=0;i<N;++i)
     {
              r=sqrt((obj_pos[i].x-pos->x)*(obj_pos[i].x-pos->x)+(obj_pos[i].y-pos->y)*(obj_pos[i].y-pos->y));
              if(r<0.4) collision(dir,vel,pos,obj_pos+i,dmg,Vmax);
     }
}

void boost_detection(struct vec *obj_pos, GLint *rys, GLint N, struct vec car_pos, struct vec *vel, struct vec *dir, GLint *boost,GLfloat Vmax)
{
     if(*boost>0)
     {
                (*boost)-=4;
                vel->x=(Vmax/2.0+*boost/200.0*Vmax)*dir->x;
                vel->y=(Vmax/2.0+*boost/200.0*Vmax)*dir->y;
     }
     GLfloat r;
     GLint i;
     for(i=0;i<N;++i)
     {
                     if(rys[i]==0) continue;
                     r=sqrt((obj_pos[i].x-car_pos.x)*(obj_pos[i].x-car_pos.x)+(obj_pos[i].y-car_pos.y)*(obj_pos[i].y-car_pos.y));
                     if(r<0.4&&rys[i]==1)
                     {
                              rys[i]=0;
                              *boost+=100;
                              vel->x=Vmax*dir->x;
                              vel->y=Vmax*dir->y;
                     }
     }
}

void gate_detection(struct vec *obj_pos, GLint *rys,GLint N, struct vec car_pos)
{
     GLint i;
     GLfloat r;
     for(i=0;i<N;++i)
     {
                     if(rys[i]==0||rys[i]==1) continue;
                     r=sqrt((obj_pos[i].x-car_pos.x)*(obj_pos[i].x-car_pos.x)+(obj_pos[i].y-car_pos.y)*(obj_pos[i].y-car_pos.y));
                     if(r<0.5&&i==0)
                     {
                                    rys[0]=0;
                                    rys[1]=2;
                     }
                     if(r<0.5&&rys[i]==2)
                     {
                              rys[i]=0;
                              if(i<N) rys[i+1]=2;
                     }
     }
}
                              
void keep_boundaries(struct terrain *teren, struct vec terr_pos, struct vec car_pos, struct vec *vel, struct vec *dir)
{
     if((-teren->SX*0.8>car_pos.x-terr_pos.x-3)||(car_pos.x-terr_pos.x>-2)||(-teren->SY*0.8>car_pos.y-terr_pos.y-3)||(car_pos.y-terr_pos.y>-2))
     {
                                                                           vel->x*=-1;
                                                                           vel->y*=-1;
                                                                           dir->x*=-1;
                                                                           dir->y*=-1;
     }
}

void velocity_control(struct vec *dir,struct vec *vel)
{
        GLfloat fi=0,d=sqrt(dir->x*dir->x+dir->y*dir->y),s=1;
        fi=atan2(dir->z,d);
        if(fi<0.1) return;
        if(fi<=0) s=0.3;
        s=(1-s*2*fi/3.14)*(1-s*2*fi/3.14);
        vel->x*=s;
        vel->y*=s;
        //printf("S: %f\n",s);
}

struct vec normal_to_terrain(struct terrain *teren, struct vec terr_pos,struct vec pos, GLfloat skala)
{
     GLint i, j, index, max=(teren->SX-1)*(teren->SY-1)*18, check=1;
     i=-(pos.x-terr_pos.x)/skala;
     j=-(pos.y-terr_pos.y)/skala;
     index=((teren->SX-1)*i+j)*18;
     
     struct vec n;     
     if(index>=max||index<0)
     {
                  n.x=0;
                  n.y=0;
                  n.z=1;
                  return n;
     }          
     
     GLfloat v1z,v3z,c;
     
     double p;
     if(modf(pos.x/skala,&p)>modf(pos.y/skala,&p)) check=2;
     else check=1;

     //obliczenie wspolrzednych wektora normalnego
     if(check==1)
     {
                 v1z=teren->map[index+2]-teren->map[index+5];
                 v3z=teren->map[index+8]-teren->map[index+5];
                 n.x=skala*v1z;
                 n.y=-skala*v3z;
                 n.z=skala*skala;
     }
     else
     {
         v1z=teren->map[index+17]-teren->map[index+14];
         v3z=teren->map[index+11]-teren->map[index+14];
         n.x=-skala*v3z;
         n.y=skala*v1z;
         n.z=skala*skala;
     }
     //normalizacja
     c=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
     n.x/=c;
     n.y/=c;
     n.z/=c;
     //printf("normalny: %f %f %f\n",n.x,n.y,n.z);
     return n;
}

void dir_control(struct vec *dir, struct vec n)
{
     GLfloat c;
     dir->z=-(dir->x*n.x+dir->y*n.y)/n.z;
     c=sqrt(dir->x*dir->x+dir->y*dir->y+dir->z*dir->z);
     dir->x/=c;
     dir->y/=c;
     dir->z/=c;
}

struct vec third_ortho(struct vec d, struct vec n)
{
       struct vec tmp;
       tmp.x=n.y*d.z-d.y*n.z;
       tmp.y=n.z*d.x-n.x*d.z;
       tmp.z=n.x*d.y-n.y*d.x;
       return tmp;
}

void check_finish(GLint *game_state, GLint dmg, GLint last_gate, struct vec *vel)
{
     if(last_gate==0||dmg==0)
     {
                     *game_state=2;
                     vel->x=0;
                     vel->y=0;
     }
}

void restart(GLint *game_state,GLint *rys_bramki,GLint Nbramki,GLint *rys_beczki,GLint Nbeczki,struct vec pos0, struct vec *car_pos, struct vec dir0, struct vec *car_dir,GLint *boost,GLfloat *dmg)
{
     GLint i;
     for(i=0;i<Nbramki;++i)
     {
                           rys_bramki[i]=1;
     }
     rys_bramki[0]=2;
     
     for(i=0;i<Nbeczki;++i)
     {
                           rys_beczki[i]=1;
     }
     *game_state=0;
     *car_pos=pos0;
     *car_dir=dir0;
     *boost=0;
     *dmg=100;
}
