#ifndef MOVE_H
#define MOVE_H
#include"structs.h"

void forward(struct vec *, struct vec, GLfloat);
void backward(struct vec *, struct vec, GLfloat);
void turn(struct vec *,struct vec *,GLfloat);


void collision(struct vec*,struct vec *,struct vec*,struct vec *,GLfloat*,GLfloat);
void collision_detection(struct vec *,GLint, struct vec *,struct vec*,struct vec*,GLfloat *,GLfloat);
void boost_detection(struct vec*, GLint*, GLint, struct vec, struct vec*, struct vec*, GLint*,GLfloat);

//GLfloat change_height(GLfloat, struct vec, struct vec *);
GLfloat height_control(struct terrain *, struct vec ,struct vec *,struct vec*,GLfloat);

void velocity_control(struct vec*,struct vec*);
void keep_boundaries(struct terrain*, struct vec, struct vec, struct vec*,struct vec*);


struct vec normal_to_terrain(struct terrain*, struct vec,struct vec, GLfloat);
void dir_control(struct vec*,struct vec);
struct vec third_ortho(struct vec, struct vec);

void check_finish(GLint*,GLint,GLint,struct vec*);

void restart(GLint*,GLint*,GLint,GLint*,GLint,struct vec, struct vec*, struct vec, struct vec*,GLint*,GLfloat*);

#endif
