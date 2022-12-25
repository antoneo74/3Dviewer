#include "load_object.h"

int parse(const char *fname, Object *Obj) {
  FILE *Objfile;
  if ((Objfile = fopen(fname, "r")) == NULL) {
    exit(EXIT_FAILURE);
  } else {
    Obj->count_index = 0;
    Obj->count_faces = 0;
    Obj->count_vertex = 1;
    count_elements(Objfile, Obj);
    get_vertices_n_faces(Objfile, Obj);
    fclose(Objfile);
  }
  return EXIT_SUCCESS;
}

void count_elements(FILE *Objfile, Object *Obj) {
  fseek(Objfile, 0, SEEK_SET);
  char *token, *buff;
  char *str = (char *)calloc(255, sizeof(char));
  while (fgets(str, 255, Objfile) != NULL) {
    if (strstr(str, "v ")) {
      Obj->count_vertex++;
    }
    if (strstr(str, "f ")) {
      token = strtok_r(str, "f \n", &buff);
      while (token != NULL) {
        token = strtok_r(NULL, " f\n", &buff);
        Obj->count_index++;
      }
      Obj->count_faces++;
    }
  }
  free(str);
}

void normalize(char *str) {
  int i = strlen(str) - 2;
  if (i > 1) {
    while (str[i] == ' ' || str[i] == '\r') {
      str[i] = '\n';
      i--;
    }
  }
}

void get_vertices_n_faces(FILE *Objfile, Object *Obj) {
  char *str = (char *)calloc(255, sizeof(char));
  char *token, *buff;
  unsigned i_v = 3, i_f = 0;
  Obj->vertices = (float *)calloc((Obj->count_vertex * 3), sizeof(float));
  Obj->vertices[0] = Obj->vertices[1] = Obj->vertices[2] = 0.0f;
  Obj->indexies = (unsigned *)calloc((Obj->count_index * 2), sizeof(unsigned));
  fseek(Objfile, 0, SEEK_SET);
  while (!feof(Objfile)) {
    fgets(str, 255, Objfile);
    normalize(str);
    if (!strstr(str, "#")) {
      if (strstr(str, "v ")) {
        token = strtok_r(str, "v \n", &buff);
        while (token != NULL) {
          char *tmp;
          Obj->vertices[i_v] = strtod(token, &tmp);
          token = strtok_r(NULL, "v \n", &buff);
          i_v++;
        }
      } else if (strstr(str, "f ")) {
        token = strtok_r(str, "f \n", &buff);
        int first = atoi(token);
        int last = first;
        while ((token = strtok_r(NULL, " \nf", &buff))) {
          int current = atoi(token);
          Obj->indexies[i_f++] = last;
          Obj->indexies[i_f++] = current;
          last = current;
        }
        Obj->indexies[i_f++] = last;
        Obj->indexies[i_f++] = first;
      }
    }
  }
  free(str);
}

void free_object(Object *Obj) {
  if (Obj) {
    if (Obj->vertices) free(Obj->vertices);
    if (Obj->indexies) free(Obj->indexies);
  }
}
