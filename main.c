#include <GL/glut.h>
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "move.h"
#include "model_fun.h"
#include "glm/glm.h"

GLint game_state;
time_t time0,time_end;

GLint swiatla=1;
GLfloat Vmax=1;

GLint boost=0;
GLfloat damage=100;

GLint tryb_kamery;

GLMmodel *car;
GLMmodel *bramka;
GLMmodel *drzewko;
GLMmodel *beczka;


GLfloat *trawa=NULL,*trawa2=NULL;

struct terrain teren;
struct terrain terr_n;

struct texture tex1;
struct texture tex_inter1;
struct texture tex_ground;
struct texture tex_sand;
struct texture tex_mud;
struct texture tex_con;
struct texture tex_roof;
struct texture tex_mapka;

GLint id_tekstury[10];

struct vec pos;
struct vec dir;
struct vec vel;
struct vec car_n;
struct vec car_o;
struct vec terr_pos;

struct vec bramka_pos={-15,-40,0}, bramka_dir={1,0,0}, normalny={0,0,1},orto={0,1,0};
struct vec drzewko_pos={-15,-39,0}, drzewko_dir={1,0,0};
struct vec trawa_pos={-14,-39,2};
struct vec trawa_pos2={-22,-20,1.95};
struct vec trawa_pos3={-4.3,-2.5,0.9};
struct vec trawa_pos4={-2.8,-6,0.45};
struct vec trawa_pos5={-3.2,-10,0.65};
struct vec *grass_pos, *grass_dir;
GLint *grass_fi,*grass_eta,*grass_dens;

struct vec beczka_pos={-10,-10,0};

struct vec *pos_drzew1;
struct vec *dir_drzew1;
struct vec gr_drzew1;

struct vec *pos_drzew2;
struct vec *dir_drzew2;
struct vec gr_drzew2;

struct vec *pos_drzew3;
struct vec *dir_drzew3;
struct vec gr_drzew3;

struct vec *pos_drzew4;
struct vec *dir_drzew4;
struct vec gr_drzew4;

struct vec *pos_drzew5;
struct vec *dir_drzew5;
struct vec gr_drzew5;



struct vec *pos_beczki;
struct vec *dir_beczki;
GLint *rys_beczki;

struct vec *pos_bramki;
struct vec *dir_bramki;
GLint *rys_bramki;

struct vec pos0={-5.5,-2,0};
struct vec dir0={1,-1,0};

