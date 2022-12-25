#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <math.h>

#include "load_object.h"

void scale(Object* Obj, float* new_array, float mash_scale);
void rotate_vertices(Object* Obj, float* new_array, float rotx, float roty,
                     float rotz);
void shift(Object* Obj, float* new_array, float max, float shiftx, float shifty,
           float shiftz);

#endif  // TRANSFORM_H_
