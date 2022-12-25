#include "transform.h"

void scale(Object* Obj, float* new_array, float mash_scale) {
  for (size_t i = 0; i < Obj->count_vertex * 3; i += 3) {
    new_array[i] = Obj->vertices[i] * mash_scale;
    new_array[i + 1] = Obj->vertices[i + 1] * mash_scale;
    new_array[i + 2] = Obj->vertices[i + 2] * mash_scale;
  }
}

void rotate_vertices(Object* Obj, float* new_array, float rotx, float roty,
                     float rotz) {
  for (size_t i = 0; i < Obj->count_vertex * 3; i += 3) {
    float x = new_array[i];
    float y = new_array[i + 1];
    float z = new_array[i + 2];
    float x1 = x;
    float y1 = cos(rotx) * y - sin(rotx) * z;
    float z1 = sin(rotx) * y + cos(rotx) * z;
    float x2 = cos(roty) * x1 + sin(roty) * z1;
    float y2 = y1;
    float z2 = -sin(roty) * x1 + cos(roty) * z1;
    float x3 = cos(rotz) * x2 + sin(rotz) * y2;
    float y3 = -sin(rotz) * x2 + cos(rotz) * y2;
    float z3 = z2;
    new_array[i] = x3;
    new_array[i + 1] = y3;
    new_array[i + 2] = z3;
  }
}

void shift(Object* Obj, float* new_array, float max, float shiftx, float shifty,
           float shiftz) {
  for (size_t i = 0; i < Obj->count_vertex * 3; i += 3) {
    new_array[i] += shiftx * max;
    new_array[i + 1] += shifty * max;
    new_array[i + 2] += shiftz * max;
  }
}
