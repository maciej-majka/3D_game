#ifndef STRUCTS_H
#define STRUCTS_H
#include<stdio.h>
#include<stdlib.h>
#include "glm/glm.h"

struct vec
{
       GLfloat x,y,z;
};

struct texture
{
       GLubyte *img;
       GLsizei SX,SY;
};

struct terrain
{
       GLfloat *map;
       GLint SX,SY;
};

GLfloat* terrain_generation(GLfloat, GLfloat,GLint *,GLint *);
void draw_terrain(struct terrain *,struct terrain *,struct vec,GLint*,struct vec *);
void set_norm_terr(struct terrain *, struct terrain *,struct vec);

GLfloat *gen_grass(GLfloat ,GLfloat ,GLint ,GLfloat *);
void gen_grass2(struct vec*, struct vec*,GLint*,GLint*,GLint, struct terrain*, struct vec);

void draw_grass(struct vec pos, struct vec dir,GLint,GLfloat *,GLfloat,GLfloat);

void trees_generator(struct vec *, struct vec *,GLint ,struct vec , GLfloat ,struct terrain *,struct vec);
void draw_trees(struct vec *, struct vec *, GLint, struct vec,GLMmodel *);

void gen_barrels(struct vec*, struct vec*, GLint*, GLint, struct terrain*, struct vec);
void draw_barrels(struct vec*, struct vec *, GLint*, GLint, GLMmodel*);

void gen_gates(struct vec*, struct vec*, GLint*, GLint, struct terrain*, struct vec);
void draw_gates(struct vec*, struct vec*, GLint, GLMmodel*);
#endif