void set_beginning()
{
     game_state=0;
     tryb_kamery=1;
     pos=pos0;
     dir=dir0;
     
     vel.x=0;
     vel.y=0;
     vel.z=0;
     
     terr_pos.x=2;
     terr_pos.y=2;
     terr_pos.z=2;
     
     teren.map=terrain_generation(0.8,5/((GLfloat)255),&teren.SX,&teren.SY);
     set_norm_terr(&teren,&terr_n,terr_pos);
     printf("wygenerowano model terenu: SX=%i, SY=%i;\n",teren.SX,teren.SY);
     
     car_n=normal_to_terrain(&teren,terr_pos,pos,0.8);
     dir_control(&dir,car_n);
     car_o=third_ortho(dir,car_n);
     
     GLint i;
     trawa=gen_grass(1,0.1,2000,trawa);
     trawa2=gen_grass(0.5,0.1,1000,trawa2);
     grass_pos=(struct vec*)malloc(200*sizeof(struct vec));
     grass_dir=(struct vec*)malloc(200*sizeof(struct vec));
     grass_fi=(GLint*)malloc(200*sizeof(GLint));
     grass_eta=(GLint*)malloc(200*sizeof(GLint));
     grass_dens=(GLint*)malloc(200*sizeof(GLint));
     for(i=0;i<200;++i)
     grass_dens[i]=250+rand()%750;
     
     gen_grass2(grass_pos,grass_dir,grass_fi,grass_eta,100,&teren,terr_pos);
     
     car=glmReadOBJ("modele\\car.obj");
     glmUnitize(car);
     glmScale(car,0.3);
     
     beczka=glmReadOBJ("modele\\beczka.obj");
     glmUnitize(beczka);
     glmScale(beczka,0.1);
     
     
     bramka=glmReadOBJ("modele\\bramka.OBJ");
     glmUnitize(bramka);
     glmScale(bramka,0.7);
     
     drzewko=glmReadOBJ("modele\\tree1.obj");
     glmUnitize(drzewko);
     glmScale(drzewko,0.8);
     
     printf("przygotowanie obiektow:\n");
     
     printf("-drzewa\n");
     gr_drzew1.x=-12;
     gr_drzew1.y=-39;
     pos_drzew1=(struct vec*)malloc(10*sizeof(struct vec));
     dir_drzew1=(struct vec*)malloc(10*sizeof(struct vec));
     trees_generator(pos_drzew1,dir_drzew1,10,gr_drzew1,5,&teren,terr_pos);
     
     gr_drzew2.x=-39;
     gr_drzew2.y=-39;
     pos_drzew2=(struct vec*)malloc(10*sizeof(struct vec));
     dir_drzew2=(struct vec*)malloc(10*sizeof(struct vec));
     trees_generator(pos_drzew2,dir_drzew2,10,gr_drzew2,6,&teren,terr_pos);
     
     gr_drzew3.x=-38;
     gr_drzew3.y=-5;
     pos_drzew3=(struct vec*)malloc(10*sizeof(struct vec));
     dir_drzew3=(struct vec*)malloc(10*sizeof(struct vec));
     trees_generator(pos_drzew3,dir_drzew3,10,gr_drzew3,6,&teren,terr_pos);
     
     gr_drzew4.x=-30;
     gr_drzew4.y=-4;
     pos_drzew4=(struct vec*)malloc(10*sizeof(struct vec));
     dir_drzew4=(struct vec*)malloc(10*sizeof(struct vec));
     trees_generator(pos_drzew4,dir_drzew4,10,gr_drzew4,6,&teren,terr_pos);
     /*
     gr_drzew5.x=-20;
     gr_drzew5.y=-20;
     pos_drzew5=(struct vec*)malloc(10*sizeof(struct vec));
     dir_drzew5=(struct vec*)malloc(10*sizeof(struct vec));
     trees_generator(pos_drzew5,dir_drzew5,10,gr_drzew5,6,&teren,terr_pos);
     */
     
     printf("-beczki\n");
     pos_beczki=(struct vec*)malloc(6*sizeof(struct vec));
     dir_beczki=(struct vec*)malloc(6*sizeof(struct vec));
     rys_beczki=(GLint*)malloc(6*sizeof(GLint));
     gen_barrels(pos_beczki,dir_beczki,rys_beczki,6,&teren,terr_pos);
     
     printf("-bramki\n");
     pos_bramki=(struct vec*)malloc(6*sizeof(struct vec));
     dir_bramki=(struct vec*)malloc(6*sizeof(struct vec));
     rys_bramki=(GLint*)malloc(6*sizeof(GLint));
     gen_gates(pos_bramki,dir_bramki,rys_bramki,6,&teren,terr_pos);
}

GLfloat zoom=-10;
GLfloat rotacjaOX=0;
GLfloat rotacjaOZ = 0.0;
GLfloat rotacjaOY = 0.0;

GLfloat srodekX = 0.0, srodekY = 0.0;
GLfloat szybkoscX = 0.05, szybkoscY = 0.0;

