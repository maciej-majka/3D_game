#ifndef MODEL_FUN_H
#define MODEL_FUN_H

#include "glm/glm.h"

void draw_model(GLMmodel*,struct vec, struct vec,struct vec, struct vec, GLfloat,GLfloat);
void draw_triangle(struct vec, struct vec, struct vec*,GLint*,GLint);

#endif
