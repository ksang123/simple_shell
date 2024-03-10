#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

void bash(char command[MAX_INPUT], char path[][MAX_PATH_LEN]) {
    //TODO: deal with the working directory
    system(&command[5]);
}

void clear(char command[MAX_INPUT], char path[][MAX_PATH_LEN]) {
    printf("\033[2J");
    printf("\033[H");
}