void initialize()
{
    glClearColor(0.0, 0.2, 0.7, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(5.0);

    /* przy rysowaniu używaj tekstur 2D w trybie DECAL */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    /* stwórz nową teksturę (początkowo pustą) */
    glGenTextures(10, id_tekstury);
    /* wybierz jako bieżącą */
    glBindTexture(GL_TEXTURE_2D, id_tekstury[0]);
    /* ustaw jej parametry */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    /* załaduj dane tekseli */
    tekstura_auto();
    load_texture("tekstury\\inter1.png",&tex_inter1);
    printf("inicjalizacja\n");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_inter1.SX, tex_inter1.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_inter1.img);
    
    glBindTexture(GL_TEXTURE_2D, id_tekstury[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    load_texture("tekstury\\ground.png",&tex_ground);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_ground.SX, tex_ground.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_ground.img);
    
    glBindTexture(GL_TEXTURE_2D, id_tekstury[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    load_texture("tekstury\\sand.png",&tex_sand);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_ground.SX, tex_ground.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_sand.img);
    
    glBindTexture(GL_TEXTURE_2D, id_tekstury[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    load_texture("tekstury\\mud.png",&tex_mud);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_ground.SX, tex_ground.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_mud.img);
    
    glBindTexture(GL_TEXTURE_2D, id_tekstury[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    load_texture("tekstury\\Concrete1.png",&tex_con);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_ground.SX, tex_ground.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_con.img);
    
    glBindTexture(GL_TEXTURE_2D, id_tekstury[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    load_texture("tekstury\\roof.png",&tex_roof);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_ground.SX, tex_ground.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_roof.img);
    
    glBindTexture(GL_TEXTURE_2D, id_tekstury[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    load_texture("terrain_map.png",&tex_mapka);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex_mapka.SX, tex_mapka.SY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_mapka.img);
    
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        
    
}

void reshape(int width, int height)
{
    GLfloat aspect = (GLfloat) width / (GLfloat) height;

    /* wyświetlaj zrzutowaną scenę na całej powierzchni okna */
    glViewport(0, 0, width, height);
    /* wejdź w tryb modyfikacji macierzy rzutowania */
    glMatrixMode(GL_PROJECTION);
    /* zainicjuj macierz rzutowania */
    glLoadIdentity();
    /* załaduj do macierzy parametry projekcji ortograficznej */
    /*
    if (width >= height) {
        glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1);
    } else {
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1);
    }
    */
    gluPerspective(60,1.33,0.1,30);
    /* powróć do trybu pracy z macierzą współrzędnych sceny */
    glMatrixMode(GL_MODELVIEW);
}

void PrintString(GLfloat x, GLfloat y, char *str, GLint N)
{
     GLint i;
     GLfloat dlugosc=0,offset;
     for(i=0;i<N;++i)
     {
                     dlugosc+=glutBitmapWidth(GLUT_BITMAP_HELVETICA_18,str[i]);
     }
     offset=dlugosc/(2.0*800.0)+N*0.005;
     for(i=0;i<N;++i)
     {
                     glRasterPos2f(x-offset,y);
                     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
                     x+=glutBitmapWidth(GLUT_BITMAP_HELVETICA_18,str[i])/800.0+0.01;
     }
}

void hud()
{
     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     
     glScalef(0.75,1,1);
     
     glDisable(GL_COLOR_MATERIAL);
     glDisable(GL_LIGHTING);
     
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,id_tekstury[6]);
     glBegin(GL_QUADS);
     glTexCoord2f(1,1);
     glVertex3f(-0.6,-0.7,0.1);
     glTexCoord2f(0,1);
     glVertex3f(-0.9,-0.7,0.1);
     glTexCoord2f(0,0);
     glVertex3f(-0.9,-0.4,0.1);
     glTexCoord2f(1,0);
     glVertex3f(-0.6,-0.4,0.1);
     glEnd();
     
     glDisable(GL_TEXTURE_2D);
     
     glLineWidth(10);
     glBegin(GL_LINES);
     glColor3f(0,1,0);
     glVertex3f(-0.5,-0.7,0.1);
     glVertex3f(damage/100.0-0.5,-0.7,0.1);
     glEnd();
     glBegin(GL_LINES);
     glColor3f(1,0,0);
     glVertex3f(damage/100.0-0.5,-0.7,0.1);
     glVertex3f(0.5,-0.7,0.1);
     glEnd();
     
     GLint i=0,max;
     GLfloat fi=0;
     max=sqrt(vel.x*vel.x+vel.y*vel.y)/Vmax*90;
     
     glBegin(GL_TRIANGLE_FAN);
     glColor3f(0,1,0);
     glVertex3f(0.75,-0.7,0.1);
     for(i=0;i<max;++i)
     {
                       glColor3f(max/90.0,0,1-max/90.0);
                 fi=i*2/360.0*6.28;
                 glVertex3f(0.75+0.2*cos(3.14-fi),-0.7+0.2*sin(3.14-fi),0.1);
     }
     glEnd();
     
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,id_tekstury[6]);
     glBegin(GL_QUADS);
     glTexCoord2f(1,1);
     glVertex3f(-0.6,-0.7,0.1);
     glTexCoord2f(0,1);
     glVertex3f(-0.9,-0.7,0.1);
     glTexCoord2f(0,0);
     glVertex3f(-0.9,-0.4,0.1);
     glTexCoord2f(1,0);
     glVertex3f(-0.6,-0.4,0.1);
     glEnd();
     
     GLfloat x,y;
     x=-(pos.x-terr_pos.x)/(0.8*teren.SX)*0.3;
     y=-(pos.y-terr_pos.y)/(0.8*teren.SY)*0.3;
     glPointSize(2);
     glColor3f(1,0,0);
     glBegin(GL_POINTS);
     glVertex3f(-0.9+x,-0.7+y,0.09);
     glEnd();
     
     for(i=0;i<6;++i)
     {
                     x=-0.9-(pos_bramki[i].x-terr_pos.x)/(0.8*teren.SX)*0.3;
                     y=-0.7-(pos_bramki[i].y-terr_pos.y)/(0.8*teren.SY)*0.3;
                     if(rys_bramki[i]==0) glColor3f(1,1,1);
                     if(rys_bramki[i]==2) glColor3f(0,1,0);
                     if(rys_bramki[i]==1) glColor3f(0,0,1);
                     glRasterPos2f(x,y);
                     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 49+i);
     }
     
     char str[50];
     GLint time_tmp=(difftime(time_end,time0)*CLOCKS_PER_SEC)/10000.0;
     sprintf(str,"czas: %2i.%2i.%2i",time_tmp/6000,(time_tmp/100)%60,time_tmp%100);
     glColor3f(1,1,1);
     if(game_state==1) PrintString(0,0.5,str,17);
     
     if(game_state==0) 
     {
                       glColor3f(0,1,0);
                       PrintString(0,0.2,"klawisze: strzalki -sterowanie, s -wlacz/wylacz swiatla, q -wyjscie",55);
                       PrintString(0,0.1,"cel: przejedz przez kolejne bramki w jak najkrotszym czasie",59);
                       PrintString(0,0,"Pamietaj, ze beczki czasowo zwiekszaja twoja predkosc",55);
                       PrintString(0,-0.1, "a zderzenia z obiektami uszkadzaja twoj pojazd",47);
                       PrintString(0,-0.2,"aby rozpoczac gre wcisnij spacje",32);
     }
     
     if(game_state==2&&damage>0)
     {
                                glColor3f(0,1,0);
                                sprintf(str,"ukonczyles trase w czasie: %2i.%2i.%2i sekund",time_tmp/6000,(time_tmp/100)%60,time_tmp%100);
                                PrintString(0,0,str,43);
     }
     
     if(game_state==2&&damage<=0)
     {
                                 glColor3f(1,0,0);
                                 PrintString(0,0,"koniec twej drogi wedrowcze :p",30);
     }
     
     if(game_state==2)
     {
                      glColor3f(0,1,0);
                      PrintString(0,-0.1,"Nacisnij R aby rozpoczac od nowa lub Q aby wyjsc z programu",59);
     }
     
     glEnable(GL_TEXTURE_2D);
     glEnable(GL_LIGHTING);
     
     glPopMatrix();
     glMatrixMode(GL_MODELVIEW);
}


void display(void)
{
     GLint i,j,points;
     /* wyczyść ekran */
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    /* zapamiętaj aktualny stan macierzy transformacji */
    glPushMatrix();
    //glRotatef(rotacjaOX,dir.x*cos(1.57079)+dir.y*sin(1.57079),dir.y*cos(1.57079)-dir.x*sin(1.57079),0);
    GLfloat a=2.5;
    gluLookAt(-pos.x+a*dir.x,-pos.y+a*dir.y,pos.z+0.75,-pos.x-dir.x,-pos.y-dir.y,pos.z+0.72,0,0,1);

    if(tryb_kamery==2)
    {
                      glLoadIdentity();
                      glTranslatef(pos.x,pos.y,zoom);
                      
                      //glRotatef(rotacjaOX,0,1,0);
                      //glRotatef(rotacjaOY, 0, 0, 1);
                      
                      
    }
    
    glPushMatrix();
   
    GLfloat ambient[]={0,0,0,1};
    GLfloat light0_pos[]={1,1,0.5,0}, light1_pos[]={-pos.x,-pos.y,-pos.z+3,1};
    GLfloat light1_dir[]={-dir.x,-dir.y,-1.5};
    GLfloat light0_col_d[]={0.8,0.8,0.8,1}, light1_col_d[]={1,1,1,1};
    GLfloat light0_col_s[]={0,0,0,1},light1_col_s[]={1,1,1,1};
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light0_col_s);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_col_d);
    
    glLightfv(GL_LIGHT1,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT1,GL_SPECULAR,light1_col_s);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_col_d);
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light1_dir);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,10);
    glPopMatrix();
    
    draw_terrain(&teren,&terr_n,terr_pos,id_tekstury,&pos);
    
    draw_grass(trawa_pos,drzewko_dir,1000,trawa,0,0);
    draw_grass(trawa_pos2,drzewko_dir,1000,trawa,0,0);
    draw_grass(trawa_pos3,drzewko_dir,1000,trawa,0,0);
    draw_grass(trawa_pos4,drzewko_dir,1000,trawa,0,0);
    draw_grass(trawa_pos5,drzewko_dir,1000,trawa,0,0);
    
    for(i=0;i<200;++i)
    draw_grass(grass_pos[i],grass_dir[i],grass_dens[i],trawa2,grass_fi[i],grass_eta[i]);
    
    draw_model(car,pos,dir,car_n,car_o,180,0.12);
    draw_model(drzewko,drzewko_pos,drzewko_dir,normalny,orto,0,-1.5);
    
    draw_trees(pos_drzew1,dir_drzew1,10,gr_drzew1,drzewko);
    draw_trees(pos_drzew2,dir_drzew2,10,gr_drzew2,drzewko);
    draw_trees(pos_drzew3,dir_drzew3,10,gr_drzew3,drzewko);
    draw_trees(pos_drzew4,dir_drzew4,10,gr_drzew4,drzewko);
    
    draw_barrels(pos_beczki,dir_beczki,rys_beczki,6,beczka);
    draw_gates(pos_bramki,dir_bramki,6,bramka);
    
    draw_triangle(pos,dir,pos_bramki,rys_bramki,6);
    
    glPopMatrix();
    
    hud();
    /* upewnij się, że powyższe polecenia wysłano do GPU */
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
     if(game_state==1)
     {
                      switch(key)
                      {
                      case 27:    /* Esc */
                      case 'q':
                           exit(0);
                           break;
                           case 'z':
                           if ((zoom += 0.5) == 0) zoom = 0;
                           break;
                      case 'y':
                           if ((rotacjaOY += 10) >= 360)
                           rotacjaOY = 0;
                      case 't':
                           if ((rotacjaOX += 10) >= 360)
                           rotacjaOX=0;
                           break;
                      case 'x':
                           zoom -= 0.5;
                           break;
                      case 'k':
                           {if(tryb_kamery==1) tryb_kamery=2;
                           else tryb_kamery=1;
                           break;}
                      case 's':
                           {
                            if(swiatla==1)
                            {swiatla=0;
                            glDisable(GL_LIGHT1);}
                            else
                            {swiatla=1;
                            glEnable(GL_LIGHT1);}
                           }
                      }
     }
     else if(key==32&&game_state!=2) 
     {
          game_state=1;
          time0=clock();
     }
     if(key=='q') exit(0);
     if(game_state==2&&key=='r') restart(&game_state,rys_bramki,6,rys_beczki,6,pos0,&pos,dir0,&dir,&boost,&damage);
    /* poproś system o przerysowanie okna w najbliższej wolnej chwili */
    glutPostRedisplay();
}

