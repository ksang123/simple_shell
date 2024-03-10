#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashmap.h"

HashMap* new_map() {
    HashMap* map = (HashMap*) malloc(sizeof(HashMap));
    if (map == NULL) {
        printf("\033[0;31mMemory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < BUCKETS; i++) {
        map->buckets[i] = NULL;
    }
    return map;
}

void insert(HashMap* map, char key[MAX_INPUT], void (*function_ptr)(char command[MAX_INPUT], char path[][MAX_PATH_LEN])) {
    List* last = map->buckets[key[0]-'a'];
    if (last == NULL) {
        map->buckets[key[0]-'a'] = (List*) malloc(sizeof(List));
        if (map->buckets[key[0]-'a'] == NULL) {
            printf("\033[0;31mMemory allocation failed\n");
            exit(1);
        }
        strcpy(map->buckets[key[0]-'a']->key, key);
        map->buckets[key[0]-'a']->function_ptr = function_ptr;
        map->buckets[key[0]-'a']->next = NULL;
        return;
    }
    while (last->next != NULL) {
        last = (List*) last->next;
    }
    last->next = (struct List *) malloc(sizeof(List));
    last = (List *) last->next;
    if (last == NULL) {
        printf("\033[0;31mMemory allocation failed\n");
        exit(1);
    }
    strcpy(last->key, key);
    last->function_ptr = function_ptr;
    last->next = NULL;
}

void (*get(HashMap* map, char key[MAX_INPUT]))(char command[MAX_INPUT], char path[][MAX_PATH_LEN]) {
    if (strlen(key) == 0) {
        return NULL;
    }
    List* list = map->buckets[key[0]-'a'];
    if (list == NULL) {
        return NULL;
    }
    int len;
    while (list != NULL) {
        len = (int)strlen(list->key);
        if (strncmp(list->key, key, len) == 0 &&
                (key[len] == ' ' || key[len] == '\0')) {
            return list->function_ptr;
        }
        list = (List *) list->next;
    }
    return NULL;
}

void free_map(HashMap* map) {
    if (map == NULL) {
        return;
    }
    for (int i = 0; i < BUCKETS; i++) {
        free_list(map->buckets[i]);
    }
    free(map);
}

void free_list(List* list) {
    while (list != NULL) {
        List* next = (List *) list->next;
        free(list);
        list = next;
    }
}