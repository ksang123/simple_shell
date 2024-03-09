//a simple hashmap implementation to store commands-functions

#define BUCKETS 26
#define MAX_PATH_LEN 50
#define MAX_PATH_DEPTH 20

#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdbool.h>
#include "built_ins.h"


typedef struct {
    char key[MAX_COMMAND_LEN];
    void (*function_ptr)(char command[MAX_COMMAND_LEN], char path[][MAX_PATH_LEN]);
    struct List* next;
} List;

typedef struct {
    List* buckets[BUCKETS]; //'z'-'a' + 1, a bucket for every letter
} HashMap;

HashMap* new_map();
void free_map(HashMap* map);
void free_list(List* list);
void (*get(HashMap* map, char key[MAX_COMMAND_LEN]))(char command[MAX_COMMAND_LEN], char path[][MAX_PATH_LEN]);
void insert(HashMap* map, char key[MAX_COMMAND_LEN], void (*function_ptr)(char command[MAX_COMMAND_LEN], char path[][MAX_PATH_LEN]));


#endif //HASHMAP_H