void spec_keys(int key, int x, int y)
{
     if(game_state==1)
     {
                      switch(key)
                      {
                                 case GLUT_KEY_UP:
                                 {if((vel.x*vel.x+vel.y*vel.y)<Vmax*Vmax/4.0) forward(&vel,dir,0.01);
                                 break;}
                                 case GLUT_KEY_LEFT:
                                 {turn(&vel,&dir,0.2);
                                 break;}
                                 case GLUT_KEY_RIGHT:
                                 {turn(&vel,&dir,-0.1);
                                 break;}
                                 case GLUT_KEY_DOWN:
                                 {backward(&vel,dir,0.1);
                                 break;}
                      }
     }
}

void animate(int value)
{
     printf("%f %f %f\n", pos.x,pos.y,pos.z);
     GLfloat d_z=0;
     pos.z=height_control(&teren,terr_pos,&pos,&dir,0.8);
     keep_boundaries(&teren,terr_pos,pos,&vel,&dir);
     velocity_control(&dir,&vel);
     pos.x+=vel.x;
     pos.y+=vel.y;
     collision_detection(pos_drzew1,10,&pos,&dir,&vel,&damage,Vmax);
     collision_detection(pos_drzew2,10,&pos,&dir,&vel,&damage,Vmax);
     collision_detection(pos_drzew3,10,&pos,&dir,&vel,&damage,Vmax);
     collision_detection(pos_drzew4,10,&pos,&dir,&vel,&damage,Vmax);
     boost_detection(pos_beczki,rys_beczki,6,pos,&vel,&dir,&boost,Vmax);
     gate_detection(pos_bramki,rys_bramki,6,pos);
     
     car_n=normal_to_terrain(&teren,terr_pos,pos,0.8);
     car_o=third_ortho(dir,car_n);
     check_finish(&game_state,damage,rys_bramki[5],&vel);
     if(game_state!=2)
     {
                                time_end=clock();
     }
    glutPostRedisplay();
    glutTimerFunc(100, animate, 0);
}
 
int main(int argc,char *argv[])
{    
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(1024, 768);
    glutInit(&argc, argv);
    glutCreateWindow("Okno OpenGL");
    initialize();
    set_beginning();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(spec_keys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, animate, 0);
    glutMainLoop();
    
    texture_free(&tex1);
    
    free(teren.map);
    free(pos_drzew1);
    free(dir_drzew1);
    free(pos_drzew2);
    free(dir_drzew2);
    free(pos_drzew3);
    free(dir_drzew3);
    free(pos_drzew4);
    free(dir_drzew4);
    
    free(grass_pos);
    free(grass_dir);
    free(grass_fi);
    free(grass_eta);
    free(grass_dens);
    
    free(pos_beczki);
    free(dir_beczki);
    free(rys_beczki);
    free(pos_bramki);
    free(dir_bramki);
    free(rys_bramki);
    free(trawa);

    return 0;
}

