#ifndef LOAD_OBJECT_H_
#define LOAD_OBJECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Obj {
  unsigned *indexies;
  float *vertices;
  unsigned count_index;  // общее количество вершин в полигонах
  unsigned count_faces;   // количество полигонов
  unsigned count_vertex;  // количество вершин
} Object;

int parse(const char *fname, Object *Obj);
void count_elements(FILE *Objfile, Object *Obj);
void get_vertices_n_faces(FILE *Objfile, Object *Obj);
void free_object(Object *Obj);
void normalize(char *str);

#endif  // LOAD_OBJECT_H_
